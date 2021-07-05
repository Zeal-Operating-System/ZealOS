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
<a name="l1"></a><span class=cF0>#</span><span class=cF1>define</span><span class=cF0> DOWNLOAD_FILE1              </span><span class=cF6>&quot;TOS_Distro.ISO&quot;</span><span class=cF0>
<a name="l2"></a>#</span><span class=cF1>define</span><span class=cF0> DOWNLOAD_FILE1_SIZE         </span><span class=cFE>16000000</span><span class=cF0>
<a name="l3"></a>
<a name="l4"></a>#</span><span class=cF1>define</span><span class=cF0> HOURS_MAX                   (</span><span class=cFE>24</span><span class=cF0>*</span><span class=cFE>3</span><span class=cF0>)
<a name="l5"></a>
<a name="l6"></a></span><span class=cF1>class</span><span class=cF0> LogStruct
<a name="l7"></a>{
<a name="l8"></a>    LogStruct   *next, *last;
<a name="l9"></a>    LogStruct   *ip_num_left, *ip_num_right;
<a name="l10"></a>    </span><span class=cF9>U32</span><span class=cF0>          ip_num, code;
<a name="l11"></a>    </span><span class=cF9>I64</span><span class=cF0>          size;
<a name="l12"></a>    </span><span class=cF1>U8</span><span class=cF0>          *file, *link;
<a name="l13"></a>    </span><span class=cF9>CDate</span><span class=cF0>        datetime;
<a name="l14"></a>};
<a name="l15"></a>
<a name="l16"></a></span><span class=cF1>class</span><span class=cF0> LinkStruct
<a name="l17"></a>{
<a name="l18"></a>    LinkStruct  *left, *right;
<a name="l19"></a>    </span><span class=cF1>U8</span><span class=cF0>          *link, *file;
<a name="l20"></a>    </span><span class=cF9>I64</span><span class=cF0>          count;
<a name="l21"></a>};
<a name="l22"></a>
<a name="l23"></a></span><span class=cF1>class</span><span class=cF0> BlockedStruct
<a name="l24"></a>{
<a name="l25"></a>    BlockedStruct   *next, *last;
<a name="l26"></a>    </span><span class=cF9>U32</span><span class=cF0>              ip_num;
<a name="l27"></a>};
<a name="l28"></a>
<a name="l29"></a></span><span class=cF1>U0</span><span class=cF0> LogStructDel(LogStruct *tmplg)
<a name="l30"></a>{
<a name="l31"></a>    </span><span class=cF5>Free</span><span class=cF0>(tmplg-&gt;file);
<a name="l32"></a>    </span><span class=cF5>Free</span><span class=cF0>(tmplg-&gt;link);
<a name="l33"></a>    </span><span class=cF5>Free</span><span class=cF0>(tmplg);
<a name="l34"></a>}
<a name="l35"></a>
<a name="l36"></a></span><span class=cF1>U0</span><span class=cF0> ParseSingleLogFile(LogStruct *head, </span><span class=cF1>U8</span><span class=cF0> *name, </span><span class=cF9>CDate</span><span class=cF0> *_dstart, </span><span class=cF9>CDate</span><span class=cF0> *_dend)
<a name="l37"></a>{
<a name="l38"></a>    </span><span class=cF9>CDoc</span><span class=cF0>        *doc = </span><span class=cF5>DocRead</span><span class=cF0>(name, </span><span class=cF3>DOCF_PLAIN_TEXT_TABS</span><span class=cF0> | </span><span class=cF3>DOCF_DBL_DOLLARS</span><span class=cF0> | </span><span class=cF3>DOCF_NO_CURSOR</span><span class=cF0>);
<a name="l39"></a>    </span><span class=cF9>CDocEntry</span><span class=cF0>   *doc_e = doc-&gt;head.next;
<a name="l40"></a>    </span><span class=cF1>U8</span><span class=cF0>          *src, *src2, *mon_list = </span><span class=cF5>Define</span><span class=cF0>(</span><span class=cF6>&quot;ST_MONTHS&quot;</span><span class=cF0>);
<a name="l41"></a>    LogStruct   *tmplg;
<a name="l42"></a>    </span><span class=cF9>CDateStruct</span><span class=cF0>  ds;
<a name="l43"></a>    </span><span class=cF9>I64</span><span class=cF0> i;
<a name="l44"></a>
<a name="l45"></a>    </span><span class=cF6>&quot;%$Q\n&quot;</span><span class=cF0>, name;
<a name="l46"></a>    </span><span class=cF1>while</span><span class=cF0> (doc_e != doc)
<a name="l47"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l48"></a>        </span><span class=cF1>if</span><span class=cF0> (doc_e-&gt;type_u8 == </span><span class=cF3>DOCT_TEXT</span><span class=cF0>)
<a name="l49"></a>        {
<a name="l50"></a>            tmplg = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF0>LogStruct</span><span class=cF7>)</span><span class=cF0>);
<a name="l51"></a>            </span><span class=cF1>try</span><span class=cF0>
<a name="l52"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l53"></a>                src = doc_e-&gt;tag;
<a name="l54"></a>                tmplg-&gt;ip_num.u8[</span><span class=cFE>3</span><span class=cF0>] = </span><span class=cF5>Str2I64</span><span class=cF0>(src, </span><span class=cFE>10</span><span class=cF0>, &amp;src);
<a name="l55"></a>                </span><span class=cF1>if</span><span class=cF0> (*src++ != </span><span class=cF6>'.'</span><span class=cF0>) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l56"></a>                tmplg-&gt;ip_num.u8[</span><span class=cFE>2</span><span class=cF0>] = </span><span class=cF5>Str2I64</span><span class=cF0>(src, </span><span class=cFE>10</span><span class=cF0>, &amp;src);
<a name="l57"></a>                </span><span class=cF1>if</span><span class=cF0> (*src++ != </span><span class=cF6>'.'</span><span class=cF0>) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l58"></a>                tmplg-&gt;ip_num.u8[</span><span class=cFE>1</span><span class=cF0>] = </span><span class=cF5>Str2I64</span><span class=cF0>(src, </span><span class=cFE>10</span><span class=cF0>, &amp;src);
<a name="l59"></a>                </span><span class=cF1>if</span><span class=cF0> (*src++ != </span><span class=cF6>'.'</span><span class=cF0>) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l60"></a>                tmplg-&gt;ip_num.u8[</span><span class=cFE>0</span><span class=cF0>] = </span><span class=cF5>Str2I64</span><span class=cF0>(src, </span><span class=cFE>10</span><span class=cF0>, &amp;src);
<a name="l61"></a>
<a name="l62"></a>                </span><span class=cF1>do</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (!*src) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l63"></a>                </span><span class=cF1>while</span><span class=cF0> (*src++ != </span><span class=cF6>'['</span><span class=cF0>);
<a name="l64"></a>                </span><span class=cF5>MemSet</span><span class=cF0>(&amp;ds, </span><span class=cFE>0</span><span class=cF0>, </span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF9>CDateStruct</span><span class=cF7>)</span><span class=cF0>);
<a name="l65"></a>                ds.day_of_mon = </span><span class=cF5>Str2I64</span><span class=cF0>(src, </span><span class=cFE>10</span><span class=cF0>, &amp;src);
<a name="l66"></a>                </span><span class=cF1>if</span><span class=cF0> (*src++ != </span><span class=cF6>'/'</span><span class=cF0>) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l67"></a>                src2 = src;
<a name="l68"></a>                </span><span class=cF1>do</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (!*src2) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l69"></a>                </span><span class=cF1>while</span><span class=cF0> (*src2++ != </span><span class=cF6>'/'</span><span class=cF0>);
<a name="l70"></a>                * --src2 = </span><span class=cFE>0</span><span class=cF0>;
<a name="l71"></a>                ds.mon = </span><span class=cFE>1</span><span class=cF0> + </span><span class=cF5>ListMatch</span><span class=cF0>(src, mon_list, </span><span class=cF3>LMF_IGNORE_CASE</span><span class=cF0>);
<a name="l72"></a>                src = ++src2;
<a name="l73"></a>                ds.year = </span><span class=cF5>Str2I64</span><span class=cF0>(src, </span><span class=cFE>10</span><span class=cF0>, &amp;src);
<a name="l74"></a>                </span><span class=cF1>if</span><span class=cF0> (*src++ != </span><span class=cF6>':'</span><span class=cF0>) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l75"></a>                ds.hour = </span><span class=cF5>Str2I64</span><span class=cF0>(src, </span><span class=cFE>10</span><span class=cF0>, &amp;src);
<a name="l76"></a>                </span><span class=cF1>if</span><span class=cF0> (*src++ != </span><span class=cF6>':'</span><span class=cF0>) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l77"></a>                ds.min = </span><span class=cF5>Str2I64</span><span class=cF0>(src, </span><span class=cFE>10</span><span class=cF0>, &amp;src);
<a name="l78"></a>                </span><span class=cF1>if</span><span class=cF0> (*src++ != </span><span class=cF6>':'</span><span class=cF0>) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l79"></a>                ds.sec = </span><span class=cF5>Str2I64</span><span class=cF0>(src, </span><span class=cFE>10</span><span class=cF0>, &amp;src);
<a name="l80"></a>                tmplg-&gt;datetime = </span><span class=cF5>Struct2Date</span><span class=cF0>(&amp;ds);
<a name="l81"></a>                </span><span class=cF1>if</span><span class=cF0> (*src++ != </span><span class=cF3>CH_SPACE</span><span class=cF0>) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l82"></a>                i = </span><span class=cF5>Str2I64</span><span class=cF0>(src, </span><span class=cFE>10</span><span class=cF0>, &amp;src);
<a name="l83"></a>                tmplg-&gt;datetime -= (i / </span><span class=cFE>100</span><span class=cF0> + i % </span><span class=cFE>100</span><span class=cF0> / </span><span class=cFE>60</span><span class=cF0>.</span><span class=cFE>0</span><span class=cF0>) * </span><span class=cF3>CDATE_FREQ</span><span class=cF0> * </span><span class=cFE>60</span><span class=cF0> * </span><span class=cFE>60</span><span class=cF0>;
<a name="l84"></a>                </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF5>Str2Date</span><span class=cF0>(</span><span class=cF6>&quot;1/1/2017&quot;</span><span class=cF0>) &lt;= tmplg-&gt;datetime &lt; </span><span class=cF5>Str2Date</span><span class=cF0>(</span><span class=cF6>&quot;1/1/2050&quot;</span><span class=cF0>)</span><span class=cF7>)</span><span class=cF0>)
<a name="l85"></a>                    </span><span class=cF5>throw</span><span class=cF0>;
<a name="l86"></a>                </span><span class=cF1>if</span><span class=cF0> (tmplg-&gt;datetime &lt; *_dstart) *_dstart = tmplg-&gt;datetime;
<a name="l87"></a>                </span><span class=cF1>if</span><span class=cF0> (tmplg-&gt;datetime &gt; *_dend)   *_dend   = tmplg-&gt;datetime;
<a name="l88"></a>
<a name="l89"></a>                </span><span class=cF1>do</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (!*src) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l90"></a>                </span><span class=cF1>while</span><span class=cF0> (*src++ != </span><span class=cF6>']'</span><span class=cF0>);
<a name="l91"></a>
<a name="l92"></a>                </span><span class=cF1>if</span><span class=cF0> (*src++ != </span><span class=cF3>CH_SPACE</span><span class=cF0>) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l93"></a>                </span><span class=cF1>if</span><span class=cF0> (*src++ != </span><span class=cF6>'\&quot;'</span><span class=cF0>) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l94"></a>                </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF5>StrNCompare</span><span class=cF7>(</span><span class=cF0>src, </span><span class=cF6>&quot;GET &quot;</span><span class=cF0>, </span><span class=cFE>4</span><span class=cF7>)</span><span class=cF0>)
<a name="l95"></a>                {
<a name="l96"></a>                    src2 = src += </span><span class=cFE>4</span><span class=cF0>;
<a name="l97"></a>                    </span><span class=cF1>do</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (!*src2) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l98"></a>                    </span><span class=cF1>while</span><span class=cF0> (*src2++ != </span><span class=cF3>CH_SPACE</span><span class=cF0>);
<a name="l99"></a>                    * --src2 = </span><span class=cFE>0</span><span class=cF0>;
<a name="l100"></a>                    tmplg-&gt;file = </span><span class=cF5>StrNew</span><span class=cF0>(src);
<a name="l101"></a>                    src = ++src2;
<a name="l102"></a>
<a name="l103"></a>                    </span><span class=cF1>do</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (!*src) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l104"></a>                    </span><span class=cF1>while</span><span class=cF0> (*src++ != </span><span class=cF6>'\&quot;'</span><span class=cF0>);
<a name="l105"></a>
<a name="l106"></a>                    tmplg-&gt;code = </span><span class=cF5>Str2I64</span><span class=cF0>(src, </span><span class=cFE>10</span><span class=cF0>, &amp;src);
<a name="l107"></a>                    </span><span class=cF1>if</span><span class=cF0> (*src++ != </span><span class=cF3>CH_SPACE</span><span class=cF0>) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l108"></a>                    tmplg-&gt;size = </span><span class=cF5>Str2I64</span><span class=cF0>(src, </span><span class=cFE>10</span><span class=cF0>, &amp;src);
<a name="l109"></a>                    </span><span class=cF1>if</span><span class=cF0> (*src++ != </span><span class=cF3>CH_SPACE</span><span class=cF0>) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l110"></a>
<a name="l111"></a>                    </span><span class=cF1>if</span><span class=cF0> (*src++ != </span><span class=cF6>'\&quot;'</span><span class=cF0>) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l112"></a>                    src2 = src;
<a name="l113"></a>                    </span><span class=cF1>do</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (!*src2) </span><span class=cF5>throw</span><span class=cF0>;
<a name="l114"></a>                    </span><span class=cF1>while</span><span class=cF0> (*src2++ != </span><span class=cF6>'\&quot;'</span><span class=cF0>);
<a name="l115"></a>                    * --src2 = </span><span class=cFE>0</span><span class=cF0>;
<a name="l116"></a>                    tmplg-&gt;link = </span><span class=cF5>StrNew</span><span class=cF0>(src);
<a name="l117"></a>                    src = ++src2;
<a name="l118"></a>
<a name="l119"></a>                    </span><span class=cF5>QueueInsert</span><span class=cF0>(tmplg, head-&gt;last);
<a name="l120"></a>                }
<a name="l121"></a>                </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF5>StrNCompare</span><span class=cF7>(</span><span class=cF0>src, </span><span class=cF6>&quot;HEAD &quot;</span><span class=cF0>, </span><span class=cFE>5</span><span class=cF7>)</span><span class=cF0>)
<a name="l122"></a>                {
<a name="l123"></a>                    LogStructDel(tmplg);
<a name="l124"></a>                }
<a name="l125"></a>                </span><span class=cF1>else</span><span class=cF0>
<a name="l126"></a>                    </span><span class=cF5>throw</span><span class=cF0>;
<a name="l127"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l128"></a>            </span><span class=cF1>catch</span><span class=cF0>
<a name="l129"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l130"></a>                </span><span class=cF5>Fs</span><span class=cF0>-&gt;catch_except = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l131"></a>                </span><span class=cF6>&quot;%$Q\n&quot;</span><span class=cF0>, doc_e-&gt;tag;
<a name="l132"></a>                LogStructDel(tmplg);
<a name="l133"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l134"></a>        }
<a name="l135"></a>        doc_e = doc_e-&gt;next;
<a name="l136"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l137"></a>    </span><span class=cF5>DocDel</span><span class=cF0>(doc);
<a name="l138"></a>}
<a name="l139"></a>
<a name="l140"></a>LogStruct *ParseLogFiles(</span><span class=cF1>U8</span><span class=cF0> *files_find_mask, </span><span class=cF9>CDate</span><span class=cF0> *_dstart, </span><span class=cF9>CDate</span><span class=cF0> *_dend)
<a name="l141"></a>{
<a name="l142"></a>    LogStruct *head = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF0>LogStruct</span><span class=cF7>)</span><span class=cF0>);
<a name="l143"></a>    </span><span class=cF9>CDirEntry</span><span class=cF0> *tmpde = </span><span class=cF5>FilesFind</span><span class=cF0>(files_find_mask), *tmpde1 = tmpde;
<a name="l144"></a>
<a name="l145"></a>    </span><span class=cF5>QueueInit</span><span class=cF0>(head);
<a name="l146"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpde)
<a name="l147"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l148"></a>        ParseSingleLogFile(head, tmpde-&gt;full_name, _dstart, _dend);
<a name="l149"></a>        tmpde = tmpde-&gt;next;
<a name="l150"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l151"></a>    </span><span class=cF5>DirTreeDel</span><span class=cF0>(tmpde1);
<a name="l152"></a>
<a name="l153"></a>    </span><span class=cF1>return</span><span class=cF0> head;
<a name="l154"></a>}
<a name="l155"></a>
<a name="l156"></a></span><span class=cF1>U0</span><span class=cF0> LogListDel(LogStruct *head)
<a name="l157"></a>{
<a name="l158"></a>    LogStruct *tmplg = head-&gt;next, *tmplg1;
<a name="l159"></a>
<a name="l160"></a>    </span><span class=cF1>while</span><span class=cF0> (tmplg != head)
<a name="l161"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l162"></a>        tmplg1 = tmplg-&gt;next;
<a name="l163"></a>        LogStructDel(tmplg);
<a name="l164"></a>        tmplg = tmplg1;
<a name="l165"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l166"></a>}
<a name="l167"></a>
<a name="l168"></a></span><span class=cF1>U0</span><span class=cF0> BlockedStructAdd(BlockedStruct *head, </span><span class=cF9>U32</span><span class=cF0> ip_num)
<a name="l169"></a>{
<a name="l170"></a>    BlockedStruct *tmpb = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF0>BlockedStruct</span><span class=cF7>)</span><span class=cF0>);
<a name="l171"></a>
<a name="l172"></a>    tmpb-&gt;ip_num = ip_num;
<a name="l173"></a>    </span><span class=cF5>QueueInsert</span><span class=cF0>(tmpb, head-&gt;last);
<a name="l174"></a>}
<a name="l175"></a>
<a name="l176"></a></span><span class=cF1>Bool</span><span class=cF0> IsBlocked(BlockedStruct *head, </span><span class=cF9>U32</span><span class=cF0> ip_num)
<a name="l177"></a>{
<a name="l178"></a>    BlockedStruct *tmpb = head-&gt;next;
<a name="l179"></a>
<a name="l180"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpb != head)
<a name="l181"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l182"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpb-&gt;ip_num == ip_num)
<a name="l183"></a>            </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l184"></a>        tmpb = tmpb-&gt;next;
<a name="l185"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l186"></a>
<a name="l187"></a>    </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l188"></a>}
<a name="l189"></a>
<a name="l190"></a></span><span class=cF1>U0</span><span class=cF0> BlockIPNuip(LogStruct *head)
<a name="l191"></a>{
<a name="l192"></a>    BlockedStruct blocked_head;
<a name="l193"></a>    LogStruct    *tmplg = head-&gt;next, *tmplg1;
<a name="l194"></a>
<a name="l195"></a>    </span><span class=cF5>QueueInit</span><span class=cF0>(&amp;blocked_head);
<a name="l196"></a>
<a name="l197"></a>    BlockedStructAdd(&amp;blocked_head, </span><span class=cFE>68</span><span class=cF0> &lt;&lt; </span><span class=cFE>24</span><span class=cF0> + </span><span class=cFE>227</span><span class=cF0> &lt;&lt; </span><span class=cFE>16</span><span class=cF0> + </span><span class=cFE>61</span><span class=cF0> &lt;&lt; </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>6</span><span class=cF0>);
<a name="l198"></a>
<a name="l199"></a>    </span><span class=cF2>//pass 1: collect robot list</span><span class=cF0>
<a name="l200"></a>    </span><span class=cF1>while</span><span class=cF0> (tmplg != head)
<a name="l201"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l202"></a>        </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>StrIMatch</span><span class=cF7>(</span><span class=cF6>&quot;ROBOT&quot;</span><span class=cF0>, tmplg-&gt;file</span><span class=cF7>)</span><span class=cF0> &amp;&amp; !IsBlocked</span><span class=cF7>(</span><span class=cF0>&amp;blocked_head, tmplg-&gt;ip_num</span><span class=cF7>)</span><span class=cF0>)
<a name="l203"></a>            BlockedStructAdd(&amp;blocked_head, tmplg-&gt;ip_num);
<a name="l204"></a>        tmplg = tmplg-&gt;next;
<a name="l205"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l206"></a>
<a name="l207"></a>    </span><span class=cF2>//pass 2: removed blocked ip_nuip</span><span class=cF0>
<a name="l208"></a>    tmplg = head-&gt;next;
<a name="l209"></a>    </span><span class=cF1>while</span><span class=cF0> (tmplg != head)
<a name="l210"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l211"></a>        tmplg1 = tmplg-&gt;next;
<a name="l212"></a>        </span><span class=cF1>if</span><span class=cF0> (IsBlocked</span><span class=cF7>(</span><span class=cF0>&amp;blocked_head, tmplg-&gt;ip_num</span><span class=cF7>)</span><span class=cF0>)
<a name="l213"></a>        {
<a name="l214"></a>            </span><span class=cF5>QueueRemove</span><span class=cF0>(tmplg);
<a name="l215"></a>            LogStructDel(tmplg);
<a name="l216"></a>        }
<a name="l217"></a>        tmplg = tmplg1;
<a name="l218"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l219"></a>
<a name="l220"></a>    </span><span class=cF5>QueueDel</span><span class=cF0>(&amp;blocked_head);
<a name="l221"></a>}
<a name="l222"></a>
<a name="l223"></a></span><span class=cF1>Bool</span><span class=cF0> IsDownLoad(LogStruct *tmplg)
<a name="l224"></a>{
<a name="l225"></a>    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>StrMatch</span><span class=cF7>(</span><span class=cF0>DOWNLOAD_FILE1, tmplg-&gt;file</span><span class=cF7>)</span><span class=cF0>&amp;&amp;tmplg-&gt;size &gt;= DOWNLOAD_FILE1_SIZE)
<a name="l226"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l227"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l228"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l229"></a>}
<a name="l230"></a>
<a name="l231"></a></span><span class=cF1>Bool</span><span class=cF0> IsIndex(LogStruct *tmplg)
<a name="l232"></a>{
<a name="l233"></a>    </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF5>StrCompare</span><span class=cF7>(</span><span class=cF0>tmplg-&gt;file, </span><span class=cF6>&quot;/index.html&quot;</span><span class=cF7>)</span><span class=cF0> || !</span><span class=cF5>StrCompare</span><span class=cF7>(</span><span class=cF0>tmplg-&gt;file, </span><span class=cF6>&quot;/&quot;</span><span class=cF7>)</span><span class=cF0>)
<a name="l234"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l235"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l236"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l237"></a>}
<a name="l238"></a>
<a name="l239"></a></span><span class=cF1>Bool</span><span class=cF0> IsKeeper(LogStruct *tmplg, </span><span class=cF9>CDate</span><span class=cF0> dstart, </span><span class=cF9>CDate</span><span class=cF0> dend)
<a name="l240"></a>{
<a name="l241"></a>    </span><span class=cF1>if</span><span class=cF0> (dstart &lt;= tmplg-&gt;datetime &lt;= dend                                   &amp;&amp;
<a name="l242"></a>        !</span><span class=cF5>StrOcc</span><span class=cF7>(</span><span class=cF0>tmplg-&gt;file, </span><span class=cF6>'?'</span><span class=cF7>)</span><span class=cF0>                                           &amp;&amp;
<a name="l243"></a>        </span><span class=cF5>StrLen</span><span class=cF7>(</span><span class=cF0>tmplg-&gt;file</span><span class=cF7>)</span><span class=cF0> &gt; </span><span class=cFE>2</span><span class=cF0>                                             &amp;&amp;
<a name="l244"></a>        </span><span class=cF6>'A'</span><span class=cF0> &lt;= tmplg-&gt;file[</span><span class=cFE>1</span><span class=cF0>] &lt;= </span><span class=cF6>'Z'</span><span class=cF0>                                        &amp;&amp;
<a name="l245"></a>        tmplg-&gt;size                                                         &amp;&amp;
<a name="l246"></a>        tmplg-&gt;file[</span><span class=cF5>StrLen</span><span class=cF7>(</span><span class=cF0>tmplg-&gt;file</span><span class=cF7>)</span><span class=cF0> - </span><span class=cFE>1</span><span class=cF0>] != </span><span class=cF6>'/'</span><span class=cF0>                         &amp;&amp;
<a name="l247"></a>        </span><span class=cF7>(</span><span class=cF5>StrLen</span><span class=cF0>(tmplg-&gt;file) &lt; </span><span class=cFE>3</span><span class=cF0> || </span><span class=cF5>MemCompare</span><span class=cF0>(&amp;tmplg-&gt;file[</span><span class=cFE>1</span><span class=cF0>], </span><span class=cF6>&quot;Wb&quot;</span><span class=cF0>, </span><span class=cFE>2</span><span class=cF0>)</span><span class=cF7>)</span><span class=cF0>   &amp;&amp;
<a name="l248"></a>        </span><span class=cF7>(</span><span class=cF5>StrLen</span><span class=cF0>(tmplg-&gt;file) &lt; </span><span class=cFE>7</span><span class=cF0> || </span><span class=cF5>MemCompare</span><span class=cF0>(&amp;tmplg-&gt;file[</span><span class=cFE>1</span><span class=cF0>], </span><span class=cF6>&quot;Family&quot;</span><span class=cF0>, </span><span class=cFE>6</span><span class=cF0>)</span><span class=cF7>)</span><span class=cF0>)
<a name="l249"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l250"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l251"></a>
<a name="l252"></a></span><span class=cF7>}</span><span class=cF0>  </span><span class=cF1>else</span><span class=cF0>
<a name="l253"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l254"></a>}
<a name="l255"></a>
<a name="l256"></a></span><span class=cF1>Bool</span><span class=cF0> IPNumTreeAdd(LogStruct **_head, LogStruct *tmplg)
<a name="l257"></a>{
<a name="l258"></a>    LogStruct *head;
<a name="l259"></a>
<a name="l260"></a>    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>UnusedStack</span><span class=cF0> &lt; </span><span class=cFE>0x200</span><span class=cF0>)
<a name="l261"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l262"></a>        </span><span class=cF5>PrintErr</span><span class=cF0>(</span><span class=cF6>&quot;Stack Overflow&quot;</span><span class=cF0>);
<a name="l263"></a>        </span><span class=cF5>throw</span><span class=cF0>;
<a name="l264"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l265"></a>    </span><span class=cF1>if</span><span class=cF0> (head = *_head)
<a name="l266"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l267"></a>        </span><span class=cF1>if</span><span class=cF0> (tmplg-&gt;ip_num == head-&gt;ip_num)
<a name="l268"></a>            </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l269"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (tmplg-&gt;ip_num &lt; head-&gt;ip_num)
<a name="l270"></a>            </span><span class=cF1>return</span><span class=cF0> IPNumTreeAdd(&amp;head-&gt;ip_num_left, tmplg);
<a name="l271"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l272"></a>            </span><span class=cF1>return</span><span class=cF0> IPNumTreeAdd(&amp;head-&gt;ip_num_right, tmplg);
<a name="l273"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l274"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l275"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l276"></a>        tmplg-&gt;ip_num_left = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l277"></a>        tmplg-&gt;ip_num_right = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l278"></a>        *_head = tmplg;
<a name="l279"></a>
<a name="l280"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l281"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l282"></a>}
<a name="l283"></a>
<a name="l284"></a></span><span class=cF1>U0</span><span class=cF0> LinkTreeAdd(LinkStruct **_root, LogStruct *tmplg)
<a name="l285"></a>{
<a name="l286"></a>    </span><span class=cF9>I64</span><span class=cF0>         i;
<a name="l287"></a>    LinkStruct *root, *tmplk;
<a name="l288"></a>
<a name="l289"></a>    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>UnusedStack</span><span class=cF0> &lt; </span><span class=cFE>0x200</span><span class=cF0>)
<a name="l290"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l291"></a>        </span><span class=cF5>PrintErr</span><span class=cF0>(</span><span class=cF6>&quot;Stack Overflow&quot;</span><span class=cF0>);
<a name="l292"></a>        </span><span class=cF5>throw</span><span class=cF0>;
<a name="l293"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l294"></a>    </span><span class=cF1>if</span><span class=cF0> (root = *_root)
<a name="l295"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l296"></a>        </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>i = </span><span class=cF5>StrCompare</span><span class=cF0>(tmplg-&gt;link, root-&gt;link)</span><span class=cF7>)</span><span class=cF0>)
<a name="l297"></a>            root-&gt;count++;
<a name="l298"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (i &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l299"></a>            LinkTreeAdd(&amp;root-&gt;left, tmplg);
<a name="l300"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l301"></a>            LinkTreeAdd(&amp;root-&gt;right, tmplg);
<a name="l302"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l303"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l304"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l305"></a>        tmplk = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF0>LinkStruct</span><span class=cF7>)</span><span class=cF0>);
<a name="l306"></a>        tmplk-&gt;link  = tmplg-&gt;link;
<a name="l307"></a>        tmplk-&gt;count = </span><span class=cFE>1</span><span class=cF0>;
<a name="l308"></a>        *_root = tmplk;
<a name="l309"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l310"></a>}
<a name="l311"></a>
<a name="l312"></a></span><span class=cF1>U0</span><span class=cF0> FileTreeAdd(LinkStruct **_root, LogStruct *tmplg)
<a name="l313"></a>{
<a name="l314"></a>    </span><span class=cF9>I64</span><span class=cF0>         i;
<a name="l315"></a>    LinkStruct *root, *tmplk;
<a name="l316"></a>    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>UnusedStack</span><span class=cF0> &lt; </span><span class=cFE>0x200</span><span class=cF0>)
<a name="l317"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l318"></a>        </span><span class=cF5>PrintErr</span><span class=cF0>(</span><span class=cF6>&quot;Stack Overflow&quot;</span><span class=cF0>);
<a name="l319"></a>        </span><span class=cF5>throw</span><span class=cF0>;
<a name="l320"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l321"></a>    </span><span class=cF1>if</span><span class=cF0> (root = *_root)
<a name="l322"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l323"></a>        </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>i = </span><span class=cF5>StrCompare</span><span class=cF0>(tmplg-&gt;file, root-&gt;file)</span><span class=cF7>)</span><span class=cF0>)
<a name="l324"></a>            root-&gt;count++;
<a name="l325"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (i &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l326"></a>            FileTreeAdd(&amp;root-&gt;left, tmplg);
<a name="l327"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l328"></a>            FileTreeAdd(&amp;root-&gt;right, tmplg);
<a name="l329"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l330"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l331"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l332"></a>        tmplk = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF0>LinkStruct</span><span class=cF7>)</span><span class=cF0>);
<a name="l333"></a>        tmplk-&gt;file  = tmplg-&gt;file;
<a name="l334"></a>        tmplk-&gt;count = </span><span class=cFE>1</span><span class=cF0>;
<a name="l335"></a>        *_root = tmplk;
<a name="l336"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l337"></a>}
<a name="l338"></a>
<a name="l339"></a></span><span class=cF1>U0</span><span class=cF0> LinkTreeDel(LinkStruct *root)
<a name="l340"></a>{
<a name="l341"></a>    </span><span class=cF1>if</span><span class=cF0> (root)
<a name="l342"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l343"></a>        LinkTreeDel(root-&gt;left);
<a name="l344"></a>        LinkTreeDel(root-&gt;right);
<a name="l345"></a>        </span><span class=cF5>Free</span><span class=cF0>(root);
<a name="l346"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l347"></a>}
<a name="l348"></a>
<a name="l349"></a></span><span class=cF1>U0</span><span class=cF0> LinkTreeTraverse(LinkStruct *root)
<a name="l350"></a>{
<a name="l351"></a>    </span><span class=cF1>if</span><span class=cF0> (root)
<a name="l352"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l353"></a>        LinkTreeTraverse(root-&gt;left);
<a name="l354"></a>        </span><span class=cF6>&quot;%3d:%$Q\n&quot;</span><span class=cF0>, root-&gt;count, root-&gt;link;
<a name="l355"></a>        LinkTreeTraverse(root-&gt;right);
<a name="l356"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l357"></a>}
<a name="l358"></a>
<a name="l359"></a></span><span class=cF1>U0</span><span class=cF0> FileTreeDel(LinkStruct *root)
<a name="l360"></a>{
<a name="l361"></a>    </span><span class=cF1>if</span><span class=cF0> (root)
<a name="l362"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l363"></a>        FileTreeDel(root-&gt;left);
<a name="l364"></a>        FileTreeDel(root-&gt;right);
<a name="l365"></a>        </span><span class=cF5>Free</span><span class=cF0>(root);
<a name="l366"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l367"></a>}
<a name="l368"></a>
<a name="l369"></a></span><span class=cF1>U0</span><span class=cF0> FileTreeTraverse(LinkStruct *root)
<a name="l370"></a>{
<a name="l371"></a>    </span><span class=cF1>if</span><span class=cF0> (root)
<a name="l372"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l373"></a>        FileTreeTraverse(root-&gt;left);
<a name="l374"></a>        </span><span class=cF6>&quot;%3d:%$Q\n&quot;</span><span class=cF0>, root-&gt;count, root-&gt;file;
<a name="l375"></a>        FileTreeTraverse(root-&gt;right);
<a name="l376"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l377"></a>}
<a name="l378"></a>
<a name="l379"></a></span><span class=cF1>U0</span><span class=cF0> DownLoadRep(LogStruct *head, </span><span class=cF9>CDate</span><span class=cF0> dstart, </span><span class=cF9>CDate</span><span class=cF0> dend)
<a name="l380"></a>{
<a name="l381"></a>    </span><span class=cF9>I64</span><span class=cF0>         i, j, count, dups, 
<a name="l382"></a>                hours_start, hours_end, *hour_counts, *dup_counts, 
<a name="l383"></a>                days_start, days_end, *day_counts, *day_dup_counts;
<a name="l384"></a>    LogStruct  *tmplg = head-&gt;next, *dup_head = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l385"></a>    LinkStruct *link_root = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l386"></a>    </span><span class=cF9>CDateStruct</span><span class=cF0> ds;
<a name="l387"></a>
<a name="l388"></a>    i = dstart  * </span><span class=cFE>24</span><span class=cF0>;
<a name="l389"></a>    hours_start = i.u32[</span><span class=cFE>1</span><span class=cF0>];
<a name="l390"></a>    i = dend    * </span><span class=cFE>24</span><span class=cF0>;
<a name="l391"></a>    hours_end   = i.u32[</span><span class=cFE>1</span><span class=cF0>];
<a name="l392"></a>
<a name="l393"></a>    days_start  = (dstart + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0>;
<a name="l394"></a>    days_end    = (dend   + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0>;
<a name="l395"></a>
<a name="l396"></a>    hour_counts     = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF7>(</span><span class=cF0>hours_end - hours_start + </span><span class=cFE>1</span><span class=cF7>)</span><span class=cF0> * </span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF7>)</span><span class=cF0>);
<a name="l397"></a>    dup_counts      = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF7>(</span><span class=cF0>hours_end - hours_start + </span><span class=cFE>1</span><span class=cF7>)</span><span class=cF0> * </span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF7>)</span><span class=cF0>);
<a name="l398"></a>    day_counts      = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF7>(</span><span class=cF0>days_end  - days_start  + </span><span class=cFE>1</span><span class=cF7>)</span><span class=cF0> * </span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF7>)</span><span class=cF0>);
<a name="l399"></a>    day_dup_counts  = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF7>(</span><span class=cF0>days_end  - days_start  + </span><span class=cFE>1</span><span class=cF7>)</span><span class=cF0> * </span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF7>)</span><span class=cF0>);
<a name="l400"></a>    dups = count = </span><span class=cFE>0</span><span class=cF0>;
<a name="l401"></a>    </span><span class=cF1>while</span><span class=cF0> (tmplg != head)
<a name="l402"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l403"></a>        </span><span class=cF1>if</span><span class=cF0> (IsKeeper</span><span class=cF7>(</span><span class=cF0>tmplg, dstart, dend</span><span class=cF7>)</span><span class=cF0> &amp;&amp; IsDownLoad</span><span class=cF7>(</span><span class=cF0>tmplg</span><span class=cF7>)</span><span class=cF0>)
<a name="l404"></a>        {
<a name="l405"></a>            i = tmplg-&gt;datetime * </span><span class=cFE>24</span><span class=cF0>;
<a name="l406"></a>            hour_counts[i.u32[</span><span class=cFE>1</span><span class=cF0>] - hours_start]++;
<a name="l407"></a>            day_counts[(tmplg-&gt;datetime + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0> - days_start]++;
<a name="l408"></a>            count++;
<a name="l409"></a>            </span><span class=cF1>if</span><span class=cF0> (IPNumTreeAdd</span><span class=cF7>(</span><span class=cF0>&amp;dup_head, tmplg</span><span class=cF7>)</span><span class=cF0>)
<a name="l410"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l411"></a>                day_dup_counts[(tmplg-&gt;datetime + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0> - days_start]++;
<a name="l412"></a>                dup_counts[i.u32[</span><span class=cFE>1</span><span class=cF0>] - hours_start]++;
<a name="l413"></a>                dups++;
<a name="l414"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l415"></a>            LinkTreeAdd(&amp;link_root, tmplg);
<a name="l416"></a>        }
<a name="l417"></a>        tmplg = tmplg-&gt;next;
<a name="l418"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l419"></a>
<a name="l420"></a>    </span><span class=cF6>&quot;\n\nDownloads of /TOS_Distro.ISO\n&quot;</span><span class=cF0>;
<a name="l421"></a>    </span><span class=cF1>for</span><span class=cF0> (i = dstart; i &lt;= dend; i += </span><span class=cFE>1</span><span class=cF0> &lt;&lt; </span><span class=cFE>32</span><span class=cF0>)
<a name="l422"></a>        </span><span class=cF6>&quot;%D  Dups:%5d  Total:%5d  Uniques:%5d\n&quot;</span><span class=cF0>, i, 
<a name="l423"></a>        day_dup_counts[(i + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0> - days_start], 
<a name="l424"></a>        day_counts[(i + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0> - days_start], 
<a name="l425"></a>        day_counts[(i + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0> - days_start] - day_dup_counts[(i + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0> - days_start];
<a name="l426"></a>
<a name="l427"></a>    </span><span class=cF6>&quot;\n\nDownloads of /TOS_Distro.ISO\n&quot;</span><span class=cF0>
<a name="l428"></a>    </span><span class=cF6>&quot;'-' is a dup.  '+' is not a dup.\n&quot;</span><span class=cF0>;
<a name="l429"></a>    </span><span class=cF1>if</span><span class=cF0> (hours_end - hours_start &gt;= HOURS_MAX)
<a name="l430"></a>        i = hours_end - HOURS_MAX + </span><span class=cFE>1</span><span class=cF0>;
<a name="l431"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l432"></a>        i = hours_start;
<a name="l433"></a>    </span><span class=cF1>for</span><span class=cF0> (; i &lt;= hours_end; i++)
<a name="l434"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l435"></a>        </span><span class=cF5>Date2Struct</span><span class=cF0>(&amp;ds, i &lt;&lt; </span><span class=cFE>32</span><span class=cF0> / </span><span class=cFE>24</span><span class=cF0> + </span><span class=cFB>local_time_offset</span><span class=cF0>);
<a name="l436"></a>        </span><span class=cF6>&quot;%D %02d: &quot;</span><span class=cF0>, i &lt;&lt; </span><span class=cFE>32</span><span class=cF0> / </span><span class=cFE>24</span><span class=cF0>, ds.hour;
<a name="l437"></a>        </span><span class=cF1>for</span><span class=cF0> (j = </span><span class=cFE>0</span><span class=cF0>; j &lt; dup_counts[i - hours_start]; j++)
<a name="l438"></a>            </span><span class=cF6>'-'</span><span class=cF0>;
<a name="l439"></a>        </span><span class=cF1>for</span><span class=cF0> (; j &lt; hour_counts[i - hours_start]; j++)
<a name="l440"></a>            </span><span class=cF6>'+'</span><span class=cF0>;
<a name="l441"></a>        </span><span class=cF6>'\n'</span><span class=cF0>;
<a name="l442"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l443"></a>    </span><span class=cF6>&quot;Total:%d  Dups:%d  Uniques:%d\n&quot;</span><span class=cF0>, count, dups, count - dups;
<a name="l444"></a>
<a name="l445"></a>    </span><span class=cF6>&quot;\n\nDownloads of /TOS_Distro.ISO\n&quot;</span><span class=cF0>;
<a name="l446"></a>    LinkTreeTraverse(link_root);
<a name="l447"></a>    </span><span class=cF6>'\n'</span><span class=cF0>;
<a name="l448"></a>
<a name="l449"></a>    LinkTreeDel(link_root);
<a name="l450"></a>    </span><span class=cF5>Free</span><span class=cF0>(hour_counts);
<a name="l451"></a>    </span><span class=cF5>Free</span><span class=cF0>(dup_counts);
<a name="l452"></a>    </span><span class=cF5>Free</span><span class=cF0>(day_counts);
<a name="l453"></a>    </span><span class=cF5>Free</span><span class=cF0>(day_dup_counts);
<a name="l454"></a>}
<a name="l455"></a>
<a name="l456"></a></span><span class=cF1>U0</span><span class=cF0> FileRep(LogStruct *head, </span><span class=cF9>CDate</span><span class=cF0> dstart, </span><span class=cF9>CDate</span><span class=cF0> dend)
<a name="l457"></a>{
<a name="l458"></a>    LogStruct  *tmplg = head-&gt;next;
<a name="l459"></a>    LinkStruct *file_root = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l460"></a>
<a name="l461"></a>    </span><span class=cF1>while</span><span class=cF0> (tmplg != head)
<a name="l462"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l463"></a>        </span><span class=cF1>if</span><span class=cF0> (IsKeeper</span><span class=cF7>(</span><span class=cF0>tmplg, dstart, dend</span><span class=cF7>)</span><span class=cF0>)
<a name="l464"></a>            FileTreeAdd(&amp;file_root, tmplg);
<a name="l465"></a>        tmplg = tmplg-&gt;next;
<a name="l466"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l467"></a>    </span><span class=cF6>&quot;\n\nFile Hits\n&quot;</span><span class=cF0>;
<a name="l468"></a>    FileTreeTraverse(file_root);
<a name="l469"></a>    </span><span class=cF6>'\n'</span><span class=cF0>;
<a name="l470"></a>    FileTreeDel(file_root);
<a name="l471"></a>}
<a name="l472"></a>
<a name="l473"></a></span><span class=cF1>U0</span><span class=cF0> IndexRep(LogStruct *head, </span><span class=cF9>CDate</span><span class=cF0> dstart, </span><span class=cF9>CDate</span><span class=cF0> dend)
<a name="l474"></a>{
<a name="l475"></a>    </span><span class=cF9>I64</span><span class=cF0>         i, j, count, dups, 
<a name="l476"></a>                hours_start, hours_end, *hour_counts, *dup_counts, 
<a name="l477"></a>                days_start, days_end, *day_counts, *day_dup_counts;
<a name="l478"></a>    LogStruct  *tmplg = head-&gt;next, *dup_head = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l479"></a>    LinkStruct *link_root = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l480"></a>    </span><span class=cF9>CDateStruct</span><span class=cF0> ds;
<a name="l481"></a>
<a name="l482"></a>    i = dstart  * </span><span class=cFE>24</span><span class=cF0>;
<a name="l483"></a>    hours_start = i.u32[</span><span class=cFE>1</span><span class=cF0>];
<a name="l484"></a>    i = dend    * </span><span class=cFE>24</span><span class=cF0>;
<a name="l485"></a>    hours_end   = i.u32[</span><span class=cFE>1</span><span class=cF0>];
<a name="l486"></a>
<a name="l487"></a>    days_start  = (dstart + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0>;
<a name="l488"></a>    days_end    = (dend   + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0>;
<a name="l489"></a>
<a name="l490"></a>    hour_counts     = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF7>(</span><span class=cF0>hours_end - hours_start + </span><span class=cFE>1</span><span class=cF7>)</span><span class=cF0> * </span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF7>)</span><span class=cF0>);
<a name="l491"></a>    dup_counts      = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF7>(</span><span class=cF0>hours_end - hours_start + </span><span class=cFE>1</span><span class=cF7>)</span><span class=cF0> * </span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF7>)</span><span class=cF0>);
<a name="l492"></a>    day_counts      = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF7>(</span><span class=cF0>days_end  - days_start  + </span><span class=cFE>1</span><span class=cF7>)</span><span class=cF0> * </span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF7>)</span><span class=cF0>);
<a name="l493"></a>    day_dup_counts  = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF7>(</span><span class=cF0>days_end  - days_start  + </span><span class=cFE>1</span><span class=cF7>)</span><span class=cF0> * </span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF7>)</span><span class=cF0>);
<a name="l494"></a>    dups = count = </span><span class=cFE>0</span><span class=cF0>;
<a name="l495"></a>    </span><span class=cF1>while</span><span class=cF0> (tmplg != head)
<a name="l496"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l497"></a>        </span><span class=cF1>if</span><span class=cF0> (IsKeeper</span><span class=cF7>(</span><span class=cF0>tmplg, dstart, dend</span><span class=cF7>)</span><span class=cF0> &amp;&amp; IsIndex</span><span class=cF7>(</span><span class=cF0>tmplg</span><span class=cF7>)</span><span class=cF0>)
<a name="l498"></a>        {
<a name="l499"></a>            i = tmplg-&gt;datetime * </span><span class=cFE>24</span><span class=cF0>;
<a name="l500"></a>            hour_counts[i.u32[</span><span class=cFE>1</span><span class=cF0>] - hours_start]++;
<a name="l501"></a>            day_counts[(tmplg-&gt;datetime + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0> - days_start]++;
<a name="l502"></a>            count++;
<a name="l503"></a>            </span><span class=cF1>if</span><span class=cF0> (IPNumTreeAdd</span><span class=cF7>(</span><span class=cF0>&amp;dup_head, tmplg</span><span class=cF7>)</span><span class=cF0>)
<a name="l504"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l505"></a>                day_dup_counts[(tmplg-&gt;datetime + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0> - days_start]++;
<a name="l506"></a>                dup_counts[i.u32[</span><span class=cFE>1</span><span class=cF0>] - hours_start]++;
<a name="l507"></a>                dups++;
<a name="l508"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l509"></a>            LinkTreeAdd(&amp;link_root, tmplg);
<a name="l510"></a>        }
<a name="l511"></a>        tmplg = tmplg-&gt;next;
<a name="l512"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l513"></a>
<a name="l514"></a>    </span><span class=cF6>&quot;\n\nHits on /index.html\n&quot;</span><span class=cF0>
<a name="l515"></a>    </span><span class=cF6>&quot;'-' is a dup.  '+' is not a dup.\n&quot;</span><span class=cF0>;
<a name="l516"></a>    </span><span class=cF1>for</span><span class=cF0> (i = dstart; i &lt;= dend; i += </span><span class=cFE>1</span><span class=cF0> &lt;&lt; </span><span class=cFE>32</span><span class=cF0>)
<a name="l517"></a>        </span><span class=cF6>&quot;%D  Dups:%5d  Total:%5d  Uniques:%5d\n&quot;</span><span class=cF0>, i, 
<a name="l518"></a>        day_dup_counts[(i + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0> - days_start], 
<a name="l519"></a>        day_counts[(i + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0> - days_start], 
<a name="l520"></a>        day_counts[(i + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0> - days_start] - day_dup_counts[(i + </span><span class=cFB>local_time_offset</span><span class=cF0>) &gt;&gt; </span><span class=cFE>32</span><span class=cF0> - days_start];
<a name="l521"></a>
<a name="l522"></a>    </span><span class=cF6>&quot;\n\nHits on /index.html\n&quot;</span><span class=cF0>;
<a name="l523"></a>    </span><span class=cF1>if</span><span class=cF0> (hours_end - hours_start &gt;= HOURS_MAX)
<a name="l524"></a>        i = hours_end - HOURS_MAX + </span><span class=cFE>1</span><span class=cF0>;
<a name="l525"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l526"></a>        i = hours_start;
<a name="l527"></a>    </span><span class=cF1>for</span><span class=cF0> (; i &lt;= hours_end; i++)
<a name="l528"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l529"></a>        </span><span class=cF5>Date2Struct</span><span class=cF0>(&amp;ds, i &lt;&lt; </span><span class=cFE>32</span><span class=cF0> / </span><span class=cFE>24</span><span class=cF0> + </span><span class=cFB>local_time_offset</span><span class=cF0>);
<a name="l530"></a>        </span><span class=cF6>&quot;%D %02d: &quot;</span><span class=cF0>, i &lt;&lt; </span><span class=cFE>32</span><span class=cF0> / </span><span class=cFE>24</span><span class=cF0>, ds.hour;
<a name="l531"></a>        </span><span class=cF1>for</span><span class=cF0> (j = </span><span class=cFE>0</span><span class=cF0>; j &lt; dup_counts[i - hours_start];j++)
<a name="l532"></a>            </span><span class=cF6>'-'</span><span class=cF0>;
<a name="l533"></a>        </span><span class=cF1>for</span><span class=cF0> (; j &lt; hour_counts[i - hours_start]; j++)
<a name="l534"></a>            </span><span class=cF6>'+'</span><span class=cF0>;
<a name="l535"></a>        </span><span class=cF6>'\n'</span><span class=cF0>;
<a name="l536"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l537"></a>    </span><span class=cF6>&quot;Total:%d  Dups:%d  Uniques:%d\n&quot;</span><span class=cF0>, count, dups, count - dups;
<a name="l538"></a>
<a name="l539"></a>    </span><span class=cF6>&quot;\n\nHits on /index.html\n&quot;</span><span class=cF0>;
<a name="l540"></a>    LinkTreeTraverse(link_root);
<a name="l541"></a>    </span><span class=cF6>'\n'</span><span class=cF0>;
<a name="l542"></a>
<a name="l543"></a>    LinkTreeDel(link_root);
<a name="l544"></a>    </span><span class=cF5>Free</span><span class=cF0>(hour_counts);
<a name="l545"></a>    </span><span class=cF5>Free</span><span class=cF0>(dup_counts);
<a name="l546"></a>    </span><span class=cF5>Free</span><span class=cF0>(day_counts);
<a name="l547"></a>    </span><span class=cF5>Free</span><span class=cF0>(day_dup_counts);
<a name="l548"></a>}
<a name="l549"></a>
<a name="l550"></a></span><span class=cF1>U0</span><span class=cF0> WebLogRep(</span><span class=cF1>U8</span><span class=cF0> *mask, </span><span class=cF1>U8</span><span class=cF0> *output_filename)
<a name="l551"></a>{
<a name="l552"></a>    LogStruct  *head;
<a name="l553"></a>    </span><span class=cF9>CDate</span><span class=cF0>       dstart = </span><span class=cF3>I64_MAX</span><span class=cF0>, dend = </span><span class=cF3>I64_MIN</span><span class=cF0>;
<a name="l554"></a>
<a name="l555"></a>    </span><span class=cF5>DocMax</span><span class=cF0>;
<a name="l556"></a>
<a name="l557"></a>    head = ParseLogFiles(mask, &amp;dstart, &amp;dend);
<a name="l558"></a>    </span><span class=cF1>if</span><span class=cF0> (dstart &gt; dend)
<a name="l559"></a>        </span><span class=cF5>PrintErr</span><span class=cF0>(</span><span class=cF6>&quot;No Data.\n&quot;</span><span class=cF0>);
<a name="l560"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l561"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l562"></a>        dstart  = </span><span class=cF5>DateGet</span><span class=cF0>(</span><span class=cF6>&quot;Start(%D):&quot;</span><span class=cF0>, dstart);
<a name="l563"></a>        dend    = </span><span class=cF5>DateGet</span><span class=cF0>(</span><span class=cF6>&quot;End  (%D):&quot;</span><span class=cF0>, dend);
<a name="l564"></a>        BlockIPNuip(head);
<a name="l565"></a>
<a name="l566"></a>        </span><span class=cF5>DocClear</span><span class=cF0>;
<a name="l567"></a>        </span><span class=cF6>&quot;$WW,0$&quot;</span><span class=cF0>;
<a name="l568"></a>        IndexRep(head, dstart, dend);
<a name="l569"></a>        FileRep(head, dstart, dend);
<a name="l570"></a>        DownLoadRep(head, dstart, dend);
<a name="l571"></a>
<a name="l572"></a>        </span><span class=cF5>StrCopy</span><span class=cF0>(</span><span class=cF5>DocPut</span><span class=cF0>-&gt;filename.name, output_filename);
<a name="l573"></a>        </span><span class=cF5>DocWrite</span><span class=cF0>(</span><span class=cF5>DocPut</span><span class=cF0>, </span><span class=cF3>TRUE</span><span class=cF0>);
<a name="l574"></a>
<a name="l575"></a>        </span><span class=cF6>&quot;$WW,1$&quot;</span><span class=cF0>;
<a name="l576"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l577"></a>    LogListDel(head);
<a name="l578"></a>}
<a name="l579"></a>
<a name="l580"></a>#</span><span class=cF1>if</span><span class=cF0> </span><span class=cF3>__CMD_LINE__</span><span class=cF0>
<a name="l581"></a></span><span class=cF5>Cd</span><span class=cF0>(</span><span class=cF3>__DIR__</span><span class=cF0>);;
<a name="l582"></a>WebLogRep(</span><span class=cF6>&quot;*.log*&quot;</span><span class=cF0>, </span><span class=cF6>&quot;~/DemoWebLog.DD&quot;</span><span class=cF0>);
<a name="l583"></a>#</span><span class=cF1>endif</span><span class=cF0>
</span></pre></body>
</html>
