#ifndef MYMALTRON_H
#define MYMALTRON_H

#include "quantum.h"
#include "matrix.h"
#include <stddef.h>

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
  /* left well: */ \
  k00, k01, k02, k03, k04, k05, \
  k10, k11, k12, k13, k14, k15, \
  k20, k21, k22, k23, k24, k25, \
  k30, k31, k32, k33, k34, k35, \
  k40, k41, k42, k43, k44, k45, \
       k51, k52, k53, k54, \
  \
  /* left thumb cluster:  */ \
                 k46, k47, k48, \
                 k56, k57, k58, \
                           k59, \
  \
  /* center: */ \
  k06, k07, k08, k09, k0a, k0b, k0c, \
  k16, k17, k18, k19, k1a, k1b, k1c, \
  k26, k27, k28, k29, k2a, k2b, k2c, \
  k36, k37, k38, k39, k3a, k3b, k3c, \
  \
  /* right well: */ \
  k0d, k0e, k0f, k0g, k0h, k0i, \
  k1d, k1e, k1f, k1g, k1h, k1i, \
  k2d, k2e, k2f, k2g, k2h, k2i, \
  k3d, k3e, k3f, k3g, k3h, k3i, \
  k4d, k4e, k4f, k4g, k4h, k4i, \
       k5e, k5f, k5g, k5h, \
  \
  /* right thumb cluster: */ \
  k4a, k4b, k4c, \
  k5a, k5b, k5c, \
  k49 )\
{ \
	{   k00, k01, k02, k03, k04, k05,   k06, k07, k08, k09, k0a, k0b, k0c,   k0d, k0e, k0f, k0g, k0h, k0i   }, \
	{   k10, k11, k12, k13, k14, k15,   k16, k17, k18, k19, k1a, k1b, k1c,   k1d, k1e, k1f, k1g, k1h, k1i   }, \
	{   k20, k21, k22, k23, k24, k25,   k26, k27, k28, k29, k2a, k2b, k2c,   k2d, k2e, k2f, k2g, k2h, k2i   }, \
	{   k30, k31, k32, k33, k34, k35,   k36, k37, k38, k39, k3a, k3b, k3c,   k3d, k3e, k3f, k3g, k3h, k3i   }, \
	{   k40, k41, k42, k43, k44, k45,   k46, k47, k48, k49, k4a, k4b, k4c,   k4d, k4e, k4f, k4g, k4h, k4i   }, \
	{ KC_NO, k51, k52, k53, k54, KC_NO, k56, k57, k58, k59, k5a, k5b, k5c, KC_NO, k5e, k5f, k5g, k5h, KC_NO }, \
}

#endif
