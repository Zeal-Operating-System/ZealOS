#!/bin/bash
echo "mounting..."
sudo modprobe nbd
sudo qemu-nbd -c dev/nbd0 ~/VirtualBox\ VMs/ZealOS/ZealOS.vdi #Replace with path to disk
#sudo qemu-nbd -c dev/nbd0 ~/vmware/ZealOS/ZealOS.vmdk #Replace with path to disk
sudo partprobe /dev/nbd0
sudo mount /dev/nbd0p1 /mnt
echo "mounted .vdi"

echo "removing src/ files"
rm -rf src/*
echo "copying src/ files from root of mounted .vdi"
sudo cp -r /mnt/* src/
echo "src/ files copied"

echo "removing doc/ files"
rm -rf docs/*
echo "copying docs/ files from HTML/ folder of mounted .vdi"
sudo cp -r /mnt/HTML/* docs/
echo "docs/ files copied"

echo "unmounting..."
sudo umount /mnt
sudo qemu-nbd -d /dev/nbd0
echo "unmounted .vdi"
echo "set perms, update ISO."
sudo chown -R $USER:$USER src/*
sudo chown -R $USER:$USER docs/*
rm ZealOS-*
mv src/Tmp/MyDistro.ISO.C ./ZealOS-$(date +%Y-%m-%d-%H_%M_%S).iso
mv src/Tmp/AUTO.ISO.C ./build/AUTO.ISO

echo "removing duplicates"
rm -rf ./src/HTML/*

echo "finished."
git status
