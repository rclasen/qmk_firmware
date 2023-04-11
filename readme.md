# Local hacks/keymaps for Quantum Mechanical Keyboard Firmware

based on an old version of [QMK](https://github.com/qmk/qmk_firmware).

Comes with my own OneShot/TapHold implementations using a custom
[myevent](/quantum/process_keycode/process_myevent.h) backend. I'm not
sure if that's still needed, but when I started using QMK in 2017 I 
couldn't get the following working:

* consistent behavior for Modifiers and layers
* allow "queueing" multiple oneshot operations
* consistent oneshot un/lock behavior
* avoid interfering with regular typing (TapHold)
* easy per-keymap customization (eg. suppress shift keys in my symbol
  layer and on numpad keys of nav layer)

I'm trying to keep my keymaps "similar". For simplifying this, all of
them use the [shared definitions](/mykeys.h). The shared definitions
also include some explanations/requirements I used to build the layout.

Most notably, I'm trying to move all modifiers/layers to the thumbs.
Thumb keys are arranged to allow holding 2 of them at once.

The layout tries to eliminate keys where I'd move my wrists too much:
Even on the "bigger" keyboards (ergodox, ...) I use only few of the
extra keys. I'm using the ergodox keymap as "master".

My keymaps (have ASCII art in keymap.c):

* [atreus](/keyboards/rclasen/atreus/keymaps/rclasen/) 2017/11 - Handwired
  atreus. Great staggering, but thumb keys are way too far up. I could use
  a bigger angle between the halves and the pinky column a bit futher
  down, but it's a good compromise to be portable (=transporting and
  setting up split boards somehow feels anoying). Could use 1 or two extra
  keys.  Got Lost.

* [atreus2](/keyboards/atreus/keymaps/rclasen/) 2020/08 - Replacement for
  lost atreus with hot-swap from falbatech.

* [atreus50](/keyboards/rclasen/atreus50/keymaps/rclasen/) 2019/08 - handwired
  atreus.  extra pinky column and thumb key is further down. Need to build
  and try.

* [chimera ergo 42](/keyboards/rclasen/chimera42/keymaps/rclasen/) 2018/08 -
  I love it. Thumb keys are where I need them, staggering is great. Has
  few keys I don't use. Clearly my favourite layout. I'm missing power
  switches to keep it from draining batterie when transporting it...  and
  the receiver could use some enclosure. Actually, I'm now looking for a
  wired alternative to make this a daily driver. I love how flat it is: I
  do get along without a wrist rest. Unfortunately it stopped working -
  not sure how I killed it.

* [corne](/keyboards/crkbd/keymaps/rclasen/) 2018/12 - AKA corne/helidox.
  Has similar issues as the iris, but is more compact. For whatever reason
  I'm having less issues with the thumb cluster when switching from
  ergodox/chimera/diverge to corne as I have with the iris. I love the pro
  micro placement. My current daily driver.

* [corne_aurora](/keyboards/splitkb/aurora/corne/keymaps/rclasen/) 2023/04
  - see corne. Got this to have a backup in a nicer case.

* [dactyl manuform](/keyboards/rclasen/dactyform/keymaps/rclasen/) 2018/09 -
  need to try.

* [diverge3](/keyboards/rclasen/diverge3/keymaps/rclasen/) 2016/09 - ported the
  lets split firmware to unikeyboards diverge3. Needs extra pullup
  resistors to get i2c working - official QMK diverge3 uses serial.
  Initially staggering felt strange... likely caused by the outermost
  column. Thumb cluster feels good. Index finger column could be a bit
  further down.  Once I started to see the single key that sticks out to
  the top as separate row, I started to love the staggering. Unfortunately
  it's with Gateron browns - and I can't stand typing on them. Plate
  doesn't support top-removal... and I'm too lazy to desolder.

* [ergodash](/keyboards/omkbd/ergodash/keymaps/rclasen/) 2020/02 - don't
  get along with the thumb cluster... the 2u keys are too far away... and
  the key next to M tucks too far below the palm. Has same staggering as
  ergodox.

* [ergodox](/keyboards/ergodox_ez/keymaps/rclasen/) 2016/09, 2016/11,
  2017/05 - that's what I started with. I've stopped using it as it caused
  thumb pain. It has way too many keys and is way too big, aswell.  My
  tenting stands make it even less portable.  Staggering is too low and
  the thumb cluster is a tad too wide. While you can get fitting keycaps,
  it's still quite limited. It's the master for my keymaps.

* [ergotravel](/keyboards/ergotravel/keymaps/rclasen/) 2018/07 - why on
  earth is the innermost thumb key tilted? It's useless and sacrifies
  another good thumb key below B. Staggering is like ergodox: Too
  conservative. Pro micro prevents later access to switches/leds/... and
  creates extra height.

