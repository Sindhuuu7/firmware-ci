#include "sensor.h"

int sensor_adc_to_celsius(uint32_t adc)
{
    if (adc > ADC_MAX) {
        adc = ADC_MAX;
    }
    return (int)((adc * 330U) / ADC_MAX);
}

int sensor_is_overheat(int celsius)
{
    return celsius >= OVERHEAT_C;
}
