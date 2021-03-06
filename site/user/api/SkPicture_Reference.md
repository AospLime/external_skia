SkPicture Reference
===


<a name='SkPicture'></a>

---

<pre style="padding: 1em 1em 1em 1em;width: 62.5em; background-color: #f0f0f0">
class <a href='SkPicture_Reference#SkPicture'>SkPicture</a> : public <a href='undocumented#SkRefCnt'>SkRefCnt</a> {

    static <a href='undocumented#sk_sp'>sk_sp</a><<a href='SkPicture_Reference#SkPicture'>SkPicture</a>> <a href='#SkPicture_MakeFromStream'>MakeFromStream</a>(<a href='SkStream_Reference#SkStream'>SkStream</a>* <a href='SkStream_Reference#Stream'>stream</a>,
                                           const <a href='undocumented#SkDeserialProcs'>SkDeserialProcs</a>* procs = nullptr);
    static <a href='undocumented#sk_sp'>sk_sp</a><<a href='SkPicture_Reference#SkPicture'>SkPicture</a>> <a href='#SkPicture_MakeFromData'>MakeFromData</a>(const <a href='undocumented#SkData'>SkData</a>* <a href='undocumented#Data'>data</a>,
                                         const <a href='undocumented#SkDeserialProcs'>SkDeserialProcs</a>* procs = nullptr);
    static <a href='undocumented#sk_sp'>sk_sp</a><<a href='SkPicture_Reference#SkPicture'>SkPicture</a>> <a href='#SkPicture_MakeFromData'>MakeFromData</a>(const void* <a href='undocumented#Data'>data</a>, size_t <a href='undocumented#Size'>size</a>,
                                         const <a href='undocumented#SkDeserialProcs'>SkDeserialProcs</a>* procs = nullptr);
    virtual void <a href='#SkPicture_playback'>playback</a>(<a href='SkCanvas_Reference#SkCanvas'>SkCanvas</a>* <a href='SkCanvas_Reference#Canvas'>canvas</a>, <a href='#SkPicture_AbortCallback'>AbortCallback</a>* callback = nullptr) const = 0;
    virtual <a href='SkRect_Reference#SkRect'>SkRect</a> <a href='#SkPicture_cullRect'>cullRect</a>() const = 0;
    uint32_t <a href='#SkPicture_uniqueID'>uniqueID</a>() const;
    <a href='undocumented#sk_sp'>sk_sp</a><<a href='undocumented#SkData'>SkData</a>> <a href='#SkPicture_serialize'>serialize</a>(const <a href='undocumented#SkSerialProcs'>SkSerialProcs</a>* procs = nullptr) const;
    void <a href='#SkPicture_serialize'>serialize</a>(<a href='SkWStream_Reference#SkWStream'>SkWStream</a>* <a href='SkStream_Reference#Stream'>stream</a>, const <a href='undocumented#SkSerialProcs'>SkSerialProcs</a>* procs = nullptr) const;
    static <a href='undocumented#sk_sp'>sk_sp</a><<a href='SkPicture_Reference#SkPicture'>SkPicture</a>> <a href='#SkPicture_MakePlaceholder'>MakePlaceholder</a>(<a href='SkRect_Reference#SkRect'>SkRect</a> cull);
    virtual int <a href='#SkPicture_approximateOpCount'>approximateOpCount</a>() const = 0;
    virtual size_t <a href='#SkPicture_approximateBytesUsed'>approximateBytesUsed</a>() const = 0;
};

</pre>

<a href='SkPicture_Reference#Picture'>Picture</a> records drawing commands made to <a href='SkCanvas_Reference#Canvas'>Canvas</a>. The command <a href='SkStream_Reference#Stream'>stream</a> may be
played in whole or in part at a later time.

<a href='SkPicture_Reference#Picture'>Picture</a> is an abstract class. <a href='SkPicture_Reference#Picture'>Picture</a> may be generated by <a href='#Picture_Recorder'>Picture_Recorder</a>
or <a href='undocumented#Drawable'>Drawable</a>, or from <a href='SkPicture_Reference#Picture'>Picture</a> previously saved to <a href='undocumented#Data'>Data</a> or <a href='SkStream_Reference#Stream'>Stream</a>.

