#!/bin/bash
sudo modprobe nbd
sudo qemu-nbd -c dev/nbd0 "~/VirtualBox\ VMs/ZenithOS/ZenithOS.vmdk" #Replace with path to disk
sudo mount /dev/nbd0p1 /mnt

rm -rf src/*
sudo cp -r /mnt/* src/

sudo umount /mnt
sudo qemu-nbd -d /dev/nbd0
sudo chown -R $USER:$USER src/*
rm Zenith-latest*
mv src/Tmp/MyDistro.ISO.C ./Zenith-latest-$(date +%Y-%m-%d-%H_%M_%S).iso
