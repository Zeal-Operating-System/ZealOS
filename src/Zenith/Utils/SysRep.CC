//SMBIOS parsing.
//Based on SMBIOS specification 3.3.0 (document "DSP0134")
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
		" \0Other\0Unknown\0APM Timer\0Modem Ring\0LAN Remote\0Power Switch\0PCI PME#\0AC Power Restored");
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
	DefineListLoad("ST_SMBIOS_ENCLOSURE_STATES", " \0Other\0Unknown\0Safe\0Warning\0Critical\0Non-Recoverable");
	//Section 7.4.3 line 994 (enclosure security status field)
	DefineListLoad("ST_SMBIOS_ENCLOSURE_SECURITY_STATUSES",
		" \0Other\0Unknown\0None\0External Interface Locked Out\0External Interface Enabled");
	//Section 7.5.1 line 1014 (processor type field)
	DefineListLoad("ST_SMBIOS_PROCESSOR_TYPES", " \0Other\0Unknown\0Central Processor\0Math Processor\0DSP Processor\0Video Processor");
	//Section 7.5.4 line 1050 (processor voltage field)
	DefineListLoad("ST_SMBIOS_PROCESSOR_VOLTAGE_LEVELS", "5V\03.3V\02.9V");
	DefineListLoad("ST_CPUID_1_EDX_FLAGS", "x87 FPU\0Virtual 8086 Mode Enhancements\0Debugging Extensions\0Page Size Extensions\0"
		"Time Stamp Counter\0MSRs\0Page Address Extension\0Machine Check Exceptions\0CMPXCHG8B\0APIC\0 \0SYSENTER/SYSEXIT\0"
		"Memory Type Range Registers\0Page Global Bit\0Machine Check Architecture\0CMOV Instructions\0Page Attribute Table\0"
		"36 Bit Page Size Extension\0Processor Serial Number\0CLFLUSH\0 \0Debug Store\0ACPI\0MMX\0FXSAVE/FXRSTOR\0SSE\0SSE2\0"
		"Self Snoop\0HTT\0Thermal Monitor\0 \0Pending Break Enable\0");
	DefineListLoad("ST_CPUID_1_ECX_FLAGS", "SSE3\0PCLMULQDQ\064 bit DS AREA\0MONITOR/MWAIT\0CPL Qualified Debug Store\0"
		"Virtual Machine Extensions\0Safer Mode Extensions\0 \0Thermal Monitor 2\0SSSE3\0L1 Context ID\0"
		"IA32_DEBUG_INTERFACE\0FMA Extensions\0CMPXCHG16B\0xTPR Update Control\0Perfmon and Debug Capability\0 \0"
		"Process Context Identifiers\0MMIO Prefetch\0SSE4.1\0SSE4.2\0x2APIC\0MOVBE\0POPCNT\0TSC Deadline\0AESNI\0XSAVE\0"
		"OSXSAVE\0AVX\0F16C\0RDRAND");
	//Section 7.5.5 line 1058 (upgrade field)
	DefineListLoad("ST_SMBIOS_PROCESSOR_UPGRADES", " \0Other\0Unknown\0Daughterboard\0ZIF Socket\0Replacable Piggy Back\0"
		"None\0LIF Socket\0Slot 1\0Slot2\0370-pin Socket\0Slot A\0Slot M\0Socket 423\0Socket A (Socket 462)\0Socket 478\0"
		"754\0940\0939\0mPGA604\0LGA771\0LGA775\0S1\0AM2\0F (1207)\0LGA1366\0G34\0AM3\0C32\0LGA1156\0LGA1567\0PGA988A\0"
		"BGA1288\0rPGA988B\0BGA1023\0BGA1224\0LGA1155\0LGA1356\0LGA2011\0FS1\0FS2\0FM1\FM2\0LGA2011-3\0LGA1356-3\0LGA1150\0"
		"BGA1168\0BGA1234\BGA1364\0AM4\0LGA1151\0BGA1440\0BGA1515\0LGA3647-1\0SP3\0SP3r2\0LGA2066\0BGA1932\0BGA1510\0BGA1528");
	//Section 7.5.9 line 1110 (processor characteristics)
	DefineListLoad("ST_SMBIOS_PROCESSOR_FLAGS",  " \0 \064 Bit\0Multicore\0HyperThreading\0NX/XD Protection\0Enhanced Virtualization\0"
		"Power/Performance Control\0128 Bit Capable");
	//Section 7.8.2 line 1178 (cache information SRAM type field)
	DefineListLoad("ST_SMBIOS_CACHE_SRAM_TYPES", "Other\0Unknown\0Non-Burst\0Burst\0Pipeline Burst\0Synchronous\0Asynchronous");
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
	//Section 7.10.1 line 1229 (slot type)
	DefineListLoad("ST_SMBIOS_SLOT_TYPES1", " \0Other\0Unknown\0ISA\0MCA\0EISA\0PCI\0PC Card (PCMCIA)\0VESA Local Bus\0Proprietary\0"
		"Proprietary Card Slot\0Proprietary Memory Card Slot\0I/O Riser Card Slot\0NuBus\0PCI - 66 MHz Capable\0AGP\0AGP 2X\0AGP 4X\0"
		"PCI-X\0AGP 8X\0M.2 Socket 1-DP (Mechanical Key A)\0M.2 Socket 1-SD (Mechanical Key E)\0M.2 Socket 2 (Mechanical Key B)\0"
		"M.2 Socket 3 (Mechanical Key M)\0MXM Type I\0MXM Type II\0MXM Type III (Standard Connector)\0MXM Type III (HE Connector)\0"
		"MXM Type IV\0MXM 3.0 Type A\0MXM 3.0 Type B\0PCI Express Gen 2 SFF-8639\0PCI Express Gen 3 SFF-8639\0"
		"PCI Express Mini 52-Pin with bottom-side keep-outs\0PCI Express Mini 52-Pin without bottom-side keep-outs\0"
		"PCI Express Mini 76-Pin\0CXL Flexbus 1.0");
	DefineListLoad("ST_SMBIOS_SLOT_TYPES2", " \0 \0 \0 \0 \0PCI Express\0PCI Express 1x\0PCI Express 2x\0PCI Express 4x\0PCI Express 8x\0"
		"PCI Express 16x\0PCI Express Gen 2\0PCI Express Gen 2 1x\0PCI Express Gen 2 2x\0PCI Express Gen 2 4x\0PCI Express Gen 2 8x\0"
		"PCI Express Gen 2 16x\0PCI Express Gen 3\0PCI Express Gen 3 1x\0PCI Express Gen 3 2x\0PCI Express Gen 3 4x\0PCI Express Gen 3 8x\0"
		"PCI Express Gen 3 16x\0PCI Express Gen 4\0PCI Express Gen 4 1x\0PCI Express Gen 4 2x\0PCI Express Gen 4 4x\0PCI Express Gen 4 8x\0"
		"PCI Express Gen 4 16x");
	//Section 7.10.2 line 1244 (slot data bus width field)
	DefineListLoad("ST_SMBIOS_SLOT_DATA_BUS_WIDTHS"," \0Other\0Unknown\08 Bit\016 Bit\032 Bit\064 Bit\0128 Bit\01x\02x\04x\08x\012x\016x\032x");
	//Section 7.10.6 line 1259 (slot characteristics 1 field)
	DefineListLoad("ST_SMBIOS_SLOT_FLAGS1", " \05.0 V\03.3 V\0Shared Slot Opening\0PC Card 16\0CardBus\0Zoom Video\0Modem Ring Resume");
	//Section 7.10.7 line 1262 (slot characteristics 2 field)
	DefineListLoad("ST_SMBIOS_SLOT_FLAGS2", "PCI Power Management Event (PME#) Signal\0HotPlug\0SMBus\0Bifurcation");
	//Section 7.17.1 line 1523 (memory array location field)
	DefineListLoad("ST_SMBIOS_PHYMEM_LOCATIONS", " \0Other\0Unknown\0Motherboard\0ISA Add-On Card\0EISA Add-On Card\0PCI Add-On Card\0"
		"MCA Add-On Card\0PCMCIA Add-On Card\0Proprietary Add-On Card\0NuBus\0 \0 \0 \0 \0 \0");
	//Section 7.17.2 line 1527 (memory array use field)
	DefineListLoad("ST_SMBIOS_PHYMEM_USES", " \0Other\0Unknown\0System Memory\0Video Memory\0Flash Memory\0Non-Volatile RAM\0Cache Memory");
	//Section 7.18.1 line 1542 (form factor field)
	DefineListLoad("ST_SMBIOS_MEMDEV_FORM_FACTORS",
		" \0Other\0Unknown\0SIMM\0SIP\0DIP\0ZIP\0Proprietary Card\0DIMM\0TSOP\0Row of Chips\0RIMM\0SODIMM\0SRIMM\0FB-DIMM\0Die");
	//Section 7.18.2 line 1546 (type field)
	DefineListLoad("ST_SMBIOS_MEMDEV_TYPES", " \0Unknown\0DRAM\0EDRAM\0VRAM\0SRAM\0RAM\0ROM\0FLASH\0EEPROM\0FEPROM\0EPROM\0CDRAM\0"
		"3DRAM\0SDRAM\0SGRAM\0RDRAM\0DDR\0DDR2\0DDR2 FB-DIMM\0 \0 \0 \0DDR3\0FBD2\0DDR4\0LPDDR\0LPDDR2\0LPDDR3\0LPDDR4\0"
		"Logical Non-Volatile Device\0HBM (High Bandwidth Memory)\0HBM2 (High Bandwidth Memory Gen 2)");
	//Section 7.18.3 line 1550 (type detail field)
	DefineListLoad("ST_SMBIOS_MEMDEV_TYPE_DETAILS", " \0 \0 \0Fast Paged\0Static Column\0Psuedo Static\0RAMBUS\0Synchronous\0"
		"CMOS\0EDO\0Window DRAM\0Cache DRAM\0Non Volatile\0Registered (Buffered)\0Unregistered (Unbuffered)\0LRDIMM");
} SMBIOSInit;

