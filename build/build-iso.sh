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

# Uncomment if you use doas instead of sudo
#alias sudo=doas 

TMPDIR="/tmp/zealtmp"
TMPISODIR="$TMPDIR/iso"
TMPDISK="$TMPDIR/ZealOS.raw"
TMPMOUNT="$TMPDIR/mnt"

mount_tempdisk() {
	sudo modprobe nbd
	sudo qemu-nbd -c /dev/nbd0 -f raw $TMPDISK
	sudo partprobe /dev/nbd0
	sudo mount /dev/nbd0p1 $TMPMOUNT
}

umount_tempdisk() {
	sync
	sudo umount $TMPMOUNT
	sudo qemu-nbd -d /dev/nbd0
}

[ ! -d $TMPMOUNT ] && mkdir -p $TMPMOUNT
[ ! -d $TMPISODIR ] && mkdir -p $TMPISODIR

set -e
echo "Building ZealBooter..."
( cd ../zealbooter && make distclean all )
set +e

echo "Making temp vdisk, running auto-install ..."
qemu-img create -f raw $TMPDISK 192M
qemu-system-x86_64 -machine q35,accel=kvm -drive format=raw,file=$TMPDISK -m 1G -rtc base=localtime -smp 4 -cdrom AUTO.ISO -device isa-debug-exit

echo "Copying src/Kernel/KStart16.ZC and src/Kernel/KernelA.HH into vdisk ..."
rm ../src/Home/Registry.ZC 2> /dev/null
rm ../src/Home/MakeHome.ZC 2> /dev/null
mount_tempdisk
sudo cp -rf ../src/Kernel/KStart16.ZC $TMPMOUNT/Kernel/
sudo cp -rf ../src/Kernel/KernelA.HH $TMPMOUNT/Kernel/
umount_tempdisk

echo "Rebuilding kernel headers ..."
qemu-system-x86_64 -machine q35,accel=kvm -drive format=raw,file=$TMPDISK -m 1G -rtc base=localtime -smp 4 -device isa-debug-exit

echo "Copying all kernel code into vdisk ..."
rm ../src/Home/Registry.ZC 2> /dev/null
rm ../src/Home/MakeHome.ZC 2> /dev/null
mount_tempdisk
sudo cp -rf ../src/Kernel/* $TMPMOUNT/Kernel/
umount_tempdisk

echo "Rebuilding kernel..."
qemu-system-x86_64 -machine q35,accel=kvm -drive format=raw,file=$TMPDISK -m 1G -rtc base=localtime -smp 4 -device isa-debug-exit

echo "Copying all src/ code into vdisk ..."
rm ../src/Home/Registry.ZC 2> /dev/null
rm ../src/Home/MakeHome.ZC 2> /dev/null
rm ../src/Boot/Kernel.ZXE 2> /dev/null
mount_tempdisk
sudo cp -r ../src/* $TMPMOUNT
umount_tempdisk

echo "Building Distro ISO ..."
qemu-system-x86_64 -machine q35,accel=kvm -drive format=raw,file=$TMPDISK -m 1G -rtc base=localtime -smp 4 -device isa-debug-exit

LIMINE_BINARY_BRANCH="v4.x-branch-binary"

if [ -d "limine" ]
then
	cd limine
	git remote set-branches origin $LIMINE_BINARY_BRANCH
	git fetch
	git remote set-head origin $LIMINE_BINARY_BRANCH
	git switch $LIMINE_BINARY_BRANCH
	git pull
	rm limine-deploy
	rm limine-version

	cd ..
fi
if [ ! -d "limine" ]; then
    git clone https://github.com/limine-bootloader/limine.git --branch=$LIMINE_BINARY_BRANCH --depth=1
fi
make -C limine

touch limine/Limine-HDD.HH
echo "/*\$WW,1\$" > limine/Limine-HDD.HH
cat limine/LICENSE.md >> limine/Limine-HDD.HH
echo "*/\$WW,0\$" >> limine/Limine-HDD.HH
cat limine/limine-hdd.h >> limine/Limine-HDD.HH
sed -i 's/const uint8_t/U8/g' limine/Limine-HDD.HH
sed -i "s/\[\]/\[$(grep -o "0x" ./limine/limine-hdd.h | wc -l)\]/g" limine/Limine-HDD.HH

