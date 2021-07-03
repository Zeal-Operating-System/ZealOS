/* This converts $LK,"::/Demo/ToHtmlToTXTDemo/DemoInPage.DD"$ to
an html document named "OutPage.html".

Notice that an entry like $$TX,"GOOGLE",HTML="http://www.google.com"$$
will be converted to text in the html with an html link.

Terry cheated by hardcoding $LK,"www.templeos.org",A="FF:::/Demo/ToHtmlToTXTDemo/ToHtml.CC,www.templeos.org"$ as the website
for $LK,"ZealOS Links",A="MN:LK_FILE"$.  Why don't you copy
$LK,"::/Demo/ToHtmlToTXTDemo/ToHtml.CC"$ to your /Home directory
and modify it?	You are welcome to link to
http://www.templeos.org if you want file that come on the
ZealOS distribution.

You can pass html meta data as args to $LK,"ToHtml",A="FF:::/Demo/ToHtmlToTXTDemo/ToHtml.CC,ToHtml"$().
*/

Cd(__DIR__);;
#include "ToHtml"

//ToHtml("DemoInPage.DD", "~/DemoOutPage");

I64	Dir2Html(U8 *src_files_find_mask, U8 *dst_files_find_mask)
{
	CDirEntry	*tmpde1 = NULL, *tmpde2;
	I64			 res = 0;
	U8			*dest_path, *dest_file, *dest_abs;

	tmpde1 = FilesFind(src_files_find_mask);
	dest_abs = DirNameAbs(dst_files_find_mask);

	if (tmpde1)
	{
		while (tmpde1)
		{
			tmpde2 = tmpde1->next;
			res++;

			dest_file = StrNew(tmpde1->name);
			FileExtRemove(dest_file);

			dest_path = MStrPrint("%s/%s", dest_abs, dest_file);

			if (!(tmpde1->attr & RS_ATTR_DIR)	&&
				StrCompare(DirFile(dest_path), DirFile(tmpde1->full_name)))
			{
				ToHtml(tmpde1->full_name, dest_path);
//				PutFileLink(tmpde1->name, tmpde1->full_name);
			}

			DirEntryDel(tmpde1);
			tmpde1 = tmpde2;

			Free(dest_path);
			Free(dest_file);
		}
	}

	Free(dest_abs);

	return res;
}

Dir2Html("::/", "::/HTML/");