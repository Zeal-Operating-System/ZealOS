qemu-system-x86_64 -machine q35,kernel_irqchip=off,accel=kvm -cdrom ./ZealOS-2021-11-02-19_04_16.iso -hda ../dist/ZealOS.qcow2 -m 2G -smp $(nproc) -rtc base=localtime -soundhw pcspk -nic user,model=virtio-net-pci
# qemu-system-x86_64 -machine q35,kernel_irqchip=off,accel=kvm -hda ../dist/ZealOS.qcow2 -m 2G -smp $(nproc) -rtc base=localtime -soundhw pcspk -nic user,model=virtio-net-pci
