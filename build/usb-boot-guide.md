dd if=/dev/zero of=usbdisk.img bs=1M count=512
echo 'start=2048, type=c' | sfdisk usbdisk.img
LOOP=$(sudo losetup -f --show -P usbdisk.img)
sudo mkfs.vfat -F 32 ${LOOP}p1
sudo losetup -d $LOOP


qemu-system-x86_64 -machine q35,accel=kvm -m 2G \
  -boot d \
  -cdrom ZealOS-PublicDomain-BIOS-2026-07-24-03_43_40.iso  \
  -device qemu-xhci,id=xhci \
  -drive if=none,id=ub,format=raw,file=usbdisk.img \
  -device usb-storage,bus=xhci.0,drive=ub


CopyTree("::/", "V:/");   # copies the whole CD to the stick
Dir("V:/");               # should now list Boot, Kernel, System, Compiler, Home, etc.
BootHDIns('V');           # recompiles kernel on V: (few min), writes FAT32 boot record
BootMHDIns('V');          # MBR chain-loader

# At the BootHDIns config prompt, enter V for boot drive, ENTER through the rest.

qemu-system-x86_64 -machine q35,accel=kvm -m 2G \
  -device qemu-xhci,id=xhci \
  -drive if=none,id=ub,format=raw,file=usbdisk.img \
  -device usb-storage,bus=xhci.0,drive=ub \
  -device usb-kbd,bus=xhci.0 -device usb-mouse,bus=xhci.0