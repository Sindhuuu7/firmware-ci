#ifndef LED_H
#define LED_H
#include <stdint.h>
#define LED_MASK (1U << 13)
#ifdef __arm__
#define LED_REG (*(volatile uint32_t *)0x4001100CU)
#else
extern volatile uint32_t led_reg_sim;
#define LED_REG led_reg_sim
#endif
void led_init(void);
void led_set(int on);
void led_toggle(void);
#endif
