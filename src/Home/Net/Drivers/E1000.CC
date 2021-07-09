/*	Intel(R) E1000 Driver
	Author: TomAwezome

	Driver is based on:
	-	01000101's example i825xx driver
	-	OSDev Intel(R) 8254x documentation
	-	Intel(R) PCI/PCI-X Family of Gigabit Ethernet Controllers Software Developer's Manual
	-	Linux E1000 driver
	-	any other useful sources.

	Guidelines:
	-	Magic numbers are bad. #defines are good.
	-	Understandability over LOC.
	-	Clear documentation.
*/

// TODO: clean up entire driver

#define E1000_REG_CTRL	0x0000
#define E1000_REG_EERD	0x0014	// EEPROM Read
#define E1000_REG_IMS	0x00D0
#define E1000_REG_RCTL	0x0100
#define E1000_REG_TCTL	0x0400
#define E1000_REG_RDBAL	0x2800
#define E1000_REG_RDBAH	0x2804
#define E1000_REG_RDLEN	0x2808
#define E1000_REG_RDH	0x2810
#define E1000_REG_RDT	0x2818
#define E1000_REG_TDBAL	0x3800
#define E1000_REG_TDBAH	0x3804
#define E1000_REG_TDLEN	0x3808
#define E1000_REG_TDH	0x3810
#define E1000_REG_TDT	0x3818
#define E1000_REG_MTA	0x5200	// Multicast Table Array

#define E1000_CTRLf_SLU	6 // Set Link Up ?

#define E1000_CTRLF_SLU	(1 << E1000_CTRLf_SLU) // Set Link Up ?

#define E1000_RCTLf_EN				1
#define E1000_RCTLf_SBP				2
#define E1000_RCTLf_UPE				3
#define E1000_RCTLf_MPE				4
#define E1000_RCTLf_LPE				5
//#define E1000_RCTLf_RDMTS_HALF		
#define E1000_RCTLf_RDMTS_QUARTER	8
#define E1000_RCTLf_RDMTS_EIGHTH	9
#define E1000_RCTLf_BAM				15
#define E1000_RCTLf_BSIZE_1024		16
#define E1000_RCTLf_BSIZE_512		17
#define E1000_RCTLf_BSIZE_256		18
//#define E1000_RCTLf_BSIZE_2048		
//#define E1000_RCTLf_BSIZE_4096		
//#define E1000_RCTLf_BSIZE_8192		
//#define E1000_RCTLf_BSIZE_16384		
#define E1000_RCTLf_SECRC			26

#define E1000_RCTLF_EN				(1 << E1000_RCTLf_EN)
#define E1000_RCTLF_SBP				(1 << E1000_RCTLf_SBP)
#define E1000_RCTLF_UPE				(1 << E1000_RCTLf_UPE)
#define E1000_RCTLF_MPE				(1 << E1000_RCTLf_MPE)
#define E1000_RCTLF_LPE				(1 << E1000_RCTLf_LPE)
//#define E1000_RCTLF_RDMTS_HALF		
#define E1000_RCTLF_RDMTS_QUARTER	(1 << E1000_RCTLf_RDMTS_QUARTER)
#define E1000_RCTLF_RDMTS_EIGHTH	(2 << E1000_RCTLf_RDMTS_QUARTER)
#define E1000_RCTLF_BAM				(1 << E1000_RCTLf_BAM)
#define E1000_RCTLF_BSIZE_1024		(1 << E1000_RCTLf_BSIZE_1024)
#define E1000_RCTLF_BSIZE_512		(2 << E1000_RCTLf_BSIZE_1024)
#define E1000_RCTLF_BSIZE_256		(3 << E1000_RCTLf_BSIZE_1024)
//#define E1000_RCTLF_BSIZE_2048		
//#define E1000_RCTLF_BSIZE_4096		
//#define E1000_RCTLF_BSIZE_8192		
//#define E1000_RCTLF_BSIZE_16384		
#define E1000_RCTLF_SECRC			(1 << E1000_RCTLf_SECRC)

#define E1000_TCTLf_EN	1
#define E1000_TCTLf_PSP	3

#define E1000_TCTLF_EN	(1 << E1000_TCTLf_EN)
#define E1000_TCTLF_PSP	(1 << E1000_TCTLf_PSP)

#define E1000_RX_BUFF_COUNT	32	// 01000101's driver uses 768 for each of these...
#define E1000_TX_BUFF_COUNT	8

class CE1000DescriptorEntryRX
{
	U64	address;
	U16 length;
	U16 checksum;
	U8	status;
	U8	errors;
	U16	special;
};

class CE1000DescriptorEntryTX
{
	U64 address;
	U16 length;
	U8	cso;
	U8	cmd;
	U8	sta;
	U8	css;
	U16 special;
};

