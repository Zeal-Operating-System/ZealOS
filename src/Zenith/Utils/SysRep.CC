//SMBIOS parsing.
//Based on SMBIOS specification 3.3.0 (document "DSP0134")
U0 SMBIOSInit()
{
	//Section 7.1.1 line 925 (BIOS characteristics)
	DefineListLoad("ST_SMBIOS_BIOS_FLAGS",

		" \0"
		" \0"
		" \0"
		" \0"
		"ISA\0"
		"MCA\0"
		"EISA\0"
		"PCI\0"
		"PC Card\0"
		"Plug and Play\0"
		"APM\0"
		"Flashable BIOS\0"
		"BIOS shadowing\0"
		"VESA Local Bus\0"
		"ESCD\0"
		"CD Boot\0"
		"Selectable boot\0"
		"BIOS ROM socketed\0"
		"PC Card Boot\0"
		"Enhanced Disk Drive Services\0"
		" \0"
		" \0"
		"INT 0x13 5.25\"/360 KB Floppy Support\0"
		"INT 0x13 5.25\"/1.2 MB Floppy Support\0"
		"INT 0x13 3.5\"/720 KB Floppy Support\0"
		"INT 0x13 3.5\"/2.88 MB Floppy Support\0"
		"INT 0x05 Screen Printing\0"
		"INT 0x09 8042 Keyboard\0"
		"INT 0x14 Serial\0"
		"INT 0x17 Printer\0"
		"INT 0x10 CGA/Mono Video");

	//Section 7.1.2.1 line 931 (BIOS characteristics extension byte 1)
	DefineListLoad("ST_SMBIOS_BIOS_FLAGSEXT1",

		"ACPI\0"
		"USB Legacy\0"
		" \0"
		" \0"
		" \0"
		" \0"
		"Serial Boot\0"
		"Smart Battery"); 

	//Section 7.1.2.2 line 935 (BIOS characteristics extension byte 2)
	DefineListLoad("ST_SMBIOS_BIOS_FLAGSEXT2",

		"BIOS Boot\0"
		"Network Boot\0"
		"Targeted Content Distribution\0"
		"UEFI\0"
		"Virtual Machine");

	//Section 7.2.2 line 959 (system wakeup types)
	DefineListLoad("ST_SMBIOS_WAKEUP_TYPES",

		" \0"
		"Other\0"
		"Unknown\0"
		"APM Timer\0"
		"Modem Ring\0"
		"LAN Remote\0"
		"Power Switch\0"
		"PCI PME#\0"
		"AC Power Restored");

	//Section 7.3.1 line 972 (baseboard feature flags)
	DefineListLoad("ST_SMBIOS_BASEBOARD_FLAGS",

		"Hosting Board (Motherboard)\0"
		"Requires Auxilary Board\0"
		"Removable\0"
		"Replaceable\0"
		"Hot Swappable");

	//Section 7.3.2 line 977 (baseboard board types)
	DefineListLoad("ST_SMBIOS_BASEBOARD_TYPES",

		" \0"
		"Unknown\0"
		"Other\0"
		"Server Blade\0"
		"Connectivity Switch\0"
		"System Management Module\0"
		"Processor Module\0"
		"I/O Module\0"
		"Daughterboard\0"
		"Motherboard\0"
		"Processor/Memory Module\0"
		"Processor/IO Module\0"
		"Interconnect Board\0");

	//Section 7.4.1 line 988 (system enclosure types)
	DefineListLoad("ST_SMBIOS_ENCLOSURE_TYPES",

		" \0"
		"Other\0"
		"Unknown\0"
		"Desktop\0"
		"Low Profile Desktop\0"
		"Pizza Box\0"
		"Mini Tower\0"
		"Tower\0"
		"Portable\0"
		"Laptop\0"
		"Notebook\0"
		"Hand Held\0"
		"Docking Station\0"
		"All-in-One\0"
		"Sub Notebook\0"
		"Space-saving\0"
		"Lunch box\0"
		"Main Server Chassis\0"
		"Expansion Chassis\0"
		"SubChassis\0"
		"Bus Expansion Chassis\0"
		"Peripheral Chassis\0"
		"RAID Chassis\0"
		"Rack Mount Chassis\0"
		"Sealed-case PC\0"
		"Multi-system Chassis\0"
		"Compact PCI\0"
		"Advanced TCA\0"
		"Blade\0"
		"Blade Enclosure\0"
		"Tablet\0"
		"Convertible\0"
		"Detachable\0"
		"IoT Gateway\0"
		"Embedded PC\0"
		"Mini PC\0"
		"Stick PC");

	//Section 7.4.2 line 991 (enclosure states)
	DefineListLoad("ST_SMBIOS_ENCLOSURE_STATES",

		" \0"
		"Other\0"
		"Unknown\0"
		"Safe\0"
		"Warning\0"
		"Critical\0"
		"Non-Recoverable");

	//Section 7.4.3 line 994 (enclosure security status field)
	DefineListLoad("ST_SMBIOS_ENCLOSURE_SECURITY_STATUSES",

		" \0"
		"Other\0"
		"Unknown\0"
		"None\0"
		"External Interface Locked Out\0"
		"External Interface Enabled");

	//Section 7.5.1 line 1014 (processor type field)
	DefineListLoad("ST_SMBIOS_PROCESSOR_TYPES",

		" \0"
		"Other\0"
		"Unknown\0"
		"Central Processor\0"
		"Math Processor\0"
		"DSP Processor\0"
		"Video Processor");
	//Section 7.5.4 line 1050 (processor voltage field)

	DefineListLoad("ST_SMBIOS_PROCESSOR_VOLTAGE_LEVELS",

		"5V\0"
		"3.3V\0"
		"2.9V");

	DefineListLoad("ST_CPUID_1_EDX_FLAGS",

		"x87 FPU\0"
		"Virtual 8086 Mode Enhancements\0"
		"Debugging Extensions\0"
		"Page Size Extensions\0"
		"Time Stamp Counter\0"
		"MSRs\0"
		"Page Address Extension\0"
		"Machine Check Exceptions\0"
		"CMPXCHG8B\0"
		"APIC\0"
		" \0"
		"SYSENTER/SYSEXIT\0"
		"Memory Type Range Registers\0"
		"Page Global Bit\0"
		"Machine Check Architecture\0"
		"CMOV Instructions\0"
		"Page Attribute Table\0"
		"36 Bit Page Size Extension\0"
		"Processor Serial Number\0"
		"CLFLUSH\0"
		" \0"
		"Debug Store\0"
		"ACPI\0"
		"MMX\0"
		"FXSAVE/FXRSTOR\0"
		"SSE\0"
		"SSE2\0"
		"Self Snoop\0"
		"HTT\0"
		"Thermal Monitor\0"
		" \0"
		"Pending Break Enable\0");

	DefineListLoad("ST_CPUID_1_ECX_FLAGS",

		"SSE3\0"
		"PCLMULQDQ\0"
		"64 bit DS AREA\0"
		"MONITOR/MWAIT\0"
		"CPL Qualified Debug Store\0"
		"Virtual Machine Extensions\0"
		"Safer Mode Extensions\0"
		" \0"
		"Thermal Monitor 2\0"
		"SSSE3\0"
		"L1 Context ID\0"
		"IA32_DEBUG_INTERFACE\0"
		"FMA Extensions\0"
		"CMPXCHG16B\0"
		"xTPR Update Control\0"
		"Perfmon and Debug Capability\0"
		" \0"
		"Process Context Identifiers\0"
		"MMIO Prefetch\0"
		"SSE4.1\0"
		"SSE4.2\0"
		"x2APIC\0"
		"MOVBE\0"
		"POPCNT\0"
		"TSC Deadline\0"
		"AESNI\0"
		"XSAVE\0"
		"OSXSAVE\0"
		"AVX\0"
		"F16C\0"
		"RDRAND");

	//Section 7.5.5 line 1058 (upgrade field)
	DefineListLoad("ST_SMBIOS_PROCESSOR_UPGRADES",

		" \0"
		"Other\0"
		"Unknown\0"
		"Daughterboard\0"
		"ZIF Socket\0"
		"Replacable Piggy Back\0"
		"None\0"
		"LIF Socket\0"
		"Slot 1\0"
		"Slot2\0"
		"370-pin Socket\0"
		"Slot A\0"
		"Slot M\0"
		"Socket 423\0"
		"Socket A (Socket 462)\0"
		"Socket 478\0"
		"754\0"
		"940\0"
		"939\0"
		"mPGA604\0"
		"LGA771\0"
		"LGA775\0"
		"S1\0"
		"AM2\0"
		"F (1207)\0"
		"LGA1366\0"
		"G34\0"
		"AM3\0"
		"C32\0"
		"LGA1156\0"
		"LGA1567\0"
		"PGA988A\0"
		"BGA1288\0"
		"rPGA988B\0"
		"BGA1023\0"
		"BGA1224\0"
		"LGA1155\0"
		"LGA1356\0"
		"LGA2011\0"
		"FS1\0"
		"FS2\0"
		"FM1\FM2\0"
		"LGA2011-3\0"
		"LGA1356-3\0"
		"LGA1150\0"
		"BGA1168\0"
		"BGA1234\BGA1364\0"
		"AM4\0"
		"LGA1151\0"
		"BGA1440\0"
		"BGA1515\0"
		"LGA3647-1\0"
		"SP3\0"
		"SP3r2\0"
		"LGA2066\0"
		"BGA1932\0"
		"BGA1510\0"
		"BGA1528");

	//Section 7.5.9 line 1110 (processor characteristics)
	DefineListLoad("ST_SMBIOS_PROCESSOR_FLAGS",

		" \0"
		" \0"
		"64 Bit\0"
		"Multicore\0"
		"HyperThreading\0"
		"NX/XD Protection\0"
		"Enhanced Virtualization\0"
		"Power/Performance Control\0"
		"128 Bit Capable");

	//Section 7.8.2 line 1178 (cache information SRAM type field)
	DefineListLoad("ST_SMBIOS_CACHE_SRAM_TYPES",

		"Other\0"
		"Unknown\0"
		"Non-Burst\0"
		"Burst\0"
		"Pipeline Burst\0"
		"Synchronous\0"
		"Asynchronous");

	//Section 7.8.6 line 1193 (cache information associativity field)
	DefineListLoad("ST_SMBIOS_CACHE_ASSOCIATIVITY",

		" \0"
		"Other\0"
		"Unknown\0"
		"Direct Mapped\0"
		"2-way Set-Associative\0"
		"4-way Set-Associative\0"
		"Fully Associative\0"
		"8-way Set-Associative\0"
		"16-way Set-Associative\0"
		"12-way Set-Associative\0"
		"24-way Set-Associative\0"
		"32-way Set-Associative\0"
		"48-way Set-Associative\0"
		"64-way Set-Associative\0"
		"20-way Set-Associative");

	//Section 7.9.2 line 1219 (connector type field)
	DefineListLoad("ST_SMBIOS_CONNECTOR_TYPES",

		"None\0"
		"Centronics\0"
		"Mini Centronics\0"
		"Proprietary\0"
		"DB-25 Pin Male\0"
		"DB-25 Pin Female\0"
		"DB-15 Pin Male\0"
		"DB-15 Pin Female\0"
		"DB-9 Pin Male\0"
		"DB-9 Pin Female\0"
		"RJ-11\0"
		"RJ-45\0"
		"50-Pin MiniSCSI\0"
		"Mini-DIN\0"
		"Micro-DIN\0"
		"PS/2\0"
		"Infrared\0"
		"HP-HIL\0"
		"Access Bus (USB)\0"
		"SSA SCSI\0"
		"Circular DIN-8 Male\0"
		"Circular DIN-8 Female\0"
		"Onboard IDE\0"
		"Onboard Floppy\0"
		"9-Pin Dual Inline (Pin 10 Cut)\0"
		"25-Pin Dual Inline (Pin 26 Cut)\0"
		"50-Pin Dual Inline\0"
		"68-Pin Dual Inline\0"
		"Onboard CD-ROM Sound Input\0"
		"Mini-Centronics Type-14\0"
		"Mini-Centronics Type-26\0"
		"Mini-Jack (Headphones)\0"
		"BNC\0"
		"1394\0"
		"SAS\SATA Plug\0"
		"USB Type-C");

	//Section 7.9.3 line 1222 (port type field)
	DefineListLoad("ST_SMBIOS_PORT_TYPES",

		"None\0"
		"Parallel Port XT/AT Compatible\0"
		"Parallel Port PS/2\0"
		"Parallel Port ECP\0"
		"Parallel Port EPP\0"
		"Parallel Port ECP/EPP\0"
		"Serial Port XT/AT Compatible\0"
		"Serial Port 16450 Compatible\0"
		"Serial Port 16550 Compatible\0"
		"Serial Port 16550A Compatible\0"
		"SCSI Port\0"
		"MIDI Port\0"
		"Joystick Port\0"
		"Keyboard Port\0"
		"Mouse Port\0"
		"SSA SCSI\0"
		"USB\0"
		"FireWire (IEEE 1394)\0"
		"PCMCIA Type I\0"
		"PCMCIA Type II\0"
		"PCMCIA Type III\0"
		"Cardbus\0"
		"Access Bus Port\0"
		"SCSI II\0"
		"SCSI Wide\0"
		" \0"
		" \0"
		" \0"
		"Video Port\0"
		"Audio Port\0"
		"Modem Port\0"
		"Network Port\0"
		"SATA\0"
		"SAS\0"
		"MFDP (Multi-Function Display Port\0"
		"Thunderbolt\0"
		"8251 Compatible\0"
		"8251 FIFO Compatible");

	//Section 7.10.1 line 1229 (slot type)
	DefineListLoad("ST_SMBIOS_SLOT_TYPES1",

		" \0"
		"Other\0"
		"Unknown\0"
		"ISA\0"
		"MCA\0"
		"EISA\0"
		"PCI\0"
		"PC Card (PCMCIA)\0"
		"VESA Local Bus\0"
		"Proprietary\0"
		"Proprietary Card Slot\0"
		"Proprietary Memory Card Slot\0"
		"I/O Riser Card Slot\0"
		"NuBus\0"
		"PCI - 66 MHz Capable\0"
		"AGP\0"
		"AGP 2X\0"
		"AGP 4X\0"
		"PCI-X\0"
		"AGP 8X\0"
		"M.2 Socket 1-DP (Mechanical Key A)\0"
		"M.2 Socket 1-SD (Mechanical Key E)\0"
		"M.2 Socket 2 (Mechanical Key B)\0"
		"M.2 Socket 3 (Mechanical Key M)\0"
		"MXM Type I\0"
		"MXM Type II\0"
		"MXM Type III (Standard Connector)\0"
		"MXM Type III (HE Connector)\0"
		"MXM Type IV\0"
		"MXM 3.0 Type A\0"
		"MXM 3.0 Type B\0"
		"PCI Express Gen 2 SFF-8639\0"
		"PCI Express Gen 3 SFF-8639\0"
		"PCI Express Mini 52-Pin with bottom-side keep-outs\0"
		"PCI Express Mini 52-Pin without bottom-side keep-outs\0"
		"PCI Express Mini 76-Pin\0"
		"CXL Flexbus 1.0");

	DefineListLoad("ST_SMBIOS_SLOT_TYPES2",

		" \0"
		" \0"
		" \0"
		" \0"
		" \0"
		"PCI Express\0"
		"PCI Express 1x\0"
		"PCI Express 2x\0"
		"PCI Express 4x\0"
		"PCI Express 8x\0"
		"PCI Express 16x\0"
		"PCI Express Gen 2\0"
		"PCI Express Gen 2 1x\0"
		"PCI Express Gen 2 2x\0"
		"PCI Express Gen 2 4x\0"
		"PCI Express Gen 2 8x\0"
		"PCI Express Gen 2 16x\0"
		"PCI Express Gen 3\0"
		"PCI Express Gen 3 1x\0"
		"PCI Express Gen 3 2x\0"
		"PCI Express Gen 3 4x\0"
		"PCI Express Gen 3 8x\0"
		"PCI Express Gen 3 16x\0"
		"PCI Express Gen 4\0"
		"PCI Express Gen 4 1x\0"
		"PCI Express Gen 4 2x\0"
		"PCI Express Gen 4 4x\0"
		"PCI Express Gen 4 8x\0"
		"PCI Express Gen 4 16x");

	//Section 7.10.2 line 1244 (slot data bus width field)
	DefineListLoad("ST_SMBIOS_SLOT_DATA_BUS_WIDTHS",

		" \0"
		"Other\0"
		"Unknown\0"
		"8 Bit\0"
		"16 Bit\0"
		"32 Bit\0"
		"64 Bit\0"
		"128 Bit\0"
		"1x\0"
		"2x\0"
		"4x\0"
		"8x\0"
		"12x\0"
		"16x\0"
		"32x");

	//Section 7.10.6 line 1259 (slot characteristics 1 field)
	DefineListLoad("ST_SMBIOS_SLOT_FLAGS1",

		" \0"
		"5.0 V\0"
		"3.3 V\0"
		"Shared Slot Opening\0"
		"PC Card 16\0"
		"CardBus\0"
		"Zoom Video\0"
		"Modem Ring Resume");

	//Section 7.10.7 line 1262 (slot characteristics 2 field)
	DefineListLoad("ST_SMBIOS_SLOT_FLAGS2",

		"PCI Power Management Event (PME#) Signal\0"
		"HotPlug\0"
		"SMBus\0"
		"Bifurcation");

	//Section 7.17.1 line 1523 (memory array location field)
	DefineListLoad("ST_SMBIOS_PHYMEM_LOCATIONS",

		" \0"
		"Other\0"
		"Unknown\0"
		"Motherboard\0"
		"ISA Add-On Card\0"
		"EISA Add-On Card\0"
		"PCI Add-On Card\0"
		"MCA Add-On Card\0"
		"PCMCIA Add-On Card\0"
		"Proprietary Add-On Card\0"
		"NuBus\0"
		" \0"
		" \0"
		" \0"
		" \0"
		" \0");

	//Section 7.17.2 line 1527 (memory array use field)
	DefineListLoad("ST_SMBIOS_PHYMEM_USES",

		" \0"
		"Other\0"
		"Unknown\0"
		"System Memory\0"
		"Video Memory\0"
		"Flash Memory\0"
		"Non-Volatile RAM\0"
		"Cache Memory");

	//Section 7.18.1 line 1542 (form factor field)
	DefineListLoad("ST_SMBIOS_MEMDEV_FORM_FACTORS",

		" \0"
		"Other\0"
		"Unknown\0"
		"SIMM\0"
		"SIP\0"
		"DIP\0"
		"ZIP\0"
		"Proprietary Card\0"
		"DIMM\0"
		"TSOP\0"
		"Row of Chips\0"
		"RIMM\0"
		"SODIMM\0"
		"SRIMM\0"
		"FB-DIMM\0"
		"Die");

	//Section 7.18.2 line 1546 (type field)
	DefineListLoad("ST_SMBIOS_MEMDEV_TYPES",

		" \0"
		"Unknown\0"
		"DRAM\0"
		"EDRAM\0"
		"VRAM\0"
		"SRAM\0"
		"RAM\0"
		"ROM\0"
		"FLASH\0"
		"EEPROM\0"
		"FEPROM\0"
		"EPROM\0"
		"CDRAM\0"
		"3DRAM\0"
		"SDRAM\0"
		"SGRAM\0"
		"RDRAM\0"
		"DDR\0"
		"DDR2\0"
		"DDR2 FB-DIMM\0"
		" \0"
		" \0"
		" \0"
		"DDR3\0"
		"FBD2\0"
		"DDR4\0"
		"LPDDR\0"
		"LPDDR2\0"
		"LPDDR3\0"
		"LPDDR4\0"
		"Logical Non-Volatile Device\0"
		"HBM (High Bandwidth Memory)\0"
		"HBM2 (High Bandwidth Memory Gen 2)");

	//Section 7.18.3 line 1550 (type detail field)
	DefineListLoad("ST_SMBIOS_MEMDEV_TYPE_DETAILS",

		" \0"
		" \0"
		" \0"
		"Fast Paged\0"
		"Static Column\0"
		"Psuedo Static\0"
		"RAMBUS\0"
		"Synchronous\0"
		"CMOS\0"
		"EDO\0"
		"Window DRAM\0"
		"Cache DRAM\0"
		"Non Volatile\0"
		"Registered (Buffered)\0"
		"Unregistered (Unbuffered)\0"
		"LRDIMM");
} SMBIOSInit;

