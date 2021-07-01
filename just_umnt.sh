#!/bin/bash

echo "unmounting..."
sudo umount /mnt
sudo qemu-nbd -d /dev/nbd0
echo "unmounted .vdi"
echo "not copying/updating ISO."
#echo "set perms, update ISO."
#sudo chown -R $USER:$USER src/*
#rm ZealOS-*
#mv src/Tmp/MyDistro.ISO.C ./ZealOS-$(date +%Y-%m-%d-%H_%M_%S).iso
echo "finished."
