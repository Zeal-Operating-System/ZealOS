/*	AMD PCNetII Driver
	Author: TomAwezome

	Driver is based on:
	-	minexew's ShrineOS PCNet.CC implementation
	-	OSDev AMD_PCNET documentation
	-	AMD PCnet(TM)-PCI datasheet
	-	any other useful sources.

	Guidelines:
	-	Magic numbers are bad. #defines are good.
	-	Understandability over LOC.
	-	Clear documentation.
*/

#include "Net.HH"
#include "NetQueue"

#define	PCNET_DEVICE_ID	0x2000
#define	PCNET_VENDOR_ID	0x1022

#define	PCI_REG_COMMAND	0x04

#define	PCNET_CMDf_IOEN	0
#define	PCNET_CMDf_BMEN	2

#define PCNET_CMDF_IOEN	(1 << PCNET_CMDf_IOEN)
#define PCNET_CMDF_BMEN	(1 << PCNET_CMDf_BMEN)

#define PCNET_WD_RESET	0x14 // reset reg location when card is in 16-bit mode

#define PCNET_DW_RDP	0x10
#define PCNET_DW_RAP	0x14
#define PCNET_DW_RESET	0x18 // reset reg location when card is in 32-bit mode

#define PCNET_CSR_CTRLSTATUS	0
#define PCNET_CSR_INTERRUPTS	3
#define PCNET_CSR_FEATURECTRL	4
#define PCNET_CSR_LADRF0		8
#define PCNET_CSR_LADRF1		9
#define PCNET_CSR_LADRF2		10
#define PCNET_CSR_LADRF3		11
#define PCNET_CSR_PADR0			12
#define PCNET_CSR_PADR1			13
#define PCNET_CSR_PADR2			14
#define PCNET_CSR_MODE			15
#define PCNET_CSR_BADRL			24
#define PCNET_CSR_BADRU			25
#define PCNET_CSR_BADTL			30
#define PCNET_CSR_BADTU			31
#define PCNET_CSR_POLLINT		47
#define PCNET_CSR_SOFTWARESTYLE	58
#define PCNET_CSR_RXRINGLEN		76
#define PCNET_CSR_TXRINGLEN		78

#define PCNET_SWSTYLE_SELECTION	2 // AMD PCNet datasheet p. 1-968

// Refer to AMD PCNet datasheet p. 1-954, 1-956, 1-957 for Interrupt Mask details.
#define PCNET_INT_BSWP		2	// Byte Swap (Big-Endian / Little-Endian)
#define PCNET_INT_IDONM		8	// Initialization Done Mask
#define PCNET_INT_TINTM		9	// Transmit Interrupt Mask
#define PCNET_INT_RINTM		10	// Receive Interrupt Mask

#define PCNET_FEATURE_APADXMT	11

#define PCNET_CTRL_INIT	0
#define PCNET_CTRL_STRT	1
#define PCNET_CTRL_STOP	2
#define PCNET_CTRL_RINT 10

#define PCNET_RX_BUFF_COUNT	32	// Linux & Shrine Driver use 32 and 8 for
#define PCNET_TX_BUFF_COUNT	8	// these, we could allow more if wanted.

#define PCNET_DESCRIPTORf_ENP	24
#define PCNET_DESCRIPTORf_STP	25
#define PCNET_DESCRIPTORf_OWN	31 // AMD PCNet datasheet p.1-992, 1-994
//#define PCNET_DESCRIPTORF_OWN	(1 << PCNET_DESCRIPTORf_OWN)

#define INT_DEST_CPU	0

class CPCNet
{
	CPCIDev *pci;
	U8 mac_address[6];			// MAC address is first 6 bytes of PCNet EEPROM	(page # ? )

	I64 current_rx_de_index;	// Current Receive DE being processed.  Gets incremented, wrapped to 0 at max of PCNET_RX_BUFF_COUNT.
	I64 current_tx_de_index;	// Current Transmit DE being processed. Gets incremented, wrapped to 0 at max of PCNET_TX_BUFF_COUNT.

