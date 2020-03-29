//SMBIOS parsing.
//Based on SMBIOS specification 3.3.0 (document "DSP0134")

//Section 6.2 line 910 (required structures)
#define SMBIOSt_BIOS				0
#define SMBIOSt_SYSTEM				1
#define SMBIOSt_BASEBOARD			2
#define SMBIOSt_ENCLOSURE			3
#define SMBIOSt_PROCESSOR			4
#define SMBIOSt_CACHE				7
#define SMBIOSt_CONNECTOR			8
#define SMBIOSt_SLOT				9
#define SMBIOSt_OEM_STRINGS			11
#define SMBIOSt_SYS_CONFIG_OPTIONS	12
#define SMBIOSt_PHYMEM				16
#define SMBIOSt_MEM_DEVICE			17
#define SMBIOSt_MAPPED_ADDR			19
#define SMBIOSt_BATTERY				22
#define SMBIOSt_BOOT_INFO			32

#define SMBIOS_BIOSf_NO_SUPPORT		3
#define SMBIOS_BIOSf_ISA			4
#define SMBIOS_BIOSf_MCA			5
#define SMBIOS_BIOSf_EISA			6
#define SMBIOS_BIOSf_PCI			7
#define SMBIOS_BIOSf_PCMCIA			8
#define SMBIOS_BIOSf_PNP			9
#define SMBIOS_BIOSf_APM			10
#define SMBIOS_BIOSf_BIOS_FLASH		11
#define SMBIOS_BIOSf_BIOS_SHADOW	12
#define SMBIOS_BIOSf_VLVESA			13
#define SMBIOS_BIOSf_ESCD			14
#define SMBIOS_BIOSf_CD_BOOT		15
#define SMBIOS_BIOSf_BOOT_SELECT	16
#define SMBIOS_BIOSf_ROM_SOCKETED	17
#define SMBIOS_BIOSf_PCMCIA_BOOT	18
#define SMBIOS_BIOSf_EDD			19

//Section 7.3.1 line 972 (baseboard feature flags)
#define SMBIOS_BASEBOARDf_HOST			0
#define SMBIOS_BASEBOARDf_AUX_REQUIRED	1
#define SMBIOS_BASEBOARDf_REMOVABLE		2
#define SMBIOS_BASEBOARDf_REPLACEABLE	3
#define SMBIOS_BASEBOARDf_HOTSWAPPABLE	4

class CSMBIOSHeader
{//Section 6.1.2 line 885
	U8	type,	//SMBIOSt_*
		length;
	U16	handle;	//identifier for this structure.
};
class CSMBIOSEntryPoint
{//Section 5.2.1 line 812
	U8	anchor_str[4], // '_SM_'
		checksum,
		length,
		major_version,
		minor_version;
	U16	max_structure_size;
	U8	entry_point_revision,
		formatted_area[5],
		anchor_str2[5], // '_DMI_'
		checksum2;
	U16	table_length;
	U32	table_address;
	U16	structure_count;
	U8	bcd_revision;
};

class CSMBIOSBIOSInfo
{//Section 7.1 line 922
	CSMBIOSHeader header;
	U8	vendor,
		version;
	U16	start_address_segment;
	U8	release_date,
		rom_size;
	U64	flags;
	U8	extended_flags[2];
	U8	major_release,
		minor_release,
		embedded_controller_firmware_major_release,
		embedded_controller_firmware_minor_release;
	U16	extended_rom_size;
};

class CSMBIOSSystemInfo
{//Section 7.2 line 936
	CSMBIOSHeader header;
	U8	manufacturer,
		product_name,
		version,
		serial_number,
		uuid[16],
		wakeup_type,
		sku_number,
		family;
};

class CSMBIOSBaseboardInfo
{//Section 7.3 line 968
	CSMBIOSHeader header;
	U8	manufacturer,
		product,
		version,
		serial_number,
		asset_tag,
		feature_flags,
		chassis_location;
	U16	chassis_handle;
	U8	board_type,
		contained_object_handles_num;
	U16	contained_object_handles[1]; //Variable length, member above gives length
};

class CSMBIOSEnclosureInfo
{//Section 7.4 line 984
	CSMBIOSHeader header;
	U8	manufacturer,
		type,
		version,
		serial_number,
		asset_tag,
		bootup_state,
		power_supply_state,
		thermal_state,
		security_status;
	U32	oem_defined;
	U8	height,
		power_cord_count,
		contained_element_count,
		contained_element_record_length,
		contained_elements[1]; //array length == count * record_length;
};

class CSMBIOSEnclosureContainedElement
{//Section 7.4.4 line 999
	U8	contained_element_type,
		contained_element_minimum,
		contained_element_maximum;
};

class CSMBIOSProcessorInfo
{//Section 7.5 line 1010
	CSMBIOSHeader header;
	U8	name,
		type,
		family,
		manufacturer;
	U64	id;
	U8	version,
		voltage;
	U16	external_clock,
		max_speed,
		current_speed;
	U8	status,
		upgrade;
	U16	l1_cache_handle,
		l2_cache_handle,
		l3_cache_handle;
	U8	serial_number,
		asset_tag,
		part_number,
		core_count,
		cores_enabled,
		thread_count;
	U16	characteristics;
};

