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
<a name="l1"></a><span class=cF0>#</span><span class=cF1>help_index</span><span class=cF0> </span><span class=cF6>&quot;DolDoc/Misc&quot;</span><span class=cF0>
<a name="l2"></a>
<a name="l3"></a></span><span class=cF1>U8</span><span class=cF0> </span><span class=cFB>captured_macro_name</span><span class=cF0>[</span><span class=cF3>STR_LEN</span><span class=cF0>];
<a name="l4"></a></span><span class=cF5>StrCopy</span><span class=cF0>(</span><span class=cFB>captured_macro_name</span><span class=cF0>, </span><span class=cF6>&quot;Test&quot;</span><span class=cF0>);
<a name="l5"></a>
<a name="l6"></a></span><span class=cF9>I64</span><span class=cF0> </span><span class=cFB>sys_macro_repeat_n</span><span class=cF0> = </span><span class=cFE>1</span><span class=cF0>;
<a name="l7"></a>
<a name="l8"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>SysMacroStripKey</span><span class=cF0>(</span><span class=cF9>CJob</span><span class=cF0> *macro_head, </span><span class=cF9>I64</span><span class=cF0> arg1, </span><span class=cF9>I64</span><span class=cF0> arg2)
<a name="l9"></a>{
<a name="l10"></a>    </span><span class=cF9>CJob</span><span class=cF0> *tmpc,*tmpc1;
<a name="l11"></a>
<a name="l12"></a>    tmpc = macro_head-&gt;next;
<a name="l13"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpc != macro_head)
<a name="l14"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l15"></a>        tmpc1 = tmpc-&gt;next;
<a name="l16"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpc-&gt;job_code == </span><span class=cF3>JOBT_MESSAGE</span><span class=cF0> &amp;&amp;
<a name="l17"></a>            </span><span class=cF7>(</span><span class=cF0>tmpc-&gt;message_code == </span><span class=cF3>MESSAGE_KEY_DOWN</span><span class=cF0> ||
<a name="l18"></a>             tmpc-&gt;message_code == </span><span class=cF3>MESSAGE_KEY_UP</span><span class=cF0> ||
<a name="l19"></a>             tmpc-&gt;message_code == </span><span class=cF3>MESSAGE_KEY_DOWN_UP</span><span class=cF7>)</span><span class=cF0> &amp;&amp;
<a name="l20"></a>            arg1 &amp;&amp; tmpc-&gt;aux1 == arg1 || !arg1 &amp;&amp; tmpc-&gt;aux2 == arg2)
<a name="l21"></a>        {
<a name="l22"></a>            </span><span class=cF5>QueueRemove</span><span class=cF0>(tmpc);
<a name="l23"></a>            </span><span class=cF5>JobDel</span><span class=cF0>(tmpc);
<a name="l24"></a>        }
<a name="l25"></a>        tmpc = tmpc1;
<a name="l26"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l27"></a>}
<a name="l28"></a>
<a name="l29"></a>#</span><span class=cF1>define</span><span class=cF0> </span><span class=cF3>MT_NULL</span><span class=cF0>     </span><span class=cFE>0</span><span class=cF0>
<a name="l30"></a>#</span><span class=cF1>define</span><span class=cF0> </span><span class=cF3>MT_MESSAGE</span><span class=cF0>  </span><span class=cFE>1</span><span class=cF0>
<a name="l31"></a>#</span><span class=cF1>define</span><span class=cF0> </span><span class=cF3>MT_CHAR</span><span class=cF0>     </span><span class=cFE>2</span><span class=cF0>
<a name="l32"></a>
<a name="l33"></a></span><span class=cF1>class</span><span class=cF0> </span><span class=cF9>CMacroTmp</span><span class=cF0>
<a name="l34"></a>{
<a name="l35"></a>    </span><span class=cF9>CMacroTmp</span><span class=cF0>   *next, *last;
<a name="l36"></a>    </span><span class=cF9>I64</span><span class=cF0>          type;
<a name="l37"></a>    </span><span class=cF1>U8</span><span class=cF0>           buf[</span><span class=cF3>STR_LEN</span><span class=cF0>];
<a name="l38"></a>};
<a name="l39"></a>
<a name="l40"></a></span><span class=cF9>CMacroTmp</span><span class=cF0> *</span><span class=cF5>Cmd2MT</span><span class=cF0>(</span><span class=cF9>CJob</span><span class=cF0> *tmpc)
<a name="l41"></a>{
<a name="l42"></a>    </span><span class=cF1>U8</span><span class=cF0>           buf[</span><span class=cFE>8</span><span class=cF0>];
<a name="l43"></a>    </span><span class=cF9>CMacroTmp</span><span class=cF0>   *tmpmt = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF9>CMacroTmp</span><span class=cF7>)</span><span class=cF0>);
<a name="l44"></a>
<a name="l45"></a>    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>Bt</span><span class=cF7>(</span><span class=cFB>char_bmp_macro</span><span class=cF0>, tmpc-&gt;aux1</span><span class=cF7>)</span><span class=cF0> &amp;&amp; tmpc-&gt;message_code == </span><span class=cF3>MESSAGE_KEY_DOWN</span><span class=cF0>)
<a name="l46"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l47"></a>        tmpmt-&gt;type = </span><span class=cF3>MT_CHAR</span><span class=cF0>;
<a name="l48"></a>        buf[</span><span class=cFE>0</span><span class=cF0>] = tmpc-&gt;aux1;
<a name="l49"></a>        buf[</span><span class=cFE>1</span><span class=cF0>] = </span><span class=cFE>0</span><span class=cF0>;
<a name="l50"></a>        </span><span class=cF5>StrPrint</span><span class=cF0>(tmpmt-&gt;buf, </span><span class=cF6>&quot;%Q&quot;</span><span class=cF0>, buf);
<a name="l51"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l52"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l53"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l54"></a>        tmpmt-&gt;type = </span><span class=cF3>MT_MESSAGE</span><span class=cF0>;
<a name="l55"></a>        </span><span class=cF5>StrPrint</span><span class=cF0>(tmpmt-&gt;buf, </span><span class=cF6>&quot;Message(0x%X,0x%X,0x%X);&quot;</span><span class=cF0>, tmpc-&gt;message_code, tmpc-&gt;aux1, tmpc-&gt;aux2);
<a name="l56"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l57"></a>
<a name="l58"></a>    </span><span class=cF1>return</span><span class=cF0> tmpmt;
<a name="l59"></a>}
<a name="l60"></a>
<a name="l61"></a></span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF5>SysMacro2Str</span><span class=cF0>(</span><span class=cF9>CJob</span><span class=cF0> *macro_head)
<a name="l62"></a>{
<a name="l63"></a>    </span><span class=cF9>CJob</span><span class=cF0>        *tmpc;
<a name="l64"></a>    </span><span class=cF9>I64</span><span class=cF0>          count = </span><span class=cFE>1</span><span class=cF0>; </span><span class=cF2>//terminating zero</span><span class=cF0>
<a name="l65"></a>    </span><span class=cF1>U8</span><span class=cF0>          *ptr, *m;
<a name="l66"></a>    </span><span class=cF9>CMacroTmp</span><span class=cF0>   *tmpmt, *tmpmt1,head;
<a name="l67"></a>
<a name="l68"></a>    </span><span class=cF5>LBtr</span><span class=cF0>(&amp;</span><span class=cFB>sys_semas</span><span class=cF0>[</span><span class=cF3>SEMA_RECORD_MACRO</span><span class=cF0>], </span><span class=cFE>0</span><span class=cF0>);
<a name="l69"></a>
<a name="l70"></a>    </span><span class=cF5>QueueInit</span><span class=cF0>(&amp;head);
<a name="l71"></a>    head.type = </span><span class=cF3>MT_NULL</span><span class=cF0>;
<a name="l72"></a>    tmpc = macro_head-&gt;next;
<a name="l73"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpc != macro_head)
<a name="l74"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l75"></a>        tmpmt = </span><span class=cF5>Cmd2MT</span><span class=cF0>(tmpc);
<a name="l76"></a>        </span><span class=cF5>QueueInsert</span><span class=cF0>(tmpmt, head.last);
<a name="l77"></a>        count += </span><span class=cF5>StrLen</span><span class=cF0>(tmpmt-&gt;buf);
<a name="l78"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpmt-&gt;type == </span><span class=cF3>MT_CHAR</span><span class=cF0>)
<a name="l79"></a>        {
<a name="l80"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpmt-&gt;last-&gt;type != </span><span class=cF3>MT_CHAR</span><span class=cF0>)
<a name="l81"></a>                count += </span><span class=cF5>StrLen</span><span class=cF0>(</span><span class=cF6>&quot;\&quot;&quot;</span><span class=cF0>);
<a name="l82"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpmt-&gt;next-&gt;type != </span><span class=cF3>MT_CHAR</span><span class=cF0>)
<a name="l83"></a>                count += </span><span class=cF5>StrLen</span><span class=cF0>(</span><span class=cF6>&quot;\&quot;;&quot;</span><span class=cF0>);
<a name="l84"></a>        }
<a name="l85"></a>        tmpc = tmpc-&gt;next;
<a name="l86"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l87"></a>
<a name="l88"></a>    m = </span><span class=cF5>MAlloc</span><span class=cF0>(count);
<a name="l89"></a>    ptr = m;
<a name="l90"></a>
<a name="l91"></a>    tmpmt = head.next;
<a name="l92"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpmt != &amp;head)
<a name="l93"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l94"></a>        tmpmt1 = tmpmt-&gt;next;
<a name="l95"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpmt-&gt;type == </span><span class=cF3>MT_MESSAGE</span><span class=cF0>)
<a name="l96"></a>        {
<a name="l97"></a>            </span><span class=cF5>StrCopy</span><span class=cF0>(ptr, tmpmt-&gt;buf);
<a name="l98"></a>            ptr += </span><span class=cF5>StrLen</span><span class=cF0>(tmpmt-&gt;buf);
<a name="l99"></a>        }
<a name="l100"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l101"></a>        {
<a name="l102"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpmt-&gt;last-&gt;type != </span><span class=cF3>MT_CHAR</span><span class=cF0>)
<a name="l103"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l104"></a>                </span><span class=cF5>StrCopy</span><span class=cF0>(ptr, </span><span class=cF6>&quot;\&quot;&quot;</span><span class=cF0>);
<a name="l105"></a>                ptr += </span><span class=cF5>StrLen</span><span class=cF0>(</span><span class=cF6>&quot;\&quot;&quot;</span><span class=cF0>);
<a name="l106"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l107"></a>            </span><span class=cF5>StrCopy</span><span class=cF0>(ptr, tmpmt-&gt;buf);
<a name="l108"></a>            ptr += </span><span class=cF5>StrLen</span><span class=cF0>(tmpmt-&gt;buf);
<a name="l109"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpmt-&gt;next-&gt;type != </span><span class=cF3>MT_CHAR</span><span class=cF0>)
<a name="l110"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l111"></a>                </span><span class=cF5>StrCopy</span><span class=cF0>(ptr, </span><span class=cF6>&quot;\&quot;;&quot;</span><span class=cF0>);
<a name="l112"></a>                ptr += </span><span class=cF5>StrLen</span><span class=cF0>(</span><span class=cF6>&quot;\&quot;;&quot;</span><span class=cF0>);
<a name="l113"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l114"></a>        }
<a name="l115"></a>        </span><span class=cF5>Free</span><span class=cF0>(tmpmt);
<a name="l116"></a>        tmpmt = tmpmt1;
<a name="l117"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l118"></a>    *ptr = </span><span class=cFE>0</span><span class=cF0>;
<a name="l119"></a>
<a name="l120"></a>    </span><span class=cF1>return</span><span class=cF0> m;
<a name="l121"></a>}
<a name="l122"></a>
<a name="l123"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>PlaySysMacro</span><span class=cF0>(</span><span class=cF9>I64</span><span class=cF0> n=</span><span class=cFE>1</span><span class=cF0>)
<a name="l124"></a>{
<a name="l125"></a>    </span><span class=cF9>CTask</span><span class=cF0>   *task = </span><span class=cFB>sys_focus_task</span><span class=cF0>;
<a name="l126"></a>    </span><span class=cF1>U8</span><span class=cF0>      *m;
<a name="l127"></a>
<a name="l128"></a>    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>TaskValidate</span><span class=cF7>(</span><span class=cF0>task</span><span class=cF7>)</span><span class=cF0>)
<a name="l129"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l130"></a>        </span><span class=cF5>LBtr</span><span class=cF0>(&amp;</span><span class=cFB>sys_semas</span><span class=cF0>[</span><span class=cF3>SEMA_RECORD_MACRO</span><span class=cF0>], </span><span class=cFE>0</span><span class=cF0>);
<a name="l131"></a>        m = </span><span class=cF5>SysMacro2Str</span><span class=cF0>(&amp;</span><span class=cFB>sys_macro_head</span><span class=cF0>);
<a name="l132"></a>        </span><span class=cF1>while</span><span class=cF0> (n-- &amp;&amp; </span><span class=cF5>TaskValidate</span><span class=cF7>(</span><span class=cF0>task</span><span class=cF7>)</span><span class=cF0>)
<a name="l133"></a>        {
<a name="l134"></a>            </span><span class=cF1>if</span><span class=cF0> (task == </span><span class=cF5>Fs</span><span class=cF0>)
<a name="l135"></a>                </span><span class=cF5>InStr</span><span class=cF0>(</span><span class=cF6>&quot;%s&quot;</span><span class=cF0>, m);
<a name="l136"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l137"></a>                </span><span class=cF5>XTalkStrWait</span><span class=cF0>(task, </span><span class=cF6>&quot;%s&quot;</span><span class=cF0>, m);
<a name="l138"></a>        }
<a name="l139"></a>        </span><span class=cF5>Free</span><span class=cF0>(m);
<a name="l140"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l141"></a>}
<a name="l142"></a>
<a name="l143"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>EdInsCapturedMacro</span><span class=cF0>()
<a name="l144"></a>{
<a name="l145"></a>    </span><span class=cF1>U8</span><span class=cF0> *st = </span><span class=cF5>SysMacro2Str</span><span class=cF0>(&amp;</span><span class=cFB>sys_macro_head</span><span class=cF0>);
<a name="l146"></a>
<a name="l147"></a>    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cFB>sys_focus_task</span><span class=cF0>)
<a name="l148"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l149"></a>        </span><span class=cF5>XTalk</span><span class=cF0>(</span><span class=cFB>sys_focus_task</span><span class=cF0>, </span><span class=cF6>&quot;$MA+LIS,T=\&quot;%s\&quot;,LM=\&quot;%$Q\&quot;$&quot;</span><span class=cF0>, </span><span class=cFB>captured_macro_name</span><span class=cF0>, st);
<a name="l150"></a>        </span><span class=cF5>Free</span><span class=cF0>(st);
<a name="l151"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l152"></a>}
<a name="l153"></a>
<a name="l154"></a>#</span><span class=cF1>define</span><span class=cF0> </span><span class=cF3>SM_RECORD</span><span class=cF0>       </span><span class=cFE>0</span><span class=cF0>
<a name="l155"></a>#</span><span class=cF1>define</span><span class=cF0> </span><span class=cF3>SM_INS</span><span class=cF0>          </span><span class=cFE>1</span><span class=cF0>
<a name="l156"></a>#</span><span class=cF1>define</span><span class=cF0> </span><span class=cF3>SM_PLAY</span><span class=cF0>         </span><span class=cFE>2</span><span class=cF0>
<a name="l157"></a>#</span><span class=cF1>define</span><span class=cF0> </span><span class=cF3>SM_REPEAT_N</span><span class=cF0>     </span><span class=cFE>3</span><span class=cF0>
<a name="l158"></a>#</span><span class=cF1>define</span><span class=cF0> </span><span class=cF3>SM_STOP</span><span class=cF0>         </span><span class=cFE>4</span><span class=cF0>
<a name="l159"></a>
<a name="l160"></a></span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>PopUpMacroMenu</span><span class=cF0>()
<a name="l161"></a>{
<a name="l162"></a>    </span><span class=cF9>I64</span><span class=cF0>          res = </span><span class=cFE>0</span><span class=cF0>;
<a name="l163"></a>    </span><span class=cF1>U8</span><span class=cF0>           buf[</span><span class=cF3>STR_LEN</span><span class=cF0>];
<a name="l164"></a>    </span><span class=cF9>CJob</span><span class=cF0>        *tmpc;
<a name="l165"></a>    </span><span class=cF9>CDoc</span><span class=cF0>        *doc = </span><span class=cF5>DocNew</span><span class=cF0>;
<a name="l166"></a>    </span><span class=cF9>CDocEntry</span><span class=cF0>   *doc_e = </span><span class=cF5>DocPrint</span><span class=cF0>(doc, </span><span class=cF6>&quot;$DA-P,LEN=STR_LEN-1,A=\&quot;Name:%%s\&quot;$&quot;</span><span class=cF0>);
<a name="l167"></a>
<a name="l168"></a>    doc_e-&gt;data = </span><span class=cFB>captured_macro_name</span><span class=cF0>;
<a name="l169"></a>    </span><span class=cF5>DocDataFormat</span><span class=cF0>(doc, doc_e);
<a name="l170"></a>
<a name="l171"></a>    doc_e = </span><span class=cF5>DocPrint</span><span class=cF0>(doc, </span><span class=cF6>&quot;\n$DA,A=\&quot;Repeat N:%%d\&quot;$&quot;</span><span class=cF0>);
<a name="l172"></a>    doc_e-&gt;data = &amp;</span><span class=cFB>sys_macro_repeat_n</span><span class=cF0>;
<a name="l173"></a>    </span><span class=cF5>DocDataFormat</span><span class=cF0>(doc, doc_e);
<a name="l174"></a>
<a name="l175"></a>    </span><span class=cF5>DocPrint</span><span class=cF0>(doc,</span><span class=cF6>&quot;\n&quot;</span><span class=cF0>
<a name="l176"></a>                </span><span class=cF6>&quot;$CM+LX,1,3$$BT,\&quot;RECORD\&quot;,LE=SM_RECORD$&quot;</span><span class=cF0>
<a name="l177"></a>                </span><span class=cF6>&quot;$CM+LX,17,0$$BT,\&quot;INSERT\&quot;,LE=SM_INS$&quot;</span><span class=cF0>
<a name="l178"></a>                </span><span class=cF6>&quot;$CM+LX,1,3$$BT,\&quot;PLAY\&quot;,LE=SM_PLAY$&quot;</span><span class=cF0>
<a name="l179"></a>                </span><span class=cF6>&quot;$CM+LX,17,0$$BT,\&quot;REPEAT N\&quot;,LE=SM_REPEAT_N$&quot;</span><span class=cF0>
<a name="l180"></a>                </span><span class=cF6>&quot;$CM+LX,1,3$$BT,\&quot;STOP\&quot;,LE=SM_STOP$&quot;</span><span class=cF0>
<a name="l181"></a>                </span><span class=cF6>&quot;$CM+LX,17,0$$BT,\&quot;CANCEL\&quot;,LE=DOCM_CANCEL$&quot;</span><span class=cF0>
<a name="l182"></a>                </span><span class=cF6>&quot;\n\n\n$GREEN$SHIFT-F2$FG$ will play macro.\n&quot;</span><span class=cF0>);
<a name="l183"></a>
<a name="l184"></a>    doc-&gt;flags |= </span><span class=cF3>DOCF_SIZE_MIN</span><span class=cF0> | </span><span class=cF3>DOCF_FORM</span><span class=cF0>;
<a name="l185"></a>    </span><span class=cF5>StrPrint</span><span class=cF0>(buf, </span><span class=cF6>&quot;DocMenu(%d);&quot;</span><span class=cF0>, doc);
<a name="l186"></a>    </span><span class=cFB>sys_macro_task</span><span class=cF0> = </span><span class=cF5>Spawn</span><span class=cF0>(&amp;</span><span class=cF5>ServerCmdLine</span><span class=cF0>, </span><span class=cF3>NULL</span><span class=cF0>, </span><span class=cF6>&quot;Macro Popup&quot;</span><span class=cF0>,, </span><span class=cF5>Fs</span><span class=cF0>);
<a name="l187"></a>    </span><span class=cF5>Fs</span><span class=cF0>-&gt;popup_task = </span><span class=cFB>sys_macro_task</span><span class=cF0>;
<a name="l188"></a>    </span><span class=cF5>LBts</span><span class=cF0>(&amp;</span><span class=cFB>sys_macro_task</span><span class=cF0>-&gt;display_flags, </span><span class=cF3>DISPLAYf_WIN_ON_TOP</span><span class=cF0>);
<a name="l189"></a>    tmpc = </span><span class=cF5>TaskExe</span><span class=cF0>(</span><span class=cFB>sys_macro_task</span><span class=cF0>, </span><span class=cF5>Fs</span><span class=cF0>, buf, </span><span class=cFE>1</span><span class=cF0> &lt;&lt; </span><span class=cF3>JOBf_WAKE_MASTER</span><span class=cF0> | </span><span class=cFE>1</span><span class=cF0> &lt;&lt; </span><span class=cF3>JOBf_FOCUS_MASTER</span><span class=cF0>);
<a name="l190"></a>    </span><span class=cF5>JobResScan</span><span class=cF0>(tmpc, &amp;res);
<a name="l191"></a>    </span><span class=cF5>Fs</span><span class=cF0>-&gt;popup_task = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l192"></a>    </span><span class=cF5>Kill</span><span class=cF0>(</span><span class=cFB>sys_macro_task</span><span class=cF0>);
<a name="l193"></a>    </span><span class=cFB>sys_macro_task</span><span class=cF0> = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l194"></a>    </span><span class=cF5>DocDataScan</span><span class=cF0>(doc, doc_e);
<a name="l195"></a>    </span><span class=cF5>DocDel</span><span class=cF0>(doc);
<a name="l196"></a>
<a name="l197"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l198"></a>}
<a name="l199"></a>
<a name="l200"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>MacroTask</span><span class=cF0>(</span><span class=cF9>I64</span><span class=cF0>)
<a name="l201"></a>{
<a name="l202"></a>    </span><span class=cF9>I64</span><span class=cF0> i;
<a name="l203"></a>
<a name="l204"></a>    </span><span class=cF5>StrCopy</span><span class=cF0>(</span><span class=cFB>captured_macro_name</span><span class=cF0>, </span><span class=cF6>&quot;Click Here&quot;</span><span class=cF0>);
<a name="l205"></a>    </span><span class=cFB>sys_macro_repeat_n</span><span class=cF0> = </span><span class=cFE>1</span><span class=cF0>;
<a name="l206"></a>    </span><span class=cF1>do</span><span class=cF0>
<a name="l207"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l208"></a>        i = </span><span class=cF5>PopUpMacroMenu</span><span class=cF0>;
<a name="l209"></a>        </span><span class=cF5>WinRefocus</span><span class=cF0>(</span><span class=cFB>sys_focus_task</span><span class=cF0>);
<a name="l210"></a>        </span><span class=cF1>switch</span><span class=cF0> (i)
<a name="l211"></a>        {
<a name="l212"></a>            </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>SM_RECORD</span><span class=cF0>:
<a name="l213"></a>                </span><span class=cF5>LBtr</span><span class=cF0>(&amp;</span><span class=cFB>sys_semas</span><span class=cF0>[</span><span class=cF3>SEMA_RECORD_MACRO</span><span class=cF0>], </span><span class=cFE>0</span><span class=cF0>);
<a name="l214"></a>                </span><span class=cF5>QueueDel</span><span class=cF0>(&amp;</span><span class=cFB>sys_macro_head</span><span class=cF0>,</span><span class=cF3>TRUE</span><span class=cF0>);
<a name="l215"></a>                </span><span class=cF5>LBts</span><span class=cF0>(&amp;</span><span class=cFB>sys_semas</span><span class=cF0>[</span><span class=cF3>SEMA_RECORD_MACRO</span><span class=cF0>], </span><span class=cFE>0</span><span class=cF0>);
<a name="l216"></a>                </span><span class=cF1>break</span><span class=cF0>;
<a name="l217"></a>
<a name="l218"></a>            </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>SM_PLAY</span><span class=cF0>:
<a name="l219"></a>                </span><span class=cF5>PlaySysMacro</span><span class=cF0>;
<a name="l220"></a>                </span><span class=cF1>break</span><span class=cF0>;
<a name="l221"></a>
<a name="l222"></a>            </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>SM_REPEAT_N</span><span class=cF0>:
<a name="l223"></a>                </span><span class=cF5>PlaySysMacro</span><span class=cF0>(</span><span class=cFB>sys_macro_repeat_n</span><span class=cF0>);
<a name="l224"></a>                </span><span class=cF1>break</span><span class=cF0>;
<a name="l225"></a>
<a name="l226"></a>            </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>SM_STOP</span><span class=cF0>:
<a name="l227"></a>                </span><span class=cF5>LBtr</span><span class=cF0>(&amp;</span><span class=cFB>sys_semas</span><span class=cF0>[</span><span class=cF3>SEMA_RECORD_MACRO</span><span class=cF0>], </span><span class=cFE>0</span><span class=cF0>);
<a name="l228"></a>                </span><span class=cF1>break</span><span class=cF0>;
<a name="l229"></a>
<a name="l230"></a>            </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>SM_INS</span><span class=cF0>:
<a name="l231"></a>                </span><span class=cF5>LBtr</span><span class=cF0>(&amp;</span><span class=cFB>sys_semas</span><span class=cF0>[</span><span class=cF3>SEMA_RECORD_MACRO</span><span class=cF0>], </span><span class=cFE>0</span><span class=cF0>);
<a name="l232"></a>                </span><span class=cF5>EdInsCapturedMacro</span><span class=cF0>;
<a name="l233"></a>                </span><span class=cF1>break</span><span class=cF0>;
<a name="l234"></a>        }
<a name="l235"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l236"></a>    </span><span class=cF1>while</span><span class=cF0> (i &gt;= </span><span class=cFE>0</span><span class=cF0>);
<a name="l237"></a>}
<a name="l238"></a>
<a name="l239"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>EdMacroUtil</span><span class=cF0>()
<a name="l240"></a>{
<a name="l241"></a>    </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cFB>sys_macro_task</span><span class=cF0>)
<a name="l242"></a>        </span><span class=cF5>Spawn</span><span class=cF0>(&amp;</span><span class=cF5>MacroTask</span><span class=cF0>, </span><span class=cF3>NULL</span><span class=cF0>, </span><span class=cF6>&quot;Macro&quot;</span><span class=cF0>);
<a name="l243"></a>}
</span></pre></body>
</html>
