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
<a name="l1"></a><span class=cF0>#</span><span class=cF1>define</span><span class=cF0> SQUARE_SIZE     </span><span class=cFE>20</span><span class=cF0>
<a name="l2"></a>#</span><span class=cF1>define</span><span class=cF0> SQUARE_GAP      </span><span class=cFE>5</span><span class=cF0>
<a name="l3"></a>#</span><span class=cF1>define</span><span class=cF0> SQUARE_DELAY    </span><span class=cFE>5</span><span class=cF0> </span><span class=cF2>// mS</span><span class=cF0>
<a name="l4"></a>
<a name="l5"></a></span><span class=cF1>I0</span><span class=cF0> DrawPixel(</span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y, </span><span class=cF9>CBGR24</span><span class=cF0> color)
<a name="l6"></a>{
<a name="l7"></a>    </span><span class=cFB>text</span><span class=cF0>.fb_alias[x + y * </span><span class=cF3>GR_WIDTH</span><span class=cF0>] = color;
<a name="l8"></a>}
<a name="l9"></a>
<a name="l10"></a></span><span class=cF1>I0</span><span class=cF0> Color32Demo()
<a name="l11"></a>{
<a name="l12"></a>    </span><span class=cF9>I64</span><span class=cF0>     i, j, x, y;
<a name="l13"></a>    </span><span class=cF9>CBGR24</span><span class=cF0>  color;
<a name="l14"></a>
<a name="l15"></a>    </span><span class=cF6>&quot;\nPress any key to exit demo.\n\n&quot;</span><span class=cF0>;
<a name="l16"></a>
<a name="l17"></a>    </span><span class=cF5>Sleep</span><span class=cF0>(</span><span class=cFE>500</span><span class=cF0>);
<a name="l18"></a>
<a name="l19"></a>    </span><span class=cFB>text</span><span class=cF0>.is_fb_busy = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l20"></a>
<a name="l21"></a>    </span><span class=cF1>while</span><span class=cF0> (!</span><span class=cF5>CharScan</span><span class=cF0>)
<a name="l22"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l23"></a>        x = </span><span class=cF5>FloorI64</span><span class=cF0>(</span><span class=cF5>RandU16</span><span class=cF0> % </span><span class=cF3>GR_WIDTH</span><span class=cF0>, SQUARE_SIZE + SQUARE_GAP);
<a name="l24"></a>        y = </span><span class=cF5>FloorI64</span><span class=cF0>(</span><span class=cF5>RandU16</span><span class=cF0> % </span><span class=cF3>GR_WIDTH</span><span class=cF0>, SQUARE_SIZE + SQUARE_GAP);
<a name="l25"></a>        color = </span><span class=cF5>RandU32</span><span class=cF0>;
<a name="l26"></a>
<a name="l27"></a>        </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; SQUARE_SIZE; i++)
<a name="l28"></a>            </span><span class=cF1>for</span><span class=cF0> (j = </span><span class=cFE>0</span><span class=cF0>; j &lt; SQUARE_SIZE; j++)
<a name="l29"></a>                DrawPixel(x + i, y + j, color);
<a name="l30"></a>
<a name="l31"></a>        </span><span class=cF5>Sleep</span><span class=cF0>(SQUARE_DELAY);
<a name="l32"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l33"></a>
<a name="l34"></a>    </span><span class=cFB>text</span><span class=cF0>.is_fb_busy = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l35"></a>    </span><span class=cF5>LFBFlush</span><span class=cF0>;
<a name="l36"></a>
<a name="l37"></a>}
<a name="l38"></a>
<a name="l39"></a>Color32Demo;</span></pre></body>
</html>