<a href='SkPicture_Reference#Picture'>Picture</a> may contain any <a href='SkCanvas_Reference#Canvas'>Canvas</a> drawing command, as well as one or more
<a href='#Canvas_Matrix'>Canvas_Matrix</a> or <a href='#Canvas_Clip'>Canvas_Clip</a>. <a href='SkPicture_Reference#Picture'>Picture</a> has a cull <a href='SkRect_Reference#Rect'>Rect</a>, which is used as
a bounding box hint. To limit <a href='SkPicture_Reference#Picture'>Picture</a> bounds, use <a href='#Canvas_Clip'>Canvas_Clip</a> when
recording or drawing <a href='SkPicture_Reference#Picture'>Picture</a>.

<a name='SkPicture_AbortCallback'></a>

---

<pre style="padding: 1em 1em 1em 1em;width: 62.5em; background-color: #f0f0f0">
    class <a href='#SkPicture_AbortCallback'>AbortCallback</a> {
    public:
        <a href='#SkPicture_AbortCallback_AbortCallback'>AbortCallback()</a> {}
        virtual <a href='#SkPicture_AbortCallback_destructor'>~AbortCallback()</a> {}
        virtual bool <a href='#SkPicture_AbortCallback_abort'>abort()</a> = 0;
    };
</pre>

<a href='#SkPicture_AbortCallback'>AbortCallback</a> is an abstract class. An implementation of <a href='#SkPicture_AbortCallback'>AbortCallback</a> may
passed as a parameter to <a href='SkPicture_Reference#SkPicture'>SkPicture</a>::<a href='#SkPicture_playback'>playback</a>, to stop it before all drawing
commands have been processed.

If <a href='#SkPicture_AbortCallback'>AbortCallback</a>::<a href='#SkPicture_AbortCallback_abort'>abort</a> returns true, <a href='SkPicture_Reference#SkPicture'>SkPicture</a>::<a href='#SkPicture_playback'>playback</a> is interrupted.

<a name='SkPicture_AbortCallback_AbortCallback'></a>

---

<pre style="padding: 1em 1em 1em 1em; width: 62.5em;background-color: #f0f0f0">
<a href='#SkPicture_AbortCallback_AbortCallback'>AbortCallback()</a>
</pre>

Has no effect.

### Return Value

abstract class cannot be instantiated

### See Also

<a href='#SkPicture_playback'>playback</a>

<a name='SkPicture_AbortCallback_destructor'></a>

---

<pre style="padding: 1em 1em 1em 1em; width: 62.5em;background-color: #f0f0f0">
virtual <a href='#SkPicture_AbortCallback_destructor'>~AbortCallback()</a>
</pre>

Has no effect.

### See Also

<a href='#SkPicture_playback'>playback</a>

<a name='SkPicture_AbortCallback_abort'></a>

---

<pre style="padding: 1em 1em 1em 1em; width: 62.5em;background-color: #f0f0f0">
virtual bool <a href='#SkPicture_AbortCallback_abort'>abort()</a> = 0
</pre>

Stops <a href='SkPicture_Reference#SkPicture'>SkPicture</a> playback when some condition is met. A subclass of
<a href='#SkPicture_AbortCallback'>AbortCallback</a> provides an override for <a href='#SkPicture_AbortCallback_abort'>abort()</a> that can stop <a href='SkPicture_Reference#SkPicture'>SkPicture</a>::<a href='#SkPicture_playback'>playback</a>.

The part of <a href='SkPicture_Reference#SkPicture'>SkPicture</a> drawn when aborted is undefined. <a href='SkPicture_Reference#SkPicture'>SkPicture</a> instantiations are
free to stop drawing at different <a href='SkPoint_Reference#Point'>points</a> during playback.

If the abort happens inside one or more calls to <a href='SkCanvas_Reference#SkCanvas'>SkCanvas</a>::<a href='#SkCanvas_save'>save()</a>, stack
of <a href='SkCanvas_Reference#SkCanvas'>SkCanvas</a> <a href='SkMatrix_Reference#Matrix'>matrix</a> and <a href='SkCanvas_Reference#SkCanvas'>SkCanvas</a> clip values is restored to its state before
<a href='SkPicture_Reference#SkPicture'>SkPicture</a>::<a href='#SkPicture_playback'>playback</a> was called.

