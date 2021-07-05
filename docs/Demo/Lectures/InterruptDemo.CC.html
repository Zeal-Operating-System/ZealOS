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
<a name="l1"></a><span class=cF2>//This is the software interrupt num</span><span class=cF0>
<a name="l2"></a></span><span class=cF2>//we will use.  See </span><a href="https://tomawezome.github.io/ZealOS/Kernel/KernelA.html#l336"><span class=cF4>Software Int's</span></a><span class=cF2> for</span><span class=cF0>
<a name="l3"></a></span><span class=cF2>//picking a num.  Nums are subject to change.</span><span class=cF0>
<a name="l4"></a>
<a name="l5"></a>#</span><span class=cF1>define</span><span class=cF0> I_F_UNARY_MINUS </span><span class=cF3>I_USER</span><span class=cF0>
<a name="l6"></a>
<a name="l7"></a></span><span class=cF1>asm</span><span class=cF0> {
<a name="l8"></a>
<a name="l9"></a></span><span class=cF2>//This changes the sign of the floating</span><span class=cF0>
<a name="l10"></a></span><span class=cF2>//point val in RAX</span><span class=cF0>
<a name="l11"></a>F_UNARY_MINUS_INT::
<a name="l12"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RAX</span><span class=cF0>
<a name="l13"></a>                </span><span class=cF1>FLD</span><span class=cF0>         </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RSP</span><span class=cF0>]
<a name="l14"></a>                </span><span class=cF1>FCHS</span><span class=cF0>
<a name="l15"></a>                </span><span class=cF1>FSTP</span><span class=cF0>        </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RSP</span><span class=cF0>]
<a name="l16"></a>                </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>
<a name="l17"></a>                </span><span class=cF1>IRET</span><span class=cF0>
<a name="l18"></a>
<a name="l19"></a></span><span class=cF2>//This does the same thing, but not as</span><span class=cF0>
<a name="l20"></a></span><span class=cF2>//an interrupt.</span><span class=cF0>
<a name="l21"></a>F_UNARY_MINUS_CALL::
<a name="l22"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RAX</span><span class=cF0>
<a name="l23"></a>                </span><span class=cF1>FLD</span><span class=cF0>         </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RSP</span><span class=cF0>]
<a name="l24"></a>                </span><span class=cF1>FCHS</span><span class=cF0>
<a name="l25"></a>                </span><span class=cF1>FSTP</span><span class=cF0>        </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RSP</span><span class=cF0>]
<a name="l26"></a>                </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>
<a name="l27"></a>                </span><span class=cF1>RET</span><span class=cF0>
<a name="l28"></a>
<a name="l29"></a></span><span class=cF2>//This invokes the interrupt version</span><span class=cF0>
<a name="l30"></a></span><span class=cF2>//with a C callable function.</span><span class=cF0>
<a name="l31"></a>_F_UM_INT::
<a name="l32"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RBP</span><span class=cF0>
<a name="l33"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBP</span><span class=cF0>, </span><span class=cFC>RSP</span><span class=cF0>
<a name="l34"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cF3>SF_ARG1</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>]
<a name="l35"></a>                </span><span class=cF1>INT</span><span class=cF0>         I_F_UNARY_MINUS
<a name="l36"></a>                </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>RBP</span><span class=cF0>
<a name="l37"></a>                </span><span class=cF1>RET1</span><span class=cF0>        </span><span class=cFE>8</span><span class=cF0>
<a name="l38"></a>
<a name="l39"></a></span><span class=cF2>//This invokes the call version</span><span class=cF0>
<a name="l40"></a></span><span class=cF2>//with a C callable function.</span><span class=cF0>
<a name="l41"></a>_F_UM_CALL::
<a name="l42"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RBP</span><span class=cF0>
<a name="l43"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBP</span><span class=cF0>, </span><span class=cFC>RSP</span><span class=cF0>
<a name="l44"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cF3>SF_ARG1</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>]
<a name="l45"></a>                </span><span class=cF1>CALL</span><span class=cF0>        F_UNARY_MINUS_CALL
<a name="l46"></a>                </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>RBP</span><span class=cF0>
<a name="l47"></a>                </span><span class=cF1>RET1</span><span class=cF0>        </span><span class=cFE>8</span><span class=cF0>
<a name="l48"></a>}
<a name="l49"></a>
<a name="l50"></a></span><span class=cF1>_extern</span><span class=cF0> _F_UM_INT  </span><span class=cF1>F64</span><span class=cF0> UnaryMinusInt(</span><span class=cF1>F64</span><span class=cF0> d);
<a name="l51"></a></span><span class=cF1>_extern</span><span class=cF0> _F_UM_CALL </span><span class=cF1>F64</span><span class=cF0> UnaryMinusCall(</span><span class=cF1>F64</span><span class=cF0> d);
<a name="l52"></a>
<a name="l53"></a>#</span><span class=cF1>define</span><span class=cF0> SAMPLE_SIZE         </span><span class=cFE>1000000</span><span class=cF0>
<a name="l54"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>TimeIns</span><span class=cF0>()
<a name="l55"></a>{
<a name="l56"></a>    </span><span class=cF9>I64</span><span class=cF0> </span><span class=cF1>start</span><span class=cF0>, </span><span class=cF1>end</span><span class=cF0>;
<a name="l57"></a>    </span><span class=cF9>I64</span><span class=cF0> i, old_irq;
<a name="l58"></a>
<a name="l59"></a>    </span><span class=cF5>CPURep</span><span class=cF0>;
<a name="l60"></a>    old_irq = </span><span class=cF5>IntEntrySet</span><span class=cF0>(I_F_UNARY_MINUS, F_UNARY_MINUS_INT, </span><span class=cF3>IDTET_TRAP</span><span class=cF0>);
<a name="l61"></a>
<a name="l62"></a>    </span><span class=cF2>//Measure interrupt time</span><span class=cF0>
<a name="l63"></a>    </span><span class=cF1>start</span><span class=cF0> = </span><span class=cF5>TSCGet</span><span class=cF0>;
<a name="l64"></a>    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; SAMPLE_SIZE; i++)
<a name="l65"></a>        UnaryMinusInt(</span><span class=cF3>pi</span><span class=cF0>);
<a name="l66"></a>    </span><span class=cF1>end</span><span class=cF0> = </span><span class=cF5>TSCGet</span><span class=cF0>;
<a name="l67"></a>    </span><span class=cF6>&quot;Interrupt Cycles: %10.5f\n&quot;</span><span class=cF0>, </span><span class=cF5>ToF64</span><span class=cF0>(</span><span class=cF1>end</span><span class=cF0> - </span><span class=cF1>start</span><span class=cF0>) / SAMPLE_SIZE;
<a name="l68"></a>
<a name="l69"></a>    </span><span class=cF2>//Measure call time</span><span class=cF0>
<a name="l70"></a>    </span><span class=cF1>start</span><span class=cF0> = </span><span class=cF5>TSCGet</span><span class=cF0>;
<a name="l71"></a>    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; SAMPLE_SIZE; i++)
<a name="l72"></a>        UnaryMinusCall(</span><span class=cF3>pi</span><span class=cF0>);
<a name="l73"></a>    </span><span class=cF1>end</span><span class=cF0> = </span><span class=cF5>TSCGet</span><span class=cF0>;
<a name="l74"></a>    </span><span class=cF6>&quot;Call      Cycles: %10.5f\n&quot;</span><span class=cF0>, </span><span class=cF5>ToF64</span><span class=cF0>(</span><span class=cF1>end</span><span class=cF0> - </span><span class=cF1>start</span><span class=cF0>) / SAMPLE_SIZE;
<a name="l75"></a>
<a name="l76"></a>    </span><span class=cF5>IntEntrySet</span><span class=cF0>(I_F_UNARY_MINUS, old_irq, </span><span class=cF3>IDTET_IRQ</span><span class=cF0>);
<a name="l77"></a>}
<a name="l78"></a>
<a name="l79"></a></span><span class=cF5>TimeIns</span><span class=cF0>;
<a name="l80"></a>
<a name="l81"></a></span><span class=cF2>/*</span><span class=cF0>  </span><span class=cF2>Program Output</span><span class=cF1>
<a name="l82"></a>6 Cores 3.395GHz
<a name="l83"></a>Interrupt Cycles:  573.98543
<a name="l84"></a>Call            Cycles:      9.74349
<a name="l85"></a></span><span class=cF2>*/</span><span class=cF1>
<a name="l86"></a>
</span></pre></body>
</html>