class CE1000
{
	CPCIDev *pci;

	U8	mac_address[6];
	U64	mmio_address;
	U8 *rx_de_buffer;			// Uncached-alias of pointer to the buffer of RX Descriptor Entries.
	U8 *tx_de_buffer;			// Uncached-alias of pointer to the buffer of TX Descriptor Entries.
	U8 *rx_de_buffer_phys;		// Pointer to the buffer of RX Descriptor Entries. (Code Heap, lower 2Gb)
	U8 *tx_de_buffer_phys;		// Pointer to the buffer of TX Descriptor Entries. (Code Heap, lower 2Gb)
	U64 rx_buffer_addr;			// Uncached-alias of address of receive buffers.
	U64 tx_buffer_addr;			// Uncached-alias of address of transmit buffers.
	U64 rx_buffer_addr_phys;	// Physical address of actual receive buffers  (< 4 Gb)
	U64 tx_buffer_addr_phys;	// Physical address of actual transmit buffers (< 4 Gb)

} e1000; // e1000 is the global variable we store all of this into.

CPCIDev *E1000PCIDevFind()
{// Find and return E1000 card as a CPCIDev pointer.

	CPCIDev *pci = PCIDevFind(PCIC_NETWORK,, PCIV_E1000);

	if (!pci)
		return NULL;

	ClassRep(pci);

	switch (pci->device_id)
	{
		case PCID_82545EM:
			break;

		default:
			pci = NULL;
	}

	return pci;
}

U32	E1000MMIORead(U32 offset)
{
	U32 *val = e1000.mmio_address + offset;

	return *val;
}

U0 E1000MMIOWrite(U32 offset, U32 val)
{
	U32 *addr = e1000.mmio_address + offset;

	*addr = val;
}

U16	E1000EEPROMRead(U8 word)
{ // word arg is which U16 to read
	U16 data;
	U32 temp;

	E1000MMIOWrite(E1000_REG_EERD, 1 | word << 8);

	while (!((temp = E1000MMIORead(E1000_REG_EERD)) & (1 << 4)))
		Sleep(1);

	data = (temp >> 16) & 0xFFFF;
	return data;
}

U0 E1000MACGet()
{
	I64 i;
	U16 mac;

	NetLog("E1000 GET MAC: Getting VM MAC.");

	for (i = 0; i < 3; i++)
	{
		mac = E1000EEPROMRead(i);
		e1000.mac_address[2*i]	 = mac & 0xFF;
		e1000.mac_address[2*i+1] = (mac >> 8) & 0xFF;
		NetLog(" %02X %02X", mac.u8[0], mac.u8[1]);
	}
	
}

U0 EthernetFrameFinish(I64 de_index)
{//Alias for driver Finish TX function.
	//E1000TransmitPacketFinish(de_index);
	no_warn de_index;
	NetErr("TODO E1000");
}

/*
U0 PCIInterruptsReroute(I64 base)
{ // todo: comments explaining process, maybe better var names
	I64	 i;
	U8	*da = dev.uncached_alias + IOAPIC_REG;
	U32 *_d = dev.uncached_alias + IOAPIC_DATA;

	for (i = 0; i < 4; i++)
	{
		*da = IOREDTAB + i * 2 + 1;
		*_d = dev.mp_apic_ids[INT_DEST_CPU] << 24;
		*da = IOREDTAB + i * 2;
		*_d = 0x4000 + base + i;
	}
}


U0 E1000InterruptsSetup()
{
//	PCIInterruptsReroute(I_E1000);
	NetErr("TODO E1000");
}
*/

