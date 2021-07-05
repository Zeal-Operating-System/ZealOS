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
<a name="l1"></a><span class=cF0>#</span><span class=cF1>help_index</span><span class=cF0> </span><span class=cF6>&quot;Graphics&quot;</span><span class=cF0>
<a name="l2"></a></span><span class=cF1>extern</span><span class=cF0> </span><span class=cF1>U8</span><span class=cF0>       *</span><span class=cF5>GrBitMap4ToBitMap8</span><span class=cF0>(</span><span class=cF1>U8</span><span class=cF0> *dst, </span><span class=cF1>U8</span><span class=cF0> *src, </span><span class=cF9>I64</span><span class=cF0> src_size, </span><span class=cF9>I64</span><span class=cF0> bkcolor);
<a name="l3"></a></span><span class=cF1>extern</span><span class=cF0> </span><span class=cF9>I64</span><span class=cF0>       </span><span class=cF5>GrBlot3</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc, </span><span class=cF9>I64</span><span class=cF0> x1, </span><span class=cF9>I64</span><span class=cF0> y1, </span><span class=cF9>I64</span><span class=cF0> z1, </span><span class=cF9>CDC</span><span class=cF0> *img);
<a name="l4"></a></span><span class=cF1>extern</span><span class=cF0> </span><span class=cF9>I64</span><span class=cF0>      *</span><span class=cF5>Mat4x4New</span><span class=cF0>(</span><span class=cF9>I64</span><span class=cF0> *src, </span><span class=cF9>CTask</span><span class=cF0> *mem_task=</span><span class=cF3>NULL</span><span class=cF0>);
<a name="l5"></a></span><span class=cF1>extern</span><span class=cF0> </span><span class=cF1>U8</span><span class=cF0>       *</span><span class=cF5>SpriteQueue2Sprite</span><span class=cF0>(</span><span class=cF9>CSprite</span><span class=cF0> *head, </span><span class=cF9>I64</span><span class=cF0> *_size=</span><span class=cF3>NULL</span><span class=cF0>);
<a name="l6"></a></span><span class=cF1>extern</span><span class=cF0> </span><span class=cF9>CSprite</span><span class=cF0>  *</span><span class=cF5>SpriteSetSettings</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc=</span><span class=cF3>NULL</span><span class=cF0>, </span><span class=cF9>CSprite</span><span class=cF0> *head, </span><span class=cF9>I64</span><span class=cF0> elem_num,
<a name="l7"></a>                                   </span><span class=cF9>I64</span><span class=cF0> x=</span><span class=cFE>0</span><span class=cF0>, </span><span class=cF9>I64</span><span class=cF0> y=</span><span class=cFE>0</span><span class=cF0>,
<a name="l8"></a>                                   </span><span class=cF9>CColorROPU32</span><span class=cF0> *_color=</span><span class=cF3>NULL</span><span class=cF0>, </span><span class=cF9>I64</span><span class=cF0> *_thick=</span><span class=cF3>NULL</span><span class=cF0>, </span><span class=cF9>I64</span><span class=cF0> *_xx=</span><span class=cF3>NULL</span><span class=cF0>, </span><span class=cF9>I64</span><span class=cF0> *_yy=</span><span class=cF3>NULL</span><span class=cF0>);
</span></pre></body>
</html>
