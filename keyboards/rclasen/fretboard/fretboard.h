#ifndef MYATREUS_H
#define MYATREUS_H

#include "quantum.h"
#include "matrix.h"
#include <stddef.h>

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
  l00, l01, l02, l03, l04, l05, \
  l10, l11, l12, l13, l14, l15,       l17, \
       l21, l22, l23, l24, l25, l26, \
                      l34, l35, l36, \
  \
       r01, r02, r03, r04, r05, r06, \
       r11, r12, r13, r14, r15, r16, \
  r20, r21, r22, r23, r24, r25,  \
  r30, r31, r32 \
) \
{ \
	{ l00,   l01,   l02,   l03,   l04,   l05,   KC_NO, r01,   r02,   r03,   r04,   r05,   r06   }, \
	{ l10,   l11,   l12,   l13,   l14,   l15,   KC_NO, r11,   r12,   r13,   r14,   r15,   r16   }, \
	{ KC_NO, l21,   l22,   l23,   l24,   l25,   l17,   r21,   r22,   r23,   r24,   r25,   KC_NO }, \
	{ KC_NO, KC_NO, l34,   l35,   l36,   l26,   KC_NO, r20,   r30,   r31,   r32,   KC_NO, KC_NO } \
}

#endif
