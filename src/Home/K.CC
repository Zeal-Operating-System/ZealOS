//Ed("/Doc/ChangeLog.DD");

In("CC\n\n1\n\n5\n\n\n");
BootHDIns;

"\n\nSuccessful? ";
if (YorN)
{
	Once(	"CursorRemove(\"/*\");;;"
			"#include \"DoDistro\";;"
			"if (DriveIsWritable)"
			"{"
				"Del(\"~/Registry.CC\");"
				"OutU16(0x4004, 0x3400);"
			"}");

	BootRAM;
}
