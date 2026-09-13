#!/bin/sh

set -e

# Build OS using AUTO.ISO minimal auto-install as bootstrap to merge codebase, recompile system, attempt build limine UEFI hybrid ISO

# make sure we are in the correct directory
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd -P)"
SCRIPT_NAME="$(basename "$0")"
EXPECTED_DIR="$(pwd -P)"

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

TMPDIR="$(mktemp -d)"
TMPISODIR="$TMPDIR/iso"
TMPDISK="$TMPDIR/ZealOS.raw"
TMPMOUNT="$TMPDIR/mnt"

# Change this if your default QEMU version does not work and you have installed a different version elsewhere.
QEMU_BIN_PATH="$(dirname "$(which qemu-system-x86_64)")"

mount_tempdisk() {
	sudo modprobe nbd
	sudo "$QEMU_BIN_PATH/qemu-nbd" -c /dev/nbd0 -f raw "$TMPDISK"
	sudo partprobe /dev/nbd0 || true
	sudo mount /dev/nbd0p1 "$TMPMOUNT"
}

umount_tempdisk() {
	sync
	sudo umount "$TMPMOUNT"
	sudo "$QEMU_BIN_PATH/qemu-nbd" -d /dev/nbd0
}

script_cleanup() {
    sync

    sudo umount "$TMPMOUNT" >/dev/null 2>&1 || true
    sudo "$QEMU_BIN_PATH/qemu-nbd" -d /dev/nbd0 >/dev/null 2>&1 || true

    echo "Deleting temp folder ..."
    sudo rm -rf "$TMPDIR"
    sudo rm -rf "$TMPISODIR"
}

trap 'script_cleanup' EXIT

mkdir -p "$TMPMOUNT"
mkdir -p "$TMPISODIR"

echo "Building ZealBooter..."
make -C ../zealbooter distclean all || ( echo "ERROR: ZealBooter build failed !" && false )

echo "Making temp vdisk, running auto-install ..."
"$QEMU_BIN_PATH/qemu-img" create -f raw "$TMPDISK" 1024M
"$QEMU_BIN_PATH/qemu-system-x86_64" -machine q35 $KVM -drive format=raw,file="$TMPDISK" -m 1G -rtc base=localtime -smp 4 -cdrom AUTO.ISO -device isa-debug-exit $QEMU_HEADLESS || true

echo "Copying all src/ code into vdisk Tmp/OSBuild/ ..."
rm -f ../src/Home/Registry.ZC
rm -f ../src/Home/MakeHome.ZC
rm -f ../src/Boot/Kernel.ZXE
mount_tempdisk
sudo mkdir -p "$TMPMOUNT/Tmp/OSBuild"
sudo cp -r ../src/* "$TMPMOUNT/Tmp/OSBuild/"
umount_tempdisk

echo "Rebuilding kernel headers, kernel, OS, and building Distro ISO ..."
"$QEMU_BIN_PATH/qemu-system-x86_64" -machine q35 $KVM -drive format=raw,file="$TMPDISK" -m 1G -rtc base=localtime -smp 4 -device isa-debug-exit $QEMU_HEADLESS || true

if [ ! -d "limine-binary" ]
then
	echo "Downloading latest Limine binary release ..."
	rm -f limine-binary.tar.gz
	curl -fL -o limine-binary.tar.gz https://github.com/Limine-Bootloader/Limine/releases/latest/download/limine-binary.tar.gz
	gunzip < limine-binary.tar.gz | tar -xf -
	rm -f limine-binary.tar.gz
fi

touch limine-binary/Limine-BIOS-HDD.HH
echo "/*\$WW,1\$" > limine-binary/Limine-BIOS-HDD.HH
cat limine-binary/LICENSE >> limine-binary/Limine-BIOS-HDD.HH
echo "*/\$WW,0\$" >> limine-binary/Limine-BIOS-HDD.HH
cat limine-binary/limine-bios-hdd.h >> limine-binary/Limine-BIOS-HDD.HH
sed -i 's/const uint8_t/U8/g' limine-binary/Limine-BIOS-HDD.HH
sed -i "s/\[\]/\[$(grep -o "0x" ./limine-binary/limine-bios-hdd.h | wc -l)\]/g" limine-binary/Limine-BIOS-HDD.HH

