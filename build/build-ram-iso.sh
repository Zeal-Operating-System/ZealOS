#!/usr/bin/env bash
# Package the self-contained RAM-distro ISO: the normal Kernel.ZXE plus the OS
# image (RAMDistro.BIN, made in-OS by src/Misc/DoDistroRAM.ZC) as a second
# Limine module. ZealBooter hands the image address to the kernel, which mounts
# it as RAM drive B: and boots -- works from CD, dd'd USB, Ventoy, PXE.
#
# Usage: ./build-ram-iso.sh <RAMDistro.BIN> [Kernel.ZXE]
#   RAMDistro.BIN : OS image from the VM (see sync.sh for mounting the vdisk)
#   Kernel.ZXE    : normal kernel; defaults to the one build-iso.sh produced
#                   (build/limine ISO), else supply a path.
set -e
cd "$(dirname "$0")"

IMG="${1:-RAMDistro.BIN}"
KZXE="${2:-Kernel.ZXE}"

if [ ! -f "$IMG" ]; then
    echo "ERROR: OS image not found: $IMG"
    echo "Run src/Misc/DoDistroRAM.ZC inside ZealOS, then copy Tmp/RAMDistro.BIN here."
    exit 1
fi
if [ ! -f "$KZXE" ]; then
    echo "ERROR: kernel not found: $KZXE"
    echo "Copy a normal Kernel.ZXE here (e.g. from build-iso.sh output or the vdisk)."
    exit 1
fi

LIMINE_BINARY_BRANCH="v10.x-binary"
[ -d limine ] || git clone https://github.com/limine-bootloader/limine.git --branch=$LIMINE_BINARY_BRANCH --depth=1
make -C limine
[ -f ../zealbooter/bin/kernel ] || make -C ../zealbooter distclean all

TMPISODIR=$(mktemp -d)
trap 'rm -rf "$TMPISODIR"' EXIT
mkdir -p "$TMPISODIR/Boot" "$TMPISODIR/EFI/BOOT"

cp limine/BOOTX64.EFI        "$TMPISODIR/EFI/BOOT/BOOTX64.EFI"
cp limine/limine-uefi-cd.bin "$TMPISODIR/Boot/Limine-UEFI-CD.BIN"
cp limine/limine-bios-cd.bin "$TMPISODIR/Boot/Limine-BIOS-CD.BIN"
cp limine/limine-bios.sys    "$TMPISODIR/Boot/Limine-BIOS.SYS"
cp ../zealbooter/bin/kernel  "$TMPISODIR/Boot/ZealBooter.ELF"
cp "$KZXE"                   "$TMPISODIR/Boot/Kernel.ZXE"
cp "$IMG"                    "$TMPISODIR/Boot/RAMDistro.BIN"

# limine.conf: kernel = module 0, OS image = module 1
cat > "$TMPISODIR/Boot/Limine.CONF" <<'EOF'
timeout: 1
interface_resolution: 1024x768

/ZealOS (RAM)
    protocol: limine
    resolution: 1024x768
    path: boot():/Boot/ZealBooter.ELF
    module_path: boot():/Boot/Kernel.ZXE
    module_path: boot():/Boot/RAMDistro.BIN
EOF

truncate -s 32K bios_boot.img
xorriso -as mkisofs -R -r -J -b Boot/Limine-BIOS-CD.BIN \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        --efi-boot Boot/Limine-UEFI-CD.BIN \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        -append_partition 4 21686148-6449-6E6F-744E-656564454649 bios_boot.img \
        -appended_part_as_gpt \
        "$TMPISODIR" -o ZealOS-RAM.iso
rm -f bios_boot.img

./limine/limine bios-install ZealOS-RAM.iso --no-gpt-to-mbr-isohybrid-conversion

echo
echo "Built: build/ZealOS-RAM.iso (self-contained; CD / dd-to-USB / Ventoy / PXE)"
