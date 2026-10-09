#include "led.h"

#ifndef __arm__
volatile uint32_t led_reg_sim;
#endif

void led_init(void)
{
    LED_REG = 0U;
}

void led_set(int on)
{
    if (on != 0) {
        LED_REG |= LED_MASK;
    } else {
        LED_REG &= ~LED_MASK;
    }
}

void led_toggle(void)
{
    LED_REG ^= LED_MASK;
}
