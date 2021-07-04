#!/bin/bash
echo "mounting..."
sudo modprobe nbd
#sudo qemu-nbd -c dev/nbd0 ~/VirtualBox\ VMs/ZealOS/ZealOS.vdi #Replace with path to disk
sudo qemu-nbd -c dev/nbd0 ~/vmware/ZealOS/ZealOS.vmdk #Replace with path to disk
sudo partprobe /dev/nbd0
sudo mount /dev/nbd0p1 /mnt
echo "mounted .vdi"

