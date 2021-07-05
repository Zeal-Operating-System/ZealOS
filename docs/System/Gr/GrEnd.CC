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
<a name="l1"></a><span class=cF0>#</span><span class=cF1>help_index</span><span class=cF0> </span><span class=cF6>&quot;Graphics/Screen&quot;</span><span class=cF0>
<a name="l2"></a>
<a name="l3"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>CtrlAltZ</span><span class=cF0>(</span><span class=cF9>I64</span><span class=cF0> sc)
<a name="l4"></a>{
<a name="l5"></a>    </span><span class=cF1>if</span><span class=cF0> (sc &amp; </span><span class=cF3>SCF_SHIFT</span><span class=cF0>)
<a name="l6"></a>        </span><span class=cF5>GrScaleZoom</span><span class=cF0>(</span><span class=cFE>0</span><span class=cF0>.</span><span class=cFE>5</span><span class=cF0>);
<a name="l7"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l8"></a>        </span><span class=cF5>GrScaleZoom</span><span class=cF0>(</span><span class=cFE>2</span><span class=cF0>.</span><span class=cFE>0</span><span class=cF0>);
<a name="l9"></a>}
<a name="l10"></a></span><span class=cF5>CtrlAltCBSet</span><span class=cF0>(</span><span class=cF6>'Z'</span><span class=cF0>, &amp;</span><span class=cF5>CtrlAltZ</span><span class=cF0>, </span><span class=cF6>&quot;Cmd /Zoom In&quot;</span><span class=cF0>, </span><span class=cF6>&quot;Cmd /Zoom Out&quot;</span><span class=cF0>);
<a name="l11"></a>
<a name="l12"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>Screen2Clip</span><span class=cF0>(</span><span class=cF9>I64</span><span class=cF0>)
<a name="l13"></a>{
<a name="l14"></a>    </span><span class=cF9>CDC</span><span class=cF0> *dc = </span><span class=cF5>DCScreenCapture</span><span class=cF0>;
<a name="l15"></a>    </span><span class=cF1>U8</span><span class=cF0>  *elems = </span><span class=cF5>DC2Sprite</span><span class=cF0>(dc);
<a name="l16"></a>    </span><span class=cF1>Bool</span><span class=cF0> unlock_doc = </span><span class=cF5>DocLock</span><span class=cF0>(</span><span class=cFB>sys_clip_doc</span><span class=cF0>);
<a name="l17"></a>
<a name="l18"></a>    </span><span class=cF5>ClipDel</span><span class=cF0>;
<a name="l19"></a>    </span><span class=cF5>DocSprite</span><span class=cF0>(</span><span class=cFB>sys_clip_doc</span><span class=cF0>, elems);
<a name="l20"></a>    </span><span class=cF1>if</span><span class=cF0> (unlock_doc)
<a name="l21"></a>        </span><span class=cF5>DocUnlock</span><span class=cF0>(</span><span class=cFB>sys_clip_doc</span><span class=cF0>);
<a name="l22"></a>    </span><span class=cF5>Free</span><span class=cF0>(elems);
<a name="l23"></a>    </span><span class=cF5>DCDel</span><span class=cF0>(dc);
<a name="l24"></a>}
<a name="l25"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>CtrlAltS</span><span class=cF0>(</span><span class=cF9>I64</span><span class=cF0>)
<a name="l26"></a>{
<a name="l27"></a>    </span><span class=cF5>Spawn</span><span class=cF0>(&amp;</span><span class=cF5>Screen2Clip</span><span class=cF0>);
<a name="l28"></a>}
<a name="l29"></a></span><span class=cF5>CtrlAltCBSet</span><span class=cF0>(</span><span class=cF6>'S'</span><span class=cF0>, &amp;</span><span class=cF5>CtrlAltS</span><span class=cF0>, </span><span class=cF6>&quot;Cmd /Screen Shot to Clip&quot;</span><span class=cF0>);
</span></pre></body>
</html>
