#include <stdint.h>

#define RCC_APB2ENR ( *(volatile uint32_t *)0x40021018U)
#define RCC_APB1ENR ( *(volatile uint32_t *)0x4002101CU)
// Defined the rcc (clock thingy) 
#define GPIOC_CRH (*(volatile uint32_t *)0x40011004U)
#define GPIOC_BSRR (*(volatile uint32_t *)0x40011010U)

//GPIOC registers initialized 

#define TIM2_CR1 (*(volatile uint32_t *)0x40000000U) // starting stopping the timer
#define TIM2_SR  (*(volatile uint32_t *)0x40000010U) //time events report, UIF is bit 0 Update flag
#define TIM2_EGR (*(volatile uint32_t *)0x40000014U) //trigger an event manually
#define TIM2_CNT (*(volatile uint32_t *)0x40000024U) //current count of timer
#define TIM2_PSC (*(volatile uint32_t *)0x40000028U) //prescalar
#define TIM2_ARR (*(volatile uint32_t *)0x4000002CU) //counter's maximum
#define TIM2_DIER (*(volatile uint32_t *)0x4000000CU) //for Interrupt, DMA Interrupt ENable register
// defining the timer registers , TIM2 

#define NVIC_ISER0 (*(volatile uint32_t *)0xE000E100U) //CPU Interrupt Controller

volatile uint32_t ms_count = 0; //how many counter interrupts have occured 
uint8_t led_on = 0; //led state on or off
static void timer_init(void)
{
	RCC_APB1ENR |= (1U << 0); //enabling the TIM2 clock
	TIM2_CR1 = 0; // stopping the timer while  configuring it

	TIM2_PSC = 7; //setting the prescalar to 7 which is 7+1 = 8, 8MHz / 8 = 1Mhz
	TIM2_ARR = 999; //maximum 999, 0 to 999 = 1000, till  999 requires 1 milli second

	TIM2_EGR = 1U; //manually updating to load the prescalar

	TIM2_SR = 0; //resetting the UIF bit
	TIM2_CNT = 0; //resetting the counter to 0

	NVIC_ISER0 = (1U << 28); //enable IRQ 28

	TIM2_DIER |= 1U;
	TIM2_CR1 = 1U; //enabling the counter to start functioning


}
static void timer_wait_1ms(void) //No need for this function anymore
{
	while((TIM2_SR & 1U) == 0U) //wait for  UIF to go 1, it goes 1 every 1ms
	{
	}
	TIM2_SR = 0; // resetting it
}
void TIM2_IRQHandler(void)
{
	TIM2_SR  = 0;
	ms_count++;
	if(ms_count >= 500U)
	{
		ms_count = 0;
		if(led_on)
		{
			GPIOC_BSRR = (1U << 13);
			led_on = 0;
		}
		else
		{
			GPIOC_BSRR = (1U << 29);
			led_on = 1;
		}
	}
}
int main(void)
{

	RCC_APB2ENR |= (1U << 4); /* This enables the clock for GPIOC ports */
	GPIOC_CRH &= ~(0xFU << 20); /* i reset the bits to 0*/
	GPIOC_CRH |= (0X2U << 20); /* set the CNF and MOde, 2MHZ output and push pull output */
	GPIOC_BSRR = (1U << 13);
	timer_init();
	__asm volatile ("cpsie i");
	while(1)
	{
	}
}
