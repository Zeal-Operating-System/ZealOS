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
<a name="l3"></a></span><span class=cF5>Option</span><span class=cF0>(</span><span class=cF3>OPTf_WARN_HEADER_MISMATCH</span><span class=cF0>, </span><span class=cF3>OFF</span><span class=cF0>);
<a name="l4"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF1>Bool</span><span class=cF0> </span><span class=cF5>GrPlot0</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc=</span><span class=cFB>gr</span><span class=cF0>.dc, </span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y)
<a name="l5"></a>{</span><span class=cF2>//2D. No clipping or transformation or thick.</span><span class=cF0>
<a name="l6"></a>    </span><span class=cF1>U8</span><span class=cF0>              *dst;
<a name="l7"></a>    </span><span class=cF9>I32</span><span class=cF0>             *db;
<a name="l8"></a>    </span><span class=cF9>I64</span><span class=cF0>              d, dist;
<a name="l9"></a>    </span><span class=cF9>CColorROPU32</span><span class=cF0>     c, color = dc-&gt;color, bkcolor = dc-&gt;bkcolor;
<a name="l10"></a>    </span><span class=cF1>Bool</span><span class=cF0>             was_timer_rand = </span><span class=cF5>Bts</span><span class=cF0>(&amp;</span><span class=cF5>Fs</span><span class=cF0>-&gt;task_flags, </span><span class=cF3>TASKf_NONTIMER_RAND</span><span class=cF0>);
<a name="l11"></a>
<a name="l12"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_LOCATE_NEAREST</span><span class=cF0>)
<a name="l13"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l14"></a>        dist = </span><span class=cF5>DistSqrI64</span><span class=cF0>(x, y, dc-&gt;cur_x, dc-&gt;cur_y);
<a name="l15"></a>        </span><span class=cF1>if</span><span class=cF0> (dist &lt;= dc-&gt;nearest_dist)
<a name="l16"></a>            dc-&gt;nearest_dist = dist;
<a name="l17"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l18"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_RECORD_EXTENTS</span><span class=cF0>)
<a name="l19"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l20"></a>        </span><span class=cF1>if</span><span class=cF0> (x &lt; dc-&gt;min_x)
<a name="l21"></a>            dc-&gt;min_x = x;
<a name="l22"></a>
<a name="l23"></a>        </span><span class=cF1>if</span><span class=cF0> (x &gt; dc-&gt;max_x)
<a name="l24"></a>            dc-&gt;max_x = x;
<a name="l25"></a>
<a name="l26"></a>        </span><span class=cF1>if</span><span class=cF0> (y &lt; dc-&gt;min_y)
<a name="l27"></a>            dc-&gt;min_y = y;
<a name="l28"></a>
<a name="l29"></a>        </span><span class=cF1>if</span><span class=cF0> (y &gt; dc-&gt;max_y)
<a name="l30"></a>            dc-&gt;max_y = y;
<a name="l31"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l32"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_DONT_DRAW</span><span class=cF0>)
<a name="l33"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l34"></a>    d = dc-&gt;width_internal * y + x;
<a name="l35"></a>    </span><span class=cF1>if</span><span class=cF0> (db = dc-&gt;depth_buf)
<a name="l36"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l37"></a>        db += d;
<a name="l38"></a>        </span><span class=cF1>if</span><span class=cF0> (</span><span class=cFE>0</span><span class=cF0> &lt;= dc-&gt;db_z &lt;= *db)
<a name="l39"></a>            *db = dc-&gt;db_z;
<a name="l40"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l41"></a>            </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l42"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l43"></a>    </span><span class=cF1>if</span><span class=cF0> (color.c1.rop &amp; </span><span class=cF7>(</span><span class=cF3>ROPBF_DITHER</span><span class=cF0> | </span><span class=cF3>ROPBF_PROBABILITY_DITHER</span><span class=cF7>)</span><span class=cF0>)
<a name="l44"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l45"></a>        </span><span class=cF1>if</span><span class=cF0> (color.c1.rop &amp; </span><span class=cF3>ROPBF_PROBABILITY_DITHER</span><span class=cF0>)
<a name="l46"></a>        {
<a name="l47"></a>            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>RandU16</span><span class=cF0>&lt;dc-&gt;dither_probability_u16)
<a name="l48"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l49"></a>                color.c1.rop = color.c0.rop;
<a name="l50"></a>                color.c0     = color.c1;
<a name="l51"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l52"></a>            </span><span class=cF5>BEqual</span><span class=cF0>(&amp;</span><span class=cF5>Fs</span><span class=cF0>-&gt;task_flags, </span><span class=cF3>TASKf_NONTIMER_RAND</span><span class=cF0>, was_timer_rand);
<a name="l53"></a>        }
<a name="l54"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l55"></a>        {
<a name="l56"></a>            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>x ^ y</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>1</span><span class=cF0>)
<a name="l57"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l58"></a>                color.c1.rop = color.c0.rop;
<a name="l59"></a>                color.c0     = color.c1;
<a name="l60"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l61"></a>        }
<a name="l62"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l63"></a>    dst = dc-&gt;body + d;
<a name="l64"></a>    </span><span class=cF1>switch</span><span class=cF0> [color.c0.rop]
<a name="l65"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l66"></a>        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_EQU</span><span class=cF0>:
<a name="l67"></a>        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_MONO</span><span class=cF0>:
<a name="l68"></a>            *dst = color.c0.color;
<a name="l69"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l70"></a>
<a name="l71"></a>        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_COLLISION</span><span class=cF0>:
<a name="l72"></a>            c = *dst;
<a name="l73"></a>            </span><span class=cF1>if</span><span class=cF0> (c != </span><span class=cF3>TRANSPARENT</span><span class=cF0> &amp;&amp; c != bkcolor.c0.color)
<a name="l74"></a>                dc-&gt;collision_count++;
<a name="l75"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l76"></a>
<a name="l77"></a>        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_XOR</span><span class=cF0>:
<a name="l78"></a>            *dst ^= color.c0.color;
<a name="l79"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l80"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l81"></a>
<a name="l82"></a>    </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l83"></a>}
<a name="l84"></a></span><span class=cF5>Option</span><span class=cF0>(</span><span class=cF3>OPTf_WARN_HEADER_MISMATCH</span><span class=cF0>, </span><span class=cF3>ON</span><span class=cF0>);
<a name="l85"></a>
<a name="l86"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>GrPeek0</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc=</span><span class=cFB>gr</span><span class=cF0>.dc, </span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y)
<a name="l87"></a>{</span><span class=cF2>//2D. No clipping or transformation.</span><span class=cF0>
<a name="l88"></a>    </span><span class=cF1>return</span><span class=cF0> dc-&gt;body[dc-&gt;width_internal * y + x];
<a name="l89"></a>}
<a name="l90"></a>
<a name="l91"></a>#</span><span class=cF1>help_index</span><span class=cF0> </span><span class=cF6>&quot;Graphics;Graphics/Device Contexts&quot;</span><span class=cF0>
<a name="l92"></a>
<a name="l93"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>GrBlot</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc=</span><span class=cFB>gr</span><span class=cF0>.dc, </span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y, </span><span class=cF9>CDC</span><span class=cF0> *img)
<a name="l94"></a>{</span><span class=cF2>//2D. Clipping but not transformation..</span><span class=cF0>
<a name="l95"></a>    </span><span class=cF9>I64</span><span class=cF0>              i, j, k, k1, kk, kk1, w1, h1, w2, h2, dist, 
<a name="l96"></a>                     leading_pixels, leading_pixel_mask, whole_I64s, 
<a name="l97"></a>                     trailing_pixels, trailing_pixel_mask, 
<a name="l98"></a>                </span><span class=cF1>reg</span><span class=cF0>  bit_shift, win_z_buf_line_inc, win_z_buf_line_dec, win_z_num, 
<a name="l99"></a>                     color_mask;
<a name="l100"></a>    </span><span class=cF1>U8</span><span class=cF0>          </span><span class=cF1>reg</span><span class=cF0> *dst, *src;
<a name="l101"></a>    </span><span class=cF9>I32</span><span class=cF0>             *db;
<a name="l102"></a>    </span><span class=cF9>U16</span><span class=cF0>         </span><span class=cF1>reg</span><span class=cF0> *win_z_buf_ptr;
<a name="l103"></a>    </span><span class=cF9>CColorROPU32</span><span class=cF0>     color, c, old_color;
<a name="l104"></a>    </span><span class=cF9>CTask</span><span class=cF0>           *win_task;
<a name="l105"></a>
<a name="l106"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l107"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l108"></a>        win_task = dc-&gt;win_task;
<a name="l109"></a>        x += win_task-&gt;scroll_x;
<a name="l110"></a>        y += win_task-&gt;scroll_y;
<a name="l111"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l112"></a>    </span><span class=cF1>if</span><span class=cF0> (x &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l113"></a>        w1 = -x;
<a name="l114"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l115"></a>        w1 = </span><span class=cFE>0</span><span class=cF0>;
<a name="l116"></a>    </span><span class=cF1>if</span><span class=cF0> (y &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l117"></a>        h1 = -y;
<a name="l118"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l119"></a>        h1 = </span><span class=cFE>0</span><span class=cF0>;
<a name="l120"></a>    w2 = img-&gt;width;
<a name="l121"></a>    h2 = img-&gt;height;
<a name="l122"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l123"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l124"></a>        x += win_task-&gt;pix_left;
<a name="l125"></a>        y += win_task-&gt;pix_top;
<a name="l126"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l127"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_LOCATE_NEAREST</span><span class=cF0>)
<a name="l128"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l129"></a>        dist = </span><span class=cF5>DistSqrI64</span><span class=cF0>(x + img-&gt;width &gt;&gt; </span><span class=cFE>1</span><span class=cF0>, y + img-&gt;height &gt;&gt; </span><span class=cFE>1</span><span class=cF0>, dc-&gt;cur_x, dc-&gt;cur_y);
<a name="l130"></a>        </span><span class=cF1>if</span><span class=cF0> (dist &lt;= dc-&gt;nearest_dist)
<a name="l131"></a>            dc-&gt;nearest_dist = dist;
<a name="l132"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l133"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l134"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l135"></a>        </span><span class=cF1>if</span><span class=cF0> (x + w1 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l136"></a>            w1=-x;
<a name="l137"></a>        </span><span class=cF1>if</span><span class=cF0> (x + w2 &gt; win_task-&gt;pix_right + </span><span class=cFE>1</span><span class=cF0>)
<a name="l138"></a>            w2 = win_task-&gt;pix_right + </span><span class=cFE>1</span><span class=cF0> - x;
<a name="l139"></a>
<a name="l140"></a>        </span><span class=cF1>if</span><span class=cF0> (y + h1 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l141"></a>            h1 = -y;
<a name="l142"></a>        </span><span class=cF1>if</span><span class=cF0> (y + h2 &gt; win_task-&gt;pix_bottom + </span><span class=cFE>1</span><span class=cF0>)
<a name="l143"></a>            h2 = win_task-&gt;pix_bottom + </span><span class=cFE>1</span><span class=cF0> - y;
<a name="l144"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l145"></a>    </span><span class=cF1>if</span><span class=cF0> (x + w2&gt;dc-&gt;width)
<a name="l146"></a>        w2 = dc-&gt;width - x;
<a name="l147"></a>    </span><span class=cF1>if</span><span class=cF0> (y + h2 &gt; dc-&gt;height)
<a name="l148"></a>        h2 = dc-&gt;height - y;
<a name="l149"></a>    </span><span class=cF1>if</span><span class=cF0> (w1 &lt; w2 &lt;= img-&gt;width &amp;&amp; h1 &lt; h2 &lt;= img-&gt;height)
<a name="l150"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l151"></a>        </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_RECORD_EXTENTS</span><span class=cF0>)
<a name="l152"></a>        {
<a name="l153"></a>            </span><span class=cF1>if</span><span class=cF0> (x + w1 &lt; dc-&gt;min_x)
<a name="l154"></a>                dc-&gt;min_x = x + w1;
<a name="l155"></a>
<a name="l156"></a>            </span><span class=cF1>if</span><span class=cF0> (x + w2 - </span><span class=cFE>1</span><span class=cF0> &gt; dc-&gt;max_x)
<a name="l157"></a>                dc-&gt;max_x = x + w2 - </span><span class=cFE>1</span><span class=cF0>;
<a name="l158"></a>
<a name="l159"></a>            </span><span class=cF1>if</span><span class=cF0> (y + h1 &lt; dc-&gt;min_y)
<a name="l160"></a>                dc-&gt;min_y = y + h1;
<a name="l161"></a>
<a name="l162"></a>            </span><span class=cF1>if</span><span class=cF0> (y + h2 - </span><span class=cFE>1</span><span class=cF0> &gt; dc-&gt;max_y)
<a name="l163"></a>                dc-&gt;max_y = y + h2 - </span><span class=cFE>1</span><span class=cF0>;
<a name="l164"></a>        }
<a name="l165"></a>        </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_DONT_DRAW</span><span class=cF0>)
<a name="l166"></a>            </span><span class=cF1>return</span><span class=cF0> </span><span class=cFE>1</span><span class=cF0>;
<a name="l167"></a>
<a name="l168"></a>        old_color = dc-&gt;color;
<a name="l169"></a>        db = dc-&gt;depth_buf;
<a name="l170"></a>        dc-&gt;depth_buf = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l171"></a>        dc-&gt;color &amp;= ~</span><span class=cF3>ROPF_DITHER</span><span class=cF0>;
<a name="l172"></a>        color = dc-&gt;color;
<a name="l173"></a>        leading_pixels = -(w1 + x) &amp; </span><span class=cFE>7</span><span class=cF0>;
<a name="l174"></a>        leading_pixel_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[</span><span class=cFE>0xFF</span><span class=cF0> &gt;&gt; leading_pixels];
<a name="l175"></a>        bit_shift = -x &amp; </span><span class=cFE>7</span><span class=cF0>;
<a name="l176"></a>        whole_I64s = (w2 - w1 - leading_pixels) &gt;&gt; </span><span class=cFE>3</span><span class=cF0>;
<a name="l177"></a>        </span><span class=cF1>if</span><span class=cF0> (whole_I64s &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l178"></a>            whole_I64s = </span><span class=cFE>0</span><span class=cF0>;
<a name="l179"></a>        trailing_pixels = (x + w2) &amp; </span><span class=cFE>7</span><span class=cF0>;
<a name="l180"></a>        trailing_pixel_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[</span><span class=cFE>0xFF</span><span class=cF0> &lt;&lt; trailing_pixels &amp; </span><span class=cFE>0xFF</span><span class=cF0>];
<a name="l181"></a>        </span><span class=cF1>if</span><span class=cF0> (leading_pixels + trailing_pixels &gt; w2 - w1)
<a name="l182"></a>        {
<a name="l183"></a>            leading_pixel_mask |= trailing_pixel_mask;
<a name="l184"></a>            trailing_pixels = </span><span class=cFE>0</span><span class=cF0>;
<a name="l185"></a>        }
<a name="l186"></a>        </span><span class=cF1>switch</span><span class=cF0> (color.c0.rop)
<a name="l187"></a>        {
<a name="l188"></a>            </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_COLLISION</span><span class=cF0>: </span><span class=cF2>//TODO: Might want to check win_z_buf</span><span class=cF0>
<a name="l189"></a>                color = dc-&gt;bkcolor.c0.color;
<a name="l190"></a>                k = h1 * img-&gt;width_internal;
<a name="l191"></a>                k1 = (h1 + y) * dc-&gt;width_internal + x;
<a name="l192"></a>                </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l193"></a>                </span><span class=cF7>{</span><span class=cF0>
<a name="l194"></a>                    </span><span class=cF1>for</span><span class=cF0> (i = w1; i &lt; w2; i++)
<a name="l195"></a>                    {
<a name="l196"></a>                        c = dc-&gt;body[k1 + i];
<a name="l197"></a>                        </span><span class=cF1>if</span><span class=cF0> (c != </span><span class=cF3>TRANSPARENT</span><span class=cF0> &amp;&amp; c != color &amp;&amp; img-&gt;body[k + i] != </span><span class=cF3>TRANSPARENT</span><span class=cF0>)
<a name="l198"></a>                            dc-&gt;collision_count++;
<a name="l199"></a>                    }
<a name="l200"></a>                    k += img-&gt;width_internal;
<a name="l201"></a>                    k1 += dc-&gt;width_internal;
<a name="l202"></a>                </span><span class=cF7>}</span><span class=cF0>
<a name="l203"></a>                </span><span class=cF1>break</span><span class=cF0>;
<a name="l204"></a>
<a name="l205"></a>            </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_MONO</span><span class=cF0>:
<a name="l206"></a>                color_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c0.color];
<a name="l207"></a>                </span><span class=cF1>if</span><span class=cF0> (img-&gt;flags &amp; </span><span class=cF3>DCF_NO_TRANSPARENTS</span><span class=cF0>)
<a name="l208"></a>                </span><span class=cF7>{</span><span class=cF0>
<a name="l209"></a>                    </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF7>)</span><span class=cF0> || dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF0>)
<a name="l210"></a>                        win_z_buf_ptr = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l211"></a>                    </span><span class=cF1>else</span><span class=cF0>
<a name="l212"></a>                    {
<a name="l213"></a>                        win_z_num = win_task-&gt;win_z_num;
<a name="l214"></a>                        win_z_buf_ptr = </span><span class=cFB>gr</span><span class=cF0>.win_z_buf(</span><span class=cF1>U8</span><span class=cF0> *) +
<a name="l215"></a>                                        (</span><span class=cF7>(</span><span class=cF0>h1 + y</span><span class=cF7>)</span><span class=cF0> / </span><span class=cF3>FONT_HEIGHT</span><span class=cF0> * </span><span class=cF3>TEXT_COLS</span><span class=cF0> + </span><span class=cF7>(</span><span class=cF0>w1 + x</span><span class=cF7>)</span><span class=cF0> / </span><span class=cF3>FONT_WIDTH</span><span class=cF0>) * </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>);
<a name="l216"></a>                        win_z_buf_line_dec = whole_I64s;
<a name="l217"></a>                        </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l218"></a>                            win_z_buf_line_dec++;
<a name="l219"></a>                        </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l220"></a>                            win_z_buf_line_dec++;
<a name="l221"></a>                        win_z_buf_line_dec *= </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>);
<a name="l222"></a>                        win_z_buf_line_inc = </span><span class=cF3>TEXT_COLS</span><span class=cF0> * </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>) - win_z_buf_line_dec;
<a name="l223"></a>                    }
<a name="l224"></a>                    kk = h1 * img-&gt;width_internal + w1;
<a name="l225"></a>                    kk1 = (h1 + y) * dc-&gt;width_internal + x + w1;
<a name="l226"></a>                    kk = (kk - bit_shift) &amp; ~</span><span class=cFE>7</span><span class=cF0> + bit_shift;
<a name="l227"></a>                    bit_shift *= </span><span class=cFE>8</span><span class=cF0>;
<a name="l228"></a>                    </span><span class=cF1>if</span><span class=cF0> (win_z_buf_ptr)
<a name="l229"></a>                        </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l230"></a>                        {
<a name="l231"></a>                            src = img-&gt;body + kk  &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l232"></a>                            dst = dc-&gt;body  + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l233"></a>                            </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l234"></a>                            </span><span class=cF7>{</span><span class=cF0>
<a name="l235"></a>                                </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l236"></a>                                {
<a name="l237"></a>                                    </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l238"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l239"></a>                                                       (*src</span><span class=cF7>(</span><span class=cF9>U64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++ &gt;&gt; bit_shift | *src</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &lt;&lt; </span><span class=cF7>(</span><span class=cFE>64</span><span class=cF0> - bit_shift</span><span class=cF7>)</span><span class=cF0>) &amp;
<a name="l240"></a>                                                        ~leading_pixel_mask &amp; color_mask;
<a name="l241"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l242"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *)   &amp;  leading_pixel_mask |
<a name="l243"></a>                                                        *src(</span><span class=cF9>I64</span><span class=cF0> *)++ &amp; ~leading_pixel_mask &amp; color_mask;
<a name="l244"></a>                                }
<a name="l245"></a>                                </span><span class=cF1>else</span><span class=cF0>
<a name="l246"></a>                                {
<a name="l247"></a>                                    src(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l248"></a>                                    dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l249"></a>                                }
<a name="l250"></a>                            </span><span class=cF7>}</span><span class=cF0>
<a name="l251"></a>                            </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l252"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++)
<a name="l253"></a>                                    </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l254"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = (*src</span><span class=cF7>(</span><span class=cF9>U64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++ &gt;&gt; bit_shift | *src</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &lt;&lt; </span><span class=cF7>(</span><span class=cFE>64</span><span class=cF0> - bit_shift</span><span class=cF7>)</span><span class=cF0>) &amp;
<a name="l255"></a>                                                        color_mask;
<a name="l256"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l257"></a>                                    </span><span class=cF7>{</span><span class=cF0>
<a name="l258"></a>                                        src(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l259"></a>                                        dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l260"></a>                                    </span><span class=cF7>}</span><span class=cF0>
<a name="l261"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l262"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++)
<a name="l263"></a>                                    </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l264"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *src(</span><span class=cF9>I64</span><span class=cF0> *)++ &amp; color_mask;
<a name="l265"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l266"></a>                                    </span><span class=cF7>{</span><span class=cF0>
<a name="l267"></a>                                        src(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l268"></a>                                        dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l269"></a>                                    </span><span class=cF7>}</span><span class=cF0>
<a name="l270"></a>                            </span><span class=cF1>if</span><span class=cF0> (trailing_pixels &amp;&amp; win_z_num &gt;= *win_z_buf_ptr++)
<a name="l271"></a>                            </span><span class=cF7>{</span><span class=cF0>
<a name="l272"></a>                                </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l273"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l274"></a>                                                 (*src</span><span class=cF7>(</span><span class=cF9>U64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++ &gt;&gt; bit_shift | *src</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &lt;&lt; </span><span class=cF7>(</span><span class=cFE>64</span><span class=cF0> - bit_shift</span><span class=cF7>)</span><span class=cF0>) &amp;
<a name="l275"></a>                                                  ~trailing_pixel_mask &amp; color_mask;
<a name="l276"></a>                                </span><span class=cF1>else</span><span class=cF0>
<a name="l277"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l278"></a>                                                  *src(</span><span class=cF9>I64</span><span class=cF0> *)++ &amp; ~trailing_pixel_mask &amp; color_mask;
<a name="l279"></a>                            </span><span class=cF7>}</span><span class=cF0>
<a name="l280"></a>                            kk  += img-&gt;width_internal;
<a name="l281"></a>                            kk1 += dc-&gt;width_internal;
<a name="l282"></a>                            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>j + y</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>7</span><span class=cF0> == </span><span class=cFE>7</span><span class=cF0>)
<a name="l283"></a>                                win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) += win_z_buf_line_inc;
<a name="l284"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l285"></a>                                win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) -= win_z_buf_line_dec;
<a name="l286"></a>                        }
<a name="l287"></a>                    </span><span class=cF1>else</span><span class=cF0>
<a name="l288"></a>                        </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l289"></a>                        {
<a name="l290"></a>                            src = img-&gt;body + kk  &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l291"></a>                            dst = dc-&gt;body  + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l292"></a>                            </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l293"></a>                            </span><span class=cF7>{</span><span class=cF0>
<a name="l294"></a>                                </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l295"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l296"></a>                                                   (*src</span><span class=cF7>(</span><span class=cF9>U64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++ &gt;&gt; bit_shift | *src</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &lt;&lt; </span><span class=cF7>(</span><span class=cFE>64</span><span class=cF0> - bit_shift</span><span class=cF7>)</span><span class=cF0>) &amp;
<a name="l297"></a>                                                    ~leading_pixel_mask &amp; color_mask;
<a name="l298"></a>                                </span><span class=cF1>else</span><span class=cF0>
<a name="l299"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *)   &amp;  leading_pixel_mask |
<a name="l300"></a>                                                    *src(</span><span class=cF9>I64</span><span class=cF0> *)++ &amp; ~leading_pixel_mask &amp; color_mask;
<a name="l301"></a>                            </span><span class=cF7>}</span><span class=cF0>
<a name="l302"></a>                            </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l303"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++)
<a name="l304"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = (*src</span><span class=cF7>(</span><span class=cF9>U64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++ &gt;&gt; bit_shift | *src</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &lt;&lt; </span><span class=cF7>(</span><span class=cFE>64</span><span class=cF0> - bit_shift</span><span class=cF7>)</span><span class=cF0>) &amp;
<a name="l305"></a>                                                    color_mask;
<a name="l306"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l307"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++)
<a name="l308"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *src(</span><span class=cF9>I64</span><span class=cF0> *)++ &amp; color_mask;
<a name="l309"></a>
<a name="l310"></a>                            </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l311"></a>                            </span><span class=cF7>{</span><span class=cF0>
<a name="l312"></a>                                </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l313"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l314"></a>                                                 (*src</span><span class=cF7>(</span><span class=cF9>U64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++ &gt;&gt; bit_shift | *src</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &lt;&lt; </span><span class=cF7>(</span><span class=cFE>64</span><span class=cF0> - bit_shift</span><span class=cF7>)</span><span class=cF0>) &amp;
<a name="l315"></a>                                                  ~trailing_pixel_mask &amp; color_mask;
<a name="l316"></a>                                </span><span class=cF1>else</span><span class=cF0>
<a name="l317"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *)   &amp;  trailing_pixel_mask |
<a name="l318"></a>                                                  *src(</span><span class=cF9>I64</span><span class=cF0> *)++ &amp; ~trailing_pixel_mask &amp; color_mask;
<a name="l319"></a>                            </span><span class=cF7>}</span><span class=cF0>
<a name="l320"></a>                            kk  += img-&gt;width_internal;
<a name="l321"></a>                            kk1 += dc-&gt;width_internal;
<a name="l322"></a>                        }
<a name="l323"></a>                </span><span class=cF7>}</span><span class=cF0>
<a name="l324"></a>                </span><span class=cF1>else</span><span class=cF0>
<a name="l325"></a>                </span><span class=cF7>{</span><span class=cF0>
<a name="l326"></a>                    k = h1 * img-&gt;width_internal;
<a name="l327"></a>                    </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF7>)</span><span class=cF0> || dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF0>)
<a name="l328"></a>                    {
<a name="l329"></a>                        </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l330"></a>                        </span><span class=cF7>{</span><span class=cF0>
<a name="l331"></a>                            </span><span class=cF1>for</span><span class=cF0> (i = w1; i &lt; w2; i++)
<a name="l332"></a>                                </span><span class=cF1>if</span><span class=cF0> (img-&gt;body[k + i])
<a name="l333"></a>                                    </span><span class=cF5>GrPlot0</span><span class=cF0>(dc, x + i, y + j);
<a name="l334"></a>                            k += img-&gt;width_internal;
<a name="l335"></a>                        </span><span class=cF7>}</span><span class=cF0>
<a name="l336"></a>                    }
<a name="l337"></a>                    </span><span class=cF1>else</span><span class=cF0>
<a name="l338"></a>                    {
<a name="l339"></a>                        win_z_num = win_task-&gt;win_z_num;
<a name="l340"></a>                        win_z_buf_ptr = </span><span class=cFB>gr</span><span class=cF0>.win_z_buf(</span><span class=cF1>U8</span><span class=cF0> *) +
<a name="l341"></a>                                        (</span><span class=cF7>(</span><span class=cF0>h1 + y</span><span class=cF7>)</span><span class=cF0> / </span><span class=cF3>FONT_HEIGHT</span><span class=cF0> * </span><span class=cF3>TEXT_COLS</span><span class=cF0> + </span><span class=cF7>(</span><span class=cF0>w1 + x</span><span class=cF7>)</span><span class=cF0> / </span><span class=cF3>FONT_WIDTH</span><span class=cF0>) * </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>);
<a name="l342"></a>                        win_z_buf_line_dec = whole_I64s;
<a name="l343"></a>                        </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l344"></a>                            win_z_buf_line_dec++;
<a name="l345"></a>                        </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l346"></a>                            win_z_buf_line_dec++;
<a name="l347"></a>                        win_z_buf_line_dec *= </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>);
<a name="l348"></a>                        win_z_buf_line_inc = </span><span class=cF3>TEXT_COLS</span><span class=cF0> * </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>) - win_z_buf_line_dec;
<a name="l349"></a>                        </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l350"></a>                        </span><span class=cF7>{</span><span class=cF0>
<a name="l351"></a>                            </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l352"></a>                                color_mask = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l353"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l354"></a>                                color_mask = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l355"></a>                            </span><span class=cF1>for</span><span class=cF0> (i = w1; i &lt; w2;)
<a name="l356"></a>                            {
<a name="l357"></a>                                </span><span class=cF1>if</span><span class=cF0> (color_mask)
<a name="l358"></a>                                    </span><span class=cF1>if</span><span class=cF0> (img-&gt;body[k + i])
<a name="l359"></a>                                        </span><span class=cF5>GrPlot0</span><span class=cF0>(dc, x + i, y + j);
<a name="l360"></a>                                </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>(++i + x) &amp; </span><span class=cFE>7</span><span class=cF7>)</span><span class=cF0> &amp;&amp; i &lt; w2)
<a name="l361"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l362"></a>                                    </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l363"></a>                                        color_mask = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l364"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l365"></a>                                        color_mask = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l366"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l367"></a>                            }
<a name="l368"></a>                            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>j + y</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>7</span><span class=cF0> == </span><span class=cFE>7</span><span class=cF0>)
<a name="l369"></a>                                win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) += win_z_buf_line_inc;
<a name="l370"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l371"></a>                                win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) -= win_z_buf_line_dec;
<a name="l372"></a>                            k += img-&gt;width_internal;
<a name="l373"></a>                        </span><span class=cF7>}</span><span class=cF0>
<a name="l374"></a>                    }
<a name="l375"></a>                </span><span class=cF7>}</span><span class=cF0>
<a name="l376"></a>                </span><span class=cF1>break</span><span class=cF0>;
<a name="l377"></a>
<a name="l378"></a>            </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_EQU</span><span class=cF0>:
<a name="l379"></a>                </span><span class=cF1>if</span><span class=cF0> (img-&gt;flags &amp; </span><span class=cF3>DCF_NO_TRANSPARENTS</span><span class=cF0>)
<a name="l380"></a>                </span><span class=cF7>{</span><span class=cF0>
<a name="l381"></a>                    </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF7>)</span><span class=cF0> || dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF0>)
<a name="l382"></a>                        win_z_buf_ptr = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l383"></a>                    </span><span class=cF1>else</span><span class=cF0>
<a name="l384"></a>                    {
<a name="l385"></a>                        win_z_num = win_task-&gt;win_z_num;
<a name="l386"></a>                        win_z_buf_ptr = </span><span class=cFB>gr</span><span class=cF0>.win_z_buf(</span><span class=cF1>U8</span><span class=cF0> *) +
<a name="l387"></a>                                        (</span><span class=cF7>(</span><span class=cF0>h1 + y</span><span class=cF7>)</span><span class=cF0> / </span><span class=cF3>FONT_HEIGHT</span><span class=cF0> * </span><span class=cF3>TEXT_COLS</span><span class=cF0> + </span><span class=cF7>(</span><span class=cF0>w1 + x</span><span class=cF7>)</span><span class=cF0> / </span><span class=cF3>FONT_WIDTH</span><span class=cF0>) * </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>);
<a name="l388"></a>                        win_z_buf_line_dec = whole_I64s;
<a name="l389"></a>                        </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l390"></a>                            win_z_buf_line_dec++;
<a name="l391"></a>                        </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l392"></a>                            win_z_buf_line_dec++;
<a name="l393"></a>                        win_z_buf_line_dec *= </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>);
<a name="l394"></a>                        win_z_buf_line_inc = </span><span class=cF3>TEXT_COLS</span><span class=cF0> * </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>) - win_z_buf_line_dec;
<a name="l395"></a>                    }
<a name="l396"></a>                    kk = h1 * img-&gt;width_internal + w1;
<a name="l397"></a>                    kk1 = (h1 + y) * dc-&gt;width_internal + x + w1;
<a name="l398"></a>                    kk = (kk - bit_shift) &amp; ~</span><span class=cFE>7</span><span class=cF0> + bit_shift;
<a name="l399"></a>                    bit_shift *= </span><span class=cFE>8</span><span class=cF0>;
<a name="l400"></a>                    </span><span class=cF1>if</span><span class=cF0> (win_z_buf_ptr)
<a name="l401"></a>                        </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l402"></a>                        {
<a name="l403"></a>                            src = img-&gt;body + kk  &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l404"></a>                            dst = dc-&gt;body  + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l405"></a>                            </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l406"></a>                            </span><span class=cF7>{</span><span class=cF0>
<a name="l407"></a>                                </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l408"></a>                                {
<a name="l409"></a>                                    </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l410"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l411"></a>                                                       (*src</span><span class=cF7>(</span><span class=cF9>U64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++ &gt;&gt; bit_shift | *src</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &lt;&lt; </span><span class=cF7>(</span><span class=cFE>64</span><span class=cF0> - bit_shift</span><span class=cF7>)</span><span class=cF0>) &amp;
<a name="l412"></a>                                                        ~leading_pixel_mask;
<a name="l413"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l414"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *)   &amp;  leading_pixel_mask |
<a name="l415"></a>                                                        *src(</span><span class=cF9>I64</span><span class=cF0> *)++ &amp; ~leading_pixel_mask;
<a name="l416"></a>                                }
<a name="l417"></a>                                </span><span class=cF1>else</span><span class=cF0>
<a name="l418"></a>                                {
<a name="l419"></a>                                    src(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l420"></a>                                    dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l421"></a>                                }
<a name="l422"></a>                            </span><span class=cF7>}</span><span class=cF0>
<a name="l423"></a>                            </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l424"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++)
<a name="l425"></a>                                    </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l426"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *src(</span><span class=cF9>U64</span><span class=cF0> *)++ &gt;&gt; bit_shift |
<a name="l427"></a>                                                        *src(</span><span class=cF9>I64</span><span class=cF0> *) &lt;&lt; (</span><span class=cFE>64</span><span class=cF0> - bit_shift);
<a name="l428"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l429"></a>                                    </span><span class=cF7>{</span><span class=cF0>
<a name="l430"></a>                                        src(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l431"></a>                                        dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l432"></a>                                    </span><span class=cF7>}</span><span class=cF0>
<a name="l433"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l434"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++)
<a name="l435"></a>                                    </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l436"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *src(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l437"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l438"></a>                                    </span><span class=cF7>{</span><span class=cF0>
<a name="l439"></a>                                        src(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l440"></a>                                        dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l441"></a>                                    </span><span class=cF7>}</span><span class=cF0>
<a name="l442"></a>                            </span><span class=cF1>if</span><span class=cF0> (trailing_pixels &amp;&amp; win_z_num &gt;= *win_z_buf_ptr++)
<a name="l443"></a>                            </span><span class=cF7>{</span><span class=cF0>
<a name="l444"></a>                                </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l445"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l446"></a>                                                 (*src</span><span class=cF7>(</span><span class=cF9>U64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++ &gt;&gt; bit_shift | *src</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &lt;&lt; </span><span class=cF7>(</span><span class=cFE>64</span><span class=cF0> - bit_shift</span><span class=cF7>)</span><span class=cF0>) &amp;
<a name="l447"></a>                                                  ~trailing_pixel_mask;
<a name="l448"></a>                                </span><span class=cF1>else</span><span class=cF0>
<a name="l449"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *)   &amp;  trailing_pixel_mask |
<a name="l450"></a>                                                  *src(</span><span class=cF9>I64</span><span class=cF0> *)++ &amp; ~trailing_pixel_mask;
<a name="l451"></a>                            </span><span class=cF7>}</span><span class=cF0>
<a name="l452"></a>                            kk  += img-&gt;width_internal;
<a name="l453"></a>                            kk1 += dc-&gt;width_internal;
<a name="l454"></a>                            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>j + y</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>7</span><span class=cF0> == </span><span class=cFE>7</span><span class=cF0>)
<a name="l455"></a>                                win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) += win_z_buf_line_inc;
<a name="l456"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l457"></a>                                win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) -= win_z_buf_line_dec;
<a name="l458"></a>                        }
<a name="l459"></a>                    </span><span class=cF1>else</span><span class=cF0>
<a name="l460"></a>                        </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l461"></a>                        {
<a name="l462"></a>                            src = img-&gt;body + kk  &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l463"></a>                            dst = dc-&gt;body  + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l464"></a>                            </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l465"></a>                            </span><span class=cF7>{</span><span class=cF0>
<a name="l466"></a>                                </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l467"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l468"></a>                                                   (*src</span><span class=cF7>(</span><span class=cF9>U64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++ &gt;&gt; bit_shift | *src</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &lt;&lt; </span><span class=cF7>(</span><span class=cFE>64</span><span class=cF0> - bit_shift</span><span class=cF7>)</span><span class=cF0>) &amp;
<a name="l469"></a>                                                    ~leading_pixel_mask;
<a name="l470"></a>                                </span><span class=cF1>else</span><span class=cF0>
<a name="l471"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *)   &amp;  leading_pixel_mask |
<a name="l472"></a>                                                    *src(</span><span class=cF9>I64</span><span class=cF0> *)++ &amp; ~leading_pixel_mask;
<a name="l473"></a>                            </span><span class=cF7>}</span><span class=cF0>
<a name="l474"></a>                            </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l475"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++)
<a name="l476"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *src(</span><span class=cF9>U64</span><span class=cF0> *)++ &gt;&gt; bit_shift |
<a name="l477"></a>                                                    *src(</span><span class=cF9>I64</span><span class=cF0> *) &lt;&lt; (</span><span class=cFE>64</span><span class=cF0> - bit_shift);
<a name="l478"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l479"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++)
<a name="l480"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *src(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l481"></a>
<a name="l482"></a>                            </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l483"></a>                            </span><span class=cF7>{</span><span class=cF0>
<a name="l484"></a>                                </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l485"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l486"></a>                                                 (*src</span><span class=cF7>(</span><span class=cF9>U64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++ &gt;&gt; bit_shift | *src</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &lt;&lt; </span><span class=cF7>(</span><span class=cFE>64</span><span class=cF0> - bit_shift</span><span class=cF7>)</span><span class=cF0>) &amp;
<a name="l487"></a>                                                  ~trailing_pixel_mask;
<a name="l488"></a>                                </span><span class=cF1>else</span><span class=cF0>
<a name="l489"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *)   &amp;  trailing_pixel_mask |
<a name="l490"></a>                                                  *src(</span><span class=cF9>I64</span><span class=cF0> *)++ &amp; ~trailing_pixel_mask;
<a name="l491"></a>                            </span><span class=cF7>}</span><span class=cF0>
<a name="l492"></a>                            kk  += img-&gt;width_internal;
<a name="l493"></a>                            kk1 += dc-&gt;width_internal;
<a name="l494"></a>                        }
<a name="l495"></a>                </span><span class=cF7>}</span><span class=cF0>
<a name="l496"></a>                </span><span class=cF1>else</span><span class=cF0>
<a name="l497"></a>                </span><span class=cF7>{</span><span class=cF0>
<a name="l498"></a>here1a:
<a name="l499"></a>                    k = h1 * img-&gt;width_internal;
<a name="l500"></a>                    </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF7>)</span><span class=cF0> || dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF0>)
<a name="l501"></a>                    {
<a name="l502"></a>                        </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l503"></a>                        </span><span class=cF7>{</span><span class=cF0>
<a name="l504"></a>                            </span><span class=cF1>for</span><span class=cF0> (i = w1; i &lt; w2; i++)
<a name="l505"></a>                            {
<a name="l506"></a>                                c = img-&gt;body[k + i];
<a name="l507"></a>                                </span><span class=cF1>if</span><span class=cF0> (c != </span><span class=cF3>TRANSPARENT</span><span class=cF0>)
<a name="l508"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l509"></a>                                    dc-&gt;color.c0.color = c;
<a name="l510"></a>                                    </span><span class=cF5>GrPlot0</span><span class=cF0>(dc, x + i, y + j);
<a name="l511"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l512"></a>                            }
<a name="l513"></a>                            k += img-&gt;width_internal;
<a name="l514"></a>                        </span><span class=cF7>}</span><span class=cF0>
<a name="l515"></a>                    }
<a name="l516"></a>                    </span><span class=cF1>else</span><span class=cF0>
<a name="l517"></a>                    {
<a name="l518"></a>                        win_z_num = win_task-&gt;win_z_num;
<a name="l519"></a>                        win_z_buf_ptr = </span><span class=cFB>gr</span><span class=cF0>.win_z_buf(</span><span class=cF1>U8</span><span class=cF0> *) +
<a name="l520"></a>                                        (</span><span class=cF7>(</span><span class=cF0>h1 + y</span><span class=cF7>)</span><span class=cF0> / </span><span class=cF3>FONT_HEIGHT</span><span class=cF0> * </span><span class=cF3>TEXT_COLS</span><span class=cF0> + </span><span class=cF7>(</span><span class=cF0>w1 + x</span><span class=cF7>)</span><span class=cF0> / </span><span class=cF3>FONT_WIDTH</span><span class=cF0>) * </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>);
<a name="l521"></a>                        win_z_buf_line_dec = whole_I64s;
<a name="l522"></a>                        </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l523"></a>                            win_z_buf_line_dec++;
<a name="l524"></a>                        </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l525"></a>                            win_z_buf_line_dec++;
<a name="l526"></a>                        win_z_buf_line_dec *= </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>);
<a name="l527"></a>                        win_z_buf_line_inc = </span><span class=cF3>TEXT_COLS</span><span class=cF0> * </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>) - win_z_buf_line_dec;
<a name="l528"></a>                        </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l529"></a>                        </span><span class=cF7>{</span><span class=cF0>
<a name="l530"></a>                            </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l531"></a>                                color_mask = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l532"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l533"></a>                                color_mask = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l534"></a>                            </span><span class=cF1>for</span><span class=cF0> (i = w1; i &lt; w2;)
<a name="l535"></a>                            {
<a name="l536"></a>                                </span><span class=cF1>if</span><span class=cF0> (color_mask)
<a name="l537"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l538"></a>                                    c = img-&gt;body[k + i];
<a name="l539"></a>                                    </span><span class=cF1>if</span><span class=cF0> (c != </span><span class=cF3>TRANSPARENT</span><span class=cF0>)
<a name="l540"></a>                                    {
<a name="l541"></a>                                        dc-&gt;color.c0.color = c;
<a name="l542"></a>                                        </span><span class=cF5>GrPlot0</span><span class=cF0>(dc, x + i, y + j);
<a name="l543"></a>                                    }
<a name="l544"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l545"></a>                                </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>(++i + x) &amp; </span><span class=cFE>7</span><span class=cF7>)</span><span class=cF0> &amp;&amp; i &lt; w2)
<a name="l546"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l547"></a>                                    </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l548"></a>                                        color_mask = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l549"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l550"></a>                                        color_mask = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l551"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l552"></a>                            }
<a name="l553"></a>                            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>j + y</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>7</span><span class=cF0> == </span><span class=cFE>7</span><span class=cF0>)
<a name="l554"></a>                                win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) += win_z_buf_line_inc;
<a name="l555"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l556"></a>                                win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) -= win_z_buf_line_dec;
<a name="l557"></a>                            k += img-&gt;width_internal;
<a name="l558"></a>                        </span><span class=cF7>}</span><span class=cF0>
<a name="l559"></a>                    }
<a name="l560"></a>                    dc-&gt;color = color;
<a name="l561"></a>                </span><span class=cF7>}</span><span class=cF0>
<a name="l562"></a>                </span><span class=cF1>break</span><span class=cF0>;
<a name="l563"></a>
<a name="l564"></a>            </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_XOR</span><span class=cF0>:
<a name="l565"></a>                </span><span class=cF1>if</span><span class=cF0> (img-&gt;flags &amp; </span><span class=cF3>DCF_NO_TRANSPARENTS</span><span class=cF0>)
<a name="l566"></a>                </span><span class=cF7>{</span><span class=cF0>
<a name="l567"></a>                    </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF7>)</span><span class=cF0> || dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF0>)
<a name="l568"></a>                        win_z_buf_ptr = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l569"></a>                    </span><span class=cF1>else</span><span class=cF0>
<a name="l570"></a>                    {
<a name="l571"></a>                        win_z_num = win_task-&gt;win_z_num;
<a name="l572"></a>                        win_z_buf_ptr = </span><span class=cFB>gr</span><span class=cF0>.win_z_buf(</span><span class=cF1>U8</span><span class=cF0> *) +
<a name="l573"></a>                                        (</span><span class=cF7>(</span><span class=cF0>h1 + y</span><span class=cF7>)</span><span class=cF0> / </span><span class=cF3>FONT_HEIGHT</span><span class=cF0> * </span><span class=cF3>TEXT_COLS</span><span class=cF0> + </span><span class=cF7>(</span><span class=cF0>w1 + x</span><span class=cF7>)</span><span class=cF0> / </span><span class=cF3>FONT_WIDTH</span><span class=cF0>) * </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>);
<a name="l574"></a>                        win_z_buf_line_dec = whole_I64s;
<a name="l575"></a>                        </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l576"></a>                            win_z_buf_line_dec++;
<a name="l577"></a>                        </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l578"></a>                            win_z_buf_line_dec++;
<a name="l579"></a>                        win_z_buf_line_dec *= </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>);
<a name="l580"></a>                        win_z_buf_line_inc = </span><span class=cF3>TEXT_COLS</span><span class=cF0> * </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>) - win_z_buf_line_dec;
<a name="l581"></a>                    }
<a name="l582"></a>                    kk = h1 * img-&gt;width_internal + w1;
<a name="l583"></a>                    kk1 = (h1 + y) * dc-&gt;width_internal + x + w1;
<a name="l584"></a>                    kk = (kk - bit_shift) &amp; ~</span><span class=cFE>7</span><span class=cF0> + bit_shift;
<a name="l585"></a>                    bit_shift *= </span><span class=cFE>8</span><span class=cF0>;
<a name="l586"></a>                    </span><span class=cF1>if</span><span class=cF0> (win_z_buf_ptr)
<a name="l587"></a>                        </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l588"></a>                        {
<a name="l589"></a>                            src = img-&gt;body + kk  &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l590"></a>                            dst = dc-&gt;body  + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l591"></a>                            </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l592"></a>                            </span><span class=cF7>{</span><span class=cF0>
<a name="l593"></a>                                </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l594"></a>                                {
<a name="l595"></a>                                    </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l596"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l597"></a>                                                       (*dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> ^
<a name="l598"></a>                                                            </span><span class=cF7>(</span><span class=cF0>*src(</span><span class=cF9>U64</span><span class=cF0> *)++ &gt;&gt; bit_shift | *src(</span><span class=cF9>I64</span><span class=cF0> *) &lt;&lt; (</span><span class=cFE>64</span><span class=cF0> - bit_shift)</span><span class=cF7>)</span><span class=cF0>) &amp;
<a name="l599"></a>                                                        ~leading_pixel_mask;
<a name="l600"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l601"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l602"></a>                                                       (*dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> ^ *src</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++) &amp; ~leading_pixel_mask;
<a name="l603"></a>                                }
<a name="l604"></a>                                </span><span class=cF1>else</span><span class=cF0>
<a name="l605"></a>                                {
<a name="l606"></a>                                    src(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l607"></a>                                    dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l608"></a>                                }
<a name="l609"></a>                            </span><span class=cF7>}</span><span class=cF0>
<a name="l610"></a>                            </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l611"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++)
<a name="l612"></a>                                    </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l613"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ ^= *src(</span><span class=cF9>U64</span><span class=cF0> *)++ &gt;&gt; bit_shift |
<a name="l614"></a>                                                         *src(</span><span class=cF9>I64</span><span class=cF0> *) &lt;&lt; (</span><span class=cFE>64</span><span class=cF0> - bit_shift);
<a name="l615"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l616"></a>                                    </span><span class=cF7>{</span><span class=cF0>
<a name="l617"></a>                                        src(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l618"></a>                                        dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l619"></a>                                    </span><span class=cF7>}</span><span class=cF0>
<a name="l620"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l621"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++)
<a name="l622"></a>                                    </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l623"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ ^= *src(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l624"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l625"></a>                                    </span><span class=cF7>{</span><span class=cF0>
<a name="l626"></a>                                        src(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l627"></a>                                        dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l628"></a>                                    </span><span class=cF7>}</span><span class=cF0>
<a name="l629"></a>                            </span><span class=cF1>if</span><span class=cF0> (trailing_pixels &amp;&amp; win_z_num &gt;= *win_z_buf_ptr++)
<a name="l630"></a>                            </span><span class=cF7>{</span><span class=cF0>
<a name="l631"></a>                                </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l632"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l633"></a>                                                 (*dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> ^
<a name="l634"></a>                                                    </span><span class=cF7>(</span><span class=cF0>*src(</span><span class=cF9>U64</span><span class=cF0> *)++ &gt;&gt; bit_shift | *src(</span><span class=cF9>I64</span><span class=cF0> *) &lt;&lt; (</span><span class=cFE>64</span><span class=cF0> - bit_shift)</span><span class=cF7>)</span><span class=cF0>) &amp;
<a name="l635"></a>                                                  ~trailing_pixel_mask;
<a name="l636"></a>                                </span><span class=cF1>else</span><span class=cF0>
<a name="l637"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l638"></a>                                                 (*dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> ^ *src</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++) &amp; ~trailing_pixel_mask;
<a name="l639"></a>                            </span><span class=cF7>}</span><span class=cF0>
<a name="l640"></a>                            kk  += img-&gt;width_internal;
<a name="l641"></a>                            kk1 += dc-&gt;width_internal;
<a name="l642"></a>                            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>j + y</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>7</span><span class=cF0> == </span><span class=cFE>7</span><span class=cF0>)
<a name="l643"></a>                                win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) += win_z_buf_line_inc;
<a name="l644"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l645"></a>                                win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) -= win_z_buf_line_dec;
<a name="l646"></a>                        }
<a name="l647"></a>                    </span><span class=cF1>else</span><span class=cF0>
<a name="l648"></a>                        </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l649"></a>                        {
<a name="l650"></a>                            src = img-&gt;body + kk  &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l651"></a>                            dst = dc-&gt;body  + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l652"></a>                            </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l653"></a>                            </span><span class=cF7>{</span><span class=cF0>
<a name="l654"></a>                                </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l655"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l656"></a>                                                   (*dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> ^
<a name="l657"></a>                                                        </span><span class=cF7>(</span><span class=cF0>*src(</span><span class=cF9>U64</span><span class=cF0> *)++ &gt;&gt; bit_shift | *src(</span><span class=cF9>I64</span><span class=cF0> *) &lt;&lt; (</span><span class=cFE>64</span><span class=cF0> - bit_shift)</span><span class=cF7>)</span><span class=cF0>) &amp;
<a name="l658"></a>                                                    ~leading_pixel_mask;
<a name="l659"></a>                                </span><span class=cF1>else</span><span class=cF0>
<a name="l660"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l661"></a>                                                   (*dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> ^ *src</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++) &amp; ~leading_pixel_mask;
<a name="l662"></a>                            </span><span class=cF7>}</span><span class=cF0>
<a name="l663"></a>                            </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l664"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++)
<a name="l665"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ ^= *src(</span><span class=cF9>U64</span><span class=cF0> *)++ &gt;&gt; bit_shift | *src(</span><span class=cF9>I64</span><span class=cF0> *) &lt;&lt; (</span><span class=cFE>64</span><span class=cF0> - bit_shift);
<a name="l666"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l667"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++)
<a name="l668"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ ^= *src(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l669"></a>                            </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l670"></a>                            </span><span class=cF7>{</span><span class=cF0>
<a name="l671"></a>                                </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l672"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *)&amp;trailing_pixel_mask |
<a name="l673"></a>                                                 (*dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> ^
<a name="l674"></a>                                                    </span><span class=cF7>(</span><span class=cF0>*src(</span><span class=cF9>U64</span><span class=cF0> *)++ &gt;&gt; bit_shift | *src(</span><span class=cF9>I64</span><span class=cF0> *) &lt;&lt; (</span><span class=cFE>64</span><span class=cF0> - bit_shift)</span><span class=cF7>)</span><span class=cF0>) &amp;
<a name="l675"></a>                                                  ~trailing_pixel_mask;
<a name="l676"></a>                                </span><span class=cF1>else</span><span class=cF0>
<a name="l677"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l678"></a>                                                 (*dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> ^ *src</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++) &amp; ~trailing_pixel_mask;
<a name="l679"></a>                            </span><span class=cF7>}</span><span class=cF0>
<a name="l680"></a>                            kk  += img-&gt;width_internal;
<a name="l681"></a>                            kk1 += dc-&gt;width_internal;
<a name="l682"></a>                        }
<a name="l683"></a>                </span><span class=cF7>}</span><span class=cF0>
<a name="l684"></a>                </span><span class=cF1>else</span><span class=cF0>
<a name="l685"></a>                    </span><span class=cF1>goto</span><span class=cF0> here1a;
<a name="l686"></a>                </span><span class=cF1>break</span><span class=cF0>;
<a name="l687"></a>        }
<a name="l688"></a>        dc-&gt;depth_buf   = db;
<a name="l689"></a>        dc-&gt;color       = old_color;
<a name="l690"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cFE>1</span><span class=cF0>;
<a name="l691"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l692"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l693"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cFE>0</span><span class=cF0>;
<a name="l694"></a>}
<a name="l695"></a>
<a name="l696"></a>#</span><span class=cF1>help_index</span><span class=cF0> </span><span class=cF6>&quot;Graphics/Device Contexts&quot;</span><span class=cF0>
<a name="l697"></a>
<a name="l698"></a></span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF5>GrBitMap4ToBitMap8</span><span class=cF0>(</span><span class=cF1>U8</span><span class=cF0> *dst, </span><span class=cF1>U8</span><span class=cF0> *src, </span><span class=cF9>I64</span><span class=cF0> src_size, </span><span class=cF9>I64</span><span class=cF0> bkcolor)
<a name="l699"></a>{
<a name="l700"></a>    </span><span class=cF9>I64</span><span class=cF0> c, k, i = src_size * </span><span class=cFE>2</span><span class=cF0>, i1 = i &gt;&gt; </span><span class=cFE>3</span><span class=cF0>;
<a name="l701"></a>
<a name="l702"></a>    </span><span class=cF1>for</span><span class=cF0> (k = </span><span class=cFE>0</span><span class=cF0>; k &lt; i; k++)
<a name="l703"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l704"></a>        c = </span><span class=cFE>0</span><span class=cF0>;
<a name="l705"></a>        </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>Bt</span><span class=cF7>(</span><span class=cF0>src,          k</span><span class=cF7>)</span><span class=cF0>) c |= </span><span class=cFE>1</span><span class=cF0>;
<a name="l706"></a>        </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>Bt</span><span class=cF7>(</span><span class=cF0>src + i1,     k</span><span class=cF7>)</span><span class=cF0>) c |= </span><span class=cFE>2</span><span class=cF0>;
<a name="l707"></a>        </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>Bt</span><span class=cF7>(</span><span class=cF0>src + i1 * </span><span class=cFE>2</span><span class=cF0>, k</span><span class=cF7>)</span><span class=cF0>) c |= </span><span class=cFE>4</span><span class=cF0>;
<a name="l708"></a>        </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>Bt</span><span class=cF7>(</span><span class=cF0>src + i1 * </span><span class=cFE>3</span><span class=cF0>, k</span><span class=cF7>)</span><span class=cF0>) c |= </span><span class=cFE>8</span><span class=cF0>;
<a name="l709"></a>        </span><span class=cF1>if</span><span class=cF0> (c == bkcolor)        c  = </span><span class=cF3>TRANSPARENT</span><span class=cF0>;
<a name="l710"></a>        *dst++ = c;
<a name="l711"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l712"></a>
<a name="l713"></a>    </span><span class=cF1>return</span><span class=cF0> dst;
<a name="l714"></a>}
<a name="l715"></a>
<a name="l716"></a></span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF5>GrBitMap1ToBitMap8</span><span class=cF0>(</span><span class=cF1>U8</span><span class=cF0> *dst, </span><span class=cF1>U8</span><span class=cF0> *src, </span><span class=cF9>I64</span><span class=cF0> src_size, </span><span class=cF9>I64</span><span class=cF0> bkcolor)
<a name="l717"></a>{
<a name="l718"></a>    </span><span class=cF9>I64</span><span class=cF0> c, k, i = src_size * </span><span class=cFE>8</span><span class=cF0>;
<a name="l719"></a>
<a name="l720"></a>    </span><span class=cF1>for</span><span class=cF0> (k = </span><span class=cFE>0</span><span class=cF0>; k &lt; i; k++)
<a name="l721"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l722"></a>        c = </span><span class=cFE>0</span><span class=cF0>;
<a name="l723"></a>        </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>Bt</span><span class=cF7>(</span><span class=cF0>src, k</span><span class=cF7>)</span><span class=cF0>)   c = </span><span class=cF3>COLOR_MONO</span><span class=cF0>;
<a name="l724"></a>        </span><span class=cF1>if</span><span class=cF0> (c == bkcolor) c = </span><span class=cF3>TRANSPARENT</span><span class=cF0>;
<a name="l725"></a>        *dst++ = c;
<a name="l726"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l727"></a>
<a name="l728"></a>    </span><span class=cF1>return</span><span class=cF0> dst;
<a name="l729"></a>}
<a name="l730"></a>
<a name="l731"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF9>CDC</span><span class=cF0> *</span><span class=cF5>DCExt</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc=</span><span class=cFB>gr</span><span class=cF0>.dc, </span><span class=cF9>I64</span><span class=cF0> x1, </span><span class=cF9>I64</span><span class=cF0> y1, </span><span class=cF9>I64</span><span class=cF0> x2, </span><span class=cF9>I64</span><span class=cF0> y2, </span><span class=cF9>CTask</span><span class=cF0> *task=</span><span class=cF3>NULL</span><span class=cF0>)
<a name="l732"></a>{</span><span class=cF2>//Extract new device context rect from device context.</span><span class=cF0>
<a name="l733"></a>    </span><span class=cF9>CDC</span><span class=cF0>   *res;
<a name="l734"></a>    </span><span class=cF9>CTask</span><span class=cF0> *win_task;
<a name="l735"></a>
<a name="l736"></a>    </span><span class=cF1>if</span><span class=cF0> (x1 &gt; x2)
<a name="l737"></a>        </span><span class=cF5>SwapI64</span><span class=cF0>(&amp;x1, &amp;x2);
<a name="l738"></a>    </span><span class=cF1>if</span><span class=cF0> (y1 &gt; y2)
<a name="l739"></a>        </span><span class=cF5>SwapI64</span><span class=cF0>(&amp;y1, &amp;y2);
<a name="l740"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l741"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l742"></a>        win_task = dc-&gt;win_task;
<a name="l743"></a>        x1 += win_task-&gt;pix_left + win_task-&gt;scroll_x;
<a name="l744"></a>        y1 += win_task-&gt;pix_top  + win_task-&gt;scroll_y;
<a name="l745"></a>        x2 += win_task-&gt;pix_left + win_task-&gt;scroll_x;
<a name="l746"></a>        y2 += win_task-&gt;pix_top  + win_task-&gt;scroll_y;
<a name="l747"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l748"></a>    res = </span><span class=cF5>DCNew</span><span class=cF0>(x2 - x1 + </span><span class=cFE>1</span><span class=cF0>, y2 -y1 + </span><span class=cFE>1</span><span class=cF0>, task);
<a name="l749"></a>    </span><span class=cF5>DCFill</span><span class=cF0>(res);
<a name="l750"></a>    </span><span class=cF5>GrBlot</span><span class=cF0>(res, -x1, -y1, dc);
<a name="l751"></a>
<a name="l752"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l753"></a>}
<a name="l754"></a>
<a name="l755"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF9>CDC</span><span class=cF0> *</span><span class=cF5>DCDiff</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *base, </span><span class=cF9>CDC</span><span class=cF0> *update)
<a name="l756"></a>{</span><span class=cF2>//Trim to win of what has chged.</span><span class=cF0>
<a name="l757"></a>    </span><span class=cF9>I64</span><span class=cF0>  i, x1 = </span><span class=cFE>0</span><span class=cF0>, y1 = </span><span class=cFE>0</span><span class=cF0>, x2 = update-&gt;width - </span><span class=cFE>1</span><span class=cF0>, y2 = update-&gt;height - </span><span class=cFE>1</span><span class=cF0>; </span><span class=cF2>//inclusive</span><span class=cF0>
<a name="l758"></a>    </span><span class=cF9>U32</span><span class=cF0> *ptr_base, *ptr_update;
<a name="l759"></a>    </span><span class=cF9>CDC</span><span class=cF0> *res;
<a name="l760"></a>
<a name="l761"></a>    ptr_base   = base-&gt;body;
<a name="l762"></a>    ptr_update = update-&gt;body;
<a name="l763"></a>    </span><span class=cF1>while</span><span class=cF0> (y1 &lt;= y2)
<a name="l764"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l765"></a>        i = update-&gt;width &gt;&gt; </span><span class=cFE>2</span><span class=cF0>;
<a name="l766"></a>        </span><span class=cF1>while</span><span class=cF0> (i--)
<a name="l767"></a>            </span><span class=cF1>if</span><span class=cF0> (*ptr_base++ != *ptr_update++)
<a name="l768"></a>                </span><span class=cF1>goto</span><span class=cF0> df_y2;
<a name="l769"></a>        i = update-&gt;width &amp; </span><span class=cFE>3</span><span class=cF0>;
<a name="l770"></a>        </span><span class=cF1>while</span><span class=cF0> (i--)
<a name="l771"></a>            </span><span class=cF1>if</span><span class=cF0> (*ptr_base</span><span class=cF7>(</span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++ != *ptr_update</span><span class=cF7>(</span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++)
<a name="l772"></a>                </span><span class=cF1>goto</span><span class=cF0> df_y2;
<a name="l773"></a>        y1++;
<a name="l774"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l775"></a>    </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l776"></a>df_y2:
<a name="l777"></a>    ptr_base   = base-&gt;body   + base-&gt;width_internal    * base-&gt;height;
<a name="l778"></a>    ptr_update = update-&gt;body + update-&gt;width_internal  * update-&gt;height;
<a name="l779"></a>    </span><span class=cF1>while</span><span class=cF0> (y1 &lt; y2)
<a name="l780"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l781"></a>        i = update-&gt;width &gt;&gt; </span><span class=cFE>2</span><span class=cF0>;
<a name="l782"></a>        </span><span class=cF1>while</span><span class=cF0> (i--)
<a name="l783"></a>            </span><span class=cF1>if</span><span class=cF0> (*--ptr_base != *--ptr_update)
<a name="l784"></a>                </span><span class=cF1>goto</span><span class=cF0> df_x1;
<a name="l785"></a>        i = update-&gt;width &amp; </span><span class=cFE>3</span><span class=cF0>;
<a name="l786"></a>        </span><span class=cF1>while</span><span class=cF0> (i--)
<a name="l787"></a>            </span><span class=cF1>if</span><span class=cF0> (*--ptr_base</span><span class=cF7>(</span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> != *--ptr_update</span><span class=cF7>(</span><span class=cF1>U8</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>)
<a name="l788"></a>                </span><span class=cF1>goto</span><span class=cF0> df_x1;
<a name="l789"></a>        y2--;
<a name="l790"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l791"></a>df_x1:
<a name="l792"></a>    </span><span class=cF1>while</span><span class=cF0> (x1 &lt; x2)
<a name="l793"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l794"></a>        </span><span class=cF1>for</span><span class=cF0> (i = y1; i &lt;= y2; i++)
<a name="l795"></a>            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>GrPeek0</span><span class=cF7>(</span><span class=cF0>base, x1, i</span><span class=cF7>)</span><span class=cF0> != </span><span class=cF5>GrPeek0</span><span class=cF7>(</span><span class=cF0>update, x1, i</span><span class=cF7>)</span><span class=cF0>)
<a name="l796"></a>                 </span><span class=cF1>goto</span><span class=cF0> df_x2;
<a name="l797"></a>        x1++;
<a name="l798"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l799"></a>df_x2:
<a name="l800"></a>    </span><span class=cF1>while</span><span class=cF0> (x1 &lt; x2)
<a name="l801"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l802"></a>        </span><span class=cF1>for</span><span class=cF0> (i = y1; i &lt;= y2; i++)
<a name="l803"></a>            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>GrPeek0</span><span class=cF7>(</span><span class=cF0>base, x2, i</span><span class=cF7>)</span><span class=cF0> != </span><span class=cF5>GrPeek0</span><span class=cF7>(</span><span class=cF0>update, x2, i</span><span class=cF7>)</span><span class=cF0>)
<a name="l804"></a>                 </span><span class=cF1>goto</span><span class=cF0> df_done;
<a name="l805"></a>        x2--;
<a name="l806"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l807"></a>df_done:
<a name="l808"></a>    res = </span><span class=cF5>DCExt</span><span class=cF0>(update, x1, y1, x2, y2);
<a name="l809"></a>    res-&gt;x0 = x1;
<a name="l810"></a>    res-&gt;y0 = y1;
<a name="l811"></a>
<a name="l812"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l813"></a>}
<a name="l814"></a>
<a name="l815"></a>#</span><span class=cF1>help_index</span><span class=cF0> </span><span class=cF6>&quot;Graphics/Char;Char/Graphics&quot;</span><span class=cF0>
<a name="l816"></a>
<a name="l817"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>GrPutChar</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc=</span><span class=cFB>gr</span><span class=cF0>.dc, </span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y, </span><span class=cF1>U8</span><span class=cF0> ch)
<a name="l818"></a>{</span><span class=cF2>//2D. Clipping but not transformation.</span><span class=cF0>
<a name="l819"></a>    </span><span class=cF1>U8</span><span class=cF0>          </span><span class=cF1>reg</span><span class=cF0> *src, </span><span class=cF1>reg</span><span class=cF0> *dst, *font_ptr;
<a name="l820"></a>    </span><span class=cF9>I64</span><span class=cF0>              i, m, leading_pixels, trailing_pixels, leading_pixel_mask, trailing_pixel_mask, 
<a name="l821"></a>                     j, k1, kk1, w1, h1, w2, h2, </span><span class=cF1>reg</span><span class=cF0> bit_shift, </span><span class=cF1>reg</span><span class=cF0> color_mask, dist;
<a name="l822"></a>    </span><span class=cF9>CColorROPU32</span><span class=cF0>     color, c;
<a name="l823"></a>    </span><span class=cF9>CTask</span><span class=cF0>           *win_task;
<a name="l824"></a>
<a name="l825"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l826"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l827"></a>        win_task = dc-&gt;win_task;
<a name="l828"></a>        x += win_task-&gt;scroll_x;
<a name="l829"></a>        y += win_task-&gt;scroll_y;
<a name="l830"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l831"></a>
<a name="l832"></a>    </span><span class=cF1>if</span><span class=cF0> (x &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l833"></a>        w1 = -x;
<a name="l834"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l835"></a>        w1 = </span><span class=cFE>0</span><span class=cF0>;
<a name="l836"></a>    </span><span class=cF1>if</span><span class=cF0> (y &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l837"></a>        h1 = -y;
<a name="l838"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l839"></a>        h1 = </span><span class=cFE>0</span><span class=cF0>;
<a name="l840"></a>    w2 = </span><span class=cF3>FONT_WIDTH</span><span class=cF0>;
<a name="l841"></a>    h2 = </span><span class=cF3>FONT_HEIGHT</span><span class=cF0>;
<a name="l842"></a>
<a name="l843"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l844"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l845"></a>        x += win_task-&gt;pix_left;
<a name="l846"></a>        y += win_task-&gt;pix_top;
<a name="l847"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l848"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_LOCATE_NEAREST</span><span class=cF0>)
<a name="l849"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l850"></a>        dist = </span><span class=cF5>DistSqrI64</span><span class=cF0>(x + w2 &gt;&gt; </span><span class=cFE>1</span><span class=cF0>, y + h2 &gt;&gt; </span><span class=cFE>1</span><span class=cF0>, dc-&gt;cur_x, dc-&gt;cur_y);
<a name="l851"></a>        </span><span class=cF1>if</span><span class=cF0> (dist &lt;= dc-&gt;nearest_dist)
<a name="l852"></a>            dc-&gt;nearest_dist = dist;
<a name="l853"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l854"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l855"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l856"></a>        </span><span class=cF1>if</span><span class=cF0> (x + w1 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l857"></a>            w1 = -x;
<a name="l858"></a>        </span><span class=cF1>if</span><span class=cF0> (x + w2 &gt; win_task-&gt;pix_right + </span><span class=cFE>1</span><span class=cF0>)
<a name="l859"></a>            w2 = win_task-&gt;pix_right + </span><span class=cFE>1</span><span class=cF0> - x;
<a name="l860"></a>
<a name="l861"></a>        </span><span class=cF1>if</span><span class=cF0> (y + h1 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l862"></a>            h1 = -y;
<a name="l863"></a>        </span><span class=cF1>if</span><span class=cF0> (y + h2 &gt; win_task-&gt;pix_bottom + </span><span class=cFE>1</span><span class=cF0>)
<a name="l864"></a>            h2 = win_task-&gt;pix_bottom + </span><span class=cFE>1</span><span class=cF0> - y;
<a name="l865"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l866"></a>    </span><span class=cF1>if</span><span class=cF0> (x + w2 &gt; dc-&gt;width)
<a name="l867"></a>        w2 = dc-&gt;width - x;
<a name="l868"></a>    </span><span class=cF1>if</span><span class=cF0> (y + h2&gt;dc-&gt;height)
<a name="l869"></a>        h2 = dc-&gt;height - y;
<a name="l870"></a>    </span><span class=cF1>if</span><span class=cF0> (w1 &lt; w2 &lt;= </span><span class=cF3>FONT_WIDTH</span><span class=cF0> &amp;&amp; h1 &lt; h2 &lt;= </span><span class=cF3>FONT_HEIGHT</span><span class=cF0>)
<a name="l871"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l872"></a>        </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_RECORD_EXTENTS</span><span class=cF0>)
<a name="l873"></a>        {
<a name="l874"></a>            </span><span class=cF1>if</span><span class=cF0> (x + w1 &lt; dc-&gt;min_x)
<a name="l875"></a>                dc-&gt;min_x = x + w1;
<a name="l876"></a>
<a name="l877"></a>            </span><span class=cF1>if</span><span class=cF0> (x + w2 - </span><span class=cFE>1</span><span class=cF0> &gt; dc-&gt;max_x)
<a name="l878"></a>                dc-&gt;max_x = x + w2 - </span><span class=cFE>1</span><span class=cF0>;
<a name="l879"></a>
<a name="l880"></a>            </span><span class=cF1>if</span><span class=cF0> (y + h1  &lt; dc-&gt;min_y)
<a name="l881"></a>                dc-&gt;min_y = y + h1;
<a name="l882"></a>
<a name="l883"></a>            </span><span class=cF1>if</span><span class=cF0> (y + h2 - </span><span class=cFE>1</span><span class=cF0> &gt; dc-&gt;max_y)
<a name="l884"></a>                dc-&gt;max_y = y + h2 - </span><span class=cFE>1</span><span class=cF0>;
<a name="l885"></a>        }
<a name="l886"></a>        </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_DONT_DRAW</span><span class=cF0>)
<a name="l887"></a>            </span><span class=cF1>return</span><span class=cF0> </span><span class=cFE>1</span><span class=cF0>;
<a name="l888"></a>        color = dc-&gt;color;
<a name="l889"></a>        leading_pixels = -(w1 + x) &amp; </span><span class=cFE>7</span><span class=cF0>;
<a name="l890"></a>        </span><span class=cF1>if</span><span class=cF0> (!leading_pixels)
<a name="l891"></a>            leading_pixels = </span><span class=cFE>8</span><span class=cF0>;
<a name="l892"></a>        leading_pixel_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[</span><span class=cFE>0xFF</span><span class=cF0> &gt;&gt; leading_pixels];
<a name="l893"></a>        bit_shift = -x &amp; </span><span class=cFE>7</span><span class=cF0>;
<a name="l894"></a>        trailing_pixels = (x + w2) &amp; </span><span class=cFE>7</span><span class=cF0>;
<a name="l895"></a>        trailing_pixel_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[</span><span class=cFE>0xFF</span><span class=cF0> &lt;&lt; trailing_pixels &amp; </span><span class=cFE>0xFF</span><span class=cF0>];
<a name="l896"></a>        </span><span class=cF1>if</span><span class=cF0> (leading_pixels + trailing_pixels &gt; w2 - w1)
<a name="l897"></a>        {
<a name="l898"></a>            leading_pixel_mask |= trailing_pixel_mask;
<a name="l899"></a>            trailing_pixels = </span><span class=cFE>0</span><span class=cF0>;
<a name="l900"></a>        }
<a name="l901"></a>        font_ptr = &amp;</span><span class=cFB>text</span><span class=cF0>.font(</span><span class=cF1>U8</span><span class=cF0> *)[</span><span class=cF3>FONT_HEIGHT</span><span class=cF0> * ch + h1];
<a name="l902"></a>        </span><span class=cF1>if</span><span class=cF0> (color.c0.rop == </span><span class=cF3>ROPB_COLLISION</span><span class=cF0>)
<a name="l903"></a>        {
<a name="l904"></a>            m = w1 &amp; (</span><span class=cF3>FONT_WIDTH</span><span class=cF0> - </span><span class=cFE>1</span><span class=cF0>);
<a name="l905"></a>#</span><span class=cF1>assert</span><span class=cF0> </span><span class=cF3>FONT_WIDTH</span><span class=cF0> == </span><span class=cFE>8</span><span class=cF0>
<a name="l906"></a>            color =dc-&gt;bkcolor.c0.color;
<a name="l907"></a>            </span><span class=cF1>for</span><span class=cF0> (i = w1; i &lt; w2; i++, m++)
<a name="l908"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l909"></a>                k1 = (h1 + y) * dc-&gt;width_internal + x;
<a name="l910"></a>                src = font_ptr;
<a name="l911"></a>                </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l912"></a>                {
<a name="l913"></a>                    c = dc-&gt;body[k1 + i];
<a name="l914"></a>                    </span><span class=cF1>if</span><span class=cF0> (c != </span><span class=cF3>TRANSPARENT</span><span class=cF0> &amp;&amp; c != color &amp;&amp; </span><span class=cF5>Bt</span><span class=cF7>(</span><span class=cF0>src, m</span><span class=cF7>)</span><span class=cF0>)
<a name="l915"></a>                        dc-&gt;collision_count++;
<a name="l916"></a>                    k1 += dc-&gt;width_internal;
<a name="l917"></a>                    src++;
<a name="l918"></a>                }
<a name="l919"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l920"></a>        }
<a name="l921"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l922"></a>        {
<a name="l923"></a>            color_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c0.color];
<a name="l924"></a>            k1 = x + w1;
<a name="l925"></a>            kk1 = (h1 + y) * dc-&gt;width_internal + k1;
<a name="l926"></a>            </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF7>)</span><span class=cF0> || dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF0>)
<a name="l927"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l928"></a>                </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l929"></a>                {
<a name="l930"></a>                    dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l931"></a>                    src = font_ptr;
<a name="l932"></a>                    </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l933"></a>                        src--;
<a name="l934"></a>                    </span><span class=cF1>switch</span><span class=cF0> [color.c0.rop]
<a name="l935"></a>                    </span><span class=cF7>{</span><span class=cF0>
<a name="l936"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_EQU</span><span class=cF0>:
<a name="l937"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_MONO</span><span class=cF0>:
<a name="l938"></a>                            </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l939"></a>                            {
<a name="l940"></a>                                m = </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[*src(</span><span class=cF9>U16</span><span class=cF0> *) &gt;&gt; bit_shift &amp; </span><span class=cFE>0xFF</span><span class=cF0>];
<a name="l941"></a>                                *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l942"></a>                                             (color_mask &amp; m | *dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &amp; ~m) &amp; ~leading_pixel_mask;
<a name="l943"></a>                                src++;
<a name="l944"></a>                                dst += dc-&gt;width_internal;
<a name="l945"></a>                            }
<a name="l946"></a>                            </span><span class=cF1>break</span><span class=cF0>;
<a name="l947"></a>
<a name="l948"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_XOR</span><span class=cF0>:
<a name="l949"></a>                            </span><span class=cF1>if</span><span class=cF0> (color_mask)
<a name="l950"></a>                            {
<a name="l951"></a>                                </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l952"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l953"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l954"></a>                                                 (*dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> ^ </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[*src</span><span class=cF7>(</span><span class=cF9>U16</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &gt;&gt; bit_shift &amp; </span><span class=cFE>0xFF</span><span class=cF0>]) &amp;
<a name="l955"></a>                                                  ~leading_pixel_mask;
<a name="l956"></a>                                    src++;
<a name="l957"></a>                                    dst += dc-&gt;width_internal;
<a name="l958"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l959"></a>                            }
<a name="l960"></a>                            </span><span class=cF1>break</span><span class=cF0>;
<a name="l961"></a>                    </span><span class=cF7>}</span><span class=cF0>
<a name="l962"></a>                    kk1 += </span><span class=cFE>8</span><span class=cF0>;
<a name="l963"></a>                }
<a name="l964"></a>                </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l965"></a>                {
<a name="l966"></a>                    dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l967"></a>                    src = font_ptr + </span><span class=cFE>1</span><span class=cF0>;
<a name="l968"></a>                    </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l969"></a>                        src--;
<a name="l970"></a>                    </span><span class=cF1>switch</span><span class=cF0> [color.c0.rop]
<a name="l971"></a>                    </span><span class=cF7>{</span><span class=cF0>
<a name="l972"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_EQU</span><span class=cF0>:
<a name="l973"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_MONO</span><span class=cF0>:
<a name="l974"></a>                            </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l975"></a>                            {
<a name="l976"></a>                                m = </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[*src(</span><span class=cF9>U16</span><span class=cF0> *) &gt;&gt; bit_shift &amp; </span><span class=cFE>0xFF</span><span class=cF0>];
<a name="l977"></a>                                *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l978"></a>                                             (color_mask &amp; m | *dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &amp; ~m) &amp; ~trailing_pixel_mask;
<a name="l979"></a>                                src++;
<a name="l980"></a>                                dst += dc-&gt;width_internal;
<a name="l981"></a>                            }
<a name="l982"></a>                            </span><span class=cF1>break</span><span class=cF0>;
<a name="l983"></a>
<a name="l984"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_XOR</span><span class=cF0>:
<a name="l985"></a>                            </span><span class=cF1>if</span><span class=cF0> (color_mask)
<a name="l986"></a>                                </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l987"></a>                                {
<a name="l988"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l989"></a>                                                 (*dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> ^ </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[*src</span><span class=cF7>(</span><span class=cF9>U16</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &gt;&gt; bit_shift &amp; </span><span class=cFE>0xFF</span><span class=cF0>]) &amp;
<a name="l990"></a>                                                  ~trailing_pixel_mask;
<a name="l991"></a>                                    src++;
<a name="l992"></a>                                    dst += dc-&gt;width_internal;
<a name="l993"></a>                                }
<a name="l994"></a>                            </span><span class=cF1>break</span><span class=cF0>;
<a name="l995"></a>                    </span><span class=cF7>}</span><span class=cF0>
<a name="l996"></a>                }
<a name="l997"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l998"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l999"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1000"></a>                </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l1001"></a>                {
<a name="l1002"></a>                    dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l1003"></a>                    src = font_ptr;
<a name="l1004"></a>                    </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l1005"></a>                        src--;
<a name="l1006"></a>                    </span><span class=cF1>switch</span><span class=cF0> [color.c0.rop]
<a name="l1007"></a>                    </span><span class=cF7>{</span><span class=cF0>
<a name="l1008"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_EQU</span><span class=cF0>:
<a name="l1009"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_MONO</span><span class=cF0>:
<a name="l1010"></a>                            </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l1011"></a>                            {
<a name="l1012"></a>                                </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF5>IsPixCovered0</span><span class=cF7>(</span><span class=cF0>win_task, k1, y + j</span><span class=cF7>)</span><span class=cF0>)
<a name="l1013"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l1014"></a>                                    m = </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[*src(</span><span class=cF9>U16</span><span class=cF0> *) &gt;&gt; bit_shift &amp; </span><span class=cFE>0xFF</span><span class=cF0>];
<a name="l1015"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l1016"></a>                                                 (color_mask &amp; m | *dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &amp; ~m) &amp; ~leading_pixel_mask;
<a name="l1017"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l1018"></a>                                src++;
<a name="l1019"></a>                                dst += dc-&gt;width_internal;
<a name="l1020"></a>                            }
<a name="l1021"></a>                            </span><span class=cF1>break</span><span class=cF0>;
<a name="l1022"></a>
<a name="l1023"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_XOR</span><span class=cF0>:
<a name="l1024"></a>                            </span><span class=cF1>if</span><span class=cF0> (color_mask)
<a name="l1025"></a>                                </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l1026"></a>                                {
<a name="l1027"></a>                                    </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF5>IsPixCovered0</span><span class=cF7>(</span><span class=cF0>win_task, k1, y + j</span><span class=cF7>)</span><span class=cF0>)
<a name="l1028"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l1029"></a>                                                     (*dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> ^ </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[*src</span><span class=cF7>(</span><span class=cF9>U16</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &gt;&gt; bit_shift &amp; </span><span class=cFE>0xFF</span><span class=cF0>]) &amp;
<a name="l1030"></a>                                                      ~leading_pixel_mask;
<a name="l1031"></a>                                    src++;
<a name="l1032"></a>                                    dst += dc-&gt;width_internal;
<a name="l1033"></a>                                }
<a name="l1034"></a>                            </span><span class=cF1>break</span><span class=cF0>;
<a name="l1035"></a>                    </span><span class=cF7>}</span><span class=cF0>
<a name="l1036"></a>                    k1 += </span><span class=cFE>8</span><span class=cF0>;
<a name="l1037"></a>                    kk1 += </span><span class=cFE>8</span><span class=cF0>;
<a name="l1038"></a>                }
<a name="l1039"></a>                </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l1040"></a>                {
<a name="l1041"></a>                    dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l1042"></a>                    src = font_ptr + </span><span class=cFE>1</span><span class=cF0>;
<a name="l1043"></a>                    </span><span class=cF1>if</span><span class=cF0> (bit_shift)
<a name="l1044"></a>                        src--;
<a name="l1045"></a>                    </span><span class=cF1>switch</span><span class=cF0> [color.c0.rop]
<a name="l1046"></a>                    </span><span class=cF7>{</span><span class=cF0>
<a name="l1047"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_EQU</span><span class=cF0>:
<a name="l1048"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_MONO</span><span class=cF0>:
<a name="l1049"></a>                            </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l1050"></a>                            {
<a name="l1051"></a>                                </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF5>IsPixCovered0</span><span class=cF7>(</span><span class=cF0>win_task, k1, y + j</span><span class=cF7>)</span><span class=cF0>)
<a name="l1052"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l1053"></a>                                    m = </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[*src(</span><span class=cF9>U16</span><span class=cF0> *) &gt;&gt; bit_shift &amp; </span><span class=cFE>0xFF</span><span class=cF0>];
<a name="l1054"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l1055"></a>                                                 (color_mask &amp; m | *dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &amp; ~m) &amp; ~trailing_pixel_mask;
<a name="l1056"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l1057"></a>                                src++;
<a name="l1058"></a>                                dst += dc-&gt;width_internal;
<a name="l1059"></a>                            }
<a name="l1060"></a>                            </span><span class=cF1>break</span><span class=cF0>;
<a name="l1061"></a>
<a name="l1062"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_XOR</span><span class=cF0>:
<a name="l1063"></a>                            </span><span class=cF1>if</span><span class=cF0> (color_mask)
<a name="l1064"></a>                                </span><span class=cF1>for</span><span class=cF0> (j  =h1; j &lt; h2; j++)
<a name="l1065"></a>                                {
<a name="l1066"></a>                                    </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF5>IsPixCovered0</span><span class=cF7>(</span><span class=cF0>win_task, k1, y + j</span><span class=cF7>)</span><span class=cF0>)
<a name="l1067"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l1068"></a>                                                     (*dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> ^ </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[*src</span><span class=cF7>(</span><span class=cF9>U16</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> &gt;&gt; bit_shift &amp; </span><span class=cFE>0xFF</span><span class=cF0>]) &amp;
<a name="l1069"></a>                                                      ~trailing_pixel_mask;
<a name="l1070"></a>                                    src++;
<a name="l1071"></a>                                    dst += dc-&gt;width_internal;
<a name="l1072"></a>                                }
<a name="l1073"></a>                            </span><span class=cF1>break</span><span class=cF0>;
<a name="l1074"></a>                    </span><span class=cF7>}</span><span class=cF0>
<a name="l1075"></a>                }
<a name="l1076"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1077"></a>        }
<a name="l1078"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cFE>1</span><span class=cF0>;
<a name="l1079"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1080"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l1081"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cFE>0</span><span class=cF0>;
<a name="l1082"></a>}
<a name="l1083"></a>
<a name="l1084"></a></span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>GrPutS</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc=</span><span class=cFB>gr</span><span class=cF0>.dc, </span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y, </span><span class=cF1>U8</span><span class=cF0> *_s)
<a name="l1085"></a>{</span><span class=cF2>//Use </span><a href="https://tomawezome.github.io/ZealOS/System/Gr/GrBitMap.html#l1194"><span class=cF4>GrPrint</span></a><span class=cF2>()</span><span class=cF0>
<a name="l1086"></a>    </span><span class=cF9>I64</span><span class=cF0> x0, sx = </span><span class=cFE>0</span><span class=cF0>, sy = </span><span class=cFE>0</span><span class=cF0>, res;
<a name="l1087"></a>
<a name="l1088"></a>    </span><span class=cF1>if</span><span class=cF0> (!_s)
<a name="l1089"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cFE>0</span><span class=cF0>;
<a name="l1090"></a>    x0 = x;
<a name="l1091"></a>    res = </span><span class=cFE>0</span><span class=cF0>;
<a name="l1092"></a>    </span><span class=cF1>while</span><span class=cF0> (*_s)
<a name="l1093"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l1094"></a>        </span><span class=cF1>if</span><span class=cF0> (*_s == </span><span class=cF6>'\n'</span><span class=cF0>)
<a name="l1095"></a>        {
<a name="l1096"></a>            x = x0;
<a name="l1097"></a>            y += </span><span class=cF3>FONT_HEIGHT</span><span class=cF0>;
<a name="l1098"></a>            _s++;
<a name="l1099"></a>        }
<a name="l1100"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (*_s == </span><span class=cF6>'\t'</span><span class=cF0>)
<a name="l1101"></a>        {
<a name="l1102"></a>            x = x0 + </span><span class=cF5>CeilU64</span><span class=cF0>(x - x0 + </span><span class=cF3>FONT_WIDTH</span><span class=cF0>, </span><span class=cFE>8</span><span class=cF0> * </span><span class=cF3>FONT_WIDTH</span><span class=cF0>);
<a name="l1103"></a>            _s++;
<a name="l1104"></a>        }
<a name="l1105"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (*_s</span><span class=cF7>(</span><span class=cF9>U32</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> == </span><span class=cF6>'$SY,'</span><span class=cF0>)
<a name="l1106"></a>        {
<a name="l1107"></a>            </span><span class=cF1>if</span><span class=cF0> (_s[</span><span class=cFE>4</span><span class=cF0>] == </span><span class=cF6>'-'</span><span class=cF0>)
<a name="l1108"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1109"></a>                _s++;
<a name="l1110"></a>                sy = </span><span class=cF6>'0'</span><span class=cF0> - _s[</span><span class=cFE>4</span><span class=cF0>];
<a name="l1111"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1112"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l1113"></a>                sy = _s[</span><span class=cFE>4</span><span class=cF0>] - </span><span class=cF6>'0'</span><span class=cF0>;
<a name="l1114"></a>            _s += </span><span class=cFE>6</span><span class=cF0>;
<a name="l1115"></a>        }
<a name="l1116"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (*_s</span><span class=cF7>(</span><span class=cF9>U32</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> == </span><span class=cF6>'$SX,'</span><span class=cF0>)
<a name="l1117"></a>        {
<a name="l1118"></a>            </span><span class=cF1>if</span><span class=cF0> (_s[</span><span class=cFE>4</span><span class=cF0>] == </span><span class=cF6>'-'</span><span class=cF0>)
<a name="l1119"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1120"></a>                _s++;
<a name="l1121"></a>                sx = </span><span class=cF6>'0'</span><span class=cF0> - _s[</span><span class=cFE>4</span><span class=cF0>];
<a name="l1122"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1123"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l1124"></a>                sx = _s[</span><span class=cFE>4</span><span class=cF0>] - </span><span class=cF6>'0'</span><span class=cF0>;
<a name="l1125"></a>            _s += </span><span class=cFE>6</span><span class=cF0>;
<a name="l1126"></a>        }
<a name="l1127"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l1128"></a>        {
<a name="l1129"></a>            res += </span><span class=cF5>GrPutChar</span><span class=cF0>(dc, x + sx, y + sy, *_s);
<a name="l1130"></a>            x += </span><span class=cF3>FONT_WIDTH</span><span class=cF0>;
<a name="l1131"></a>            _s++;
<a name="l1132"></a>        }
<a name="l1133"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1134"></a>
<a name="l1135"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l1136"></a>}
<a name="l1137"></a>
<a name="l1138"></a></span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>GrVPutS</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc=</span><span class=cFB>gr</span><span class=cF0>.dc, </span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y, </span><span class=cF1>U8</span><span class=cF0> *_s)
<a name="l1139"></a>{</span><span class=cF2>//Vertical Text.  Use </span><a href="https://tomawezome.github.io/ZealOS/System/Gr/GrBitMap.html#l1205"><span class=cF4>GrVPrint</span></a><span class=cF2>()</span><span class=cF0>
<a name="l1140"></a>    </span><span class=cF9>I64</span><span class=cF0> y0, sx = </span><span class=cFE>0</span><span class=cF0>, sy = </span><span class=cFE>0</span><span class=cF0>, res;
<a name="l1141"></a>    </span><span class=cF1>U8</span><span class=cF0>  buf[</span><span class=cFE>2</span><span class=cF0>];
<a name="l1142"></a>
<a name="l1143"></a>    </span><span class=cF1>if</span><span class=cF0> (!_s)
<a name="l1144"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cFE>0</span><span class=cF0>;
<a name="l1145"></a>    y0 = y;
<a name="l1146"></a>    res = </span><span class=cFE>0</span><span class=cF0>;
<a name="l1147"></a>    buf[</span><span class=cFE>1</span><span class=cF0>] = </span><span class=cFE>0</span><span class=cF0>;
<a name="l1148"></a>    </span><span class=cF1>while</span><span class=cF0> (*_s)
<a name="l1149"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l1150"></a>        </span><span class=cF1>if</span><span class=cF0> (*_s == </span><span class=cF6>'\n'</span><span class=cF0>)
<a name="l1151"></a>        {
<a name="l1152"></a>            y = y0;
<a name="l1153"></a>            x += </span><span class=cF3>FONT_WIDTH</span><span class=cF0>;
<a name="l1154"></a>            _s++;
<a name="l1155"></a>        }
<a name="l1156"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (*_s == </span><span class=cF6>'\t'</span><span class=cF0>)
<a name="l1157"></a>        {
<a name="l1158"></a>            y = y0 + </span><span class=cF5>CeilU64</span><span class=cF0>(y - y0 + </span><span class=cF3>FONT_HEIGHT</span><span class=cF0>, </span><span class=cFE>8</span><span class=cF0> * </span><span class=cF3>FONT_HEIGHT</span><span class=cF0>);
<a name="l1159"></a>            _s++;
<a name="l1160"></a>        }
<a name="l1161"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (*_s</span><span class=cF7>(</span><span class=cF9>U32</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> == </span><span class=cF6>'$SY,'</span><span class=cF0>)
<a name="l1162"></a>        {
<a name="l1163"></a>            </span><span class=cF1>if</span><span class=cF0> (_s[</span><span class=cFE>4</span><span class=cF0>] == </span><span class=cF6>'-'</span><span class=cF0>)
<a name="l1164"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1165"></a>                _s++;
<a name="l1166"></a>                sx = </span><span class=cF6>'0'</span><span class=cF0> - _s[</span><span class=cFE>4</span><span class=cF0>];
<a name="l1167"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1168"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l1169"></a>                sx = _s[</span><span class=cFE>4</span><span class=cF0>] - </span><span class=cF6>'0'</span><span class=cF0>;
<a name="l1170"></a>            _s += </span><span class=cFE>6</span><span class=cF0>;
<a name="l1171"></a>        }
<a name="l1172"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (*_s</span><span class=cF7>(</span><span class=cF9>U32</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0> == </span><span class=cF6>'$SX,'</span><span class=cF0>)
<a name="l1173"></a>        {
<a name="l1174"></a>            </span><span class=cF1>if</span><span class=cF0> (_s[</span><span class=cFE>4</span><span class=cF0>] == </span><span class=cF6>'-'</span><span class=cF0>)
<a name="l1175"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1176"></a>                _s++;
<a name="l1177"></a>                sy = </span><span class=cF6>'0'</span><span class=cF0> - _s[</span><span class=cFE>4</span><span class=cF0>];
<a name="l1178"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1179"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l1180"></a>                sy = _s[</span><span class=cFE>4</span><span class=cF0>] - </span><span class=cF6>'0'</span><span class=cF0>;
<a name="l1181"></a>            _s += </span><span class=cFE>6</span><span class=cF0>;
<a name="l1182"></a>        }
<a name="l1183"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l1184"></a>        {
<a name="l1185"></a>            *buf = *_s++;
<a name="l1186"></a>            res += </span><span class=cF5>GrPutS</span><span class=cF0>(dc, x, y, buf);
<a name="l1187"></a>            y += </span><span class=cF3>FONT_HEIGHT</span><span class=cF0>;
<a name="l1188"></a>        }
<a name="l1189"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1190"></a>
<a name="l1191"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l1192"></a>}
<a name="l1193"></a>
<a name="l1194"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>GrPrint</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc=</span><span class=cFB>gr</span><span class=cF0>.dc, </span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y, </span><span class=cF1>U8</span><span class=cF0> *format, ...)
<a name="l1195"></a>{</span><span class=cF2>//2D. Clipping but not transformation.</span><span class=cF0>
<a name="l1196"></a>    </span><span class=cF9>I64</span><span class=cF0> res;
<a name="l1197"></a>    </span><span class=cF1>U8</span><span class=cF0> *buf = </span><span class=cF5>StrPrintJoin</span><span class=cF0>(</span><span class=cF3>NULL</span><span class=cF0>, format, argc, argv);
<a name="l1198"></a>
<a name="l1199"></a>    res = </span><span class=cF5>GrPutS</span><span class=cF0>(dc, x, y, buf);
<a name="l1200"></a>    </span><span class=cF5>Free</span><span class=cF0>(buf);
<a name="l1201"></a>
<a name="l1202"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l1203"></a>}
<a name="l1204"></a>
<a name="l1205"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>GrVPrint</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc=</span><span class=cFB>gr</span><span class=cF0>.dc, </span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y, </span><span class=cF1>U8</span><span class=cF0> *format, ...)
<a name="l1206"></a>{</span><span class=cF2>//2D. Vertical text. Clipping but not transformation.</span><span class=cF0>
<a name="l1207"></a>    </span><span class=cF9>I64</span><span class=cF0> res;
<a name="l1208"></a>    </span><span class=cF1>U8</span><span class=cF0> *buf = </span><span class=cF5>StrPrintJoin</span><span class=cF0>(</span><span class=cF3>NULL</span><span class=cF0>, format, argc, argv);
<a name="l1209"></a>
<a name="l1210"></a>    res = </span><span class=cF5>GrVPutS</span><span class=cF0>(dc, x, y, buf);
<a name="l1211"></a>    </span><span class=cF5>Free</span><span class=cF0>(buf);
<a name="l1212"></a>
<a name="l1213"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l1214"></a>}
<a name="l1215"></a>
<a name="l1216"></a>#</span><span class=cF1>help_index</span><span class=cF0> </span><span class=cF6>&quot;Graphics&quot;</span><span class=cF0>
<a name="l1217"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>GrRect</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc=</span><span class=cFB>gr</span><span class=cF0>.dc, </span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y, </span><span class=cF9>I64</span><span class=cF0> w, </span><span class=cF9>I64</span><span class=cF0> h)
<a name="l1218"></a>{</span><span class=cF2>//2D. Width Height. Clipping but not transformation.</span><span class=cF0>
<a name="l1219"></a></span><span class=cF2>//Returns count of pixs changed.</span><span class=cF0>
<a name="l1220"></a>    </span><span class=cF9>I64</span><span class=cF0>              i, res = </span><span class=cFE>0</span><span class=cF0>, j, k1, kk1, w1, h1, w2, h2, dist, 
<a name="l1221"></a>                     leading_pixels, original_leading_pixels, whole_I64s, 
<a name="l1222"></a>                     trailing_pixels, leading_pixel_mask, trailing_pixel_mask, 
<a name="l1223"></a>                     win_z_buf_line_inc, win_z_buf_line_dec, win_z_num, color_mask;
<a name="l1224"></a>    </span><span class=cF1>U8</span><span class=cF0>          </span><span class=cF1>reg</span><span class=cF0> *dst;
<a name="l1225"></a>    </span><span class=cF9>U16</span><span class=cF0>         </span><span class=cF1>reg</span><span class=cF0> *win_z_buf_ptr;
<a name="l1226"></a>    </span><span class=cF9>CColorROPU32</span><span class=cF0>     color, c, dither_colors;
<a name="l1227"></a>    </span><span class=cF1>Bool</span><span class=cF0>             dither, probability_dither, was_timer_rand = </span><span class=cF5>Bts</span><span class=cF0>(&amp;</span><span class=cF5>Fs</span><span class=cF0>-&gt;task_flags, </span><span class=cF3>TASKf_NONTIMER_RAND</span><span class=cF0>);
<a name="l1228"></a>    </span><span class=cF9>CTask</span><span class=cF0>           *win_task;
<a name="l1229"></a>
<a name="l1230"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l1231"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l1232"></a>        win_task = dc-&gt;win_task;
<a name="l1233"></a>        x += win_task-&gt;scroll_x;
<a name="l1234"></a>        y += win_task-&gt;scroll_y;
<a name="l1235"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1236"></a>
<a name="l1237"></a>    </span><span class=cF1>if</span><span class=cF0> (x &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l1238"></a>        w1 = -x;
<a name="l1239"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l1240"></a>        w1 = </span><span class=cFE>0</span><span class=cF0>;
<a name="l1241"></a>    </span><span class=cF1>if</span><span class=cF0> (y &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l1242"></a>        h1 = -y;
<a name="l1243"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l1244"></a>        h1 = </span><span class=cFE>0</span><span class=cF0>;
<a name="l1245"></a>    w2 = w;
<a name="l1246"></a>    h2 = h;
<a name="l1247"></a>
<a name="l1248"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l1249"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l1250"></a>        x += win_task-&gt;pix_left;
<a name="l1251"></a>        y += win_task-&gt;pix_top;
<a name="l1252"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1253"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_LOCATE_NEAREST</span><span class=cF0>)
<a name="l1254"></a>    </span><span class=cF7>{</span><span class=cF2>//TODO:Untested</span><span class=cF0>
<a name="l1255"></a>        </span><span class=cF1>if</span><span class=cF0> (x &lt;= dc-&gt;cur_x &lt;= x + w &amp;&amp; y &lt;= dc-&gt;cur_y &lt;= y + h)
<a name="l1256"></a>            dist = </span><span class=cFE>0</span><span class=cF0>;
<a name="l1257"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l1258"></a>            dist = </span><span class=cF5>DistSqrI64</span><span class=cF0>(x + w &gt;&gt; </span><span class=cFE>1</span><span class=cF0>, y + h &gt;&gt; </span><span class=cFE>1</span><span class=cF0>, dc-&gt;cur_x, dc-&gt;cur_y);
<a name="l1259"></a>        </span><span class=cF1>if</span><span class=cF0> (dist &lt;= dc-&gt;nearest_dist)
<a name="l1260"></a>            dc-&gt;nearest_dist = dist;
<a name="l1261"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1262"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l1263"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l1264"></a>        </span><span class=cF1>if</span><span class=cF0> (x + w1 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l1265"></a>            w1 = -x;
<a name="l1266"></a>        </span><span class=cF1>if</span><span class=cF0> (x + w2 &gt; win_task-&gt;pix_right + </span><span class=cFE>1</span><span class=cF0>)
<a name="l1267"></a>            w2 = win_task-&gt;pix_right + </span><span class=cFE>1</span><span class=cF0> - x;
<a name="l1268"></a>
<a name="l1269"></a>        </span><span class=cF1>if</span><span class=cF0> (y + h1 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l1270"></a>            h1 = -y;
<a name="l1271"></a>        </span><span class=cF1>if</span><span class=cF0> (y + h2 &gt; win_task-&gt;pix_bottom + </span><span class=cFE>1</span><span class=cF0>)
<a name="l1272"></a>            h2 = win_task-&gt;pix_bottom + </span><span class=cFE>1</span><span class=cF0> - y;
<a name="l1273"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1274"></a>    </span><span class=cF1>if</span><span class=cF0> (x + w2 &gt; dc-&gt;width)
<a name="l1275"></a>        w2 = dc-&gt;width - x;
<a name="l1276"></a>
<a name="l1277"></a>    </span><span class=cF1>if</span><span class=cF0> (y + h2 &gt; dc-&gt;height)
<a name="l1278"></a>        h2 = dc-&gt;height - y;
<a name="l1279"></a>
<a name="l1280"></a>    </span><span class=cF1>if</span><span class=cF0> (w1 &lt; w2 &lt;= w &amp;&amp; h1 &lt; h2 &lt;= h)
<a name="l1281"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l1282"></a>        </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_RECORD_EXTENTS</span><span class=cF0>)
<a name="l1283"></a>        {
<a name="l1284"></a>            </span><span class=cF1>if</span><span class=cF0> (x + w1  &lt; dc-&gt;min_x)
<a name="l1285"></a>                dc-&gt;min_x = x + w1;
<a name="l1286"></a>
<a name="l1287"></a>            </span><span class=cF1>if</span><span class=cF0> (x + w2 - </span><span class=cFE>1</span><span class=cF0> &gt; dc-&gt;max_x)
<a name="l1288"></a>                dc-&gt;max_x = x + w2 - </span><span class=cFE>1</span><span class=cF0>;
<a name="l1289"></a>
<a name="l1290"></a>            </span><span class=cF1>if</span><span class=cF0> (y + h1  &lt; dc-&gt;min_y)
<a name="l1291"></a>                dc-&gt;min_y = y + h1;
<a name="l1292"></a>
<a name="l1293"></a>            </span><span class=cF1>if</span><span class=cF0> (y + h2 - </span><span class=cFE>1</span><span class=cF0> &gt; dc-&gt;max_y)
<a name="l1294"></a>                dc-&gt;max_y = y + h2 - </span><span class=cFE>1</span><span class=cF0>;
<a name="l1295"></a>        }
<a name="l1296"></a>        </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_DONT_DRAW</span><span class=cF0>)
<a name="l1297"></a>            </span><span class=cF1>return</span><span class=cF0> </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l1298"></a>        color = dc-&gt;color;
<a name="l1299"></a>        </span><span class=cF1>if</span><span class=cF0> (color.c1.rop &amp; </span><span class=cF7>(</span><span class=cF3>ROPBF_DITHER</span><span class=cF0> | </span><span class=cF3>ROPBF_PROBABILITY_DITHER</span><span class=cF7>)</span><span class=cF0>)
<a name="l1300"></a>        {
<a name="l1301"></a>            dither = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l1302"></a>            </span><span class=cF1>if</span><span class=cF0> (color.c1.rop &amp; </span><span class=cF3>ROPBF_PROBABILITY_DITHER</span><span class=cF0>)
<a name="l1303"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1304"></a>                probability_dither = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l1305"></a>                color.c1.rop = color.c0.rop;
<a name="l1306"></a>                dither_colors = color;
<a name="l1307"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1308"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l1309"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1310"></a>                probability_dither = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l1311"></a>                color.c1.rop = color.c0.rop;
<a name="l1312"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1313"></a>        }
<a name="l1314"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l1315"></a>            dither = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l1316"></a>        original_leading_pixels = leading_pixels = -(w1 + x) &amp; </span><span class=cFE>7</span><span class=cF0>;
<a name="l1317"></a>        leading_pixel_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[</span><span class=cFE>0xFF</span><span class=cF0> &gt;&gt; leading_pixels];
<a name="l1318"></a>        whole_I64s = (w2 - w1 - leading_pixels) &gt;&gt; </span><span class=cFE>3</span><span class=cF0>;
<a name="l1319"></a>        </span><span class=cF1>if</span><span class=cF0> (whole_I64s &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l1320"></a>            whole_I64s = </span><span class=cFE>0</span><span class=cF0>;
<a name="l1321"></a>        trailing_pixels = (x + w2) &amp; </span><span class=cFE>7</span><span class=cF0>;
<a name="l1322"></a>        trailing_pixel_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[</span><span class=cFE>0xFF</span><span class=cF0> &lt;&lt; trailing_pixels &amp; </span><span class=cFE>0xFF</span><span class=cF0>];
<a name="l1323"></a>        </span><span class=cF1>if</span><span class=cF0> (leading_pixels + trailing_pixels &gt; w2 - w1)
<a name="l1324"></a>        {
<a name="l1325"></a>            leading_pixel_mask |= trailing_pixel_mask;
<a name="l1326"></a>            leading_pixels = w2 - w1; </span><span class=cF2>//Correct so it's right for res.</span><span class=cF0>
<a name="l1327"></a>            trailing_pixels = </span><span class=cFE>0</span><span class=cF0>;
<a name="l1328"></a>        }
<a name="l1329"></a>        </span><span class=cF1>if</span><span class=cF0> (color.c0.rop == </span><span class=cF3>ROPB_COLLISION</span><span class=cF0>)
<a name="l1330"></a>        {</span><span class=cF2>//TODO: Might want to check win_z_buf</span><span class=cF0>
<a name="l1331"></a>            color = dc-&gt;bkcolor.c0.color;
<a name="l1332"></a>            k1 = (h1 + y) * dc-&gt;width_internal + x;
<a name="l1333"></a>            res = -dc-&gt;collision_count;
<a name="l1334"></a>            </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l1335"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1336"></a>                </span><span class=cF1>for</span><span class=cF0> (i = w1; i &lt; w2; i++)
<a name="l1337"></a>                {
<a name="l1338"></a>                    c = dc-&gt;body[k1 + i];
<a name="l1339"></a>                    </span><span class=cF1>if</span><span class=cF0> (c != </span><span class=cF3>TRANSPARENT</span><span class=cF0> &amp;&amp; c != color)
<a name="l1340"></a>                        dc-&gt;collision_count++;
<a name="l1341"></a>                }
<a name="l1342"></a>                k1 += dc-&gt;width_internal;
<a name="l1343"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1344"></a>            res += dc-&gt;collision_count;
<a name="l1345"></a>        }
<a name="l1346"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l1347"></a>        {
<a name="l1348"></a>            </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF7>)</span><span class=cF0> || dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF0>)
<a name="l1349"></a>                win_z_buf_ptr = </span><span class=cF3>NULL</span><span class=cF0>;
<a name="l1350"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l1351"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1352"></a>                win_z_num = win_task-&gt;win_z_num;
<a name="l1353"></a>                win_z_buf_ptr = </span><span class=cFB>gr</span><span class=cF0>.win_z_buf(</span><span class=cF1>U8</span><span class=cF0> *) +
<a name="l1354"></a>                                (</span><span class=cF7>(</span><span class=cF0>h1 + y</span><span class=cF7>)</span><span class=cF0> / </span><span class=cF3>FONT_HEIGHT</span><span class=cF0> * </span><span class=cF3>TEXT_COLS</span><span class=cF0> + </span><span class=cF7>(</span><span class=cF0>w1 + x</span><span class=cF7>)</span><span class=cF0> / </span><span class=cF3>FONT_WIDTH</span><span class=cF0>) * </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>);
<a name="l1355"></a>                win_z_buf_line_dec = whole_I64s;
<a name="l1356"></a>                </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l1357"></a>                    win_z_buf_line_dec++;
<a name="l1358"></a>                </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l1359"></a>                    win_z_buf_line_dec++;
<a name="l1360"></a>                win_z_buf_line_dec *= </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>);
<a name="l1361"></a>                win_z_buf_line_inc = </span><span class=cF3>TEXT_COLS</span><span class=cF0> * </span><span class=cF1>sizeof</span><span class=cF0>(</span><span class=cF9>U16</span><span class=cF0>) - win_z_buf_line_dec;
<a name="l1362"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1363"></a>            kk1 = (h1 + y) * dc-&gt;width_internal + x + w1;
<a name="l1364"></a>            </span><span class=cF1>if</span><span class=cF0> (dither)
<a name="l1365"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1366"></a>                </span><span class=cF1>if</span><span class=cF0> (probability_dither)
<a name="l1367"></a>                {
<a name="l1368"></a>                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>RandU16</span><span class=cF0> &lt; dc-&gt;dither_probability_u16)
<a name="l1369"></a>                        color.c0 = dither_colors.c1;
<a name="l1370"></a>                    </span><span class=cF1>else</span><span class=cF0>
<a name="l1371"></a>                        color.c0 = dither_colors.c0;
<a name="l1372"></a>                    </span><span class=cF1>switch</span><span class=cF0> [color.c0.rop]
<a name="l1373"></a>                    </span><span class=cF7>{</span><span class=cF0>
<a name="l1374"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_EQU</span><span class=cF0>:
<a name="l1375"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_MONO</span><span class=cF0>:
<a name="l1376"></a>                            </span><span class=cF1>if</span><span class=cF0> (win_z_buf_ptr)
<a name="l1377"></a>                            {
<a name="l1378"></a>                                res = </span><span class=cFE>0</span><span class=cF0>;
<a name="l1379"></a>                                </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l1380"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l1381"></a>                                    color_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c0.color];
<a name="l1382"></a>                                    dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l1383"></a>                                    </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l1384"></a>                                    {
<a name="l1385"></a>                                        </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1386"></a>                                        </span><span class=cF7>{</span><span class=cF0>
<a name="l1387"></a>                                            *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask | color_mask &amp; ~leading_pixel_mask;
<a name="l1388"></a>                                            res += leading_pixels;
<a name="l1389"></a>                                        </span><span class=cF7>}</span><span class=cF0>
<a name="l1390"></a>                                        dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l1391"></a>                                    }
<a name="l1392"></a>                                    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++, dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++)
<a name="l1393"></a>                                        </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1394"></a>                                        {
<a name="l1395"></a>                                            *dst(</span><span class=cF9>I64</span><span class=cF0> *) = color_mask;
<a name="l1396"></a>                                            res += </span><span class=cFE>8</span><span class=cF0>;
<a name="l1397"></a>                                        }
<a name="l1398"></a>                                    </span><span class=cF1>if</span><span class=cF0> (trailing_pixels &amp;&amp; win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1399"></a>                                    {
<a name="l1400"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask | color_mask &amp; ~trailing_pixel_mask;
<a name="l1401"></a>                                        res += trailing_pixels;
<a name="l1402"></a>                                    }
<a name="l1403"></a>                                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>j + y</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>7</span><span class=cF0> == </span><span class=cFE>7</span><span class=cF0>)
<a name="l1404"></a>                                        win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) += win_z_buf_line_inc;
<a name="l1405"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l1406"></a>                                        win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) -= win_z_buf_line_dec;
<a name="l1407"></a>                                    kk1 += dc-&gt;width_internal;
<a name="l1408"></a>                                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>RandU16</span><span class=cF0> &lt; dc-&gt;dither_probability_u16)
<a name="l1409"></a>                                        color.c0 = dither_colors.c1;
<a name="l1410"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l1411"></a>                                        color.c0 = dither_colors.c0;
<a name="l1412"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l1413"></a>                            }
<a name="l1414"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l1415"></a>                            {
<a name="l1416"></a>                                </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l1417"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l1418"></a>                                    color_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c0.color];
<a name="l1419"></a>                                    dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l1420"></a>                                    </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l1421"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask | color_mask &amp; ~leading_pixel_mask;
<a name="l1422"></a>                                    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++, dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++)
<a name="l1423"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = color_mask;
<a name="l1424"></a>                                    </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l1425"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask | color_mask &amp; ~trailing_pixel_mask;
<a name="l1426"></a>                                    kk1 += dc-&gt;width_internal;
<a name="l1427"></a>                                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>RandU16</span><span class=cF0> &lt; dc-&gt;dither_probability_u16)
<a name="l1428"></a>                                        color.c0 = dither_colors.c1;
<a name="l1429"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l1430"></a>                                        color.c0 = dither_colors.c0;
<a name="l1431"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l1432"></a>                                res = (h2 - h1) * (w2 - w1);
<a name="l1433"></a>                            }
<a name="l1434"></a>                            </span><span class=cF5>BEqual</span><span class=cF0>(&amp;</span><span class=cF5>Fs</span><span class=cF0>-&gt;task_flags, </span><span class=cF3>TASKf_NONTIMER_RAND</span><span class=cF0>, was_timer_rand);
<a name="l1435"></a>
<a name="l1436"></a>                            </span><span class=cF1>break</span><span class=cF0>;
<a name="l1437"></a>
<a name="l1438"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_XOR</span><span class=cF0>:
<a name="l1439"></a>                            </span><span class=cF1>if</span><span class=cF0> (win_z_buf_ptr)
<a name="l1440"></a>                            {
<a name="l1441"></a>                                res = </span><span class=cFE>0</span><span class=cF0>;
<a name="l1442"></a>                                </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l1443"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l1444"></a>                                    color_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c0.color];
<a name="l1445"></a>                                    dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l1446"></a>                                    </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l1447"></a>                                    {
<a name="l1448"></a>                                        </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1449"></a>                                        </span><span class=cF7>{</span><span class=cF0>
<a name="l1450"></a>                                            *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l1451"></a>                                                          *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^ color_mask &amp; ~leading_pixel_mask;
<a name="l1452"></a>                                            res += leading_pixels;
<a name="l1453"></a>                                        </span><span class=cF7>}</span><span class=cF0>
<a name="l1454"></a>                                        dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l1455"></a>                                    }
<a name="l1456"></a>                                    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++, dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++)
<a name="l1457"></a>                                        </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1458"></a>                                        {
<a name="l1459"></a>                                            *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^= color_mask;
<a name="l1460"></a>                                            res += </span><span class=cFE>8</span><span class=cF0>;
<a name="l1461"></a>                                        }
<a name="l1462"></a>                                    </span><span class=cF1>if</span><span class=cF0> (trailing_pixels &amp;&amp; win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1463"></a>                                    {
<a name="l1464"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l1465"></a>                                                      *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^ color_mask &amp; ~trailing_pixel_mask;
<a name="l1466"></a>                                        res += trailing_pixels;
<a name="l1467"></a>                                    }
<a name="l1468"></a>                                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>j + y</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>7</span><span class=cF0> == </span><span class=cFE>7</span><span class=cF0>)
<a name="l1469"></a>                                        win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) += win_z_buf_line_inc;
<a name="l1470"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l1471"></a>                                        win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) -= win_z_buf_line_dec;
<a name="l1472"></a>                                    kk1 += dc-&gt;width_internal;
<a name="l1473"></a>                                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>RandU16</span><span class=cF0> &lt; dc-&gt;dither_probability_u16)
<a name="l1474"></a>                                        color.c0 = dither_colors.c1;
<a name="l1475"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l1476"></a>                                        color.c0 = dither_colors.c0;
<a name="l1477"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l1478"></a>                            }
<a name="l1479"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l1480"></a>                            {
<a name="l1481"></a>                                </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l1482"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l1483"></a>                                    color_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c0.color];
<a name="l1484"></a>                                    dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l1485"></a>                                    </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l1486"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l1487"></a>                                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^ color_mask &amp; ~leading_pixel_mask;
<a name="l1488"></a>                                    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++, dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++)
<a name="l1489"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^= color_mask;
<a name="l1490"></a>                                    </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l1491"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l1492"></a>                                                      *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^ color_mask &amp; ~trailing_pixel_mask;
<a name="l1493"></a>                                    kk1 += dc-&gt;width_internal;
<a name="l1494"></a>                                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>RandU16</span><span class=cF0> &lt; dc-&gt;dither_probability_u16)
<a name="l1495"></a>                                        color.c0 = dither_colors.c1;
<a name="l1496"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l1497"></a>                                        color.c0 = dither_colors.c0;
<a name="l1498"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l1499"></a>                                res = (h2 - h1) * (w2 - w1);
<a name="l1500"></a>                            }
<a name="l1501"></a>                            </span><span class=cF5>BEqual</span><span class=cF0>(&amp;</span><span class=cF5>Fs</span><span class=cF0>-&gt;task_flags, </span><span class=cF3>TASKf_NONTIMER_RAND</span><span class=cF0>, was_timer_rand);
<a name="l1502"></a>
<a name="l1503"></a>                            </span><span class=cF1>break</span><span class=cF0>;
<a name="l1504"></a>                    </span><span class=cF7>}</span><span class=cF0>
<a name="l1505"></a>                }
<a name="l1506"></a>                </span><span class=cF1>else</span><span class=cF0>
<a name="l1507"></a>                {
<a name="l1508"></a>                    </span><span class=cF5>BEqual</span><span class=cF0>(&amp;</span><span class=cF5>Fs</span><span class=cF0>-&gt;task_flags, </span><span class=cF3>TASKf_NONTIMER_RAND</span><span class=cF0>, was_timer_rand);
<a name="l1509"></a>
<a name="l1510"></a>                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>(x + w1 - original_leading_pixels) ^ (y + h1)</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>1</span><span class=cF0>)
<a name="l1511"></a>                        </span><span class=cF5>SwapU16</span><span class=cF0>(&amp;color.c0, &amp;color.c1);
<a name="l1512"></a>                    </span><span class=cF1>switch</span><span class=cF0> [color.c0.rop]
<a name="l1513"></a>                    </span><span class=cF7>{</span><span class=cF0>
<a name="l1514"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_EQU</span><span class=cF0>:
<a name="l1515"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_MONO</span><span class=cF0>:
<a name="l1516"></a>                            </span><span class=cF1>if</span><span class=cF0> (win_z_buf_ptr)
<a name="l1517"></a>                            {
<a name="l1518"></a>                                res = </span><span class=cFE>0</span><span class=cF0>;
<a name="l1519"></a>                                </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l1520"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l1521"></a>                                    color_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[</span><span class=cFE>0x55</span><span class=cF0>] &amp; </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c0.color] |
<a name="l1522"></a>                                                 </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[</span><span class=cFE>0xAA</span><span class=cF0>] &amp; </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c1.color];
<a name="l1523"></a>                                    dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l1524"></a>                                    </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l1525"></a>                                    {
<a name="l1526"></a>                                        </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1527"></a>                                        </span><span class=cF7>{</span><span class=cF0>
<a name="l1528"></a>                                            *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask | color_mask &amp; ~leading_pixel_mask;
<a name="l1529"></a>                                            res += leading_pixels;
<a name="l1530"></a>                                        </span><span class=cF7>}</span><span class=cF0>
<a name="l1531"></a>                                        dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l1532"></a>                                    }
<a name="l1533"></a>                                    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++, dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++)
<a name="l1534"></a>                                        </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1535"></a>                                        {
<a name="l1536"></a>                                            *dst(</span><span class=cF9>I64</span><span class=cF0> *) = color_mask;
<a name="l1537"></a>                                            res += </span><span class=cFE>8</span><span class=cF0>;
<a name="l1538"></a>                                        }
<a name="l1539"></a>                                    </span><span class=cF1>if</span><span class=cF0> (trailing_pixels &amp;&amp; win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1540"></a>                                    {
<a name="l1541"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask | color_mask &amp; ~trailing_pixel_mask;
<a name="l1542"></a>                                        res += trailing_pixels;
<a name="l1543"></a>                                    }
<a name="l1544"></a>                                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>j + y</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>7</span><span class=cF0> == </span><span class=cFE>7</span><span class=cF0>)
<a name="l1545"></a>                                        win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) += win_z_buf_line_inc;
<a name="l1546"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l1547"></a>                                        win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) -= win_z_buf_line_dec;
<a name="l1548"></a>                                    kk1 += dc-&gt;width_internal;
<a name="l1549"></a>                                    </span><span class=cF5>SwapU16</span><span class=cF0>(&amp;color.c0, &amp;color.c1);
<a name="l1550"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l1551"></a>                            }
<a name="l1552"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l1553"></a>                            {
<a name="l1554"></a>                                </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l1555"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l1556"></a>                                    color_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[</span><span class=cFE>0x55</span><span class=cF0>] &amp; </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c0.color] |
<a name="l1557"></a>                                                 </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[</span><span class=cFE>0xAA</span><span class=cF0>] &amp; </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c1.color];
<a name="l1558"></a>                                    dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l1559"></a>                                    </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l1560"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask | color_mask &amp; ~leading_pixel_mask;
<a name="l1561"></a>                                    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++, dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++)
<a name="l1562"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = color_mask;
<a name="l1563"></a>                                    </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l1564"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask | color_mask &amp; ~trailing_pixel_mask;
<a name="l1565"></a>                                    kk1 += dc-&gt;width_internal;
<a name="l1566"></a>                                    </span><span class=cF5>SwapU16</span><span class=cF0>(&amp;color.c0, &amp;color.c1);
<a name="l1567"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l1568"></a>                                res = (h2 - h1) * (w2 - w1);
<a name="l1569"></a>                            }
<a name="l1570"></a>                            </span><span class=cF1>break</span><span class=cF0>;
<a name="l1571"></a>
<a name="l1572"></a>                        </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_XOR</span><span class=cF0>:
<a name="l1573"></a>                            </span><span class=cF1>if</span><span class=cF0> (win_z_buf_ptr)
<a name="l1574"></a>                            {
<a name="l1575"></a>                                res = </span><span class=cFE>0</span><span class=cF0>;
<a name="l1576"></a>                                </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l1577"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l1578"></a>                                    color_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[</span><span class=cFE>0x55</span><span class=cF0>] &amp; </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c0.color] |
<a name="l1579"></a>                                                 </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[</span><span class=cFE>0xAA</span><span class=cF0>] &amp; </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c1.color];
<a name="l1580"></a>                                    dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l1581"></a>                                    </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l1582"></a>                                    {
<a name="l1583"></a>                                        </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1584"></a>                                        </span><span class=cF7>{</span><span class=cF0>
<a name="l1585"></a>                                            *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l1586"></a>                                                          *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^ color_mask &amp; ~leading_pixel_mask;
<a name="l1587"></a>                                            res += leading_pixels;
<a name="l1588"></a>                                        </span><span class=cF7>}</span><span class=cF0>
<a name="l1589"></a>                                        dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l1590"></a>                                    }
<a name="l1591"></a>                                    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++, dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++)
<a name="l1592"></a>                                        </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1593"></a>                                        {
<a name="l1594"></a>                                            *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^= color_mask;
<a name="l1595"></a>                                            res += </span><span class=cFE>8</span><span class=cF0>;
<a name="l1596"></a>                                        }
<a name="l1597"></a>                                    </span><span class=cF1>if</span><span class=cF0> (trailing_pixels &amp;&amp; win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1598"></a>                                    {
<a name="l1599"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l1600"></a>                                                      *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^ color_mask &amp; ~trailing_pixel_mask;
<a name="l1601"></a>                                        res += trailing_pixels;
<a name="l1602"></a>                                    }
<a name="l1603"></a>                                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>j + y</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>7</span><span class=cF0> == </span><span class=cFE>7</span><span class=cF0>)
<a name="l1604"></a>                                        win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) += win_z_buf_line_inc;
<a name="l1605"></a>                                    </span><span class=cF1>else</span><span class=cF0>
<a name="l1606"></a>                                        win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) -= win_z_buf_line_dec;
<a name="l1607"></a>                                    kk1 += dc-&gt;width_internal;
<a name="l1608"></a>                                    </span><span class=cF5>SwapU16</span><span class=cF0>(&amp;color.c0, &amp;color.c1);
<a name="l1609"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l1610"></a>                            }
<a name="l1611"></a>                            </span><span class=cF1>else</span><span class=cF0>
<a name="l1612"></a>                            {
<a name="l1613"></a>                                </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l1614"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l1615"></a>                                    color_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[</span><span class=cFE>0x55</span><span class=cF0>] &amp; </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c0.color] |
<a name="l1616"></a>                                                 </span><span class=cFB>gr</span><span class=cF0>.to_8_bits[</span><span class=cFE>0xAA</span><span class=cF0>] &amp; </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c1.color];
<a name="l1617"></a>                                    dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l1618"></a>                                    </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l1619"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l1620"></a>                                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^ color_mask &amp; ~leading_pixel_mask;
<a name="l1621"></a>                                    </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++, dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++)
<a name="l1622"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^= color_mask;
<a name="l1623"></a>                                    </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l1624"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l1625"></a>                                                      *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^ color_mask &amp; ~trailing_pixel_mask;
<a name="l1626"></a>                                    kk1 += dc-&gt;width_internal;
<a name="l1627"></a>                                    </span><span class=cF5>SwapU16</span><span class=cF0>(&amp;color.c0, &amp;color.c1);
<a name="l1628"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l1629"></a>                                res = (h2 - h1) * (w2 - w1);
<a name="l1630"></a>                            }
<a name="l1631"></a>                            </span><span class=cF1>break</span><span class=cF0>;
<a name="l1632"></a>                    </span><span class=cF7>}</span><span class=cF0>
<a name="l1633"></a>                }
<a name="l1634"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1635"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l1636"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1637"></a>                </span><span class=cF5>BEqual</span><span class=cF0>(&amp;</span><span class=cF5>Fs</span><span class=cF0>-&gt;task_flags, </span><span class=cF3>TASKf_NONTIMER_RAND</span><span class=cF0>, was_timer_rand);
<a name="l1638"></a>
<a name="l1639"></a>                color_mask = </span><span class=cFB>gr</span><span class=cF0>.to_8_colors[color.c0.color];
<a name="l1640"></a>                </span><span class=cF1>switch</span><span class=cF0> [color.c0.rop]
<a name="l1641"></a>                {
<a name="l1642"></a>                    </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_EQU</span><span class=cF0>:
<a name="l1643"></a>                    </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_MONO</span><span class=cF0>:
<a name="l1644"></a>                        </span><span class=cF1>if</span><span class=cF0> (win_z_buf_ptr)
<a name="l1645"></a>                        </span><span class=cF7>{</span><span class=cF0>
<a name="l1646"></a>                            res = </span><span class=cFE>0</span><span class=cF0>;
<a name="l1647"></a>                            </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l1648"></a>                            {
<a name="l1649"></a>                                dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l1650"></a>                                </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l1651"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l1652"></a>                                    </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1653"></a>                                    {
<a name="l1654"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask | color_mask &amp; ~leading_pixel_mask;
<a name="l1655"></a>                                        res += leading_pixels;
<a name="l1656"></a>                                    }
<a name="l1657"></a>                                    dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l1658"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l1659"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++, dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++)
<a name="l1660"></a>                                    </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1661"></a>                                    </span><span class=cF7>{</span><span class=cF0>
<a name="l1662"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = color_mask;
<a name="l1663"></a>                                        res += </span><span class=cFE>8</span><span class=cF0>;
<a name="l1664"></a>                                    </span><span class=cF7>}</span><span class=cF0>
<a name="l1665"></a>                                </span><span class=cF1>if</span><span class=cF0> (trailing_pixels &amp;&amp; win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1666"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l1667"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask | color_mask &amp; ~trailing_pixel_mask;
<a name="l1668"></a>                                    res += trailing_pixels;
<a name="l1669"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l1670"></a>                                </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>j + y</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>7</span><span class=cF0> == </span><span class=cFE>7</span><span class=cF0>)
<a name="l1671"></a>                                    win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) += win_z_buf_line_inc;
<a name="l1672"></a>                                </span><span class=cF1>else</span><span class=cF0>
<a name="l1673"></a>                                    win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) -= win_z_buf_line_dec;
<a name="l1674"></a>                                kk1 += dc-&gt;width_internal;
<a name="l1675"></a>                            }
<a name="l1676"></a>                        </span><span class=cF7>}</span><span class=cF0>
<a name="l1677"></a>                        </span><span class=cF1>else</span><span class=cF0>
<a name="l1678"></a>                        </span><span class=cF7>{</span><span class=cF0>
<a name="l1679"></a>                            </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l1680"></a>                            {
<a name="l1681"></a>                                dst(</span><span class=cF9>I64</span><span class=cF0> *) = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l1682"></a>                                </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l1683"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask | color_mask &amp; ~leading_pixel_mask;
<a name="l1684"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++, dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++)
<a name="l1685"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = color_mask;
<a name="l1686"></a>                                </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l1687"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask | color_mask &amp; ~trailing_pixel_mask;
<a name="l1688"></a>                                kk1 += dc-&gt;width_internal;
<a name="l1689"></a>                            }
<a name="l1690"></a>                            res = (h2 - h1) * (w2 - w1);
<a name="l1691"></a>                        </span><span class=cF7>}</span><span class=cF0>
<a name="l1692"></a>                        </span><span class=cF1>break</span><span class=cF0>;
<a name="l1693"></a>
<a name="l1694"></a>                    </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_XOR</span><span class=cF0>:
<a name="l1695"></a>                        </span><span class=cF1>if</span><span class=cF0> (win_z_buf_ptr)
<a name="l1696"></a>                        </span><span class=cF7>{</span><span class=cF0>
<a name="l1697"></a>                            res = </span><span class=cFE>0</span><span class=cF0>;
<a name="l1698"></a>                            </span><span class=cF1>for</span><span class=cF0> (j = h1; j &lt; h2; j++)
<a name="l1699"></a>                            {
<a name="l1700"></a>                                dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l1701"></a>                                </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l1702"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l1703"></a>                                    </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1704"></a>                                    {
<a name="l1705"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l1706"></a>                                                      *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^ color_mask &amp; ~leading_pixel_mask;
<a name="l1707"></a>                                        res += leading_pixels;
<a name="l1708"></a>                                    }
<a name="l1709"></a>                                    dst(</span><span class=cF9>I64</span><span class=cF0> *)++;
<a name="l1710"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l1711"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++, dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++)
<a name="l1712"></a>                                    </span><span class=cF1>if</span><span class=cF0> (win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1713"></a>                                    </span><span class=cF7>{</span><span class=cF0>
<a name="l1714"></a>                                        *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^= color_mask;
<a name="l1715"></a>                                        res += </span><span class=cFE>8</span><span class=cF0>;
<a name="l1716"></a>                                    </span><span class=cF7>}</span><span class=cF0>
<a name="l1717"></a>                                </span><span class=cF1>if</span><span class=cF0> (trailing_pixels &amp;&amp; win_z_num &gt;= *win_z_buf_ptr++)
<a name="l1718"></a>                                </span><span class=cF7>{</span><span class=cF0>
<a name="l1719"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l1720"></a>                                                  *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^ color_mask &amp; ~trailing_pixel_mask;
<a name="l1721"></a>                                    res += trailing_pixels;
<a name="l1722"></a>                                </span><span class=cF7>}</span><span class=cF0>
<a name="l1723"></a>                                </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>j + y</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>7</span><span class=cF0> == </span><span class=cFE>7</span><span class=cF0>)
<a name="l1724"></a>                                    win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) += win_z_buf_line_inc;
<a name="l1725"></a>                                </span><span class=cF1>else</span><span class=cF0>
<a name="l1726"></a>                                    win_z_buf_ptr(</span><span class=cF1>U8</span><span class=cF0> *) -= win_z_buf_line_dec;
<a name="l1727"></a>                                kk1 += dc-&gt;width_internal;
<a name="l1728"></a>                            }
<a name="l1729"></a>                        </span><span class=cF7>}</span><span class=cF0>
<a name="l1730"></a>                        </span><span class=cF1>else</span><span class=cF0>
<a name="l1731"></a>                        </span><span class=cF7>{</span><span class=cF0>
<a name="l1732"></a>                            </span><span class=cF1>for</span><span class=cF0> (j = h2 - h1; j; j--)
<a name="l1733"></a>                            {
<a name="l1734"></a>                                dst = dc-&gt;body + kk1 &amp; ~</span><span class=cFE>7</span><span class=cF0>;
<a name="l1735"></a>                                </span><span class=cF1>if</span><span class=cF0> (leading_pixels)
<a name="l1736"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *)++ = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; leading_pixel_mask |
<a name="l1737"></a>                                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^ color_mask &amp; ~leading_pixel_mask;
<a name="l1738"></a>                                </span><span class=cF1>for</span><span class=cF0> (i = </span><span class=cFE>0</span><span class=cF0>; i &lt; whole_I64s; i++, dst</span><span class=cF7>(</span><span class=cF9>I64</span><span class=cF0> *</span><span class=cF7>)</span><span class=cF0>++)
<a name="l1739"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^= color_mask;
<a name="l1740"></a>                                </span><span class=cF1>if</span><span class=cF0> (trailing_pixels)
<a name="l1741"></a>                                    *dst(</span><span class=cF9>I64</span><span class=cF0> *) = *dst(</span><span class=cF9>I64</span><span class=cF0> *) &amp; trailing_pixel_mask |
<a name="l1742"></a>                                                  *dst(</span><span class=cF9>I64</span><span class=cF0> *) ^ color_mask &amp; ~trailing_pixel_mask;
<a name="l1743"></a>                                kk1 += dc-&gt;width_internal;
<a name="l1744"></a>                            }
<a name="l1745"></a>                            res = (h2 - h1) * (w2 - w1);
<a name="l1746"></a>                        </span><span class=cF7>}</span><span class=cF0>
<a name="l1747"></a>                        </span><span class=cF1>break</span><span class=cF0>;
<a name="l1748"></a>                }
<a name="l1749"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1750"></a>        }
<a name="l1751"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1752"></a>
<a name="l1753"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l1754"></a>}
<a name="l1755"></a>
<a name="l1756"></a></span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>GrRayLenMinus</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc, </span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y)
<a name="l1757"></a>{</span><span class=cF2>//Returns count of pixs changed</span><span class=cF0>
<a name="l1758"></a>    </span><span class=cF9>I64</span><span class=cF0>      res = </span><span class=cFE>0</span><span class=cF0>, c, x3, y3, d;
<a name="l1759"></a>    </span><span class=cF1>U8</span><span class=cF0>      *dst, *dst2;
<a name="l1760"></a>    </span><span class=cF1>Bool</span><span class=cF0>     not_color = </span><span class=cF5>ToBool</span><span class=cF0>(dc-&gt;flags &amp; </span><span class=cF3>DCF_FILL_NOT_COLOR</span><span class=cF0>);
<a name="l1761"></a>    </span><span class=cF9>CTask</span><span class=cF0>   *win_task;
<a name="l1762"></a>
<a name="l1763"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l1764"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l1765"></a>        win_task = dc-&gt;win_task;
<a name="l1766"></a>        x += win_task-&gt;scroll_x;
<a name="l1767"></a>        y += win_task-&gt;scroll_y;
<a name="l1768"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1769"></a>    x3 = x;
<a name="l1770"></a>    y3 = y;
<a name="l1771"></a>    </span><span class=cF1>if</span><span class=cF0> (x3 &lt; </span><span class=cFE>0</span><span class=cF0> || y3 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l1772"></a>        </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l1773"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l1774"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l1775"></a>        x3 += win_task-&gt;pix_left;
<a name="l1776"></a>        y3 += win_task-&gt;pix_top;
<a name="l1777"></a>        </span><span class=cF1>if</span><span class=cF0> (    !</span><span class=cF7>(</span><span class=cFE>0</span><span class=cF0> &lt;= x3 &lt;= win_task-&gt;pix_right</span><span class=cF7>)</span><span class=cF0>  ||
<a name="l1778"></a>                !</span><span class=cF7>(</span><span class=cFE>0</span><span class=cF0> &lt;= y3 &lt;= win_task-&gt;pix_bottom</span><span class=cF7>)</span><span class=cF0> ||
<a name="l1779"></a>                !</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF7>)</span><span class=cF0> &amp;&amp; </span><span class=cF5>IsPixCovered0</span><span class=cF7>(</span><span class=cF0>win_task, x3, y3</span><span class=cF7>)</span><span class=cF0>)
<a name="l1780"></a>            </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l1781"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1782"></a>    </span><span class=cF1>if</span><span class=cF0> (x3 &gt;= dc-&gt;width || y3 &gt;= dc-&gt;height)
<a name="l1783"></a>        </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l1784"></a>
<a name="l1785"></a>    d = y3 * dc-&gt;width_internal;
<a name="l1786"></a>    dst2 = dc-&gt;body + d;
<a name="l1787"></a>    </span><span class=cF1>while</span><span class=cF0> (</span><span class=cF3>TRUE</span><span class=cF0>)
<a name="l1788"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l1789"></a>        x3 = x;
<a name="l1790"></a>        </span><span class=cF1>if</span><span class=cF0> (x3 &amp; </span><span class=cF7>(</span><span class=cF3>FONT_WIDTH</span><span class=cF0> - </span><span class=cFE>1</span><span class=cF7>)</span><span class=cF0> == </span><span class=cF3>FONT_WIDTH</span><span class=cF0> - </span><span class=cFE>1</span><span class=cF0>)
<a name="l1791"></a>        {
<a name="l1792"></a>            </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l1793"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1794"></a>                </span><span class=cF1>if</span><span class=cF0> (x3 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l1795"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l1796"></a>                x3 += win_task-&gt;pix_left;
<a name="l1797"></a>                </span><span class=cF1>if</span><span class=cF0> (    !</span><span class=cF7>(</span><span class=cFE>0</span><span class=cF0> &lt;= x3 &lt;= win_task-&gt;pix_right</span><span class=cF7>)</span><span class=cF0> || x3 &gt;= dc-&gt;width ||
<a name="l1798"></a>                        !</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF7>)</span><span class=cF0> &amp;&amp; </span><span class=cF5>IsPixCovered0</span><span class=cF7>(</span><span class=cF0>win_task, x3, y3</span><span class=cF7>)</span><span class=cF0>)
<a name="l1799"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l1800"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1801"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l1802"></a>                </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cFE>0</span><span class=cF0> &lt;= x3 &lt; dc-&gt;width</span><span class=cF7>)</span><span class=cF0>)
<a name="l1803"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l1804"></a>        }
<a name="l1805"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l1806"></a>            x3 += win_task-&gt;pix_left;
<a name="l1807"></a>        dst = dst2 + x3;
<a name="l1808"></a>        c = *dst;
<a name="l1809"></a>        </span><span class=cF1>if</span><span class=cF0> (not_color)
<a name="l1810"></a>        {
<a name="l1811"></a>            </span><span class=cF1>if</span><span class=cF0> (c != dc-&gt;color2)
<a name="l1812"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1813"></a>                res++;
<a name="l1814"></a>                x--;
<a name="l1815"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1816"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l1817"></a>                </span><span class=cF1>break</span><span class=cF0>;
<a name="l1818"></a>        }
<a name="l1819"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l1820"></a>        {
<a name="l1821"></a>            </span><span class=cF1>if</span><span class=cF0> (c == dc-&gt;color2)
<a name="l1822"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1823"></a>                res++;
<a name="l1824"></a>                x--;
<a name="l1825"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1826"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l1827"></a>                </span><span class=cF1>break</span><span class=cF0>;
<a name="l1828"></a>        }
<a name="l1829"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1830"></a>
<a name="l1831"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l1832"></a>gr_done:
<a name="l1833"></a>    </span><span class=cF1>return</span><span class=cF0> </span><span class=cFE>0</span><span class=cF0>;
<a name="l1834"></a>}
<a name="l1835"></a>
<a name="l1836"></a></span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>GrRayLen</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc, </span><span class=cF9>I64</span><span class=cF0> *x1, </span><span class=cF9>I64</span><span class=cF0> y, </span><span class=cF9>I64</span><span class=cF0> z=</span><span class=cFE>0</span><span class=cF0>, </span><span class=cF9>I32</span><span class=cF0> *db=</span><span class=cF3>NULL</span><span class=cF0>)
<a name="l1837"></a>{
<a name="l1838"></a></span><span class=cF2>//Returns count of pixs changed</span><span class=cF0>
<a name="l1839"></a>    </span><span class=cF9>I64</span><span class=cF0>              res = </span><span class=cFE>0</span><span class=cF0>, d, x = *x1, x2, x3, y3, dist;
<a name="l1840"></a>    </span><span class=cF1>Bool</span><span class=cF0>             plot, dither, probability_dither, 
<a name="l1841"></a>                     not_color = </span><span class=cF5>ToBool</span><span class=cF0>(dc-&gt;flags &amp; </span><span class=cF3>DCF_FILL_NOT_COLOR</span><span class=cF0>), 
<a name="l1842"></a>                     was_timer_rand = </span><span class=cF5>Bts</span><span class=cF0>(&amp;</span><span class=cF5>Fs</span><span class=cF0>-&gt;task_flags, </span><span class=cF3>TASKf_NONTIMER_RAND</span><span class=cF0>);
<a name="l1843"></a>    </span><span class=cF1>U8</span><span class=cF0>              *dst, *dst2;
<a name="l1844"></a>    </span><span class=cF9>CColorROPU32</span><span class=cF0>     c, c2, color = dc-&gt;color, bkcolor = dc-&gt;bkcolor;
<a name="l1845"></a>    </span><span class=cF9>I32</span><span class=cF0>             *db2;
<a name="l1846"></a>    </span><span class=cF9>CTask</span><span class=cF0>           *win_task;
<a name="l1847"></a>
<a name="l1848"></a>
<a name="l1849"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l1850"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l1851"></a>        win_task = dc-&gt;win_task;
<a name="l1852"></a>        x += win_task-&gt;scroll_x;
<a name="l1853"></a>        y += win_task-&gt;scroll_y;
<a name="l1854"></a>        z += win_task-&gt;scroll_z;
<a name="l1855"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1856"></a>    x2 = x;
<a name="l1857"></a>    x3 = x;
<a name="l1858"></a>    y3 = y;
<a name="l1859"></a>    </span><span class=cF1>if</span><span class=cF0> (x3 &lt; </span><span class=cFE>0</span><span class=cF0> || y3 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l1860"></a>        </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l1861"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l1862"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l1863"></a>        x3 += win_task-&gt;pix_left;
<a name="l1864"></a>        y3 += win_task-&gt;pix_top;
<a name="l1865"></a>        </span><span class=cF1>if</span><span class=cF0> (    !</span><span class=cF7>(</span><span class=cFE>0</span><span class=cF0> &lt;= x3 &lt;= win_task-&gt;pix_right</span><span class=cF7>)</span><span class=cF0>  ||
<a name="l1866"></a>                !</span><span class=cF7>(</span><span class=cFE>0</span><span class=cF0> &lt;= y3 &lt;= win_task-&gt;pix_bottom</span><span class=cF7>)</span><span class=cF0> ||
<a name="l1867"></a>                !</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF7>)</span><span class=cF0> &amp;&amp; </span><span class=cF5>IsPixCovered0</span><span class=cF7>(</span><span class=cF0>win_task, x3, y3</span><span class=cF7>)</span><span class=cF0>)
<a name="l1868"></a>            </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l1869"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1870"></a>    </span><span class=cF1>if</span><span class=cF0> (x3 &gt;= dc-&gt;width || y3 &gt;= dc-&gt;height)
<a name="l1871"></a>        </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l1872"></a>
<a name="l1873"></a>    d = dc-&gt;width_internal * y3;
<a name="l1874"></a>    </span><span class=cF1>if</span><span class=cF0> (db)
<a name="l1875"></a>        db += d;
<a name="l1876"></a>
<a name="l1877"></a>    color = dc-&gt;color;
<a name="l1878"></a>    </span><span class=cF1>if</span><span class=cF0> (color.c1.rop &amp; </span><span class=cF7>(</span><span class=cF3>ROPBF_DITHER</span><span class=cF0> | </span><span class=cF3>ROPBF_PROBABILITY_DITHER</span><span class=cF7>)</span><span class=cF0>)
<a name="l1879"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l1880"></a>        dither = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l1881"></a>        </span><span class=cF1>if</span><span class=cF0> (color.c1.rop &amp; </span><span class=cF3>ROPBF_PROBABILITY_DITHER</span><span class=cF0>)
<a name="l1882"></a>        {
<a name="l1883"></a>            probability_dither = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l1884"></a>            color.c1.rop = color.c0.rop;
<a name="l1885"></a>        }
<a name="l1886"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l1887"></a>        {
<a name="l1888"></a>            probability_dither = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l1889"></a>            color.c1.rop = color.c0.rop;
<a name="l1890"></a>        }
<a name="l1891"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1892"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l1893"></a>        dither = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l1894"></a>    dst2 = dc-&gt;body + d;
<a name="l1895"></a>    </span><span class=cF1>while</span><span class=cF0> (</span><span class=cF3>TRUE</span><span class=cF0>)
<a name="l1896"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l1897"></a>        x3 = x;
<a name="l1898"></a>        </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>x3 &amp; (</span><span class=cF3>FONT_WIDTH</span><span class=cF0> - </span><span class=cFE>1</span><span class=cF0>)</span><span class=cF7>)</span><span class=cF0>)
<a name="l1899"></a>        {
<a name="l1900"></a>            </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l1901"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1902"></a>                </span><span class=cF1>if</span><span class=cF0> (x3 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l1903"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l1904"></a>                x3 += win_task-&gt;pix_left;
<a name="l1905"></a>                </span><span class=cF1>if</span><span class=cF0> (    !</span><span class=cF7>(</span><span class=cFE>0</span><span class=cF0> &lt;= x3 &lt;= win_task-&gt;pix_right</span><span class=cF7>)</span><span class=cF0> || x3 &gt;= dc-&gt;width ||
<a name="l1906"></a>                        !</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF7>)</span><span class=cF0> &amp;&amp; </span><span class=cF5>IsPixCovered0</span><span class=cF7>(</span><span class=cF0>win_task, x3, y3</span><span class=cF7>)</span><span class=cF0>)
<a name="l1907"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l1908"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1909"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l1910"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1911"></a>                </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cFE>0</span><span class=cF0> &lt;= x3 &lt; dc-&gt;width</span><span class=cF7>)</span><span class=cF0>)
<a name="l1912"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l1913"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1914"></a>        }
<a name="l1915"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l1916"></a>            x3 += win_task-&gt;pix_left;
<a name="l1917"></a>
<a name="l1918"></a>        dst = dst2 + x3;
<a name="l1919"></a>
<a name="l1920"></a>        c = *dst;
<a name="l1921"></a>        </span><span class=cF1>if</span><span class=cF0> (db)
<a name="l1922"></a>        {
<a name="l1923"></a>            db2 = db + x3;
<a name="l1924"></a>            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cFE>0</span><span class=cF0> &lt;= z &lt;= *db2)
<a name="l1925"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1926"></a>                *db2 = z;
<a name="l1927"></a>                plot = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l1928"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1929"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l1930"></a>                plot = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l1931"></a>        }
<a name="l1932"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l1933"></a>            plot = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l1934"></a>
<a name="l1935"></a>        </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>not_color &amp;&amp; c != dc-&gt;color2 || !not_color &amp;&amp; c == dc-&gt;color2</span><span class=cF7>)</span><span class=cF0> &amp;&amp; plot)
<a name="l1936"></a>        {
<a name="l1937"></a>            </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_LOCATE_NEAREST</span><span class=cF0>)
<a name="l1938"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1939"></a>                dist = </span><span class=cF5>DistSqrI64</span><span class=cF0>(x3, y3, dc-&gt;cur_x, dc-&gt;cur_y);
<a name="l1940"></a>                </span><span class=cF1>if</span><span class=cF0> (dist &lt;= dc-&gt;nearest_dist)
<a name="l1941"></a>                    dc-&gt;nearest_dist = dist;
<a name="l1942"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1943"></a>            </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_RECORD_EXTENTS</span><span class=cF0>)
<a name="l1944"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1945"></a>                </span><span class=cF1>if</span><span class=cF0> (x3 &lt; dc-&gt;min_x)
<a name="l1946"></a>                    dc-&gt;min_x = x3;
<a name="l1947"></a>
<a name="l1948"></a>                </span><span class=cF1>if</span><span class=cF0> (x3 &gt; dc-&gt;max_x)
<a name="l1949"></a>                    dc-&gt;max_x = x3;
<a name="l1950"></a>
<a name="l1951"></a>                </span><span class=cF1>if</span><span class=cF0> (y3 &lt; dc-&gt;min_y)
<a name="l1952"></a>                    dc-&gt;min_y = y3;
<a name="l1953"></a>
<a name="l1954"></a>                </span><span class=cF1>if</span><span class=cF0> (y3 &gt; dc-&gt;max_y)
<a name="l1955"></a>                    dc-&gt;max_y = y3;
<a name="l1956"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1957"></a>            dst = dst2 + x3;
<a name="l1958"></a>
<a name="l1959"></a>            c = color.c0.color;
<a name="l1960"></a>            </span><span class=cF1>if</span><span class=cF0> (dither)
<a name="l1961"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1962"></a>                </span><span class=cF1>if</span><span class=cF0> (probability_dither)
<a name="l1963"></a>                {
<a name="l1964"></a>                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>RandU16</span><span class=cF0> &lt; dc-&gt;dither_probability_u16)
<a name="l1965"></a>                        c = color.c1.color;
<a name="l1966"></a>                }
<a name="l1967"></a>                </span><span class=cF1>else</span><span class=cF0>
<a name="l1968"></a>                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>x3 ^ y3</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>1</span><span class=cF0>)
<a name="l1969"></a>                        c = color.c1.color;
<a name="l1970"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1971"></a>            </span><span class=cF1>switch</span><span class=cF0> [color.c0.rop]
<a name="l1972"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l1973"></a>                </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_EQU</span><span class=cF0>:
<a name="l1974"></a>                </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_MONO</span><span class=cF0>:
<a name="l1975"></a>                    *dst = c;
<a name="l1976"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l1977"></a>
<a name="l1978"></a>                </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_COLLISION</span><span class=cF0>:
<a name="l1979"></a>                    c2 = *dst;
<a name="l1980"></a>                    </span><span class=cF1>if</span><span class=cF0> (c2 != </span><span class=cF3>TRANSPARENT</span><span class=cF0> &amp;&amp; c2 != bkcolor.c0.color)
<a name="l1981"></a>                        dc-&gt;collision_count++;
<a name="l1982"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l1983"></a>
<a name="l1984"></a>                </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_XOR</span><span class=cF0>:
<a name="l1985"></a>                    *dst ^= c;
<a name="l1986"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l1987"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l1988"></a>            res++;
<a name="l1989"></a>            x++;
<a name="l1990"></a>        }
<a name="l1991"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l1992"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l1993"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l1994"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l1995"></a>        *x1 = x - </span><span class=cFE>1</span><span class=cF0> - win_task-&gt;scroll_x;
<a name="l1996"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l1997"></a>        *x1 = x - </span><span class=cFE>1</span><span class=cF0>;
<a name="l1998"></a>    x = x2 - </span><span class=cFE>1</span><span class=cF0>;
<a name="l1999"></a>    </span><span class=cF1>while</span><span class=cF0> (</span><span class=cF3>TRUE</span><span class=cF0>)
<a name="l2000"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2001"></a>        x3 = x;
<a name="l2002"></a>        </span><span class=cF1>if</span><span class=cF0> (x3 &amp; </span><span class=cF7>(</span><span class=cF3>FONT_WIDTH</span><span class=cF0> - </span><span class=cFE>1</span><span class=cF7>)</span><span class=cF0> == </span><span class=cF3>FONT_WIDTH</span><span class=cF0> - </span><span class=cFE>1</span><span class=cF0>)
<a name="l2003"></a>        {
<a name="l2004"></a>            </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l2005"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l2006"></a>                </span><span class=cF1>if</span><span class=cF0> (x3 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l2007"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l2008"></a>                x3 += win_task-&gt;pix_left;
<a name="l2009"></a>                </span><span class=cF1>if</span><span class=cF0> (    !</span><span class=cF7>(</span><span class=cFE>0</span><span class=cF0> &lt;= x3 &lt;= win_task-&gt;pix_right</span><span class=cF7>)</span><span class=cF0> || x3 &gt;= dc-&gt;width ||
<a name="l2010"></a>                        !</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF7>)</span><span class=cF0> &amp;&amp; </span><span class=cF5>IsPixCovered0</span><span class=cF7>(</span><span class=cF0>win_task, x3, y3</span><span class=cF7>)</span><span class=cF0>)
<a name="l2011"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l2012"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l2013"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l2014"></a>                </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cFE>0</span><span class=cF0> &lt;= x3 &lt; dc-&gt;width</span><span class=cF7>)</span><span class=cF0>)
<a name="l2015"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l2016"></a>        }
<a name="l2017"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l2018"></a>            x3 += win_task-&gt;pix_left;
<a name="l2019"></a>
<a name="l2020"></a>        dst = dst2 + x3;
<a name="l2021"></a>        c = *dst;
<a name="l2022"></a>        </span><span class=cF1>if</span><span class=cF0> (db)
<a name="l2023"></a>        {
<a name="l2024"></a>            db2 = db + x3;
<a name="l2025"></a>            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cFE>0</span><span class=cF0> &lt;= z &lt;= *db2)
<a name="l2026"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l2027"></a>                *db2 = z;
<a name="l2028"></a>                plot = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l2029"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l2030"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l2031"></a>                plot = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l2032"></a>        }
<a name="l2033"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l2034"></a>            plot = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l2035"></a>
<a name="l2036"></a>        </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>not_color &amp;&amp; c != dc-&gt;color2 || !not_color &amp;&amp; c == dc-&gt;color2</span><span class=cF7>)</span><span class=cF0> &amp;&amp; plot)
<a name="l2037"></a>        {
<a name="l2038"></a>            </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_LOCATE_NEAREST</span><span class=cF0>)
<a name="l2039"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l2040"></a>                dist = </span><span class=cF5>DistSqrI64</span><span class=cF0>(x3, y3, dc-&gt;cur_x, dc-&gt;cur_y);
<a name="l2041"></a>                </span><span class=cF1>if</span><span class=cF0> (dist &lt;= dc-&gt;nearest_dist)
<a name="l2042"></a>                    dc-&gt;nearest_dist = dist;
<a name="l2043"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l2044"></a>            </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_RECORD_EXTENTS</span><span class=cF0>)
<a name="l2045"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l2046"></a>                </span><span class=cF1>if</span><span class=cF0> (x3 &lt; dc-&gt;min_x)
<a name="l2047"></a>                    dc-&gt;min_x = x3;
<a name="l2048"></a>                </span><span class=cF1>if</span><span class=cF0> (x3 &gt; dc-&gt;max_x)
<a name="l2049"></a>                    dc-&gt;max_x = x3;
<a name="l2050"></a>                </span><span class=cF1>if</span><span class=cF0> (y3 &lt; dc-&gt;min_y)
<a name="l2051"></a>                    dc-&gt;min_y = y3;
<a name="l2052"></a>                </span><span class=cF1>if</span><span class=cF0> (y3 &gt; dc-&gt;max_y)
<a name="l2053"></a>                    dc-&gt;max_y = y3;
<a name="l2054"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l2055"></a>            dst = dst2 + x3;
<a name="l2056"></a>
<a name="l2057"></a>            c = color.c0.color;
<a name="l2058"></a>            </span><span class=cF1>if</span><span class=cF0> (dither)
<a name="l2059"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l2060"></a>                </span><span class=cF1>if</span><span class=cF0> (probability_dither)
<a name="l2061"></a>                {
<a name="l2062"></a>                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>RandU16</span><span class=cF0> &lt; dc-&gt;dither_probability_u16)
<a name="l2063"></a>                        c = color.c1.color;
<a name="l2064"></a>                }
<a name="l2065"></a>                </span><span class=cF1>else</span><span class=cF0>
<a name="l2066"></a>                    </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>x3 ^ y3</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>1</span><span class=cF0>)
<a name="l2067"></a>                        c = color.c1.color;
<a name="l2068"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l2069"></a>            </span><span class=cF1>switch</span><span class=cF0> [color.c0.rop]
<a name="l2070"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l2071"></a>                </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_EQU</span><span class=cF0>:
<a name="l2072"></a>                </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_MONO</span><span class=cF0>:
<a name="l2073"></a>                    *dst = c;
<a name="l2074"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l2075"></a>
<a name="l2076"></a>                </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_COLLISION</span><span class=cF0>:
<a name="l2077"></a>                    c2 = *dst;
<a name="l2078"></a>                    </span><span class=cF1>if</span><span class=cF0> (c2 != </span><span class=cF3>TRANSPARENT</span><span class=cF0> &amp;&amp; c2 != bkcolor.c0.color)
<a name="l2079"></a>                        dc-&gt;collision_count++;
<a name="l2080"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l2081"></a>
<a name="l2082"></a>                </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_XOR</span><span class=cF0>:
<a name="l2083"></a>                    *dst ^= c;
<a name="l2084"></a>                    </span><span class=cF1>break</span><span class=cF0>;
<a name="l2085"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l2086"></a>            res++;
<a name="l2087"></a>            x--;
<a name="l2088"></a>        }
<a name="l2089"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l2090"></a>            </span><span class=cF1>break</span><span class=cF0>;
<a name="l2091"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2092"></a>    </span><span class=cF5>BEqual</span><span class=cF0>(&amp;</span><span class=cF5>Fs</span><span class=cF0>-&gt;task_flags, </span><span class=cF3>TASKf_NONTIMER_RAND</span><span class=cF0>, was_timer_rand);
<a name="l2093"></a>
<a name="l2094"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l2095"></a>gr_done:
<a name="l2096"></a>    </span><span class=cF5>BEqual</span><span class=cF0>(&amp;</span><span class=cF5>Fs</span><span class=cF0>-&gt;task_flags, </span><span class=cF3>TASKf_NONTIMER_RAND</span><span class=cF0>, was_timer_rand);
<a name="l2097"></a>
<a name="l2098"></a>    </span><span class=cF1>return</span><span class=cF0> </span><span class=cFE>0</span><span class=cF0>;
<a name="l2099"></a>}
<a name="l2100"></a>
<a name="l2101"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>GrHLine</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc=</span><span class=cFB>gr</span><span class=cF0>.dc, </span><span class=cF9>I64</span><span class=cF0> x1, </span><span class=cF9>I64</span><span class=cF0> x2, </span><span class=cF9>I64</span><span class=cF0> y, </span><span class=cF9>I64</span><span class=cF0> z1=</span><span class=cFE>0</span><span class=cF0>, </span><span class=cF9>I64</span><span class=cF0> z2=</span><span class=cFE>0</span><span class=cF0>)
<a name="l2102"></a>{</span><span class=cF2>//3D. No transformation or thick.</span><span class=cF0>
<a name="l2103"></a></span><span class=cF2>//Returns count of pixs changed</span><span class=cF0>
<a name="l2104"></a>    </span><span class=cF2>//Uses </span><a href="https://tomawezome.github.io/ZealOS/Demo/Lectures/FixedPoint.html#l1"><span class=cF4>fixed-point</span></a><span class=cF2>.</span><span class=cF0>
<a name="l2105"></a>    </span><span class=cF9>I64</span><span class=cF0>              dist, dx, dz, z, res = </span><span class=cFE>0</span><span class=cF0>, i, j, d;
<a name="l2106"></a>    </span><span class=cF1>U8</span><span class=cF0>              *dst;
<a name="l2107"></a>    </span><span class=cF9>CColorROPU32</span><span class=cF0>     c, c2, color = dc-&gt;color, bkcolor = dc-&gt;bkcolor, dither_colors;
<a name="l2108"></a>    </span><span class=cF9>I32</span><span class=cF0>             *db;
<a name="l2109"></a>    </span><span class=cF1>Bool</span><span class=cF0>             plot = </span><span class=cF3>TRUE</span><span class=cF0>, char_clear, dither, probability_dither,
<a name="l2110"></a>                     was_timer_rand = </span><span class=cF5>Bts</span><span class=cF0>(&amp;</span><span class=cF5>Fs</span><span class=cF0>-&gt;task_flags, </span><span class=cF3>TASKf_NONTIMER_RAND</span><span class=cF0>);
<a name="l2111"></a>    </span><span class=cF9>CTask</span><span class=cF0>           *win_task;
<a name="l2112"></a>
<a name="l2113"></a>
<a name="l2114"></a>    </span><span class=cF1>if</span><span class=cF0> (!dc-&gt;depth_buf)
<a name="l2115"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2116"></a>        </span><span class=cF1>if</span><span class=cF0> (x2 &lt; x1)
<a name="l2117"></a>            </span><span class=cF5>SwapI64</span><span class=cF0>(&amp;x1, &amp;x2);
<a name="l2118"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF5>GrRect</span><span class=cF0>(dc, x1, y, x2 - x1 + </span><span class=cFE>1</span><span class=cF0>, </span><span class=cFE>1</span><span class=cF0>);
<a name="l2119"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2120"></a>
<a name="l2121"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l2122"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2123"></a>        win_task = dc-&gt;win_task;
<a name="l2124"></a>        x1 += win_task-&gt;scroll_x;
<a name="l2125"></a>        x2 += win_task-&gt;scroll_x;
<a name="l2126"></a>        y  += win_task-&gt;scroll_y;
<a name="l2127"></a>        z1 += win_task-&gt;scroll_z;
<a name="l2128"></a>        z2 += win_task-&gt;scroll_z;
<a name="l2129"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2130"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_RECORD_EXTENTS</span><span class=cF0>)
<a name="l2131"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2132"></a>        </span><span class=cF1>if</span><span class=cF0> (x1 &lt; dc-&gt;min_x)
<a name="l2133"></a>            dc-&gt;min_x = x1;
<a name="l2134"></a>
<a name="l2135"></a>        </span><span class=cF1>if</span><span class=cF0> (x1 &gt; dc-&gt;max_x)
<a name="l2136"></a>            dc-&gt;max_x = x1;
<a name="l2137"></a>
<a name="l2138"></a>        </span><span class=cF1>if</span><span class=cF0> (x2 &lt; dc-&gt;min_x)
<a name="l2139"></a>            dc-&gt;min_x = x2;
<a name="l2140"></a>
<a name="l2141"></a>        </span><span class=cF1>if</span><span class=cF0> (x2 &gt; dc-&gt;max_x)
<a name="l2142"></a>            dc-&gt;max_x = x2;
<a name="l2143"></a>
<a name="l2144"></a>        </span><span class=cF1>if</span><span class=cF0> (y &lt; dc-&gt;min_y)
<a name="l2145"></a>            dc-&gt;min_y = y;
<a name="l2146"></a>
<a name="l2147"></a>        </span><span class=cF1>if</span><span class=cF0> (y &gt; dc-&gt;max_y)
<a name="l2148"></a>            dc-&gt;max_y = y;
<a name="l2149"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2150"></a>    </span><span class=cF1>if</span><span class=cF0> (y &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l2151"></a>        </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l2152"></a>    </span><span class=cF1>if</span><span class=cF0> (x2 &lt; x1)
<a name="l2153"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2154"></a>        </span><span class=cF5>SwapI64</span><span class=cF0>(&amp;x1, &amp;x2);
<a name="l2155"></a>        </span><span class=cF5>SwapI64</span><span class=cF0>(&amp;z1, &amp;z2);
<a name="l2156"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2157"></a>    </span><span class=cF1>if</span><span class=cF0> (x2 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l2158"></a>        </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l2159"></a>    </span><span class=cF1>if</span><span class=cF0> (x1 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l2160"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2161"></a>        i = -x1;
<a name="l2162"></a>        x1 = </span><span class=cFE>0</span><span class=cF0>;
<a name="l2163"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2164"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l2165"></a>        i = </span><span class=cFE>0</span><span class=cF0>;
<a name="l2166"></a>    j = </span><span class=cFE>0</span><span class=cF0>;
<a name="l2167"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l2168"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2169"></a>        x1 += win_task-&gt;pix_left;
<a name="l2170"></a>        x2 += win_task-&gt;pix_left;
<a name="l2171"></a>        </span><span class=cF1>if</span><span class=cF0> (x1 &gt; win_task-&gt;pix_right)
<a name="l2172"></a>            </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l2173"></a>        </span><span class=cF1>if</span><span class=cF0> (x2 &gt; win_task-&gt;pix_right)
<a name="l2174"></a>        {
<a name="l2175"></a>            j = x2 - win_task-&gt;pix_right;
<a name="l2176"></a>            x2 = win_task-&gt;pix_right;
<a name="l2177"></a>        }
<a name="l2178"></a>        y += win_task-&gt;pix_top;
<a name="l2179"></a>        </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cFE>0</span><span class=cF0> &lt;= y &lt;= win_task-&gt;pix_bottom</span><span class=cF7>)</span><span class=cF0> || x2 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l2180"></a>            </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l2181"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2182"></a>    </span><span class=cF1>if</span><span class=cF0> (x1 &gt;= dc-&gt;width || y &gt;= dc-&gt;height)
<a name="l2183"></a>        </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l2184"></a>    dx = x2 + j - (x1 - i);
<a name="l2185"></a>    d = dc-&gt;width_internal * y + x1;
<a name="l2186"></a>    </span><span class=cF1>if</span><span class=cF0> (db = dc-&gt;depth_buf)
<a name="l2187"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2188"></a>        db += d;
<a name="l2189"></a>        </span><span class=cF1>if</span><span class=cF0> (dx)
<a name="l2190"></a>            dz = (z2 - z1) &lt;&lt; </span><span class=cFE>32</span><span class=cF0> / dx;
<a name="l2191"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l2192"></a>            dz = </span><span class=cFE>0</span><span class=cF0>;
<a name="l2193"></a>        z = z1 &lt;&lt; </span><span class=cFE>32</span><span class=cF0>;
<a name="l2194"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2195"></a>    </span><span class=cF1>if</span><span class=cF0> (i)
<a name="l2196"></a>        z += i * dz;
<a name="l2197"></a>    </span><span class=cF1>if</span><span class=cF0> (x2 &gt;= dc-&gt;width)
<a name="l2198"></a>        x2 = dc-&gt;width - </span><span class=cFE>1</span><span class=cF0>;
<a name="l2199"></a>
<a name="l2200"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_LOCATE_NEAREST</span><span class=cF0>)
<a name="l2201"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2202"></a>        </span><span class=cF1>if</span><span class=cF0> (x1 &lt;= dc-&gt;cur_x &lt;= x2)
<a name="l2203"></a>            dist = </span><span class=cFE>0</span><span class=cF0>;
<a name="l2204"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (dc-&gt;cur_x &lt; x1)
<a name="l2205"></a>            dist = </span><span class=cF5>SqrI64</span><span class=cF0>(x1 - dc-&gt;cur_x);
<a name="l2206"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l2207"></a>            dist = </span><span class=cF5>SqrI64</span><span class=cF0>(dc-&gt;cur_x - x2);
<a name="l2208"></a>        dist += </span><span class=cF5>SqrI64</span><span class=cF0>(y - dc-&gt;cur_y);
<a name="l2209"></a>        </span><span class=cF1>if</span><span class=cF0> (dist &lt;= dc-&gt;nearest_dist)
<a name="l2210"></a>            dc-&gt;nearest_dist = dist;
<a name="l2211"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2212"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_DONT_DRAW</span><span class=cF0>)
<a name="l2213"></a>        </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l2214"></a>
<a name="l2215"></a>    </span><span class=cF1>if</span><span class=cF0> (    !</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF7>)</span><span class=cF0> ||
<a name="l2216"></a>            win_task-&gt;next_task == </span><span class=cFB>sys_winmgr_task</span><span class=cF0> ||
<a name="l2217"></a>            dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF0> || !</span><span class=cF5>IsPixCovered0</span><span class=cF7>(</span><span class=cF0>win_task, x1, y</span><span class=cF7>)</span><span class=cF0>)
<a name="l2218"></a>        char_clear = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l2219"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l2220"></a>        char_clear = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l2221"></a>    </span><span class=cF1>if</span><span class=cF0> (color.c1.rop &amp; </span><span class=cF7>(</span><span class=cF3>ROPBF_DITHER</span><span class=cF0> | </span><span class=cF3>ROPBF_PROBABILITY_DITHER</span><span class=cF7>)</span><span class=cF0>)
<a name="l2222"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2223"></a>        dither = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l2224"></a>        </span><span class=cF1>if</span><span class=cF0> (color.c1.rop &amp; </span><span class=cF3>ROPBF_PROBABILITY_DITHER</span><span class=cF0>)
<a name="l2225"></a>        {
<a name="l2226"></a>            probability_dither = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l2227"></a>            color.c1.rop = color.c0.rop;
<a name="l2228"></a>            dither_colors = color;
<a name="l2229"></a>            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>RandU16</span><span class=cF0> &lt; dc-&gt;dither_probability_u16)
<a name="l2230"></a>                color.c0 = dither_colors.c1;
<a name="l2231"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l2232"></a>                color.c0 = dither_colors.c0;
<a name="l2233"></a>        }
<a name="l2234"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l2235"></a>        {
<a name="l2236"></a>            probability_dither = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l2237"></a>            color.c1.rop = color.c0.rop;
<a name="l2238"></a>            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>x1 ^ y</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>1</span><span class=cF0>)
<a name="l2239"></a>                </span><span class=cF5>SwapU16</span><span class=cF0>(&amp;color.c0, &amp;color.c1);
<a name="l2240"></a>        }
<a name="l2241"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2242"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l2243"></a>        dither = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l2244"></a>    </span><span class=cF1>while</span><span class=cF0> (x1 &lt;= x2)
<a name="l2245"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2246"></a>        </span><span class=cF1>if</span><span class=cF0> (char_clear)
<a name="l2247"></a>        {
<a name="l2248"></a>            </span><span class=cF1>if</span><span class=cF0> (db)
<a name="l2249"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l2250"></a>                </span><span class=cF1>if</span><span class=cF0> (</span><span class=cFE>0</span><span class=cF0> &lt;= z.i32[</span><span class=cFE>1</span><span class=cF0>] &lt;= *db)
<a name="l2251"></a>                {
<a name="l2252"></a>                    *db = z.i32[</span><span class=cFE>1</span><span class=cF0>];
<a name="l2253"></a>                    plot = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l2254"></a>                }
<a name="l2255"></a>                </span><span class=cF1>else</span><span class=cF0>
<a name="l2256"></a>                    plot = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l2257"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l2258"></a>            </span><span class=cF1>if</span><span class=cF0> (plot)
<a name="l2259"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l2260"></a>                dst = dc-&gt;body + d;
<a name="l2261"></a>                c = color.c0.color;
<a name="l2262"></a>                </span><span class=cF1>switch</span><span class=cF0> [color.c0.rop]
<a name="l2263"></a>                {
<a name="l2264"></a>                    </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_EQU</span><span class=cF0>:
<a name="l2265"></a>                    </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_MONO</span><span class=cF0>:
<a name="l2266"></a>                        *dst = c;
<a name="l2267"></a>                        </span><span class=cF1>break</span><span class=cF0>;
<a name="l2268"></a>
<a name="l2269"></a>                    </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_COLLISION</span><span class=cF0>:
<a name="l2270"></a>                        c2 = *dst;
<a name="l2271"></a>                        </span><span class=cF1>if</span><span class=cF0> (c2 != </span><span class=cF3>TRANSPARENT</span><span class=cF0> &amp;&amp; c2 != bkcolor.c0.color)
<a name="l2272"></a>                            dc-&gt;collision_count++;
<a name="l2273"></a>                        </span><span class=cF1>break</span><span class=cF0>;
<a name="l2274"></a>
<a name="l2275"></a>                    </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_XOR</span><span class=cF0>:
<a name="l2276"></a>                        *dst ^= c;
<a name="l2277"></a>                        </span><span class=cF1>break</span><span class=cF0>;
<a name="l2278"></a>                }
<a name="l2279"></a>                res++;
<a name="l2280"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l2281"></a>        }
<a name="l2282"></a>        </span><span class=cF1>if</span><span class=cF0> (dither)
<a name="l2283"></a>        {
<a name="l2284"></a>            </span><span class=cF1>if</span><span class=cF0> (probability_dither)
<a name="l2285"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l2286"></a>                </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>RandU16</span><span class=cF0> &lt; dc-&gt;dither_probability_u16)
<a name="l2287"></a>                    color.c0 = dither_colors.c1;
<a name="l2288"></a>                </span><span class=cF1>else</span><span class=cF0>
<a name="l2289"></a>                    color.c0 = dither_colors.c0;
<a name="l2290"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l2291"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l2292"></a>                </span><span class=cF5>SwapU16</span><span class=cF0>(&amp;color.c0, &amp;color.c1);
<a name="l2293"></a>        }
<a name="l2294"></a>        d++;
<a name="l2295"></a>        x1++;
<a name="l2296"></a>        </span><span class=cF1>if</span><span class=cF0> (db)
<a name="l2297"></a>            db++;
<a name="l2298"></a>        z += dz;
<a name="l2299"></a>        </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>x1 &amp; (</span><span class=cF3>FONT_WIDTH</span><span class=cF0> - </span><span class=cFE>1</span><span class=cF0>)</span><span class=cF7>)</span><span class=cF0> &amp;&amp; x1 &lt;= x2)
<a name="l2300"></a>        {
<a name="l2301"></a>            </span><span class=cF1>if</span><span class=cF0> (    !</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF7>)</span><span class=cF0>||
<a name="l2302"></a>                    win_task-&gt;next_task == </span><span class=cFB>sys_winmgr_task</span><span class=cF0> ||
<a name="l2303"></a>                    dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF0> || !</span><span class=cF5>IsPixCovered0</span><span class=cF7>(</span><span class=cF0>win_task, x1, y</span><span class=cF7>)</span><span class=cF0>)
<a name="l2304"></a>                char_clear = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l2305"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l2306"></a>                char_clear = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l2307"></a>        }
<a name="l2308"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2309"></a>gr_done:
<a name="l2310"></a>    </span><span class=cF5>BEqual</span><span class=cF0>(&amp;</span><span class=cF5>Fs</span><span class=cF0>-&gt;task_flags, </span><span class=cF3>TASKf_NONTIMER_RAND</span><span class=cF0>, was_timer_rand);
<a name="l2311"></a>
<a name="l2312"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l2313"></a>}
<a name="l2314"></a>
<a name="l2315"></a></span><span class=cF1>public</span><span class=cF0> </span><span class=cF9>I64</span><span class=cF0> </span><span class=cF5>GrVLine</span><span class=cF0>(</span><span class=cF9>CDC</span><span class=cF0> *dc=</span><span class=cFB>gr</span><span class=cF0>.dc, </span><span class=cF9>I64</span><span class=cF0> x, </span><span class=cF9>I64</span><span class=cF0> y1, </span><span class=cF9>I64</span><span class=cF0> y2, </span><span class=cF9>I64</span><span class=cF0> z1=</span><span class=cFE>0</span><span class=cF0>, </span><span class=cF9>I64</span><span class=cF0> z2=</span><span class=cFE>0</span><span class=cF0>)
<a name="l2316"></a>{</span><span class=cF2>//3D. No transformation or thick.</span><span class=cF0>
<a name="l2317"></a></span><span class=cF2>//Returns count of pixs changed</span><span class=cF0>
<a name="l2318"></a>    </span><span class=cF2>//Uses </span><a href="https://tomawezome.github.io/ZealOS/Demo/Lectures/FixedPoint.html#l1"><span class=cF4>fixed-point</span></a><span class=cF2>.</span><span class=cF0>
<a name="l2319"></a>    </span><span class=cF9>I64</span><span class=cF0>              dist, dy, dz, z, res = </span><span class=cFE>0</span><span class=cF0>, i, j, d;
<a name="l2320"></a>    </span><span class=cF1>U8</span><span class=cF0>              *dst;
<a name="l2321"></a>    </span><span class=cF9>CColorROPU32</span><span class=cF0>     c, c2, color = dc-&gt;color, bkcolor = dc-&gt;bkcolor, dither_colors;
<a name="l2322"></a>    </span><span class=cF9>I32</span><span class=cF0>             *db;
<a name="l2323"></a>    </span><span class=cF1>Bool</span><span class=cF0>             plot = </span><span class=cF3>TRUE</span><span class=cF0>, char_clear, dither, probability_dither,
<a name="l2324"></a>                     was_timer_rand = </span><span class=cF5>Bts</span><span class=cF0>(&amp;</span><span class=cF5>Fs</span><span class=cF0>-&gt;task_flags, </span><span class=cF3>TASKf_NONTIMER_RAND</span><span class=cF0>);
<a name="l2325"></a>    </span><span class=cF9>CTask</span><span class=cF0>           *win_task;
<a name="l2326"></a>
<a name="l2327"></a>
<a name="l2328"></a>    </span><span class=cF1>if</span><span class=cF0> (!dc-&gt;depth_buf)
<a name="l2329"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2330"></a>        </span><span class=cF1>if</span><span class=cF0> (y2 &lt; y1)
<a name="l2331"></a>            </span><span class=cF5>SwapI64</span><span class=cF0>(&amp;y1, &amp;y2);
<a name="l2332"></a>        </span><span class=cF1>return</span><span class=cF0> </span><span class=cF5>GrRect</span><span class=cF0>(dc, x, y1, </span><span class=cFE>1</span><span class=cF0>, y2 - y1 + </span><span class=cFE>1</span><span class=cF0>);
<a name="l2333"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2334"></a>
<a name="l2335"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l2336"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2337"></a>        win_task = dc-&gt;win_task;
<a name="l2338"></a>        x  += win_task-&gt;scroll_x;
<a name="l2339"></a>        y1 += win_task-&gt;scroll_y;
<a name="l2340"></a>        y2 += win_task-&gt;scroll_y;
<a name="l2341"></a>        z1 += win_task-&gt;scroll_z;
<a name="l2342"></a>        z2 += win_task-&gt;scroll_z;
<a name="l2343"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2344"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_RECORD_EXTENTS</span><span class=cF0>)
<a name="l2345"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2346"></a>        </span><span class=cF1>if</span><span class=cF0> (x &lt; dc-&gt;min_x)
<a name="l2347"></a>            dc-&gt;min_x = x;
<a name="l2348"></a>
<a name="l2349"></a>        </span><span class=cF1>if</span><span class=cF0> (x &gt; dc-&gt;max_x)
<a name="l2350"></a>            dc-&gt;max_x = x;
<a name="l2351"></a>
<a name="l2352"></a>        </span><span class=cF1>if</span><span class=cF0> (y1 &lt; dc-&gt;min_y)
<a name="l2353"></a>            dc-&gt;min_y = y1;
<a name="l2354"></a>
<a name="l2355"></a>        </span><span class=cF1>if</span><span class=cF0> (y1 &gt; dc-&gt;max_y)
<a name="l2356"></a>            dc-&gt;max_y = y1;
<a name="l2357"></a>
<a name="l2358"></a>        </span><span class=cF1>if</span><span class=cF0> (y2 &lt; dc-&gt;min_y)
<a name="l2359"></a>            dc-&gt;min_y = y2;
<a name="l2360"></a>
<a name="l2361"></a>        </span><span class=cF1>if</span><span class=cF0> (y2 &gt; dc-&gt;max_y)
<a name="l2362"></a>            dc-&gt;max_y = y2;
<a name="l2363"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2364"></a>    </span><span class=cF1>if</span><span class=cF0> (x &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l2365"></a>        </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l2366"></a>    </span><span class=cF1>if</span><span class=cF0> (y2 &lt; y1)
<a name="l2367"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2368"></a>        </span><span class=cF5>SwapI64</span><span class=cF0>(&amp;y1, &amp;y2);
<a name="l2369"></a>        </span><span class=cF5>SwapI64</span><span class=cF0>(&amp;z1, &amp;z2);
<a name="l2370"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2371"></a>    </span><span class=cF1>if</span><span class=cF0> (y2 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l2372"></a>        </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l2373"></a>    </span><span class=cF1>if</span><span class=cF0> (y1 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l2374"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2375"></a>        i = -y1;
<a name="l2376"></a>        y1 = </span><span class=cFE>0</span><span class=cF0>;
<a name="l2377"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2378"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l2379"></a>        i = </span><span class=cFE>0</span><span class=cF0>;
<a name="l2380"></a>    j = </span><span class=cFE>0</span><span class=cF0>;
<a name="l2381"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF0>)
<a name="l2382"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2383"></a>        y1 += win_task-&gt;pix_top;
<a name="l2384"></a>        y2 += win_task-&gt;pix_top;
<a name="l2385"></a>        </span><span class=cF1>if</span><span class=cF0> (y1 &gt; win_task-&gt;pix_bottom)
<a name="l2386"></a>            </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l2387"></a>        </span><span class=cF1>if</span><span class=cF0> (y2 &gt; win_task-&gt;pix_bottom)
<a name="l2388"></a>        {
<a name="l2389"></a>            j = y2 - win_task-&gt;pix_bottom;
<a name="l2390"></a>            y2 = win_task-&gt;pix_bottom;
<a name="l2391"></a>        }
<a name="l2392"></a>        x += win_task-&gt;pix_left;
<a name="l2393"></a>        </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cFE>0</span><span class=cF0> &lt;= x &lt;= win_task-&gt;pix_right</span><span class=cF7>)</span><span class=cF0> || y2 &lt; </span><span class=cFE>0</span><span class=cF0>)
<a name="l2394"></a>            </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l2395"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2396"></a>    </span><span class=cF1>if</span><span class=cF0> (y1 &gt;= dc-&gt;height || x &gt;= dc-&gt;width)
<a name="l2397"></a>        </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l2398"></a>    dy = y2 + j - (y1 - i);
<a name="l2399"></a>    d = dc-&gt;width_internal * y1 + x;
<a name="l2400"></a>    </span><span class=cF1>if</span><span class=cF0> (db = dc-&gt;depth_buf)
<a name="l2401"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2402"></a>        db += d;
<a name="l2403"></a>        </span><span class=cF1>if</span><span class=cF0> (dy)
<a name="l2404"></a>            dz = (z2 - z1) &lt;&lt; </span><span class=cFE>32</span><span class=cF0> / dy;
<a name="l2405"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l2406"></a>            dz = </span><span class=cFE>0</span><span class=cF0>;
<a name="l2407"></a>        z = z1 &lt;&lt; </span><span class=cFE>32</span><span class=cF0>;
<a name="l2408"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2409"></a>    </span><span class=cF1>if</span><span class=cF0> (i)
<a name="l2410"></a>        z += i * dz;
<a name="l2411"></a>    </span><span class=cF1>if</span><span class=cF0> (y2 &gt;= dc-&gt;height)
<a name="l2412"></a>        y2 = dc-&gt;height - </span><span class=cFE>1</span><span class=cF0>;
<a name="l2413"></a>
<a name="l2414"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_LOCATE_NEAREST</span><span class=cF0>)
<a name="l2415"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2416"></a>        </span><span class=cF1>if</span><span class=cF0> (y1 &lt;= dc-&gt;cur_y &lt;= y2)
<a name="l2417"></a>            dist = </span><span class=cFE>0</span><span class=cF0>;
<a name="l2418"></a>        </span><span class=cF1>else</span><span class=cF0> </span><span class=cF1>if</span><span class=cF0> (dc-&gt;cur_y &lt; y1)
<a name="l2419"></a>            dist = </span><span class=cF5>SqrI64</span><span class=cF0>(y1 - dc-&gt;cur_y);
<a name="l2420"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l2421"></a>            dist = </span><span class=cF5>SqrI64</span><span class=cF0>(dc-&gt;cur_y - y2);
<a name="l2422"></a>        dist += </span><span class=cF5>SqrI64</span><span class=cF0>(x - dc-&gt;cur_x);
<a name="l2423"></a>        </span><span class=cF1>if</span><span class=cF0> (dist &lt;= dc-&gt;nearest_dist)
<a name="l2424"></a>            dc-&gt;nearest_dist = dist;
<a name="l2425"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2426"></a>    </span><span class=cF1>if</span><span class=cF0> (dc-&gt;flags &amp; </span><span class=cF3>DCF_DONT_DRAW</span><span class=cF0>)
<a name="l2427"></a>        </span><span class=cF1>goto</span><span class=cF0> gr_done;
<a name="l2428"></a>
<a name="l2429"></a>    </span><span class=cF1>if</span><span class=cF0> (    !</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF7>)</span><span class=cF0> ||
<a name="l2430"></a>            win_task-&gt;next_task == </span><span class=cFB>sys_winmgr_task</span><span class=cF0> ||
<a name="l2431"></a>            dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF0> || !</span><span class=cF5>IsPixCovered0</span><span class=cF7>(</span><span class=cF0>win_task, x, y1</span><span class=cF7>)</span><span class=cF0>)
<a name="l2432"></a>        char_clear = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l2433"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l2434"></a>        char_clear = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l2435"></a>    </span><span class=cF1>if</span><span class=cF0> (color.c1.rop &amp; </span><span class=cF7>(</span><span class=cF3>ROPBF_DITHER</span><span class=cF0> | </span><span class=cF3>ROPBF_PROBABILITY_DITHER</span><span class=cF7>)</span><span class=cF0>)
<a name="l2436"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2437"></a>        dither = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l2438"></a>        </span><span class=cF1>if</span><span class=cF0> (color.c1.rop &amp; </span><span class=cF3>ROPBF_PROBABILITY_DITHER</span><span class=cF0>)
<a name="l2439"></a>        {
<a name="l2440"></a>            probability_dither = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l2441"></a>            color.c1.rop = color.c0.rop;
<a name="l2442"></a>            dither_colors = color;
<a name="l2443"></a>            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>RandU16</span><span class=cF0> &lt; dc-&gt;dither_probability_u16)
<a name="l2444"></a>                color.c0 = dither_colors.c1;
<a name="l2445"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l2446"></a>                color.c0 = dither_colors.c0;
<a name="l2447"></a>        }
<a name="l2448"></a>        </span><span class=cF1>else</span><span class=cF0>
<a name="l2449"></a>        {
<a name="l2450"></a>            probability_dither = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l2451"></a>            color.c1.rop = color.c0.rop;
<a name="l2452"></a>            </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF7>(</span><span class=cF0>x ^ y1</span><span class=cF7>)</span><span class=cF0> &amp; </span><span class=cFE>1</span><span class=cF0>)
<a name="l2453"></a>                </span><span class=cF5>SwapU16</span><span class=cF0>(&amp;color.c0, &amp;color.c1);
<a name="l2454"></a>        }
<a name="l2455"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2456"></a>    </span><span class=cF1>else</span><span class=cF0>
<a name="l2457"></a>        dither = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l2458"></a>    </span><span class=cF1>while</span><span class=cF0> (y1 &lt;= y2)
<a name="l2459"></a>    </span><span class=cF7>{</span><span class=cF0>
<a name="l2460"></a>        </span><span class=cF1>if</span><span class=cF0> (char_clear)
<a name="l2461"></a>        {
<a name="l2462"></a>            </span><span class=cF1>if</span><span class=cF0> (db)
<a name="l2463"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l2464"></a>                </span><span class=cF1>if</span><span class=cF0> (</span><span class=cFE>0</span><span class=cF0> &lt;= z.i32[</span><span class=cFE>1</span><span class=cF0>] &lt;= *db)
<a name="l2465"></a>                {
<a name="l2466"></a>                    *db = z.i32[</span><span class=cFE>1</span><span class=cF0>];
<a name="l2467"></a>                    plot = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l2468"></a>                }
<a name="l2469"></a>                </span><span class=cF1>else</span><span class=cF0>
<a name="l2470"></a>                    plot = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l2471"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l2472"></a>            </span><span class=cF1>if</span><span class=cF0> (plot)
<a name="l2473"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l2474"></a>                dst = dc-&gt;body + d;
<a name="l2475"></a>                c = color.c0.color;
<a name="l2476"></a>                </span><span class=cF1>switch</span><span class=cF0> [color.c0.rop]
<a name="l2477"></a>                {
<a name="l2478"></a>                    </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_EQU</span><span class=cF0>:
<a name="l2479"></a>                    </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_MONO</span><span class=cF0>:
<a name="l2480"></a>                        *dst = c;
<a name="l2481"></a>                        </span><span class=cF1>break</span><span class=cF0>;
<a name="l2482"></a>
<a name="l2483"></a>                    </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_COLLISION</span><span class=cF0>:
<a name="l2484"></a>                        c2 = *dst;
<a name="l2485"></a>                        </span><span class=cF1>if</span><span class=cF0> (c2 != </span><span class=cF3>TRANSPARENT</span><span class=cF0> &amp;&amp; c2 != bkcolor.c0.color)
<a name="l2486"></a>                            dc-&gt;collision_count++;
<a name="l2487"></a>                        </span><span class=cF1>break</span><span class=cF0>;
<a name="l2488"></a>
<a name="l2489"></a>                    </span><span class=cF1>case</span><span class=cF0> </span><span class=cF3>ROPB_XOR</span><span class=cF0>:
<a name="l2490"></a>                        *dst ^= c;
<a name="l2491"></a>                        </span><span class=cF1>break</span><span class=cF0>;
<a name="l2492"></a>                }
<a name="l2493"></a>                res++;
<a name="l2494"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l2495"></a>        }
<a name="l2496"></a>        </span><span class=cF1>if</span><span class=cF0> (dither)
<a name="l2497"></a>        {
<a name="l2498"></a>            </span><span class=cF1>if</span><span class=cF0> (probability_dither)
<a name="l2499"></a>            </span><span class=cF7>{</span><span class=cF0>
<a name="l2500"></a>                </span><span class=cF1>if</span><span class=cF0> (</span><span class=cF5>RandU16</span><span class=cF0> &lt; dc-&gt;dither_probability_u16)
<a name="l2501"></a>                    color.c0 = dither_colors.c1;
<a name="l2502"></a>                </span><span class=cF1>else</span><span class=cF0>
<a name="l2503"></a>                    color.c0 = dither_colors.c0;
<a name="l2504"></a>            </span><span class=cF7>}</span><span class=cF0>
<a name="l2505"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l2506"></a>                </span><span class=cF5>SwapU16</span><span class=cF0>(&amp;color.c0, &amp;color.c1);
<a name="l2507"></a>        }
<a name="l2508"></a>        d += dc-&gt;width_internal;
<a name="l2509"></a>        y1++;
<a name="l2510"></a>        </span><span class=cF1>if</span><span class=cF0> (db)
<a name="l2511"></a>            db += dc-&gt;width_internal;
<a name="l2512"></a>        z += dz;
<a name="l2513"></a>        </span><span class=cF1>if</span><span class=cF0> (!</span><span class=cF7>(</span><span class=cF0>y1 &amp; (</span><span class=cF3>FONT_HEIGHT</span><span class=cF0> - </span><span class=cFE>1</span><span class=cF0>)</span><span class=cF7>)</span><span class=cF0> &amp;&amp; y1 &lt;= y2)
<a name="l2514"></a>        {
<a name="l2515"></a>            </span><span class=cF1>if</span><span class=cF0> (    !</span><span class=cF7>(</span><span class=cF0>dc-&gt;flags &amp; </span><span class=cF3>DCF_SCREEN_BITMAP</span><span class=cF7>)</span><span class=cF0> ||
<a name="l2516"></a>                    win_task-&gt;next_task == </span><span class=cFB>sys_winmgr_task</span><span class=cF0> ||
<a name="l2517"></a>                    dc-&gt;flags &amp; </span><span class=cF3>DCF_ON_TOP</span><span class=cF0> || !</span><span class=cF5>IsPixCovered0</span><span class=cF7>(</span><span class=cF0>win_task, x, y1</span><span class=cF7>)</span><span class=cF0>)
<a name="l2518"></a>                char_clear = </span><span class=cF3>TRUE</span><span class=cF0>;
<a name="l2519"></a>            </span><span class=cF1>else</span><span class=cF0>
<a name="l2520"></a>                char_clear = </span><span class=cF3>FALSE</span><span class=cF0>;
<a name="l2521"></a>        }
<a name="l2522"></a>    </span><span class=cF7>}</span><span class=cF0>
<a name="l2523"></a>gr_done:
<a name="l2524"></a>    </span><span class=cF5>BEqual</span><span class=cF0>(&amp;</span><span class=cF5>Fs</span><span class=cF0>-&gt;task_flags, </span><span class=cF3>TASKf_NONTIMER_RAND</span><span class=cF0>, was_timer_rand);
<a name="l2525"></a>
<a name="l2526"></a>    </span><span class=cF1>return</span><span class=cF0> res;
<a name="l2527"></a>}
</span></pre></body>
</html>
