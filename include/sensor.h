#ifndef SENSOR_H
#define SENSOR_H
#include <stdint.h>
#define ADC_MAX 4095U
#define OVERHEAT_C 75
int sensor_adc_to_celsius(uint32_t adc);
int sensor_is_overheat(int celsius);
#endif
