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
<a name="l1"></a><span class=cF1>U0</span><span class=cF0> IPV4Handler(CEthernetFrame *ethernet_frame)
<a name="l2"></a>{
<a name="l3"></a>    CIPV4Packet packet;
<a name="l4"></a>
<a name="l5"></a>    IPV4PacketParse(&amp;packet, ethernet_frame);
<a name="l6"></a>
<a name="l7"></a>    ARPCachePut(packet.source_ip_address, ethernet_frame-&gt;source_address);
<a name="l8"></a>
<a name="l9"></a>    </span><span class=cF1>switch</span><span class=cF0> (packet.protocol)
<a name="l10"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l11"></a>        </span><span class=cF1>case</span><span class=cF0> IP_PROTOCOL_ICMP:
<a name="l12"></a>            NetLog(</span><span class=cF6>&quot;IPV4 HANDLER: ICMP.&quot;</span><span class=cF0>);
<a name="l13"></a>            ICMPHandler(&amp;packet);
<a name="l14"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l15"></a>
<a name="l16"></a>        </span><span class=cF1>case</span><span class=cF0> IP_PROTOCOL_TCP:
<a name="l17"></a>            NetWarn(</span><span class=cF6>&quot;IPV4 HANDLER: TCP.&quot;</span><span class=cF0>);
<a name="l18"></a>            TCPHandler(&amp;packet);
<a name="l19"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l20"></a>
<a name="l21"></a>        </span><span class=cF1>case</span><span class=cF0> IP_PROTOCOL_UDP:
<a name="l22"></a>            NetLog(</span><span class=cF6>&quot;IPV4 HANDLER: UDP.&quot;</span><span class=cF0>);
<a name="l23"></a>            UDPHandler(&amp;packet);
<a name="l24"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l25"></a>
<a name="l26"></a>        </span><span class=cF1>default</span><span class=cF0>:
<a name="l27"></a>            NetErr(</span><span class=cF6>&quot;IPV4 HANDLER: Unrecognized protocol: 0x%X&quot;</span><span class=cF0>, packet.protocol);
<a name="l28"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l29"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l30"></a>
<a name="l31"></a>    NetLog(</span><span class=cF6>&quot;IPV4 HANDLER: Exiting.&quot;</span><span class=cF0>);
<a name="l32"></a>}
<a name="l33"></a>
<a name="l34"></a></span><span class=cF1>U0</span><span class=cF0> NetQueueEntryHandle(CNetQueueEntry *entry)
<a name="l35"></a>{
<a name="l36"></a>    CEthernetFrame ethernet_frame;
<a name="l37"></a>
<a name="l38"></a>    EthernetFrameParse(&amp;ethernet_frame, entry-&gt;frame, entry-&gt;packet_length);
<a name="l39"></a>
<a name="l40"></a>    </span><span class=cF1>switch</span><span class=cF0> (ethernet_frame.ethertype)
<a name="l41"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l42"></a>        </span><span class=cF1>case</span><span class=cF0> ETHERTYPE_ARP:
<a name="l43"></a>            NetLog(</span><span class=cF6>&quot;HANDLE NETQUEUE ENTRY: ARP.&quot;</span><span class=cF0>);
<a name="l44"></a>            ARPHandler(&amp;ethernet_frame);
<a name="l45"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l46"></a>
<a name="l47"></a>        </span><span class=cF1>case</span><span class=cF0> ETHERTYPE_IPV4:
<a name="l48"></a>            NetLog(</span><span class=cF6>&quot;HANDLE NETQUEUE ENTRY: IPV4.&quot;</span><span class=cF0>);
<a name="l49"></a>            IPV4Handler(&amp;ethernet_frame);
<a name="l50"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l51"></a>
<a name="l52"></a>        </span><span class=cF1>case</span><span class=cF0> ETHERTYPE_IPV6:
<a name="l53"></a>            NetWarn(</span><span class=cF6>&quot;HANDLE NETQUEUE ENTRY: IPV6. FIXME&quot;</span><span class=cF0>);
<a name="l54"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l55"></a>
<a name="l56"></a>        </span><span class=cF1>default</span><span class=cF0>:
<a name="l57"></a>            NetErr(</span><span class=cF6>&quot;HANDLE NETQUEUE ENTRY: Unrecognized ethertype: 0x%X&quot;</span><span class=cF0>, ethernet_frame.ethertype);
<a name="l58"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l59"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l60"></a>
<a name="l61"></a>    NetLog(</span><span class=cF6>&quot;HANDLE NETQUEUE ENTRY: Exiting.&quot;</span><span class=cF0>);
<a name="l62"></a>}
<a name="l63"></a>
<a name="l64"></a></span><span class=cF1>interrupt</span><span class=cF0> </span><span class=cF1>U0</span><span class=cF0> NetHandler()
<a name="l65"></a>{
<a name="l66"></a>    CNetQueueEntry *entry;
<a name="l67"></a>
<a name="l68"></a>    NetLog(</span><span class=cF6>&quot;$BG,DKGRAY$$FG,BLACK$&quot;</span><span class=cF0>
<a name="l69"></a>           </span><span class=cF6>&quot;=== NET HANDLER ===&quot;</span><span class=cF0>
<a name="l70"></a>           </span><span class=cF6>&quot;$BG$$FG$&quot;</span><span class=cF0>);
<a name="l71"></a>
<a name="l72"></a>    NetLog(</span><span class=cF6>&quot;$BD,LTGRAY$$FD,WHITE$&quot;</span><span class=cF0>
<a name="l73"></a>           </span><span class=cF6>&quot;NET HANDLER: Entering interrupt.&quot;</span><span class=cF0>);
<a name="l74"></a>
<a name="l75"></a>    </span><span class=cF1>while</span><span class=cF0> (entry = NetQueuePull)
<a name="l76"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l77"></a>        NetLog(</span><span class=cF6>&quot;NET HANDLER: Caught NetQueue Entry, handling.&quot;</span><span class=cF0>);
<a name="l78"></a>        NetQueueEntryHandle(entry);
<a name="l79"></a>        NetLog(</span><span class=cF6>&quot;NET HANDLER: Finished handling NetQueue Entry, Freeing.&quot;</span><span class=cF0>);
<a name="l80"></a>        </span><span class=cF5>Free</span><span class=cF0>(entry);
<a name="l81"></a>
<a name="l82"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l83"></a>
<a name="l84"></a>    NetLog(</span><span class=cF6>&quot;NET HANDLER: NetQueue empty, exiting interrupt.\n&quot;</span><span class=cF0>
<a name="l85"></a>           </span><span class=cF6>&quot;$BD,WHITE$$FD,LTGRAY$&quot;</span><span class=cF0>
<a name="l86"></a>           </span><span class=cF6>&quot;$BG,DKGRAY$$FG,BLACK$&quot;</span><span class=cF0>
<a name="l87"></a>           </span><span class=cF6>&quot;===================&quot;</span><span class=cF0>
<a name="l88"></a>           </span><span class=cF6>&quot;$BG$$FG$&quot;</span><span class=cF0>);
<a name="l89"></a>
<a name="l90"></a>    *(</span><span class=cFB>dev</span><span class=cF0>.uncached_alias + </span><span class=cF3>LAPIC_EOI</span><span class=cF0>)(</span><span class=cF9>U32</span><span class=cF0>*) = </span><span class=cFE>0</span><span class=cF0>;
<a name="l91"></a>}
<a name="l92"></a>
<a name="l93"></a></span><span class=cF1>U0</span><span class=cF0> NetHandlerInit()
<a name="l94"></a>{
<a name="l95"></a>    </span><span class=cF5>IntEntrySet</span><span class=cF0>(I_NETHANDLER, &amp;NetHandler);
<a name="l96"></a>}
<a name="l97"></a>
<a name="l98"></a>NetHandlerInit;
</span></pre></body>
</html>
