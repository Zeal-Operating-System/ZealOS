#!/bin/sh

# Build Distro ISO using AUTO.ISO minimal auto-install as bootstrap to merge codebase, recompile system, and export ISO

# make sure we are in the correct directory
SCRIPT_DIR=$(realpath "$(dirname "$0")")
SCRIPT_NAME=$(basename "$0")
EXPECTED_DIR=$(realpath "$PWD")

if test "${EXPECTED_DIR}" != "${SCRIPT_DIR}"
then
	( cd "$SCRIPT_DIR" || exit ; "./$SCRIPT_NAME" );
	exit
fi

# Uncomment if you use doas instead of sudo
#alias sudo=doas 

TMPDIR="/tmp/zealtmp"
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

echo "Making temp vdisk, running auto-install..."
qemu-img create -f raw $TMPDISK 192M
qemu-system-x86_64 -machine q35,accel=kvm -drive format=raw,file=$TMPDISK -m 1G -rtc base=localtime -cdrom AUTO.ISO -device isa-debug-exit

echo "Mounting vdisk and copying src/..."
rm ../src/Home/Registry.ZC 2> /dev/null
rm ../src/Home/MakeHome.ZC 2> /dev/null
mount_tempdisk
sudo cp -r ../src/* $TMPMOUNT
umount_tempdisk

echo "Generating ISO..."
qemu-system-x86_64 -machine q35,accel=kvm -drive format=raw,file=$TMPDISK -m 1G -rtc base=localtime -device isa-debug-exit

echo "Extracting ISO from vdisk..."
rm ./ZealOS-*.iso 2> /dev/null # comment this line if you want lingering old ISOs
mount_tempdisk
cp $TMPMOUNT/Tmp/MyDistro.ISO.C ./ZealOS-$(date +%Y-%m-%d-%H_%M_%S).iso 
umount_tempdisk

echo "Deleting temp folder..."
rm -rf $TMPDIR
echo "Finished."
ls -lh ZealOS-*.iso

