#!/bin/bash
sudo modprobe nbd
sudo qemu-nbd -c dev/nbd0 ~/VirtualBox\ VMs/ZenithOS/ZenithOS.qcow
sudo mount /dev/nbd0p1 /mnt
sudo cp -r /mnt/* ~/Projects/ZenithOS/
sudo umount /mnt
sudo qemu-nbd -d /dev/nbd0
sudo chown -R v:v ~/Projects/ZenithOS/*
