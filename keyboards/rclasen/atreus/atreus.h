#ifndef MYATREUS_H
#define MYATREUS_H

#include "quantum.h"
#include "matrix.h"
#include <stddef.h>

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
  k00, k01, k02, k03, k04, \
  k10, k11, k12, k13, k14, \
  k20, k21, k22, k23, k24,  \
  k30, k31, k32, k33, k34, k25, \
  \
       k06, k07, k08, k09, k0a, \
       k16, k17, k18, k19, k1a, \
       k26, k27, k28, k29, k2a, \
  k35, k36, k37, k38, k39, k3a \
) \
{ \
	{ k00, k01, k02, k03, k04, KC_NO, k06, k07, k08, k09, k0a }, \
	{ k10, k11, k12, k13, k14, KC_NO, k16, k17, k18, k19, k1a }, \
	{ k20, k21, k22, k23, k24,  k25,  k26, k27, k28, k29, k2a }, \
	{ k30, k31, k32, k33, k34,  k35,  k36, k37, k38, k39, k3a } \
}

#endif
