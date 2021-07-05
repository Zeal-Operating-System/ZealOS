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
<a name="l1"></a><span class=cF0>#</span><span class=cF1>help_index</span><span class=cF0> </span><span class=cF6>&quot;Graphics/Misc&quot;</span><span class=cF0>
<a name="l2"></a></span><span class=cF1>asm</span><span class=cF0> {
<a name="l3"></a></span><span class=cF2>//************************************</span><span class=cF0>
<a name="l4"></a></span><span class=cFD>_DC_BLOT_COLOR4</span><span class=cF0>::
<a name="l5"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RBP</span><span class=cF0>
<a name="l6"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBP</span><span class=cF0>, </span><span class=cFC>RSP</span><span class=cF0>
<a name="l7"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RSI</span><span class=cF0>
<a name="l8"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RDI</span><span class=cF0>
<a name="l9"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>R10</span><span class=cF0>
<a name="l10"></a>
<a name="l11"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RDI</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> </span><span class=cF3>SF_ARG1</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>]
<a name="l12"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RSI</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> </span><span class=cF3>SF_ARG2</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>]
<a name="l13"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> </span><span class=cF3>SF_ARG3</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>]
<a name="l14"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> </span><span class=cF3>SF_ARG4</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>]
<a name="l15"></a>
<a name="l16"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>R8</span><span class=cF0>,  </span><span class=cFC>RDI</span><span class=cF0>
<a name="l17"></a>                </span><span class=cF1>ADD</span><span class=cF0>         </span><span class=cFC>R8</span><span class=cF0>,  </span><span class=cFC>RCX</span><span class=cF0>
<a name="l18"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>R9</span><span class=cF0>,  </span><span class=cFC>R8</span><span class=cF0>
<a name="l19"></a>                </span><span class=cF1>ADD</span><span class=cF0>         </span><span class=cFC>R9</span><span class=cF0>,  </span><span class=cFC>RCX</span><span class=cF0>
<a name="l20"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>R10</span><span class=cF0>, </span><span class=cFC>R9</span><span class=cF0>
<a name="l21"></a>                </span><span class=cF1>ADD</span><span class=cF0>         </span><span class=cFC>R10</span><span class=cF0>, </span><span class=cFC>RCX</span><span class=cF0>
<a name="l22"></a>
<a name="l23"></a>@@5:        </span><span class=cF1>LODSQ</span><span class=cF0>
<a name="l24"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RBX</span><span class=cF0>]
<a name="l25"></a>                </span><span class=cF1>CMP</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l26"></a>                </span><span class=cF1>JE</span><span class=cF0>          </span><span class=cF9>I32</span><span class=cF0> @@10
<a name="l27"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RBX</span><span class=cF0>], </span><span class=cFC>RAX</span><span class=cF0>
<a name="l28"></a>
<a name="l29"></a>                </span><span class=cF1>XOR</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l30"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>7</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>0</span><span class=cF0>
<a name="l31"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l32"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l33"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>6</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>0</span><span class=cF0>
<a name="l34"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l35"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l36"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>5</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>0</span><span class=cF0>
<a name="l37"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l38"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l39"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>4</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>0</span><span class=cF0>
<a name="l40"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l41"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l42"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>3</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>0</span><span class=cF0>
<a name="l43"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l44"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l45"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>2</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>0</span><span class=cF0>
<a name="l46"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l47"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l48"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>1</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>0</span><span class=cF0>
<a name="l49"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l50"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l51"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>0</span><span class=cF0>
<a name="l52"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l53"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cF1>U8</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>], </span><span class=cFC>DL</span><span class=cF0>
<a name="l54"></a>
<a name="l55"></a>                </span><span class=cF1>XOR</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l56"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>7</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>1</span><span class=cF0>
<a name="l57"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l58"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l59"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>6</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>1</span><span class=cF0>
<a name="l60"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l61"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l62"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>5</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>1</span><span class=cF0>
<a name="l63"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l64"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l65"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>4</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>1</span><span class=cF0>
<a name="l66"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l67"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l68"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>3</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>1</span><span class=cF0>
<a name="l69"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l70"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l71"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>2</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>1</span><span class=cF0>
<a name="l72"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l73"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l74"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>1</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>1</span><span class=cF0>
<a name="l75"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l76"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l77"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>1</span><span class=cF0>
<a name="l78"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l79"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cF1>U8</span><span class=cF0> [</span><span class=cFC>R8</span><span class=cF0>], </span><span class=cFC>DL</span><span class=cF0>
<a name="l80"></a>
<a name="l81"></a>                </span><span class=cF1>XOR</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l82"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>7</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>2</span><span class=cF0>
<a name="l83"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l84"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l85"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>6</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>2</span><span class=cF0>
<a name="l86"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l87"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l88"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>5</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>2</span><span class=cF0>
<a name="l89"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l90"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l91"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>4</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>2</span><span class=cF0>
<a name="l92"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l93"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l94"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>3</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>2</span><span class=cF0>
<a name="l95"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l96"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l97"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>2</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>2</span><span class=cF0>
<a name="l98"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l99"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l100"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>1</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>2</span><span class=cF0>
<a name="l101"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l102"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l103"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>2</span><span class=cF0>
<a name="l104"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l105"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cF1>U8</span><span class=cF0> [</span><span class=cFC>R9</span><span class=cF0>], </span><span class=cFC>DL</span><span class=cF0>
<a name="l106"></a>
<a name="l107"></a>                </span><span class=cF1>XOR</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l108"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>7</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>3</span><span class=cF0>
<a name="l109"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l110"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l111"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>6</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>3</span><span class=cF0>
<a name="l112"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l113"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l114"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>5</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>3</span><span class=cF0>
<a name="l115"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l116"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l117"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>4</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>3</span><span class=cF0>
<a name="l118"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l119"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l120"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>3</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>3</span><span class=cF0>
<a name="l121"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l122"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l123"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>2</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>3</span><span class=cF0>
<a name="l124"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l125"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l126"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>1</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>3</span><span class=cF0>
<a name="l127"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l128"></a>                </span><span class=cF1>SHL1</span><span class=cF0>        </span><span class=cFC>RDX</span><span class=cF0>
<a name="l129"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0> + </span><span class=cFE>3</span><span class=cF0>
<a name="l130"></a>                </span><span class=cF1>ADC</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>
<a name="l131"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cF1>U8</span><span class=cF0> [</span><span class=cFC>R10</span><span class=cF0>], </span><span class=cFC>DL</span><span class=cF0>
<a name="l132"></a>
<a name="l133"></a>@@10:           </span><span class=cF1>ADD</span><span class=cF0>         </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cFE>8</span><span class=cF0>
<a name="l134"></a>
<a name="l135"></a>                </span><span class=cF1>INC</span><span class=cF0>         </span><span class=cFC>RDI</span><span class=cF0>
<a name="l136"></a>                </span><span class=cF1>INC</span><span class=cF0>         </span><span class=cFC>R8</span><span class=cF0>
<a name="l137"></a>                </span><span class=cF1>INC</span><span class=cF0>         </span><span class=cFC>R9</span><span class=cF0>
<a name="l138"></a>                </span><span class=cF1>INC</span><span class=cF0>         </span><span class=cFC>R10</span><span class=cF0>
<a name="l139"></a>
<a name="l140"></a>                </span><span class=cF1>DEC</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>
<a name="l141"></a>                </span><span class=cF1>JNZ</span><span class=cF0>         </span><span class=cF9>I32</span><span class=cF0> @@5
<a name="l142"></a>
<a name="l143"></a>                </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>R10</span><span class=cF0>
<a name="l144"></a>                </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>RDI</span><span class=cF0>
<a name="l145"></a>                </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>RSI</span><span class=cF0>
<a name="l146"></a>                </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>RBP</span><span class=cF0>
<a name="l147"></a>                </span><span class=cF1>RET1</span><span class=cF0>        </span><span class=cFE>32</span><span class=cF0>
<a name="l148"></a></span><span class=cF2>//************************************</span><span class=cF0>
<a name="l149"></a></span><span class=cFD>_IS_PIX_COVERED0</span><span class=cF0>::
<a name="l150"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RBP</span><span class=cF0>
<a name="l151"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBP</span><span class=cF0>, </span><span class=cFC>RSP</span><span class=cF0>
<a name="l152"></a>#</span><span class=cF1>assert</span><span class=cF0> </span><span class=cF3>FONT_WIDTH</span><span class=cF0> == </span><span class=cF3>FONT_HEIGHT</span><span class=cF0> == </span><span class=cFE>8</span><span class=cF0>
<a name="l153"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> </span><span class=cF3>SF_ARG3</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>]
<a name="l154"></a>                </span><span class=cF1>SAR</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFE>3</span><span class=cF0>
<a name="l155"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> </span><span class=cF3>SF_ARG2</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>]
<a name="l156"></a>                </span><span class=cF1>SAR</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>3</span><span class=cF0>
<a name="l157"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> </span><span class=cF3>SF_ARG1</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>]
<a name="l158"></a>                </span><span class=cF1>IMUL2</span><span class=cF0>       </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cF3>TEXT_COLS</span><span class=cF0>
<a name="l159"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [&amp;</span><span class=cFB>gr</span><span class=cF0>.win_z_buf]
<a name="l160"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>DX</span><span class=cF0>,  </span><span class=cF9>U16</span><span class=cF0> </span><span class=cF9>CTask</span><span class=cF0>.win_z_num[</span><span class=cFC>RDX</span><span class=cF0>]
<a name="l161"></a>                </span><span class=cF1>ADD</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RAX</span><span class=cF0>
<a name="l162"></a>                </span><span class=cF1>XOR</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFC>RAX</span><span class=cF0>
<a name="l163"></a>                </span><span class=cF1>CMP</span><span class=cF0>         </span><span class=cFC>DX</span><span class=cF0>, </span><span class=cF9>U16</span><span class=cF0> [</span><span class=cFC>RBX</span><span class=cF0> + </span><span class=cFC>RCX</span><span class=cF0> * </span><span class=cFE>2</span><span class=cF0>]
<a name="l164"></a>                </span><span class=cF1>JAE</span><span class=cF0>         @@05        </span><span class=cF2>//Jump not covered</span><span class=cF0>
<a name="l165"></a>                </span><span class=cF1>INC</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>
<a name="l166"></a>@@05:           </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>RBP</span><span class=cF0>
<a name="l167"></a>                </span><span class=cF1>RET1</span><span class=cF0>        </span><span class=cFE>24</span><span class=cF0>
<a name="l168"></a></span><span class=cF2>//************************************</span><span class=cF0>
<a name="l169"></a></span><span class=cFD>_GR_ROP_EQU_U8_NO_CLIPPING</span><span class=cF0>::
<a name="l170"></a></span><span class=cF2>//Puts foreground char shape onto gr.dc2.</span><span class=cF0>
<a name="l171"></a></span><span class=cF2>//ch.u8[1] is color as a whole byte</span><span class=cF0>
<a name="l172"></a></span><span class=cF2>//ch ATTRf_UNDERLINE attr flag is used.</span><span class=cF0>
<a name="l173"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RBP</span><span class=cF0>
<a name="l174"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBP</span><span class=cF0>, </span><span class=cFC>RSP</span><span class=cF0>
<a name="l175"></a>                </span><span class=cF1>MOVZX</span><span class=cF0>       </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cF1>U8</span><span class=cF0> </span><span class=cF3>SF_ARG1</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>]
<a name="l176"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [&amp;</span><span class=cFB>text</span><span class=cF0>.font]
<a name="l177"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDX</span><span class=cF0> + </span><span class=cFC>RAX</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0>]        </span><span class=cF2>//RAX is 8x8 char font data, 64-bits</span><span class=cF0>
<a name="l178"></a>                </span><span class=cF1>BT</span><span class=cF0>          </span><span class=cF9>U64</span><span class=cF0> </span><span class=cF3>SF_ARG1</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>], </span><span class=cF3>ATTRf_UNDERLINE</span><span class=cF0>
<a name="l179"></a>                </span><span class=cF1>JNC</span><span class=cF0>         @@05
<a name="l180"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cFE>0xFF00000000000000</span><span class=cF0>
<a name="l181"></a>                </span><span class=cF1>OR</span><span class=cF0>          </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFC>RBX</span><span class=cF0>
<a name="l182"></a>@@05:           </span><span class=cF1>TEST</span><span class=cF0>        </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFC>RAX</span><span class=cF0>
<a name="l183"></a>                </span><span class=cF1>JZ</span><span class=cF0>          </span><span class=cF9>I32</span><span class=cF0> @@10
<a name="l184"></a>
<a name="l185"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RSI</span><span class=cF0>
<a name="l186"></a>                </span><span class=cF1>PUSH</span><span class=cF0>        </span><span class=cFC>RDI</span><span class=cF0>
<a name="l187"></a>                </span><span class=cF1>MOVZX</span><span class=cF0>       </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cF1>U8</span><span class=cF0> </span><span class=cF3>SF_ARG1</span><span class=cF0> + </span><span class=cFE>1</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>]    </span><span class=cF2>//Warning color is 8-bit</span><span class=cF0>
<a name="l188"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [&amp;</span><span class=cFB>gr</span><span class=cF0>.to_8_colors]
<a name="l189"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>R8</span><span class=cF0>,  </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDX</span><span class=cF0> + </span><span class=cFC>RBX</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0>]            </span><span class=cF2>//R8 is color repeated 8 times.</span><span class=cF0>
<a name="l190"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>R9</span><span class=cF0>,  </span><span class=cF9>U64</span><span class=cF0> </span><span class=cF3>SF_ARG3</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>]       </span><span class=cF2>//R9 is width_internal</span><span class=cF0>
<a name="l191"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RDI</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> </span><span class=cF3>SF_ARG2</span><span class=cF0>[</span><span class=cFC>RBP</span><span class=cF0>]
<a name="l192"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RSI</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [&amp;</span><span class=cFB>gr</span><span class=cF0>.to_8_bits] </span><span class=cF2>//RSI is gr.to_8_bits</span><span class=cF0>
<a name="l193"></a>
<a name="l194"></a></span><span class=cF2>//</span><span class=cF0>          </span><span class=cF2>m=my_1_to_8_bits[ch&amp;255];ch&gt;&gt;=8;</span><span class=cF0>
<a name="l195"></a></span><span class=cF2>//</span><span class=cF0>          </span><span class=cF2>*dst=*dst&amp;~m|c&amp;m;</span><span class=cF0>
<a name="l196"></a></span><span class=cF2>//</span><span class=cF0>          </span><span class=cF2>dst(U8 *)+=w1;</span><span class=cF0>
<a name="l197"></a>
<a name="l198"></a>                </span><span class=cF1>MOVZX</span><span class=cF0>       </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cFC>AL</span><span class=cF0>
<a name="l199"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RSI</span><span class=cF0> + </span><span class=cFC>RBX</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0>]
<a name="l200"></a>                </span><span class=cF1>SHR</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>8</span><span class=cF0>
<a name="l201"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>]
<a name="l202"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l203"></a>                </span><span class=cF1>NOT</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>
<a name="l204"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFC>R8</span><span class=cF0>
<a name="l205"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RBX</span><span class=cF0>
<a name="l206"></a>                </span><span class=cF1>OR</span><span class=cF0>          </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l207"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>], </span><span class=cFC>RCX</span><span class=cF0>
<a name="l208"></a>                </span><span class=cF1>ADD</span><span class=cF0>         </span><span class=cFC>RDI</span><span class=cF0>, </span><span class=cFC>R9</span><span class=cF0>
<a name="l209"></a>
<a name="l210"></a>                </span><span class=cF1>MOVZX</span><span class=cF0>       </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cFC>AL</span><span class=cF0>
<a name="l211"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RSI</span><span class=cF0> + </span><span class=cFC>RBX</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0>]
<a name="l212"></a>                </span><span class=cF1>SHR</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>8</span><span class=cF0>
<a name="l213"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>]
<a name="l214"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l215"></a>                </span><span class=cF1>NOT</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>
<a name="l216"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFC>R8</span><span class=cF0>
<a name="l217"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RBX</span><span class=cF0>
<a name="l218"></a>                </span><span class=cF1>OR</span><span class=cF0>          </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l219"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>], </span><span class=cFC>RCX</span><span class=cF0>
<a name="l220"></a>                </span><span class=cF1>ADD</span><span class=cF0>         </span><span class=cFC>RDI</span><span class=cF0>, </span><span class=cFC>R9</span><span class=cF0>
<a name="l221"></a>
<a name="l222"></a>                </span><span class=cF1>MOVZX</span><span class=cF0>       </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cFC>AL</span><span class=cF0>
<a name="l223"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RSI</span><span class=cF0> + </span><span class=cFC>RBX</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0>]
<a name="l224"></a>                </span><span class=cF1>SHR</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>8</span><span class=cF0>
<a name="l225"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>]
<a name="l226"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l227"></a>                </span><span class=cF1>NOT</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>
<a name="l228"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFC>R8</span><span class=cF0>
<a name="l229"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RBX</span><span class=cF0>
<a name="l230"></a>                </span><span class=cF1>OR</span><span class=cF0>          </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l231"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>], </span><span class=cFC>RCX</span><span class=cF0>
<a name="l232"></a>                </span><span class=cF1>ADD</span><span class=cF0>         </span><span class=cFC>RDI</span><span class=cF0>, </span><span class=cFC>R9</span><span class=cF0>
<a name="l233"></a>
<a name="l234"></a>                </span><span class=cF1>MOVZX</span><span class=cF0>       </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cFC>AL</span><span class=cF0>
<a name="l235"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RSI</span><span class=cF0> + </span><span class=cFC>RBX</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0>]
<a name="l236"></a>                </span><span class=cF1>SHR</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>8</span><span class=cF0>
<a name="l237"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>]
<a name="l238"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l239"></a>                </span><span class=cF1>NOT</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>
<a name="l240"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFC>R8</span><span class=cF0>
<a name="l241"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RBX</span><span class=cF0>
<a name="l242"></a>                </span><span class=cF1>OR</span><span class=cF0>          </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l243"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>], </span><span class=cFC>RCX</span><span class=cF0>
<a name="l244"></a>                </span><span class=cF1>ADD</span><span class=cF0>         </span><span class=cFC>RDI</span><span class=cF0>, </span><span class=cFC>R9</span><span class=cF0>
<a name="l245"></a>
<a name="l246"></a>                </span><span class=cF1>MOVZX</span><span class=cF0>       </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cFC>AL</span><span class=cF0>
<a name="l247"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RSI</span><span class=cF0> + </span><span class=cFC>RBX</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0>]
<a name="l248"></a>                </span><span class=cF1>SHR</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>8</span><span class=cF0>
<a name="l249"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>]
<a name="l250"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l251"></a>                </span><span class=cF1>NOT</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>
<a name="l252"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFC>R8</span><span class=cF0>
<a name="l253"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RBX</span><span class=cF0>
<a name="l254"></a>                </span><span class=cF1>OR</span><span class=cF0>          </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l255"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>], </span><span class=cFC>RCX</span><span class=cF0>
<a name="l256"></a>                </span><span class=cF1>ADD</span><span class=cF0>         </span><span class=cFC>RDI</span><span class=cF0>, </span><span class=cFC>R9</span><span class=cF0>
<a name="l257"></a>
<a name="l258"></a>                </span><span class=cF1>MOVZX</span><span class=cF0>       </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cFC>AL</span><span class=cF0>
<a name="l259"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RSI</span><span class=cF0> + </span><span class=cFC>RBX</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0>]
<a name="l260"></a>                </span><span class=cF1>SHR</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>8</span><span class=cF0>
<a name="l261"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>]
<a name="l262"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l263"></a>                </span><span class=cF1>NOT</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>
<a name="l264"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFC>R8</span><span class=cF0>
<a name="l265"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RBX</span><span class=cF0>
<a name="l266"></a>                </span><span class=cF1>OR</span><span class=cF0>          </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l267"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>], </span><span class=cFC>RCX</span><span class=cF0>
<a name="l268"></a>                </span><span class=cF1>ADD</span><span class=cF0>         </span><span class=cFC>RDI</span><span class=cF0>, </span><span class=cFC>R9</span><span class=cF0>
<a name="l269"></a>
<a name="l270"></a>                </span><span class=cF1>MOVZX</span><span class=cF0>       </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cFC>AL</span><span class=cF0>
<a name="l271"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RSI</span><span class=cF0> + </span><span class=cFC>RBX</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0>]
<a name="l272"></a>                </span><span class=cF1>SHR</span><span class=cF0>         </span><span class=cFC>RAX</span><span class=cF0>, </span><span class=cFE>8</span><span class=cF0>
<a name="l273"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>]
<a name="l274"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l275"></a>                </span><span class=cF1>NOT</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>
<a name="l276"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFC>R8</span><span class=cF0>
<a name="l277"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RBX</span><span class=cF0>
<a name="l278"></a>                </span><span class=cF1>OR</span><span class=cF0>          </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l279"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>], </span><span class=cFC>RCX</span><span class=cF0>
<a name="l280"></a>                </span><span class=cF1>ADD</span><span class=cF0>         </span><span class=cFC>RDI</span><span class=cF0>, </span><span class=cFC>R9</span><span class=cF0>
<a name="l281"></a>
<a name="l282"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RSI</span><span class=cF0> + </span><span class=cFC>RAX</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0>]
<a name="l283"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RBX</span><span class=cF0>, </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>]
<a name="l284"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l285"></a>                </span><span class=cF1>NOT</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>
<a name="l286"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RDX</span><span class=cF0>, </span><span class=cFC>R8</span><span class=cF0>
<a name="l287"></a>                </span><span class=cF1>AND</span><span class=cF0>         </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RBX</span><span class=cF0>
<a name="l288"></a>                </span><span class=cF1>OR</span><span class=cF0>          </span><span class=cFC>RCX</span><span class=cF0>, </span><span class=cFC>RDX</span><span class=cF0>
<a name="l289"></a>                </span><span class=cF1>MOV</span><span class=cF0>         </span><span class=cF9>U64</span><span class=cF0> [</span><span class=cFC>RDI</span><span class=cF0>], </span><span class=cFC>RCX</span><span class=cF0>
<a name="l290"></a>
<a name="l291"></a>                </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>RDI</span><span class=cF0>
<a name="l292"></a>                </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>RSI</span><span class=cF0>
<a name="l293"></a>@@10:           </span><span class=cF1>POP</span><span class=cF0>         </span><span class=cFC>RBP</span><span class=cF0>
<a name="l294"></a>                </span><span class=cF1>RET1</span><span class=cF0>        </span><span class=cFE>24</span><span class=cF0>
<a name="l295"></a>};
<a name="l296"></a>
<a name="l297"></a></span><span class=cF1>_extern</span><span class=cF0>         </span><span class=cFD>_GR_ROP_EQU_U8_NO_CLIPPING</span><span class=cF0>  </span><span class=cF1>U0</span><span class=cF0>   </span><span class=cF5>GrRopEquU8NoClipping</span><span class=cF0>(</span><span class=cF9>I64</span><span class=cF0> ch, </span><span class=cF1>U8</span><span class=cF0> *dst, </span><span class=cF9>I64</span><span class=cF0> width_internal);
<a name="l298"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF1>_extern</span><span class=cF0>  </span><span class=cFD>_IS_PIX_COVERED0</span><span class=cF0>            </span><span class=cF1>Bool</span><span class=cF0> </span><span class=cF5>IsPixCovered0</span><span class=cF0>(</span><span class=cF9>CTask</span><span class=cF0> *task, </span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y);</span><span class=cF2>//No clipping</span><span class=cF0>
<a name="l299"></a></span><span class=cF1>_extern</span><span class=cF0>         </span><span class=cFD>_DC_BLOT_COLOR4</span><span class=cF0>             </span><span class=cF1>U0</span><span class=cF0>   </span><span class=cF5>DCBlotColor4</span><span class=cF0>(</span><span class=cF1>U8</span><span class=cF0> *dst, </span><span class=cF9>I64</span><span class=cF0> *img, </span><span class=cF9>I64</span><span class=cF0> *img_cache, </span><span class=cF9>I64</span><span class=cF0> count);
</span></pre></body>
</html>