### Return Value

true to stop playback

### See Also

<a href='#SkPicture_playback'>playback</a>

### Example

<div><fiddle-embed name="56ed920dadbf2b2967ac45fb5a9bded6"><div>JustOneDraw allows the black rectangle to draw but stops playback before the
white rectangle appears.
</div></fiddle-embed></div>

<a name='SkPicture_MakeFromStream'></a>

---

<pre style="padding: 1em 1em 1em 1em; width: 62.5em;background-color: #f0f0f0">
static <a href='undocumented#sk_sp'>sk_sp</a>&lt;<a href='SkPicture_Reference#SkPicture'>SkPicture</a>&gt; <a href='#SkPicture_MakeFromStream'>MakeFromStream</a>(<a href='SkStream_Reference#SkStream'>SkStream</a>* <a href='SkStream_Reference#Stream'>stream</a>, const <a href='undocumented#SkDeserialProcs'>SkDeserialProcs</a>* procs = nullptr)
</pre>

Recreates <a href='SkPicture_Reference#SkPicture'>SkPicture</a> that was serialized into a <a href='#SkPicture_MakeFromStream_stream'>stream</a>. Returns constructed <a href='SkPicture_Reference#SkPicture'>SkPicture</a>
if successful; otherwise, returns nullptr. Fails if <a href='undocumented#Data'>data</a> does not permit
constructing valid <a href='SkPicture_Reference#SkPicture'>SkPicture</a>.

<a href='#SkPicture_MakeFromStream_procs'>procs</a>-><a href='#SkDeserialProcs_fPictureProc'>fPictureProc</a> permits supplying a custom function to decode <a href='SkPicture_Reference#SkPicture'>SkPicture</a>.
If <a href='#SkPicture_MakeFromStream_procs'>procs</a>-><a href='#SkDeserialProcs_fPictureProc'>fPictureProc</a> is nullptr, default decoding is used. <a href='#SkPicture_MakeFromStream_procs'>procs</a>-><a href='#SkDeserialProcs_fPictureCtx'>fPictureCtx</a>
may be used to provide user context to <a href='#SkPicture_MakeFromStream_procs'>procs</a>-><a href='#SkDeserialProcs_fPictureProc'>fPictureProc</a>; <a href='#SkPicture_MakeFromStream_procs'>procs</a>-><a href='#SkDeserialProcs_fPictureProc'>fPictureProc</a>
is called with a pointer to <a href='undocumented#Data'>data</a>, <a href='undocumented#Data'>data</a> byte length, and user context.

### Parameters

<table>  <tr>    <td><a name='SkPicture_MakeFromStream_stream'><code><strong>stream</strong></code></a></td>
    <td>container for serial <a href='undocumented#Data'>data</a></td>
  </tr>
  <tr>    <td><a name='SkPicture_MakeFromStream_procs'><code><strong>procs</strong></code></a></td>
    <td>custom serial <a href='undocumented#Data'>data</a> decoders; may be nullptr</td>
  </tr>
</table>

### Return Value

<a href='SkPicture_Reference#SkPicture'>SkPicture</a> constructed from <a href='#SkPicture_MakeFromStream_stream'>stream</a> <a href='undocumented#Data'>data</a>

### Example

<div><fiddle-embed name="404fb42560a289c2004cad1caf3b96de"></fiddle-embed></div>

### See Also

<a href='#SkPicture_MakeFromData'>MakeFromData</a> <a href='undocumented#SkPictureRecorder'>SkPictureRecorder</a>

<a name='SkPicture_MakeFromData'></a>

---

<pre style="padding: 1em 1em 1em 1em; width: 62.5em;background-color: #f0f0f0">
static <a href='undocumented#sk_sp'>sk_sp</a>&lt;<a href='SkPicture_Reference#SkPicture'>SkPicture</a>&gt; <a href='#SkPicture_MakeFromData'>MakeFromData</a>(const <a href='undocumented#SkData'>SkData</a>* <a href='undocumented#Data'>data</a>, const <a href='undocumented#SkDeserialProcs'>SkDeserialProcs</a>* procs = nullptr)
</pre>

