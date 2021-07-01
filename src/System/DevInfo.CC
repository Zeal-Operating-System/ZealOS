#help_index "PCI;Processor;Devices;Info"

//The file was downloaded from
//http://www.pcidatabase.com/reports.php?type=tab-delimeted

#define PCI_DEV_FILE "::/Misc/PCIDevices.DD"

/****
//1) Download http://www.pcidatabase.com/reports.php?type=tab-delimeted
//2) Rename to ::/Misc/PCIDevices.DD
//3) ToDolDoc("::/Misc/PCIDevices.DD");
//4) Edit and remove file header and tail
//5) Text find-and-replace "=0A=" with "". (Doesn't seem necessary anmore.)
//6) Run PCIDevFileGen(). (Doesn't seem necessary anmore.)

public U0 PCIDevFileGen()
{
	Bool first=TRUE,del=FALSE,del2=FALSE,cont=FALSE;
	CDoc *doc=DocRead(PCI_DEV_FILE,
				DOCF_PLAIN_TEXT|DOCF_DBL_DOLLARS|DOCF_NO_CURSOR);
	CDocEntry *doc_e=doc->head.next,*doc_e2;
	while (doc_e!=doc) {
		doc_e2=doc_e->next;
		if (first) {
			if (doc_e->type_u8==DOCT_TEXT) {
				if (doc_e->tag[0]==';')
					del=TRUE;
			}
			first=FALSE;
		}
		if (doc_e->type_u8==DOCT_TEXT && doc_e->tag[StrLen(doc_e->tag)-1]=='=' &&
					doc_e2->type_u8==DOCT_NEW_LINE) {
			doc_e->tag[StrLen(doc_e->tag)-1]=CH_SPACE;
			cont=TRUE;
		}
		del2=del;
		if (doc_e->type_u8==DOCT_NEW_LINE) {
			first=TRUE;
			del2=FALSE;
			if (cont) {
				del=TRUE;
				cont=FALSE;
			}
		}
		if (del)
			DocEntryDel(doc,doc_e);
		del=del2;
		doc_e=doc_e2;
	}
	DocWrite(doc);
}
****/

//$LK,"::/Misc/PCIDevices.DD",A="PI:::/Misc/PCIDevices.DD"$
U0 PCILookUpSingle(CDoc *doc, I64 m, I64 d, U8 **_vendor, U8 **_dev)
{
	Bool		 first = TRUE;
	U8			 buf[8], *vendor = NULL, *dev = NULL;
	CDocEntry	*doc_e = doc->head.next;

	while (doc_e != doc)
	{
		if (first)
		{
			if (doc_e->type_u8 == DOCT_TEXT && doc_e->tag[0] != ';' && StrLen(doc_e->tag) >= 4)
			{
				buf[0](U16) = '0x';
				buf[2](U32) = doc_e->tag(U32 *)[0];
				buf[6] = '\0';
				if (Str2I64(buf) == m)
				{
					doc_e = doc_e->next->next->next;
					if (doc_e->type_u8 == DOCT_TEXT)
					{
						vendor = ZStrNew(doc_e->tag);
						first = FALSE;
						break;
					}
				}
			}
			first=FALSE;
		}
		if (doc_e->type_u8 == DOCT_NEW_LINE)
			first = TRUE;
		doc_e = doc_e->next;
	}

	if (vendor)
	{
		while (doc_e != doc)
		{
			if (first)
			{
				if (doc_e->type_u8 == DOCT_TAB)
				{
					doc_e = doc_e->next->next->next->next;
					if (doc_e->type_u8 == DOCT_TEXT && StrLen(doc_e->tag) >= 4)
					{
						buf[0](U16) = '0x';
						buf[2](U32) = doc_e->tag(U32 *)[0];
						buf[6] = '\0';
						if (Str2I64(buf) == d)
						{
							doc_e = doc_e->next->next->next;
							if (doc_e->type_u8 == DOCT_TEXT)
							{
								dev = ZStrNew(doc_e->tag);
								break;
							}
						}
					}
				}
				else
					break;
				first = FALSE;
			}
			if (doc_e->type_u8 == DOCT_NEW_LINE)
				first = TRUE;
			doc_e = doc_e->next;
		}
	}

	if (vendor)
		*_vendor = vendor;
	else
		*_vendor = ZStrNew("Unknown");

	if (dev)
		*_dev = dev;
	else
		*_dev = ZStrNew("Unknown");
}

