

public U0 PaletteSelect()
{
	CDirEntry	*tmpde1 = NULL, *tmpde2;

	CDoc *doc = DocNew;
	I64  res  =	0;

	DocPrint(doc, "$$LTBLUE$$\n\n");

	tmpde1 = FilesFind("~/PaletteEditor/Palettes/*.CC");


	if (tmpde1)
	{
		while (tmpde1)
		{
			tmpde2 = tmpde1->next;
			res++;

			FileExtRemove(tmpde1->name);

			DocPrint(doc, "  $$MU,\"%d.%s\",LE=0x%X$$\n",res, tmpde1->name, tmpde1->name);								
			DirEntryDel(tmpde1);

			tmpde1 = tmpde2;
		}


	}

	DocPrint(doc, "\n\n$$BT+CX,\"CANCEL\",LE=DOCM_CANCEL$$\n\n");
	res = PopUpMenu(doc);
	DocDel(doc);	

	if (res != (DOCM_CANCEL || 0)) PaletteSet(res, TRUE);
}


PaletteSelect;