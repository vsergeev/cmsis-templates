#include <stdint.h>

#include "LPC11Uxx.h"

volatile uint32_t msTicks = 0;

void SysTick_Handler(void) {
    msTicks++;
}

void delay_ms(uint32_t ms) {
    uint32_t now = msTicks;
    while ((msTicks-now) < ms);
}

int main(void) {
    SystemInit();
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/1000);

    LPC_GPIO->DIR[1] = (1 << 2) | (1 << 23) | (1 << 24);

    while (1) {
        LPC_GPIO->PIN[1] = (1 << 2);
        delay_ms(500);
        LPC_GPIO->PIN[1] = (1 << 23);
        delay_ms(500);
        LPC_GPIO->PIN[1] = (1 << 24);
        delay_ms(500);
        LPC_GPIO->PIN[1] = 0;
        delay_ms(500);
    }

    return 0;
}