class CSMBIOSCacheInfo
{//Section 7.8 line 1168
	CSMBIOSHeader header;
	U8	name;
	U16	config,
		max_size,
		installed_size,
		supported_sram_type,
		installed_sram_type;
	U8	cache_speed,
		error_correction_type,
		cache_type,
		associativity;
};

class CSMBIOSConnectorInfo
{//Section 7.9 line 1198
	CSMBIOSHeader header;
	U8	internal_name,
		internal_type,
		external_name,
		external_type,
		port_type;
};

class CSMBIOSSlotInfo
{//Section 7.10 line 1226
	CSMBIOSHeader header;
	U8	name,
		type,
		slot_data_bus_width,
		current_usage,
		length,
		id,
		flags1,
		flags2,
		segment_group_number,
		bus_number,
		device_function_number,
		data_bus_width,
		peer_grouping_count,
		peer_groups;
};

class CSMBIOSMemDeviceInfo
{//Section 7.18 line 1538
	CSMBIOSHeader header;
	U16	memory_array_handle,
		memory_error_info_handle,
		total_width,
		data_width,
		size;
	U8	form_factor,
		device_set,
		device_locator,
		bank_locator,
		type;
	U16	type_detail,
		speed;
	U8	manufacturer,
		serial_number,
		asset_tag,
		part_number,
		attributes;
	U32	extended_size;
	U16	configured_speed,
		min_voltage,
		max_voltage,
		configured_voltage;
	U8	technology;
	U16	operating_modes;
	U8	firmware_version;
	U16	manufacturer_id,
		product_id,
		subsystem_controller_manufacturer_id,
		subsystem_controller_product_id;
	U64	nonvolatile_size,
		volatile_size,
		cache_size,
		logical_size;
	U32	extended_speed,
		extended_configured_speed;
};

class CSMBIOSBatteryInfo
{//Section 7.23 line 1723
	CSMBIOSHeader header;
	U8	location,
		manufacturer,
		manufacture_date,
		serial_number,
		name,
		chemistry,
		capacity,
		voltage,
		sbds_version_number,
		max_battery_data_error,
		sbds_serial_number,
		sbds_manufacture_date,
		sbds_chemistry,
		capacity_multiplier;
	U32	oem;
};

