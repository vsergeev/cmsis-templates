#include <stdint.h>

/* Addresses pulled in from the linker script */
extern uint32_t _end_stack;
extern uint32_t _end_text;
extern uint32_t _start_data;
extern uint32_t _end_data;
extern uint32_t _start_bss;
extern uint32_t _end_bss;

/* Application main() called in reset handler */
extern int main(void);

#define WEAK_ALIAS(x) __attribute__ ((weak, alias(#x)))

/* Cortex M0 core interrupt handlers */
void Reset_Handler(void);
void NMI_Handler(void) WEAK_ALIAS(Dummy_Handler);
void HardFault_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SVC_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PendSV_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SysTick_Handler(void) WEAK_ALIAS(Dummy_Handler);

/* LPC8xx specific interrupt handlers */
void SPI0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SPI1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void Reserved0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void UART0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void UART1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void UART2_Handler(void) WEAK_ALIAS(Dummy_Handler);
void Reserved1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void Reserved2_Handler(void) WEAK_ALIAS(Dummy_Handler);
void I2C_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SCT_Handler(void) WEAK_ALIAS(Dummy_Handler);
void MRT_Handler(void) WEAK_ALIAS(Dummy_Handler);
void CMP_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WDT_Handler(void) WEAK_ALIAS(Dummy_Handler);
void BOD_Handler(void) WEAK_ALIAS(Dummy_Handler);
void Reserved3_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WKT_Handler(void) WEAK_ALIAS(Dummy_Handler);
void Reserved4_Handler(void) WEAK_ALIAS(Dummy_Handler);
void Reserved5_Handler(void) WEAK_ALIAS(Dummy_Handler);
void Reserved6_Handler(void) WEAK_ALIAS(Dummy_Handler);
void Reserved7_Handler(void) WEAK_ALIAS(Dummy_Handler);
void Reserved8_Handler(void) WEAK_ALIAS(Dummy_Handler);
void Reserved9_Handler(void) WEAK_ALIAS(Dummy_Handler);
void Reserved10_Handler(void) WEAK_ALIAS(Dummy_Handler);
void Reserved11_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PININT0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PININT1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PININT2_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PININT3_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PININT4_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PININT5_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PININT6_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PININT7_Handler(void) WEAK_ALIAS(Dummy_Handler);

void Dummy_Handler(void);

/* Stack top and vector handler table */
void *vector_table[] __attribute__ ((section(".vectors"))) = {
    &_end_stack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    SVC_Handler,
    0,
    0,
    PendSV_Handler,
    SysTick_Handler,

    /* LPC11xx specific interrupt vectors */
    SPI0_Handler,
    SPI1_Handler,
    Dummy_Handler,      /* Reserved */
    UART0_Handler,
    UART1_Handler,
    UART2_Handler,
    Dummy_Handler,      /* Reserved */
    Dummy_Handler,      /* Reserved */
    I2C_Handler,
    SCT_Handler,
    MRT_Handler,
    CMP_Handler,
    WDT_Handler,
    BOD_Handler,
    Dummy_Handler,      /* Reserved */
    WKT_Handler,
    Dummy_Handler,      /* Reserved */
    Dummy_Handler,      /* Reserved */
    Dummy_Handler,      /* Reserved */
    Dummy_Handler,      /* Reserved */
    Dummy_Handler,      /* Reserved */
    Dummy_Handler,      /* Reserved */
    Dummy_Handler,      /* Reserved */
    Dummy_Handler,      /* Reserved */
    PININT0_Handler,
    PININT1_Handler,
    PININT2_Handler,
    PININT3_Handler,
    PININT4_Handler,
    PININT5_Handler,
    PININT6_Handler,
    PININT7_Handler,
};

void Reset_Handler(void) {
    uint8_t *src, *dst;

    /* Copy with byte pointers to obviate unaligned access problems */

    /* Copy data section from Flash to RAM */
    src = (uint8_t *)&_end_text;
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

