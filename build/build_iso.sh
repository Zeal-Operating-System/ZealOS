#!/bin/bash
# Run this script inside build/ directory
echo "Making temp HDD, running auto-install"
qemu-img create -f raw ZealOS.raw 256M
qemu-system-x86_64 -machine q35,kernel_irqchip=off,accel=kvm -drive format=raw,file=ZealOS.raw -m 2G -smp $(nproc) -rtc base=localtime -cdrom AUTO.ISO -device isa-debug-exit
echo "Mounting"
sudo rm /mnt/* -r
sudo sync
sudo modprobe nbd
sudo qemu-nbd -c dev/nbd0 -f raw ./ZealOS.raw
sudo partprobe /dev/nbd0
echo "Merging with src/"
sudo mount /dev/nbd0p1 /mnt
sudo cp -r ../src/* /mnt/
sudo sync
echo "Files copied, unmounting"
sudo umount /mnt
sudo qemu-nbd -d /dev/nbd0
sudo rm /mnt/* -r
sudo sync
qemu-system-x86_64 -machine q35,kernel_irqchip=off,accel=kvm -drive format=raw,file=ZealOS.raw -m 2G -smp $(nproc) -rtc base=localtime -device isa-debug-exit
echo "Mounting"
sudo rm /mnt/* -r
sudo sync
sudo modprobe nbd
sudo qemu-nbd -c dev/nbd0 -f raw ./ZealOS.raw
sudo partprobe /dev/nbd0
sudo mount /dev/nbd0p1 /mnt
echo "Extracting Distro ISO"
sudo cp /mnt/Tmp/MyDistro.ISO.C ./ZealOS-$(date +%Y-%m-%d-%H_%M_%S).iso
sudo chown -R $USER:$USER ./ZealOS-*.iso
echo "Files copied, unmounting"
sudo umount /mnt
sudo qemu-nbd -d /dev/nbd0
sudo rm /mnt/* -r
sudo sync
echo "Deleting temp HDD"
rm ./ZealOS.raw
echo "Done"
