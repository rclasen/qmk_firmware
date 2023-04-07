# diverge3

TODO: no support for backlight on slave, yet.

There are 2 ways to get QMK running on a diverge:

## highspeed with hardware modification

On one half pins 2 and 3 (i2c: SDA, SCL) each need to be connected to
RAW pin with a 4k7 Ohm resistor. This adds external pull-up resistors
required for the higher i2c bus speed this code uses by default.

## enable internal pull-ups and reduce bus speed

in i2c.c `i2c_master_init()` add:

```
     PORTD |=  (1<<2) | (1<<3); // D2 - SDA, D3 - SCL
     PORTD |=  (1<<0) | (1<<1); // D2 - SDA - bit0 , D3 - SCL - bit1
```

in i2c.h lower the speed until the TXLED of the master no longer
indicates i2c errors:

```
    #define SCL_CLOCK  50000L
```

