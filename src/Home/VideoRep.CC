public I64 VideoRep()
{//List available VBE modes as indicated by the BIOS. Show current mode;
  I64 i, mode_count = 0;

  "\nVBE Version %X.%X\n\n", sys_vbe_info.version.u8[1], sys_vbe_info.version.u8[0];

  return mode_count;
}

VideoRep;