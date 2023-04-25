#include "gpio.h"
#include "ppi.h"
#include "gpiote.h"


int main(void) {
    init_gpiote();
    init_PPI();

    while (1);

    return 0;
}