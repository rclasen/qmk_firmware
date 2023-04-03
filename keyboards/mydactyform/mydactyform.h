#pragma once

#include "quantum.h"

#include <stddef.h>
#ifdef __AVR__
#include <avr/io.h>
#include <avr/interrupt.h>
#endif

//Standard Keymap
#define LAYOUT( \
	l00,l01,l02,l03,l04,l05,\
	l10,l11,l12,l13,l14,l15,\
	l20,l21,l22,l23,l24,l25,\
	        l32,l33,\
	                l44,l45,l46,l47,\
	                        l56,l57,\
    \
	        r05,r04,r03,r02,r01,r00,\
	        r15,r14,r13,r12,r11,r10,\
	        r25,r24,r23,r22,r21,r20,\
	                r33,r32,\
	r47,r46,r45,r44,\
	r57,r56\
) { \
    {l00,  l01,  l02,  l03,  l04,  l05}, \
    {l10,  l11,  l12,  l13,  l14,  l15}, \
    {l20,  l21,  l22,  l23,  l24,  l25}, \
    {KC_NO,KC_NO,l32,  l33,  l44,  l45}, \
    {KC_NO,KC_NO,l46,  l47,  l56,  l57}, \
    {r00,  r01,  r02,  r03,  r04,  r05}, \
    {r10,  r11,  r12,  r13,  r14,  r15}, \
    {r20,  r21,  r22,  r23,  r24,  r25}, \
    {KC_NO,KC_NO,r32,  r33,  r44,  r45}, \
    {KC_NO,KC_NO,r46,  r47,  r56,  r57}, \
}

