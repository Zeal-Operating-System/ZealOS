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
<a name="l2"></a>
<a name="l3"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>GrInit1</span><span class=cF0>()
<a name="l4"></a>{
<a name="l5"></a>    </span><span class=cF5>DefineListLoad</span><span class=cF0>(</span><span class=cF6>&quot;ST_SPRITE_ELEM_TYPES&quot;</span><span class=cF0>,
<a name="l6"></a>
<a name="l7"></a>                        </span><span class=cF6>&quot;End\0&quot;</span><span class=cF0>
<a name="l8"></a>                        </span><span class=cF6>&quot;Color\0&quot;</span><span class=cF0>
<a name="l9"></a>                        </span><span class=cF6>&quot;Dither Color\0&quot;</span><span class=cF0>
<a name="l10"></a>                        </span><span class=cF6>&quot;Thick\0&quot;</span><span class=cF0>
<a name="l11"></a>                        </span><span class=cF6>&quot;Planar Symmetry\0&quot;</span><span class=cF0>
<a name="l12"></a>                        </span><span class=cF6>&quot;Transform On\0&quot;</span><span class=cF0>
<a name="l13"></a>                        </span><span class=cF6>&quot;Transform Off\0&quot;</span><span class=cF0>
<a name="l14"></a>                        </span><span class=cF6>&quot;Shift\0&quot;</span><span class=cF0>
<a name="l15"></a>                        </span><span class=cF6>&quot;Point\0&quot;</span><span class=cF0>
<a name="l16"></a>                        </span><span class=cF6>&quot;PolyPoint\0&quot;</span><span class=cF0>
<a name="l17"></a>                        </span><span class=cF6>&quot;Line\0&quot;</span><span class=cF0>
<a name="l18"></a>                        </span><span class=cF6>&quot;PolyLine\0&quot;</span><span class=cF0>
<a name="l19"></a>                        </span><span class=cF6>&quot;Rect\0&quot;</span><span class=cF0>
<a name="l20"></a>                        </span><span class=cF6>&quot;Rotated Rect\0&quot;</span><span class=cF0>
<a name="l21"></a>                        </span><span class=cF6>&quot;Circle\0&quot;</span><span class=cF0>
<a name="l22"></a>                        </span><span class=cF6>&quot;Ellipse\0&quot;</span><span class=cF0>
<a name="l23"></a>                        </span><span class=cF6>&quot;Polygon\0&quot;</span><span class=cF0>
<a name="l24"></a>                        </span><span class=cF6>&quot;BSpline2\0&quot;</span><span class=cF0>
<a name="l25"></a>                        </span><span class=cF6>&quot;BSpline2 Closed\0&quot;</span><span class=cF0>
<a name="l26"></a>                        </span><span class=cF6>&quot;BSpline3\0&quot;</span><span class=cF0>
<a name="l27"></a>                        </span><span class=cF6>&quot;BSpline3 Closed\0&quot;</span><span class=cF0>
<a name="l28"></a>                        </span><span class=cF6>&quot;Flood Fill\0&quot;</span><span class=cF0>
<a name="l29"></a>                        </span><span class=cF6>&quot;Flood Fill Not Color\0&quot;</span><span class=cF0>
<a name="l30"></a>                        </span><span class=cF6>&quot;BitMap\0&quot;</span><span class=cF0>
<a name="l31"></a>                        </span><span class=cF6>&quot;Mesh\0&quot;</span><span class=cF0>
<a name="l32"></a>                        </span><span class=cF6>&quot;Shiftable Mesh\0&quot;</span><span class=cF0>
<a name="l33"></a>                        </span><span class=cF6>&quot;Arrow\0&quot;</span><span class=cF0>
<a name="l34"></a>                        </span><span class=cF6>&quot;Text\0&quot;</span><span class=cF0>
<a name="l35"></a>                        </span><span class=cF6>&quot;Text Box\0&quot;</span><span class=cF0>
<a name="l36"></a>                        </span><span class=cF6>&quot;Text Diamond\0&quot;</span><span class=cF0>);
<a name="l37"></a>
<a name="l38"></a>    </span><span class=cF5>DefineListLoad</span><span class=cF0>(</span><span class=cF6>&quot;ST_SPRITE_ELEM_CODES&quot;</span><span class=cF0>,
<a name="l39"></a>
<a name="l40"></a>                        </span><span class=cF6>&quot;End\0&quot;</span><span class=cF0>
<a name="l41"></a>                        </span><span class=cF6>&quot;Color\0&quot;</span><span class=cF0>
<a name="l42"></a>                        </span><span class=cF6>&quot;Color\0&quot;</span><span class=cF0>
<a name="l43"></a>                        </span><span class=cF6>&quot;Thick\0&quot;</span><span class=cF0>
<a name="l44"></a>                        </span><span class=cF6>&quot;PlanarSymmetry\0&quot;</span><span class=cF0>
<a name="l45"></a>                        </span><span class=cF6>&quot;Transform\0&quot;</span><span class=cF0>
<a name="l46"></a>                        </span><span class=cF6>&quot;Transform\0&quot;</span><span class=cF0>
<a name="l47"></a>                        </span><span class=cF6>&quot;Shift\0&quot;</span><span class=cF0>
<a name="l48"></a>                        </span><span class=cF6>&quot;Pt\0&quot;</span><span class=cF0>
<a name="l49"></a>                        </span><span class=cF6>&quot;PolyPt\0&quot;</span><span class=cF0>
<a name="l50"></a>                        </span><span class=cF6>&quot;Line\0&quot;</span><span class=cF0>
<a name="l51"></a>                        </span><span class=cF6>&quot;PolyLine\0&quot;</span><span class=cF0>
<a name="l52"></a>                        </span><span class=cF6>&quot;Rect\0&quot;</span><span class=cF0>
<a name="l53"></a>                        </span><span class=cF6>&quot;Rect\0&quot;</span><span class=cF0>
<a name="l54"></a>                        </span><span class=cF6>&quot;Circle\0&quot;</span><span class=cF0>
<a name="l55"></a>                        </span><span class=cF6>&quot;Ellipse\0&quot;</span><span class=cF0>
<a name="l56"></a>                        </span><span class=cF6>&quot;Polygon\0&quot;</span><span class=cF0>
<a name="l57"></a>                        </span><span class=cF6>&quot;BSpline2\0&quot;</span><span class=cF0>
<a name="l58"></a>                        </span><span class=cF6>&quot;BSpline2\0&quot;</span><span class=cF0>
<a name="l59"></a>                        </span><span class=cF6>&quot;BSpline3\0&quot;</span><span class=cF0>
<a name="l60"></a>                        </span><span class=cF6>&quot;BSpline3\0&quot;</span><span class=cF0>
<a name="l61"></a>                        </span><span class=cF6>&quot;FloodFill\0&quot;</span><span class=cF0>
<a name="l62"></a>                        </span><span class=cF6>&quot;FloodFill\0&quot;</span><span class=cF0>
<a name="l63"></a>                        </span><span class=cF6>&quot;BitMap\0&quot;</span><span class=cF0>
<a name="l64"></a>                        </span><span class=cF6>&quot;Mesh\0&quot;</span><span class=cF0>
<a name="l65"></a>                        </span><span class=cF6>&quot;Mesh\0&quot;</span><span class=cF0>
<a name="l66"></a>                        </span><span class=cF6>&quot;Arrow\0&quot;</span><span class=cF0>
<a name="l67"></a>                        </span><span class=cF6>&quot;Text\0&quot;</span><span class=cF0>
<a name="l68"></a>                        </span><span class=cF6>&quot;TextBox\0&quot;</span><span class=cF0>
<a name="l69"></a>                        </span><span class=cF6>&quot;TextDiamond\0&quot;</span><span class=cF0>);
<a name="l70"></a>}
<a name="l71"></a>
<a name="l72"></a></span><span class=cF5>GrInit1</span><span class=cF0>;
</span></pre></body>
</html>