U0 E1000RXInit()
{
	I64 de_index;

	e1000.rx_de_buffer_phys = CAllocAligned(sizeof(CE1000DescriptorEntryRX) * E1000_RX_BUFF_COUNT,
											16, 
											Fs->code_heap);

	e1000.rx_de_buffer = dev.uncached_alias + e1000.rx_de_buffer_phys;

	e1000.rx_buffer_addr_phys = CAlloc(ETHERNET_FRAME_SIZE * E1000_RX_BUFF_COUNT, Fs->code_heap);

	e1000.rx_buffer_addr = dev.uncached_alias + e1000.rx_buffer_addr_phys;

	// iterate de's and make packet buffers for each
	CE1000DescriptorEntryRX *entry = e1000.rx_de_buffer;
	for (de_index = 0; de_index < E1000_RX_BUFF_COUNT; de_index++)
	{
		entry->address = e1000.rx_buffer_addr + de_index * ETHERNET_FRAME_SIZE; // is this right? might need to change ?..
																				// 01000101 MAlloc's 8208 for each DE
//		PCNetDescriptorEntryInit(&entry[de_index],
//								 pcnet.rx_buffer_addr + de_index * ETHERNET_FRAME_SIZE,
//								 TRUE); // TRUE for is_rx.
	}

	// setup rx de ring buffer
	E1000MMIOWrite(E1000_REG_RDBAH, e1000.rx_de_buffer >> 32);			// should we be using uncached addr here ?
	E1000MMIOWrite(E1000_REG_RDBAL, e1000.rx_de_buffer & 0xFFFFFFFF);

	// set receive buffer length
	E1000MMIOWrite(E1000_REG_RDLEN, E1000_RX_BUFF_COUNT * 16);

	// set head tail pointers
	E1000MMIOWrite(E1000_REG_RDH, 0);
	E1000MMIOWrite(E1000_REG_RDT, E1000_RX_BUFF_COUNT);

	// set receive control reg
	E1000MMIOWrite(E1000_REG_RCTL,	E1000_RCTLF_SBP			|
//									E1000_RCTLF_UPE			|
//									E1000_RCTLF_RDMTS_HALF	|
//									E1000_RCTLF_BSIZE_2048	|
//									E1000_RCTLF_MPE			|
									E1000_RCTLF_SECRC		|
									E1000_RCTLF_LPE			|
									E1000_RCTLF_BAM);
}

U0 E1000TXInit()
{
	e1000.tx_de_buffer_phys = CAllocAligned(sizeof(CE1000DescriptorEntryTX) * E1000_TX_BUFF_COUNT,
											16, 
											Fs->code_heap);

	e1000.tx_de_buffer = dev.uncached_alias + e1000.tx_de_buffer_phys;

	e1000.tx_buffer_addr_phys = CAlloc(ETHERNET_FRAME_SIZE * E1000_TX_BUFF_COUNT, Fs->code_heap);

	e1000.tx_buffer_addr = dev.uncached_alias + e1000.tx_buffer_addr_phys;

	// setup tx de ring buffer
	E1000MMIOWrite(E1000_REG_TDBAH, e1000.tx_de_buffer >> 32);			// should we be using uncached addr here ?
	E1000MMIOWrite(E1000_REG_TDBAL, e1000.tx_de_buffer & 0xFFFFFFFF);

	// set tx buffer length
	E1000MMIOWrite(E1000_REG_TDLEN, E1000_TX_BUFF_COUNT * 16);

	// set head tail pointers
	E1000MMIOWrite(E1000_REG_TDH, 0);
	E1000MMIOWrite(E1000_REG_TDT, E1000_RX_BUFF_COUNT);

	// set transmit control reg
	E1000MMIOWrite(E1000_REG_TCTL, E1000_TCTLF_EN | E1000_TCTLF_PSP);

}


U0 E1000Init()
{
	I64 i;

	MemSet(&e1000, 0, sizeof(CE1000)); // e1000 global var will hold member data the driver uses often.
	"\nE1000 driver WIP\n\n";

	e1000.pci = E1000PCIDevFind;
	if (!e1000.pci)
		return; // if we don't find the card, quit.


	e1000.mmio_address = dev.uncached_alias + e1000.pci->base[0] & ~0xF;
	// Assuming card supports MMIO... lower 4 bits are hardwired zero (?)

	"\nMMIO address: 0x%0X\n", e1000.mmio_address;

	// init rx/tx addrs? (linux)

	// eeprom? MAC ?
	E1000MACGet;

	// setup link? (01000101's driver)
	E1000MMIOWrite(E1000_REG_CTRL, E1000MMIORead(E1000_REG_CTRL) | E1000_CTRLF_SLU);

	// zero out multicast hash? (linux)
	// zero out multicast table array (01000101's driver)
	for (i = 0; i < 128; i++)
		E1000MMIOWrite(E1000_REG_MTA + i*4, 0);

	// setup link? (linux)

	// clear all statistics regs after link establish attempt (linux)

	// enable & clear existing interupts (01000101's driver)
	E1000MMIOWrite(E1000_REG_IMS, 0x1F6DC); // TODO: WHAT IS THIS
	E1000MMIORead(0xC0); // TODO : WHAT IS THIS ???

	// start rx tx?
	E1000RXInit;
	E1000TXInit;


	NetErr("TODO E1000");
	"\n";
	ClassRep(&e1000);
}

I64 EthernetFrameAllocate(U8 **packet_buffer_out,
						  U8 *source_address,
						  U8 *destination_address,
						  U16 ethertype,
						  I64 packet_length)
{
	no_warn packet_buffer_out, source_address, destination_address, ethertype, packet_length;
	NetErr("TODO E1000");
	return -1;
}

U8 *EthernetMACGet()
{
	return e1000.mac_address;
}

U0 NetStop()
{

}

U0 NetStart()
{

}

E1000Init;