Recreates <a href='SkPicture_Reference#SkPicture'>SkPicture</a> that was serialized into <a href='#SkPicture_MakeFromData_data'>data</a>. Returns constructed <a href='SkPicture_Reference#SkPicture'>SkPicture</a>
if successful; otherwise, returns nullptr. Fails if <a href='#SkPicture_MakeFromData_data'>data</a> does not permit
constructing valid <a href='SkPicture_Reference#SkPicture'>SkPicture</a>.

<a href='#SkPicture_MakeFromData_procs'>procs</a>-><a href='#SkDeserialProcs_fPictureProc'>fPictureProc</a> permits supplying a custom function to decode <a href='SkPicture_Reference#SkPicture'>SkPicture</a>.
If <a href='#SkPicture_MakeFromData_procs'>procs</a>-><a href='#SkDeserialProcs_fPictureProc'>fPictureProc</a> is nullptr, default decoding is used. <a href='#SkPicture_MakeFromData_procs'>procs</a>-><a href='#SkDeserialProcs_fPictureCtx'>fPictureCtx</a>
may be used to provide user context to <a href='#SkPicture_MakeFromData_procs'>procs</a>-><a href='#SkDeserialProcs_fPictureProc'>fPictureProc</a>; <a href='#SkPicture_MakeFromData_procs'>procs</a>-><a href='#SkDeserialProcs_fPictureProc'>fPictureProc</a>
is called with a pointer to <a href='#SkPicture_MakeFromData_data'>data</a>, <a href='#SkPicture_MakeFromData_data'>data</a> byte length, and user context.

### Parameters

<table>  <tr>    <td><a name='SkPicture_MakeFromData_data'><code><strong>data</strong></code></a></td>
    <td>container for serial <a href='#SkPicture_MakeFromData_data'>data</a></td>
  </tr>
  <tr>    <td><a name='SkPicture_MakeFromData_procs'><code><strong>procs</strong></code></a></td>
    <td>custom serial <a href='#SkPicture_MakeFromData_data'>data</a> decoders; may be nullptr</td>
  </tr>
</table>

### Return Value

<a href='SkPicture_Reference#SkPicture'>SkPicture</a> constructed from <a href='#SkPicture_MakeFromData_data'>data</a>

### Example

<div><fiddle-embed name="58b44bf47d8816782066618700afdecb"></fiddle-embed></div>

### See Also

<a href='#SkPicture_MakeFromStream'>MakeFromStream</a> <a href='undocumented#SkPictureRecorder'>SkPictureRecorder</a>

<a name='SkPicture_MakeFromData_2'></a>

---

<pre style="padding: 1em 1em 1em 1em; width: 62.5em;background-color: #f0f0f0">
static <a href='undocumented#sk_sp'>sk_sp</a>&lt;<a href='SkPicture_Reference#SkPicture'>SkPicture</a>&gt; <a href='#SkPicture_MakeFromData'>MakeFromData</a>(const void* <a href='undocumented#Data'>data</a>, size_t <a href='undocumented#Size'>size</a>,
                                     const <a href='undocumented#SkDeserialProcs'>SkDeserialProcs</a>* procs = nullptr)
</pre>

### Parameters

<table>  <tr>    <td><a name='SkPicture_MakeFromData_2_data'><code><strong>data</strong></code></a></td>
    <td>pointer to serial <a href='#SkPicture_MakeFromData_2_data'>data</a></td>
  </tr>
  <tr>    <td><a name='SkPicture_MakeFromData_2_size'><code><strong>size</strong></code></a></td>
    <td><a href='#SkPicture_MakeFromData_2_size'>size</a> of <a href='#SkPicture_MakeFromData_2_data'>data</a></td>
  </tr>
  <tr>    <td><a name='SkPicture_MakeFromData_2_procs'><code><strong>procs</strong></code></a></td>
    <td>custom serial <a href='#SkPicture_MakeFromData_2_data'>data</a> decoders; may be nullptr</td>
  </tr>
</table>

### Return Value

<a href='SkPicture_Reference#SkPicture'>SkPicture</a> constructed from <a href='#SkPicture_MakeFromData_2_data'>data</a>

### Example