U0 SMBIOSInit()
{
	//Section 7.1.1 line 925 (BIOS characteristics)
	DefineListLoad("ST_SMBIOS_BIOS_FLAGS", " \0 \0 \0 \0ISA\0MCA\0EISA\0PCI\0PC Card\0Plug and Play\0APM\0Flashable BIOS\0BIOS shadowing\0"
		"VESA Local Bus\0ESCD\0CD Boot\0Selectable boot\0BIOS ROM socketed\0PC Card Boot\0Enhanced Disk Drive Services\0"
		" \0 \0INT 0x13 5.25\"/360 KB Floppy Support\0INT 0x13 5.25\"/1.2 MB Floppy Support\0INT 0x13 3.5\"/720 KB Floppy Support\0"
		"INT 0x13 3.5\"/2.88 MB Floppy Support\0"
		"INT 0x05 Screen Printing\0INT 0x09 8042 Keyboard\0INT 0x14 Serial\0INT 0x17 Printer\0INT 0x10 CGA/Mono Video");
	//Section 7.1.2.1 line 931 (BIOS characteristics extension byte 1)
	DefineListLoad("ST_SMBIOS_BIOS_FLAGSEXT1",
		"ACPI\0USB Legacy\0 \0 \0 \0 \0Serial Boot\0Smart Battery"); 
	//Section 7.1.2.2 line 935 (BIOS characteristics extension byte 2)
	DefineListLoad("ST_SMBIOS_BIOS_FLAGSEXT2", "BIOS Boot\0Network Boot\0Targeted Content Distribution\0UEFI\0Virtual Machine");
	//Section 7.2.2 line 959 (system wakeup types)
	DefineListLoad("ST_SMBIOS_WAKEUP_TYPES",
		"Reserved\0Other\0Unknown\0APM Timer\0Modem Ring\0LAN Remote\0Power Switch\0PCI PME#\0AC Power Restored");
	//Section 7.3.1 line 972 (baseboard feature flags)
	DefineListLoad("ST_SMBIOS_BASEBOARD_FLAGS","Hosting Board (Motherboard)\0Requires Auxilary Board\0Removable\0Replaceable\0Hot Swappable");
	//Section 7.3.2 line 977 (baseboard board types)
	DefineListLoad("ST_SMBIOS_BASEBOARD_TYPES", " \0Unknown\0Other\0Server Blade\0Connectivity Switch\0"
		"System Management Module\0Processor Module\0I/O Module\0Daughterboard\0Motherboard\0Processor/Memory Module\0"
		"Processor/IO Module\0Interconnect Board\0");
	//Section 7.4.1 line 988 (system enclosure types)
	DefineListLoad("ST_SMBIOS_ENCLOSURE_TYPES", " \0Other\0Unknown\0Desktop\0Low Profile Desktop\0Pizza Box\0"
		"Mini Tower\0Tower\0Portable\0Laptop\0Notebook\0Hand Held\0Docking Station\0All-in-One\0Sub Notebook\0"
		"Space-saving\0Lunch box\0Main Server Chassis\0Expansion Chassis\0SubChassis\0Bus Expansion Chassis\0"
		"Peripheral Chassis\0RAID Chassis\0Rack Mount Chassis\0Sealed-case PC\0Multi-system Chassis\0Compact PCI\0"
		"Advanced TCA\0Blade\0Blade Enclosure\0Tablet\0Convertible\0Detachable\0IoT Gateway\0Embedded PC\0Mini PC\0Stick PC");
	//Section 7.4.2 line 991 (enclosure states)
	DefineListLoad("ST_SMBIOS_ENCLOSURE_STATES", " \0Other\0Unknown\0Safe\0Warning\0Critcal\0Non-recoverable");
	//Section 7.4.3 line 994 (enclosure security status field)
	DefineListLoad("ST_SMBIOS_ENCLOSURE_SECURITY_STATUSES",
		" \0Other\0Unknown\0None\0External Interface Locked Out\0External Interface Enabled");
	//Section 7.5.1 line 1014 (processor type field)
	DefineListLoad("ST_SMBIOS_PROCESSOR_TYPES", " \0Other\0Unknown\0Central Processor\0Math Processor\0DSP Processor\0Video Processor");
	//Section 7.5.4 line 1050 (processor voltage field)
	DefineListLoad("ST_SMBIOS_PROCESSOR_VOLTAGE_LEVELS", "5V\03.3V\02.9V");
	DefineListLoad("ST_CPUID_1_EDX_FLAGS", "x87 FPU\0Virtual 8086 Mode Enhancements\0Debugging Extensions\0Page Size Extensions\0"
		"Time Stamp Counter\0MSRs\0Page Address Extension\0Machine Check Exceptions\0CMPXCHG8B\0APIC\0Reserved\0SYSENTER/SYSEXIT\0"
		"Memory Type Range Registers\0Page Global Bit\0Machine Check Architecture\0CMOV Instructions\0Page Attribute Table\0"
		"36 Bit Page Size Extension\0Processor Serial Number\0CLFLUSH\0Reserved\0Debug Store\0ACPI\0MMX\0FXSAVE/FXRSTOR\0SSE\0SSE2\0"
		"Self Snoop\0HTT\0Thermal Monitor\0Reserved\0Pending Break Enable\0");
	DefineListLoad("ST_CPUID_1_ECX_FLAGS", "SSE3\0PCLMULQDQ\064 bit DS AREA\0MONITOR/MWAIT\0CPL Qualified Debug Store\0"
		"Virtual Machine Extensions\0Safer Mode Extensions\0Reserved\0Thermal Monitor 2\0SSSE3\0L1 Context ID\0"
		"IA32_DEBUG_INTERFACE MSR\0FMA Extensions\0CMPXCHG16B\0xTPR Update Control\0Perfmon and Debug Capability\0Reserved\0"
		"Process Context Identifiers\0MMIO Prefetch\0SSE4.1\0SSE4.2\0x2APIC\0MOVBE\0POPCNT\0TSC Deadline\0AESNI\0XSAVE\0"
		"OSXSAVE\0AVX\0F16C\0RDRAND");
	//Section 7.5.5 line 1058 (upgrade field)
	DefineListLoad("ST_SMBIOS_PROCESSOR_UPGRADES", " \0Other\0Unknown\0Daughterboard\0ZIF Socket\0Replacable Piggy Back\0"
		"None\0LIF Socket\0Slot 1\0Slot2\0370-pin Socket\0 Slot A\0Slot M\0Socket 423\0Socket A (Socket 462)\0Socket 478\0"
		"754\0940\0939\0 mPGA604\0LGA771\0LGA775\0S1\0AM2\0F (1207)\0LGA1366\0G34\0AM3\0C32\0LGA1156\0LGA1567\0PGA988A\0"
		"BGA1288\0rPGA988B\0BGA1023\0BGA1224\0LGA1155\0LGA1356\0LGA2011\0FS1\0FS2\0FM1\FM2\0LGA2011-3\0LGA1356-3\0LGA1150\0"
		"BGA1168\0BGA1234\BGA1364\0AM4\0LGA1151\0BGA1440\0BGA1515\0LGA3647-1\0SP3\0SP3r2\0LGA2066\0BGA1932\0BGA1510\0BGA1528");
	//Section 7.5.9 line 1110 (processor characteristics)
	DefineListLoad("ST_SMBIOS_PROCESSOR_FLAGS",  " \0 \064 Bit\0Multicore\0HyperThreading\0NX/XD Protection\0Enhanced Virtualization\0"
		"Power/Performance Control\0128 Bit Capable");
	//Section 7.8.2 line 1178 (cache information SRAM type field)
	DefineListLoad("ST_SMBIOS_CACHE_SRAM_TYPES", "Other\0Unknown\0Non Burst\0Burst\0Pipeline Burst\0Synchronous\0Asynchronous");
	//Section 7.8.6 line 1193 (cache information associativity field)
	DefineListLoad("ST_SMBIOS_CACHE_ASSOCIATIVITY", " \0Other\0Unknown\0Direct Mapped\02-way Set-Associative\04-way Set-Associative\0"
		"Fully Associative\08-way Set-Associative\016-way Set-Associative\012-way Set-Associative\024-way Set-Associative\0"
		"32-way Set-Associative\048-way Set-Associative\064-way Set-Associative\020-way Set-Associative");
	//Section 7.9.2 line 1219 (connector type field)
	DefineListLoad("ST_SMBIOS_CONNECTOR_TYPES", "None\0Centronics\0Mini Centronics\0Proprietary\0DB-25 Pin Male\0DB-25 Pin Female\0"
		"DB-15 Pin Male\0DB-15 Pin Female\0DB-9 Pin Male\0DB-9 Pin Female\0RJ-11\0RJ-45\050-Pin MiniSCSI\0Mini-DIN\0Micro-DIN\0PS/2\0"
		"Infrared\0HP-HIL\0Access Bus (USB)\0SSA SCSI\0Circular DIN-8 Male\0Circular DIN-8 Female\0Onboard IDE\0Onboard Floppy\0"
		"9-Pin Dual Inline (Pin 10 Cut)\025-Pin Dual Inline (Pin 26 Cut)\050-Pin Dual Inline\068-Pin Dual Inline\0Onboard CD-ROM Sound Input\0"
		"Mini-Centronics Type-14\0Mini-Centronics Type-26\0Mini-Jack (Headphones)\0BNC\01394\0SAS\SATA Plug\0USB Type-C");
	//Section 7.9.3 line 1222 (port type field)
	DefineListLoad("ST_SMBIOS_PORT_TYPES", "None\0Parallel Port XT/AT Compatible\0Parallel Port PS/2\0Parallel Port ECP\0Parallel Port EPP\0"
		"Parallel Port ECP/EPP\0Serial Port XT/AT Compatible\0Serial Port 16450 Compatible\0Serial Port 16550 Compatible\0"
		"Serial Port 16550A Compatible\0SCSI Port\0MIDI Port\0Joystick Port\0Keyboard Port\0Mouse Port\0SSA SCSI\0USB\0FireWire (IEEE 1394)\0"
		"PCMCIA Type I\0PCMCIA Type II\0PCMCIA Type III\0Cardbus\0Access Bus Port\0SCSI II\0SCSI Wide\0 \0 \0 \0Video Port\0Audio Port\0"
		"Modem Port\0Network Port\0SATA\0SAS\0MFDP (Multi-Function Display Port\0Thunderbolt\08251 Compatible\08251 FIFO Compatible");
	//Section 
}