U0 PCILookUpDevs()
{
	CPCIDev	*tmppci;
	I64		 w1, w2, b, d, f, timeout = 32 * 8 * 2;
	CDoc	*doc;

	if (dev.pci_head.next != &dev.pci_head)
		return;
	doc = DocRead(PCI_DEV_FILE, DOCF_PLAIN_TEXT | DOCF_NO_CURSOR);
	for (b = 0; b < sys_pci_buses; b++)
		for (d = 0; d < 32; d++)
			for (f = 0; f < 8; f++)
			{
				w1 = PCIReadU16(b, d, f, PCIR_VENDOR_ID);
				if (w1 != 0xFFFF)
				{
					tmppci = ZCAlloc(sizeof(CPCIDev));
					tmppci->bus = b;
					tmppci->dev = d;
					tmppci->fun = f;
					tmppci->vendor_id = w1;
					tmppci->device_id = w2 = PCIReadU16(b, d, f, PCIR_DEVICE_ID);
					tmppci->sub_code =		PCIReadU8(b, d, f, PCIR_SUB_CODE);
					tmppci->class_code =	PCIReadU8(b, d, f, PCIR_CLASS_CODE);
					tmppci->prog_if = 		PCIReadU8(b, d, f, PCIR_PROG_IF);
					tmppci->revision_id = PCIReadU8(b, d, f, PCIR_REVISION_ID);
					tmppci->bist =				PCIReadU8(b, d, f, PCIR_BIST);
					tmppci->header_type = PCIReadU8(b, d, f, PCIR_HEADER_TYPE);
					tmppci->latency_timer=PCIReadU8(b, d, f, PCIR_LATENCY_TIMER);
					tmppci->capabilities= PCIReadU8(b, d, f, PCIR_CAPABILITIES);
					tmppci->cache_line_size=PCIReadU8(b, d, f, PCIR_CACHE_LINE_SIZE);
					tmppci->subsys_id = 	PCIReadU16(b, d, f, PCIR_SUBSYS_ID);
					tmppci->subsys_vendor_id=PCIReadU16(b, d, f, PCIR_SUBSYS_VENDOR_ID);
					tmppci->erom =				PCIReadU32(b, d, f, PCIR_EXPANSION_ROM);
					tmppci->base[0] = 		PCIReadU32(b, d, f, PCIR_BASE0);
					tmppci->base[1] = 		PCIReadU32(b, d, f, PCIR_BASE1);
					tmppci->base[2] = 		PCIReadU32(b, d, f, PCIR_BASE2);
					tmppci->base[3] = 		PCIReadU32(b, d, f, PCIR_BASE3);
					tmppci->base[4] = 		PCIReadU32(b, d, f, PCIR_BASE4);
					tmppci->base[5] = 		PCIReadU32(b, d, f, PCIR_BASE5);
					PCILookUpSingle(doc, w1, w2, &tmppci->vendor_str, &tmppci->dev_id_str);
					QueueInsert(tmppci, dev.pci_head.last);
					timeout = 32 * 8 * 2;
				}
				else if (sys_pci_buses == 256 && --timeout <= 0)
					goto lud_done;
			}
lud_done:
	DocDel(doc);
}

public CPCIDev *PCIDevFind(U16 class_code=NULL, U16 sub_code=NULL,
												U16 vendor_id=NULL, U16 device_id=NULL,
												U8 _bus=0xFF, U8 _dev=0xFF, U8 _fun=0xFF)
{//return first device with matching class & subcode, vendor & device id, or a specific device.
	PCILookUpDevs;
	CPCIDev *p = dev.pci_head.next;

	while (p != &dev.pci_head)
	{
		if (p->vendor_id == vendor_id && p->device_id == device_id ||
				p->class_code == class_code && p->sub_code == sub_code ||
				p->bus == _bus && p->dev == _dev && p->fun == _fun)

			return p;
 
		p = p->next;
	}
	return NULL;
}

