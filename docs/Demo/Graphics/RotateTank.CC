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
<a name="l1"></a><span class=cF0>
<a name="l2"></a>
<a name="l3"></a>
<a name="l4"></a>
<a name="l5"></a>
<a name="l6"></a>
<a name="l7"></a>
<a name="l8"></a>
<a name="l9"></a>
<a name="l10"></a>
<a name="l11"></a>
<a name="l12"></a>
<a name="l13"></a>                                </span><span class=cFA>&lt;1&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l14"></a>
<a name="l15"></a>
<a name="l16"></a>
<a name="l17"></a>
<a name="l18"></a>
<a name="l19"></a>
<a name="l20"></a>
<a name="l21"></a>
<a name="l22"></a>
<a name="l23"></a>
<a name="l24"></a>
<a name="l25"></a></span><span class=cF1>U0</span><span class=cF0> RotateTank()
<a name="l26"></a>{
<a name="l27"></a>    </span><span class=cF9>CDC</span><span class=cF0> *dc = </span><span class=cF5>DCAlias</span><span class=cF0>;
<a name="l28"></a>
<a name="l29"></a>    </span><span class=cF5>DCDepthBufAlloc</span><span class=cF0>(dc);
<a name="l30"></a>    dc-&gt;flags |= </span><span class=cF3>DCF_TRANSFORMATION</span><span class=cF0>;
<a name="l31"></a>    </span><span class=cF5>WinHorz</span><span class=cF0>(</span><span class=cF3>TEXT_COLS</span><span class=cF0> / </span><span class=cFE>2</span><span class=cF0> - </span><span class=cFE>12</span><span class=cF0>, </span><span class=cF3>TEXT_COLS</span><span class=cF0> / </span><span class=cFE>2</span><span class=cF0> + </span><span class=cFE>12</span><span class=cF0>);
<a name="l32"></a>    </span><span class=cF5>WinVert</span><span class=cF0>(</span><span class=cF3>TEXT_ROWS</span><span class=cF0> / </span><span class=cFE>2</span><span class=cF0> - </span><span class=cFE>12</span><span class=cF0>, </span><span class=cF3>TEXT_ROWS</span><span class=cF0> / </span><span class=cFE>2</span><span class=cF0> + </span><span class=cFE>12</span><span class=cF0>);
<a name="l33"></a>    </span><span class=cF5>DocClear</span><span class=cF0>;
<a name="l34"></a>    </span><span class=cF1>try</span><span class=cF0>
<a name="l35"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l36"></a>        </span><span class=cF1>while</span><span class=cF0> (!</span><span class=cF5>CharScan</span><span class=cF0>)
<a name="l37"></a>        {
<a name="l38"></a>            </span><span class=cF5>DCDepthBufReset</span><span class=cF0>(dc);
<a name="l39"></a>            </span><span class=cF5>Mat4x4IdentEqu</span><span class=cF0>(dc-&gt;r);
<a name="l40"></a>            </span><span class=cF5>Mat4x4RotY</span><span class=cF0>(dc-&gt;r, </span><span class=cFE>0</span><span class=cF0>.</span><span class=cFE>25</span><span class=cF0> * </span><span class=cF5>Sin</span><span class=cF7>(</span><span class=cF5>tS</span><span class=cF0> / </span><span class=cFE>10</span><span class=cF0> * </span><span class=cFE>2</span><span class=cF0> *</span><span class=cF3>pi</span><span class=cF7>)</span><span class=cF0> + </span><span class=cF3>pi</span><span class=cF0> / </span><span class=cFE>2</span><span class=cF0>);
<a name="l41"></a>            </span><span class=cF5>Mat4x4RotX</span><span class=cF0>(dc-&gt;r, </span><span class=cFE>0</span><span class=cF0>.</span><span class=cFE>4</span><span class=cF0>  * </span><span class=cF5>Sin</span><span class=cF7>(</span><span class=cF5>tS</span><span class=cF0> / </span><span class=cFE>5</span><span class=cF0>  * </span><span class=cFE>2</span><span class=cF0> *</span><span class=cF3>pi</span><span class=cF7>)</span><span class=cF0>);
<a name="l42"></a>            </span><span class=cF5>Mat4x4RotZ</span><span class=cF0>(dc-&gt;r, </span><span class=cFE>0</span><span class=cF0>.</span><span class=cFE>25</span><span class=cF0> * </span><span class=cF5>Sin</span><span class=cF7>(</span><span class=cF5>tS</span><span class=cF0> / </span><span class=cFE>10</span><span class=cF0> * </span><span class=cFE>2</span><span class=cF0> *</span><span class=cF3>pi</span><span class=cF7>)</span><span class=cF0> - </span><span class=cF3>pi</span><span class=cF0> / </span><span class=cFE>2</span><span class=cF0>);
<a name="l43"></a>            </span><span class=cF5>Mat4x4Scale</span><span class=cF0>(dc-&gt;r, </span><span class=cFE>0</span><span class=cF0>.</span><span class=cFE>25</span><span class=cF0> + </span><span class=cF5>Saw</span><span class=cF7>(</span><span class=cF5>tS</span><span class=cF0>, </span><span class=cFE>5</span><span class=cF7>)</span><span class=cF0>);
<a name="l44"></a>            </span><span class=cF5>DCMat4x4Set</span><span class=cF0>(dc, dc-&gt;r);</span><span class=cF2>//Not needed--Sets scale for pen-width</span><span class=cF0>
<a name="l45"></a>
<a name="l46"></a>            dc-&gt;x = </span><span class=cF5>Fs</span><span class=cF0>-&gt;pix_width  / </span><span class=cFE>2</span><span class=cF0>;
<a name="l47"></a>            dc-&gt;y = </span><span class=cF5>Fs</span><span class=cF0>-&gt;pix_height / </span><span class=cFE>2</span><span class=cF0>;
<a name="l48"></a>            </span><span class=cF2>//Offsets the image Z so that no parts are clipped by</span><span class=cF0>
<a name="l49"></a>            </span><span class=cF2>//the conceptual plane of the screen.</span><span class=cF0>
<a name="l50"></a>            dc-&gt;z = </span><span class=cF3>GR_Z_ALL</span><span class=cF0>;
<a name="l51"></a>
<a name="l52"></a>            </span><span class=cF5>Sprite3</span><span class=cF0>(dc, </span><span class=cFE>0</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>, </span><span class=cFA>&lt;1&gt;</span><span class=cF0>);
<a name="l53"></a>            </span><span class=cF5>Refresh</span><span class=cF0>;
<a name="l54"></a>            </span><span class=cF5>DCFill</span><span class=cF0>;
<a name="l55"></a>        }
<a name="l56"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l57"></a>    </span><span class=cF1>catch</span><span class=cF0>
<a name="l58"></a>        </span><span class=cF5>PutExcept</span><span class=cF0>;
<a name="l59"></a>
<a name="l60"></a>    </span><span class=cF5>DCFill</span><span class=cF0>;
<a name="l61"></a>    </span><span class=cF5>DCDel</span><span class=cF0>(dc);
<a name="l62"></a>}
<a name="l63"></a>
<a name="l64"></a>RotateTank;
</span></pre></body>
</html>