Bool SMBIOSEntryScan(CSMBIOSEntryPoint **entry)
{//Search 0xF0000 - 0x100000 for SMBIOS Entry Point structure.
	I64 i;
	U8 noreg checksum = 0, *mem = 0xF0000;

	while (mem < 0x100000)
	{
		if (!MemCompare(mem, "_SM_", 4))
		{
			*entry = mem;
			for (i = 0; i < (*entry)->length; i++)
				checksum += mem[i];

			if (checksum == 0) //valid checksums sum to zero
				break;
		}
		mem += 16; //anchor sits on 16-byte boundary
	}
	return mem != 0x100000;
}

U8 *SMBIOSStr(CSMBIOSHeader *header, I64 str_num, U8 *default="None")
{//Get string str_num from end of structure (string section).
	I64 i;
	U8* ptr = header(U8 *) + header->length;

	if (!str_num) return default;

	for (i = 1; i < str_num; i++)
	{
		while (*ptr++);
		if (!ptr[0] && !ptr[1])  //structure ends in double NULL
			return default;
	}
	return ptr;
}

CSMBIOSHeader *SMBIOSStructGet(CSMBIOSHeader *head, I64 type=0xFFFFF, I64 handle=0xFFFFF)
{//Search for struct with type or handle. Return NULL if not found.
	I64 i;
	while (head->type != 127)
	{
		if (head->handle == handle)
			return head;
		if (head->type == type)
			return head;

		head = head(U8 *) + head->length;
		for (i = 1; head(U8 *)[i - 1] || head(U8 *)[i]; i++);
		head = head(U8 *) + i + 1;	
	}
	return NULL;
}

U8 *SysRepFlagsMake(U8 *buf)
{
	U8 *str;
	U8 *tmp = StrReplace(StrReplace(StrReplace(StrReplace(buf,
		"+ ", ""),
		"- ", "",, TRUE),
		"+", "\n$$BLUE$$+$$GREEN$$",,TRUE),
		"-", "\n$$BLUE$$-$$RED$$",,TRUE);

//	StrCopy(tmp, tmp + 1); //remove first newline
	str = MStrPrint("$$ID,16$$%s$$ID,-16$$", tmp);
	Free(tmp);
	return str;
}