* [fretboard](/keyboards/rclasen/fretboard/keymaps/rclasen/) 2020/04 - need to
  build + try.  Designed by [fretsome](https://www.reddit.com/u/Fretsome).
  Staggering + Thumb keys look amazing. Probably an amazing
  traveling/couch/lap-use board... mabye with bluetooth? Not sure if/how
  to protect the raw PCB, though.... so...  need ideas for a 'case'(?)

* [iris](/keyboards/keebio/iris/keymaps/rclasen/) 2017/12 - built it with
  2x1u thumb key ... but I don't like the upper position. Unfortunately
  the thumb key below c and v is a tiny bit too far under my palm for
  frequent use. It's nice to have the thumb keys shifted by .5u ... but
  I'd prefer to have them shifted the other direction. Staggering is like
  ergodox: Too conservative. Pro micro prevents later access to
  switches/leds/...  and creates extra height.

* [kimiko](/keyboards/keycapsss/kimiko/keymaps/rclasen/) 2021/08 - Coming back to
  a keyboard with reasonably aggressive stagger and an 'aligned' thumb
  cluster felt like coming home. I really like the layout. Seems to be an
  improved version of a Sofle v2 ... with per-key RGB. Would make it my
  daily driver if it wasn't that 'big' and I had a 2nd board with a
  similar layout for home+work.

* [kyria](/keyboards/splitkb/kyria/keymaps/rclasen/) 2019/09 - staggering feels
  great.  Thumb cluster is like iris + another key on each side. Need to
  try shifting my thumb layout.

* [lets split](/keyboards/lets_split/keymaps/rclasen/) 2017/11 - note that
  I start with the alphas on the outermost columns! While I'm heavily into
  columnar stagger I'm surprised how good I get along with a plain ortho
  layout. Though, my thumbs often loose their homing key -> needs
  significantly different caps for thumbs! On dox/diverge this is
  accomplished by the gap between bottom row and thumb cluster. Pro micro
  prevents later access to switches/leds/... and creates extra height.

* [levinson](/keyboards/keebio/levinson/keymaps/rclasen/) 2017/12 - same
  as lets split, but with backlight.

* [lily58](/keyboards/lily58/keymaps/rclasen/) 2020/02 - Has similar
  issues as iris. Just got it because of hot-swap support and better pro
  micro placement.

* [maltron](/keyboards/rclasen/maltron/keymaps/rclasen/) 2017/09 - handwired
  Maltron.  Thumb cluster is hard to use when resting your palm -> made it
  impossible for me to use it for long enough to get used to the dwells.
  Angle between halves is ok, but I do miss adjusting the angle when
  changing posture.

* [orthodox](/keyboards/orthodox/keymaps/rclasen/) 2017/12 - Got it to
  test the Thumb cluster. Upper thumb row is useless and moves the other
  thumb keys too far down. Bottom thumb keys could move closer to M. Pro
  micro prevents later access to switches/leds/... and creates extra
  height.

* [piantor](/keyboards/beekeeb/piantor/keymaps/rclasen/) 2023/04 - Was by
  far the fastest build I've ever had: No diodes and castellated holes on
  RPi made it a breeze. Stagger is nice but thumb cluster is too close to
  iris.  Just realized, that the travel of choc switches actually isn't
  too way of from regular switches.  Actually some mods (QMX, Zealencios,
  Jailhouse blue) reduce travel way more. Though, (my) chocs sound awful
  and the lack of profiled keycaps is killihg me.

* [reviung41](/keyboards/reviung/reviung41/keymaps/rclasen/) 2021/08 - No
  Idea why I got it. It's missing thumb keys and the stagger is
  insufficient.

* [tbk mini](/keyboards/bastardkb/tbkmini/rclasen/) 2021/07 - Tried it with
  SA caps and liked the curve... though, the thumb cluster is waaaay too
  wide.

[incomplete family picture](https://imgur.com/daPI7GG). Some keymap
folders have links to individual pictures / build logs.

## layout styles

switching between massively different layouts takes a (short) while to get
used to. Following list is helping me to pick 'similar' sets for work +
home.

keyboard        | split | stagger style | thumb style
---             | ---   | ---           | ---
atreus          | mono  | aggressive    | aligned (mostly)
atreus50        | mono  | aggressive    | aligned (mostly)
chimera ergo 42 | split | aggressive    | aligned
corne           | split | ergodox       | iris
dactyl manuform | split | maltron       | manuform
diverge3        | split | aggressive    | aligned (mostly)
ergodash        | split | ergodox       | iris
ergodox         | split | ergodox       | maltron
ergotravel      | split | ergodox       | broken
fretboard       | mono  | aggressive    | aligned (mostly)
iris            | split | ergodox       | iris
kimiko          | split | aggressive    | aligned (mostly)
kyria           | split | aggressive    | iris
lets split      | split | none          | aligned
levinson        | split | none          | aligned
lily58          | split | ergodox       | iris
maltron         | mono  | ergodox       | maltron
orthodox        | split | none          | maltron-like
piantor         | split | aggressive    | aligned (mostly)
reviung41       | mono  | ergodox       | broken
tbk mini        | split | maltron       | maltron-like

