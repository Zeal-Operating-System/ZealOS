#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include <lib.h>

static volatile struct limine_module_request module_request = {
    .id = LIMINE_MODULE_REQUEST,
    .revision = 0
};

static volatile struct limine_kernel_address_request kernel_address_request = {
    .id = LIMINE_KERNEL_ADDRESS_REQUEST,
    .revision = 0
};

static volatile struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

struct CZXE {
    uint16_t jmp;
    uint8_t module_align_bits;
    uint8_t reserved;
    uint32_t signature;
    int64_t org;
    int64_t patch_table_offset;
    int64_t file_size;
};

struct CDate {
    uint32_t time;
    int32_t date;
};

#define MEM_E820_ENTRIES_NUM 48

#define MEM_E820T_USABLE 1
#define MEM_E820T_RESERVED 2
#define MEM_E820T_ACPI 3
#define MEM_E820T_ACPI_NVS 4
#define MEM_E820T_BAD_MEM 5
#define MEM_E820T_PERM_MEM 7

struct CMemE820 {
    uint8_t *base;
    int64_t len;
    uint8_t type, pad[3];
};

struct CGDTEntry {
    uint64_t lo, hi;
};

#define MP_PROCESSORS_NUM 128

struct CGDT {
    struct CGDTEntry null;
    struct CGDTEntry boot_ds;
    struct CGDTEntry boot_cs;
    struct CGDTEntry cs32;
    struct CGDTEntry cs64;
    struct CGDTEntry cs64_ring3;
    struct CGDTEntry ds;
    struct CGDTEntry ds_ring3;
    struct CGDTEntry tr[MP_PROCESSORS_NUM];
    struct CGDTEntry tr_ring3[MP_PROCESSORS_NUM];
};

struct CKernel {
    struct CZXE h;
    uint32_t jmp;
    uint32_t boot_src;
    uint32_t boot_blk;
    uint32_t boot_patch_table_base;
    uint32_t sys_run_level;
    struct CDate compile_time;
    // start
    uint32_t boot_base;
    uint16_t mem_E801[2];
    struct CMemE820 mem_E820[MEM_E820_ENTRIES_NUM];
    uint64_t mem_physical_space;
    struct {
        uint16_t limit;
        uint8_t *base;
    } __attribute__((packed)) sys_gdt_ptr;
    uint16_t sys_pci_buses;
    struct CGDT sys_gdt;
    uint32_t sys_font_ptr;
} __attribute__((packed));

#define BOOT_SRC_RAM 2
#define RLF_16BIT 0b01
#define RLF_VESA  0b10

void lower(void);

struct E801 {
    size_t lowermem;
    size_t uppermem;
};

struct E801 get_E801(void) {
    struct E801 E801 = {0};

    for (size_t i = 0; i < memmap_request.response->entry_count; i++) {
        struct limine_memmap_entry *entry = memmap_request.response->entries[i];

        if (entry->type == LIMINE_MEMMAP_USABLE) {
            if (entry->base == 0x100000) {
                if (entry->length > 0xf00000) {
                    E801.lowermem = 0x3c00;
                } else {
                    E801.lowermem = entry->length / 1024;
                }
            }
            if (entry->base <= 0x1000000 && entry->base + entry->length > 0x1000000) {
                E801.uppermem = ((entry->length - (0x1000000 - entry->base)) / 1024) / 64;
            }
        }
    }

    return E801;
}

struct CVBEMode {
    uint16_t attributes, pad0[7], pitch, width, height;
    uint8_t pad1[3], bpp, pad2, memory_model, pad[12];
    uint32_t framebuffer;
    uint16_t pad3[9];
    uint32_t max_pixel_clock;
    uint8_t reserved[190];
} __attribute__((packed));

