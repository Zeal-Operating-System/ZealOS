<!DOCTYPE HTML>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html;charset=US-ASCII">
<meta name="generator" content="ZealOS V0.05">
<style type="text/css">
body {background-color:#000000;}
.cF0{color:#ffffff;background-color:#000000;}
.cF1{color:#3465a4;background-color:#000000;}
.cF2{color:#4e9a06;background-color:#000000;}
.cF3{color:#06989a;background-color:#000000;}
.cF4{color:#a24444;background-color:#000000;}
.cF5{color:#75507b;background-color:#000000;}
.cF6{color:#ce982f;background-color:#000000;}
.cF7{color:#bcc0b9;background-color:#000000;}
.cF8{color:#555753;background-color:#000000;}
.cF9{color:#729fcf;background-color:#000000;}
.cFA{color:#82bc49;background-color:#000000;}
.cFB{color:#34e2e2;background-color:#000000;}
.cFC{color:#ac3535;background-color:#000000;}
.cFD{color:#ad7fa8;background-color:#000000;}
.cFE{color:#fce94f;background-color:#000000;}
.cFF{color:#000000;background-color:#000000;}
</style>
</head>
<body>
<pre style="font-family:monospace;font-size:12pt">
<a name="l1"></a><span class=cF1>Bool</span><span class=cF0> </span><span class=cF5>DirNew</span><span class=cF0>(</span><span class=cF9>CDrive</span><span class=cF0> *drive, </span><span class=cF1>U8</span><span class=cF0> *cur_dir, </span><span class=cF9>CDirEntry</span><span class=cF0> *tmpde, </span><span class=cF1>Bool</span><span class=cF0> free_old_chain=</span><span class=cF3>TRUE</span><span class=cF0>)
<a name="l2"></a>{</span><span class=cF2>//Makes a directory entry in the directory from a </span><a href="https://tomawezome.github.io/ZealOS/Kernel/KernelA.html#l3167"><span class=cF4>CDirEntry</span></a><span class=cF2> node.</span><span class=cF0>
<a name="l3"></a>    </span><span class=cF1>switch</span><span class=cF0> (drive-&gt;fs_type)
<a name="l4"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l5"></a>        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>FSt_REDSEA</span><span class=cF0>:
<a name="l6"></a>            </span><span class=cF1>return</span><span class=cF0> </span><span class=cFD>RedSeaDirNew</span><span class=cF0>(drive, cur_dir, tmpde, free_old_chain);
<a name="l7"></a>
<a name="l8"></a>        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>FSt_FAT32</span><span class=cF0>:
<a name="l9"></a>            </span><span class=cF1>return</span><span class=cF0> </span><span class=cFD>FAT32DirNew</span><span class=cF0>(drive, cur_dir, tmpde, free_old_chain);
<a name="l10"></a>
<a name="l11"></a>        </span><span class=cF1>default</span><span class=cF0>:
<a name="l12"></a>            </span><span class=cF5>PrintErr</span><span class=cF0>(</span><span class=cF6>&quot;File System Not Supported\n&quot;</span><span class=cF0>);
<a name="l13"></a>            </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l14"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l15"></a>}
<a name="l16"></a>
<a name="l17"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>DirEntryDel</span><span class=cF0>(</span><span class=cF9>CDirEntry</span><span class=cF0> *tmpde)
<a name="l18"></a>{</span><span class=cF2>//Free node returned from </span><a href="https://tomawezome.github.io/ZealOS/Kernel/BlkDev/DiskFind.html#l32"><span class=cF4>FilesFind</span></a><span class=cF2>().  Doesn't Free user_data.</span><span class=cF0>
<a name="l19"></a></span><span class=cF2>//Does not change the directory on disk.</span><span class=cF0>
<a name="l20"></a>    </span><span class=cF1>if</span><span class=cF0> (tmpde)
<a name="l21"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l22"></a>        </span><span class=cF5>Free</span><span class=cF0>(tmpde-&gt;full_name);
<a name="l23"></a>        </span><span class=cF5>Free</span><span class=cF0>(tmpde);
<a name="l24"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l25"></a>}
<a name="l26"></a>
<a name="l27"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>DirEntryDel2</span><span class=cF0>(</span><span class=cF9>CDirEntry</span><span class=cF0> *tmpde)
<a name="l28"></a>{</span><span class=cF2>//Free node returned from </span><a href="https://tomawezome.github.io/ZealOS/Kernel/BlkDev/DiskFind.html#l32"><span class=cF4>FilesFind</span></a><span class=cF2>().  Frees user_data</span><span class=cF0>
<a name="l29"></a></span><span class=cF2>//Does not change the directory on disk.</span><span class=cF0>
<a name="l30"></a>    </span><span class=cF1>if</span><span class=cF0> (tmpde)
<a name="l31"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l32"></a>        </span><span class=cF5>Free</span><span class=cF0>(tmpde-&gt;full_name);
<a name="l33"></a>        </span><span class=cF5>Free</span><span class=cF0>(tmpde-&gt;user_data);
<a name="l34"></a>        </span><span class=cF5>Free</span><span class=cF0>(tmpde);
<a name="l35"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l36"></a>}
<a name="l37"></a>
<a name="l38"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>DirTreeDel</span><span class=cF0>(</span><span class=cF9>CDirEntry</span><span class=cF0> *tmpde)
<a name="l39"></a>{</span><span class=cF2>//Free tree returned from </span><a href="https://tomawezome.github.io/ZealOS/Kernel/BlkDev/DiskFind.html#l32"><span class=cF4>FilesFind</span></a><span class=cF2>().  Doesn't Free user_data.</span><span class=cF0>
<a name="l40"></a></span><span class=cF2>//Does not change the directory on disk.</span><span class=cF0>
<a name="l41"></a>    </span><span class=cF9>CDirEntry</span><span class=cF0> *tmpde2;
<a name="l42"></a>
<a name="l43"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpde)
<a name="l44"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l45"></a>        tmpde2 = tmpde-&gt;next;
<a name="l46"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpde-&gt;sub)
<a name="l47"></a>            </span><span class=cF5>DirTreeDel</span><span class=cF0>(tmpde-&gt;sub);
<a name="l48"></a>        </span><span class=cF5>DirEntryDel</span><span class=cF0>(tmpde);
<a name="l49"></a>        tmpde = tmpde2;
<a name="l50"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l51"></a>}
<a name="l52"></a>
<a name="l53"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>DirTreeDel2</span><span class=cF0>(</span><span class=cF9>CDirEntry</span><span class=cF0> *tmpde)
<a name="l54"></a>{</span><span class=cF2>//Free tree returned from </span><a href="https://tomawezome.github.io/ZealOS/Kernel/BlkDev/DiskFind.html#l32"><span class=cF4>FilesFind</span></a><span class=cF2>().  Frees user_data</span><span class=cF0>
<a name="l55"></a></span><span class=cF2>//Does not change the directory on disk.</span><span class=cF0>
<a name="l56"></a>    </span><span class=cF9>CDirEntry</span><span class=cF0> *tmpde2;
<a name="l57"></a>
<a name="l58"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpde)
<a name="l59"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l60"></a>        tmpde2 = tmpde-&gt;next;
<a name="l61"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpde-&gt;sub)
<a name="l62"></a>            </span><span class=cF5>DirTreeDel2</span><span class=cF0>(tmpde-&gt;sub);
<a name="l63"></a>        </span><span class=cF5>DirEntryDel2</span><span class=cF0>(tmpde);
<a name="l64"></a>        tmpde = tmpde2;
<a name="l65"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l66"></a>}
<a name="l67"></a>
<a name="l68"></a></span><span class=cF9>I64</span><span class=cF0> </span><span class=cFD>DirEntryCompareName</span><span class=cF0>(</span><span class=cF9>CDirEntry</span><span class=cF0> *e1, </span><span class=cF9>CDirEntry</span><span class=cF0> *e2)
<a name="l69"></a>{
<a name="l70"></a>    </span><span class=cF1>U8</span><span class=cF0>  buf1[</span><span class=cF3>CDIR_FILENAME_LEN</span><span class=cF0>], buf2[</span><span class=cF3>CDIR_FILENAME_LEN</span><span class=cF0>], buf3[</span><span class=cF3>CDIR_FILENAME_LEN</span><span class=cF0>], buf4[</span><span class=cF3>CDIR_FILENAME_LEN</span><span class=cF0>];
<a name="l71"></a>    </span><span class=cF9>I64</span><span class=cF0> d1 = </span><span class=cFE>0</span><span class=cF0>, d2 = </span><span class=cFE>0</span><span class=cF0>;
<a name="l72"></a>
<a name="l73"></a>    </span><span class=cF1>if</span><span class=cF0> (e1-&gt;attr &amp; </span><span class=cF3>RS_ATTR_DIR</span><span class=cF0>)
<a name="l74"></a>        d1 = </span><span class=cFE>1</span><span class=cF0>;
<a name="l75"></a>    </span><span class=cF1>if</span><span class=cF0> (e2-&gt;attr &amp; </span><span class=cF3>RS_ATTR_DIR</span><span class=cF0>)
<a name="l76"></a>        d2 = </span><span class=cFE>1</span><span class=cF0>;
<a name="l77"></a>    </span><span class=cF1>if</span><span class=cF0> (d1 != d2)
<a name="l78"></a>        </span><span class=cF1>return</span><span class=cF0> d2-d1;
<a name="l79"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l80"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l81"></a>        </span><span class=cF5>StrCopy</span><span class=cF0>(buf1, e1-&gt;name);
<a name="l82"></a>        </span><span class=cF5>StrCopy</span><span class=cF0>(buf2, e2-&gt;name);
<a name="l83"></a>        </span><span class=cF5>FileExtRemove</span><span class=cF0>(buf1, buf3);
<a name="l84"></a>        </span><span class=cF5>FileExtRemove</span><span class=cF0>(buf2, buf4);
<a name="l85"></a>        </span><span class=cF1>if</span><span class=cF0> (d1 = </span><span class=cF5>StrCompare</span><span class=cF7>(</span><span class=cF0>buf3, buf4</span><span class=cF7>)</span><span class=cF0>)
<a name="l86"></a>            </span><span class=cF1>return</span><span class=cF0> d1;
<a name="l87"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF5>StrCompare</span><span class=cF0>(buf1, buf2);
<a name="l88"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l89"></a>}
<a name="l90"></a>
<a name="l91"></a></span><span class=cF9>I64</span><span class=cF0> </span><span class=cFD>DirEntryCompareClus</span><span class=cF0>(</span><span class=cF9>CDirEntry</span><span class=cF0> *e1, </span><span class=cF9>CDirEntry</span><span class=cF0> *e2)
<a name="l92"></a>{
<a name="l93"></a>    </span><span class=cF1>return</span><span class=cF0> e1-&gt;clus - e2-&gt;clus;
<a name="l94"></a>}
<a name="l95"></a>
<a name="l96"></a>#</span><span class=cF1>define</span><span class=cF0> SK_NAME </span><span class=cFE>0</span><span class=cF0>
<a name="l97"></a>#</span><span class=cF1>define</span><span class=cF0> SK_CLUS </span><span class=cFE>1</span><span class=cF0>
<a name="l98"></a>
<a name="l99"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cFD>DirFilesSort</span><span class=cF0>(</span><span class=cF9>CDirEntry</span><span class=cF0> **_tmpde, </span><span class=cF9>I64</span><span class=cF0> key)
<a name="l100"></a>{
<a name="l101"></a>    </span><span class=cF9>I64</span><span class=cF0>          i, count;
<a name="l102"></a>    </span><span class=cF9>CDirEntry</span><span class=cF0>   *tmpde = *_tmpde, *tmpde1, **sort_buf;
<a name="l103"></a>
<a name="l104"></a>    </span><span class=cF1>if</span><span class=cF0> (tmpde)
<a name="l105"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l106"></a>        count = </span><span class=cF5>LinkedListCount</span><span class=cF0>(tmpde);
<a name="l107"></a>        </span><span class=cF1>if</span><span class=cF0> (count &gt; </span><span class=cFE>1</span><span class=cF0>)
<a name="l108"></a>        {
<a name="l109"></a>            sort_buf = </span><span class=cF5>MAlloc</span><span class=cF0>(count * </span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>);
<a name="l110"></a>            i = </span><span class=cFE>0</span><span class=cF0>;
<a name="l111"></a>            tmpde1 = tmpde;
<a name="l112"></a>            </span><span class=cF1>while</span><span class=cF0> (tmpde1)
<a name="l113"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l114"></a>                sort_buf[i++] = tmpde1;
<a name="l115"></a>                tmpde1 = tmpde1-&gt;next;
<a name="l116"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l117"></a>            </span><span class=cF1>switch</span><span class=cF0> [key]
<a name="l118"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l119"></a>                </span><span class=cF1>case</span><span class=cF0> SK_NAME:
<a name="l120"></a>                    </span><span class=cF5>QuickSortI64</span><span class=cF0>(sort_buf, count, &amp;</span><span class=cFD>DirEntryCompareName</span><span class=cF0>);
<a name="l121"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l122"></a>
<a name="l123"></a>                </span><span class=cF1>case</span><span class=cF0> SK_CLUS:
<a name="l124"></a>                    </span><span class=cF5>QuickSortI64</span><span class=cF0>(sort_buf, count, &amp;</span><span class=cFD>DirEntryCompareClus</span><span class=cF0>);
<a name="l125"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l126"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l127"></a>            tmpde = sort_buf[</span><span class=cFE>0</span><span class=cF0>];
<a name="l128"></a>            *_tmpde = tmpde;
<a name="l129"></a>            </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; count - </span><span class=cFE>1</span><span class=cF0>; i++)
<a name="l130"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l131"></a>                tmpde1 = sort_buf[i];
<a name="l132"></a>                tmpde1-&gt;next = sort_buf[i + </span><span class=cFE>1</span><span class=cF0>];
<a name="l133"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l134"></a>            tmpde1 = sort_buf[i];
<a name="l135"></a>            tmpde1-&gt;next = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l136"></a>            </span><span class=cF5>Free</span><span class=cF0>(sort_buf);
<a name="l137"></a>
<a name="l138"></a>            tmpde1 = tmpde;
<a name="l139"></a>            </span><span class=cF1>while</span><span class=cF0> (tmpde1)
<a name="l140"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l141"></a>                </span><span class=cF1>if</span><span class=cF0> (tmpde1-&gt;sub)
<a name="l142"></a>                    </span><span class=cFD>DirFilesSort</span><span class=cF0>(&amp;tmpde1-&gt;sub, key);
<a name="l143"></a>                tmpde1 = tmpde1-&gt;next;
<a name="l144"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l145"></a>        }
<a name="l146"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l147"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpde-&gt;sub)
<a name="l148"></a>                </span><span class=cFD>DirFilesSort</span><span class=cF0>(&amp;tmpde-&gt;sub, key);
<a name="l149"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l150"></a>}
<a name="l151"></a>
<a name="l152"></a></span><span class=cF9>CDirEntry</span><span class=cF0> *</span><span class=cFD>DirFilesFlatten</span><span class=cF0>(</span><span class=cF9>CDirEntry</span><span class=cF0> *tmpde, </span><span class=cF9>CDirEntry</span><span class=cF0> **_res, </span><span class=cF9>I64</span><span class=cF0> fuf_flags)
<a name="l153"></a>{</span><span class=cF2>//Returns last node</span><span class=cF0>
<a name="l154"></a>    </span><span class=cF9>CDirEntry</span><span class=cF0>   *tmpde1;
<a name="l155"></a>    </span><span class=cF1>Bool</span><span class=cF0>         del;
<a name="l156"></a>
<a name="l157"></a>    </span><span class=cF1>if</span><span class=cF0> (tmpde)
<a name="l158"></a>        </span><span class=cF1>while</span><span class=cF0> (</span><span class=cF3>TRUE</span><span class=cF0>)
<a name="l159"></a>        </span><span class=cF7>{</span><span class=cF0>
<a name="l160"></a>            tmpde1 = tmpde-&gt;next;
<a name="l161"></a>            </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>tmpde-&gt;attr &amp; </span><span class=cF3>RS_ATTR_DIR</span><span class=cF7>)</span><span class=cF0> || !</span><span class=cF7>(</span><span class=cF0>fuf_flags &amp; </span><span class=cF3>FUF_JUST_FILES</span><span class=cF7>)</span><span class=cF0>)
<a name="l162"></a>            {
<a name="l163"></a>                _res = *_res = tmpde;
<a name="l164"></a>                del = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l165"></a>            }
<a name="l166"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l167"></a>                del = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l168"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpde-&gt;sub)
<a name="l169"></a>            {
<a name="l170"></a>                _res = </span><span class=cFD>DirFilesFlatten</span><span class=cF0>(tmpde-&gt;sub, _res, fuf_flags);
<a name="l171"></a>                tmpde-&gt;sub = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l172"></a>            }
<a name="l173"></a>            </span><span class=cF1>if</span><span class=cF0> (del)
<a name="l174"></a>                </span><span class=cF5>DirEntryDel</span><span class=cF0>(tmpde);
<a name="l175"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpde1)
<a name="l176"></a>                tmpde = tmpde1;
<a name="l177"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l178"></a>                </span><span class=cF1>break</span><span class=cF0>;
<a name="l179"></a>        </span><span class=cF7>}</span><span class=cF0>
<a name="l180"></a>    *_res = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l181"></a>    </span><span class=cF1>return</span><span class=cF0> _res;
<a name="l182"></a>}
<a name="l183"></a>
<a name="l184"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>PutFileLink</span><span class=cF0>(</span><span class=cF1>U8</span><span class=cF0> *filename, </span><span class=cF1>U8</span><span class=cF0> *full_name=</span><span class=cF3>NULL</span><span class=cF0>, </span><span class=cF9>I64</span><span class=cF0> line=</span><span class=cFE>0</span><span class=cF0>, </span><span class=cF1>Bool</span><span class=cF0> plain_text=</span><span class=cF3>FALSE</span><span class=cF0>)
<a name="l185"></a>{</span><span class=cF2>//Put </span><a href="https://tomawezome.github.io/ZealOS/Doc/DolDocOverview.html#l1"><span class=cF4>DolDoc</span></a><span class=cF2> file,line link to StdOut, </span><a href="https://tomawezome.github.io/ZealOS/System/DolDoc/DocDblBuf.html#l2"><span class=cF4>DocPut</span></a><span class=cF2>.</span><span class=cF0>
<a name="l186"></a>    </span><span class=cF1>U8</span><span class=cF0> *st;
<a name="l187"></a>
<a name="l188"></a>    </span><span class=cF1>if</span><span class=cF0> (!filename)
<a name="l189"></a>        </span><span class=cF1>return</span><span class=cF0>;
<a name="l190"></a>    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>IsRaw</span><span class=cF0>)
<a name="l191"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l192"></a>        </span><span class=cF1>if</span><span class=cF0> (line)
<a name="l193"></a>            </span><span class=cF6>&quot;%s,%04d&quot;</span><span class=cF0>, filename, line;
<a name="l194"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l195"></a>            </span><span class=cF6>&quot;%s&quot;</span><span class=cF0>, filename;
<a name="l196"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l197"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l198"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l199"></a></span><span class=cF2>//LK_DOC,LK_DOC_ANCHOR,LK_DOC_FIND,LK_DOC_LINE</span><span class=cF0>
<a name="l200"></a>        </span><span class=cF1>if</span><span class=cF0> (filename[</span><span class=cFE>0</span><span class=cF0>] == </span><span class=cF6>'A'</span><span class=cF0>&amp;&amp;filename[</span><span class=cFE>2</span><span class=cF0>] == </span><span class=cF6>':'</span><span class=cF0>)
<a name="l201"></a>        {
<a name="l202"></a>            </span><span class=cF1>if</span><span class=cF0> (line) </span><span class=cF2>//See </span><a href="https://tomawezome.github.io/ZealOS/System/Gr/SpriteEd.html#l701"><span class=cF4>SpriteEdText</span></a><span class=cF2>()</span><span class=cF0>
<a name="l203"></a>                </span><span class=cF6>&quot;$LK,\&quot;%s,%04d\&quot;,A=\&quot;AL:%s,%d\&quot;$&quot;</span><span class=cF0>, filename + </span><span class=cFE>3</span><span class=cF0>, line, filename + </span><span class=cFE>3</span><span class=cF0>, line;
<a name="l204"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l205"></a>                </span><span class=cF6>&quot;$LK,\&quot;%s\&quot;,A=\&quot;AI:%s\&quot;$&quot;</span><span class=cF0>, filename + </span><span class=cFE>3</span><span class=cF0>, filename + </span><span class=cFE>3</span><span class=cF0>;
<a name="l206"></a>        }
<a name="l207"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l208"></a>        {
<a name="l209"></a>            </span><span class=cF1>if</span><span class=cF0> (!full_name)
<a name="l210"></a>                full_name = st = </span><span class=cF5>FileNameAbs</span><span class=cF0>(filename);
<a name="l211"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l212"></a>                st = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l213"></a>            </span><span class=cF1>if</span><span class=cF0> (plain_text)
<a name="l214"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l215"></a>                </span><span class=cF1>if</span><span class=cF0> (line)
<a name="l216"></a>                    </span><span class=cF6>&quot;$LK,\&quot;%s,%04d\&quot;,A=\&quot;PL:%s,%d\&quot;$&quot;</span><span class=cF0>, filename, line, full_name, line;
<a name="l217"></a>                </span><span class=cF1>else</span><span class=cF0>
<a name="l218"></a>                    </span><span class=cF6>&quot;$LK,\&quot;%s\&quot;,A=\&quot;PI:%s\&quot;$&quot;</span><span class=cF0>, filename, full_name;
<a name="l219"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l220"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l221"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l222"></a>                </span><span class=cF1>if</span><span class=cF0> (line)
<a name="l223"></a>                    </span><span class=cF6>&quot;$LK,\&quot;%s,%04d\&quot;,A=\&quot;FL:%s,%d\&quot;$&quot;</span><span class=cF0>, filename, line, full_name, line;
<a name="l224"></a>                </span><span class=cF1>else</span><span class=cF0>
<a name="l225"></a>                    </span><span class=cF6>&quot;$LK,\&quot;%s\&quot;,A=\&quot;FI:%s\&quot;$&quot;</span><span class=cF0>, filename, full_name;
<a name="l226"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l227"></a>            </span><span class=cF5>Free</span><span class=cF0>(st);
<a name="l228"></a>        }
<a name="l229"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l230"></a>}
<a name="l231"></a>
<a name="l232"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>PutDirLink</span><span class=cF0>(</span><span class=cF1>U8</span><span class=cF0> *dirname, </span><span class=cF1>U8</span><span class=cF0> *full_name=</span><span class=cF3>NULL</span><span class=cF0>)
<a name="l233"></a>{</span><span class=cF2>//Put </span><a href="https://tomawezome.github.io/ZealOS/Doc/DolDocOverview.html#l1"><span class=cF4>DolDoc</span></a><span class=cF2> dir macro to StdOut, </span><a href="https://tomawezome.github.io/ZealOS/System/DolDoc/DocDblBuf.html#l2"><span class=cF4>DocPut</span></a><span class=cF2>.</span><span class=cF0>
<a name="l234"></a>    </span><span class=cF1>U8</span><span class=cF0> *st;
<a name="l235"></a>
<a name="l236"></a>    </span><span class=cF1>if</span><span class=cF0> (!dirname)
<a name="l237"></a>        </span><span class=cF1>return</span><span class=cF0>;
<a name="l238"></a>    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>IsRaw</span><span class=cF0>)
<a name="l239"></a>        </span><span class=cF6>&quot;%s&quot;</span><span class=cF0>, dirname;
<a name="l240"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l241"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l242"></a>        </span><span class=cF1>if</span><span class=cF0> (!full_name)
<a name="l243"></a>            full_name = st = </span><span class=cF5>DirNameAbs</span><span class=cF0>(dirname);
<a name="l244"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l245"></a>            st = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l246"></a>        </span><span class=cF6>&quot;$MA,T=\&quot;%s\&quot;,LM=\&quot;Cd(\\\&quot;%s\\\&quot;);Dir;\n\&quot;$&quot;</span><span class=cF0>, dirname, full_name;
<a name="l247"></a>        </span><span class=cF5>Free</span><span class=cF0>(st);
<a name="l248"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l249"></a>}
</span></pre></body>
</html>
