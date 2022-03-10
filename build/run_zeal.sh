#!/bin/bash

qemu-system-x86_64 -machine q35,kernel_irqchip=off,accel=kvm -hda ZealOS.qcow2 -m 2G -smp $(nproc) -rtc base=localtime -soundhw pcspk -nic user,model=pcnet -display gtk,gl=on,grab-on-hover=on,zoom-to-fit=on
