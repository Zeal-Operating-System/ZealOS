#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include <lib.h>

__attribute__((used, section(".limine_requests_start")))
static volatile uint64_t limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile uint64_t limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;

__attribute__((used, section(".limine_requests")))
static volatile struct limine_module_request module_request = {
    .id = LIMINE_MODULE_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_smbios_request smbios_request = {
    .id = LIMINE_SMBIOS_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_efi_system_table_request efi_request = {
    .id = LIMINE_EFI_SYSTEM_TABLE_REQUEST_ID,
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
} __attribute__((packed));

struct CDate {
    uint32_t time;
    int32_t date;
} __attribute__((packed));

#define MEM_E820_ENTRIES_NUM 256

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
} __attribute__((packed));

struct CGDTEntry {
    uint64_t lo, hi;
} __attribute__((packed));

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
} __attribute__((packed));

struct CSysLimitBase {
    uint16_t limit;
    uint8_t *base;
} __attribute__((packed));

struct CVideoInfo {
    uint16_t width;
    uint16_t height;
} __attribute__((packed));

#define VBE_MODES_NUM 32

#define ZEALBOOTER_LIMINE_SIGNATURE_1 0xaa23c08ed10bd4d7
#define ZEALBOOTER_LIMINE_SIGNATURE_2 0xf6ceba7d4b74179a

struct CKernel {
    struct CZXE h;
    uint32_t jmp;
    uint32_t boot_src;
    uint32_t boot_blk;
    uint32_t boot_patch_table_base;
    uint32_t sys_run_level;
    struct CDate compile_time;
    // U0 start
    uint32_t boot_base;
    uint16_t mem_E801[2];
    struct CMemE820 mem_E820[MEM_E820_ENTRIES_NUM];
    uint64_t mem_physical_space;
    struct CSysLimitBase sys_gdt_ptr;
    uint16_t sys_pci_buses;
    struct CGDT sys_gdt __attribute__((aligned(16)));
    uint64_t sys_framebuffer_addr;
    uint64_t sys_framebuffer_width;
    uint64_t sys_framebuffer_height;
    uint64_t sys_framebuffer_pitch;
    uint8_t sys_framebuffer_bpp;
    uint64_t sys_smbios_entry;
    uint64_t sys_disk_uuid[2];
	uint32_t sys_boot_stack;
	uint8_t sys_is_uefi_booted;
    uint8_t sys_bootloader_id;
	struct CVideoInfo sys_framebuffer_list[VBE_MODES_NUM];
} __attribute__((packed));

#define BL_ZEAL    0
#define BL_LIMINE  1

#define BOOT_SRC_RAM 2
#define BOOT_SRC_HDD 3
#define BOOT_SRC_DVD 4
#define RLF_16BIT 0b001
#define RLF_VESA  0b010
#define RLF_32BIT 0b100

#define BOOT_RAM_BASE  0x7c00  // KernelA.HH, where the native boot loaders load the kernel
#define BOOT_RAM_LIMIT 0x97000 // KernelA.HH, top of the native boot stack
#define MP_VECT_ADDR   0x97000 // KernelA.HH, the kernel copies its AP startup code to this page

// the offsets in trampoline.S must match
struct trampoline_args {
    uint32_t stack;
    uint32_t kernel;
    uint32_t kernel_size;
    uint32_t kernel_base;
    uint32_t gdt_ptr;
    uint32_t entry_point;
    uint32_t patch_table_base;
    uint32_t boot_base;
    uint32_t boot_stack;
} __attribute__((packed));

static void hcf(void) {
    for (;;) {
        asm("hlt");
    }
}

// the types handed to the kernel as usable
static bool is_usable(uint64_t type) {
    return type == LIMINE_MEMMAP_USABLE || type == LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE || type == LIMINE_MEMMAP_EXECUTABLE_AND_MODULES;
}

// end of the usable memory contiguous from base, entries other than usable ones may overlap
static uint64_t usable_top(uint64_t base) {
    uint64_t top = base;
    bool progress;

    do {
        progress = false;
        for (size_t i = 0; i < memmap_request.response->entry_count; i++) {
            struct limine_memmap_entry *entry = memmap_request.response->entries[i];

            if (is_usable(entry->type) && entry->base <= top && entry->base + entry->length > top) {
                top = entry->base + entry->length;
                progress = true;
            }
        }
    } while (progress);

    return top;
}

extern symbol trampoline, trampoline_end;

struct E801 {
    size_t lowermem;
    size_t uppermem;
};

