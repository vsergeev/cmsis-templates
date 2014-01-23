#include <stdint.h>

/* Addresses pulled in from the linker script */
extern uint32_t _end_stack;
extern uint32_t _start_data_flash;
extern uint32_t _start_data;
extern uint32_t _end_data;
extern uint32_t _start_bss;
extern uint32_t _end_bss;

/* Application main() called in reset handler */
extern int main(void);

#define WEAK_ALIAS(x) __attribute__ ((weak, alias(#x)))

/* Cortex M3 core interrupt handlers */
void Reset_Handler(void);
void NMI_Handler(void) WEAK_ALIAS(Dummy_Handler);
void HardFault_Handler(void) WEAK_ALIAS(Dummy_Handler);
void MemManage_Handler(void) WEAK_ALIAS(Dummy_Handler);
void BusFault_Handler(void) WEAK_ALIAS(Dummy_Handler);
void UsageFault_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SVC_Handler(void) WEAK_ALIAS(Dummy_Handler);
void DebugMon_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PendSV_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SysTick_Handler(void) WEAK_ALIAS(Dummy_Handler);

/* LPC17xx specific interrupt handlers */
void WDT_Handler(void) WEAK_ALIAS(Dummy_Handler);
void TIMER0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void TIMER1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void TIMER2_Handler(void) WEAK_ALIAS(Dummy_Handler);
void TIMER3_Handler(void) WEAK_ALIAS(Dummy_Handler);
void UART0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void UART1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void UART2_Handler(void) WEAK_ALIAS(Dummy_Handler);
void UART3_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PWM1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void I2C0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void I2C1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void I2C2_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SPI_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SSP0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SSP1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PLL0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void RTC_Handler(void) WEAK_ALIAS(Dummy_Handler);
void EINT0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void EINT1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void EINT2_Handler(void) WEAK_ALIAS(Dummy_Handler);
void EINT3_Handler(void) WEAK_ALIAS(Dummy_Handler);
void ADC_Handler(void) WEAK_ALIAS(Dummy_Handler);
void BOD_Handler(void) WEAK_ALIAS(Dummy_Handler);
void USB_Handler(void) WEAK_ALIAS(Dummy_Handler);
void CAN_Handler(void) WEAK_ALIAS(Dummy_Handler);
void DMA_Handler(void) WEAK_ALIAS(Dummy_Handler);
void I2S_Handler(void) WEAK_ALIAS(Dummy_Handler);
void ENET_Handler(void) WEAK_ALIAS(Dummy_Handler);
void RIT_Handler(void) WEAK_ALIAS(Dummy_Handler);
void MCPWM_Handler(void) WEAK_ALIAS(Dummy_Handler);
void QEI_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PLL1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void USBActivity_Handler(void) WEAK_ALIAS(Dummy_Handler);
void CANActivity_Handler(void) WEAK_ALIAS(Dummy_Handler);

void Dummy_Handler(void);

/* Stack top and vector handler table */
void *vector_table[] __attribute__ ((section(".vectors"))) = {
    &_end_stack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,

    /* LPC17xx specific interrupt vectors */
    WDT_Handler,
    TIMER0_Handler,
    TIMER1_Handler,
    TIMER2_Handler,
    TIMER3_Handler,
    UART0_Handler,
    UART1_Handler,
    UART2_Handler,
    UART3_Handler,
    PWM1_Handler,
    I2C0_Handler,
    I2C1_Handler,
    I2C2_Handler,
    SPI_Handler,
    SSP0_Handler,
    SSP1_Handler,
    PLL0_Handler,
    RTC_Handler,
    EINT0_Handler,
    EINT1_Handler,
    EINT2_Handler,
    EINT3_Handler,
    ADC_Handler,
    BOD_Handler,
    USB_Handler,
    CAN_Handler,
    DMA_Handler,
    I2S_Handler,
    ENET_Handler,
    RIT_Handler,
    MCPWM_Handler,
    QEI_Handler,
    PLL1_Handler,
    USBActivity_Handler,
    CANActivity_Handler,
};

void Reset_Handler(void) {
    uint8_t *src, *dst;

    /* Copy with byte pointers to obviate unaligned access problems */

    /* Copy data section from Flash to RAM */
    src = (uint8_t *)&_start_data_flash;
    dst = (uint8_t *)&_start_data;
    while (dst < (uint8_t *)&_end_data)
        *dst++ = *src++;

    /* Clear the bss section */
    dst = (uint8_t *)&_start_bss;
    while (dst < (uint8_t *)&_end_bss)
        *dst++ = 0;

    main();
}

void Dummy_Handler(void) {
    while (1)
        ;
}

