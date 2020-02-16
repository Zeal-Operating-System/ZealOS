In("CC\n\n1\n\n\n\n");
BootHDIns;
"\n\nSuccessful?";
if(YorN)
{
  Once("#include\"DoDistro\";;Del(\"~/Registry.CC\");;OutU16(0x4004, 0x3400);");
  Reboot;
}
