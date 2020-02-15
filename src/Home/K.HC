In("CC\n\n1\n\n\n\n");
BootHDIns;
"\n\nSuccessful?";
if(YorN)
{
  Del("~/Registry.HC");
  Once("#include\"DoDistro\";;OutU16(0x4004, 0x3400);");
  Reboot;
}