mount_tempdisk
echo "Extracting MyDistro ISO from vdisk ..."
cp $TMPMOUNT/Tmp/MyDistro.ISO.C ./ZealOS-MyDistro.iso
sudo rm $TMPMOUNT/Tmp/MyDistro.ISO.C 2> /dev/null
echo "Setting up temp ISO directory contents for use with limine xorriso command ..."
sudo cp -rf $TMPMOUNT/* $TMPISODIR
sudo rm $TMPISODIR/Boot/OldMBR.BIN 2> /dev/null
sudo rm $TMPISODIR/Boot/BootMHD2.BIN 2> /dev/null
sudo mkdir -p $TMPISODIR/EFI/BOOT
sudo cp limine/Limine-HDD.HH $TMPISODIR/Boot/Limine-HDD.HH
sudo cp limine/BOOTX64.EFI $TMPISODIR/EFI/BOOT/BOOTX64.EFI
sudo cp limine/limine-cd-efi.bin $TMPISODIR/Boot/Limine-CD-EFI.BIN
sudo cp limine/limine-cd.bin $TMPISODIR/Boot/Limine-CD.BIN
sudo cp limine/limine.sys $TMPISODIR/Boot/Limine.SYS
sudo cp ../zealbooter/zealbooter.elf $TMPISODIR/Boot/ZealBooter.ELF
sudo cp ../zealbooter/Limine.CFG $TMPISODIR/Boot/Limine.CFG
echo "Copying DVDKernel.ZXE over ISO Boot/Kernel.ZXE ..."
sudo mv $TMPMOUNT/Tmp/DVDKernel.ZXE $TMPISODIR/Boot/Kernel.ZXE
sudo rm $TMPISODIR/Tmp/DVDKernel.ZXE 2> /dev/null
umount_tempdisk

sudo ls $TMPISODIR -al

xorriso -joliet "on" -rockridge "on" -as mkisofs -b Boot/Limine-CD.BIN \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        --efi-boot Boot/Limine-CD-EFI.BIN \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        $TMPISODIR -o ZealOS-UEFI-limine-dev.iso

./limine/limine-deploy ZealOS-UEFI-limine-dev.iso

if [ ! -d "ovmf" ]; then
    echo "Downloading OVMF..."
    mkdir ovmf
    cd ovmf
    curl -o OVMF-X64.zip https://efi.akeo.ie/OVMF/OVMF-X64.zip
    7z x OVMF-X64.zip
    cd ..
fi

echo "Testing limine-zealbooter-xorriso isohybrid boot in UEFI mode ..."
qemu-system-x86_64 -machine q35,accel=kvm -m 1G -rtc base=localtime -bios ovmf/OVMF.fd -smp 4 -cdrom ZealOS-UEFI-limine-dev.iso
echo "Testing limine-zealbooter-xorriso isohybrid boot in BIOS mode ..."
qemu-system-x86_64 -machine q35,accel=kvm -m 1G -rtc base=localtime -smp 4 -cdrom ZealOS-UEFI-limine-dev.iso

echo "Testing native ZealC MyDistro legacy ISO in BIOS mode ..."
qemu-system-x86_64 -machine q35,accel=kvm -m 1G -rtc base=localtime -smp 4 -cdrom ZealOS-MyDistro.iso

rm ./ZealOS-2*.iso 2> /dev/null # comment this line if you want lingering old Distro ISOs
mv ./ZealOS-MyDistro.iso ./ZealOS-$(date +%Y-%m-%d-%H_%M_%S).iso

echo "Deleting temp folder ..."
sudo rm -rf $TMPDIR
sudo rm -rf $TMPISODIR
echo "Finished."