void _start(void) {
    struct limine_file *kernel = module_request.response->modules[0];
    struct CKernel *CKernel = (void *)0x7c00;
    memcpy(CKernel, kernel->address, kernel->size);

    struct CVBEMode *sys_vbe_mode;
    for (uint64_t *p = (uint64_t *)CKernel; ; p++) {
        if (*p != 0x5439581381193aaf) {
            continue;
        }
        p++;
        if (*p != 0x2a8a30e69ec9f845) {
            continue;
        }
        p++;
        sys_vbe_mode = (void *)p;
        break;
    }

    struct limine_framebuffer *fb = framebuffer_request.response->framebuffers[0];
    sys_vbe_mode->pitch = fb->pitch;
    sys_vbe_mode->width = fb->width;
    sys_vbe_mode->height = fb->height;
    sys_vbe_mode->bpp = fb->bpp;
    sys_vbe_mode->framebuffer = (uintptr_t)fb->address - hhdm_request.response->offset;

    void *CORE0_32BIT_INIT;
    for (uint64_t *p = (uint64_t *)CKernel; ; p++) {
        if (*p != 0xaa23c08ed10bd4d7) {
            continue;
        }
        p++;
        if (*p != 0xf6ceba7d4b74179a) {
            continue;
        }
        p++;
        CORE0_32BIT_INIT = p;
        break;
    }

    CKernel->boot_src = BOOT_SRC_RAM;
    CKernel->boot_blk = 0;
    CKernel->boot_patch_table_base = (uintptr_t)CKernel + CKernel->h.patch_table_offset;

//    asm volatile ("jmp ." ::"a"(CKernel->boot_patch_table_base));

    CKernel->sys_run_level = RLF_VESA | RLF_16BIT;

    CKernel->boot_base = (uintptr_t)&CKernel->jmp;

    CKernel->sys_gdt.boot_ds.lo = 0x00CF92000000FFFF;
    CKernel->sys_gdt.boot_cs.lo = 0x00CF9A000000FFFF;
    CKernel->sys_gdt.cs32.lo = 0x00CF9A000000FFFF;
    CKernel->sys_gdt.cs64.lo = 0x00209A0000000000;
    CKernel->sys_gdt.cs64_ring3.lo = 0x0020FA0000000000;
    CKernel->sys_gdt.ds.lo = 0x00CF92000000FFFF;
    CKernel->sys_gdt.ds_ring3.lo = 0x00CFF2000000FFFF;

    CKernel->sys_gdt_ptr.limit = sizeof(CKernel->sys_gdt) - 1;
    CKernel->sys_gdt_ptr.base = (void *)&CKernel->sys_gdt;

    struct E801 E801 = get_E801();
    CKernel->mem_E801[0] = E801.lowermem;
    CKernel->mem_E801[1] = E801.uppermem;

    for (size_t i = 0; i < memmap_request.response->entry_count; i++) {
        struct limine_memmap_entry *entry = memmap_request.response->entries[i];

        int our_type;
        switch (entry->type) {
            case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
            case LIMINE_MEMMAP_KERNEL_AND_MODULES:
            case LIMINE_MEMMAP_USABLE:
                our_type = MEM_E820T_USABLE; break;
            case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
                our_type = MEM_E820T_ACPI; break;
            case LIMINE_MEMMAP_ACPI_NVS:
                our_type = MEM_E820T_ACPI_NVS; break;
            case LIMINE_MEMMAP_BAD_MEMORY:
                our_type = MEM_E820T_BAD_MEM; break;
            case LIMINE_MEMMAP_RESERVED:
            default:
                our_type = MEM_E820T_RESERVED; break;
        }

        CKernel->mem_E820[i].base = (void *)entry->base;
        CKernel->mem_E820[i].len = entry->length;
        CKernel->mem_E820[i].type = our_type;
    }

    void *target_addr = (void *)lower - kernel_address_request.response->virtual_base;
    target_addr += kernel_address_request.response->physical_base;

    asm volatile ("jmp *%0" :: "a"(target_addr), "b"(CORE0_32BIT_INIT), "c"(&CKernel->sys_gdt_ptr), "S"(CKernel->boot_patch_table_base), "D"(CKernel->boot_base) : "memory");

    __builtin_unreachable();
}