Bool SMBIOSEntryScan(CSMBIOSEntryPoint **entry)
{//Search 0xF0000 - 0x100000 for SMBIOS Entry Point structure.
	I64 i;
	U8 noreg checksum = 0, *mem = 0xF0000;
	do
	{
		if (!MemCompare(mem, "_SM_", 4))
		{
			*entry = mem;
			for (i = 0; i < (*entry)->length; i++)
				checksum += mem[i];

			if (checksum == 0) //valid checksums sum to zero
				break;
		}
	} while ((mem += 16) < 0x100000); //anchor sits on 16-byte boundary
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
		"+", "\n$$BLUE$$+$$GREEN$$",, TRUE),
		"-", "\n$$BLUE$$-$$RED$$",, TRUE);

	str = MStrPrint("$$ID,17$$%s$$ID,-17$$", tmp);
	Free(tmp);
	return str;
}

public I64 SysRep(I64 type=0xFF, I64 handle=0, Bool show_all_flags=FALSE, I64 memdev_handle=0xFFFF)
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
					"$$ID,3$$"
					"Vendor\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, bios_info->vendor);
					"Version\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, bios_info->version);
					"Release Date\t\t:$$BLACK$$%s (mm/dd/yyyy)$$FG$$\n", SMBIOSStr(header, bios_info->release_date);
					"Release Version\t:$$BLACK$$%d.%d$$FG$$\n", bios_info->major_release, bios_info->minor_release;
					"Start Address\t:$$BLACK$$0x%X$$FG$$\n", Seg2Linear(&start_addr);
					"Image Size\t\t:$$BLACK$$%d bytes$$FG$$\n", (0x10000 - bios_info->start_address_segment) * 16;
					"ROM Size\t\t\t:$$BLACK$$";
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
					"$$ID,-3$$";
					break;
				case SMBIOSt_SYSTEM:
					CSMBIOSSystemInfo *sys_info = header;
					"$$TR-C,\"System\"$$\n";
					"$$ID,3$$Manufacturer\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, sys_info->manufacturer);
					"Product Name\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, sys_info->product_name);
					"Version\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, sys_info->version);
					"Serial Number\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, sys_info->serial_number);
					"UUID\t\t\t\t:$$BLACK$$%X-%X-%X-%X-%X$$FG$$\n", EndianU32(sys_info->uuid(U32 *)),
						EndianU16((sys_info->uuid)(U16 *)[2]), EndianU16((sys_info->uuid)(U16 *)[3]), EndianU16((sys_info->uuid)(U16 *)[4]),
						EndianU16((sys_info->uuid)(U16 *)[5]) << 32 | EndianU32((sys_info->uuid)(U32 *)[3]);
					"Wakeup Type\t\t:$$BLACK$$%Z$$FG$$\n", sys_info->wakeup_type, "ST_SMBIOS_WAKEUP_TYPES";
					"SKU Number\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, sys_info->sku_number);
					"Family\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, sys_info->family);
					"$$ID,-3$$";
					break;
				case SMBIOSt_ENCLOSURE:
					CSMBIOSEnclosureInfo *info = header;
					"$$TR-C,\"Enclosure\"$$\n";
					"$$ID,3$$Manufacturer\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, info->manufacturer);
					"Type\t\t\t\t:$$BLACK$$%Z%z$$FG$$\n", info->type & 0x7F, "ST_SMBIOS_ENCLOSURE_TYPES",
						Bt(&info->type, 7), " \0, Lock Present";
					"Version\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, info->version);
					"Bootup State\t\t:$$BLACK$$%Z$$FG$$\n", info->bootup_state, "ST_SMBIOS_ENCLOSURE_STATES";
					"Thermal State\t:$$BLACK$$%Z$$FG$$\n", info->thermal_state, "ST_SMBIOS_ENCLOSURE_STATES";
					"Power Supply\t\t:$$BLACK$$%Z$$FG$$\n", info->power_supply_state, "ST_SMBIOS_ENCLOSURE_STATES";
					"Security Status\t:$$BLACK$$%Z$$FG$$\n", info->security_status, "ST_SMBIOS_ENCLOSURE_SECURITY_STATUSES";
					"Height\t\t\t:$$BLACK$$";
					if (info->height)
						"%0.2f\"$$FG$$\n", info->height * 1.75; //height is in 'U' units. 1 'U' is 1.75 inches or 4.445 cm.
					else "Unknown$$FG$$\n";
					"Serial Number\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, info->serial_number);
					"Asset Tag\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, info->asset_tag);
					"Power Cord Count\t:$$BLACK$$";
					if (info->power_cord_count)
						"%d$$FG$$\n", info->power_cord_count;
					else "Unknown$$FG$$\n";
