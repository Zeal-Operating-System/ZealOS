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
<a name="l2"></a>        </span><span class=cFA>
<a name="l3"></a>        &lt;1&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l4"></a>        </span><span class=cFA>
<a name="l5"></a>        &lt;2&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l6"></a>        </span><span class=cFA>
<a name="l7"></a>        &lt;3&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l8"></a>        </span><span class=cFA>
<a name="l9"></a>        &lt;4&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l10"></a>        </span><span class=cFA>
<a name="l11"></a>        &lt;5&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l12"></a>        </span><span class=cFA>
<a name="l13"></a>        &lt;6&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l14"></a>        
<a name="l15"></a>        </span><span class=cFA>
<a name="l16"></a>        &lt;7&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l17"></a>        
<a name="l18"></a>         </span><span class=cFA>
<a name="l19"></a>        &lt;8&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l20"></a>        
<a name="l21"></a>        </span><span class=cFA>
<a name="l22"></a>        &lt;9&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l23"></a>        
<a name="l24"></a>        </span><span class=cFA>
<a name="l25"></a>        &lt;10&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l26"></a>        
<a name="l27"></a>        </span><span class=cFA>
<a name="l28"></a>        &lt;11&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l29"></a>        
<a name="l30"></a>        
<a name="l31"></a>        
<a name="l32"></a>        
<a name="l33"></a>        
<a name="l34"></a>        
<a name="l35"></a>        </span><span class=cFA>
<a name="l36"></a>        &lt;12&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l37"></a>        
<a name="l38"></a>        
<a name="l39"></a>         
<a name="l40"></a>        </span><span class=cFA>
<a name="l41"></a>        &lt;13&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l42"></a>        </span><span class=cFA>
<a name="l43"></a>        &lt;14&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l44"></a>        </span><span class=cFA>
<a name="l45"></a>        &lt;15&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l46"></a>        
<a name="l47"></a>        </span><span class=cFA>
<a name="l48"></a>        &lt;16&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l49"></a>
<a name="l50"></a>#</span><span class=cF1>define</span><span class=cF0> PSM_NOTE_SPACING            </span><span class=cFE>9</span><span class=cF0>
<a name="l51"></a>#</span><span class=cF1>define</span><span class=cF0> PSM_DURATIONS_NUM           </span><span class=cFE>12</span><span class=cF0>
<a name="l52"></a>
<a name="l53"></a></span><span class=cF1>F64</span><span class=cF0> psm_durations[PSM_DURATIONS_NUM + </span><span class=cFE>1</span><span class=cF0>] =
<a name="l54"></a>        {</span><span class=cFE>2</span><span class=cF0> * .</span><span class=cFE>25</span><span class=cF0> / </span><span class=cFE>3</span><span class=cF0>, .</span><span class=cFE>25</span><span class=cF0>, </span><span class=cFE>2</span><span class=cF0> * .</span><span class=cFE>5</span><span class=cF0> / </span><span class=cFE>3</span><span class=cF0>, .</span><span class=cFE>5</span><span class=cF0>, </span><span class=cFE>2</span><span class=cF0>.</span><span class=cFE>0</span><span class=cF0> / </span><span class=cFE>3</span><span class=cF0>.</span><span class=cFE>0</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>.</span><span class=cFE>5</span><span class=cF0> * </span><span class=cFE>1</span><span class=cF0>.</span><span class=cFE>5</span><span class=cF0>, </span><span class=cFE>1</span><span class=cF0>.</span><span class=cFE>0</span><span class=cF0>, </span><span class=cFE>1</span><span class=cF0>.</span><span class=cFE>5</span><span class=cF0>, </span><span class=cFE>2</span><span class=cF0>.</span><span class=cFE>0</span><span class=cF0>, </span><span class=cFE>3</span><span class=cF0>.</span><span class=cFE>0</span><span class=cF0>, </span><span class=cFE>4</span><span class=cF0>.</span><span class=cFE>0</span><span class=cF0>, </span><span class=cFE>6</span><span class=cF0>.</span><span class=cFE>0</span><span class=cF0>, </span><span class=cFE>1000000</span><span class=cF0>.</span><span class=cFE>0</span><span class=cF0>};
<a name="l55"></a></span><span class=cF1>U8</span><span class=cF0> *psm_duration_list = </span><span class=cF6>&quot;st\0s\0et\0e\0qt\0e.\0q\0q.\0h\0h.\0w\0w.\0&quot;</span><span class=cF0>;
<a name="l56"></a></span><span class=cF1>U8</span><span class=cF0> *psm_duration_imgs[PSM_DURATIONS_NUM] = {</span><span class=cFA>&lt;1&gt;</span><span class=cF0>, </span><span class=cFA>&lt;1&gt;</span><span class=cF0>, </span><span class=cFA>&lt;2&gt;</span><span class=cF0>, </span><span class=cFA>&lt;2&gt;</span><span class=cF0>, </span><span class=cFA>&lt;3&gt;</span><span class=cF0>, </span><span class=cFA>&lt;2&gt;</span><span class=cF0>, </span><span class=cFA>&lt;3&gt;</span><span class=cF0>, </span><span class=cFA>&lt;3&gt;</span><span class=cF0>, </span><span class=cFA>&lt;4&gt;</span><span class=cF0>, </span><span class=cFA>&lt;4&gt;</span><span class=cF0>, </span><span class=cFA>&lt;5&gt;</span><span class=cF0>, </span><span class=cFA>&lt;5&gt;</span><span class=cF0>};
<a name="l57"></a></span><span class=cF1>Bool</span><span class=cF0> psm_triplet_durations[PSM_DURATIONS_NUM] =
<a name="l58"></a>        {</span><span class=cF3>TRUE</span><span class=cF0>, </span><span class=cF3>FALSE</span><span class=cF0>, </span><span class=cF3>TRUE</span><span class=cF0>, </span><span class=cF3>FALSE</span><span class=cF0>, </span><span class=cF3>TRUE</span><span class=cF0>, </span><span class=cF3>FALSE</span><span class=cF0>, </span><span class=cF3>FALSE</span><span class=cF0>, </span><span class=cF3>FALSE</span><span class=cF0>, </span><span class=cF3>FALSE</span><span class=cF0>, </span><span class=cF3>FALSE</span><span class=cF0>, </span><span class=cF3>FALSE</span><span class=cF0>, </span><span class=cF3>FALSE</span><span class=cF0>};
<a name="l59"></a>
<a name="l60"></a></span><span class=cF1>Bool</span><span class=cF0> PsmBlink()
<a name="l61"></a>{
<a name="l62"></a>    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>Blink</span><span class=cF0> || psm.playing)
<a name="l63"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l64"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l65"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l66"></a>}
<a name="l67"></a>
<a name="l68"></a></span><span class=cF1>Bool</span><span class=cF0> PsmHasWords(</span><span class=cF1>U8</span><span class=cF0> *st)
<a name="l69"></a>{
<a name="l70"></a>    </span><span class=cF1>if</span><span class=cF0> (st &amp;&amp; *st &amp;&amp; </span><span class=cF7>(</span><span class=cF5>StrLen</span><span class=cF0>(st) &gt; </span><span class=cFE>1</span><span class=cF0> || *st != </span><span class=cF3>CH_SPACE</span><span class=cF7>)</span><span class=cF0>)
<a name="l71"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l72"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l73"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l74"></a>}
<a name="l75"></a>
<a name="l76"></a></span><span class=cF1>Bool</span><span class=cF0> PsmIsDotted(</span><span class=cF9>I64</span><span class=cF0> duration)
<a name="l77"></a>{
<a name="l78"></a>    </span><span class=cF1>U8</span><span class=cF0> *st = </span><span class=cF5>ListSub</span><span class=cF0>(duration, psm_duration_list);
<a name="l79"></a>
<a name="l80"></a>    </span><span class=cF1>if</span><span class=cF0> (st[</span><span class=cFE>1</span><span class=cF0>] == </span><span class=cF6>'.'</span><span class=cF0>)
<a name="l81"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l82"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l83"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l84"></a>}
<a name="l85"></a>
<a name="l86"></a></span><span class=cF1>U0</span><span class=cF0> PsmMarkSel(</span><span class=cF9>I64</span><span class=cF0> x1, </span><span class=cF9>I64</span><span class=cF0> x2, </span><span class=cF1>Bool</span><span class=cF0> sel)
<a name="l87"></a>{
<a name="l88"></a>    PsmNote *tmpn = psm.head.next;
<a name="l89"></a>
<a name="l90"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpn != &amp;psm.head)
<a name="l91"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l92"></a>        </span><span class=cF1>if</span><span class=cF0> (sel)
<a name="l93"></a>        {
<a name="l94"></a>            </span><span class=cF1>if</span><span class=cF0> (x1 &lt;= tmpn-&gt;x &lt;= x2)
<a name="l95"></a>                tmpn-&gt;flags |= PSMF_SEL;
<a name="l96"></a>        }
<a name="l97"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l98"></a>            tmpn-&gt;flags &amp;= ~PSMF_SEL;
<a name="l99"></a>        tmpn = tmpn-&gt;next;
<a name="l100"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l101"></a>}
<a name="l102"></a>
<a name="l103"></a></span><span class=cF1>U0</span><span class=cF0> PsmSetWidth(PsmNote *tmpn)
<a name="l104"></a>{
<a name="l105"></a>    </span><span class=cF1>if</span><span class=cF0> (tmpn-&gt;type == PSMT_METER)
<a name="l106"></a>        tmpn-&gt;width = </span><span class=cFE>12</span><span class=cF0>;
<a name="l107"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l108"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l109"></a>        tmpn-&gt;width = PSM_NOTE_SPACING;
<a name="l110"></a>        </span><span class=cF1>if</span><span class=cF0> (PsmIsDotted</span><span class=cF7>(</span><span class=cF0>tmpn-&gt;duration</span><span class=cF7>)</span><span class=cF0>)
<a name="l111"></a>            tmpn-&gt;width += PSM_NOTE_SPACING / </span><span class=cFE>2</span><span class=cF0>;
<a name="l112"></a>        </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>Bt</span><span class=cF7>(</span><span class=cF0>&amp;tmpn-&gt;flags, PSMf_SHARP</span><span class=cF7>)</span><span class=cF0> || </span><span class=cF5>Bt</span><span class=cF7>(</span><span class=cF0>&amp;tmpn-&gt;flags, PSMf_FLAT</span><span class=cF7>)</span><span class=cF0>)
<a name="l113"></a>            tmpn-&gt;width += PSM_NOTE_SPACING;
<a name="l114"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l115"></a>}
<a name="l116"></a>
<a name="l117"></a></span><span class=cF1>U0</span><span class=cF0> PsmSetOctave(</span><span class=cF9>I64</span><span class=cF0> octave)
<a name="l118"></a>{
<a name="l119"></a>    </span><span class=cF9>I64</span><span class=cF0>          i;
<a name="l120"></a>    </span><span class=cF1>U8</span><span class=cF0>           buf[</span><span class=cF3>STR_LEN</span><span class=cF0>];
<a name="l121"></a>    </span><span class=cF9>CMenuEntry</span><span class=cF0>  *tmpse;
<a name="l122"></a>
<a name="l123"></a>    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>1</span><span class=cF0>; i &lt;= </span><span class=cFE>7</span><span class=cF0>; i++)
<a name="l124"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l125"></a>        </span><span class=cF5>StrPrint</span><span class=cF0>(buf, </span><span class=cF6>&quot;Sound/Octave%d&quot;</span><span class=cF0>, i);
<a name="l126"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpse = </span><span class=cF5>MenuEntryFind</span><span class=cF7>(</span><span class=cF5>Fs</span><span class=cF0>-&gt;cur_menu, buf</span><span class=cF7>)</span><span class=cF0>)
<a name="l127"></a>        {
<a name="l128"></a>            </span><span class=cF1>if</span><span class=cF0> (i == octave)
<a name="l129"></a>                tmpse-&gt;checked = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l130"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l131"></a>                tmpse-&gt;checked = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l132"></a>        }
<a name="l133"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l134"></a>}
<a name="l135"></a>
<a name="l136"></a></span><span class=cF1>U0</span><span class=cF0> DrawNote(</span><span class=cF9>CDC</span><span class=cF0> *dc, </span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y, </span><span class=cF9>I64</span><span class=cF0> duration)
<a name="l137"></a>{
<a name="l138"></a>    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cFE>0</span><span class=cF0> &lt;= duration &lt;= PSM_DURATIONS_NUM)
<a name="l139"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l140"></a>        </span><span class=cF5>Sprite3</span><span class=cF0>(dc, x, y, </span><span class=cFE>0</span><span class=cF0>, psm_duration_imgs[duration]);
<a name="l141"></a>        </span><span class=cF1>if</span><span class=cF0> (psm_triplet_durations[duration])
<a name="l142"></a>            </span><span class=cF5>Sprite3</span><span class=cF0>(dc, x, y, </span><span class=cFE>0</span><span class=cF0>, </span><span class=cFA>&lt;16&gt;</span><span class=cF0>);
<a name="l143"></a>        </span><span class=cF1>if</span><span class=cF0> (PsmIsDotted</span><span class=cF7>(</span><span class=cF0>duration</span><span class=cF7>)</span><span class=cF0>)
<a name="l144"></a>            </span><span class=cF5>Sprite3</span><span class=cF0>(dc, x, y, </span><span class=cFE>0</span><span class=cF0>, </span><span class=cFA>&lt;15&gt;</span><span class=cF0>);
<a name="l145"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l146"></a>}
<a name="l147"></a>
<a name="l148"></a></span><span class=cF1>U0</span><span class=cF0> DrawTimeSignature(</span><span class=cF9>CDC</span><span class=cF0> *dc, </span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y, </span><span class=cF9>I64</span><span class=cF0> top, </span><span class=cF9>I64</span><span class=cF0> bottom)
<a name="l149"></a>{
<a name="l150"></a>    </span><span class=cF5>GrPrint</span><span class=cF0>(dc, x, y, </span><span class=cF6>&quot;%d&quot;</span><span class=cF0>, top);
<a name="l151"></a>    </span><span class=cF5>GrPrint</span><span class=cF0>(dc, x, y + </span><span class=cF3>FONT_HEIGHT</span><span class=cF0>, </span><span class=cF6>&quot;%d&quot;</span><span class=cF0>, bottom);
<a name="l152"></a>}
<a name="l153"></a>
<a name="l154"></a></span><span class=cF1>U0</span><span class=cF0> PsmRecalcNoteXY()
<a name="l155"></a>{
<a name="l156"></a>    </span><span class=cF1>F64</span><span class=cF0>      measure_len = </span><span class=cFE>4</span><span class=cF0>, measure_left = measure_len;
<a name="l157"></a>    PsmNote *tmpn = psm.head.next;
<a name="l158"></a>    </span><span class=cF9>I64</span><span class=cF0>      x = </span><span class=cFE>8</span><span class=cF0> - psm.screen_x, ona, note, octave;
<a name="l159"></a>
<a name="l160"></a>    </span><span class=cF1>while</span><span class=cF0> (</span><span class=cF3>TRUE</span><span class=cF0>)
<a name="l161"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l162"></a>        tmpn-&gt;x = x;
<a name="l163"></a>        tmpn-&gt;y = </span><span class=cFE>50</span><span class=cF0>;
<a name="l164"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpn == &amp;psm.head)
<a name="l165"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l166"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l167"></a>        {
<a name="l168"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpn-&gt;type != PSMT_METER)
<a name="l169"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l170"></a>                </span><span class=cF1>if</span><span class=cF0> (tmpn-&gt;ona)
<a name="l171"></a>                {
<a name="l172"></a>                    ona = tmpn-&gt;ona;
<a name="l173"></a>                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>Bt</span><span class=cF7>(</span><span class=cF0>&amp;tmpn-&gt;flags, PSMf_SHARP</span><span class=cF7>)</span><span class=cF0>)
<a name="l174"></a>                        ona--;
<a name="l175"></a>                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>Bt</span><span class=cF7>(</span><span class=cF0>&amp;tmpn-&gt;flags, PSMf_FLAT</span><span class=cF7>)</span><span class=cF0>)
<a name="l176"></a>                        ona++;
<a name="l177"></a>                    octave  = </span><span class=cF5>Ona2Octave</span><span class=cF0>(ona);
<a name="l178"></a>                    note    = </span><span class=cF5>Ona2Note</span><span class=cF0>  (ona);
<a name="l179"></a>                    note = </span><span class=cFB>music</span><span class=cF0>.note_map[*</span><span class=cF5>ListSub</span><span class=cF0>(note, psm_note_list) - </span><span class=cF6>'A'</span><span class=cF0>];
<a name="l180"></a>                    </span><span class=cF1>if</span><span class=cF0> (note &lt; </span><span class=cFE>3</span><span class=cF0>)
<a name="l181"></a>                        octave++;
<a name="l182"></a>                    tmpn-&gt;y = (</span><span class=cFE>15</span><span class=cF0> + </span><span class=cF7>(</span><span class=cF0>psm_note_map[note] - </span><span class=cFE>7</span><span class=cF0> * (octave - </span><span class=cFE>4</span><span class=cF0>)</span><span class=cF7>)</span><span class=cF0>) * </span><span class=cFE>4</span><span class=cF0>;
<a name="l183"></a>                }
<a name="l184"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l185"></a>            x += tmpn-&gt;width;
<a name="l186"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpn-&gt;type == PSMT_METER)
<a name="l187"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l188"></a>                measure_len = tmpn-&gt;meter_top * </span><span class=cFE>4</span><span class=cF0>.</span><span class=cFE>0</span><span class=cF0> / tmpn-&gt;meter_bottom;
<a name="l189"></a>                measure_left = </span><span class=cFE>0</span><span class=cF0>;
<a name="l190"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l191"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l192"></a>                measure_left -= psm_durations[tmpn-&gt;duration];
<a name="l193"></a>            </span><span class=cF1>if</span><span class=cF0> (measure_left &lt; </span><span class=cFE>0</span><span class=cF0>.</span><span class=cFE>001</span><span class=cF0>)
<a name="l194"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l195"></a>                x += PSM_NOTE_SPACING;
<a name="l196"></a>                measure_left = measure_len;
<a name="l197"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l198"></a>        }
<a name="l199"></a>        tmpn = tmpn-&gt;next;
<a name="l200"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l201"></a>}
<a name="l202"></a>
<a name="l203"></a></span><span class=cF1>U0</span><span class=cF0> </span><span class=cF5>DrawIt</span><span class=cF0>(</span><span class=cF9>CTask</span><span class=cF0> *task, </span><span class=cF9>CDC</span><span class=cF0> *dc)
<a name="l204"></a>{
<a name="l205"></a>    PsmNote *tmpn;
<a name="l206"></a>    </span><span class=cF9>I64</span><span class=cF0>      i, x, y, 
<a name="l207"></a>             w = task-&gt;pix_width;
<a name="l208"></a>    </span><span class=cF1>F64</span><span class=cF0>      measure_len = </span><span class=cFE>4</span><span class=cF0>, measure_left = measure_len;
<a name="l209"></a>
<a name="l210"></a>    dc-&gt;color = </span><span class=cF3>BLACK</span><span class=cF0>;
<a name="l211"></a>    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>1</span><span class=cF0>; i &lt; </span><span class=cFE>6</span><span class=cF0>; i++)
<a name="l212"></a>        </span><span class=cF5>GrLine</span><span class=cF0>(dc, </span><span class=cFE>0</span><span class=cF0>, i * </span><span class=cFE>8</span><span class=cF0>, w, i * </span><span class=cFE>8</span><span class=cF0>);
<a name="l213"></a>    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>7</span><span class=cF0>; i &lt; </span><span class=cFE>12</span><span class=cF0>; i++)
<a name="l214"></a>        </span><span class=cF5>GrLine</span><span class=cF0>(dc, </span><span class=cFE>0</span><span class=cF0>, i * </span><span class=cFE>8</span><span class=cF0>, w, i * </span><span class=cFE>8</span><span class=cF0>);
<a name="l215"></a>
<a name="l216"></a>    PsmRecalcNoteXY;
<a name="l217"></a>    </span><span class=cF1>if</span><span class=cF0> (psm.cur_note-&gt;x &lt; </span><span class=cFE>64</span><span class=cF0>)
<a name="l218"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l219"></a>        psm.screen_x -= </span><span class=cFE>128</span><span class=cF0>;
<a name="l220"></a>        PsmRecalcNoteXY;
<a name="l221"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l222"></a>    </span><span class=cF1>if</span><span class=cF0> (psm.cur_note-&gt;x &gt;= </span><span class=cF3>GR_WIDTH</span><span class=cF0> - </span><span class=cFE>64</span><span class=cF0>)
<a name="l223"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l224"></a>        psm.screen_x += </span><span class=cFE>128</span><span class=cF0>;
<a name="l225"></a>        PsmRecalcNoteXY;
<a name="l226"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l227"></a>
<a name="l228"></a>    tmpn = psm.head.next;
<a name="l229"></a>    </span><span class=cF1>while</span><span class=cF0> (tmpn != &amp;psm.head)
<a name="l230"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l231"></a>        x = tmpn-&gt;x;
<a name="l232"></a>        y = tmpn-&gt;y;
<a name="l233"></a>        </span><span class=cF1>if</span><span class=cF0> (measure_left &lt; </span><span class=cFE>0</span><span class=cF0>.</span><span class=cFE>001</span><span class=cF0>)
<a name="l234"></a>        {
<a name="l235"></a>            dc-&gt;color = </span><span class=cF3>BLACK</span><span class=cF0>;
<a name="l236"></a>            </span><span class=cF5>GrLine</span><span class=cF0>(dc, x - PSM_NOTE_SPACING, </span><span class=cFE>8</span><span class=cF0>, x - PSM_NOTE_SPACING, </span><span class=cFE>11</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0>);
<a name="l237"></a>            measure_left = measure_len;
<a name="l238"></a>        }
<a name="l239"></a>        </span><span class=cF1>if</span><span class=cF0> (tmpn-&gt;type == PSMT_METER)
<a name="l240"></a>        {
<a name="l241"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpn == psm.cur_note &amp;&amp; PsmBlink)
<a name="l242"></a>                dc-&gt;color = </span><span class=cF3>BROWN</span><span class=cF0>;
<a name="l243"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l244"></a>                dc-&gt;color = </span><span class=cF3>BLACK</span><span class=cF0>;
<a name="l245"></a>            DrawTimeSignature(dc, x, </span><span class=cFE>5</span><span class=cF0> * </span><span class=cFE>8</span><span class=cF0>, tmpn-&gt;meter_top, tmpn-&gt;meter_bottom);
<a name="l246"></a>            measure_len = tmpn-&gt;meter_top * </span><span class=cFE>4</span><span class=cF0>.</span><span class=cFE>0</span><span class=cF0> / tmpn-&gt;meter_bottom;
<a name="l247"></a>            measure_left = </span><span class=cFE>0</span><span class=cF0>;
<a name="l248"></a>        }
<a name="l249"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l250"></a>        {
<a name="l251"></a>            </span><span class=cF1>if</span><span class=cF0> (tmpn == psm.cur_note &amp;&amp; PsmBlink)
<a name="l252"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l253"></a>                dc-&gt;color = </span><span class=cF3>BROWN</span><span class=cF0>;
<a name="l254"></a>                </span><span class=cF5>GrPrint</span><span class=cF0>(dc, x + </span><span class=cFE>8</span><span class=cF0>, y, </span><span class=cF6>&quot;%s&quot;</span><span class=cF0>, tmpn-&gt;word);
<a name="l255"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l256"></a>            </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (tmpn-&gt;flags &amp; PSMF_SEL)
<a name="l257"></a>                dc-&gt;color = </span><span class=cF3>RED</span><span class=cF0>;
<a name="l258"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l259"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l260"></a>                </span><span class=cF1>if</span><span class=cF0> (tmpn-&gt;ona)
<a name="l261"></a>                    dc-&gt;color = </span><span class=cF3>BLACK</span><span class=cF0>;
<a name="l262"></a>                </span><span class=cF1>else</span><span class=cF0>
<a name="l263"></a>                    dc-&gt;color = </span><span class=cF3>LTGRAY</span><span class=cF0>;
<a name="l264"></a>                </span><span class=cF1>if</span><span class=cF0> (PsmHasWords</span><span class=cF7>(</span><span class=cF0>tmpn-&gt;word</span><span class=cF7>)</span><span class=cF0>)
<a name="l265"></a>                    dc-&gt;color = </span><span class=cF3>GREEN</span><span class=cF0>;
<a name="l266"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l267"></a>            DrawNote(dc, x, y, tmpn-&gt;duration);
<a name="l268"></a>            </span><span class=cF1>if</span><span class=cF0> (PsmIsDotted</span><span class=cF7>(</span><span class=cF0>tmpn-&gt;duration</span><span class=cF7>)</span><span class=cF0>)
<a name="l269"></a>                x += PSM_NOTE_SPACING/</span><span class=cFE>2</span><span class=cF0>;
<a name="l270"></a>            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>Bt</span><span class=cF7>(</span><span class=cF0>&amp;tmpn-&gt;flags, PSMf_SHARP</span><span class=cF7>)</span><span class=cF0>)
<a name="l271"></a>                </span><span class=cF5>Sprite3</span><span class=cF0>(dc, x, y, </span><span class=cFE>0</span><span class=cF0>, </span><span class=cFA>&lt;13&gt;</span><span class=cF0>);
<a name="l272"></a>            </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>Bt</span><span class=cF7>(</span><span class=cF0>&amp;tmpn-&gt;flags, PSMf_FLAT</span><span class=cF7>)</span><span class=cF0>)
<a name="l273"></a>                </span><span class=cF5>Sprite3</span><span class=cF0>(dc, x, y, </span><span class=cFE>0</span><span class=cF0>, </span><span class=cFA>&lt;14&gt;</span><span class=cF0>);
<a name="l274"></a>            measure_left -= psm_durations[tmpn-&gt;duration];
<a name="l275"></a>        }
<a name="l276"></a>        tmpn = tmpn-&gt;next;
<a name="l277"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l278"></a>
<a name="l279"></a>    </span><span class=cF1>if</span><span class=cF0> (psm.cur_note == &amp;psm.head &amp;&amp; PsmBlink)
<a name="l280"></a>        dc-&gt;color = </span><span class=cF3>BROWN</span><span class=cF0>;
<a name="l281"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l282"></a>        dc-&gt;color = </span><span class=cF3>BLACK</span><span class=cF0>;
<a name="l283"></a>    </span><span class=cF5>Sprite3</span><span class=cF0>(dc, psm.head.x, </span><span class=cFE>50</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>, </span><span class=cFA>&lt;12&gt;</span><span class=cF0>);
<a name="l284"></a>}
<a name="l285"></a>
<a name="l286"></a>#</span><span class=cF1>define</span><span class=cF0> PSM_NOTE_BOX_X  </span><span class=cFE>220</span><span class=cF0>
<a name="l287"></a>#</span><span class=cF1>define</span><span class=cF0> PSM_NOTE_BOX_Y  (</span><span class=cFE>13</span><span class=cF0> * </span><span class=cF3>FONT_HEIGHT</span><span class=cF0> + </span><span class=cFE>14</span><span class=cF0>)
<a name="l288"></a></span><span class=cF1>U0</span><span class=cF0> PsmSetPickNoteBoxX(</span><span class=cF9>I64</span><span class=cF0> duration, </span><span class=cF9>I64</span><span class=cF0> *x)
<a name="l289"></a>{
<a name="l290"></a>    </span><span class=cF9>I64</span><span class=cF0> i;
<a name="l291"></a>
<a name="l292"></a>    *x = PSM_NOTE_BOX_X;
<a name="l293"></a>    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; duration; i++)
<a name="l294"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l295"></a>        </span><span class=cF1>if</span><span class=cF0> (PsmIsDotted</span><span class=cF7>(</span><span class=cF0>i</span><span class=cF7>)</span><span class=cF0>)
<a name="l296"></a>            *x += PSM_NOTE_SPACING / </span><span class=cFE>2</span><span class=cF0>;
<a name="l297"></a>        *x += PSM_NOTE_SPACING + </span><span class=cFE>4</span><span class=cF0>;
<a name="l298"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l299"></a>}
<a name="l300"></a>
<a name="l301"></a></span><span class=cF9>I64</span><span class=cF0> PsmGetPickNoteBoxDuration(</span><span class=cF9>I64</span><span class=cF0> xx, </span><span class=cF9>I64</span><span class=cF0> yy)
<a name="l302"></a>{
<a name="l303"></a>    </span><span class=cF9>I64</span><span class=cF0> i, x1, x2;
<a name="l304"></a>
<a name="l305"></a>    </span><span class=cF1>if</span><span class=cF0> (PSM_NOTE_BOX_Y  -</span><span class=cFE>14</span><span class=cF0> &lt;= yy &lt; PSM_NOTE_BOX_Y + </span><span class=cFE>6</span><span class=cF0>)
<a name="l306"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l307"></a>        </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; PSM_DURATIONS_NUM; i++)
<a name="l308"></a>        {
<a name="l309"></a>            PsmSetPickNoteBoxX(i, &amp;x1);
<a name="l310"></a>            PsmSetPickNoteBoxX(i + </span><span class=cFE>1</span><span class=cF0>, &amp; x2);
<a name="l311"></a>            </span><span class=cF1>if</span><span class=cF0> (x1 &lt;= xx + PSM_NOTE_SPACING / </span><span class=cFE>2</span><span class=cF0> &lt; x2)
<a name="l312"></a>                </span><span class=cF1>return</span><span class=cF0> i;
<a name="l313"></a>        }
<a name="l314"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l315"></a>
<a name="l316"></a>    </span><span class=cF1>return</span><span class=cF0> -</span><span class=cFE>1</span><span class=cF0>;
<a name="l317"></a>}
<a name="l318"></a>
<a name="l319"></a></span><span class=cF1>U0</span><span class=cF0> DrawPickNoteBox()
<a name="l320"></a>{
<a name="l321"></a>    </span><span class=cF9>I64</span><span class=cF0> i, x;
<a name="l322"></a>
<a name="l323"></a>    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; PSM_DURATIONS_NUM; i++)
<a name="l324"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l325"></a>        PsmSetPickNoteBoxX(i, &amp;x);
<a name="l326"></a>        </span><span class=cF1>if</span><span class=cF0> (PsmIsDotted</span><span class=cF7>(</span><span class=cF0>i</span><span class=cF7>)</span><span class=cF0>)
<a name="l327"></a>            psm.dc2-&gt;color = </span><span class=cF3>RED</span><span class=cF0>;
<a name="l328"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (psm_triplet_durations[i])
<a name="l329"></a>            psm.dc2-&gt;color = </span><span class=cF3>LTRED</span><span class=cF0>;
<a name="l330"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l331"></a>            psm.dc2-&gt;color = </span><span class=cF3>BLACK</span><span class=cF0>;
<a name="l332"></a>        DrawNote(psm.dc2, x, PSM_NOTE_BOX_Y, i);
<a name="l333"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l334"></a>}
<a name="l335"></a>
<a name="l336"></a>#</span><span class=cF1>define</span><span class=cF0> PSM_TOOLS_X     </span><span class=cFE>450</span><span class=cF0>
<a name="l337"></a>#</span><span class=cF1>define</span><span class=cF0> PSM_TOOLS_Y     </span><span class=cFE>13</span><span class=cF0> * </span><span class=cF3>FONT_HEIGHT</span><span class=cF0>
<a name="l338"></a>
<a name="l339"></a></span><span class=cF1>U0</span><span class=cF0> DrawPickTools()
<a name="l340"></a>{
<a name="l341"></a>    </span><span class=cF1>if</span><span class=cF0> (psm.tool == PSMTT_BOX_TOOL)
<a name="l342"></a>        psm.dc2-&gt;color = </span><span class=cF3>ROPF_DITHER</span><span class=cF0> + </span><span class=cF3>WHITE</span><span class=cF0> &lt;&lt; </span><span class=cFE>16</span><span class=cF0> + </span><span class=cF3>RED</span><span class=cF0>;
<a name="l343"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l344"></a>        psm.dc2-&gt;color = </span><span class=cF3>ROPF_DITHER</span><span class=cF0> + </span><span class=cF3>WHITE</span><span class=cF0> &lt;&lt; </span><span class=cFE>16</span><span class=cF0> + </span><span class=cF3>BLACK</span><span class=cF0>;
<a name="l345"></a>    </span><span class=cF5>GrBorder</span><span class=cF0>(psm.dc2, PSM_TOOLS_X, PSM_TOOLS_Y, PSM_TOOLS_X + </span><span class=cFE>10</span><span class=cF0>, PSM_TOOLS_Y + </span><span class=cFE>10</span><span class=cF0>);
<a name="l346"></a>
<a name="l347"></a>    </span><span class=cF1>if</span><span class=cF0> (psm.tool == PSMTT_PTR_TOOL)
<a name="l348"></a>        psm.dc2-&gt;color = </span><span class=cF3>RED</span><span class=cF0>;
<a name="l349"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l350"></a>        psm.dc2-&gt;color = </span><span class=cF3>BLACK</span><span class=cF0>;
<a name="l351"></a>    (*</span><span class=cFB>gr</span><span class=cF0>.fp_draw_mouse)(psm.dc2, PSM_TOOLS_X + </span><span class=cFE>15</span><span class=cF0>, PSM_TOOLS_Y);
<a name="l352"></a>    psm.dc2-&gt;color = </span><span class=cF3>BLACK</span><span class=cF0>;
<a name="l353"></a>}
<a name="l354"></a>
<a name="l355"></a></span><span class=cF1>Bool</span><span class=cF0> PsmGetPickToolBox(</span><span class=cF9>I64</span><span class=cF0> xx, </span><span class=cF9>I64</span><span class=cF0> yy)
<a name="l356"></a>{
<a name="l357"></a>    </span><span class=cF1>if</span><span class=cF0> (PSM_TOOLS_X &lt;= xx &lt; PSM_TOOLS_X + </span><span class=cFE>27</span><span class=cF0> &amp;&amp; PSM_TOOLS_Y &lt;= yy &lt; PSM_TOOLS_Y + </span><span class=cFE>15</span><span class=cF0>)
<a name="l358"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l359"></a>        PsmMarkSel(</span><span class=cFE>0</span><span class=cF0>, </span><span class=cFE>0</span><span class=cF0>, </span><span class=cF3>FALSE</span><span class=cF0>);
<a name="l360"></a>        </span><span class=cF1>if</span><span class=cF0> (xx &lt; PSM_TOOLS_X + </span><span class=cFE>13</span><span class=cF0>)
<a name="l361"></a>            psm.tool = PSMTT_BOX_TOOL;
<a name="l362"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l363"></a>            psm.tool = PSMTT_PTR_TOOL;
<a name="l364"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l365"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l366"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l367"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l368"></a>}
<a name="l369"></a>
<a name="l370"></a>#</span><span class=cF1>define</span><span class=cF0> PSM_METERS_NUM  </span><span class=cFE>7</span><span class=cF0>
<a name="l371"></a></span><span class=cF9>I64</span><span class=cF0> meter_tops[PSM_METERS_NUM]      = {</span><span class=cFE>2</span><span class=cF0>, </span><span class=cFE>3</span><span class=cF0>, </span><span class=cFE>4</span><span class=cF0>, </span><span class=cFE>5</span><span class=cF0>, </span><span class=cFE>6</span><span class=cF0>, </span><span class=cFE>7</span><span class=cF0>, </span><span class=cFE>9</span><span class=cF0>}, 
<a name="l372"></a>    meter_bottoms[PSM_METERS_NUM]   = {</span><span class=cFE>4</span><span class=cF0>, </span><span class=cFE>4</span><span class=cF0>, </span><span class=cFE>4</span><span class=cF0>, </span><span class=cFE>4</span><span class=cF0>, </span><span class=cFE>8</span><span class=cF0>, </span><span class=cFE>8</span><span class=cF0>, </span><span class=cFE>8</span><span class=cF0>};
<a name="l373"></a>
<a name="l374"></a>#</span><span class=cF1>define</span><span class=cF0> PSM_METER_X         </span><span class=cFE>485</span><span class=cF0>
<a name="l375"></a>#</span><span class=cF1>define</span><span class=cF0> PSM_METER_Y         </span><span class=cFE>13</span><span class=cF0> * </span><span class=cF3>FONT_HEIGHT</span><span class=cF0>
<a name="l376"></a>#</span><span class=cF1>define</span><span class=cF0> PSM_METER_W         </span><span class=cFE>12</span><span class=cF0>
<a name="l377"></a></span><span class=cF1>Bool</span><span class=cF0> PsmGetPickMeterBox(</span><span class=cF9>I64</span><span class=cF0> xx, </span><span class=cF9>I64</span><span class=cF0> yy, </span><span class=cF9>I64</span><span class=cF0> *top, </span><span class=cF9>I64</span><span class=cF0> *bottom)
<a name="l378"></a>{
<a name="l379"></a>    </span><span class=cF9>I64</span><span class=cF0> i;
<a name="l380"></a>
<a name="l381"></a>    </span><span class=cF1>if</span><span class=cF0> (PSM_METER_X &lt;= xx &lt; PSM_METER_X + PSM_METER_W * PSM_METERS_NUM &amp;&amp;
<a name="l382"></a>        PSM_METER_Y &lt;= yy &lt; PSM_METER_Y + </span><span class=cFE>2</span><span class=cF0> * </span><span class=cF3>FONT_HEIGHT</span><span class=cF0>)
<a name="l383"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l384"></a>        i = (xx - PSM_METER_X) / PSM_METER_W;
<a name="l385"></a>        *top = meter_tops[i];
<a name="l386"></a>        *bottom = meter_bottoms[i];
<a name="l387"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l388"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l389"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l390"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l391"></a>}
<a name="l392"></a>
<a name="l393"></a></span><span class=cF1>U0</span><span class=cF0> DrawPickMeterBox()
<a name="l394"></a>{
<a name="l395"></a>    </span><span class=cF9>I64</span><span class=cF0> i;
<a name="l396"></a>
<a name="l397"></a>    psm.dc2-&gt;color = </span><span class=cF3>BLACK</span><span class=cF0>;
<a name="l398"></a>    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; PSM_METERS_NUM; i++)
<a name="l399"></a>        DrawTimeSignature(psm.dc2, PSM_METER_X + i * PSM_METER_W, PSM_METER_Y, meter_tops[i], meter_bottoms[i]);
<a name="l400"></a>}
<a name="l401"></a>
<a name="l402"></a></span><span class=cF1>U0</span><span class=cF0> DrawDC2()
<a name="l403"></a>{
<a name="l404"></a>    </span><span class=cF5>DCFill</span><span class=cF0>;
<a name="l405"></a>    DrawPickNoteBox;
<a name="l406"></a>    DrawPickMeterBox;
<a name="l407"></a>    DrawPickTools;
<a name="l408"></a>}
<a name="l409"></a>
<a name="l410"></a></span><span class=cFA>
<a name="l411"></a>&lt;17&gt;/* Graphics Not Rendered in HTML */</span><span class=cF0>
<a name="l412"></a> 
<a name="l413"></a>
<a name="l414"></a>
<a name="l415"></a>
<a name="l416"></a>
<a name="l417"></a></span><span class=cF1>U0</span><span class=cF0> PsmMenu(</span><span class=cF9>I64</span><span class=cF0> psm_octave)
<a name="l418"></a>{
<a name="l419"></a>    </span><span class=cF5>DocClear</span><span class=cF0>;
<a name="l420"></a>    </span><span class=cF6>&quot;$BG,WHITE$$FD,GREEN$$CM,0,12$\n&quot;</span><span class=cF0>;
<a name="l421"></a>    </span><span class=cF5>Sprite</span><span class=cF0>(</span><span class=cFA>&lt;17&gt;</span><span class=cF0>);
<a name="l422"></a>    </span><span class=cF6>'\n\n\n\n\n'</span><span class=cF0>;
<a name="l423"></a>
<a name="l424"></a>    DrawDC2;
<a name="l425"></a>
<a name="l426"></a>    </span><span class=cF6>&quot;$LTGREEN$&lt;SPACE&gt;$FG$\t\tRest\n&quot;</span><span class=cF0>
<a name="l427"></a>    </span><span class=cF6>&quot;$LTGREEN$&lt;BACKSPACE&gt;$FG$\tDeletes Last Note\n&quot;</span><span class=cF0>
<a name="l428"></a>    </span><span class=cF6>&quot;$LTGREEN$Left Mouse$FG$\tDrag note or shift word\n&quot;</span><span class=cF0>
<a name="l429"></a>    </span><span class=cF6>&quot;$LTGREEN$Right Mouse$FG$\tChange duration or set word\n&quot;</span><span class=cF0>;
<a name="l430"></a>    </span><span class=cF5>Sprite</span><span class=cF0>(</span><span class=cFA>&lt;6&gt;</span><span class=cF0>, </span><span class=cF6>&quot;$SP+LIS,\&quot;\&quot;,&quot;</span><span class=cF0>
<a name="l431"></a>                </span><span class=cF6>&quot;LM=\&quot;Message(MESSAGE_KEY_DOWN,0,SCF_CTRL|SC_CURSOR_LEFT);\&quot;,BI=%d$&quot;</span><span class=cF0>);
<a name="l432"></a>    </span><span class=cF6>&quot;   &quot;</span><span class=cF0>;
<a name="l433"></a>    </span><span class=cF1>if</span><span class=cF0> (psm.playing)
<a name="l434"></a>        </span><span class=cF5>Sprite</span><span class=cF0>(</span><span class=cFA>&lt;9&gt;</span><span class=cF0>, </span><span class=cF6>&quot;$SP,\&quot;\&quot;,LM=\&quot;x\&quot;,BI=%d$&quot;</span><span class=cF0>);
<a name="l435"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l436"></a>        </span><span class=cF5>Sprite</span><span class=cF0>(</span><span class=cFA>&lt;8&gt;</span><span class=cF0>, </span><span class=cF6>&quot;$SP,\&quot;\&quot;,LM=\&quot;x\&quot;,BI=%d$&quot;</span><span class=cF0>);
<a name="l437"></a>    </span><span class=cF6>&quot;   &quot;</span><span class=cF0>;
<a name="l438"></a>    </span><span class=cF1>if</span><span class=cF0> (psm.record_entry-&gt;checked)
<a name="l439"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l440"></a>        psm.record_entry-&gt;checked = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l441"></a>        </span><span class=cF5>Sprite</span><span class=cF0>(</span><span class=cFA>&lt;10&gt;</span><span class=cF0>, </span><span class=cF6>&quot;$SP,\&quot;\&quot;,LM=\&quot;z\&quot;,BI=%d$&quot;</span><span class=cF0>);
<a name="l442"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l443"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l444"></a>        </span><span class=cF5>Sprite</span><span class=cF0>(</span><span class=cFA>&lt;11&gt;</span><span class=cF0>, </span><span class=cF6>&quot;$SP,\&quot;\&quot;,LM=\&quot;z\&quot;,BI=%d$&quot;</span><span class=cF0>);
<a name="l445"></a>    </span><span class=cF6>&quot;   &quot;</span><span class=cF0>;
<a name="l446"></a>    </span><span class=cF5>Sprite</span><span class=cF0>(</span><span class=cFA>&lt;7&gt;</span><span class=cF0>, </span><span class=cF6>&quot;$SP+LIS,\&quot;\&quot;,&quot;</span><span class=cF0>
<a name="l447"></a>                </span><span class=cF6>&quot;LM=\&quot;Message(MESSAGE_KEY_DOWN,0,SCF_CTRL|SC_CURSOR_RIGHT);\&quot;,BI=%d$&quot;</span><span class=cF0>);
<a name="l448"></a>    </span><span class=cF6>&quot;$CM+LX,0,6$&quot;</span><span class=cF0>;
<a name="l449"></a>    PsmSetOctave(psm_octave);
<a name="l450"></a>    </span><span class=cF5>Refresh</span><span class=cF0>(</span><span class=cFE>2</span><span class=cF0>);
<a name="l451"></a>}
</span></pre></body>
</html>
