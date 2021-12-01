/*You probably don't need this.  It makes a directory
tree into a flat contiguous memory chunk, suitable for
serial communication and rebuilds it into a tree on the
other end.
*/

U0 SerializeTree()
{
	CDirEntry	*tmpde = FilesFind("/Demo/*.DD*", FUF_RECURSE);
	I64			 size;
	U8			*ptr;

	LineRep1(tmpde); //We have $LK,"CDirEntry",A="MN:CDirEntry"$.fullname
	LineRep2(DocPut, tmpde);
	"$$GREEN$$***************$$FG$$\n";
	ptr = DirTreeSerialize(tmpde, &size);
	DirTreeDel(tmpde);
	Dump(ptr, size);
	"$$GREEN$$***************:%7d$$FG$$\n", size;
	tmpde = DirTreeUnserialize(ptr);
	LineRep2(DocPut, tmpde); //We don't have $LK,"CDirEntry",A="MN:CDirEntry"$.fullname
	DirTreeDel(tmpde);
}

SerializeTree;