<div><fiddle-embed name="30b9f1b310187db6aff720a5d67591e2"></fiddle-embed></div>

### See Also

<a href='#SkPicture_MakeFromStream'>MakeFromStream</a> <a href='undocumented#SkPictureRecorder'>SkPictureRecorder</a>

<a name='SkPicture_playback'></a>

---

<pre style="padding: 1em 1em 1em 1em; width: 62.5em;background-color: #f0f0f0">
virtual void playback(<a href='SkCanvas_Reference#SkCanvas'>SkCanvas</a>* <a href='SkCanvas_Reference#Canvas'>canvas</a>, <a href='#SkPicture_AbortCallback'>AbortCallback</a>* callback = nullptr) const = 0
</pre>

Replays the drawing commands on the specified <a href='#SkPicture_playback_canvas'>canvas</a>. In the case that the
commands are recorded, each command in the <a href='SkPicture_Reference#SkPicture'>SkPicture</a> is sent separately to <a href='#SkPicture_playback_canvas'>canvas</a>.

To add a single command to draw <a href='SkPicture_Reference#SkPicture'>SkPicture</a> to recording <a href='#SkPicture_playback_canvas'>canvas</a>, call
<a href='SkCanvas_Reference#SkCanvas'>SkCanvas</a>::<a href='#SkCanvas_drawPicture'>drawPicture</a> instead.

### Parameters

<table>  <tr>    <td><a name='SkPicture_playback_canvas'><code><strong>canvas</strong></code></a></td>
    <td>receiver of drawing commands</td>
  </tr>
  <tr>    <td><a name='SkPicture_playback_callback'><code><strong>callback</strong></code></a></td>
    <td>allows interruption of playback</td>
  </tr>
</table>

### Example

<div><fiddle-embed name="6b0ffb03ba05f526b345dc65a1c73fe4"></fiddle-embed></div>

### See Also

<a href='SkCanvas_Reference#SkCanvas'>SkCanvas</a>::<a href='#SkCanvas_drawPicture'>drawPicture</a>

<a name='SkPicture_cullRect'></a>

---

<pre style="padding: 1em 1em 1em 1em; width: 62.5em;background-color: #f0f0f0">
virtual <a href='SkRect_Reference#SkRect'>SkRect</a> <a href='#SkPicture_cullRect'>cullRect</a>() const = 0
</pre>

Returns cull <a href='SkRect_Reference#SkRect'>SkRect</a> for this <a href='SkPicture_Reference#Picture'>picture</a>, passed in when <a href='SkPicture_Reference#SkPicture'>SkPicture</a> was created.
Returned <a href='SkRect_Reference#SkRect'>SkRect</a> does not specify clipping <a href='SkRect_Reference#SkRect'>SkRect</a> for <a href='SkPicture_Reference#SkPicture'>SkPicture</a>; cull is hint
of <a href='SkPicture_Reference#SkPicture'>SkPicture</a> bounds.

<a href='SkPicture_Reference#SkPicture'>SkPicture</a> is free to discard recorded drawing commands that fall outside
cull.

### Return Value

bounds passed when <a href='SkPicture_Reference#SkPicture'>SkPicture</a> was created

### Example

<div><fiddle-embed name="15bb9a9596b40c5e2045f76e8c1dcf8e"><div><a href='SkPicture_Reference#Picture'>Picture</a> recorded bounds are smaller than contents; contents outside recorded
bounds may be drawn, and are drawn in this example.
</div></fiddle-embed></div>

### See Also

<a href='SkCanvas_Reference#SkCanvas'>SkCanvas</a>::<a href='#SkCanvas_clipRect'>clipRect</a>

<a name='SkPicture_uniqueID'></a>

---

<pre style="padding: 1em 1em 1em 1em; width: 62.5em;background-color: #f0f0f0">
uint32_t <a href='#SkPicture_uniqueID'>uniqueID</a>()const
</pre>

Returns a non-zero value unique among <a href='SkPicture_Reference#SkPicture'>SkPicture</a> in Skia process.

### Return Value

identifier for <a href='SkPicture_Reference#SkPicture'>SkPicture</a>

### Example

<div><fiddle-embed name="8e4257245c988c600410fe4fd7293f07">

#### Example Output

