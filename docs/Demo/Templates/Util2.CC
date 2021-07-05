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
<a name="l1"></a><span class=cF9>I64</span><span class=cF0> MyUtilDoc(</span><span class=cF9>CDoc</span><span class=cF0> *doc, </span><span class=cF9>I64</span><span class=cF0> fuf_flags)
<a name="l2"></a>{
<a name="l3"></a>    </span><span class=cF1>Bool</span><span class=cF0>         unlock = </span><span class=cF5>DocLock</span><span class=cF0>(doc);
<a name="l4"></a>    </span><span class=cF9>I64</span><span class=cF0>          res = </span><span class=cFE>0</span><span class=cF0>;
<a name="l5"></a>    </span><span class=cF9>CDocEntry</span><span class=cF0>   *doc_e;
<a name="l6"></a>
<a name="l7"></a>    </span><span class=cF5>DocRecalc</span><span class=cF0>(doc);
<a name="l8"></a>    doc_e = doc-&gt;head.next;
<a name="l9"></a>    </span><span class=cF1>while</span><span class=cF0> (doc_e != doc)
<a name="l10"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l11"></a>        res++;
<a name="l12"></a>        doc_e = doc_e-&gt;next;
<a name="l13"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l14"></a>    </span><span class=cF5>DocRecalc</span><span class=cF0>(doc);
<a name="l15"></a>    </span><span class=cF1>if</span><span class=cF0> (unlock)
<a name="l16"></a>        </span><span class=cF5>DocUnlock</span><span class=cF0>(doc);
<a name="l17"></a>
<a name="l18"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l19"></a>}
<a name="l20"></a>
<a name="l21"></a></span><span class=cF9>I64</span><span class=cF0> MyUtilFile(</span><span class=cF1>U8</span><span class=cF0> *filename, </span><span class=cF9>I64</span><span class=cF0> fuf_flags)
<a name="l22"></a>{
<a name="l23"></a>    </span><span class=cF9>I64</span><span class=cF0>   res;
<a name="l24"></a>    </span><span class=cF9>CDoc</span><span class=cF0> *doc = </span><span class=cF5>DocRead</span><span class=cF0>(filename);
<a name="l25"></a>
<a name="l26"></a>    </span><span class=cF1>if</span><span class=cF0> (res = MyUtilDoc</span><span class=cF7>(</span><span class=cF0>doc, fuf_flags</span><span class=cF7>)</span><span class=cF0>)
<a name="l27"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l28"></a>        </span><span class=cF6>&quot;%8d:%s\n&quot;</span><span class=cF0>, res, doc-&gt;filename.name;
<a name="l29"></a>        </span><span class=cF5>DocWrite</span><span class=cF0>(doc);
<a name="l30"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l31"></a>    </span><span class=cF5>DocDel</span><span class=cF0>(doc);
<a name="l32"></a>
<a name="l33"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l34"></a>}
<a name="l35"></a></span><span class=cF9>I64</span><span class=cF0> MyUtilList(</span><span class=cF9>CDirEntry</span><span class=cF0> *tmpde, </span><span class=cF9>I64</span><span class=cF0> fuf_flags)
<a name="l36"></a>{
<a name="l37"></a>    </span><span class=cF9>I64</span><span class=cF0>          res = </span><span class=cFE>0</span><span class=cF0>;
<a name="l38"></a>    </span><span class=cF9>CDirEntry</span><span class=cF0>   *tmpde1;
<a name="l39"></a>
<a name="l40"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpde)
<a name="l41"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l42"></a>        tmpde1 = tmpde-&gt;next;
<a name="l43"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpde-&gt;attr &amp; </span><span class=cF3>RS_ATTR_DIR</span><span class=cF0>)
<a name="l44"></a>        {
<a name="l45"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpde-&gt;sub)
<a name="l46"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l47"></a>                </span><span class=cF6>&quot;Processing Directory: %s\n&quot;</span><span class=cF0>, tmpde-&gt;full_name;
<a name="l48"></a>                res += MyUtilList(tmpde-&gt;sub, fuf_flags);
<a name="l49"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l50"></a>        }
<a name="l51"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l52"></a>            res += MyUtilFile(tmpde-&gt;full_name, fuf_flags);
<a name="l53"></a>        </span><span class=cF5>DirEntryDel</span><span class=cF0>(tmpde);
<a name="l54"></a>        tmpde = tmpde1;
<a name="l55"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l56"></a>
<a name="l57"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l58"></a>}
<a name="l59"></a></span><span class=cF9>I64</span><span class=cF0> MyUtil(</span><span class=cF1>U8</span><span class=cF0> *files_find_mask=</span><span class=cF6>&quot;*&quot;</span><span class=cF0>, </span><span class=cF1>U8</span><span class=cF0> *fu_flags=</span><span class=cF3>NULL</span><span class=cF0>)
<a name="l60"></a>{
<a name="l61"></a>    </span><span class=cF9>I64</span><span class=cF0> fuf_flags = </span><span class=cFE>0</span><span class=cF0>;
<a name="l62"></a>
<a name="l63"></a>    </span><span class=cF5>FlagsScan</span><span class=cF0>(&amp;fuf_flags, </span><span class=cF5>Define</span><span class=cF7>(</span><span class=cF6>&quot;ST_FILE_UTIL_FLAGS&quot;</span><span class=cF7>)</span><span class=cF0>, </span><span class=cF6>&quot;+r+$&quot;</span><span class=cF0>);
<a name="l64"></a>    </span><span class=cF5>FlagsScan</span><span class=cF0>(&amp;fuf_flags, </span><span class=cF5>Define</span><span class=cF7>(</span><span class=cF6>&quot;ST_FILE_UTIL_FLAGS&quot;</span><span class=cF7>)</span><span class=cF0>, fu_flags);
<a name="l65"></a>
<a name="l66"></a>    </span><span class=cF1>return</span><span class=cF0> MyUtilList(</span><span class=cF5>FilesFind</span><span class=cF7>(</span><span class=cF0>files_find_mask, fuf_flags &amp; </span><span class=cF3>FUG_FILES_FIND</span><span class=cF7>)</span><span class=cF0>, fuf_flags &amp; ~</span><span class=cF3>FUG_FILES_FIND</span><span class=cF0>);
<a name="l67"></a>}
</span></pre></body>
</html>
