#include "config.h"
#include "diverge3.h"

void matrix_init_kb(void) {
    // JTAG disable for PORT F. write JTD bit twice within four
    // cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

    // TODO: init timer for back led PWM
    TCCR3A |= 1 << WGM00 | 1 << WGM01 | 1 << COM3A1;
    TCCR3B |= 1 << CS00;

    matrix_init_user();
}

