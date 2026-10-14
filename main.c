#include <stdint.h>

#define RCC_APB2ENR ( *(volatile uint32_t *)0x40021018U)
/* Defined the rcc (clock thingy) */
#define GPIOC_CRH (*(volatile uint32_t *)0x40011004U)
#define GPIOC_BSRR (*(volatile uint32_t *)0x40011010U)

/*GPIOC registers initialized */

static void delay(volatile uint32_t count)
{
	while( count--)
	{
		/*thisis for delay*/
	}
}
int main(void)
{
	RCC_APB2ENR |= (1U << 4); /* This enables the clock for GPIOC ports */
	GPIOC_CRH &= ~(0xFU << 20); /* i reset the bits to 0*/
	GPIOC_CRH |= (0X2U << 20); /* set the CNF and MOde, 2MHZ output and push pull output */
	while(1)
	{
		GPIOC_BSRR = (1U << 29); /* putting the port 13 at low  29 - 16 = 13 basically resetting it to 0 since it is active low */
		delay(500000U);
		GPIOC_BSRR = (1U << 13); /* now  setting it to 1 to turn off the led */
		delay(500000U);
	}
}