public U0 PCIRep()
{//Report description of PCI devices.
	CPCIDev *tmppci;

	"PCI Buses:%d\n", sys_pci_buses;
	if (!FileFind(PCI_DEV_FILE))
	{
		"You don't have the PCI device file.\n";
		return;
	}
	PCILookUpDevs;
	tmppci = dev.pci_head.next;
	while (tmppci != &dev.pci_head)
	{
		"%02X:%02X:%01X %02X-%02X-%02X $$GREEN$$%s $$CYAN$$%s$$FG$$\n",
					tmppci->bus, tmppci->dev, tmppci->fun,
					tmppci->class_code, tmppci->sub_code, tmppci->prog_if,
					tmppci->vendor_str, tmppci->dev_id_str;
		tmppci=tmppci->next;
	}
}

#help_index "Info;Memory/Info"
public U0 MemBIOSRep()
{//Report the memory ranges reported by the BIOS at boot.
	U16 		*m01 = MEM_E801;
	CMemE820	*m20 = MEM_E820;
	CMemRange	*tmpmr;

	"$$PURPLE$$Standard Addresses$$FG$$\n"
			"FEE00000-FEE00FFF See $LK,"APIC",A="MN:LAPIC_BASE"$\n\n"

	"$$PURPLE$$VBE Linear Framebuffer$$FG$$\n"
			"%08X-%08X  See $LK,"VBE Mode",A="FF:::/Kernel/KernelA.HH,framebuffer"$\n", text.fb_alias,
																																								text.fb_alias(U8 *) + text.buffer_size - 1;
	"\n$$PURPLE$$32 Bit Device Mem$$FG$$\n";
	while (LBts(&sys_semas[SEMA_DEV_MEM], 0))
		Yield;
	tmpmr = dev.mem32_head.next;
	while (tmpmr != &dev.mem32_head)
	{
		"%z:%08X-%08X\n", tmpmr->type, "Unused\0RAM\0Device", tmpmr->base, tmpmr->base + tmpmr->size - 1;
		tmpmr = tmpmr->next;
	}
	LBtr(&sys_semas[SEMA_DEV_MEM], 0);

	"\n$$PURPLE$$BIOS Memory Report 15:E801$$FG$$\n"
				"0000000000000000-%016X\n", 0x100000 + m01[0] * 1024 - 1;
				"0000000001000000-%016X\n", SYS_16MEG_AREA_LIMIT + m01[1] * 64 * 1024  - 1;

	if (m20->type)
	{
		"\n$$PURPLE$$BIOS Memory Report 15:E820$$FG$$\n";
		while (m20->type)
		{
			"$$RED$$";
			switch(m20->type)
			{
				case MEM_E820t_USABLE:
					"$$GREEN$$Usable     :";
					break;

				case MEM_E820t_ACPI:
				case MEM_E820t_ACPI_NVS:
					"ACPI       :";
					 break;

				case MEM_E820t_BAD_MEM:
					"Bad memory :";
					 break;

				case MEM_E820t_PERM_MEM:
					"Perm memory:";

				case MEM_E820t_RESERVED:
				default:
					"Reserved   :";
					break;
			 }
			"%016X-%016X$$FG$$\n", m20->base, m20->base + m20->len - 1;
			m20++;
		}
	}
	"\n$$PURPLE$$BIOS Total Memory Report$$FG$$: ";
	if (MemBIOSTotal < 1024 * 1024 * 1024)
		"%03d MiB\n", MemBIOSTotal / 1024 / 1024; 		
	else
		"%04d GiB\n", CeilU64(MemBIOSTotal / 1024 / 1024, 1024) / 1024;
}

public U0 MemPageRep()
{//Page Table Report.
	"MAPPED\t  :%010X with ", mem_mapped_space;
	if (Bt(&mem_page_size, 30))
		"$$RED$$1GIG$$FG$$ pages\n";
	else
		"$$RED$$2MEG$$FG$$ pages\n";
	"PML2\t  :%010X 2MEG  :%08X\n",
				*MEM_PML2(U64 *), *MEM_2MEG_NUM(U64 *);
	"PML3\t  :%010X 1GIG  :%08X\n",
				*MEM_PML3(U64 *), *MEM_1GIG_NUM(U64 *);
	"PML4\t  :%010X 512GIG:%08X\n",
				*MEM_PML4(U64 *), *MEM_512GIG_NUM(U64 *);
	"FIXED_AREA:%010X\n", SYS_FIXED_AREA;
	"HEAP_BASE :%010X\nHEAP_LIMIT:%010X\n", mem_heap_base, mem_heap_limit;
}