~~~~
empty picture id = 1
placeholder id = 2
~~~~

</fiddle-embed></div>

### See Also

<a href='undocumented#SkRefCnt'>SkRefCnt</a>

<a name='SkPicture_serialize'></a>

---

<pre style="padding: 1em 1em 1em 1em; width: 62.5em;background-color: #f0f0f0">
<a href='undocumented#sk_sp'>sk_sp</a>&lt;<a href='undocumented#SkData'>SkData</a>&gt; <a href='#SkPicture_serialize'>serialize</a>(const <a href='undocumented#SkSerialProcs'>SkSerialProcs</a>* procs = nullptr)const
</pre>

Returns storage containing <a href='undocumented#SkData'>SkData</a> describing <a href='SkPicture_Reference#SkPicture'>SkPicture</a>, using optional custom
encoders.

<a href='#SkPicture_serialize_procs'>procs</a>-><a href='#SkSerialProcs_fPictureProc'>fPictureProc</a> permits supplying a custom function to encode <a href='SkPicture_Reference#SkPicture'>SkPicture</a>.
If <a href='#SkPicture_serialize_procs'>procs</a>-><a href='#SkSerialProcs_fPictureProc'>fPictureProc</a> is nullptr, default encoding is used. <a href='#SkPicture_serialize_procs'>procs</a>-><a href='#SkSerialProcs_fPictureCtx'>fPictureCtx</a>
may be used to provide user context to <a href='#SkPicture_serialize_procs'>procs</a>-><a href='#SkSerialProcs_fPictureProc'>fPictureProc</a>; <a href='#SkPicture_serialize_procs'>procs</a>-><a href='#SkSerialProcs_fPictureProc'>fPictureProc</a>
is called with a pointer to <a href='SkPicture_Reference#SkPicture'>SkPicture</a> and user context.

### Parameters

<table>  <tr>    <td><a name='SkPicture_serialize_procs'><code><strong>procs</strong></code></a></td>
    <td>custom serial <a href='undocumented#Data'>data</a> encoders; may be nullptr</td>
  </tr>
</table>

### Return Value

storage containing serialized <a href='SkPicture_Reference#SkPicture'>SkPicture</a>

### Example

<div><fiddle-embed name="dacdebe1355c884ebd3c2ea038cc7a20"></fiddle-embed></div>

### See Also

<a href='#SkPicture_MakeFromData'>MakeFromData</a> <a href='undocumented#SkData'>SkData</a> <a href='undocumented#SkSerialProcs'>SkSerialProcs</a>

<a name='SkPicture_serialize_2'></a>

---

<pre style="padding: 1em 1em 1em 1em; width: 62.5em;background-color: #f0f0f0">
void <a href='#SkPicture_serialize'>serialize</a>(<a href='SkWStream_Reference#SkWStream'>SkWStream</a>* <a href='SkStream_Reference#Stream'>stream</a>, const <a href='undocumented#SkSerialProcs'>SkSerialProcs</a>* procs = nullptr)const
</pre>

Writes <a href='SkPicture_Reference#Picture'>picture</a> to <a href='#SkPicture_serialize_2_stream'>stream</a>, using optional custom encoders.

<a href='#SkPicture_serialize_2_procs'>procs</a>-><a href='#SkSerialProcs_fPictureProc'>fPictureProc</a> permits supplying a custom function to encode <a href='SkPicture_Reference#SkPicture'>SkPicture</a>.
If <a href='#SkPicture_serialize_2_procs'>procs</a>-><a href='#SkSerialProcs_fPictureProc'>fPictureProc</a> is nullptr, default encoding is used. <a href='#SkPicture_serialize_2_procs'>procs</a>-><a href='#SkSerialProcs_fPictureCtx'>fPictureCtx</a>
may be used to provide user context to <a href='#SkPicture_serialize_2_procs'>procs</a>-><a href='#SkSerialProcs_fPictureProc'>fPictureProc</a>; <a href='#SkPicture_serialize_2_procs'>procs</a>-><a href='#SkSerialProcs_fPictureProc'>fPictureProc</a>
is called with a pointer to <a href='SkPicture_Reference#SkPicture'>SkPicture</a> and user context.

### Parameters

