#!/bin/sh
#
# Sync VM <--> Repo.
#
# On copying from virtual disk to src/, the directory is emptied before copy. Comment out "rm -rf ../src/*" to copy onto src.
#
#

# make sure we are in the correct directory
SCRIPT_DIR=$(realpath "$(dirname "$0")")
SCRIPT_NAME=$(basename "$0")
EXPECTED_DIR=$(realpath "$PWD")

# Change this if your default QEMU version does not work and you have installed a different version elsewhere.
QEMU_BIN_PATH=$(dirname "$(which qemu-system-x86_64)")

if test "${EXPECTED_DIR}" != "${SCRIPT_DIR}"
then
	( cd "$SCRIPT_DIR" || exit ; "./$SCRIPT_NAME" "$@" );
	exit
fi


# Uncomment if you use doas instead of sudo
#alias sudo=doas

# Set this
ZEALDISK=
# Examples:
#ZEALDISK=~/VirtualBox\ VMs/ZealOS/ZealOS.vdi
#ZEALDISK=~/vmware/ZealOS/ZealOS.vmdk
#ZEALDISK=ZealOS.qcow2

[ -z "$ZEALDISK" ] && echo "Please edit this script with the full path to your ZealOS virtual disk." && exit 1
[ ! -f "$ZEALDISK" ] && echo "\$ZEALDISK is not a path to a file." && exit 1

# Set this if updating organization homepage github.io docs
DOCS_DIR=
# Example:
#DOCS_DIR=../../zeal-operating-system.github.io/

[ ! -z "$DOCS_DIR" ] && [ ! -d "$DOCS_DIR" ] && echo "\$DOCS_DIR ($DOCS_DIR) does not exist!" && exit 1

TMPMOUNT=/tmp/zealtmp

print_usage() {
	echo "Usage: $0 [ repo | vm ]"
	echo
	echo " repo - overwrites src/ with virtual disk contents."
	echo " vm - overwrites virtual disk with src/ contents."
	echo
}

mount_vdisk() {
	echo "Mounting virtual disk..."
	sudo $QEMU_BIN_PATH/qemu-nbd -c /dev/nbd0 "$ZEALDISK"
	sudo partprobe /dev/nbd0       
	sudo mount /dev/nbd0p1 $TMPMOUNT
}

umount_vdisk() {
	echo "Unmounting virtual disk..."
	sync
	sudo umount $TMPMOUNT
	sudo $QEMU_BIN_PATH/qemu-nbd -d /dev/nbd0
	sudo rm -rf $TMPMOUNT
}

if [ -z $1 ]
then
	print_usage
else
	sudo modprobe nbd
	[ ! -d $TMPMOUNT ] && mkdir $TMPMOUNT
	case $1 in
		repo)
			echo "Emptying src..."
			rm -rf ../src/*
			mount_vdisk
			echo "Copying vdisk root to src..."
			cp -r $TMPMOUNT/* ../src
			rm ../src/Boot/BootMHD2.BIN
			if [ -d $TMPMOUNT/HTML ] && [ ! -z $DOCS_DIR ]
			then
			        echo "Copying HTML docs to \$DOCS_DIR ($DOCS_DIR)..."
			        rm -rf $DOCS_DIR/*
			        cp -r $TMPMOUNT/HTML/* $DOCS_DIR
			        rm -rf ../src/HTML/
			fi
			umount_vdisk
			[ -f ../src/Tmp/AUTO.ISO.C ] && mv ../src/Tmp/AUTO.ISO.C ./AUTO.ISO
			echo "Finished."
			git status
			;;
		vm)
			mount_vdisk
			echo "Copying src to vdisk..."
			sudo cp -r ../src/* $TMPMOUNT
			umount_vdisk
			echo "Finished."
			;;
		*)
			echo "Unknown action."
			print_usage
			;;
	esac
fi
