/******************************************************************************
 * @file    adc.h
 * @author  Moustafa Hassanein
 * @brief   ADC driver header file
 * @version 1.0
 * @date    2024-11-01
 ******************************************************************************/

#ifndef ADC_H
#define ADC_H
#include <stdint.h>

void adc_init(void);
uint32_t adc_get_sample(void);

#endif // ADC_H