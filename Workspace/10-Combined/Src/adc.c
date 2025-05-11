/******************************************************************************
 * @file    adc.c
 * @author  Moustafa Hassanein
 * @brief   ADC driver implementation for STM32F4
 * @version 1.0
 * @date    2024-11-01
 *
 * @details
 * This file implements the ADC driver functionality for STM32F4 devices.
 *
 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "adc.h"
#include "drvdfn.h"
#include "bit_utils.h"
#include "stm32f4xx.h"
#include <stdint.h>

#define GPIOAEN_BIT             0
#define ADC1EN_BIT              8
#define MODER1_BIT             (1 * MODER_FIELD_WIDTH)
#define ADC_SQ_FIELD_WIDTH      5
#define SQR3_SQ1_BIT            0
#define ADC1_CH1                1
#define CR2_ADON_BIT            0
#define CR2_SWSTART_BIT         30
#define SR_EOC_BIT              1

void adc_init(void)
{
    /* Enable clock access to GPIOA */
    BIT_SET(RCC->AHB1ENR, GPIOAEN_BIT);
    /* Set PA1 to Analog mode (MODER2 = 0b11) */
    FIELD_SET(GPIOA->MODER, BIT_MASK(MODER1_BIT, MODER_FIELD_WIDTH), FIELD_VAL(ANALOG, MODER1_BIT));
	/*Enable clock access to adc1 */
    BIT_SET(RCC->APB2ENR, ADC1EN_BIT);
    /*Clear SQR3 */
    ADC1->SQR3 = 0;
    /*Set SQ1 = channel 1 (bits [4:0]) */
    FIELD_SET(ADC1->SQR3, BIT_MASK(SQR3_SQ1_BIT, ADC_SQ_FIELD_WIDTH), FIELD_VAL(ADC1_CH1, SQR3_SQ1_BIT));  // SQ1 = 1
    // Clear L[3:0] in SQR1 (1 conversion => L = 0)
    FIELD_SET(ADC1->SQR1, BIT_MASK(20, 4), FIELD_VAL(0, 20));
    /*Enable ADC Module */
    BIT_SET(ADC1->CR2, CR2_ADON_BIT);
}

void start_conversion(void)
{
    BIT_SET(ADC1->CR2, CR2_SWSTART_BIT);
}

uint32_t adc_read(void)
{
    /*Make sure the conversion ended*/
    while (IS_BIT_CLEAR(ADC1->SR, SR_EOC_BIT)) {}

    return (uint32_t)ADC1->DR;
}

uint32_t adc_get_sample(void)
{
    start_conversion();
    return adc_read();
}