	U8 *rx_de_buffer;			// Uncached-alias of pointer to the buffer of RX Descriptor Entries.
	U8 *tx_de_buffer;			// Uncached-alias of pointer to the buffer of TX Descriptor Entries.
	U8 *rx_de_buffer_phys;		// Pointer to the buffer of RX Descriptor Entries. (Code Heap, lower 2Gb)
	U8 *tx_de_buffer_phys;		// Pointer to the buffer of TX Descriptor Entries. (Code Heap, lower 2Gb)

	U32 rx_buffer_addr;			// 'Physical address of actual receive buffers  (< 4 Gb)'
	U32 tx_buffer_addr;			// 'Physical address of actual transmit buffers (< 4 Gb)'

} pcnet; // pcnet is the global variable we store all of this into.

class CPCNetDescriptorEntry
{/* AMD PCNet datasheet p.1-991 & p.1-994 NOTE: chart typo  on 1-994, see ONES and BCNT on 1-995.
	TX and RX DE's are the same size (16-Bytes) and structure,
	but have different registers and functions.
	The RX and TX DE buffers of the CPCNet class
	are allocated to a certain amount of these DEs. */
	U32	buffer_addr;
	U32 status1;
	U32 status2;
	U32 reserved;
};


CPCIDev *PCNetPCIDevFind()
{// Find and return PCNetII card as a CPCIDev pointer.
	return PCIDevFind(,, PCNET_VENDOR_ID, PCNET_DEVICE_ID);
}

U32 PCNetGetIOBase()
{/* Return memory IO base address
	of PCNet card. Bits 0-4 are not
	for the IO base, so an AND with
	~0x1F ignores those bits. */
	U32 io_base = pcnet.pci->base[0] & ~0x1F;
	return io_base;
}

U0 PCNetReset()
{/* Reads the 32- and 16-bit RESET registers,
	which, regardless of which mode the card is in,
	will reset it back to 16-bit mode. */
	InU32(PCNetGetIOBase + PCNET_DW_RESET);
	InU16(PCNetGetIOBase + PCNET_WD_RESET);
	Busy(5); // OSDev says minimum 1 ÊS
}

U0 PCNetEnter32BitMode()
{/* AMD PCNet datasheet p. 1-930
	Summary: A 32-bit write (while in 16-bit mode)
	to RDP  will cause 16-bit mode exit
	and immediate enter into 32-bit mode. */
	OutU32(PCNetGetIOBase + PCNET_DW_RDP, 0);

}

U0 PCNetWriteRAP(U32 value)
{/* AMD PCNet datasheet p. 1-952
	Summary: Register Address Pointer register
	value will indicate which CSR / BCR register
	we want to access in RDP / BDP. */
	OutU32(PCNetGetIOBase + PCNET_DW_RAP, value);
}

U0 PCNetWriteCSR(U32 csr, U32 value)
{/* AMD PCNet datasheet p. 1-952
	Summary: Control and Status Registers are
	accessed via the RDP (Register Data Port).
	Which CSR is selected is based on the value
	in the RAP. */
	PCNetWriteRAP(csr);
	OutU32(PCNetGetIOBase + PCNET_DW_RDP, value);
}

U32 PCNetReadCSR(U32 csr)
{/* AMD PCNet datasheet p. 1-952
	Summary: Control and Status Registers are
	accessed via the RDP (Register Data Port).
	Which CSR is selected is based on the value
	in the RAP. */
	PCNetWriteRAP(csr);
	return InU32(PCNetGetIOBase + PCNET_DW_RDP);
}

