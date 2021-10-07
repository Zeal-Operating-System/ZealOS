U0 MessageLoop()
{
	I64 arg1, arg2, message_code;
	"Use $LK,"message_code",A="MN:MESSAGE_CMD"$ defines in your programs instead of hardcoded nums.\n"
	"<ESC> to Exit\n";

	//We don't want the mouse buttons to reposition the cursor,
	//so we inhibit the window mgr from processing them.

	Fs->win_inhibit = WIF_SELF_MS_L | WIF_SELF_MS_R;

	do
	{
		message_code = MessageGet(&arg1, &arg2, ~(1 << MESSAGE_NULL));
		"CMD:%02X ARG1:%08X ARG2:%016X\n", message_code, arg1, arg2;
	}
	while (message_code != MESSAGE_KEY_DOWN || arg1 != CH_ESC && arg1 != CH_SHIFT_ESC);

	MessageGet(,, 1 << MESSAGE_KEY_UP);

	Fs->win_inhibit = WIG_USER_TASK_DEFAULT;
}

MessageLoop;

// Press <CTRL-SHIFT-L> and "Insert $LK,"ASCII",A="MN:CH_CTRLA"$/$LK,"ScanCode",A="FI:::/Doc/CharOverview.DD"$".
