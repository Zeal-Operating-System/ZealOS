#!/bin/bash

# Sync repo --> VM
# (copy src/ to VM. Kernel code changes won't be reflected in VM until running BootHDIns; to recompile kernel.)

# Run this script inside build/ directory

sudo modprobe nbd

echo "Edit this script first to pick your VM path & file!"
exit # Comment this line out

# Uncomment ONE of the next lines and edit it to point to your VM HDD
# sudo qemu-nbd -c dev/nbd0 ~/VirtualBox\ VMs/ZealOS/ZealOS.vdi
# sudo qemu-nbd -c dev/nbd0 ~/vmware/ZealOS/ZealOS.vmdk
# sudo qemu-nbd -c dev/nbd0 ZealOS.qcow2

sudo partprobe /dev/nbd0
sudo mkdir /tmp/zealtmp
sudo mount /dev/nbd0p1 /tmp/zealtmp
echo "Merging with src/"
sudo cp -r ../src/* /tmp/zealtmp
sudo sync
echo "Files copied, unmounting"
sudo umount /tmp/zealtmp
sudo qemu-nbd -d /dev/nbd0
sudo rm -rf /tmp/zealtmp
sudo sync
echo "finished."
