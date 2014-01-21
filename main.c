#include <stdint.h>

#include "LPC8xx.h"

volatile uint32_t msTicks = 0;

void SysTick_Handler(void) {
    msTicks++;
}

void delay_ms(uint32_t ms) {
    uint32_t now = msTicks;
    while ((msTicks-now) < ms)
        ;
}

int main(void) {
    SystemInit();
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/1000);

    /* Setup GPIO here */

    while (1) {
        /* GPIO on here */
        delay_ms(500);
        /* GPIO off here */
        delay_ms(500);
    }

    return 0;
}

