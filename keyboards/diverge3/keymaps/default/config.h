#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define USE_I2C

#define MASTER_LEFT
// #define _MASTER_RIGHT
// #define EE_HANDS


#define PREVENT_STUCK_MODIFIERS

#define TAPPING_TOGGLE  1

#define TAPPING_TERM    200
#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 2000


//#undef LEADER_TIMEOUT
//#define LEADER_TIMEOUT 300

#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 40

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 3

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0

#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 0

#endif
