#include <stdint.h>

extern unsigned int _end_stack;
extern unsigned int _end_text;
extern unsigned int _start_data;
extern unsigned int _end_data;
extern unsigned int _start_bss;
extern unsigned int _end_bss;

extern int main(void);
extern void SystemInit(void);

/* Cortex M3 core interrupt handlers */
void Reset_Handler(void);
void NMI_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void HardFault_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void MemManage_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void BusFault_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void UsageFault_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void SVC_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void DebugMon_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void PendSV_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void SysTick_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
/* LPC13xx specific interrupt handlers */
void WAKEUP_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void I2C_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void TIMER_16_0_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void TIMER_16_1_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void TIMER_32_0_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void TIMER_32_1_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void SSP_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void UART_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void USB_IRQ_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void USB_FIQ_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void ADC_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void WDT_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void BOD_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void EINT3_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void EINT2_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void EINT1_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void EINT0_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));

void Dummy_Handler(void);

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

	/* LPC13xx specific interrupt vectors */
	WAKEUP_Handler, WAKEUP_Handler, WAKEUP_Handler,	WAKEUP_Handler,
	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,
	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,
	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,
	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,
	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,
	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,
	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,
	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,
	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,	WAKEUP_Handler,
	I2C_Handler,
	TIMER_16_0_Handler,
	TIMER_16_1_Handler,
	TIMER_32_0_Handler,
	TIMER_32_1_Handler,
	SSP_Handler,
	UART_Handler,
	USB_IRQ_Handler,
	USB_FIQ_Handler,
	ADC_Handler,
	WDT_Handler,
	BOD_Handler,
	EINT3_Handler,
	EINT2_Handler,
	EINT1_Handler,
	EINT0_Handler,
};

void Reset_Handler(void) {
	unsigned int *src, *dst;
	
	/* Copy data section from flash to RAM */
	src = &_end_text;
	dst = &_start_data;
	while (dst < &_end_data)
		*dst++ = *src++;

	/* Clear the bss section */
	dst = &_start_bss;
	while (dst < &_end_bss)
		*dst++ = 0;

	SystemInit();
	main();
}	

void Dummy_Handler(void) {
	while (1)
		;
}

