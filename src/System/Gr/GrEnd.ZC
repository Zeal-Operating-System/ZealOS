#help_index "Graphics/Screen"

U0 CtrlAltZ(I64 sc)
{
	if (sc & SCF_SHIFT)
		GrScaleZoom(0.5);
	else
		GrScaleZoom(2.0);
	LFBFlush;
}
CtrlAltCBSet('Z', &CtrlAltZ, "Cmd /Zoom In", "Cmd /Zoom Out");

U0 Screen2Clip(I64)
{
	CDC *dc = DCScreenCapture;
	U8	*elems = DC2Sprite(dc);
	Bool unlock_doc = DocLock(sys_clip_doc);

	ClipDel;
	DocSprite(sys_clip_doc, elems);
	if (unlock_doc)
		DocUnlock(sys_clip_doc);
	Free(elems);
	DCDel(dc);
}
U0 CtrlAltS(I64)
{
	Spawn(&Screen2Clip);
}
CtrlAltCBSet('S', &CtrlAltS, "Cmd /Screen Shot to Clip");
