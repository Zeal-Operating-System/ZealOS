class CEthernetFrame {
	U8	source_address[6];
	U8	padding[2];
	U8	destination_address[6];
	U16	ethertype;

	U8 *data;

	I64 length;
};

class CEthernetGlobals
{
	U8 ethernet_null[6];
	U8 ethernet_broadcast[6];

} ethernet_globals;

U0 EthernetInitGlobals()
{
	I64 i;
	for (i=0;i<6;i++)
	{
		ethernet_globals.ethernet_null[i] = 0;
		ethernet_globals.ethernet_broadcast[i] = 0xFF;
	}
}




//This method is retarded. It needs help.
U0 EthernetFrameParse(CEthernetFrame *frame_out, U8 *frame, U16 length)
{
	//Shrine has a FIXME for check length! We need to figure out what
	//lengths are appropriate ...... Shrine also says MemCopy has a
	//high overhead. I'm almost tempted to say that means that a lot
	//of the current system should be done with less extra allocation
	//altogether, more passing.

	MemCopy(frame_out->destination_address, frame, 6); // 6 ? Why 6? Need a #define...

	MemCopy(frame_out->source_address, frame + 6, 6); // Ridiculous, what are those

	frame_out->ethertype = frame[13] | (frame[12] << 8); // This would be readable with #defines

	frame_out->data = frame + 14; // Fuck you Shrine

	frame_out->length = length - 14 + 4;	//... He has a comment literally just saying "??". Wow.
}

EthernetInitGlobals;