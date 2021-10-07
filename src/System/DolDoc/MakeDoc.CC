Cd(__DIR__);;

#help_index "DolDoc"
#help_file "::/Doc/DolDoc"

/*
ZealOS DolDoc's can have "cursor movement" cmds which can move the cursor up
the screen and layer on existing text.  It can also have callback functions which
supply live, changing text.  For these reasons, you can't assume you know
where the vis portion of the document is and must process much
of the document each time it is placed on the screen, becoming CPU
intensive on big documents.
See $LK,"::/Doc/DolDocOverview.DD"$
*/

//Hash Types
#define DHT_DOC_CMD 		1
#define DHT_DOC_FLAG		2
#define DHT_COLOR 			4

public class CDolDocGlobals
{
	CHashTable	*hash;
	I64			 default_de_flags			[DOCT_TYPES_NUM],
				 type_flags_nontag_invis	[(DOCT_TYPES_NUM + 63) / 64],
				 type_flags_form 			[(DOCT_TYPES_NUM + 63) / 64],
				 type_flags_data 			[(DOCT_TYPES_NUM + 63) / 64],
				 type_flags_chk_dup			[(DOCT_TYPES_NUM + 63) / 64],
				 clean_scan_codes			[4];
	I32			 default_type_flags			[DOCT_TYPES_NUM];
} doldoc;
MemSet(&doldoc, 0, sizeof(CDolDocGlobals));

#help_index "God"
#define BIBLE_FILENAME	"::/Misc/Bible.TXT"

#include "DocExterns"
#include "DocBin"
#include "DocNew"
#include "DocForm"
#include "DocDblBuf"
#include "DocPlain"
#include "DocInit"
#include "DocHighlight"
#include "DocRecalcLib"
#include "DocRecalc"
#include "DocFile"
#include "DocClipBoard"
#include "DocRun"
#include "DocGet"
#include "DocChar"
#include "DocFind"
#include "DocLink"
#include "DocEd"
#include "DocPopUp"
#include "DocGr"
#include "DocMacro"
#include "DocWidgetWiz"
#include "DocPutKey"
#include "DocPutS"
#include "DocCodeTools"
#include "DocTree"
#include "DocTerm"

KeyDevAdd(&KDDocPutKey, &KDDocPutS, 0x80000000, TRUE);
fp_getstr2 = &DocGetStr2;
fp_doc_put = &DocPut;

Cd("..");;