//					"Contained Elements:$$BLACK$$",r,'\t';  //TODO: maybe implement this?
					"$$ID,-3$$";
					break;
				case SMBIOSt_PROCESSOR:
					CSMBIOSProcessorInfo *p_info = header;
					CRAXRBXRCXRDX regs;
					CPUId(1, &regs);
					"$$TR-C,\"Processor\"$$\n";
					"$$ID,3$$Socket Name\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, p_info->name);
					"Processor Type\t:$$BLACK$$%Z$$FG$$\n", p_info->type, "ST_SMBIOS_PROCESSOR_TYPES";
					"Status\t\t\t:$$BLACK$$%z, %z$$FG$$\n",  p_info->status >> 6, "Socket Unpopulated\0Socket Populated", 
						p_info->status & 7, "Unknown\0CPU Enabled\0CPU Disabled through BIOS Setup\0"
						"CPU Disabled by BIOS (POST Error)\0CPU is Idle, Waiting to be Enabled\0 \0 \0Other";
					"Core Count\t\t:$$BLACK$$%d$$FG$$\n", p_info->core_count;
					"Cores Enabled\t:$$BLACK$$%d$$FG$$\n", p_info->cores_enabled;
					"Manufacturer\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, p_info->manufacturer);
//					"CPU Family\t\t\t:$$BLACK$$%z$$FG$$\n", p_info->family, "ST_SMBIOS_PROCESSOR_FAMILIES"; TODO: maybe implement this?
					"Name\t\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, p_info->version);
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

					"Stepping\t\t\t:$$BLACK$$%d$$FG$$\n", regs.rax & 0xF;
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
						
					StrPrintFlags(buffer, Define("ST_SMBIOS_PROCESSOR_FLAGS"), p_info->characteristics, show_all_flags, 9);
					str = SysRepFlagsMake(buffer);
					"$$TR,\"Processor Flags\"$$%s$$FG$$\n", str;
					StrPrintFlags(buffer, Define("ST_CPUID_1_EDX_FLAGS"), regs.rdx, show_all_flags, 32);
					CatPrint(buffer, StrPrintFlags(buffer2, Define("ST_CPUID_1_ECX_FLAGS"), regs.rcx, show_all_flags, 31));
					str = SysRepFlagsMake(buffer);
					"$$TR,\"CPUID 0x1 Flags\"$$%s$$FG$$\n", str;
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
					"$$ID,-3$$";
					break;
				case SMBIOSt_CACHE:
					if (!handle)
						break;
					if (cache_count++ > 0)
						break;
					CSMBIOSCacheInfo *c_info = header;
					"$$ID,3$$";
					"Name\t\t\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, c_info->name);
					"Status\t\t\t\t:$$BLACK$$%z$$FG$$\n", Bt(&c_info->config, 7), "Disabled\0Enabled";
					"Mode\t\t\t\t\t:$$BLACK$$%z$$FG$$\n",  c_info->config >> 8 & 3, "Write-Through\0Write-Back\0Varies with Memory Address\0Unknown";
					"Type\t\t\t\t\t:$$BLACK$$%z$$FG$$\n", c_info->cache_type, " \0Other\0Unknown\0Instruction\0Data\0Unified";
					"Location\t\t\t\t:$$BLACK$$%z$$FG$$\n", c_info->config >> 5 & 3, "CPU Internal\0External\0 \0Unknown";
					"Socketed\t\t\t\t:$$BLACK$$%z$$FG$$\n", Bt(&c_info->config, 3), "No\0Yes";
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
					str = StrReplace(buffer, "+", ", ");
					"Supported SRAM Types\t:$$BLACK$$%s$$FG$$\n", str + 2;
					Free(str);
					"Installed SRAM Type\t:$$BLACK$$%Z$$FG$$\n", Bsf(c_info->installed_sram_type), "ST_SMBIOS_CACHE_SRAM_TYPES";
					"Cache Speed\t\t\t:$$BLACK$$";
					if (c_info->cache_speed)
						"%d nS$$FG$$\n", c_info->cache_speed;
					else "Unknown$$FG$$\n";
					"ECC type\t\t\t\t:$$BLACK$$%z$$FG$$\n", c_info->error_correction_type, 
						" \0Other\0Unknown\0None\0Parity\0Single-bit ECC\0Multi-bit ECC";
					"Associativity\t\t\t:$$BLACK$$%Z$$FG$$\n", c_info->associativity, "ST_SMBIOS_CACHE_ASSOCIATIVITY";
					"$$ID,-3$$";
					break;
				case SMBIOSt_PHYMEM:
					CSMBIOSMemArrayInfo *ma_info = header;
					"$$TR,\"Memory Array\"$$\n";
					"$$ID,3$$";
					"Location\t\t\t:$$BLACK$$%Z$$FG$$\n", ma_info->location, "ST_SMBIOS_PHYMEM_LOCATIONS";
					"Use\t\t\t\t:$$BLACK$$%Z$$FG$$\n", ma_info->use, "ST_SMBIOS_PHYMEM_USES";
					"Error Correction\t:$$BLACK$$%z$$FG$$\n", ma_info->use, " \0Other\0Unknown\0None\0Parity\0Single-bit ECC\0Multi-bit ECC\0CRC";
					"Max Capacity\t\t:$$BLACK$$";
					if (ma_info->max_capacity == 0x80000000)
						"%d MB$$FG$$\n", ma_info->extended_max_capacity / 1024;
					else						
						"%d MB$$FG$$\n", ma_info->max_capacity / 1024;
					"Mem Device Count\t:$$BLACK$$%d$$FG$$\n", ma_info->mem_device_count;
					"$$TR,\"Memory Devices\"$$\n";
					"$$ID,3$$";
					SysRep(SMBIOSt_MEM_DEVICE, handle, show_all_flags, ma_info->header.handle);
					"$$ID,-3$$";
					"$$ID,-3$$";
					break;
				case SMBIOSt_MEM_DEVICE:
					CSMBIOSMemDeviceInfo *mem_info = header;
					if (type != SMBIOSt_MEM_DEVICE)
						break;
					if (memdev_handle != 0xFFFF && memdev_handle != mem_info->memory_array_handle)
						break;
					"$$TR,\"Memory Device\"$$\n";
					"$$ID,3$$";
					"Device Location\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, mem_info->device_locator);
					"Bank Location\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, mem_info->bank_locator);
					"Manufacturer\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, mem_info->manufacturer);
					"Size\t\t\t\t:$$BLACK$$";
					if (!mem_info->size)
						"No Device Installed$$FG$$\n";
					else if (mem_info->size == 0xFFFF)
						"Unknown$$FG$$\n";
					else if (mem_info->size == 0x7FFF)
						"%d GB$$FG$$\n", mem_info->extended_size; 
					else
						"%d %zB$$FG$$\n", mem_info->size & 0x7FFF, Bt(&mem_info->size, 15), "M\0K";
					if (entry->major_version >= 2 && entry->minor_version >= 8)
					{
						"Min Voltage\t\t:$$BLACK$$";
						if (mem_info->min_voltage)
							"%d mV$$FG$$\n", mem_info->min_voltage;
						else
							"Unknown$$FG$$\n";
						"Max Voltage\t\t:$$BLACK$$";
						if (mem_info->max_voltage)
							"%d mV$$FG$$\n", mem_info->max_voltage;
						else
							"Unknown$$FG$$\n";
						"Configured Volt.\t:$$BLACK$$";
						if (mem_info->configured_voltage)
							"%d mV$$FG$$\n", mem_info->configured_voltage;
						else
							"Unknown$$FG$$\n";
					}
					"Total Width\t\t:$$BLACK$$";
					if (mem_info->total_width != 0xFFFF)
						"%d bits$$FG$$\n", mem_info->total_width;
					else
						"Unknown$$FG$$\n";
					"Data Width\t\t\t:$$BLACK$$";
					if (mem_info->data_width != 0xFFFF)
						"%d bits$$FG$$\n", mem_info->data_width;
					else
						"Unknown$$FG$$\n";
					"Max Speed\t\t\t:$$BLACK$$";
					if (mem_info->speed)
						"%d $MA-X+PU,"MT/s",LM="\"megatransfers per second\";View;"$$$FG$$\n", mem_info->speed;
					else
						"Unknown$$FG$$\n";
					"Configured Speed\t:$$BLACK$$";
					if (mem_info->configured_speed)
						"%d $MA-X+PU,"MT/s",LM="\"megatransfers per second\";View;"$$$FG$$\n", mem_info->configured_speed;
					else
						"Unknown$$FG$$\n";
					"Serial Number\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, mem_info->serial_number);
					"Part Number\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, mem_info->part_number);
					"Asset Tag\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, mem_info->asset_tag);
					"Form Factor\t\t:$$BLACK$$%Z$$FG$$\n", mem_info->form_factor, "ST_SMBIOS_MEMDEV_FORM_FACTORS";
					"Type\t\t\t\t:$$BLACK$$%Z$$FG$$\n", mem_info->type, "ST_SMBIOS_MEMDEV_TYPES";
					StrPrintFlags(buffer, Define("ST_SMBIOS_MEMDEV_TYPE_DETAILS"), mem_info->type_detail, show_all_flags, 16);
					str = SysRepFlagsMake(buffer);
					"$$TR,\"Type Flags\"$$%s$$FG$$\n", str;
					Free(str);
					"$$ID,-3$$";
					break;
				case SMBIOSt_BASEBOARD:
					CSMBIOSBaseboardInfo *b_info = header;
					"$$TR-C,\"Baseboard\"$$\n";
					"$$ID,3$$";
					"Manufacturer\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->manufacturer);
					"Product\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->product);
					"Version\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->version);
					"Type\t\t\t\t:$$BLACK$$%Z$$FG$$\n",  b_info->board_type, "ST_SMBIOS_BASEBOARD_TYPES";
					"Location\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->chassis_location, "Not Specified");
					"Serial Number\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->serial_number);
					"Asset Tag\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->asset_tag);
					"$$TR,\"Flags\"$$";
					StrPrintFlags(buffer, Define("ST_SMBIOS_BASEBOARD_FLAGS"), b_info->feature_flags, show_all_flags, 5);
					str = SysRepFlagsMake(buffer);
					"%s$$FG$$\n", str;
					Free(str);
					"$$ID,-3$$";
					break;
				case SMBIOSt_CONNECTOR:
					CSMBIOSConnectorInfo *con_info = header;
					"$$TR,\"Port Connector\"$$\n";
					"$$ID,3$$";
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
					"$$ID,-3$$";
					break;
				case SMBIOSt_BATTERY:
					CSMBIOSBatteryInfo *bat_info = header;
					"$$TR,\"Battery\"$$\n";
					"$$ID,3$$";
					"Name\t\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, bat_info->name);
					"Manufacturer\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, bat_info->manufacturer);
					"$MA-X+PU,"SBDS",LM="\"\dGREEN\dS\dFG\dmart \dGREEN\dB\dFG\dattery \dGREEN\dD\dFG\data \dGREEN\dS\dFG\dpecification\n\";View;"$ Version\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, bat_info->manufacturer);
					"Manufacture Date\t:$$BLACK$$";
					if (bat_info->manufacture_date)
						"%s$$FG$$\n", SMBIOSStr(header, bat_info->manufacture_date);
					else
						"%s$$FG$$\n", SMBIOSStr(header, bat_info->sbds_manufacture_date);
					"Chemistry\t\t:$$BLACK$$";
					if (bat_info->chemistry)
						"%s$$FG$$\n", SMBIOSStr(header, bat_info->chemistry);
					else
						"%s$$FG$$\n", SMBIOSStr(header, bat_info->sbds_chemistry);
					"Capacity\t\t\t:$$BLACK$$";
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
					"$$ID,-3$$";
					break;
				case SMBIOSt_OEM_STRINGS:
				case SMBIOSt_SYS_CONFIG_OPTIONS:
					if (header->type == SMBIOSt_OEM_STRINGS)	
						"$$TR,\"OEM Strings\"$$\n";
					else
						"$$TR,\"Sys Config Strings\"$$\n";
					"$$ID,3$$";
					str = *(header(U8 *) + sizeof(CSMBIOSHeader)); //using str to hold the string count
					for (i = 1; i <= str; i++)
						"\t\t\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, i);
					"$$ID,-3$$";
					break;
				case SMBIOSt_SLOT:
					CSMBIOSSlotInfo *slot_info = header;
					"$$TR,\"Slot\"$$\n";
					"$$ID,3$$";
					"Name\t\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, slot_info->name);
					"Type\t\t\t\t:$$BLACK$$";
					if (slot_info->type >= 0xA0)
						"%Z$$FG$$\n", slot_info->type - 0xA0, "ST_SMBIOS_SLOT_TYPES2";
					else
						"%Z$$FG$$\n", slot_info->type, "ST_SMBIOS_SLOT_TYPES1";
					"Data Bus Width\t:$$BLACK$$%Z$$FG$$\n", slot_info->data_bus_width, "ST_SMBIOS_SLOT_DATA_BUS_WIDTHS";
					"Current Usage\t:$$BLACK$$%z$$FG$$\n", slot_info->current_usage, " \0Other\0Unknown\0Available\0In Use\0Unavailable";
					"Slot Length\t\t:$$BLACK$$%z$$FG$$\n", slot_info->length, " \0Other\0Unknown\0Short\0Long\02.5\" Drive Form Factor\03.5\" Drive Form Factor";
					"Segment Group\t:$$BLACK$$";
					if (slot_info->segment_group_number != 0xFF)
						"%d$$FG$$\n", slot_info->segment_group_number;
					else
						"None$$FG$$\n";
					"Bus\t\t\t\t:$$BLACK$$";
					if (slot_info->bus_number != 0xFF)
						"%d$$FG$$\n", slot_info->bus_number;
					else
						"None$$FG$$\n";

					if (slot_info->device_function_number != 0xFF)
					{
						"Device\t\t\t:$$BLACK$$%d$$FG$$\n", slot_info->device_function_number >> 3;
						"Function\t\t\t:$$BLACK$$%d$$FG$$\n", slot_info->device_function_number & 7;
					}
					else
						"Device\t\t\t:$$BLACK$$None$$FG$$\nFunction\t\t\t:$$BLACK$$None$$FG$$\n";
					"$$TR,\"Flags\"$$";
					if (!Bt(&slot_info->flags1, 0))
					{
						StrPrintFlags(buffer, Define("ST_SMBIOS_SLOT_FLAGS1"), slot_info->flags1, show_all_flags, 8);
						CatPrint(buffer, StrPrintFlags(buffer2, Define("ST_SMBIOS_SLOT_FLAGS2"), slot_info->flags2, show_all_flags, 4));
						str = SysRepFlagsMake(buffer);
						"%s$$FG$$\n", str;
						Free(str);
					}
					"$$ID,-3$$";
					break;
				case 28:
					"$$TR,\"Temperature Probe\"$$\n";
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