U0 PCNetSetSWStyle()
{/* AMD PCNet datasheet p. 1-968
	In CSR58 (Software Style), the 8-bit
	SWSTYLE register dictates interpretation of certain
	bits in the CSR space, and widths of descriptors and
	initialization block. In PCINet-PCI mode, CSR4 bits
	function as defined in the datasheet , and TMD1[29]
	functions as ADD_FCS. */
	U32 csr = PCNetReadCSR(PCNET_CSR_SOFTWARESTYLE);

	csr &= ~0xFF; // clears first 8 bits: SWSTYLE 8-bit register.
	csr |= PCNET_SWSTYLE_SELECTION; // set SWSTYLE to PCNet-PCI mode.

	PCNetWriteCSR(PCNET_CSR_SOFTWARESTYLE, csr);
}

U0 PCNetGetMAC()
{/* AMD PCNet datasheet p. 1-887, 1-931, 1-937
	MAC address stored at first 6 bytes of PCNet EEPROM.
	EEPROM addresses shadow-copied to APROM at hardware init.
	APROM accessible at first 16 bytes of PCI IO space. */
	I64 i;
	for (i = 0; i < 6; i++)
	{
		pcnet.mac_address[i] = InU8(PCNetGetIOBase + i);
	}
}

U0 PCNetInitDescriptorEntry(CPCNetDescriptorEntry *entry, U32 buffer_address, I64 is_rx)
{
	entry->buffer_addr = buffer_address;

	/*	AMD PCNet datasheet p.1-991.
		BCNT is the usable buffer length, expressed as first
		12 bits of 2s-complement of desired length.
		Bits 0-11 of a DE are for the buffer byte count (BCNT),
		and bits 12-15 of a DE must be written all ones (ONES) */
	U16 buffer_byte_count = -ETHERNET_FRAME_SIZE;	// Sets up as 2s complement of the desired length.
	buffer_byte_count &= 0x0FFF;					// Masks 0 over everything except bits 0-11.

	entry->status1 |= buffer_byte_count;			// Sets BCNT reg (first 12 bits) in DE TMD1/RMD1.
	entry->status1 |= 0xF000;						// Sets bits 12-15 (ONES) in DE TMD1/RMD1  as all ones.

	//if this is a Receive DE, give ownership to the card so the PCNet can fill them.
	if (is_rx)
		Bts(&entry->status1, PCNET_DESCRIPTORf_OWN);
	ClassRep(entry);
	
}

U0 PCNetAllocateBuffers()
{
	I64 de_index; // used in for loops for TX and RX DE access.

	/*	AMD PCNet datasheet p.1-913, p.1-990
		When SSIZE32=1, Descriptor Ring Entry Base Address
		must be on 16-byte boundary. (TDRA[3:0]=0, RDRA[3:0]=0) */
	pcnet.rx_de_buffer_phys = CAllocAligned(sizeof(CPCNetDescriptorEntry) * PCNET_RX_BUFF_COUNT,
											16, 
											Fs->code_heap);

	pcnet.tx_de_buffer_phys = CAllocAligned(sizeof(CPCNetDescriptorEntry) * PCNET_TX_BUFF_COUNT,
											16,
											Fs->code_heap);

	//Shrine does a check and returns -1 here, if the end of either buffer exceeds 0x100000000

	pcnet.rx_de_buffer = dev.uncached_alias + pcnet.rx_de_buffer_phys; // we want uncached
	pcnet.tx_de_buffer = dev.uncached_alias + pcnet.tx_de_buffer_phys; // access to these.

	pcnet.rx_buffer_addr = CAlloc(ETHERNET_FRAME_SIZE * PCNET_RX_BUFF_COUNT,	//Shrine has a TODO to figure out
								  Fs->code_heap);

	pcnet.tx_buffer_addr = CAlloc(ETHERNET_FRAME_SIZE * PCNET_TX_BUFF_COUNT,	//if these should be uncached too.
								  Fs->code_heap);								//note, p.1-991,1-994: RBADR is only 32 bits wide.

	//Shrine does a check and returns -1 here, if the end of either buffer exceeds 0x100000000


	CPCNetDescriptorEntry *entry = pcnet.rx_de_buffer;
	for (de_index = 0; de_index < PCNET_RX_BUFF_COUNT; de_index++)
	{
		PCNetInitDescriptorEntry(&entry[de_index], pcnet.rx_buffer_addr, TRUE); // TRUE for is_rx.
	}

	entry = pcnet.tx_de_buffer;
	for (de_index = 0; de_index < PCNET_TX_BUFF_COUNT; de_index++)
	{
		PCNetInitDescriptorEntry(&entry[de_index], pcnet.tx_buffer_addr, FALSE); // FALSE for is_rx.
	}
	
}