mount_tempdisk
echo "Extracting MyDistro ISO from vdisk ..."
cp "$TMPMOUNT/Tmp/MyDistro.ISO.C" ./ZealOS-MyDistro.iso
sudo rm -f "$TMPMOUNT/Tmp/MyDistro.ISO.C"
echo "Setting up temp ISO directory contents for use with limine xorriso command ..."
sudo cp -rf "$TMPMOUNT"/* "$TMPISODIR/"
sudo rm -f "$TMPISODIR/Boot/OldMBR.BIN"
sudo rm -f "$TMPISODIR/Boot/BootMHD2.BIN"
sudo mkdir -p "$TMPISODIR/EFI/BOOT"
sudo cp limine-binary/Limine-BIOS-HDD.HH "$TMPISODIR/Boot/Limine-BIOS-HDD.HH"
sudo cp limine-binary/BOOTX64.EFI "$TMPISODIR/EFI/BOOT/BOOTX64.EFI"
sudo cp limine-binary/BOOTIA32.EFI "$TMPISODIR/EFI/BOOT/BOOTIA32.EFI"
sudo cp limine-binary/limine-uefi-cd.bin "$TMPISODIR/Boot/Limine-UEFI-CD.BIN"
sudo cp limine-binary/limine-bios-cd.bin "$TMPISODIR/Boot/Limine-BIOS-CD.BIN"
sudo cp limine-binary/limine-bios.sys "$TMPISODIR/Boot/Limine-BIOS.SYS"
sudo cp ../zealbooter/bin/kernel "$TMPISODIR/Boot/ZealBooter.ELF"
sudo cp ../zealbooter/limine.conf "$TMPISODIR/Boot/Limine.CONF"
echo "Copying DVDKernel.ZXE over ISO Boot/Kernel.ZXE ..."
sudo mv "$TMPMOUNT/Tmp/DVDKernel.ZXE" "$TMPISODIR/Boot/Kernel.ZXE"
sudo rm -f "$TMPISODIR/Tmp/DVDKernel.ZXE"
umount_tempdisk

# ZealOS only boots off optical media, but the GPT stays, as the kernel
# finds the disc it booted from by its disk GUID.
xorriso -as mkisofs -R -r -J -b Boot/Limine-BIOS-CD.BIN \
        -no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
        -apm-block-size 2048 --efi-boot Boot/Limine-UEFI-CD.BIN \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        "$TMPISODIR" -o ZealOS-limine.iso

if [ "$TESTING" = true ]; then
	if [ ! -d "edk2-ovmf-bins" ]; then
	    echo "Downloading OVMF..."
	    curl -fL -o edk2-ovmf-bins.tar.gz https://github.com/osdev0/edk2-ovmf-stable-bins/releases/latest/download/edk2-ovmf-bins.tar.gz
	    gunzip < edk2-ovmf-bins.tar.gz | tar -xf -
	    rm -f edk2-ovmf-bins.tar.gz
	fi
	echo "Testing limine-zealbooter-xorriso isohybrid boot in UEFI mode ..."
	"$QEMU_BIN_PATH/qemu-system-x86_64" -machine q35 $KVM -m 1G -rtc base=localtime -drive if=pflash,unit=0,format=raw,file=edk2-ovmf-bins/ovmf-code-x86_64.fd,readonly=on -smp 4 -cdrom ZealOS-limine.iso $QEMU_HEADLESS
	echo "Testing limine-zealbooter-xorriso isohybrid boot in BIOS mode ..."
	"$QEMU_BIN_PATH/qemu-system-x86_64" -machine q35 $KVM -m 1G -rtc base=localtime -smp 4 -cdrom ZealOS-limine.iso $QEMU_HEADLESS
	echo "Testing native ZealC MyDistro legacy ISO in BIOS mode ..."
	"$QEMU_BIN_PATH/qemu-system-x86_64" -machine q35 $KVM -m 1G -rtc base=localtime -smp 4 -cdrom ZealOS-MyDistro.iso $QEMU_HEADLESS
fi

# comment these 2 lines if you want lingering old Distro ISOs
rm -f ./ZealOS-PublicDomain-BIOS-*.iso
rm -f ./ZealOS-BSD2-UEFI-*.iso

mv ./ZealOS-MyDistro.iso ./ZealOS-PublicDomain-BIOS-$(date +%Y-%m-%d-%H_%M_%S).iso
mv ./ZealOS-limine.iso ./ZealOS-BSD2-UEFI-$(date +%Y-%m-%d-%H_%M_%S).iso

echo "Finished."
echo
echo "ISOs built:"
ls | grep ZealOS-P
ls | grep ZealOS-B
echo
