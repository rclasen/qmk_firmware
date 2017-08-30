#ifndef DIVERGE3_H
#define DIVERGE3_H

#include "quantum.h"

#include <stddef.h>
#ifdef __AVR__
#include <avr/io.h>
#include <avr/interrupt.h>
#endif

inline void diverge_local_led_back_on(void)    { DDRB |=  (1<<5); PORTB |=  (1<<5); }
inline void diverge_local_led_back_off(void)   { DDRB &= ~(1<<5); PORTB &= ~(1<<5); }
inline void diverge_local_led_back_set(uint8_t n)    { OCR1A = n; }

inline void diverge_remote_led_back_on(void)   { /* TODO */ }
inline void diverge_remote_led_back_off(void)  { /* TODO */ }
inline void diverge_remote_led_back_set(uint8_t n)   { /* TODO */ }

inline void diverge_led_back_on(void)
{
    diverge_local_led_back_on();
    diverge_remote_led_back_on();
}

inline void diverge_led_back_off(void)
{
    diverge_local_led_back_off();
    diverge_remote_led_back_off();
}

inline void diverge_led_back_set(uint8_t n)
{
    diverge_local_led_back_set( n );
    diverge_remote_led_back_set( n );
}

//Standard Keymap
#define KEYMAP( \
	l00,l01,l02,l03,l04,l05,l06,\
	l10,l11,l12,l13,l14,l15,l16,\
	l20,l21,l22,l23,l24,l25,l26,\
	l30,l31,l32,l33,l34,l35,l36,\
	l40,l41,l42,l43,l44,l45,l46,l47,\
    \
	    r06,r05,r04,r03,r02,r01,r00,\
	    r16,r15,r14,r13,r12,r11,r10,\
	    r26,r25,r24,r23,r22,r21,r20,\
	    r36,r35,r34,r33,r32,r31,r30,\
	r47,r46,r45,r44,r43,r42,r41,r40\
) { \
    {l00,  l10,  l20,  l30,  l40  }, \
    {l01,  l11,  l21,  l31,  l41  }, \
    {l02,  l12,  l22,  l32,  l42  }, \
    {l03,  l13,  l23,  l33,  l43  }, \
    {l04,  l14,  l24,  l34,  l44  }, \
    {l05,  l15,  l25,  l35,  l45  }, \
    {l06,  l16,  l26,  l36,  l46  }, \
    {KC_NO,KC_NO,KC_NO,KC_NO,l47  }, \
    {r00,  r10,  r20,  r30,  r40  }, \
    {r01,  r11,  r21,  r31,  r41  }, \
    {r02,  r12,  r22,  r32,  r42  }, \
    {r03,  r13,  r23,  r33,  r43  }, \
    {r04,  r14,  r24,  r34,  r44  }, \
    {r05,  r15,  r25,  r35,  r45  }, \
    {r06,  r16,  r26,  r36,  r46  }, \
    {KC_NO,KC_NO,KC_NO,KC_NO,r47  } \
}

#endif
