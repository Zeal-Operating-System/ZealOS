/*	Intel(R) E1000 Driver
	Author: TomAwezome

	Driver is based on:
	-	Linux E1000 implementation
	-	01000101's example E1000 driver
	-	OSDev Intel(R) E1000 documentation
	-	Intel(R) 8254x family datasheet
	-	any other useful sources.

	Guidelines:
	-	Magic numbers are bad. #defines are good.
	-	Understandability over LOC.
	-	Clear documentation.
*/

// TODO: WIP

class CE1000
{
	CPCIDev *pci;

	U8	mac_address[6];

} e1000; // e1000 is the global variable we store all of this into.

CPCIDev *E1000PCIDevFind()
{// Find and return E1000 card as a CPCIDev pointer.

	return PCIDevFind(,, PCIV_E1000, PCID_82545EM);
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
//	PCIInterruptsReroute(I_E10000);
	NetErr("TODO E1000");
}
*/

U0 E1000Init()
{
	MemSet(&e1000, 0, sizeof(CE1000)); // e1000 global var will hold member data the driver uses often.

	e1000.pci = E1000PCIDevFind;
	if (!e1000.pci)
		return; // if we don't find the card, quit.

	"\nE1000 driver WIP\n\n";
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