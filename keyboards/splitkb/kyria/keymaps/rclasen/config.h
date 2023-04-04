#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include <myconfig.h>

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
//#define RGBLIGHT_ANIMATIONS
#endif

// #define USE_I2C

// #define MASTER_LEFT
// #define _MASTER_RIGHT
#define EE_HANDS

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

#endif
