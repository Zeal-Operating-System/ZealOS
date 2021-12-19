//See $LK,"Menus",A="HI:Menus"$

#define M_OPTION1 			1
#define M_OPTION2 			2

U0 PullDownMenuDemo()
{
	I64			message_code, arg1, arg2;
	CMenuEntry *tmpse;

	MenuPush(	"File {"
				"  Open(,'O');"
				"  Save(,'S');"
				"  Exit(,CH_SHIFT_ESC);"
				"}"
				"Edit {"
				"  Cut(,,SC_DELETE|SCF_SHIFT);"
				"  Paste(,,SC_INS|SCF_SHIFT);"
				"}"
				"Misc {"
				"  Beep(,CH_SPACE);"
				"  Opt1(MESSAGE_CMD,M_OPTION1);"
				"  Opt2(MESSAGE_CMD,M_OPTION2);"
				"}"
				"Help {"
				"  Help(,,0x3B0000003B);"
				"  About(,,0x23B0000023B);"
				"}");

	"A pull-down menu will appear "
	"if you move the mouse to the top "
	"of the screen.\n\n";

	do
	{
		message_code = MessageGet(&arg1, &arg2, 1 << MESSAGE_KEY_DOWN + 1 << MESSAGE_CMD);
		"\nCmd:%d ARG1:%X ARG2:%X\n\n", message_code, arg1, arg2;

		switch (message_code)
		{
			case MESSAGE_KEY_DOWN:
				switch (arg1)
				{//ASCII
					case CH_SPACE:
						Beep;
						break;

					case 0:
						switch (arg2.u8[0])
						{//arg2=Scan code
							case SC_F1:
								if (arg2 & SCF_SHIFT)
									"About PullDown Demo\n";
								else
									"Test the menu.\n";
								break;

							case SC_DELETE:
								if (arg2 & SCF_SHIFT)
									"Cut\n";
								break;

							case SC_INS:
								if (arg2 & SCF_SHIFT)
									"Paste\n";
								break;
						}
						break;
				}
				break;

			case MESSAGE_CMD:
			//Feel free to make your menu
			//drive by key strokes, but you can
			//use the $LK,"MESSAGE_CMD",A="MN:MESSAGE_CMD"$ value.
				switch (arg1)
				{
					case M_OPTION1:
						"Option # 1\n";
						if (tmpse = MenuEntryFind(Fs->cur_menu, "Misc/Opt1"))
							tmpse->checked = !tmpse->checked;
						break;

					case M_OPTION2:
						"Option # 2\n";
						if (tmpse = MenuEntryFind(Fs->cur_menu, "Misc/Opt2"))
							tmpse->checked = !tmpse->checked;
						break;
				}
				break;
		}

	}
	while (message_code != MESSAGE_KEY_DOWN || (arg1 != CH_SHIFT_ESC && arg1 != CH_ESC));

	MenuPop;
}

PullDownMenuDemo;
