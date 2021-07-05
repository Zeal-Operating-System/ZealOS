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
<a name="l1"></a><span class=cF2>/*Asm labels can only be defined once</span><span class=cF0>
<a name="l2"></a></span><span class=cF2>in a task.  &lt;F5&gt; will spawn a new task</span><span class=cF0>
<a name="l3"></a></span><span class=cF2>each time, so you don't get redefine</span><span class=cF0>
<a name="l4"></a></span><span class=cF2>error, like when repeatedly #including</span><span class=cF0>
<a name="l5"></a></span><span class=cF2>it from the cmd line.</span><span class=cF0>
<a name="l6"></a></span><span class=cF2>*/</span><span class=cF0>
<a name="l7"></a>
<a name="l8"></a></span><span class=cF1>asm</span><span class=cF0> {
<a name="l9"></a></span><span class=cF2>//Opcodes are slightly different to make writing the x86_64 assembler easier.</span><span class=cF0>
<a name="l10"></a></span><span class=cF2>//See </span><a href="https://tomawezome.github.io/ZealOS/Compiler/OpCodes.html#l1"><span class=cF4>::/Compiler/OpCodes.DD</span></a><span class=cF2>.</span><span class=cF0>
<a name="l11"></a>
<a name="l12"></a>                </span><span class=cF1>IMPORT</span><span class=cF0>  </span><span class=cF5>Beep</span><span class=cF0>;
<a name="l13"></a>
<a name="l14"></a>_BEEPS::
<a name="l15"></a></span><span class=cF2>//You can always clobber RAX,RBX,RCX,RDX,R8,R9.  The compiler expects that.</span><span class=cF0>
<a name="l16"></a></span><span class=cF2>//See </span><a href="https://tomawezome.github.io/ZealOS/Kernel/KernelA.html#l1935"><span class=cF4>REGG_CLOBBERED</span></a><span class=cF2> and </span><a href="https://tomawezome.github.io/ZealOS/Kernel/KernelA.html#l1937"><span class=cF4>REGG_STACK_TMP</span></a><span class=cF2>.</span><span class=cF0>
<a name="l17"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RBP</span><span class=cF0>
<a name="l18"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBP</span><span class=cF0>, </span><span class=cFC>RSP</span><span class=cF0>
<a name="l19"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> </span><span class=cF3>SF_ARG1</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>]   </span><span class=cF2>//</span><a href="https://tomawezome.github.io/ZealOS/Kernel/KernelA.html#l714"><span class=cF4>SF_ARG1</span></a><span class=cF0>
<a name="l20"></a>
<a name="l21"></a>@@05:           </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RCX</span><span class=cF0>
<a name="l22"></a></span><span class=cF2>//U0 </span><a href="https://tomawezome.github.io/ZealOS/Kernel/KMisc.html#l200"><span class=cF4>Beep</span></a><span class=cF2>(I8 ona=62,Bool busy=FALSE)</span><span class=cF0>
<a name="l23"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cF3>FALSE</span><span class=cF0>   </span><span class=cF2>//Do not busy (spin) wait</span><span class=cF0>
<a name="l24"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFE>62</span><span class=cF0>          </span><span class=cF2>//500 Hz</span><span class=cF0>
<a name="l25"></a>                </span><span class=cF1>CALL</span><span class=cF0>        </span><span class=cF5>Beep</span><span class=cF0>
<a name="l26"></a>                </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>
<a name="l27"></a>                </span><span class=cF1>LOOP</span><span class=cF0>        @@05
<a name="l28"></a>
<a name="l29"></a>                </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>RBP</span><span class=cF0>
<a name="l30"></a>                </span><span class=cF1>RET1</span><span class=cF0>        </span><span class=cFE>8</span><span class=cF0>           </span><span class=cF2>//Use special return. Pop one arg off of stack.</span><span class=cF0>
<a name="l31"></a>
<a name="l32"></a></span><span class=cF2>//CosmiC return vals are in RAX.</span><span class=cF0>    </span><span class=cF2>This function has no return value.</span><span class=cF0>
<a name="l33"></a>}
<a name="l34"></a>
<a name="l35"></a></span><span class=cF2>//_extern binds a asm sym to a function.</span><span class=cF0>
<a name="l36"></a></span><span class=cF2>//The convention is to put an underscore</span><span class=cF0>
<a name="l37"></a></span><span class=cF2>//on C callable asm routines.</span><span class=cF0>
<a name="l38"></a></span><span class=cF1>_extern</span><span class=cF0> _BEEPS </span><span class=cF1>U0</span><span class=cF0> Beeps(</span><span class=cF9>I64</span><span class=cF0> count);
<a name="l39"></a>
<a name="l40"></a></span><span class=cF9>I64</span><span class=cF0> AsmAndC1()
<a name="l41"></a>{
<a name="l42"></a>    </span><span class=cF9>I64</span><span class=cF0> </span><span class=cF1>noreg</span><span class=cF0> i;    </span><span class=cF2>//Normally this would be stored in a reg</span><span class=cF0>
<a name="l43"></a></span><span class=cF2>//Check by unassembling with </span><a href="https://tomawezome.github.io/ZealOS/System/Debug.html#l330"><span class=cF4>Uf</span></a><span class=cF2>(&quot;AsmAndC1&quot;).</span><span class=cF0>
<a name="l44"></a>
<a name="l45"></a>    i = </span><span class=cF5>I64Get</span><span class=cF0>(</span><span class=cF6>&quot;Num of beeps 1-5 (%d):&quot;</span><span class=cF0>, </span><span class=cFE>3</span><span class=cF0>, </span><span class=cFE>1</span><span class=cF0>, </span><span class=cFE>5</span><span class=cF0>);
<a name="l46"></a>    Beeps(i);
<a name="l47"></a>
<a name="l48"></a>    </span><span class=cF1>asm</span><span class=cF0> </span><span class=cF7>{</span><span class=cF0>
<a name="l49"></a></span><span class=cF2>//You can clobber RAX,RBX,RCX,RDX.</span><span class=cF0>  </span><span class=cF2>The compiler expects that.</span><span class=cF0>
<a name="l50"></a>
<a name="l51"></a>        </span><span class=cF1>IMPORT</span><span class=cF0>      </span><span class=cF5>Sound</span><span class=cF0>; </span><span class=cF2>//Import an not use &amp; or don't import and use &amp;Sound.</span><span class=cF0>
<a name="l52"></a>        </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, &amp;i[</span><span class=cFC>RBP</span><span class=cF0>] </span><span class=cF2>//You can clobber RAX,RBX,RCX,RDX.</span><span class=cF0>
<a name="l53"></a>                                 </span><span class=cF2>//You better preserve the rest.</span><span class=cF0>
<a name="l54"></a>@@05:   </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RCX</span><span class=cF0>
<a name="l55"></a>
<a name="l56"></a>                                </span><span class=cF2>//U0 </span><a href="https://tomawezome.github.io/ZealOS/Kernel/KMisc.html#l129"><span class=cF4>Sound</span></a><span class=cF2>(I8 ona);</span><span class=cF0>
<a name="l57"></a>        </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFC>RCX</span><span class=cF0> </span><span class=cF2>//ona=loop*10+50</span><span class=cF0>
<a name="l58"></a>        </span><span class=cF1>IMUL2</span><span class=cF0>       </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>10</span><span class=cF0> </span><span class=cF2>//ZealOS uses nonstandard opcodes</span><span class=cF0>
<a name="l59"></a>                            </span><span class=cF2>//to avoid multiple form of the same one.</span><span class=cF0>
<a name="l60"></a>                            </span><span class=cF2>//See </span><a href="https://tomawezome.github.io/ZealOS/Compiler/OpCodes.html#l1"><span class=cF4>::/Compiler/OpCodes.DD</span></a><span class=cF2>.</span><span class=cF0>
<a name="l61"></a>        </span><span class=cF1>ADD</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>40</span><span class=cF0>
<a name="l62"></a>        </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RAX</span><span class=cF0>
<a name="l63"></a>        </span><span class=cF1>CALL</span><span class=cF0>        </span><span class=cF5>Sound</span><span class=cF0>
<a name="l64"></a>
<a name="l65"></a>        </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFB>counts</span><span class=cF0>.time_stamp_freq &gt;&gt; </span><span class=cFE>3</span><span class=cF0> </span><span class=cF2>//JIT Const.</span><span class=cF0>   </span><span class=cF2>Simple delay loop</span><span class=cF0>
<a name="l66"></a>@@10:   </span><span class=cF1>LOOP</span><span class=cF0>        @@10
<a name="l67"></a>
<a name="l68"></a>        </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>
<a name="l69"></a>        </span><span class=cF1>LOOP</span><span class=cF0>        @@05
<a name="l70"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l71"></a>    </span><span class=cF5>Sound</span><span class=cF0>;
<a name="l72"></a>
<a name="l73"></a>    </span><span class=cF1>return</span><span class=cF0> i;
<a name="l74"></a>}
<a name="l75"></a>
<a name="l76"></a></span><span class=cF6>&quot;Beeps:%d\n&quot;</span><span class=cF0>, AsmAndC1;
</span></pre></body>
</html>