U0 PCNetDirectInit()
{/* AMD PCNet datasheet p. 1-1021
	Instead of setting up initialization block,
	direct writes to the necessary CSRs can be
	used to manually initialize the PCNet card. */

	/*	AMD PCNet datasheet p.1-991
		If Logical Address Filter is set as
		all 0, all incoming logical addresses
		are rejected. Disables multicast. */
	PCNetWriteCSR(PCNET_CSR_LADRF0, 0);
	PCNetWriteCSR(PCNET_CSR_LADRF1, 0);
	PCNetWriteCSR(PCNET_CSR_LADRF2, 0);
	PCNetWriteCSR(PCNET_CSR_LADRF3, 0);

	/*	The Physical Address is the MAC.
		AMD PCNet datasheet p.1-960, 1-961
		The first 16 bits of CSRs 12-14 are
		for the Physical Address, the upper bits
		are reserved, written 0 read undefined. 

		The OR and bit-shift of 8 allows writing
		separate U8 values in the correct locations
		of the CSR. */
	PCNetWriteCSR(PCNET_CSR_PADR0, pcnet.mac_address[0] | (pcnet.mac_address[1] << 8));
	PCNetWriteCSR(PCNET_CSR_PADR1, pcnet.mac_address[2] | (pcnet.mac_address[3] << 8));
	PCNetWriteCSR(PCNET_CSR_PADR2, pcnet.mac_address[4] | (pcnet.mac_address[5] << 8));

	/*	AMD PCNet datasheet p.1-961, 1-962, 1-963
		Refer to datasheet for specifics.
		Most relevant, when setting Mode to 0,
		promiscuous mode is is disabled, TX and
		RX enabled, enable RX broadcast and unicast. */
	PCNetWriteCSR(PCNET_CSR_MODE, 0);

	/* 	AMD PCNet datasheet p.1-964
		CSR 24 and 25 need to be filled
		with the lower and upper 16 bits,
		respectively, of the address of 
		the RX packet ring. Likewise for
		CSR 30 and 31 for the TX packet ring.

		0xFFFF AND on address will leave
		only lower 16 bits remaining.

		Bitshift right of 16 will replace
		first 16 bits  with upper 16 bits,
		remaining bits cleared.*/
	PCNetWriteCSR(PCNET_CSR_BADRL, pcnet.rx_buffer_addr & 0xFFFF);
	PCNetWriteCSR(PCNET_CSR_BADRU, pcnet.rx_buffer_addr >> 16);

	PCNetWriteCSR(PCNET_CSR_BADTL, pcnet.tx_buffer_addr & 0xFFFF);
	PCNetWriteCSR(PCNET_CSR_BADTU, pcnet.tx_buffer_addr >> 16);

	/*	AMD PCNet datasheet p. 1-967
		Default value at hardware init is
		all 0. Standard init block process
		sets this, but if doing directly
		it is imperative to manually set it 0. */
	PCNetWriteCSR(PCNET_CSR_POLLINT, 0);

	/*	AMD PCNet datasheet p. 1-970
		Receive and Transmit Ring Length CSRs
		bits 0-15 need to be set as the 2s complement
		of the ring length. The AND with 0xFFFF clears
		the upper Reserved bits, which are to be written
		as zeroes read undefined. */
	PCNetWriteCSR(PCNET_CSR_RXRINGLEN, -PCNET_RX_BUFF_COUNT & 0xFFFF);
	PCNetWriteCSR(PCNET_CSR_TXRINGLEN, -PCNET_TX_BUFF_COUNT & 0xFFFF);

	
}

