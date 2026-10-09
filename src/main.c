#include "led.h"
#include "sensor.h"

static const volatile uint32_t adc_sample = 310U;

int main(void)
{
    led_init();
    for (;;) {
        int temp = sensor_adc_to_celsius(adc_sample);
        led_set(sensor_is_overheat(temp));
    }
}
