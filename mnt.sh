#!/bin/bash
echo "mounting..."
sudo modprobe nbd
sudo qemu-nbd -c dev/nbd0 ~/VirtualBox\ VMs/ZealOS/ZealOS.vdi #Replace with path to disk
sudo partprobe /dev/nbd0
sudo mount /dev/nbd0p1 /mnt
echo "mounted .vdi"

echo "removing src/ files"
rm -rf src/*
echo "copying src/ files from root of mounted .vdi"
sudo cp -r /mnt/* src/
echo "files copied"

echo "unmounting..."
sudo umount /mnt
sudo qemu-nbd -d /dev/nbd0
echo "unmounted .vdi"
echo "set perms, update ISO."
sudo chown -R $USER:$USER src/*
rm ZealOS-*
mv src/Tmp/MyDistro.ISO.C ./ZealOS-$(date +%Y-%m-%d-%H_%M_%S).iso
echo "finished."
git status
