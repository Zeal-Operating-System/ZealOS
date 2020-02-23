#define VBOX_VMMDEV_VERSION			0x00010003

#define VBOX_REQUEST_HEADER_VERSION	0x10001
#define VBOX_REQUEST_GUEST_INFO		50

class CVBox
{
	CPCIDev *pcidev;
	I64	port;
	U32	*vmmdev;
	I64	irq;
}

class CVBoxHeader
{
	U32 size,
		version,
		request_type,
		return_code,
		reserved[2];
};

class CVBoxHGCMHeader
{
	U32	size,
		version,
		request_type;
	I32	return_code,
		reserved[2];
	U32	flags;
	I32	result;
};

class CVBoxClipboardConnect
{
	CVBoxHGCMHeader header;
	U32	location_type;
	U8	location[128];
	U32	client_id,
		msg,
		formats;
};

class CVBoxHGCMParam
{
	U32 type;
	U64	value;
};

class CVBoxHGCMPtr
{
	U32	type,
		size,
		ptr;
};



class CVBoxGuestInfo
{
	CVBoxHeader header;

	U32	version,
		os_type;
};


CPCIDev *vboxpci;
I64 vbox_port;
U32 *vbox_vmmdev;

U0 VBoxInit()
{
	vboxpci = PCIDevFind(,,0x80EE,0xCAFE);
	vbox_port = vboxpci->base[0] & ~0x3;
	vbox_vmmdev = vboxpci->base[1] & ~0xF;

	CVBoxGuestInfo *guest_info = CAllocAligned(sizeof(CVBoxGuestInfo), 16,Fs->code_heap);
	guest_info->header.size = sizeof(CVBoxGuestInfo);
	guest_info->header.version = VBOX_REQUEST_HEADER_VERSION;
	guest_info->header.request_type = VBOX_REQUEST_GUEST_INFO;
	guest_info->version = VBOX_VMMDEV_VERSION;

	OutU32(vbox_port, guest_info);

	ClassRep(guest_info);
	Free(guest_info);
}

VBoxInit;
