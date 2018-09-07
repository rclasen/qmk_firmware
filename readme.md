# Local hacks/keymaps for Quantum Mechanical Keyboard Firmware

based on an old version of [QMK](https://github.com/qmk/qmk_firmware).

Comes with my own OneShot/TapHold implementations as I could't get the
following working with the original one:

* consistent behavior for Modifiers and layers
* allow "queueing" multiple oneshot operations
* consistent oneshot un/lock behavior
* avoid interfering with regular typing (TapHold)
* easy per-keymap customization (eg. suppress shift keys in my symbol
  layer and on numpad keys of nav layer)

Both use a common [myevent](/quantum/process_keycode/process_myevent.h) backend.

I'm trying to keep my keymaps "similar". For simplifying this, all of
them use the [shared definitions](/mykeys.h). The shared definitions
also include some explanations/requirements I used to build the layout.

Most notably, I'm trying to move all modifiers/layers to the thumbs.
Thumb keys are arranged to allow holding 2 of them at once.

The layout tries to eliminate keys where I'd move my wrists too much:
Even on the "bigger" keyboards (ergodox, ...) I use only few of the
extra keys.

My keymaps (have ASCII art in keymap.c):

* [ergodox](/keyboards/ergodox_ez/keymaps/rclasen/) - that's what I started
  with. Still the master for keymap changes. Still my daily driver... but
  has too many keys I don't use and my tenting stands make it quite
  unportable. Staggering is too low and the thumb cluster needs
  improvements. While you can get fitting keycaps, it's still quite
  limited.

* [diverge3](/keyboards/mydiverge/keymaps/default/) - ported the lets
  split firmware to unikeyboards diverge3. Needs extra pullup resistors to
  get i2c working - official diverg3 QMK uses serial. Initially staggering
  felt strange... likely caused by the outermost column. Thumb cluster
  feels good. Index finger column could be bit further down. Once I
  ignored the outermost column, it got closest to my ideal
  staggering/layout.

* [iris](/keyboards/iris/keymaps/rclasen/) - need to try.

* [orthodox](/keyboards/orthodox/keymaps/rclasen/) - need to try.

* [ergogravel](/keyboards/ergotravel/keymaps/rclasen/) - need to try.

* [lets split](/keyboards/lets_split/keymaps/rclasen/) - note that I start
  with the alphas on the outermost columns! I'm surprised how good I get
  along without column stagger. Though, my thumbs often loose their homing
  key -> needs significantly differnt caps for thumbs! On dox/diverge this
  is accomplished by the gap between bottom row and thumb cluster.

* [levinson](/keyboards/levinson/keymaps/rclasen/) - same as lets split,
  but with backlight.

* [atreus](/keyboards/myatreus/keymaps/default/) - handwired atreus. Great
  staggering, but thumb keys are too far up. I could use a bigger angle
  between the halves and the pinky column a bit futher down, but it's a
  good compromise to be portable (=transporting and setting up split
  boards somehow feels anoying). Could use 1 or to extra keys.

* [maltron](/keyboards/maltron/keymaps/default/) - handwired Maltron.
  Thumb cluster is hard to use when resting your palm -> made it
  impossible for me to use it for long enough to get used to the dwells.
  Angle between halvs is ok, but I do miss adjusting the angle when
  changing posture.

upcoming:
* chimera ergo 42
* if I can get hold of it: minidox
* maybe dactyl/manuform?
* custom split... using hybrid atreus/diverge layout
* custom "atreus" with bluetooth, bigger angle and moved thumb keys?
* custom bluetooth split (chimera? something using a blue micro?)
