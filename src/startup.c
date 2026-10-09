#include <stdint.h>

extern void _estack(void);
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
int main(void);

void Reset_Handler(void);
void Default_Handler(void);

__attribute__((section(".isr_vector"), used))
void (*const vector_table[])(void) = {
    _estack,
    Reset_Handler,
    Default_Handler,
    Default_Handler
};

void Reset_Handler(void)
{
    const uint32_t *src = &_sidata;
    uint32_t *dst;
    /* cppcheck-suppress comparePointers */
    for (dst = &_sdata; dst < &_edata; dst++) { *dst = *src++; }
    /* cppcheck-suppress comparePointers */
    for (dst = &_sbss; dst < &_ebss; dst++) { *dst = 0U; }
    (void)main();
    for (;;) { }
}

void Default_Handler(void)
{
    for (;;) { }
}
