# ZealOS RAM-distro ISO (Ventoy / limine / PXE)

Builds a self-contained `ZealOS-RAM.iso`. The kernel embeds the whole OS as a
RedSea RAM disk, so it boots with no post-load disk access from any loader that
places a kernel in memory. Same repo/branch also supports native USB-drive
install (see `usb-boot-guide.md`); the two are independent.

Branch: `usb-boot-ventoy`.

## Status / prerequisite

The RAM ISO is loaded by ZealBooter → limine. The limine boot path must reach
the desktop for this ISO to boot. If a plain limine ISO black-screens in your
setup, fix that first (kernel boot markers are emitted to QEMU debug port 0xE9;
boot with `-debugcon stdio`). Native CD boot and native USB install do not use
this path and work independently.

## Host packages

```
git qemu-system-x86 xorriso gcc make sudo
# nbd kernel module (for qemu-nbd mounting)
```

## 1. Clone + branch

```
git clone git@github.com:Zeal-Operating-System/ZealOS.git
cd ZealOS
git checkout usb-boot-ventoy
```

## 2. Build the base ISOs

```
cd build
./build-iso.sh
```

Produces `ZealOS-PublicDomain-BIOS-*.iso` (native) and `ZealOS-BSD2-UEFI-*.iso`
(limine). Bootstrap uses the tracked `build/AUTO.ISO`; needs `sudo` for
`qemu-nbd`.

## 3. Create a working ZealOS VM

```
qemu-img create -f qcow2 ZealOS.qcow2 2G
qemu-system-x86_64 -machine q35,accel=kvm -m 2G -boot d \
  -cdrom ZealOS-PublicDomain-BIOS-*.iso \
  -drive file=ZealOS.qcow2,format=qcow2,if=ide
```

The CD and the disk must be on the same AHCI controller or ZealOS won't see the
CD (do NOT put them on separate `-device ich9-ahci` controllers). At the ZealOS
prompt `Install onto hard drive (y or n)?` answer `y` and follow the installer
(target drive `C`). Shut down when done.

## 4. Sync branch source into the VM

`sync.sh` uses `ZEALDISK=ZealOS.qcow2` by default (edit if elsewhere). VM must be
shut down.

```
./sync.sh vm
```

## 5. Recompile kernel in the VM

```
qemu-system-x86_64 -machine q35,accel=kvm -m 2G \
  -drive file=ZealOS.qcow2,format=qcow2,if=ide
```

In ZealOS:

```
BootHDIns('C');
```

Enter `C` at the boot-drive prompt, ENTER through the rest. Reboot the VM after.

## 6. Build the OS image in the VM

In ZealOS:

```
#include "::/Misc/DoDistroRAM";
```

Copies the OS into a RAM drive and snapshots it. Output: `::/Tmp/RAMDistro.BIN`
(~48MB). Shut down.

## 7. Extract image + kernel to the host

`RAMDistro.BIN` is the OS image; `/Boot/Kernel.ZXE` is the normal kernel that
step 5 recompiled (it carries the RAM-distro mount code).
(or use the kernel extraction script `./extract-kernel.sh`)

```
sudo modprobe nbd
sudo qemu-nbd -c /dev/nbd0 ZealOS.qcow2
sudo partprobe /dev/nbd0
sudo mkdir -p /tmp/zealtmp
sudo mount /dev/nbd0p1 /tmp/zealtmp
sudo cp /tmp/zealtmp/Tmp/RAMDistro.BIN ./RAMDistro.BIN
sudo cp /tmp/zealtmp/Boot/Kernel.ZXE   ./Kernel.ZXE
sudo umount /tmp/zealtmp
sudo qemu-nbd -d /dev/nbd0
```

## 8. Package the RAM ISO

```
./build-ram-iso.sh RAMDistro.BIN Kernel.ZXE
```

Output: `build/ZealOS-RAM.iso`. The kernel is Limine module 0, the OS image is
module 1; ZealBooter passes the image address to the kernel, which mounts it as
RAM drive B: and boots.

## 9. Test in QEMU

```
qemu-system-x86_64 -machine q35,accel=kvm -m 2G -cdrom ZealOS-RAM.iso
```

## 10. Ventoy

Copy `ZealOS-RAM.iso` to the Ventoy partition of the USB stick. Boot the stick,
select it from the Ventoy menu.

## Notes

- Bump `RAMDISTRO_OFFSET` in `src/Misc/DoDistroRAM.ZC` if the kernel ever grows
  past 1MB (`Kernel compile` will assert on a negative BINLOAD pad).
- Non-RAM ISOs on Ventoy do not work: ZealOS cannot read Ventoy's exFAT data
  partition to find the ISO. The RAM ISO avoids all post-load disk access.
- PXE: chainload limine over the network with `Boot/Kernel.ZXE` = the RAM kernel.
