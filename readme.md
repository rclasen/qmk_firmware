# Local hacks/keymaps for Quantum Mechanical Keyboard Firmware

based on an old version of [QMK](https://github.com/qmk/qmk_firmware).

Comes with my own OneShot implementation as I could't get the following
working with the original one:

* consistent behavior for Modifiers and layers
* allow "queueing" multiple oneshot operations
* consistent un/lock behavior

I'm trying to keep my keymaps "similar". For simplifying this, all of
them use the [shared definitions](/mykeys.h). The shared definitions
also include somem explanations/requirements I used to build the layout.

Most notably, I'm trying to move all modifiers/layers to the thumbs.
Thumb keys are arranged to allow holding 2 of them at once.

The layout tries to eliminate keys where I'd move my wrists too much:
Even on the "bigger" keyboards (ergodox, ...) I use only few of the
extra keys.

My keymaps (have ASCII art in keymap.c):
* [ergodox](/keyboards/ergodox/keymaps/mydox80/) - that's what I started with. Still the master for keymap changes. Still my daily driver... but has too many keys I don't use and my tenting stands make it quite unportable. Staggering is too low and the thumb cluster needs improvements.
* [diverge3](/keyboards/diverge3/keymaps/default/) - ported the lets split firmware to unikeyboards diverge3. Needs extra pullups to work. Staggering feels strange... especially for pinke. Thumb cluster feels good.
* [lets split](/keyboards/lets_split/keymaps/mysplit/) - note that I start with the alphas on the outermost columns! I'm surprised how good I get along without column stagger.
* [atreus](/keyboards/myatreus/keymaps/default/) - handwired atreus. Great staggering, but thumb keys are too far up. I could use a bigger angle between the halves, but it's a good compromise to be portable (=transporting and setting up split boards somehow feels anoying).

upcoming:
* levinson
* iris
* orthodox
* maltron - diy handwired with teensy2++
* if I can get hold of it: minidox
* maybe dactyl/manuform?
* custom split... using atreus staggering and a diverge-like thumb cluster?
* custom "atreus" with bluetooth, bigger angle and moved thumb keys?
