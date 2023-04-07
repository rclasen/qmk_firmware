#ifndef DIVERGE3_H
#define DIVERGE3_H

#include "quantum.h"

#include <stddef.h>
#ifdef __AVR__
#include <avr/io.h>
#include <avr/interrupt.h>
#endif

// arduino D17, portb, bit0, avr PB5, timer none
inline void diverge_local_led_rx_on(void)          { DDRB |=  (1<<0); PORTB &= ~(1<<0); }
inline void diverge_local_led_rx_off(void)         { DDRB &= ~(1<<0); PORTB |=  (1<<0); }

#if 0
// used by matrix.c to indicate i2c link:
// arduino D24, portd, bit5, avr PD5, timer none
inline void diverge_local_led_tx_on(void)          { DDRD |=  (1<<5); PORTD &= ~(1<<5); }
inline void diverge_local_led_tx_off(void)         { DDRD &= ~(1<<5); PORTD |=  (1<<5); }
#endif

// arduino D5, portc, bit6, avr PC6, pin 5, timer 3A
// conflicts with use as backlight
inline void diverge_local_led_back_on(void)        { DDRC |=  (1<<6); PORTC |=  (1<<6); }
inline void diverge_local_led_back_off(void)       { DDRC &= ~(1<<6); PORTC &= ~(1<<6); }
inline void diverge_local_led_back_set(uint8_t n)  { OCR3A = n; }

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
#define LAYOUT( \
	l00,\
	l10,l11,l12,l13,l14,l15,l16,\
	l20,l21,l22,l23,l24,l25,l26,\
	l30,l31,l32,l33,l34,l35,l36,\
	l40,l41,l42,l43,l44,l45,l46,\
	    l51,l52,l53,l54,  l55,l56,l57,\
    \
	                              r00,\
	      r16,r15,r14,r13,r12,r11,r10,\
	      r26,r25,r24,r23,r22,r21,r20,\
	      r36,r35,r34,r33,r32,r31,r30,\
	      r46,r45,r44,r43,r42,r41,r40,\
	r57,r56,r55,  r54,r53,r52,r51\
) { \
    {l00,  l10,  l20,  l30,  l40  }, \
    {l11,  l21,  l31,  l41,  l51  }, \
    {l12,  l22,  l32,  l42,  l52  }, \
    {l13,  l23,  l33,  l43,  l53  }, \
    {l14,  l24,  l34,  l44,  l54  }, \
    {l15,  l25,  l35,  l45,  l55  }, \
    {l16,  l26,  l36,  l46,  l56  }, \
    {KC_NO,KC_NO,KC_NO,KC_NO,l57  }, \
    {r00,  r10,  r20,  r30,  r40  }, \
    {r11,  r21,  r31,  r41,  r51  }, \
    {r12,  r22,  r32,  r42,  r52  }, \
    {r13,  r23,  r33,  r43,  r53  }, \
    {r14,  r24,  r34,  r44,  r54  }, \
    {r15,  r25,  r35,  r45,  r55  }, \
    {r16,  r26,  r36,  r46,  r56  }, \
    {KC_NO,KC_NO,KC_NO,KC_NO,r57  } \
}

#endif