<table>  <tr>    <td><a name='SkPicture_serialize_2_stream'><code><strong>stream</strong></code></a></td>
    <td>writable serial <a href='undocumented#Data'>data</a> <a href='#SkPicture_serialize_2_stream'>stream</a></td>
  </tr>
  <tr>    <td><a name='SkPicture_serialize_2_procs'><code><strong>procs</strong></code></a></td>
    <td>custom serial <a href='undocumented#Data'>data</a> encoders; may be nullptr</td>
  </tr>
</table>

### Example

<div><fiddle-embed name="30b9f1b310187db6aff720a5d67591e2"></fiddle-embed></div>

### See Also

<a href='#SkPicture_MakeFromStream'>MakeFromStream</a> <a href='SkWStream_Reference#SkWStream'>SkWStream</a> <a href='undocumented#SkSerialProcs'>SkSerialProcs</a>

<a name='SkPicture_MakePlaceholder'></a>

---

<pre style="padding: 1em 1em 1em 1em; width: 62.5em;background-color: #f0f0f0">
static <a href='undocumented#sk_sp'>sk_sp</a>&lt;<a href='SkPicture_Reference#SkPicture'>SkPicture</a>&gt; <a href='#SkPicture_MakePlaceholder'>MakePlaceholder</a>(<a href='SkRect_Reference#SkRect'>SkRect</a> cull)
</pre>

Returns a placeholder <a href='SkPicture_Reference#SkPicture'>SkPicture</a>. Result does not draw, and contains only
<a href='#SkPicture_MakePlaceholder_cull'>cull</a> <a href='SkRect_Reference#SkRect'>SkRect</a>, a hint of its bounds. Result is immutable; it cannot be changed
later. Result identifier is unique.

Returned placeholder can be intercepted during playback to insert other
commands into <a href='SkCanvas_Reference#SkCanvas'>SkCanvas</a> draw <a href='SkStream_Reference#Stream'>stream</a>.

### Parameters

<table>  <tr>    <td><a name='SkPicture_MakePlaceholder_cull'><code><strong>cull</strong></code></a></td>
    <td>placeholder dimensions</td>
  </tr>
</table>

### Return Value

placeholder with unique identifier

### Example

<div><fiddle-embed name="0d2cbf82f490ffb180e0b4531afa232c"></fiddle-embed></div>

### See Also

<a href='#SkPicture_MakeFromStream'>MakeFromStream</a> <a href='#SkPicture_MakeFromData'>MakeFromData</a> <a href='#SkPicture_uniqueID'>uniqueID</a>

<a name='SkPicture_approximateOpCount'></a>

---

<pre style="padding: 1em 1em 1em 1em; width: 62.5em;background-color: #f0f0f0">
virtual int <a href='#SkPicture_approximateOpCount'>approximateOpCount</a>() const = 0
</pre>

Returns the approximate number of operations in <a href='SkPicture_Reference#SkPicture'>SkPicture</a>. Returned value
may be greater or less than the number of <a href='SkCanvas_Reference#SkCanvas'>SkCanvas</a> calls
recorded: some calls may be recorded as more than one operation, other
calls may be optimized away.

### Return Value

approximate operation count

### Example

<div><fiddle-embed name="4b3d879118ef770d1f11a23c6493b2c4"></fiddle-embed></div>

### See Also

<a href='#SkPicture_approximateBytesUsed'>approximateBytesUsed</a>

<a name='SkPicture_approximateBytesUsed'></a>

---

<pre style="padding: 1em 1em 1em 1em; width: 62.5em;background-color: #f0f0f0">
virtual size_t <a href='#SkPicture_approximateBytesUsed'>approximateBytesUsed</a>() const = 0
</pre>

Returns the approximate byte <a href='undocumented#Size'>size</a> of <a href='SkPicture_Reference#SkPicture'>SkPicture</a>. Does not include large objects
referenced by <a href='SkPicture_Reference#SkPicture'>SkPicture</a>.

### Return Value

approximate <a href='undocumented#Size'>size</a>

### Example

<div><fiddle-embed name="ececbda21218bd732394a305dba393a2"></fiddle-embed></div>

### See Also

<a href='#SkPicture_approximateOpCount'>approximateOpCount</a>

