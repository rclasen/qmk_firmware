/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#define USE_I2C

// default:
// #define MASTER_LEFT
// else
#define MASTER_RIGHT
// #define EE_HANDS

#ifdef SUBPROJECT_rev1
    #include "../../rev1/config.h"
#endif
#ifdef SUBPROJECT_rev2
    #include "../../rev2/config.h"
#endif
#ifdef SUBPROJECT_rev2fliphalf
	#include "../../rev2fliphalf/config.h"
#endif

#define TAPPING_TERM 200

#define PREVENT_STUCK_MODIFIERS

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


