//SMBIOS parsing.
//Based on SMBIOS specification 3.3.0 (document "DSP0134")

//Section 6.2 line 910 (required structures)
#define SMBIOSt_BIOS		0
#define SMBIOSt_SYSTEM		1
#define SMBIOSt_ENCLOSURE	3
#define SMBIOSt_PROCESSOR	4
#define SMBIOSt_CACHE		7
#define SMBIOSt_SLOTS		9
#define SMBIOSt_PHYMEM		16
#define SMBIOSt_MEM_DEVICE	17
#define SMBIOSt_MAPPED_ADDR	19
#define SMBIOSt_BOOT_INFO	32

//Section 7.1.1 line 925
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

//Section 7.1.2.1 line 931
#define SMBIOS_BIOSEXT1f_ACPI		0
#define SMBIOS_BIOSEXT1f_USB_LEGACY	1
#define SMBIOS_BIOSEXT1f_AGP		2

//Section 7.1.2.2 line 935
#define SMBIOS_BIOSEXT2f_BIOS_BOOT	0
#define SMBIOS_BIOSEXT2f_NET_BOOT	1
#define SMBIOS_BIOSEXT2f_UEFI		3
#define SMBIOS_BIOSEXT2f_VM			4

//Section 7.2.2 line 959
#define SMBIOS_WAKEUPt_OTHER		1
#define SMBIOS_WAKEUPt_UNKNOWN		2
#define SMBIOS_WAKEUPt_APM			3
#define SMBIOS_WAKEUPt_MODEM		4
#define SMBIOS_WAKEUPt_LAN			5
#define SMBIOS_WAKEUPt_POWER_SWITCH	6
#define SMBIOS_WAKEUPt_PCI			7
#define SMBIOS_WAKEUPt_AC_POWER		8

//Section 7.3.2 line 977
#define SMBIOS_BASEBOARDt_UNKNOWN				1
#define SMBIOS_BASEBOARDt_OTHER					2
#define SMBIOS_BASEBOARDt_SERVER_BLADE			3
#define SMBIOS_BASEBOARDt_CONNECTIVITY_SWITCH	4
#define SMBIOS_BASEBOARDt_SM_MODULE				5
#define SMBIOS_BASEBOARDt_PROCESSOR_MODULE		6
#define SMBIOS_BASEBOARDt_IO_MODULE				7
#define SMBIOS_BASEBOARDt_MEMORY_MODULE			8
#define SMBIOS_BASEBOARDt_DAUGHTERBOARD			9
#define SMBIOS_BASEBOARDt_MOTHERBOARD			10
#define SMBIOS_BASEBOARDt_PROCESSOR_MEMORY_MODULE	11
#define SMBIOS_BASEBOARDt_PROCESSOR_IO_MODULE	12
#define SMBIOS_BASEBOARDt_INTERCONNECT_BOARD	13

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
		bios_version;
	U16	bios_start_address_segment;
	U8	bios_release_date,
		bios_rom_size;
	U64	bios_flags;
	U8	extended_bios_flags[2];
	U8	bios_major_release,
		bios_minor_release,
		embedded_controller_firmware_major_release,
		embedded_controller_firmware_minor_release;
	U16	extended_bios_rom_size;
};

class CSMBIOSSystemInfo
{//Section 7.2 line 936
	CSMBIOSHeader header;
	U8	manufacturer,
		product_name,
		version,
		serial_number,
		uuid[16],
		wake_up_type,
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
{
	CSMBIOSHeader header;
	
};

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
	ClassRep(*entry,,,,TRUE);	
	return mem != 0x100000;
}


U8 *SMBIOSStringGet(CSMBIOSHeader *header, I64 str_num)
{
	if (!str_num) return NULL;

	I64 i;
	U8* ptr = header(U8 *) + header->length;

	for (i = 1; i < str_num; i++)
	{
		while (*ptr++);
		if (!ptr[0] && !ptr[1])  //structure ends in double NULL
		{
			return NULL;
		}
	}
	return ptr;
}

U0 SMBIOSInit()
{
	I64 i = 1;
	CSMBIOSEntryPoint *entry;
	U8 *header;

	if (!SMBIOSEntryScan(&entry))
		return;

	header = entry->table_address;

	while (header(CSMBIOSHeader *)->type != 127)
	{

		switch (header(CSMBIOSHeader *)->type)
		{
			case SMBIOSt_BIOS:
				ClassRep(header(CSMBIOSBIOSInfo *),,,,TRUE);
				break;
			case SMBIOSt_SYSTEM:
				CSMBIOSSystemInfo *info = header;
				ClassRep(info,,,,TRUE);
				"%s\n", SMBIOSStringGet(info, info->manufacturer);
				"%z\n", info->wake_up_type, " \0Other\0Unknown\0APM\0Modem\0LAN\0Power Switch\0PCI\0AC Power";
				break;
		}

		header += header(CSMBIOSHeader *)->length;
		for (i = 1; header[i - 1] || header[i]; i++);
		header += i + 1;
	}
}

SMBIOSInit;