U0 PCNetSetInterruptCSR()
{/* AMD PCNet datasheet p.1-952, 1-953, 1-954, 1-955, 1-956, 1-957
	Refer to datasheet for specifics on the Interrupt Masks.
	Most of these, when set 0, allow interrupts to be set in CSR0.
	We set Big-Endian disabled, RX interrupts
	enabled, Init Done interrupt disabled, and TX interrupt
	disabled. */
	U32 csr = PCNetReadCSR(PCNET_CSR_INTERRUPTS);

	Btr(&csr, PCNET_INT_BSWP);
	Btr(&csr, PCNET_INT_RINTM);

	Bts(&csr, PCNET_INT_IDONM);
	Bts(&csr, PCNET_INT_TINTM);
	
	PCNetWriteCSR(PCNET_CSR_INTERRUPTS, csr);
}

U0 PCNetEnableTXAutoPad()
{/* AMD PCNet datasheet p.1-958
	Setting bit 11 (Auto Pad Transmit) allows
	shoft transmit frames to be automatically
	extended to 64 bytes. */
	U32 csr = PCNetReadCSR(PCNET_CSR_FEATURECTRL);

	Bts(&csr, PCNET_FEATURE_APADXMT);

	PCNetWriteCSR(PCNET_CSR_FEATURECTRL, csr);

}

U0 PCNetExitConfigMode()
{/* AMD PCNet datasheet p.1-954
	PCNet controller can be started
	after configuring by ensuring INIT
	and STOP are cleared and START bit
	is set, in Status and Control Register
	(CSR0). */
	U32 csr = PCNetReadCSR(PCNET_CSR_CTRLSTATUS);

	Btr(&csr, PCNET_CTRL_INIT);
	Btr(&csr, PCNET_CTRL_STOP);

	Bts(&csr, PCNET_CTRL_STRT);

}

I64 PCNetDriverOwns(CPCNetDescriptorEntry* entry)
{/* Returns whether the value of the OWN bit of the
	Descriptor Entry is zero. If 0, driver owns,
	if 1, PCNet card owns it. */
	return !Bt(&entry->status1, PCNET_DESCRIPTORf_OWN);

}

I64 PCNetAllocateTransmitPacket(U8 **packet_buffer_out, I64 length)
{/* Transmits the packet at the current TX DE index. The packet_buffer_out
	is a pointer, since we modify its value, ending with returning the
	index of the DE we just processed. Length is validated to fit in BCNT.
	The increment of the current TX DE index is done by assigning it the
	value of incrementing it AND the max DE index-1. This will increment it
	as well as wrap back to 0 if we hit the max DE index. */

	U16 buffer_byte_count;
	I64 de_index = pcnet.current_tx_de_index;

	if (length > 0xFFF)
	{ // Max packet length must fit into BCNT 12-bit register.
		ZenithErr("Invalid TX Packet Length");
		throw('PCNet');
	}


	CPCNetDescriptorEntry *entry = &pcnet.tx_de_buffer[de_index];

	if (!PCNetDriverOwns(entry))
	{
		ZenithErr("TX FIFO Full");
		return -1; // Positive value expected. Functions calling this must factor this in.
	}

	Bts(&entry->status1, PCNET_DESCRIPTORf_STP);

	Bts(&entry->status1, PCNET_DESCRIPTORf_ENP);

	/*	AMD PCNet datasheet p.1-991.
		BCNT is the usable buffer length, expressed as first
		12 bits of 2s-complement of desired length.
		Bits 0-11 of a DE are for the buffer byte count (BCNT),
		and bits 12-15 of a DE must be written all ones (ONES) */
	buffer_byte_count = -length;	// Sets up as 2s complement of the desired length.
	buffer_byte_count &= 0x0FFF;					// Masks 0 over everything except bits 0-11.

	entry->status1 |= buffer_byte_count;			// Sets BCNT reg (first 12 bits) in DE TMD1.
	entry->status1 |= 0xF000;						// Sets bits 12-15 (ONES) in DE TMD1 as all ones.

	pcnet.current_tx_de_index = (pcnet.current_tx_de_index + 1) & (PCNET_TX_BUFF_COUNT - 1);

	*packet_buffer_out = pcnet.tx_buffer_addr + (de_index * ETHERNET_FRAME_SIZE);

	return de_index;

}

