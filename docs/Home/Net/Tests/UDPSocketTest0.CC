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
<a name="l1"></a><span class=cF1>U0</span><span class=cF0> UDPSocketTest()
<a name="l2"></a>{
<a name="l3"></a>    CUDPSocket          *u0 = UDPSocket(AF_INET);
<a name="l4"></a>    CUDPSocket          *u1 = UDPSocket(AF_INET);
<a name="l5"></a>    CSocketAddressIPV4  *i0 = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF0>CSocketAddressIPV4</span><span class=cF7>)</span><span class=cF0>);
<a name="l6"></a>    CSocketAddressIPV4  *i1 = </span><span class=cF5>CAlloc</span><span class=cF0>(</span><span class=cF1>sizeof</span><span class=cF7>(</span><span class=cF0>CSocketAddressIPV4</span><span class=cF7>)</span><span class=cF0>);
<a name="l7"></a>
<a name="l8"></a>    i0-&gt;port            = </span><span class=cF5>EndianU16</span><span class=cF0>(</span><span class=cFE>80</span><span class=cF0>);
<a name="l9"></a>    i0-&gt;family          = AF_INET;
<a name="l10"></a>    i0-&gt;address.address = </span><span class=cFE>0xDEADBEEF</span><span class=cF0>;
<a name="l11"></a>
<a name="l12"></a>    i1-&gt;port            = </span><span class=cF5>EndianU16</span><span class=cF0>(</span><span class=cFE>68</span><span class=cF0>);
<a name="l13"></a>    i1-&gt;family          = AF_INET;
<a name="l14"></a>    i1-&gt;address.address = </span><span class=cFE>0xF00DBABE</span><span class=cF0>;
<a name="l15"></a>
<a name="l16"></a>    UDPSocketBind(u0, i0);
<a name="l17"></a>
<a name="l18"></a>    </span><span class=cF5>ClassRep</span><span class=cF0>(udp_globals.bound_socket_tree);
<a name="l19"></a>
<a name="l20"></a>    UDPSocketBind(u1, i1);
<a name="l21"></a>
<a name="l22"></a>    </span><span class=cF6>&quot;Before remove first socket\n&quot;</span><span class=cF0>;
<a name="l23"></a>    UDPRep;
<a name="l24"></a>    </span><span class=cF6>&quot;\n&quot;</span><span class=cF0>;
<a name="l25"></a>
<a name="l26"></a>    UDPSocketClose(u0);
<a name="l27"></a>
<a name="l28"></a>    </span><span class=cF6>&quot;After remove first socket\n&quot;</span><span class=cF0>;
<a name="l29"></a>    UDPRep;
<a name="l30"></a>    </span><span class=cF6>&quot;\n&quot;</span><span class=cF0>;
<a name="l31"></a>
<a name="l32"></a>    UDPSocketClose(u1);
<a name="l33"></a>
<a name="l34"></a>    </span><span class=cF6>&quot;After both sockets removed\n&quot;</span><span class=cF0>;
<a name="l35"></a>    UDPRep;
<a name="l36"></a>    </span><span class=cF6>&quot;\n&quot;</span><span class=cF0>;
<a name="l37"></a>
<a name="l38"></a>    </span><span class=cF5>Free</span><span class=cF0>(i0);
<a name="l39"></a>    </span><span class=cF5>Free</span><span class=cF0>(i1);
<a name="l40"></a>}
<a name="l41"></a>
<a name="l42"></a>UDPSocketTest;</span></pre></body>
</html>