Bool SMBIOSEntryScan(CSMBIOSEntryPoint **entry)
{//Search 0xF0000 - 0x100000 for SMBIOS Entry Point structure.
	I64		 i;
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
	}
	while ((mem += 16) < 0x100000); //anchor sits on 16-byte boundary

	return mem != 0x100000;
}

U8 *SMBIOSStr(CSMBIOSHeader *header, I64 str_num, U8 *default="None")
{//Get string str_num from end of structure (string section).
	I64 i;
	U8* ptr = header(U8 *) + header->length;

	if (!str_num)
		return default;

	for (i = 1; i < str_num; i++)
	{
		while (*ptr++);
		if (!ptr[0] && !ptr[1])  //structure ends in double NULL
			return default;
	}

	return ptr;
}

CSMBIOSHeader *SMBIOSStructGet(I64 type=0xFFFFF, I64 handle=0xFFFFF, CSMBIOSHeader *head=NULL)
{//Search for struct with type or handle. Return NULL if not found.
	I64					 i;
	CSMBIOSEntryPoint	*entry;

	if (!head)
	{
		if (!SMBIOSEntryScan(&entry))
			return NULL;
		head = entry->table_address;
	}
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

public I64 SysRep(I64 type=SMBIOSt_ALL, I64 handle=0, Bool show_all_flags=FALSE, I64 memdev_handle=0xFFFF)
{//Display info of System Management BIOS (SMBIOS) structures.  Returns structure count of displayed structures.
	I64					 i = 1, structure_count = 0, cache_count = 0;
	CSMBIOSEntryPoint	*entry;
	CSMBIOSHeader		*header;
	U8					buffer[2048], buffer2[512], *str;

	if (!SMBIOSEntryScan(&entry))
	{
		"No SMBIOS data found.\n";
		return 0;
	}
	header = entry->table_address;

	if (!handle && type == 0xFF)
		"SMBIOS version %d.%d (%d entries)\n", entry->major_version, entry->minor_version, entry->structure_count;
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
					"$$FD,CYAN$$";
					"$$ID,3$$"
					"Vendor\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, bios_info->vendor);
					"Version\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, bios_info->version);
					"Release Date\t\t:$$BLACK$$%s (mm/dd/yyyy)$$FG$$\n", SMBIOSStr(header, bios_info->release_date);
					"Release Version\t:$$BLACK$$%d.%d$$FG$$\n", bios_info->major_release, bios_info->minor_release;
					"Start Address\t:$$BLACK$$0x%X$$FG$$\n", Seg2Linear(&start_addr);
					"Image Size\t\t:$$BLACK$$%d bytes$$FG$$\n", (0x10000 - bios_info->start_address_segment) * 16;
					"ROM Size\t\t\t:$$BLACK$$";
					if (bios_info->rom_size == 0xFF)
						"%d %ziB$$FG$$\n", bios_info->extended_rom_size & ~0xC000, Bt(&bios_info->extended_rom_size, 14), "M\0G";
					else
						"%d KiB$$FG$$\n", (bios_info->rom_size + 1) * 64;
					if (Bt(&bios_info->flags, 3))
						"Flags Not Supported$$FG$$\n";
					else 
					{
						"$$TR,\"Flags\"$$";
						FlagsStrPrint(buffer, Define("ST_SMBIOS_BIOS_FLAGS"), bios_info->flags & ~0xF, show_all_flags, 31);
						CatPrint(buffer, FlagsStrPrint(buffer2, Define("ST_SMBIOS_BIOS_FLAGSEXT1"), bios_info->extended_flags[0], show_all_flags, 8));
						CatPrint(buffer, FlagsStrPrint(buffer2, Define("ST_SMBIOS_BIOS_FLAGSEXT2"), bios_info->extended_flags[1], show_all_flags, 5));
						str = SysRepFlagsMake(buffer);
						"%s$$FG$$\n", str; 
						Free(str);
					}
					"$$ID,-3$$";
					break;

				case SMBIOSt_SYSTEM:
					CSMBIOSSystemInfo *sys_info = header;
					"$$TR-C,\"System\"$$\n";
					"$$FD,CYAN$$";
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
					"$$FD,CYAN$$";
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
					"$$FD,CYAN$$";
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
						
					FlagsStrPrint(buffer, Define("ST_SMBIOS_PROCESSOR_FLAGS"), p_info->characteristics, show_all_flags, 9);
					str = SysRepFlagsMake(buffer);
					"$$TR,\"Processor Flags\"$$%s$$FG$$\n", str;
					FlagsStrPrint(buffer, Define("ST_CPUID_1_EDX_FLAGS"), regs.rdx, show_all_flags, 32);
					CatPrint(buffer, FlagsStrPrint(buffer2, Define("ST_CPUID_1_ECX_FLAGS"), regs.rcx, show_all_flags, 31));
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
					"$$FD,CYAN$$";
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
					FlagsStrPrint(buffer, Define("ST_SMBIOS_CACHE_SRAM_TYPES"), c_info->supported_sram_type);
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
					"$$FD,CYAN$$";
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
					"$$FD,CYAN$$";
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
					FlagsStrPrint(buffer, Define("ST_SMBIOS_MEMDEV_TYPE_DETAILS"), mem_info->type_detail, show_all_flags, 16);
					str = SysRepFlagsMake(buffer);
					"$$TR,\"Type Flags\"$$%s$$FG$$\n", str;
					Free(str);
					"$$ID,-3$$";
					break;

				case SMBIOSt_BASEBOARD:
					CSMBIOSBaseboardInfo *b_info = header;
					"$$TR-C,\"Baseboard\"$$\n";
					"$$FD,CYAN$$";
					"$$ID,3$$";
					"Manufacturer\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->manufacturer);
					"Product\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->product);
					"Version\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->version);
					"Type\t\t\t\t:$$BLACK$$%Z$$FG$$\n",  b_info->board_type, "ST_SMBIOS_BASEBOARD_TYPES";
					"Location\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->chassis_location, "Not Specified");
					"Serial Number\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->serial_number);
					"Asset Tag\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, b_info->asset_tag);
					"$$TR,\"Flags\"$$";
					FlagsStrPrint(buffer, Define("ST_SMBIOS_BASEBOARD_FLAGS"), b_info->feature_flags, show_all_flags, 5);
					str = SysRepFlagsMake(buffer);
					"%s$$FG$$\n", str;
					Free(str);
					"$$ID,-3$$";
					break;

				case SMBIOSt_CONNECTOR:
					CSMBIOSConnectorInfo *con_info = header;
					"$$TR,\"Port Connector\"$$\n";
					"$$FD,CYAN$$";
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
					"$$FD,CYAN$$";
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
					"$$FD,CYAN$$";
					"$$ID,3$$";
					str = *(header(U8 *) + sizeof(CSMBIOSHeader)); //using str to hold the string count
					for (i = 1; i <= str; i++)
						"\t\t\t\t\t:$$BLACK$$%s$$FG$$\n", SMBIOSStr(header, i);
					"$$ID,-3$$";
					break;

				case SMBIOSt_SLOT:
					CSMBIOSSlotInfo *slot_info = header;
					"$$TR,\"Slot\"$$\n";
					"$$FD,CYAN$$";
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
						FlagsStrPrint(buffer, Define("ST_SMBIOS_SLOT_FLAGS1"), slot_info->flags1, show_all_flags, 8);
						CatPrint(buffer, FlagsStrPrint(buffer2, Define("ST_SMBIOS_SLOT_FLAGS2"), slot_info->flags2, show_all_flags, 4));
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

public U0 BIOSRep()
{//Wrapper around $LK,"SysRep",A="MN:SysRep"$() to only show BIOS info.
	SysRep(SMBIOSt_BIOS);
}
