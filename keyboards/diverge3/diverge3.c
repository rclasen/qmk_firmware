#include "config.h"
#include "diverge3.h"
#include "print.h"

void matrix_init_kb(void) {
    // JTAG disable for PORT F. write JTD bit twice within four
    // cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

    print("mik\n");

    matrix_init_user();
}

