
I64 count = 1;



U0 PaletteChange()
{
	//"before: %d\n",count;	
	switch(count){
		case 0: count=5; break;
		case 1:	PaletteSetSlate; break;
		case 2: PaletteSetGreen; break;
		case 3: PaletteSetMarine; break;
		case 4: PaletteSetCommander; break;
		case 5: PaletteSetGray; count=0;break;
		default: count=1; break;
	}
	//"after: %d\n",count;	

}


public U0 PaletteSwapper()
{
	I64 arg1,arg2,ch=0;
	"Prev Palette: Ctrl+Z\n";
	"Next Palette: Ctrl+X\n";
	"Esc to select";

	try {
		while(TRUE) {
			switch(MessageScan(&arg1,&arg2,1<<MESSAGE_KEY_DOWN|1<<MESSAGE_KEY_UP)) {
				case MESSAGE_KEY_DOWN:
					ch=arg1;
					switch(ch){
						case CH_CTRLZ: count--; PaletteChange; break;
						case CH_CTRLX: count++; PaletteChange; break;
						case CH_ESC:
						case CH_SHIFT_ESC:
							throw;
					}
					break;
				}
			Refresh;
		}
	}
	catch
		PutExcept;

	

}


//PaletteSwapper;