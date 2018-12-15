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
extra keys. I'm using the ergodox keymap as "master".

My keymaps (have ASCII art in keymap.c):

* [atreus](/keyboards/myatreus/keymaps/default/) - handwired atreus. Great
  staggering, but thumb keys are way too far up. I could use a bigger angle
  between the halves and the pinky column a bit futher down, but it's a
  good compromise to be portable (=transporting and setting up split
  boards somehow feels anoying). Could use 1 or two extra keys.

* [chimera ergo 42](/keyboards/chimera_ergo_42/keymaps/rclasen/) - I love
  it. Thumb keys are where I need them, staggering is great. Has few keys
  I don't use. Clearly my favourite layout. I'm missing power switches to
  keep it from draining batterie when transporting it...  and the receiver
  could use some enclosure. Actually, I'm now looking for a wired
  alternative to make this a daily driver.

* [dactyl manuform](/keyboards/mydactyform/keymaps/default/) - need to try.

* [diverge3](/keyboards/mydiverge/keymaps/default/) - ported the lets
  split firmware to unikeyboards diverge3. Needs extra pullup resistors to
  get i2c working - official QMK diverge3 uses serial. Initially
  staggering felt strange... likely caused by the outermost column. Thumb
  cluster feels good. Index finger column could be a bit further down.
  Once I started to see the single key that sticks out to the top as
  separate row, I started to love the staggering. Unfortunately it's with
  Gateron browns - and I can't stand typing on them. Plate doesn't support
  top-removal... and I'm too lazy to desolder.

* [ergodox](/keyboards/ergodox_ez/keymaps/rclasen/) - that's what I
  started with and it's still my daily driver... but has too many keys I
  don't use and my tenting stands make it quite unportable. Even without
  stands it's quite huge. Staggering is too low and the thumb cluster
  needs improvements. While you can get fitting keycaps, it's still quite
  limited. It's the master for my keymaps.

* [ergotravel](/keyboards/ergotravel/keymaps/rclasen/) - why on earth is
  the innermost thumb key tilted? It's useless and sacrifies another good
  thumb key below B. Staggering is like ergodox: Too conservative.

* [iris](/keyboards/iris/keymaps/rclasen/) - built it with 2x1u thumb key
  ... but I don't like the upper position. Unfortunately the thumb key
  below c and v is a tiny bit too far under my palm for frequent use. It's
  nice to have the thumb keys shifted by .5u ... but I'd prefer to have
  them shifted the other direction. Staggering is like ergodox: Too
  conservative.

* [lets split](/keyboards/lets_split/keymaps/rclasen/) - note that I start
  with the alphas on the outermost columns! While I'm heavily into
  columnar stagger I'm surprised how good I get along with a plain ortho
  layout. Though, my thumbs often loose their homing key -> needs
  significantly differnt caps for thumbs! On dox/diverge this is
  accomplished by the gap between bottom row and thumb cluster.

* [levinson](/keyboards/levinson/keymaps/rclasen/) - same as lets split,
  but with backlight.

* [maltron](/keyboards/maltron/keymaps/default/) - handwired Maltron.
  Thumb cluster is hard to use when resting your palm -> made it
  impossible for me to use it for long enough to get used to the dwells.
  Angle between halvs is ok, but I do miss adjusting the angle when
  changing posture.

* [orthodox](/keyboards/orthodox/keymaps/rclasen/) - Got it to test the
  Thumb cluster. Upper thumb row is useless and moves the other thumb keys
  too far down. Bottom thumb keys could move closer to M.

upcoming:
* if I can get hold of it: minidox, helidox. Both have similar issues
  as the iris, but both are more compact.
* wired chimera ergo 42
* custom "atreus" with bluetooth, bigger angle and moved thumb keys?
* custom bluetooth split (chimera? something using a blue micro?)