U0 PCNetFinishTransmitPacket(I64 de_index)
{/* Release ownership of the packet to the PCNet card
	by setting the OWN bit to 1. */ 
	CPCNetDescriptorEntry *entry = &pcnet.tx_de_buffer[de_index];

	Bts(&entry->status1, PCNET_DESCRIPTORf_OWN);

}

U0 EthernetFrameFinish(I64 de_index)
{//Alias for driver Finish TX function.
	PCNetFinishTransmitPacket(de_index);
}

I64 PCNetReceivePacket(U8 **packet_buffer_out, U16 *packet_length_out)
{/* Receives the packet at the current RX DE index. Parameters
	are both pointers, since we modify the value at the packet_buffer_out,
	and at the packet_length, ending with returning the index of the DE
	we just processed.
	The MCNT is stored at the first two bytes of the RMD2. We AND with
	0xFFFF to only take in those first two bytes: that is the packet_length.
	The increment of the current RX DE index is done by assigning it the
	value of incrementing it AND the max DE index-1. This will increment it
	as well as wrap back to 0 if we hit the max DE index. */
	ZenithErr("PCNet received packet. %X , %X",packet_buffer_out,packet_length_out);
	I64 de_index = pcnet.current_rx_de_index;

	CPCNetDescriptorEntry *entry = &pcnet.rx_de_buffer[de_index];

	U16 packet_length = entry->status2 & 0xFFFF;

	pcnet.current_rx_de_index = (pcnet.current_rx_de_index + 1) & (PCNET_RX_BUFF_COUNT - 1);


	*packet_buffer_out = pcnet.rx_buffer_addr + (de_index * ETHERNET_FRAME_SIZE);
	*packet_length_out = packet_length;
	return de_index;

	
}

U0 PCNetReleaseReceivePacket(I64 de_index)
{/* Release ownership of the packet to the PCNet card
	by setting the OWN bit to 1. */ 
	CPCNetDescriptorEntry *entry = &pcnet.rx_de_buffer[de_index];

	Bts(&entry->status1, PCNET_DESCRIPTORf_OWN);
}

interrupt U0 PCNetIRQ()
{// todo: comments explaining process...maybe reimplement interrupt handling altogether.

	U8 *packet_buffer;
	U16 packet_length;
	I64 de_index;

	U32 csr = PCNetReadCSR(PCNET_CSR_CTRLSTATUS);
	//"Interrupt Reason: %X , %b\n",csr,csr;

	CPCNetDescriptorEntry *entry = pcnet.rx_de_buffer;

	while (PCNetDriverOwns(&entry[pcnet.current_rx_de_index]))
	{
		"%X", pcnet.current_rx_de_index;
		de_index = PCNetReceivePacket(&packet_buffer, &packet_length);

		if (de_index >= 0) // necessary? check increment logic in PCNetReceivePacket.
		{
			ZenithErr("Pushing copy into Net Queue, Releasing Receive Packet");
			NetQueuePushCopy(packet_buffer, packet_length);
			PCNetReleaseReceivePacket(de_index);
		}

		Bts(&csr, PCNET_CTRL_RINT);

		PCNetWriteCSR(PCNET_CSR_CTRLSTATUS, csr);
	}

	*(dev.uncached_alias + LAPIC_EOI)(U32*) = 0;
}

U0 PCIRerouteInterrupts(I64 base)
{ // todo: comments explaining process, maybe better var names
	I64 i;
	U8 *da = dev.uncached_alias + IOAPIC_REG;
	U32 *_d = dev.uncached_alias + IOAPIC_DATA;

	for (i = 0; i < 4; i++)
	{
		*da = IOREDTAB + i * 2 + 1;
		*_d = dev.mp_apic_ids[INT_DEST_CPU] << 24;
		*da = IOREDTAB + i * 2;
		*_d = 0x4000 + base + i;
	}
}

