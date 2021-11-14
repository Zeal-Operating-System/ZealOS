#define PALETTES_PATH	"~/PaletteEditor/Palettes/"

public I64 PaletteSelect()
{
	CDirEntry	*tmpde1 = NULL, *tmpde2;

	CDoc *doc = DocNew;
	I64  res  =	0;
	I64  res2 = 0;

	DocPrint(doc, "$$LTBLUE$$\n\n");

	tmpde1 = FilesFind("~/PaletteEditor/Palettes/*.CC");


	if (tmpde1)
	{
		while (tmpde1)
		{
			tmpde2 = tmpde1->next;
			res++;

			FileExtRemove(tmpde1->name);

			DocPrint(doc, "  $$MU,\"%d.%s\",LE=0x%X$$\n", res, tmpde1->name, tmpde1->name);	
			DirEntryDel(tmpde1);

			tmpde1 = tmpde2;
		}


	}

	DocPrint(doc, "\n\n$$BT+CX,\"CANCEL\",LE=DOCM_CANCEL$$\n\n");
	res2 = PopUpMenu(doc);
	DocDel(doc);	

	if (res2 != (DOCM_CANCEL || 0)) PaletteSet(res2, TRUE);
	return res2;
}