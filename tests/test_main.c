#include <stdio.h>
#include "led.h"
#include "sensor.h"

static int passed = 0;
static int failed = 0;

static void check(int cond, const char *name)
{
    if (cond) {
        printf("[PASS] %s\n", name);
        passed++;
    } else {
        printf("[FAIL] %s\n", name);
        failed++;
    }
}

int main(void)
{
    printf("Running unit tests...\n");
    check(sensor_adc_to_celsius(0) == 0, "adc 0 -> 0 C");
    check(sensor_adc_to_celsius(4095) == 330, "adc 4095 -> 330 C");
    check(sensor_adc_to_celsius(310) == 24, "adc 310 -> 24 C");
    check(sensor_adc_to_celsius(5000) == 330, "adc overflow clamps");
    check(sensor_is_overheat(74) == 0, "74 C is not overheat");
    check(sensor_is_overheat(75) == 1, "75 C is overheat");
    led_init();
    check(LED_REG == 0U, "led_init clears register");
    led_set(1);
    check(LED_REG == LED_MASK, "led_set(1) writes register");
    led_toggle();
    check(LED_REG == 0U, "led_toggle turns off");
    printf("\nTests passed: %d | Tests failed: %d\n", passed, failed);
    return failed;
}
