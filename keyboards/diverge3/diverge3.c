#include "config.h"
#include "diverge3.h"

void matrix_init_kb(void) {
    // JTAG disable for PORT F. write JTD bit twice within four
    // cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

    // TODO: init timer for led PWM

    matrix_init_user();
}

