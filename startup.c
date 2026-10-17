#include <stdint.h>

extern int main(void);

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void Reset_Handler(void);
void Default_Handler(void);
void TIM2_IRQHandler(void);

__attribute__((section(".isr_vector"), used))
const uintptr_t vectors[] = {
    (uintptr_t)&_estack,
    (uintptr_t)Reset_Handler,

    (uintptr_t)Default_Handler, // NMI
    (uintptr_t)Default_Handler, // HardFault
    (uintptr_t)Default_Handler, // MemManage
    (uintptr_t)Default_Handler, // BusFault
    (uintptr_t)Default_Handler, // UsageFault

    0, 0, 0, 0,

    (uintptr_t)Default_Handler, // SVCall
    (uintptr_t)Default_Handler, // Debug monitor
    0,
    (uintptr_t)Default_Handler, // PendSV
    (uintptr_t)Default_Handler, // SysTick

    // External interrupts: IRQ 0 through IRQ 27
    (uintptr_t)Default_Handler, // IRQ 0: WWDG
    (uintptr_t)Default_Handler, // IRQ 1: PVD
    (uintptr_t)Default_Handler, // IRQ 2: TAMPER
    (uintptr_t)Default_Handler, // IRQ 3: RTC
    (uintptr_t)Default_Handler, // IRQ 4: FLASH
    (uintptr_t)Default_Handler, // IRQ 5: RCC
    (uintptr_t)Default_Handler, // IRQ 6: EXTI0
    (uintptr_t)Default_Handler, // IRQ 7: EXTI1
    (uintptr_t)Default_Handler, // IRQ 8: EXTI2
    (uintptr_t)Default_Handler, // IRQ 9: EXTI3
    (uintptr_t)Default_Handler, // IRQ 10: EXTI4
    (uintptr_t)Default_Handler, // IRQ 11: DMA1 Channel 1
    (uintptr_t)Default_Handler, // IRQ 12: DMA1 Channel 2
    (uintptr_t)Default_Handler, // IRQ 13: DMA1 Channel 3
    (uintptr_t)Default_Handler, // IRQ 14: DMA1 Channel 4
    (uintptr_t)Default_Handler, // IRQ 15: DMA1 Channel 5
    (uintptr_t)Default_Handler, // IRQ 16: DMA1 Channel 6
    (uintptr_t)Default_Handler, // IRQ 17: DMA1 Channel 7
    (uintptr_t)Default_Handler, // IRQ 18: ADC1_2
    (uintptr_t)Default_Handler, // IRQ 19: USB HP / CAN TX
    (uintptr_t)Default_Handler, // IRQ 20: USB LP / CAN RX0
    (uintptr_t)Default_Handler, // IRQ 21: CAN RX1
    (uintptr_t)Default_Handler, // IRQ 22: CAN SCE
    (uintptr_t)Default_Handler, // IRQ 23: EXTI9_5
    (uintptr_t)Default_Handler, // IRQ 24: TIM1 break
    (uintptr_t)Default_Handler, // IRQ 25: TIM1 update
    (uintptr_t)Default_Handler, // IRQ 26: TIM1 trigger/commutation
    (uintptr_t)Default_Handler, // IRQ 27: TIM1 capture/compare

    (uintptr_t)TIM2_IRQHandler  // IRQ 28: TIM2
};

void Reset_Handler(void)
{
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;

    /* Copy initialized data from Flash to RAM */
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    /* Clear zero-initialized data in RAM */
    for (dst = &_sbss; dst < &_ebss;) {
        *dst++ = 0;
    }

    main();

    /* main() should not return */
    while (1) {
    }
}

void Default_Handler(void)
{
    while (1) {
    }
}
