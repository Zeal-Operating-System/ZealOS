#!/bin/bash
sudo modprobe nbd
sudo qemu-nbd -c dev/nbd0 ~/VirtualBox\ VMs/ZenithOS/ZenithOS.qcow
sudo mount /dev/nbd0p1 /mnt

rm -rf src/*
sudo cp -r /mnt/* src/

sudo umount /mnt
sudo qemu-nbd -d /dev/nbd0
sudo chown -R v:v src/*
mv src/Tmp/MyDistro.ISO.C src/Tmp/Zenith-Latest.iso

