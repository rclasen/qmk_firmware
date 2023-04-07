#include "config.h"
#include "dactyform.h"

void matrix_init_kb(void) {
    // JTAG disable for PORT F. write JTD bit twice within four
    // cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

    matrix_init_user();
}

