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
<a name="l1"></a><span class=cF1>U0</span><span class=cF0> </span><span class=cFD>LexBackupLastChar</span><span class=cF0>(</span><span class=cF9>CCompCtrl</span><span class=cF0> *cc)
<a name="l2"></a>{
<a name="l3"></a>    </span><span class=cF9>CLexFile</span><span class=cF0> *tmpf = cc-&gt;lex_include_stack;
<a name="l4"></a>
<a name="l5"></a>    tmpf-&gt;buf_ptr = cc-&gt;cur_buf_ptr;
<a name="l6"></a>    </span><span class=cF1>if</span><span class=cF0> (cc-&gt;flags &amp; </span><span class=cF3>CCF_USE_LAST_U16</span><span class=cF0>)
<a name="l7"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l8"></a>        tmpf-&gt;last_U16 = cc-&gt;last_U16;
<a name="l9"></a>        cc-&gt;flags &amp;= ~</span><span class=cF3>CCF_USE_LAST_U16</span><span class=cF0>;
<a name="l10"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l11"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l12"></a>        tmpf-&gt;last_U16 = </span><span class=cFE>0</span><span class=cF0>;
<a name="l13"></a>}
<a name="l14"></a>
<a name="l15"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>LexPush</span><span class=cF0>(</span><span class=cF9>CCompCtrl</span><span class=cF0> *cc)
<a name="l16"></a>{</span><span class=cF2>//Create token-stream save point.</span><span class=cF0>
<a name="l17"></a>    </span><span class=cF9>CLexFile</span><span class=cF0> *tmpf;
<a name="l18"></a>
<a name="l19"></a>    </span><span class=cFD>LexBackupLastChar</span><span class=cF0>(cc);
<a name="l20"></a>    </span><span class=cF1>if</span><span class=cF0> (cc-&gt;lex_include_stack-&gt;last_U16)
<a name="l21"></a>        cc-&gt;flags |= </span><span class=cF3>CCF_USE_LAST_U16</span><span class=cF0>;
<a name="l22"></a>    tmpf = </span><span class=cF5>MAllocIdent</span><span class=cF0>(cc-&gt;lex_include_stack);
<a name="l23"></a>    tmpf-&gt;next = cc-&gt;lex_parse_stack;
<a name="l24"></a>    cc-&gt;lex_parse_stack = tmpf;
<a name="l25"></a>}
<a name="l26"></a>
<a name="l27"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>LexPopRestore</span><span class=cF0>(</span><span class=cF9>CCompCtrl</span><span class=cF0> *cc)
<a name="l28"></a>{</span><span class=cF2>//Restore token-stream saved-point.</span><span class=cF0>
<a name="l29"></a></span><span class=cF2>//Bad things can happen if you cross an #include file boundary.</span><span class=cF0>
<a name="l30"></a>    </span><span class=cF9>CLexFile</span><span class=cF0> *tmpf = cc-&gt;lex_parse_stack;
<a name="l31"></a>
<a name="l32"></a>    cc-&gt;cur_buf_ptr = tmpf-&gt;buf_ptr;
<a name="l33"></a>    </span><span class=cF1>if</span><span class=cF0> (cc-&gt;last_U16 = tmpf-&gt;last_U16)
<a name="l34"></a>        cc-&gt;flags |= </span><span class=cF3>CCF_USE_LAST_U16</span><span class=cF0>;
<a name="l35"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l36"></a>        cc-&gt;flags &amp;= ~</span><span class=cF3>CCF_USE_LAST_U16</span><span class=cF0>;
<a name="l37"></a>    </span><span class=cF5>MemCopy</span><span class=cF0>(cc-&gt;lex_include_stack</span><span class=cF7>(</span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> + </span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>, tmpf</span><span class=cF7>(</span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> + </span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>, </span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF9>CLexFile</span><span class=cF7>)</span><span class=cF0> - </span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>);
<a name="l38"></a>    cc-&gt;lex_parse_stack = tmpf-&gt;next;
<a name="l39"></a>    </span><span class=cF5>Free</span><span class=cF0>(tmpf);
<a name="l40"></a>}
<a name="l41"></a>
<a name="l42"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>LexPopNoRestore</span><span class=cF0>(</span><span class=cF9>CCompCtrl</span><span class=cF0> *cc)
<a name="l43"></a>{</span><span class=cF2>//Don't restore token-stream saved-point.</span><span class=cF0>
<a name="l44"></a>    </span><span class=cF9>CLexFile</span><span class=cF0> *tmpf = cc-&gt;lex_parse_stack;
<a name="l45"></a>
<a name="l46"></a>    cc-&gt;lex_parse_stack = tmpf-&gt;next;
<a name="l47"></a>    </span><span class=cF5>Free</span><span class=cF0>(tmpf);
<a name="l48"></a>}
<a name="l49"></a>
<a name="l50"></a></span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>MemberMetaData</span><span class=cF0>(</span><span class=cF1>U8</span><span class=cF0> *needle_str, </span><span class=cF9>CMemberList</span><span class=cF0> *haystack_member_list)
<a name="l51"></a>{</span><span class=cF2>//Find meta data name, return meta data val. See </span><a href="https://tomawezome.github.io/ZealOS/Demo/ClassMeta.html#l1"><span class=cF4>::/Demo/ClassMeta.CC</span></a><span class=cF2>.</span><span class=cF0>
<a name="l52"></a>    </span><span class=cF9>CMemberListMeta</span><span class=cF0> *meta = haystack_member_list-&gt;meta;
<a name="l53"></a>
<a name="l54"></a>    </span><span class=cF1>while</span><span class=cF0> (meta)
<a name="l55"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l56"></a>        </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF5>StrCompare</span><span class=cF7>(</span><span class=cF0>meta-&gt;str, needle_str</span><span class=cF7>)</span><span class=cF0>)
<a name="l57"></a>            </span><span class=cF1>return</span><span class=cF0> meta-&gt;user_data;
<a name="l58"></a>        meta = meta-&gt;next;
<a name="l59"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l60"></a>
<a name="l61"></a>    </span><span class=cF1>return</span><span class=cF0> </span><span class=cFE>0</span><span class=cF0>;
<a name="l62"></a>}
<a name="l63"></a>
<a name="l64"></a></span><span class=cF9>CMemberListMeta</span><span class=cF0> *</span><span class=cF5>MemberMetaFind</span><span class=cF0>(</span><span class=cF1>U8</span><span class=cF0> *needle_str, </span><span class=cF9>CMemberList</span><span class=cF0> *haystack_member_list)
<a name="l65"></a>{</span><span class=cF2>//Find meta data name, return meta data struct. See </span><a href="https://tomawezome.github.io/ZealOS/Demo/ClassMeta.html#l1"><span class=cF4>::/Demo/ClassMeta.CC</span></a><span class=cF2>.</span><span class=cF0>
<a name="l66"></a>    </span><span class=cF9>CMemberListMeta</span><span class=cF0> *meta = haystack_member_list-&gt;meta;
<a name="l67"></a>
<a name="l68"></a>    </span><span class=cF1>while</span><span class=cF0> (meta)
<a name="l69"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l70"></a>        </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF5>StrCompare</span><span class=cF7>(</span><span class=cF0>meta-&gt;str, needle_str</span><span class=cF7>)</span><span class=cF0>)
<a name="l71"></a>            </span><span class=cF1>return</span><span class=cF0> meta;
<a name="l72"></a>        meta = meta-&gt;next;
<a name="l73"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l74"></a>
<a name="l75"></a>    </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l76"></a>}
<a name="l77"></a>
<a name="l78"></a></span><span class=cF9>CMemberList</span><span class=cF0> *</span><span class=cF5>MemberFind</span><span class=cF0>(</span><span class=cF1>U8</span><span class=cF0> *needle_str, </span><span class=cF9>CHashClass</span><span class=cF0> *haystack_class)
<a name="l79"></a>{</span><span class=cF2>//Find class member. See </span><a href="https://tomawezome.github.io/ZealOS/System/Debug.html#l216"><span class=cF4>ClassRep</span></a><span class=cF2>() and </span><a href="https://tomawezome.github.io/ZealOS/System/DolDoc/DocForm.html#l263"><span class=cF4>DocForm</span></a><span class=cF2>().</span><span class=cF0>
<a name="l80"></a>    </span><span class=cF9>I64</span><span class=cF0>          i;
<a name="l81"></a>    </span><span class=cF9>CMemberList</span><span class=cF0> *tmpm;
<a name="l82"></a>
<a name="l83"></a>    </span><span class=cF1>do</span><span class=cF0>
<a name="l84"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l85"></a>        tmpm = haystack_class-&gt;member_list_and_root;
<a name="l86"></a>        </span><span class=cF1>while</span><span class=cF0> (tmpm)
<a name="l87"></a>        {
<a name="l88"></a>            </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>i = </span><span class=cF5>StrCompare</span><span class=cF0>(tmpm-&gt;str, needle_str)</span><span class=cF7>)</span><span class=cF0>)
<a name="l89"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l90"></a>                tmpm-&gt;use_count++;
<a name="l91"></a>                </span><span class=cF1>return</span><span class=cF0> tmpm;
<a name="l92"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l93"></a>            </span><span class=cF1>if</span><span class=cF0> (i &lt;= </span><span class=cFE>0</span><span class=cF0>)
<a name="l94"></a>                tmpm = tmpm-&gt;left;
<a name="l95"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l96"></a>                tmpm = tmpm-&gt;right;
<a name="l97"></a>        }
<a name="l98"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l99"></a>    </span><span class=cF1>while</span><span class=cF0> (haystack_class = haystack_class-&gt;base_class);
<a name="l100"></a>
<a name="l101"></a>    </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l102"></a>}
<a name="l103"></a>
<a name="l104"></a></span><span class=cF9>CMemberList</span><span class=cF0> *</span><span class=cF5>MemberClassBaseFind</span><span class=cF0>(</span><span class=cF9>CHashClass</span><span class=cF0> *needle_class, </span><span class=cF9>CHashClass</span><span class=cF0> *haystack_class)
<a name="l105"></a>{</span><span class=cF2>//Find class member class base. For finding dup class local vars.</span><span class=cF0>
<a name="l106"></a>    </span><span class=cF9>CMemberList</span><span class=cF0> *tmpm;
<a name="l107"></a>
<a name="l108"></a>    tmpm = haystack_class-&gt;member_class_base_root;
<a name="l109"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpm)
<a name="l110"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l111"></a>        </span><span class=cF1>if</span><span class=cF0> (needle_class == tmpm-&gt;member_class_base)
<a name="l112"></a>            </span><span class=cF1>return</span><span class=cF0> tmpm;
<a name="l113"></a>        </span><span class=cF1>if</span><span class=cF0> (needle_class &lt; tmpm-&gt;member_class_base)
<a name="l114"></a>            tmpm = tmpm-&gt;left_class_base;
<a name="l115"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l116"></a>            tmpm = tmpm-&gt;right_class_base;
<a name="l117"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l118"></a>
<a name="l119"></a>    </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l120"></a>}
<a name="l121"></a>
<a name="l122"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cFD>MemberAdd</span><span class=cF0>(</span><span class=cF9>CCompCtrl</span><span class=cF0> *cc, </span><span class=cF9>CMemberList</span><span class=cF0> *tmpm, </span><span class=cF9>CHashClass</span><span class=cF0> *tmpc, </span><span class=cF9>I64</span><span class=cF0> mode)
<a name="l123"></a>{
<a name="l124"></a>    </span><span class=cF1>U8</span><span class=cF0>           *st = tmpm-&gt;str;
<a name="l125"></a>    </span><span class=cF9>CMemberList</span><span class=cF0> **tmpm1, *tmpm2;
<a name="l126"></a>
<a name="l127"></a>    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>MemberFind</span><span class=cF7>(</span><span class=cF0>st, tmpc</span><span class=cF7>)</span><span class=cF0> &amp;&amp; </span><span class=cF5>StrCompare</span><span class=cF7>(</span><span class=cF0>st, </span><span class=cF6>&quot;pad&quot;</span><span class=cF7>)</span><span class=cF0> &amp;&amp; </span><span class=cF5>StrCompare</span><span class=cF7>(</span><span class=cF0>st, </span><span class=cF6>&quot;reserved&quot;</span><span class=cF7>)</span><span class=cF0> &amp;&amp; </span><span class=cF5>StrCompare</span><span class=cF7>(</span><span class=cF0>st, </span><span class=cF6>&quot;_anon_&quot;</span><span class=cF7>)</span><span class=cF0>)
<a name="l128"></a>        </span><span class=cF5>LexExcept</span><span class=cF0>(cc, </span><span class=cF6>&quot;Duplicate member at &quot;</span><span class=cF0>);
<a name="l129"></a>    tmpm1 = &amp;tmpc-&gt;member_list_and_root;
<a name="l130"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpm2 = *tmpm1)
<a name="l131"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l132"></a>        </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>StrCompare</span><span class=cF7>(</span><span class=cF0>tmpm2-&gt;str, st</span><span class=cF7>)</span><span class=cF0> &lt;= </span><span class=cFE>0</span><span class=cF0>)
<a name="l133"></a>            tmpm1 = &amp;tmpm2-&gt;left;
<a name="l134"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l135"></a>            tmpm1 = &amp;tmpm2-&gt;right;
<a name="l136"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l137"></a>    *tmpm1 = tmpm;
<a name="l138"></a>
<a name="l139"></a>    </span><span class=cF1>if</span><span class=cF0> (mode == </span><span class=cF3>PRS1B_LOCAL_VAR</span><span class=cF0>)
<a name="l140"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l141"></a>        tmpm-&gt;member_class_base = tmpm-&gt;member_class - tmpm-&gt;member_class-&gt;ptr_stars_count;
<a name="l142"></a>        </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>Bt</span><span class=cF7>(</span><span class=cF0>&amp;cc-&gt;opts, </span><span class=cF3>OPTf_WARN_DUP_TYPES</span><span class=cF7>)</span><span class=cF0> &amp;&amp; </span><span class=cF5>MemberClassBaseFind</span><span class=cF7>(</span><span class=cF0>tmpm-&gt;member_class_base, tmpc</span><span class=cF7>)</span><span class=cF0>)
<a name="l143"></a>            </span><span class=cF5>LexWarn</span><span class=cF0>(cc, </span><span class=cF6>&quot;Duplicate type at &quot;</span><span class=cF0>);
<a name="l144"></a>        tmpm1 = &amp;tmpc-&gt;member_class_base_root;
<a name="l145"></a>        </span><span class=cF1>while</span><span class=cF0> (tmpm2 = *tmpm1)
<a name="l146"></a>        {
<a name="l147"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpm-&gt;member_class_base &lt; tmpm2-&gt;member_class_base)
<a name="l148"></a>                tmpm1 = &amp;tmpm2-&gt;left_class_base;
<a name="l149"></a>            </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (tmpm-&gt;member_class_base &gt; tmpm2-&gt;member_class_base)
<a name="l150"></a>                tmpm1 = &amp;tmpm2-&gt;right_class_base;
<a name="l151"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l152"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l153"></a>                tmpm1 = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l154"></a>                </span><span class=cF1>break</span><span class=cF0>;
<a name="l155"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l156"></a>        }
<a name="l157"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpm1)
<a name="l158"></a>            *tmpm1 = tmpm;
<a name="l159"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l160"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l161"></a>        tmpm-&gt;member_class_base = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l162"></a>
<a name="l163"></a>    tmpm-&gt;left = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l164"></a>    tmpm-&gt;right = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l165"></a>    tmpm-&gt;left_class_base = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l166"></a>    tmpm-&gt;right_class_base = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l167"></a>    tmpm2 = tmpc-&gt;last_in_member_list;
<a name="l168"></a>    tmpm2-&gt;next = tmpc-&gt;last_in_member_list = tmpm;
<a name="l169"></a>}
<a name="l170"></a>
<a name="l171"></a></span><span class=cF9>CMemberList</span><span class=cF0> *</span><span class=cFD>MemberListNew</span><span class=cF0>(</span><span class=cF9>I64</span><span class=cF0> _reg)
<a name="l172"></a>{
<a name="l173"></a>    </span><span class=cF9>CMemberList</span><span class=cF0> *res = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF9>CMemberList</span><span class=cF7>)</span><span class=cF0>);
<a name="l174"></a>
<a name="l175"></a>    res-&gt;</span><span class=cF1>reg</span><span class=cF0> = _reg;
<a name="l176"></a>
<a name="l177"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l178"></a>}
<a name="l179"></a>
<a name="l180"></a></span><span class=cF1>Bool</span><span class=cF0> </span><span class=cFD>MemberListCmp</span><span class=cF0>(</span><span class=cF9>CMemberList</span><span class=cF0> *tmpm1, </span><span class=cF9>CMemberList</span><span class=cF0> *tmpm2, </span><span class=cF9>I64</span><span class=cF0> count=</span><span class=cF3>I64_MAX</span><span class=cF0>)
<a name="l181"></a>{
<a name="l182"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpm1 &amp;&amp; tmpm2 &amp;&amp; count--)
<a name="l183"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l184"></a>        </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>StrCompare</span><span class=cF7>(</span><span class=cF0>tmpm1-&gt;str,tmpm2-&gt;str</span><span class=cF7>)</span><span class=cF0> ||
<a name="l185"></a>                tmpm1-&gt;member_class      != tmpm2-&gt;member_class ||
<a name="l186"></a>                tmpm1-&gt;member_class_base != tmpm2-&gt;member_class_base)
<a name="l187"></a>            </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l188"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpm1-&gt;flags &amp; </span><span class=cF3>MLF_DEFAULT_AVAILABLE</span><span class=cF0> || tmpm2-&gt;flags &amp; </span><span class=cF3>MLF_DEFAULT_AVAILABLE</span><span class=cF0>)
<a name="l189"></a>        {
<a name="l190"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpm1-&gt;flags &amp; </span><span class=cF7>(</span><span class=cF3>MLF_DEFAULT_AVAILABLE</span><span class=cF0> | </span><span class=cF3>MLF_STR_DEFAULT_AVAILABLE</span><span class=cF7>)</span><span class=cF0> !=
<a name="l191"></a>                    tmpm2-&gt;flags &amp; </span><span class=cF7>(</span><span class=cF3>MLF_DEFAULT_AVAILABLE</span><span class=cF0> | </span><span class=cF3>MLF_STR_DEFAULT_AVAILABLE</span><span class=cF7>)</span><span class=cF0>)
<a name="l192"></a>                </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l193"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpm1-&gt;flags &amp; </span><span class=cF3>MLF_STR_DEFAULT_AVAILABLE</span><span class=cF0>)
<a name="l194"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l195"></a>                </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>StrCompare</span><span class=cF7>(</span><span class=cF0>tmpm1-&gt;default_val, tmpm2-&gt;default_val</span><span class=cF7>)</span><span class=cF0>)
<a name="l196"></a>                    </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l197"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l198"></a>            </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (tmpm1-&gt;default_val != tmpm2-&gt;default_val)
<a name="l199"></a>                </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l200"></a>        }
<a name="l201"></a>        tmpm1 = tmpm1-&gt;next;
<a name="l202"></a>        tmpm2 = tmpm2-&gt;next;
<a name="l203"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l204"></a>    </span><span class=cF1>if</span><span class=cF0> (count &lt; </span><span class=cFE>0</span><span class=cF0> || !tmpm1 &amp;&amp; !tmpm2)
<a name="l205"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l206"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l207"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l208"></a>}
<a name="l209"></a>
<a name="l210"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>MemberListDel</span><span class=cF0>(</span><span class=cF9>CMemberList</span><span class=cF0> *tmpm)
<a name="l211"></a>{
<a name="l212"></a>    </span><span class=cF9>CMemberList</span><span class=cF0>     *tmpm1;
<a name="l213"></a>    </span><span class=cF9>CMemberListMeta</span><span class=cF0> *tmp_meta, *tmp_meta1;
<a name="l214"></a>
<a name="l215"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpm)
<a name="l216"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l217"></a>        tmpm1 = tmpm-&gt;next;
<a name="l218"></a>        </span><span class=cF5>Free</span><span class=cF0>(tmpm-&gt;str);
<a name="l219"></a>        </span><span class=cF5>LinkedListDel</span><span class=cF0>(tmpm-&gt;dim.next);
<a name="l220"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpm-&gt;flags &amp; </span><span class=cF3>MLF_STR_DEFAULT_AVAILABLE</span><span class=cF0>)
<a name="l221"></a>            </span><span class=cF5>Free</span><span class=cF0>(tmpm-&gt;default_val);
<a name="l222"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpm-&gt;flags &amp; </span><span class=cF3>MLF_FUN</span><span class=cF0>)
<a name="l223"></a>            </span><span class=cF5>HashDel</span><span class=cF0>(tmpm-&gt;fun_ptr - tmpm-&gt;fun_ptr-&gt;ptr_stars_count);
<a name="l224"></a>        tmp_meta = tmpm-&gt;meta;
<a name="l225"></a>        </span><span class=cF1>while</span><span class=cF0> (tmp_meta)
<a name="l226"></a>        {
<a name="l227"></a>            tmp_meta1 = tmp_meta-&gt;next;
<a name="l228"></a>            </span><span class=cF5>Free</span><span class=cF0>(tmp_meta-&gt;str);
<a name="l229"></a>            </span><span class=cF1>if</span><span class=cF0> (tmp_meta-&gt;flags &amp; </span><span class=cF3>MLMF_IS_STR</span><span class=cF0>)
<a name="l230"></a>                </span><span class=cF5>Free</span><span class=cF0>(tmp_meta-&gt;user_data);
<a name="l231"></a>            </span><span class=cF5>Free</span><span class=cF0>(tmp_meta);
<a name="l232"></a>            tmp_meta = tmp_meta1;
<a name="l233"></a>        }
<a name="l234"></a>        </span><span class=cF5>Free</span><span class=cF0>(tmpm);
<a name="l235"></a>        tmpm = tmpm1;
<a name="l236"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l237"></a>}
<a name="l238"></a>
<a name="l239"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>ClassMemberListDel</span><span class=cF0>(</span><span class=cF9>CHashClass</span><span class=cF0> *tmpc)
<a name="l240"></a>{
<a name="l241"></a>    </span><span class=cF5>MemberListDel</span><span class=cF0>(tmpc-&gt;member_list_and_root);
<a name="l242"></a>    tmpc-&gt;size = </span><span class=cFE>0</span><span class=cF0>;
<a name="l243"></a>    tmpc-&gt;last_in_member_list = &amp;tmpc-&gt;member_list_and_root;
<a name="l244"></a>    tmpc-&gt;member_list_and_root = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l245"></a>    tmpc-&gt;member_class_base_root = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l246"></a>    tmpc-&gt;member_count = </span><span class=cFE>0</span><span class=cF0>;
<a name="l247"></a>    </span><span class=cF1>if</span><span class=cF0> (tmpc-&gt;type &amp; </span><span class=cF3>HTT_FUN</span><span class=cF0>)
<a name="l248"></a>        tmpc(</span><span class=cF9>CHashFun</span><span class=cF0> *)-&gt;arg_count = </span><span class=cFE>0</span><span class=cF0>;
<a name="l249"></a>}
<a name="l250"></a>
<a name="l251"></a></span><span class=cF9>I64</span><span class=cF0> </span><span class=cFD>MemberListSize</span><span class=cF0>(</span><span class=cF9>CHashClass</span><span class=cF0> *tmpc)
<a name="l252"></a>{
<a name="l253"></a>    </span><span class=cF9>CMemberList</span><span class=cF0>     *tmpm;
<a name="l254"></a>    </span><span class=cF9>CMemberListMeta</span><span class=cF0> *tmp_meta;
<a name="l255"></a>    </span><span class=cF9>I64</span><span class=cF0>              res = </span><span class=cFE>0</span><span class=cF0>;
<a name="l256"></a>
<a name="l257"></a>    tmpm = tmpc-&gt;member_list_and_root;
<a name="l258"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpm)
<a name="l259"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l260"></a>        res += </span><span class=cF5>MSize2</span><span class=cF0>(tmpm-&gt;str);
<a name="l261"></a>        res += </span><span class=cF5>LinkedListSize</span><span class=cF0>(tmpm-&gt;dim.next);
<a name="l262"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpm-&gt;flags &amp; </span><span class=cF3>MLF_STR_DEFAULT_AVAILABLE</span><span class=cF0>)
<a name="l263"></a>            res += </span><span class=cF5>MSize2</span><span class=cF0>(tmpm-&gt;default_val);
<a name="l264"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpm-&gt;flags &amp; </span><span class=cF3>MLF_FUN</span><span class=cF0>)
<a name="l265"></a>            res += </span><span class=cF5>HashEntrySize2</span><span class=cF0>(tmpm-&gt;fun_ptr - tmpm-&gt;fun_ptr-&gt;ptr_stars_count);
<a name="l266"></a>        tmp_meta = tmpm-&gt;meta;
<a name="l267"></a>        </span><span class=cF1>while</span><span class=cF0> (tmp_meta)
<a name="l268"></a>        {
<a name="l269"></a>            res += </span><span class=cF5>MSize2</span><span class=cF0>(tmp_meta-&gt;str);
<a name="l270"></a>            </span><span class=cF1>if</span><span class=cF0> (tmp_meta-&gt;flags &amp; </span><span class=cF3>MLMF_IS_STR</span><span class=cF0>)
<a name="l271"></a>                res += </span><span class=cF5>MSize2</span><span class=cF0>(tmp_meta-&gt;user_data);
<a name="l272"></a>            res += </span><span class=cF5>MSize2</span><span class=cF0>(tmp_meta);
<a name="l273"></a>            tmp_meta = tmp_meta-&gt;next;
<a name="l274"></a>        }
<a name="l275"></a>        res += </span><span class=cF5>MSize2</span><span class=cF0>(tmpm);
<a name="l276"></a>        tmpm = tmpm-&gt;next;
<a name="l277"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l278"></a>
<a name="l279"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l280"></a>}
<a name="l281"></a>
<a name="l282"></a></span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF5>LexExtStr</span><span class=cF0>(</span><span class=cF9>CCompCtrl</span><span class=cF0> *cc, </span><span class=cF9>I64</span><span class=cF0> *_size=</span><span class=cF3>NULL</span><span class=cF0>, </span><span class=cF1>Bool</span><span class=cF0> lex_next=</span><span class=cF3>TRUE</span><span class=cF0>)
<a name="l283"></a>{</span><span class=cF2>//Lex </span><a href="https://tomawezome.github.io/ZealOS/Kernel/KernelA.html#l2215"><span class=cF4>TK_STR</span></a><span class=cF2>'s to one combined str. _size includes terminator.</span><span class=cF0>
<a name="l284"></a>    </span><span class=cF9>I64</span><span class=cF0> len = cc-&gt;cur_str_len, len1, len2;
<a name="l285"></a>    </span><span class=cF1>U8</span><span class=cF0> *st = cc-&gt;cur_str, *st1, *st2;
<a name="l286"></a>
<a name="l287"></a>    cc-&gt;cur_str = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l288"></a>    </span><span class=cF1>while</span><span class=cF0> (cc-&gt;token == </span><span class=cF3>TK_STR</span><span class=cF0>)
<a name="l289"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l290"></a>        st1 = st;
<a name="l291"></a>        len1 = len;
<a name="l292"></a>        </span><span class=cF1>if</span><span class=cF0> (!lex_next &amp;&amp; </span><span class=cF5>LexCharGet</span><span class=cF7>(</span><span class=cF0>cc</span><span class=cF7>)</span><span class=cF0> != </span><span class=cF6>'\\'</span><span class=cF0>)
<a name="l293"></a>        {
<a name="l294"></a>            cc-&gt;flags |= </span><span class=cF3>CCF_USE_LAST_U16</span><span class=cF0>;
<a name="l295"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l296"></a>        }
<a name="l297"></a>        </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>Lex</span><span class=cF7>(</span><span class=cF0>cc</span><span class=cF7>)</span><span class=cF0> == </span><span class=cF3>TK_STR</span><span class=cF0>)
<a name="l298"></a>        {
<a name="l299"></a>            len2 = cc-&gt;cur_str_len;
<a name="l300"></a>            st2 = cc-&gt;cur_str;
<a name="l301"></a>            cc-&gt;cur_str = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l302"></a>            len = len1 + len2 - </span><span class=cFE>1</span><span class=cF0>;
<a name="l303"></a>            st = </span><span class=cF5>MAlloc</span><span class=cF0>(len);
<a name="l304"></a>            </span><span class=cF1>if</span><span class=cF0> (len1 &gt; </span><span class=cFE>1</span><span class=cF0>)
<a name="l305"></a>                </span><span class=cF5>MemCopy</span><span class=cF0>(st, st1, len1 - </span><span class=cFE>1</span><span class=cF0>);
<a name="l306"></a>            </span><span class=cF5>MemCopy</span><span class=cF0>(st + len1 - </span><span class=cFE>1</span><span class=cF0>, st2, len2);
<a name="l307"></a>            </span><span class=cF5>Free</span><span class=cF0>(st1);
<a name="l308"></a>            </span><span class=cF5>Free</span><span class=cF0>(st2);
<a name="l309"></a>        }
<a name="l310"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l311"></a>    </span><span class=cF1>if</span><span class=cF0> (_size)
<a name="l312"></a>        *_size = len;
<a name="l313"></a>
<a name="l314"></a>    </span><span class=cF1>return</span><span class=cF0> st;
<a name="l315"></a>}
</span></pre></body>
</html>
