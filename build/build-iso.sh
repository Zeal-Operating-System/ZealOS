#!/bin/sh

# Build OS using AUTO.ISO minimal auto-install as bootstrap to merge codebase, recompile system, attempt build limine UEFI hybrid ISO

# make sure we are in the correct directory
SCRIPT_DIR=$(realpath "$(dirname "$0")")
SCRIPT_NAME=$(basename "$0")
EXPECTED_DIR=$(realpath "$PWD")

if test "${EXPECTED_DIR}" != "${SCRIPT_DIR}"
then
	( cd "$SCRIPT_DIR" || exit ; "./$SCRIPT_NAME" "$@" );
	exit
fi

[ "$1" = "--headless" ] && QEMU_HEADLESS='-display none'

KVM=''
(lsmod | grep -q kvm) && KVM=' -accel kvm'

# Set this true if you want to test ISOs in QEMU after building.
TESTING=false

TMPDIR="/tmp/zealtmp"
TMPISODIR="$TMPDIR/iso"
TMPDISK="$TMPDIR/ZealOS.raw"
TMPMOUNT="$TMPDIR/mnt"

# Change this if your default QEMU version does not work and you have installed a different version elsewhere.
QEMU_BIN_PATH=$(dirname "$(which qemu-system-x86_64)")

mount_tempdisk() {
	sudo modprobe nbd
	sudo $QEMU_BIN_PATH/qemu-nbd -c /dev/nbd0 -f raw $TMPDISK
	sudo partprobe /dev/nbd0
	sudo mount /dev/nbd0p1 $TMPMOUNT
}

umount_tempdisk() {
	sync
	sudo umount $TMPMOUNT
	sudo $QEMU_BIN_PATH/qemu-nbd -d /dev/nbd0
}

[ ! -d $TMPMOUNT ] && mkdir -p $TMPMOUNT
[ ! -d $TMPISODIR ] && mkdir -p $TMPISODIR

set -e
echo "Building ZealBooter..."
( cd ../zealbooter && make distclean all || echo "ERROR: ZealBooter build failed !")
set +e

echo "Making temp vdisk, running auto-install ..."
$QEMU_BIN_PATH/qemu-img create -f raw $TMPDISK 1024M
$QEMU_BIN_PATH/qemu-system-x86_64 -machine q35 $KVM -drive format=raw,file=$TMPDISK -m 1G -rtc base=localtime -smp 4 -cdrom AUTO.ISO -device isa-debug-exit $QEMU_HEADLESS

echo "Copying all src/ code into vdisk Tmp/OSBuild/ ..."
rm ../src/Home/Registry.ZC 2> /dev/null
rm ../src/Home/MakeHome.ZC 2> /dev/null
rm ../src/Boot/Kernel.ZXE 2> /dev/null
mount_tempdisk
sudo mkdir $TMPMOUNT/Tmp/OSBuild/
sudo cp -r ../src/* $TMPMOUNT/Tmp/OSBuild
umount_tempdisk

echo "Rebuilding kernel headers, kernel, OS, and building Distro ISO ..."
$QEMU_BIN_PATH/qemu-system-x86_64 -machine q35 $KVM -drive format=raw,file=$TMPDISK -m 1G -rtc base=localtime -smp 4 -device isa-debug-exit $QEMU_HEADLESS

LIMINE_BINARY_BRANCH="v8.x-binary"

if [ -d "limine" ]
then
	cd limine
	git remote set-branches origin $LIMINE_BINARY_BRANCH
	git fetch
	git remote set-head origin $LIMINE_BINARY_BRANCH
	git switch $LIMINE_BINARY_BRANCH
	git config --local pull.ff true
	git config --local pull.rebase true
	git pull
	rm limine

	cd ..
fi
if [ ! -d "limine" ]; then
    git clone https://github.com/limine-bootloader/limine.git --branch=$LIMINE_BINARY_BRANCH --depth=1
fi
make -C limine

touch limine/Limine-BIOS-HDD.HH
echo "/*\$WW,1\$" > limine/Limine-BIOS-HDD.HH
cat limine/LICENSE >> limine/Limine-BIOS-HDD.HH
echo "*/\$WW,0\$" >> limine/Limine-BIOS-HDD.HH
cat limine/limine-bios-hdd.h >> limine/Limine-BIOS-HDD.HH
sed -i 's/const uint8_t/U8/g' limine/Limine-BIOS-HDD.HH
sed -i "s/\[\]/\[$(grep -o "0x" ./limine/limine-bios-hdd.h | wc -l)\]/g" limine/Limine-BIOS-HDD.HH

