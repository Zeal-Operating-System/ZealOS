#!/bin/sh
# Robust extract of Kernel.ZXE (and optionally RAMDistro.BIN) from ZealOS.qcow2.
# Run from build/ with the VM SHUT DOWN.
set -e
DISK=ZealOS.qcow2
MNT=/tmp/zealtmp

[ -f "$DISK" ] || { echo "No $DISK in $(pwd)"; exit 1; }

# Fail if QEMU still has the disk open (would give a stale read).
if command -v fuser >/dev/null 2>&1 && sudo fuser "$DISK" >/dev/null 2>&1; then
	echo "ERROR: $DISK is in use (VM still running?). Shut down the VM first."
	exit 1
fi

sudo modprobe nbd
# Tear down any stale connection/mount from a previous run.
sudo umount "$MNT" 2>/dev/null || true
sudo qemu-nbd -d /dev/nbd0 2>/dev/null || true
sleep 1

sudo qemu-nbd -c /dev/nbd0 "$DISK"
sudo partprobe /dev/nbd0
sleep 1
sudo mkdir -p "$MNT"
sudo mount /dev/nbd0p1 "$MNT"

echo -n "Kernel.ZXE: "; sudo stat -c '%y  (%s bytes)' "$MNT/Boot/Kernel.ZXE"

sudo cp "$MNT/Boot/Kernel.ZXE" ./Kernel.ZXE
[ "$1" = "--image" ] && sudo cp "$MNT/Tmp/RAMDistro.BIN" ./RAMDistro.BIN
sudo chown "$(id -u):$(id -g)" ./Kernel.ZXE
[ -f ./RAMDistro.BIN ] && sudo chown "$(id -u):$(id -g)" ./RAMDistro.BIN || true

sync
sudo umount "$MNT"
sudo qemu-nbd -d /dev/nbd0
echo "Extracted Kernel.ZXE: $(stat -c '%y (%s bytes)' ./Kernel.ZXE)"