static struct E801 get_E801(void) {
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

void kmain(void) {
    printf("ZealBooter prekernel\n");
    printf("____________________\n\n");

    if (module_request.response == NULL || module_request.response->module_count < 1
     || memmap_request.response == NULL || hhdm_request.response == NULL
     || framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        printf("ERROR: missing Limine responses");
        hcf();
    }

    struct limine_file *module_kernel = module_request.response->modules[0];
    struct CKernel *kernel = module_kernel->address;

    // the kernel runs where the native boot loaders load it and uses the memory up to its MP vector
    if (BOOT_RAM_BASE + module_kernel->size > BOOT_RAM_LIMIT || usable_top(BOOT_RAM_BASE) < MP_VECT_ADDR + 0x1000) {
        printf("ERROR: no memory for the kernel at BOOT_RAM_BASE");
        hcf();
    }

    // the trampoline leaves Limine's page tables, stack and GDT from usable memory before copying the kernel
    const size_t trampoline_size = (uintptr_t)trampoline_end - (uintptr_t)trampoline;
    const size_t staging_stack_size = 4096;
    const size_t staging_size = align_up_u64(trampoline_size + sizeof(struct trampoline_args), 16) + align_up_u64(module_kernel->size, 16) + staging_stack_size;

    uintptr_t staging = (uintptr_t)-1;
    for (size_t i = 0; i < memmap_request.response->entry_count; i++) {
        struct limine_memmap_entry *entry = memmap_request.response->entries[i];

        if (entry->type != LIMINE_MEMMAP_USABLE) {
            continue;
        }

        // above 1MiB to stay clear of the kernel, below 4GiB for the 32-bit trampoline
        uint64_t base = entry->base > 0x100000 ? entry->base : 0x100000;
        uint64_t top = entry->base + entry->length < 0x100000000 ? entry->base + entry->length : 0x100000000;

        if (base < top && top - base >= staging_size) {
            staging = base;
            break;
        }
    }
    if (staging == (uintptr_t)-1) {
        printf("ERROR: could not find memory for the trampoline");
        hcf();
    }

	printf("staging: 0x%X\n", staging);

    struct limine_framebuffer *fb = framebuffer_request.response->framebuffers[0];
    kernel->sys_framebuffer_pitch = fb->pitch;
    kernel->sys_framebuffer_width = fb->width;
    kernel->sys_framebuffer_height = fb->height;
    kernel->sys_framebuffer_bpp = fb->bpp;
    kernel->sys_framebuffer_addr = (uintptr_t)fb->address - hhdm_request.response->offset;

    struct limine_video_mode *mode;
    for (size_t i = 0, j = 0; framebuffer_request.response->revision >= 1 && i < fb->mode_count && j < VBE_MODES_NUM; i++)
    {
        mode = fb->modes[i];
        if (mode->bpp == 32)
        {
            kernel->sys_framebuffer_list[j].height = mode->height;
            kernel->sys_framebuffer_list[j].width = mode->width;
            j++;
        }
    }

    void *entry_point; // to CORE0_32BIT_INIT
    for (uint64_t *p = (uint64_t *)kernel; ; p++) {
        if (*p != ZEALBOOTER_LIMINE_SIGNATURE_1) {
            continue;
        }
        p++;
        if (*p != ZEALBOOTER_LIMINE_SIGNATURE_2) {
            continue;
        }
        p++;
        entry_point = p;
        break;
    }

    entry_point -= (uintptr_t)module_kernel->address;
    entry_point += BOOT_RAM_BASE;

    printf("entry_point: 0x%X\n", entry_point);

    if (module_kernel->media_type == LIMINE_MEDIA_TYPE_OPTICAL)
        kernel->boot_src = BOOT_SRC_DVD;
    else if (module_kernel->media_type == LIMINE_MEDIA_TYPE_GENERIC)
        kernel->boot_src = BOOT_SRC_HDD;
    else
        kernel->boot_src = BOOT_SRC_RAM;
    kernel->boot_blk = 0;
    kernel->boot_patch_table_base = (uintptr_t)kernel + kernel->h.patch_table_offset;
    kernel->boot_patch_table_base -= (uintptr_t)module_kernel->address;
    kernel->boot_patch_table_base += BOOT_RAM_BASE;

    printf("kernel->boot_patch_table_base: 0x%X\n", kernel->boot_patch_table_base);

    kernel->sys_run_level = RLF_VESA | RLF_16BIT | RLF_32BIT;

    kernel->boot_base = (uintptr_t)&kernel->jmp - (uintptr_t)module_kernel->address;
    kernel->boot_base += BOOT_RAM_BASE;

    printf("kernel->boot_base: 0x%X\n", kernel->boot_base);

    kernel->sys_gdt_ptr.limit = sizeof(kernel->sys_gdt) - 1;
    kernel->sys_gdt_ptr.base = (void *)&kernel->sys_gdt - (uintptr_t)module_kernel->address;
    kernel->sys_gdt_ptr.base += BOOT_RAM_BASE;

    // based at boot_base as KStart16 does, CORE0_32BIT_INIT relies on it when BootRAM reenters it
    kernel->sys_gdt.boot_ds.lo += (uint64_t)kernel->boot_base << 16;
    kernel->sys_gdt.boot_cs.lo += (uint64_t)kernel->boot_base << 16;

    printf("kernel->sys_gdt_ptr.limit: 0x%X\n", kernel->sys_gdt_ptr.limit);
    printf("kernel->sys_gdt_ptr.base: 0x%X\n", kernel->sys_gdt_ptr.base);

    kernel->sys_pci_buses = 256;

    struct E801 E801 = get_E801();
    kernel->mem_E801[0] = E801.lowermem;
    kernel->mem_E801[1] = E801.uppermem;

    kernel->mem_physical_space = 0;

    printf("memory map:\n");
    size_t mem_count = memmap_request.response->entry_count;
    if (mem_count > MEM_E820_ENTRIES_NUM - 1) {
        mem_count = MEM_E820_ENTRIES_NUM - 1; // leave one to terminate, like KStart16
    }
    for (size_t i = 0; i < mem_count; i++) {
        struct limine_memmap_entry *entry = memmap_request.response->entries[i];
        int zeal_mem_type;

        printf("    ");
        switch (entry->type) {
            case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
            case LIMINE_MEMMAP_EXECUTABLE_AND_MODULES:
            case LIMINE_MEMMAP_USABLE:
                zeal_mem_type = MEM_E820T_USABLE;
                printf("  USABLE: ");
                break;
            case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
                zeal_mem_type = MEM_E820T_ACPI;
                printf("    ACPI: ");
                break;
            case LIMINE_MEMMAP_ACPI_NVS:
                zeal_mem_type = MEM_E820T_ACPI_NVS;
                printf("     NVS: ");
                break;
            case LIMINE_MEMMAP_BAD_MEMORY:
                zeal_mem_type = MEM_E820T_BAD_MEM;
                printf("     BAD: ");
                break;
            case LIMINE_MEMMAP_RESERVED:
            default:
                zeal_mem_type = MEM_E820T_RESERVED;
                printf("RESERVED: ");
                break;
        }

        kernel->mem_E820[i].base = (void *)entry->base;
        kernel->mem_E820[i].len = entry->length;
        kernel->mem_E820[i].type = zeal_mem_type;

        if (kernel->mem_physical_space < entry->base + entry->length) {
            kernel->mem_physical_space = entry->base + entry->length;
        }

        printf("0x%08X-0x%08X", entry->base, entry->base + entry->length - 1);

        if (i % 3 == 0)
        {
            printf("\n");
        }

    }
    printf("\n");

    kernel->mem_E820[mem_count].type = 0;

    kernel->mem_physical_space = align_up_u64(kernel->mem_physical_space, 0x200000);

    void *sys_gdt_ptr = (void *)&kernel->sys_gdt_ptr - (uintptr_t)module_kernel->address;
    sys_gdt_ptr += BOOT_RAM_BASE;

    printf("sys_gdt_ptr: 0x%X\n", sys_gdt_ptr);

    void *sys_smbios_entry = smbios_request.response != NULL ? (void *)smbios_request.response->entry_32 : NULL;
    if (sys_smbios_entry != NULL) {
        kernel->sys_smbios_entry = (uintptr_t)sys_smbios_entry - hhdm_request.response->offset;
    }

    memcpy(kernel->sys_disk_uuid, &module_kernel->gpt_disk_uuid, sizeof(kernel->sys_disk_uuid));

	kernel->sys_boot_stack = BOOT_RAM_LIMIT;

    if (efi_request.response)
    {
        kernel->sys_is_uefi_booted = true;
    }

    kernel->sys_bootloader_id = BL_LIMINE;

    struct trampoline_args *const args = (void *)staging + trampoline_size;
    void *const staging_kernel = (void *)staging + align_up_u64(trampoline_size + sizeof(struct trampoline_args), 16);

    memcpy((void *)staging, trampoline, trampoline_size);
    memcpy(staging_kernel, kernel, module_kernel->size);

    args->stack = staging + staging_size;
    args->kernel = (uintptr_t)staging_kernel;
    args->kernel_size = module_kernel->size;
    args->kernel_base = BOOT_RAM_BASE;
    args->gdt_ptr = (uintptr_t)sys_gdt_ptr;
    args->entry_point = (uintptr_t)entry_point;
    args->patch_table_base = kernel->boot_patch_table_base;
    args->boot_base = kernel->boot_base;
    args->boot_stack = kernel->sys_boot_stack;

//    printf("\nDEBUG: halting."); for (;;);
    asm volatile (
        "jmp *%0"
        :
        : "a"(staging), "b"(args)
        : "memory");

    __builtin_unreachable();
}
