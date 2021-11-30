#!/bin/bash

# Build Distro ISO using AUTO.ISO minimal auto-install as bootstrap to merge codebase, recompile system, and export ISO

# Run this script inside build/ directory

echo "Making temp HDD, running auto-install"
qemu-img create -f raw ZealOS.raw 192M
qemu-system-x86_64 -machine q35,kernel_irqchip=off,accel=kvm -drive format=raw,file=ZealOS.raw -m 2G -smp $(nproc) -rtc base=localtime -cdrom AUTO.ISO -device isa-debug-exit
echo "Mounting"
sudo mkdir /tmp/zealtmp/
sudo rm /tmp/zealtmp/* -r
sudo sync
sudo modprobe nbd
sudo qemu-nbd -c dev/nbd0 -f raw ./ZealOS.raw
sudo partprobe /dev/nbd0
echo "Merging with src/"
sudo mount /dev/nbd0p1 /tmp/zealtmp
rm ../src/Home/Registry.CC # we use Registry for auto-iso process, don't want to overwrite
rm ../src/Home/MakeHome.CC # unneeded file
sudo cp -r ../src/* /tmp/zealtmp/
sudo sync
echo "Files copied, unmounting"
sudo umount /tmp/zealtmp
sudo qemu-nbd -d /dev/nbd0
sudo rm /tmp/zealtmp/* -r
sudo sync
qemu-system-x86_64 -machine q35,kernel_irqchip=off,accel=kvm -drive format=raw,file=ZealOS.raw -m 2G -smp $(nproc) -rtc base=localtime -device isa-debug-exit
echo "Mounting"
sudo rm /tmp/zealtmp/* -r
sudo sync
sudo modprobe nbd
sudo qemu-nbd -c dev/nbd0 -f raw ./ZealOS.raw
sudo partprobe /dev/nbd0
sudo mount /dev/nbd0p1 /tmp/zealtmp
echo "Extracting Distro ISO"
sudo rm ./ZealOS-*.iso # comment this line if you want lingering old ISOs
sudo cp /tmp/zealtmp/Tmp/MyDistro.ISO.C ./ZealOS-$(date +%Y-%m-%d-%H_%M_%S).iso
sudo chown -R $USER:$USER ./ZealOS-*.iso
echo "Files copied, unmounting"
sudo umount /tmp/zealtmp
sudo qemu-nbd -d /dev/nbd0
sudo rm /tmp/zealtmp/* -r
sudo sync
echo "Deleting temp HDD"
rm ./ZealOS.raw
echo "Deleting temp mount folder"
sudo rm -rf /tmp/zealtmp
echo "Done, build/ contents:"
ls
