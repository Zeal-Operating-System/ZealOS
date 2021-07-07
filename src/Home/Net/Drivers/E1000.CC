/*	Intel(R) E1000 Driver
	Author: TomAwezome

	Driver is based on:
	-	Linux E1000 driver
	-	01000101's example i825xx driver
	-	OSDev Intel(R) 8254x documentation
	-	Intel(R) PCI/PCI-X Family of Gigabit Ethernet Controllers Software Developer's Manual
	-	any other useful sources.

	Guidelines:
	-	Magic numbers are bad. #defines are good.
	-	Understandability over LOC.
	-	Clear documentation.
*/

// TODO: clean up entire driver

#define E1000_REG_EERD	0x0014	// EEPROM Read

class CE1000
{
	CPCIDev *pci;

	U8	mac_address[6];
	U64	mmio_address;

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

U0 E1000Init()
{
	MemSet(&e1000, 0, sizeof(CE1000)); // e1000 global var will hold member data the driver uses often.
	"\nE1000 driver WIP\n\n";

	e1000.pci = E1000PCIDevFind;
	if (!e1000.pci)
		return; // if we don't find the card, quit.


	e1000.mmio_address = dev.uncached_alias + e1000.pci->base[0] & ~0xF;
	// Assuming card supports MMIO... lower 4 bits are hardwired zero (?)

	"\nMMIO address: 0x%0X\n", e1000.mmio_address;

	// init rx/tx addrs?

	// eeprom? MAC ?
	E1000MACGet;

	// setup link? (01000101's driver)

	// zero out multicast hash? (linux)
	// zero out multicast table array (01000101's driver)

	// setup link? (linux)

	// clear all statistics regs after link establish attempt (linux)

	// enable interupts (01000101's driver)

	// start rx tx?

	NetErr("TODO E1000");
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
	NetErr("TODO E1000");
	return e1000.mac_address;
}

U0 NetStop()
{

}

U0 NetStart()
{

}

E1000Init;