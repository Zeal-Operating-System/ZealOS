
U32 PCIReadU32(I64 bus, I64 dev, I64 fun, I64 rg)
{//Read U32 in PCI configspace at bus, dev, fun, reg.
	I64 res, addr, offset;

	if (sys_pci_services)
		res = PCIBIOSReadU32(bus, dev, fun, rg);
	else
	{
		addr =	bus << 16	|
				dev << 11	|
				fun << 8	|
				rg & 0xFC	|
				0x80000000;

		offset = rg - rg & 0xFC;
		OutU32(PCI_ADDR, addr);
		res = InU32(PCI_DATA) >> (offset * 8);
	}

	return res;
}

U8 PCIReadU8(I64 bus, I64 dev, I64 fun, I64 rg)
{//Read U8 in PCI configspace at bus, dev, fun, reg.
	I64 res;

	if (sys_pci_services)
		res = PCIBIOSReadU8(bus, dev, fun, rg);
	else
	{
		res = PCIReadU32(bus, dev, fun, rg) & 0xFF;
	}

	return res;
}

U16 PCIReadU16(I64 bus, I64 dev, I64 fun, I64 rg)
{//Read U16 in PCI configspace at bus, dev, fun, reg.
	I64 res;

	if (sys_pci_services)
		res = PCIBIOSReadU16(bus, dev, fun, rg);
	else
	{
		res = PCIReadU32(bus, dev, fun, rg) & 0xFFFF;
	}

	return res;
}

U0 PCIWriteU32(I64 bus, I64 dev, I64 fun, I64 rg, I64 val)
{//Write U32 in PCI configspace at bus, dev, fun, reg.
	I64 addr, offset;

	if (sys_pci_services)
		PCIBIOSWriteU32(bus, dev, fun, rg, val);
	else
	{
		addr =	bus << 16	|
				dev << 11	|
				fun << 8	|
				rg & 0xFC	|
				0x80000000;

		offset = rg - rg & 0xFC;
		OutU32(PCI_ADDR, addr);
		OutU32(PCI_DATA, val << (offset * 8));
	}
}


U0 PCIWriteU8(I64 bus, I64 dev, I64 fun, I64 rg, I64 val)
{//Write U8 in PCI configspace at bus, dev, fun, reg.
	if (sys_pci_services)
		PCIBIOSWriteU8(bus, dev, fun, rg, val);
	else
	{
		PCIWriteU32(bus, dev, fun, rg, val & 0xFF);
	}
}

U0 PCIWriteU16(I64 bus, I64 dev, I64 fun, I64 rg, I64 val)
{//Write U16 in PCI configspace at bus, dev, fun, reg.
	if (sys_pci_services)
		PCIBIOSWriteU16(bus, dev, fun, rg, val);
	else
	{
		PCIWriteU32(bus, dev, fun, rg, val & 0xFFFF);
	}
}

I64 PCIClassFind(I64 class_code, I64 n)
{/*Find bus, dev, fun of Nth class_code dev.

class_code is low three bytes
n is index starting at zero
Return: -1 not found
else bus, dev, fun.
*/
	I64 res = -1, cur = 0, b, d, f;


	if (sys_pci_services)
	{
		"System has PCIBIOS\n";
		res = PCIBIOSClassFind(class_code, n);
	}
	else
	{
		"System does not have PCIBIOS\n";
		for (b = 0; b < sys_pci_buses; b++)
			for (d = 0; d < 32; d++)
				for (f = 0; f < 8; f++)
				{
					if (class_code == PCIReadU32(b, d, f, PCIR_PROG_IF) & 0xFFFFFF)
					{
						if (n == cur++)
						{
							res = b << 16 | d << 8 | f;
							goto pci_end;
						}
					}
				}
	}
pci_end:
	return res;
}