U0 PCNetSetupInterrupts()
{ // todo: comments explaining process
	IntEntrySet(I_USER + 0, &PCNetIRQ, IDTET_IRQ);
	IntEntrySet(I_USER + 1, &PCNetIRQ, IDTET_IRQ);
	IntEntrySet(I_USER + 2, &PCNetIRQ, IDTET_IRQ);
	IntEntrySet(I_USER + 3, &PCNetIRQ, IDTET_IRQ);
	PCIRerouteInterrupts(I_USER);
}

U0 PCNetInit()
{
	MemSet(&pcnet, 0, sizeof(CPCNet)); // pcnet global var will hold member data the driver uses often.

	pcnet.pci = PCNetPCIDevFind;
	if (!pcnet.pci)
		return; // if we don't find the card, quit.

	/*	Clear command register of PCNet
		PCI device, set IO Enable and Bus
		Master Enable bits of the register. */
	PCIWriteU16(pcnet.pci->bus,
				pcnet.pci->dev,
				pcnet.pci->fun,
				PCI_REG_COMMAND,
				PCNET_CMDF_IOEN | PCNET_CMDF_BMEN);

	PCNetReset;

	PCNetEnter32BitMode;

	PCNetSetSWStyle;

	PCNetGetMAC;
	// OSDev has code ensuring auto selected connection...

	PCNetAllocateBuffers;

	PCNetDirectInit;

	PCNetSetInterruptCSR;

	PCNetEnableTXAutoPad;

	PCNetExitConfigMode;	

	PCNetSetupInterrupts;


	Sleep(100);//? necessary?
	ClassRep(&pcnet);

	"pcnet->rx_de_buffer: %X\n",		pcnet.rx_de_buffer;
	"pcnet->tx_de_buffer: %X\n",		pcnet.tx_de_buffer;
	"pcnet->rx_de_buffer_phys: %X\n",	pcnet.rx_de_buffer_phys;
	"pcnet->rx_de_buffer_phys: %X\n",	pcnet.tx_de_buffer_phys;


}

I64 EthernetFrameAllocate(U8 **packet_buffer_out,
						  U8 *source_address,
						  U8 *destination_address,
						  U16 ethertype,
						  I64 packet_length)
{/* Allocate an Ethernet Frame for transmit. The source
	and destination addresses are copied to the Frame,
	as well as the ethertype. The packet_buffer_out
	parameter has the value at its pointer set to the
	payload of the Ethernet Frame. */

//todo: un magic number the rest of this
	U8 *ethernet_frame;
	I64 de_index;

	//need to see if 3 years later VirtualBox supports APAD_XMT!
	if (packet_length < ETHERNET_MIN_FRAME_SIZE)
		packet_length = ETHERNET_MIN_FRAME_SIZE;

	de_index = PCNetAllocateTransmitPacket(&ethernet_frame, ETHERNET_MAC_HEADER_LENGTH + packet_length);

	if (de_index < 0)
	{
		ZenithErr("Ethernet Frame Allocate failure");
		return -1; // Positive value expected. Functions calling this must factor this in.
	}

	MemCopy(ethernet_frame,						 destination_address, MAC_ADDRESS_LENGTH);
	MemCopy(ethernet_frame + MAC_ADDRESS_LENGTH, source_address,	  MAC_ADDRESS_LENGTH);

	ethernet_frame[ETHERNET_ETHERTYPE_OFFSET]		= ethertype << 8;
	ethernet_frame[ETHERNET_ETHERTYPE_OFFSET + 1]	= ethertype & 0xFF;

	*packet_buffer_out = ethernet_frame + ETHERNET_MAC_HEADER_LENGTH;

	return de_index;
}

U8 *EthernetGetMAC()
{
	return pcnet.mac_address;
}

PCNetInit;

