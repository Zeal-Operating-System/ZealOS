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
<a name="l1"></a><span class=cF2>//x must be global.</span><span class=cF0>
<a name="l2"></a></span><span class=cF2>//Might as well make y global.</span><span class=cF0>
<a name="l3"></a>
<a name="l4"></a></span><span class=cF1>F64</span><span class=cF0> x, y, y_last;
<a name="l5"></a>
<a name="l6"></a></span><span class=cF1>U0</span><span class=cF0> Cartesian()
<a name="l7"></a>{
<a name="l8"></a>    </span><span class=cF1>U8</span><span class=cF0>  *st;
<a name="l9"></a>    </span><span class=cF9>I64</span><span class=cF0>  ch = </span><span class=cFE>0</span><span class=cF0>, h, v;
<a name="l10"></a>    </span><span class=cF1>Bool</span><span class=cF0> first;
<a name="l11"></a>    </span><span class=cF9>CDC</span><span class=cF0> *dc = </span><span class=cF5>DCAlias</span><span class=cF0>;
<a name="l12"></a>
<a name="l13"></a>    </span><span class=cF1>do</span><span class=cF0>
<a name="l14"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l15"></a>        </span><span class=cF5>DocClear</span><span class=cF0>;
<a name="l16"></a>        </span><span class=cF6>&quot;Enter algebraic equation to graph.\n&quot;</span><span class=cF0>
<a name="l17"></a>        </span><span class=cF6>&quot;Example: y=2*x\n&quot;</span><span class=cF0>
<a name="l18"></a>        </span><span class=cF6>&quot;y=&quot;</span><span class=cF0>;
<a name="l19"></a>        </span><span class=cF1>if</span><span class=cF0> (st = </span><span class=cF5>StrGet</span><span class=cF0>)
<a name="l20"></a>        {
<a name="l21"></a>            </span><span class=cF1>if</span><span class=cF0> (*st)
<a name="l22"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l23"></a>                h = </span><span class=cF5>Fs</span><span class=cF0>-&gt;pix_width  / </span><span class=cFE>2</span><span class=cF0>;
<a name="l24"></a>                v = </span><span class=cF5>Fs</span><span class=cF0>-&gt;pix_height / </span><span class=cFE>2</span><span class=cF0>;
<a name="l25"></a>                dc-&gt;color = </span><span class=cF3>RED</span><span class=cF0>;
<a name="l26"></a>                </span><span class=cF5>GrLine</span><span class=cF0>(dc, h, </span><span class=cFE>0</span><span class=cF0>, h, </span><span class=cFE>2</span><span class=cF0> * v + </span><span class=cFE>1</span><span class=cF0>);
<a name="l27"></a>                </span><span class=cF5>GrLine</span><span class=cF0>(dc, </span><span class=cFE>0</span><span class=cF0>, v, </span><span class=cFE>2</span><span class=cF0> * h + </span><span class=cFE>1</span><span class=cF0>, v);
<a name="l28"></a>                first = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l29"></a>                dc-&gt;color = </span><span class=cF3>BLACK</span><span class=cF0>;
<a name="l30"></a>                </span><span class=cF1>for</span><span class=cF0> (x = -h; x &lt;= h; x++)
<a name="l31"></a>                {
<a name="l32"></a>                    y = -</span><span class=cF5>ExePrint</span><span class=cF0>(</span><span class=cF6>&quot;ToF64(%s);&quot;</span><span class=cF0>, st)(</span><span class=cF1>F64</span><span class=cF0>);
<a name="l33"></a>                    </span><span class=cF1>if</span><span class=cF0> (!first)
<a name="l34"></a>                        </span><span class=cF5>GrLine</span><span class=cF0>(dc, x - </span><span class=cFE>1</span><span class=cF0> + h, y_last + v, x + h, y + v);
<a name="l35"></a>                    y_last = y;
<a name="l36"></a>                    first = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l37"></a>                }
<a name="l38"></a>                ch = </span><span class=cF5>CharGet</span><span class=cF0>;
<a name="l39"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l40"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l41"></a>                ch = </span><span class=cF3>CH_SHIFT_ESC</span><span class=cF0>;
<a name="l42"></a>            </span><span class=cF5>Free</span><span class=cF0>(st);
<a name="l43"></a>        }
<a name="l44"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l45"></a>            ch = </span><span class=cF3>CH_SHIFT_ESC</span><span class=cF0>;
<a name="l46"></a>        </span><span class=cF5>DCFill</span><span class=cF0>;
<a name="l47"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l48"></a>    </span><span class=cF1>while</span><span class=cF0> (ch != </span><span class=cF3>CH_SHIFT_ESC</span><span class=cF0> &amp;&amp; ch != </span><span class=cF3>CH_ESC</span><span class=cF0>);
<a name="l49"></a>
<a name="l50"></a>    </span><span class=cF5>DCDel</span><span class=cF0>(dc);
<a name="l51"></a>}
<a name="l52"></a>
<a name="l53"></a>Cartesian;
<a name="l54"></a>
<a name="l55"></a></span><span class=cF2>//For better performance, compile the expression entered by the</span><span class=cF0>
<a name="l56"></a></span><span class=cF2>//user one time with </span><a href="https://tomawezome.github.io/ZealOS/Compiler/ParseExp.html#l1281"><span class=cF4>LexExpression2Bin</span></a><span class=cF2>() and use </span><a href="https://tomawezome.github.io/ZealOS/Kernel/KernelB.html#l32"><span class=cF4>Call</span></a><span class=cF2>().</span><span class=cF0>
<a name="l57"></a></span><span class=cF2>//See </span><a href="https://tomawezome.github.io/ZealOS/Demo/CompileDemo.html#l1"><span class=cF4>::/Demo/CompileDemo.CC</span></a><span class=cF2>.</span><span class=cF0>
</span></pre></body>
</html>
