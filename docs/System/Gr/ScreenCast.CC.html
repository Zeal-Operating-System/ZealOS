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
<a name="l1"></a><span class=cF0>#</span><span class=cF1>help_index</span><span class=cF0> </span><span class=cF6>&quot;ScreenCast;Graphics/Device Contexts;Graphics/GR Files&quot;</span><span class=cF0>
<a name="l2"></a>
<a name="l3"></a>#</span><span class=cF1>define</span><span class=cF0> </span><span class=cF3>MV_FILE_MAX</span><span class=cF0>         </span><span class=cFE>0x007FF000</span><span class=cF0>
<a name="l4"></a>
<a name="l5"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>GR2MV</span><span class=cF0>(</span><span class=cF1>U8</span><span class=cF0> *print_format=</span><span class=cF6>&quot;VID%03d.MV&quot;</span><span class=cF0>, </span><span class=cF1>U8</span><span class=cF0> *files_find_mask, </span><span class=cF1>U8</span><span class=cF0> *fu_flags=</span><span class=cF3>NULL</span><span class=cF0>)
<a name="l6"></a>{</span><span class=cF2>/*Merge GR list to MV file.</span><span class=cF0>
<a name="l7"></a></span><span class=cF2>&quot;+d&quot; will delete GR list files.</span><span class=cF0>
<a name="l8"></a></span><span class=cF2>*/</span><span class=cF0>
<a name="l9"></a>    </span><span class=cF9>I64</span><span class=cF0>          fuf_flags = </span><span class=cFE>0</span><span class=cF0>, file_num = </span><span class=cFE>0</span><span class=cF0>, size;
<a name="l10"></a>    </span><span class=cF9>CDirEntry</span><span class=cF0>   *tmpde, *tmpde1;
<a name="l11"></a>    </span><span class=cF1>U8</span><span class=cF0>          *base, *dst, *src, *st;
<a name="l12"></a>    </span><span class=cF9>CDC</span><span class=cF0>         *dc, *dc_base = </span><span class=cF5>DCNew</span><span class=cF0>(</span><span class=cF3>GR_WIDTH</span><span class=cF0>, </span><span class=cF3>GR_HEIGHT</span><span class=cF0>);
<a name="l13"></a>    </span><span class=cF9>CDate</span><span class=cF0>        cdt;
<a name="l14"></a>    </span><span class=cF1>Bool</span><span class=cF0>         old_silent;
<a name="l15"></a>
<a name="l16"></a>    </span><span class=cF5>FlagsScan</span><span class=cF0>(&amp;fuf_flags, </span><span class=cF5>Define</span><span class=cF7>(</span><span class=cF6>&quot;ST_FILE_UTIL_FLAGS&quot;</span><span class=cF7>)</span><span class=cF0>, </span><span class=cF6>&quot;+f+F&quot;</span><span class=cF0>);
<a name="l17"></a>    </span><span class=cF5>FlagsScan</span><span class=cF0>(&amp;fuf_flags, </span><span class=cF5>Define</span><span class=cF7>(</span><span class=cF6>&quot;ST_FILE_UTIL_FLAGS&quot;</span><span class=cF7>)</span><span class=cF0>, fu_flags);
<a name="l18"></a>    tmpde = tmpde1 = </span><span class=cF5>FilesFind</span><span class=cF0>(files_find_mask, fuf_flags &amp; </span><span class=cF3>FUG_FILES_FIND</span><span class=cF0>);
<a name="l19"></a>    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cFB>progress1_max</span><span class=cF0> = </span><span class=cF5>LinkedListCount</span><span class=cF7>(</span><span class=cF0>tmpde1</span><span class=cF7>)</span><span class=cF0>)
<a name="l20"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l21"></a>        dst = base = </span><span class=cF5>MAlloc</span><span class=cF0>(</span><span class=cF3>MV_FILE_MAX</span><span class=cF0>);
<a name="l22"></a>        </span><span class=cF1>while</span><span class=cF0> (tmpde)
<a name="l23"></a>        {
<a name="l24"></a>            dc = </span><span class=cF5>GRRead</span><span class=cF0>(tmpde-&gt;full_name);
<a name="l25"></a>            </span><span class=cF5>GrBlot</span><span class=cF0>(dc_base, dc-&gt;x0, dc-&gt;y0, dc);
<a name="l26"></a>            </span><span class=cF1>if</span><span class=cF0> (dst + </span><span class=cF3>GR_FILE_MAX</span><span class=cF0> &gt; base + </span><span class=cF3>MV_FILE_MAX</span><span class=cF0>)
<a name="l27"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l28"></a>                st = </span><span class=cF5>MStrPrint</span><span class=cF0>(print_format, file_num++);
<a name="l29"></a>                </span><span class=cF5>FileWrite</span><span class=cF0>(st, base, dst-base);
<a name="l30"></a>                </span><span class=cF5>Free</span><span class=cF0>(st);
<a name="l31"></a>                dst = base;
<a name="l32"></a>
<a name="l33"></a>                cdt = dc-&gt;cdt;
<a name="l34"></a>                dc = </span><span class=cF5>DCCopy</span><span class=cF0>(dc_base);
<a name="l35"></a>                dc-&gt;cdt = cdt;
<a name="l36"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l37"></a>            src = </span><span class=cF5>DCSave</span><span class=cF0>(dc, &amp;size);
<a name="l38"></a>            </span><span class=cF5>DCDel</span><span class=cF0>(dc);
<a name="l39"></a>            </span><span class=cF5>MemCopy</span><span class=cF0>(dst, src, size);
<a name="l40"></a>            dst += size;
<a name="l41"></a>            </span><span class=cF5>Free</span><span class=cF0>(src);
<a name="l42"></a>            </span><span class=cF1>if</span><span class=cF0> (fuf_flags &amp; </span><span class=cF3>FUF_DEL</span><span class=cF0>)
<a name="l43"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l44"></a>                old_silent = </span><span class=cF5>Silent</span><span class=cF0>;
<a name="l45"></a>                </span><span class=cF5>Del</span><span class=cF0>(tmpde-&gt;full_name);
<a name="l46"></a>                </span><span class=cF5>Silent</span><span class=cF0>(old_silent);
<a name="l47"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l48"></a>            </span><span class=cFB>progress1</span><span class=cF0>++;
<a name="l49"></a>            tmpde = tmpde-&gt;next;
<a name="l50"></a>        }
<a name="l51"></a>        </span><span class=cF1>if</span><span class=cF0> (dst &gt; base)
<a name="l52"></a>        {
<a name="l53"></a>            st = </span><span class=cF5>MStrPrint</span><span class=cF0>(print_format, file_num++);
<a name="l54"></a>            </span><span class=cF5>FileWrite</span><span class=cF0>(st, base, dst-base);
<a name="l55"></a>            </span><span class=cF5>Free</span><span class=cF0>(st);
<a name="l56"></a>        }
<a name="l57"></a>        </span><span class=cF5>Free</span><span class=cF0>(base);
<a name="l58"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l59"></a>    </span><span class=cFB>progress1</span><span class=cF0> = </span><span class=cFB>progress1_max</span><span class=cF0> = </span><span class=cFE>0</span><span class=cF0>;
<a name="l60"></a>    </span><span class=cF5>DirTreeDel</span><span class=cF0>(tmpde1);
<a name="l61"></a>    </span><span class=cF5>DCDel</span><span class=cF0>(dc_base);
<a name="l62"></a>
<a name="l63"></a>    </span><span class=cF1>return</span><span class=cF0> file_num;
<a name="l64"></a>}
<a name="l65"></a>
<a name="l66"></a>#</span><span class=cF1>help_index</span><span class=cF0> </span><span class=cF6>&quot;ScreenCast;Sound/AU Files&quot;</span><span class=cF0>
<a name="l67"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>SoundShift</span><span class=cF0>(</span><span class=cF9>CSoundData</span><span class=cF0> *head, </span><span class=cF1>F64</span><span class=cF0> dt=</span><span class=cFE>0</span><span class=cF0>)
<a name="l68"></a>{</span><span class=cF2>//Shift CSoundData in time.</span><span class=cF0>
<a name="l69"></a>    </span><span class=cF9>CSoundData</span><span class=cF0> *tmpsd, *tmpsd1;
<a name="l70"></a>
<a name="l71"></a>    </span><span class=cF1>if</span><span class=cF0> (dt)
<a name="l72"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l73"></a>        tmpsd = head-&gt;next;
<a name="l74"></a>        </span><span class=cF1>while</span><span class=cF0> (tmpsd != head)
<a name="l75"></a>        {
<a name="l76"></a>            tmpsd1 = tmpsd-&gt;next;
<a name="l77"></a>            tmpsd-&gt;</span><span class=cF5>tS</span><span class=cF0> -= dt;
<a name="l78"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpsd-&gt;</span><span class=cF5>tS</span><span class=cF0> &lt; tmpsd-&gt;last-&gt;</span><span class=cF5>tS</span><span class=cF0>)
<a name="l79"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l80"></a>                </span><span class=cF5>QueueRemove</span><span class=cF0>(tmpsd);
<a name="l81"></a>                </span><span class=cF5>Free</span><span class=cF0>(tmpsd);
<a name="l82"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l83"></a>            tmpsd = tmpsd1;
<a name="l84"></a>        }
<a name="l85"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l86"></a>}
<a name="l87"></a>
<a name="l88"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>AUWrite</span><span class=cF0>(</span><span class=cF1>U8</span><span class=cF0> *filename, </span><span class=cF9>CSoundData</span><span class=cF0> *head, </span><span class=cF9>CDate</span><span class=cF0> *t0_now, </span><span class=cF1>F64</span><span class=cF0> t0_tS)
<a name="l89"></a>{</span><span class=cF2>//Write AU file.</span><span class=cF0>
<a name="l90"></a>    </span><span class=cF9>CSoundData</span><span class=cF0>  *tmpsd;
<a name="l91"></a>    </span><span class=cF9>CAUData</span><span class=cF0>     *base, *dst;
<a name="l92"></a>    </span><span class=cF9>I64</span><span class=cF0>          size = (</span><span class=cFE>1</span><span class=cF0> + </span><span class=cF5>QueueCount</span><span class=cF7>(</span><span class=cF0>head</span><span class=cF7>)</span><span class=cF0>) * </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>CAUData</span><span class=cF0>);
<a name="l93"></a>    </span><span class=cF1>U8</span><span class=cF0>          *st = </span><span class=cF5>ExtDefault</span><span class=cF0>(filename, </span><span class=cF6>&quot;AU&quot;</span><span class=cF0>);
<a name="l94"></a>
<a name="l95"></a>    base = dst = </span><span class=cF5>MAlloc</span><span class=cF0>(size);
<a name="l96"></a>    tmpsd = head;
<a name="l97"></a>    </span><span class=cF1>do</span><span class=cF0>
<a name="l98"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l99"></a>        dst-&gt;cdt = t0_now(</span><span class=cF9>I64</span><span class=cF0>) + </span><span class=cF5>ToI64</span><span class=cF0>(</span><span class=cF3>CDATE_FREQ</span><span class=cF0> * </span><span class=cF7>(</span><span class=cF0>tmpsd-&gt;</span><span class=cF5>tS</span><span class=cF0> - t0_tS</span><span class=cF7>)</span><span class=cF0>);
<a name="l100"></a>        dst-&gt;ona = tmpsd-&gt;ona;
<a name="l101"></a>        dst++;
<a name="l102"></a>        tmpsd = tmpsd-&gt;next;
<a name="l103"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l104"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpsd != head);
<a name="l105"></a>
<a name="l106"></a>    </span><span class=cF5>FileWrite</span><span class=cF0>(st, base, dst</span><span class=cF7>(</span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> - base</span><span class=cF7>(</span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>);
<a name="l107"></a>    </span><span class=cF5>Free</span><span class=cF0>(base);
<a name="l108"></a>    </span><span class=cF5>Free</span><span class=cF0>(st);
<a name="l109"></a>
<a name="l110"></a>    </span><span class=cF1>return</span><span class=cF0> size;
<a name="l111"></a>}
</span></pre></body>
</html>
