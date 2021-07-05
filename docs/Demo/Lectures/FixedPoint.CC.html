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
<a name="l1"></a><span class=cF2>/*</span><span class=cF0>
<a name="l2"></a></span><span class=cF2>&quot;Fixed point&quot; means you use ints</span><span class=cF0>
<a name="l3"></a></span><span class=cF2>that are scaled by a value.  A common</span><span class=cF0>
<a name="l4"></a></span><span class=cF2>example would be using number of pennies</span><span class=cF0>
<a name="l5"></a></span><span class=cF2>instead of dollars with a float.</span><span class=cF0>
<a name="l6"></a>
<a name="l7"></a></span><span class=cF2>Fixed-point used to be much </span><a href="http://en.wikipedia.org/wiki/X87"><span class=cF2>faster</span></a><span class=cF2>,</span><span class=cF0>
<a name="l8"></a></span><span class=cF2>but modern processors do well with</span><span class=cF0>
<a name="l9"></a></span><span class=cF2>floats.  It also depends on the compiler</span><span class=cF0>
<a name="l10"></a></span><span class=cF2>and the CosmiC compiler is poor with floats.</span><span class=cF0>
<a name="l11"></a>
<a name="l12"></a></span><span class=cF2>Terry often used 64-bit ints with upper 32-bits</span><span class=cF0>
<a name="l13"></a></span><span class=cF2>as int and lower 32-bits as fraction.</span><span class=cF0>
<a name="l14"></a>
<a name="l15"></a></span><span class=cF2>See </span><a href="https://tomawezome.github.io/ZealOS/Demo/SubIntAccess.html#l1"><span class=cF4>::/Demo/SubIntAccess.CC</span></a><span class=cF2> for how</span><span class=cF0>
<a name="l16"></a></span><span class=cF2>to access upper or lower 32-bits.</span><span class=cF0>
<a name="l17"></a>
<a name="l18"></a></span><span class=cF2>For a complete list of nonstandard compiler</span><span class=cF0>
<a name="l19"></a></span><span class=cF2>features, see </span><a href="https://tomawezome.github.io/ZealOS/Doc/CosmiC.html#l1"><span class=cF4>::/Doc/CosmiC.DD</span></a><span class=cF2>.</span><span class=cF0>
<a name="l20"></a></span><span class=cF2>*/</span><span class=cF0>
<a name="l21"></a>
<a name="l22"></a></span><span class=cF1>U0</span><span class=cF0> Main()
<a name="l23"></a>{
<a name="l24"></a>    </span><span class=cF1>F64</span><span class=cF0> t0, f_sum=</span><span class=cFE>0</span><span class=cF0>, f_val;
<a name="l25"></a>    </span><span class=cF9>I64</span><span class=cF0> i , i_sum=</span><span class=cFE>0</span><span class=cF0>, i_val;
<a name="l26"></a>
<a name="l27"></a>    i_val =  </span><span class=cFE>2</span><span class=cF0>.</span><span class=cFE>0000002</span><span class=cF0> * </span><span class=cFE>0x100000000</span><span class=cF0>;
<a name="l28"></a>    t0 = </span><span class=cF5>tS</span><span class=cF0>;
<a name="l29"></a>    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>1000000000</span><span class=cF0>; i; i--)
<a name="l30"></a>        i_sum += i_val;
<a name="l31"></a>    </span><span class=cF6>&quot;Int Sum\t\t:%.9f Time:%7.3fs\n&quot;</span><span class=cF0>, i_sum / </span><span class=cF5>ToF64</span><span class=cF0>(</span><span class=cFE>0x100000000</span><span class=cF0>), </span><span class=cF5>tS</span><span class=cF0> - t0;
<a name="l32"></a>
<a name="l33"></a>    f_val = </span><span class=cFE>2</span><span class=cF0>.</span><span class=cFE>0000002</span><span class=cF0>;
<a name="l34"></a>    t0 = </span><span class=cF5>tS</span><span class=cF0>;
<a name="l35"></a>    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>1000000000</span><span class=cF0>; i; i--)
<a name="l36"></a>        f_sum += f_val;
<a name="l37"></a>    </span><span class=cF6>&quot;Float Sum\t:%.9f Time:%7.3fs\n&quot;</span><span class=cF0>, f_sum, </span><span class=cF5>tS</span><span class=cF0> - t0;
<a name="l38"></a>    </span><span class=cF6>'\n'</span><span class=cF0>;
<a name="l39"></a>}
<a name="l40"></a>
<a name="l41"></a></span><span class=cF1>U0</span><span class=cF0> DoIt2()
<a name="l42"></a>{
<a name="l43"></a>    </span><span class=cF9>I64</span><span class=cF0> i = </span><span class=cFE>0x123456789ABCDEF0</span><span class=cF0>;
<a name="l44"></a>    </span><span class=cF6>&quot;i\t\t=%X\n&quot;</span><span class=cF0>, i;
<a name="l45"></a>
<a name="l46"></a>    </span><span class=cF6>&quot;i&amp;0xFFFFFFFF\t=%X\n&quot;</span><span class=cF0>, i &amp; </span><span class=cFE>0xFFFFFFFF</span><span class=cF0>;
<a name="l47"></a>    </span><span class=cF6>&quot;i&gt;&gt;32\t\t=%X\n&quot;</span><span class=cF0>, i &gt;&gt; </span><span class=cFE>32</span><span class=cF0>;
<a name="l48"></a>
<a name="l49"></a></span><span class=cF2>/*</span><span class=cF0>  </span><span class=cF2>Standard int types are declared</span><span class=cF0>
<a name="l50"></a></span><span class=cF2>with a special compiler feature which</span><span class=cF0>
<a name="l51"></a></span><span class=cF2>allows a structure to be accessed as a</span><span class=cF0>
<a name="l52"></a></span><span class=cF2>whole.  That's why the i variable can</span><span class=cF0>
<a name="l53"></a></span><span class=cF2>be accessed normally in addition to</span><span class=cF0>
<a name="l54"></a></span><span class=cF2>structure member access </span><a href="https://tomawezome.github.io/ZealOS/Kernel/KernelA.html#l103"><span class=cF4>I64</span></a><span class=cF2>.  The actual</span><span class=cF0>
<a name="l55"></a></span><span class=cF2>intrinsic compiler type is U64i.</span><span class=cF0>
<a name="l56"></a>
<a name="l57"></a></span><span class=cF2>public U64i union I64</span><span class=cF0>
<a name="l58"></a></span><span class=cF2>{</span><span class=cF0>
<a name="l59"></a>    </span><span class=cF2>I8i i8[8];</span><span class=cF0>
<a name="l60"></a>    </span><span class=cF2>U8i u8[8];</span><span class=cF0>
<a name="l61"></a>    </span><span class=cF2>I16 i16[4];</span><span class=cF0>
<a name="l62"></a>    </span><span class=cF2>U16 u16[4];</span><span class=cF0>
<a name="l63"></a>    </span><span class=cF2>I32 i32[2];</span><span class=cF0>
<a name="l64"></a>    </span><span class=cF2>U32 u32[2];</span><span class=cF0>
<a name="l65"></a></span><span class=cF2>};</span><span class=cF0>
<a name="l66"></a>
<a name="l67"></a></span><span class=cF2>It's not quite as great as it seems</span><span class=cF0>
<a name="l68"></a></span><span class=cF2>because the compiler decides it cannot</span><span class=cF0>
<a name="l69"></a></span><span class=cF2>place i into a reg, so there is a</span><span class=cF0>
<a name="l70"></a></span><span class=cF2>penalty.</span><span class=cF0>
<a name="l71"></a>
<a name="l72"></a></span><span class=cF2>For a complete list of nonstandard compiler</span><span class=cF0>
<a name="l73"></a></span><span class=cF2>features, see </span><a href="https://tomawezome.github.io/ZealOS/Doc/CosmiC.html#l1"><span class=cF4>::/Doc/CosmiC.DD</span></a><span class=cF2>.</span><span class=cF0>
<a name="l74"></a></span><span class=cF2>*/</span><span class=cF0>
<a name="l75"></a>
<a name="l76"></a>    </span><span class=cF6>&quot;i.u32[0]\t=%X\n&quot;</span><span class=cF0>, i.u32[</span><span class=cFE>0</span><span class=cF0>];
<a name="l77"></a>    </span><span class=cF6>&quot;i.u32[1]\t=%X\n&quot;</span><span class=cF0>, i.u32[</span><span class=cFE>1</span><span class=cF0>];
<a name="l78"></a>}
<a name="l79"></a>
<a name="l80"></a></span><span class=cF5>CPURep</span><span class=cF0>;
<a name="l81"></a>Main;
<a name="l82"></a>DoIt2;
<a name="l83"></a>
<a name="l84"></a></span><span class=cF2>//See </span><a href="https://tomawezome.github.io/ZealOS/Demo/Lectures/FixedPointAdvanced.html#l1"><span class=cF4>::/Demo/Lectures/FixedPointAdvanced.CC</span></a><span class=cF0>
<a name="l85"></a>
<a name="l86"></a></span><span class=cF2>/*Program Output</span><span class=cF1>
<a name="l87"></a>
<a name="l88"></a>16 Cores 3.500GHz
<a name="l89"></a>Int Sum                 :2000000199.768690240 Time:  0.803s
<a name="l90"></a>Float Sum           :2000000225.656127040 Time:  3.615s
<a name="l91"></a>
<a name="l92"></a>i                           =123456789ABCDEF0
<a name="l93"></a>i&amp;0xFFFFFFFF        =9ABCDEF0
<a name="l94"></a>i&gt;&gt;32                   =12345678
<a name="l95"></a>i.u32[0]                =9ABCDEF0
<a name="l96"></a>i.u32[1]                =12345678
<a name="l97"></a></span><span class=cF2>*/</span><span class=cF1>
</span></pre></body>
</html>