mount_tempdisk
echo "Extracting MyDistro ISO from vdisk ..."
cp $TMPMOUNT/Tmp/MyDistro.ISO.C ./ZealOS-MyDistro.iso
sudo rm $TMPMOUNT/Tmp/MyDistro.ISO.C 2> /dev/null
echo "Setting up temp ISO directory contents for use with limine xorriso command ..."
sudo cp -rf $TMPMOUNT/* $TMPISODIR
sudo rm $TMPISODIR/Boot/OldMBR.BIN 2> /dev/null
sudo rm $TMPISODIR/Boot/BootMHD2.BIN 2> /dev/null
sudo mkdir -p $TMPISODIR/EFI/BOOT
sudo cp limine/Limine-BIOS-HDD.HH $TMPISODIR/Boot/Limine-BIOS-HDD.HH
sudo cp limine/BOOTX64.EFI $TMPISODIR/EFI/BOOT/BOOTX64.EFI
sudo cp limine/limine-uefi-cd.bin $TMPISODIR/Boot/Limine-UEFI-CD.BIN
sudo cp limine/limine-bios-cd.bin $TMPISODIR/Boot/Limine-BIOS-CD.BIN
sudo cp limine/limine-bios.sys $TMPISODIR/Boot/Limine-BIOS.SYS
sudo cp ../zealbooter/bin/kernel $TMPISODIR/Boot/ZealBooter.ELF
sudo cp ../zealbooter/limine.conf $TMPISODIR/Boot/Limine.CONF
echo "Copying DVDKernel.ZXE over ISO Boot/Kernel.ZXE ..."
sudo mv $TMPMOUNT/Tmp/DVDKernel.ZXE $TMPISODIR/Boot/Kernel.ZXE
sudo rm $TMPISODIR/Tmp/DVDKernel.ZXE 2> /dev/null
umount_tempdisk

xorriso -joliet "on" -rockridge "on" -as mkisofs -b Boot/Limine-BIOS-CD.BIN \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        --efi-boot Boot/Limine-UEFI-CD.BIN \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        $TMPISODIR -o ZealOS-limine.iso

./limine/limine bios-install ZealOS-limine.iso

if [ "$TESTING" = true ]; then
	if [ ! -d "ovmf" ]; then
	    echo "Downloading OVMF..."
	    mkdir ovmf
	    cd ovmf
	    curl -o OVMF-X64.zip https://efi.akeo.ie/OVMF/OVMF-X64.zip
	    7z x OVMF-X64.zip
	    cd ..
	fi
	echo "Testing limine-zealbooter-xorriso isohybrid boot in UEFI mode ..."
	$QEMU_BIN_PATH/qemu-system-x86_64 -machine q35 $KVM -m 1G -rtc base=localtime -bios ovmf/OVMF.fd -smp 4 -cdrom ZealOS-limine.iso $QEMU_HEADLESS
	echo "Testing limine-zealbooter-xorriso isohybrid boot in BIOS mode ..."
	$QEMU_BIN_PATH/qemu-system-x86_64 -machine q35 $KVM -m 1G -rtc base=localtime -smp 4 -cdrom ZealOS-limine.iso $QEMU_HEADLESS
	echo "Testing native ZealC MyDistro legacy ISO in BIOS mode ..."
	$QEMU_BIN_PATH/qemu-system-x86_64 -machine q35 $KVM -m 1G -rtc base=localtime -smp 4 -cdrom ZealOS-MyDistro.iso $QEMU_HEADLESS
fi

# comment these 2 lines if you want lingering old Distro ISOs
rm ./ZealOS-PublicDomain-BIOS-*.iso 2> /dev/null
rm ./ZealOS-BSD2-UEFI-*.iso 2> /dev/null

mv ./ZealOS-MyDistro.iso ./ZealOS-PublicDomain-BIOS-$(date +%Y-%m-%d-%H_%M_%S).iso
mv ./ZealOS-limine.iso ./ZealOS-BSD2-UEFI-$(date +%Y-%m-%d-%H_%M_%S).iso

echo "Deleting temp folder ..."
sudo rm -rf $TMPDIR
sudo rm -rf $TMPISODIR
echo "Finished."
echo
echo "ISOs built:"
ls | grep ZealOS-P
ls | grep ZealOS-B
echo
