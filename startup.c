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
    (uintptr_t)Default_Handler  // SysTick
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
