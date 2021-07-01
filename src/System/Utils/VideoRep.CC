public I64 VideoRep(Bool full=TRUE)
{//List available VBE modes as indicated by the BIOS. Show current mode;
	I64 i, mode_count = 0;
	CVBEModeShort *mode;

	if (full)
	{
		"\nVBE Version %X.%X\n\n", sys_vbe_info.version.u8[1], sys_vbe_info.version.u8[0];
		"$$PURPLE$$Manufacturer      $$FG$$: $$BLACK$$%s$$FG$$\n", sys_vbe_info.oem;
		"$$PURPLE$$Vendor name       $$FG$$: $$BLACK$$%s$$FG$$\n", sys_vbe_info.vendor;
		"$$PURPLE$$Product name      $$FG$$: $$BLACK$$%s$$FG$$\n", sys_vbe_info.product_name;
		"$$PURPLE$$Product revision  $$FG$$: $$BLACK$$%s$$FG$$\n", sys_vbe_info.product_revision;
		"$$PURPLE$$Software revision $$FG$$: $$BLACK$$%X.%X$$FG$$\n", sys_vbe_info.software_revision.u8[1],  sys_vbe_info.software_revision.u8[0];
		"$$PURPLE$$Hardware memory   $$FG$$: $$BLACK$$%d MiB$$FG$$\n", sys_vbe_info.total_memory * 64 / 1024;
		"\n\nAll modes shown are 32-bit color.\n\n";
	}
	"$$CYAN$$ #    W  x   H\t\t Mode$$FG$$\n\n";
	for (i = 0; i < VBE_MODES_NUM; i++)
	{
		mode = &sys_vbe_modes[i];
		if (mode->height)
		{
		 "$$PURPLE$$ $$BT+X,\"%d\",LM=\"%d\\n\"$$$$FG$$$$LM,4$$", i+1, i+1;
			if (sys_vbe_mode_num == mode->mode_num)
				"$$RED$$%4d x %4d 	0x%X (Current mode)$$FG$$$$LM,0$$", mode->width, mode->height, mode->mode_num;
			else
				"$$BLACK$$%4d x %4d 	$$FG$$0x%X$$LM,0$$", mode->width, mode->height, mode->mode_num;
			"\n\n\n";
			mode_count++;
		}
	}
	return mode_count;
}