public I64 SysRep(I64 type=0xFF, I64 handle=0, Bool show_all_flags=FALSE)
{//Display info of System Management BIOS (SMBIOS) structures. 'type' is a SMBIOSt_* type. Returns structure count of displayed structures.
	I64 i = 1, structure_count = 0, cache_count = 0;
	CSMBIOSEntryPoint *entry;
	CSMBIOSHeader *header;
	U8 buffer[2048], buffer2[512], *str;

	if (!SMBIOSEntryScan(&entry))
	{
		"No SMBIOS data found.\n";
		return 0;
	}
	header = entry->table_address;

	if (!handle && type == 0xFF)
		"SMBIOS version %d.%d (%d entries)\n", entry->major_version, entry->minor_version, entry->structure_count;
	"$$FD,CYAN$$";
	while (header->type != 127)
	{
		if (handle && header->handle != handle)
			goto loop_end;
		if (type != 0xFF && header->type != type)
			goto loop_end;
		switch (header->type)
		{
			start:
				case SMBIOSt_BIOS:
					CSMBIOSBIOSInfo *bios_info = header;
					I64 start_addr = bios_info->start_address_segment << 16;
					"$$TR-C,\"BIOS\"$$\n";
					"$$ID,4$$"
					"Vendor\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, bios_info->vendor);
					"Version\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, bios_info->version);
					"Release Date\t:$$BLACK$$%s (mm/dd/yyyy)$$FG$$\n", SMBIOSStr(header, bios_info->release_date);
					"Release Version\t:$$BLACK$$%d.%d$$FG$$\n", bios_info->major_release, bios_info->minor_release;
					"Start Address\t:$$BLACK$$0x%X$$FG$$\n", Seg2Linear(&start_addr);
					"Image Size\t\t:$$BLACK$$%d bytes$$FG$$\n", (0x10000 - bios_info->start_address_segment) * 16;
					"ROM Size\t\t:$$BLACK$$";
					if (bios_info->rom_size == 0xFF)
						"%d %zB$$FG$$\n", bios_info->extended_rom_size & ~0xC000, Bt(&bios_info->extended_rom_size, 14), "M\0G";
					else
						"%d KB$$FG$$\n", (bios_info->rom_size + 1) * 64;
					if (Bt(&bios_info->flags, 3))
						"Flags Not Supported$$FG$$\n";
					else 
					{
						"$$TR,\"Flags\"$$";
						StrPrintFlags(buffer, Define("ST_SMBIOS_BIOS_FLAGS"), bios_info->flags & ~0xF, show_all_flags, 31);
						CatPrint(buffer, StrPrintFlags(buffer2, Define("ST_SMBIOS_BIOS_FLAGSEXT1"), bios_info->extended_flags[0], show_all_flags, 8));
						CatPrint(buffer, StrPrintFlags(buffer2, Define("ST_SMBIOS_BIOS_FLAGSEXT2"), bios_info->extended_flags[1], show_all_flags, 5));
						str = SysRepFlagsMake(buffer);
						"%s$$FG$$\n", str; 
						Free(str);
					}
					"$$ID,-4$$";
					break;
				case SMBIOSt_SYSTEM:
					CSMBIOSSystemInfo *sys_info = header;
					"$$TR-C,\"System\"$$\n";
					"$$ID,4$$Manufacturer\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, sys_info->manufacturer);
					"Product Name\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, sys_info->product_name);
					"Version\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, sys_info->version);
					"Serial Number\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, sys_info->serial_number);
					"UUID\t\t\t:$$BLACK$$%X-%X-%X-%X-%X$$FG$$\n", EndianU32(sys_info->uuid(U32 *)),
						EndianU16((sys_info->uuid)(U16 *)[2]), EndianU16((sys_info->uuid)(U16 *)[3]), EndianU16((sys_info->uuid)(U16 *)[4]),
						EndianU16((sys_info->uuid)(U16 *)[5]) << 32 | EndianU32((sys_info->uuid)(U32 *)[3]);
					"Wakeup Type\t\t:$$BLACK$$%Z$$FG$$\n", sys_info->wakeup_type, "ST_SMBIOS_WAKEUP_TYPES";
					"SKU Number\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, sys_info->sku_number);
					"Family\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, sys_info->family);
					"$$ID,-4$$";
					break;
				case SMBIOSt_ENCLOSURE:
					CSMBIOSEnclosureInfo *info = header;
					"$$TR-C,\"Enclosure\"$$\n";
					"$$ID,4$$Manufacturer\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, info->manufacturer);
					"Type\t\t\t:$$BLACK$$%Z%z$$FG$$\n", info->type & 0x7F, "ST_SMBIOS_ENCLOSURE_TYPES",
						Bt(&info->type, 7), " \0, Lock Present";
					"Version\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, info->version);
					"Bootup State\t:$$BLACK$$%Z$$FG$$\n", info->bootup_state, "ST_SMBIOS_ENCLOSURE_STATES";
					"Thermal State\t:$$BLACK$$%Z$$FG$$\n", info->thermal_state, "ST_SMBIOS_ENCLOSURE_STATES";
					"Power Supply\t:$$BLACK$$%Z$$FG$$\n", info->power_supply_state, "ST_SMBIOS_ENCLOSURE_STATES";
					"Security Status\t:$$BLACK$$%Z$$FG$$\n", info->security_status, "ST_SMBIOS_ENCLOSURE_SECURITY_STATUSES";
					"Height\t\t\t:$$BLACK$$";
					if (info->height)
						"%0.2f\"$$FG$$\n", info->height * 1.75; //height is in 'U' units. 1 'U' is 1.75 inches or 4.445 cm.
					else "Unknown$$FG$$\n";
					"Serial Number\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, info->serial_number);
					"Asset Tag\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, info->asset_tag);
					"Power Cord Count:$$BLACK$$";
					if (info->power_cord_count)
						"%d$$FG$$\n", info->power_cord_count;
					else "Unknown$$FG$$\n";
//					"Contained Elements:$$BLACK$$",r,'\t';  //TODO: maybe implement this?
					"$$ID,-4$$";
					break;
				case SMBIOSt_PROCESSOR:
					CSMBIOSProcessorInfo *p_info = header;
					CRAXRBXRCXRDX regs;
					CPUId(1, &regs);
					"$$TR-C,\"Processor\"$$\n";
					"$$ID,4$$Socket Name\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, p_info->name);
					"Processor Type\t:$$BLACK$$%Z$$FG$$\n", p_info->type, "ST_SMBIOS_PROCESSOR_TYPES";
					"Status\t\t\t:$$BLACK$$%z, %z$$FG$$\n",  p_info->status >> 6, "Socket Unpopulated\0Socket Populated", 
						p_info->status & 7, "Unknown\0CPU Enabled\0CPU Disabled through BIOS Setup\0"
						"CPU Disabled by BIOS (POST Error)\0CPU is Idle, Waiting to be Enabled\0 \0 \0Other";
					"Core Count\t\t:$$BLACK$$%d$$FG$$\n", p_info->core_count;
					"Cores Enabled\t:$$BLACK$$%d$$FG$$\n", p_info->cores_enabled;
					"Manufacturer\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, p_info->manufacturer);
//					"CPU Family\t\t\t:$$BLACK$$%z$$FG$$\n", p_info->family, "ST_SMBIOS_PROCESSOR_FAMILIES"; TODO: maybe implement this?
					"Name\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, p_info->version);
					"Family\t\t\t:$$BLACK$$";
					if (regs.rax >> 8 & 0xF < 0xF)
						"%d$$FG$$\n", regs.rax >> 8 & 0xF;
					else
						"%d$$FG$$\n", 0xF + regs.rax >> 20 & 0xFF;

					"Model\t\t\t:$$BLACK$$";
					if (regs.rax >> 4 & 0xF < 0xF)
						"%d$$FG$$\n", regs.rax >> 4 & 0xF;
					else
						"%d$$FG$$\n", (regs.rax >> 4 & 0xF) << 4 | (regs.rax >> 16 & 0xF);

					"Stepping\t\t:$$BLACK$$%d$$FG$$\n", regs.rax & 0xF;
					"Current Speed\t:$$BLACK$$";
					if (p_info->current_speed)
						"%0.1f GHz$$FG$$\n", p_info->current_speed / 1000.0;
					else "Unknown$$FG$$\n";

					"Max Speed\t\t:$$BLACK$$";
					if (p_info->max_speed)
						"%0.1f GHz$$FG$$\n", p_info->max_speed / 1000.0;
					else "Unknown$$FG$$\n";
					"Socket\t\t\t:$$BLACK$$%Z$$FG$$\n", p_info->upgrade, "ST_SMBIOS_PROCESSOR_UPGRADES";

					"Voltage\t\t\t:$$BLACK$$";
					if (Bt(&p_info->voltage, 7))
						"%0.1fV$$FG$$\n", (p_info->voltage & 0x7F) / 10.0;
					else
						"%Z$$FG$$\n", Bsf(p_info->voltage), "ST_SMBIOS_PROCESSOR_VOLTAGE_LEVELS";

					"External Clock\t:$$BLACK$$";
					if (p_info->external_clock)
						"%d MHz$$FG$$\n", p_info->external_clock;
					else "Unknown$$FG$$\n";
						
					"Serial Number\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, p_info->serial_number);
					"Asset Tag\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, p_info->asset_tag);
					"Part Number\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, p_info->part_number);
						
					"$$TR,\"Processor Flags\"$$";
					StrPrintFlags(buffer, Define("ST_SMBIOS_PROCESSOR_FLAGS"), p_info->characteristics, show_all_flags, 9);
					str = SysRepFlagsMake(buffer);
					"%s\n", str;
					"$$TR,\"CPUID 0x1 Flags\"$$";
					StrPrintFlags(buffer, Define("ST_CPUID_1_EDX_FLAGS"), regs.rdx, show_all_flags, 32);
					CatPrint(buffer, StrPrintFlags(buffer2, Define("ST_CPUID_1_ECX_FLAGS"), regs.rcx, show_all_flags, 31));
					str = SysRepFlagsMake(buffer);
					"%s$$FG$$\n", str;
					Free(str);
					if (p_info->l1_cache_handle && p_info->l1_cache_handle != 0xFFFF)
					{
						"$$TR,\"L1 Cache Info\"$$\n";
						SysRep(,p_info->l1_cache_handle, show_all_flags);
					}
					if (p_info->l2_cache_handle && p_info->l2_cache_handle != 0xFFFF)
					{
						"$$TR,\"L2 Cache Info\"$$\n";
						SysRep(,p_info->l2_cache_handle, show_all_flags);
					}
					if (p_info->l3_cache_handle && p_info->l3_cache_handle != 0xFFFF)
					{
						"$$TR,\"L3 Cache Info\"$$\n";
						SysRep(,p_info->l3_cache_handle, show_all_flags);
					}
					"$$ID,-4$$";
					break;
				case SMBIOSt_CACHE:
					if (!handle)
						break;
					if (cache_count++ > 0)
						break;
					CSMBIOSCacheInfo *c_info = header;
					"$$ID, 4$$";
					"Name\t\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, c_info->name);
					"Status\t\t\t\t:$$BLACK$$%z$$FG$$\n", Bt(&c_info->config, 7), "Disabled\0Enabled";
					"Mode\t\t\t\t:$$BLACK$$%z$$FG$$\n",  c_info->config >> 8 & 3, "Write-Through\0Write-Back\0Varies with Memory Address\0Unknown";
					"Type\t\t\t\t:$$BLACK$$%z$$FG$$\n", c_info->cache_type, " \0Other\0Unknown\0Instruction\0Data\0Unified";
					"Location\t\t\t:$$BLACK$$%z$$FG$$\n", c_info->config >> 5 & 3, "CPU Internal\0External\0 \0Unknown";
					"Socketed\t\t\t:$$BLACK$$%z$$FG$$\n", Bt(&c_info->config, 3), "No\0Yes";
					"Max Cache Size\t\t:$$BLACK$$";
					if (Bt(&c_info->max_size, 15)) //if Bit 15 is 1 then granularity is 64K else 1K
						"%d KB$$FG$$\n", (c_info->max_size & 0x7FFF) * 64;
					else
						"%d KB$$FG$$\n", c_info->max_size & 0x7FFF;
					"Installed Size\t\t:$$BLACK$$";
					if (Bt(&c_info->installed_size, 15)) //if Bit 15 is 1 then granularity is 64K else 1K
						"%d KB$$FG$$\n", (c_info->installed_size & 0x7FFF) * 64;
					else
						"%d KB$$FG$$\n", c_info->installed_size & 0x7FFF;
					StrPrintFlags(buffer, Define("ST_SMBIOS_CACHE_SRAM_TYPES"), c_info->supported_sram_type);
					str = StrReplace(StrReplace(buffer, "+", ", "), "+", ", ",,TRUE);
					StrCopy(str, str + 2);
					"Supported SRAM Types:$$BLACK$$%s$$FG$$\n", str;
					Free(str);
					StrPrintFlags(buffer, Define("ST_SMBIOS_CACHE_SRAM_TYPES"), c_info->installed_sram_type);
					str = StrReplace(StrReplace(buffer, "+", ", "), "+", ", ",,TRUE);
					StrCopy(str, str + 2);
					"Installed SRAM Type\t:$$BLACK$$%s$$FG$$\n", str;
					Free(str);
					"Cache Speed\t\t\t:$$BLACK$$";
					if (c_info->cache_speed)
						"%d nS$$FG$$\n", c_info->cache_speed;
					else "Unknown$$FG$$\n";
					"ECC type\t\t\t:$$BLACK$$%z$$FG$$\n", c_info->error_correction_type, 
						" \0Other\0Unknown\0None\0Parity\0Single-bit ECC\0Multi-bit ECC";
					"Associativity\t\t:$$BLACK$$%Z$$FG$$\n", c_info->associativity, "ST_SMBIOS_CACHE_ASSOCIATIVITY";
					"$$ID,-4$$";
					break;
				case SMBIOSt_MEM_DEVICE:
					CSMBIOSMemDeviceInfo *mem_info = header;
					"$$TR,\"Memory Device\"$$\n";
					"$$ID,4$$";
//					ClassRep(mem_info,,,,TRUE);
					"Size\t\t\t:$$BLACK$$";
					if (!mem_info->size)
						"No Device Installed$$FG$$\n";
					else if (mem_info->size == 0xFFFF)
						"Unknown$$FG$$\n";
					else if (mem_info->size == 0x7FFF)
						"%d GB$$FG$$\n", mem_info->extended_size;
					else
						"%d %zB$$FG$$\n", mem_info->size & 0x7FFF, Bt(&mem_info->size, 15), "M\0K";
						
					"Total Width\t\t:$$BLACK$$";
					if (mem_info->total_width != 0xFFFF)
						"%d bits$$FG$$\n", mem_info->total_width;
					else
						"Unknown$$FG$$\n";
					"Data Width\t\t:$$BLACK$$";
					if (mem_info->data_width != 0xFFFF)
						"%d bits$$FG$$\n", mem_info->data_width;
					else
						"Unknown$$FG$$\n";
					"Manufacturer\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, mem_info->manufacturer);
					"$$ID,-4$$";
					break;
				case SMBIOSt_BASEBOARD:
					CSMBIOSBaseboardInfo *b_info = header;
					"$$TR-C,\"Baseboard\"$$\n";
					"$$ID,4$$";
					"Manufacturer\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->manufacturer);
					"Product\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->product);
					"Version\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->version);
					"Type\t\t\t:$$BLACK$$%Z$$FG$$\n",  b_info->board_type, "ST_SMBIOS_BASEBOARD_TYPES";
					"Location\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->chassis_location, "Not Specified");
					"Serial Number\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->serial_number);
					"Asset Tag\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->asset_tag);
					"$$TR,\"Flags\"$$";
					StrPrintFlags(buffer, Define("ST_SMBIOS_BASEBOARD_FLAGS"), b_info->feature_flags, show_all_flags, 5);
					str = SysRepFlagsMake(buffer);
					"%s$$FG$$\n", str;
					Free(str);
					"$$ID,-4$$";
					break;
				case SMBIOSt_CONNECTOR:
					CSMBIOSConnectorInfo *con_info = header;
					"$$TR,\"Port Connector\"$$\n";
					"$$ID,4$$";
					"Port Type\t\t:$$BLACK$$";
					if (con_info->port_type == 0xFF)
						"Other$$FG$$\n";
					else
						"%Z$$FG$$\n", con_info->port_type, "ST_SMBIOS_PORT_TYPES";
					"External Name\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, con_info->external_name);
					"Internal Name\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, con_info->internal_name);
					"External Type\t:$$BLACK$$";
					if (con_info->external_type == 0xFF)
						"Other$$FG$$\n";
					else
						"%Z$$FG$$\n", con_info->external_type, "ST_SMBIOS_CONNECTOR_TYPES";
					"Internal Type\t:$$BLACK$$";
					if (con_info->internal_type == 0xFF)
						"Other$$FG$$\n";
					else
						"%Z$$FG$$\n", con_info->internal_type, "ST_SMBIOS_CONNECTOR_TYPES";
					"$$ID,-4$$";
					break;
				case SMBIOSt_BATTERY:
					CSMBIOSBatteryInfo *bat_info = header;
					"$$TR,\"Battery\"$$\n";
					"$$ID,4$$";
					"Name\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, bat_info->name);
					"Manufacturer\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, bat_info->manufacturer);
					"$MA-X+PU,"SBDS",LM="\"\dGREEN\dS\dFG\dmart \dGREEN\dB\dFG\dattery \dGREEN\dD\dFG\data \dGREEN\dS\dFG\dpecification\n\";View;"$ Version\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, bat_info->manufacturer);
					"Manufacture Date:$$BLACK$$";
					if (bat_info->manufacture_date)
						"%s$$FG$$\n", SMBIOSStr(header, bat_info->manufacture_date);
					else
						"%s$$FG$$\n", SMBIOSStr(header, bat_info->sbds_manufacture_date);
					"Chemistry\t\t:$$BLACK$$";
					if (bat_info->chemistry)
						"%s$$FG$$\n", SMBIOSStr(header, bat_info->chemistry);
					else
						"%s$$FG$$\n", SMBIOSStr(header, bat_info->sbds_chemistry);
					"Capacity\t\t:$$BLACK$$";
					if (bat_info->capacity)
						"%d Milliwatt-Hours$$FG$$\n", bat_info->capacity * bat_info->capacity_multiplier;
					else
						"Unknown$$FG$$\n";
					"Voltage\t\t\t:$$BLACK$$";
					if (bat_info->voltage)
						"%d Millivolts$$FG$$\n", bat_info->voltage;
					else
						"Unknown$$FG$$\n";
					"Max Data Error\t:$$BLACK$$";
					if (bat_info->max_battery_data_error != 0xFF)
						"%d$$FG$$\n", bat_info->max_battery_data_error;
					else
						"Unknown$$FG$$\n";
					"Serial Number\t:$$BLACK$$";
					if (bat_info->serial_number)
						"%s$$FG$$\n", SMBIOSStr(header, bat_info->serial_number);
					else
						"%d$$FG$$\n", bat_info->sbds_serial_number;
					"$$ID,-4$$";
					break;
				case SMBIOSt_OEM_STRINGS:
				case SMBIOSt_SYS_CONFIG_OPTIONS:
					if (header->type == SMBIOSt_OEM_STRINGS)	
						"$$TR,\"OEM Strings\"$$\n";
					else
						"$$TR,\"Sys Config Strings\"$$\n";
					"$$ID,4$$";
					str = *(header(U8 *) + sizeof(CSMBIOSHeader));
					"Strings";
					for (i = 1; i <= str; i++)
					{
						if (i == 1)
							"\t\t\t:";
						else
							"\t\t\t\t ";
						"$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, i);
					}
					"$$ID,-4$$";
					break;
					
			end:
				structure_count++;
 		}
loop_end:
		header = header(U8 *) + header->length;
		for (i = 1; header(U8 *)[i - 1] || header(U8 *)[i]; i++);
		header = header(U8 *) + i + 1;
	}
	if (!handle)
		"$$FD,BLUE$$";
	return structure_count;
}

U0 BIOSRep()
{
	SysRep(SMBIOSt_BIOS);
}

SMBIOSInit;
//BIOSRep;
SysRep();