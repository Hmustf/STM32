/******************************************************************************
 * @file    adc.c
 * @author  Moustafa Hassanein
 * @brief   ADC driver implementation for STM32F4
 * @version 1.0
 * @date    2024-11-01
 *
 * @details
 * This file implements the ADC driver functionality for STM32F4 devices.
 * It configures ADC1 to sample from PA1 (ADC1_IN1) and provides functions
 * for both single and continuous conversion modes.
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

/******************************************************************************
 * Defines
 ******************************************************************************/
#define GPIOAEN_BIT             0       /**< GPIO Port A clock enable bit in AHB1ENR register */
#define ADC1EN_BIT              8       /**< ADC1 clock enable bit in APB2ENR register */
#define MODER1_BIT             (1 * MODER_FIELD_WIDTH)  /**< Mode register bit position for PA1 */
#define ADC_SQ_FIELD_WIDTH      5       /**< Width of sequence fields in SQRx registers */
#define SQR3_SQ1_BIT            0       /**< First sequence position bit in SQR3 register */
#define ADC1_CH1                1       /**< ADC1 channel 1 (connected to PA1) */
#define CR2_ADON_BIT            0       /**< ADC enable bit in CR2 register */
#define CR2_CONT_BIT            1       /**< Continuous conversion mode bit in CR2 register */
#define CR2_SWSTART_BIT         30      /**< Software start conversion bit in CR2 register */
#define SR_EOC_BIT              1       /**< End of conversion flag bit in SR register */

/******************************************************************************
 * Function Prototypes
 ******************************************************************************/
/**
 * @brief  Configure ADC conversion mode
 * @param  _adc_mode: ADC conversion mode (CONV_SINGLE or CONV_CONTINUOUS)
 * @retval None
 * @note   In continuous mode, conversion is started automatically
 */
static void set_conversion_mode(conv_mode_t _adc_mode);

/******************************************************************************
 * Function Definitions
 ******************************************************************************/

/**
 * @brief  Configure ADC conversion mode
 * @param  _adc_mode: ADC conversion mode (CONV_SINGLE or CONV_CONTINUOUS)
 * @retval None
 * @note   In continuous mode, conversion is started automatically
 */
static void set_conversion_mode(conv_mode_t _adc_mode)
{
    if(_adc_mode == CONV_CONTINUOUS)
    {
        /* Set continuous conversion mode */
        BIT_SET(ADC1->CR2, CR2_CONT_BIT);
        /* Start continuous conversion */
        start_conversion();
    }
    else if (_adc_mode == CONV_SINGLE)
    {
        /* Set single conversion mode */
        BIT_CLEAR(ADC1->CR2, CR2_CONT_BIT); 
    }
}

/**
 * @brief  Initialize the ADC peripheral
 * @param  _adc_mode: ADC conversion mode (CONV_SINGLE or CONV_CONTINUOUS)
 * @retval None
 * @note   Configures ADC1 to sample from PA1 (ADC1_IN1)
 */
void adc_init(conv_mode_t _adc_mode)
{
    /* Enable clock access to GPIOA */
    BIT_SET(RCC->AHB1ENR, GPIOAEN_BIT);
    
    /* Set PA1 to Analog mode (MODER1 = 0b11) */
    FIELD_SET(GPIOA->MODER, BIT_MASK(MODER1_BIT, MODER_FIELD_WIDTH), FIELD_VAL(ANALOG, MODER1_BIT));
	
    /* Enable clock access to adc1 */
    BIT_SET(RCC->APB2ENR, ADC1EN_BIT);
    
    /* Clear SQR3 register */
    ADC1->SQR3 = 0;
    
    /* Set SQ1 = channel 1 (bits [4:0]) */
    FIELD_SET(ADC1->SQR3, BIT_MASK(SQR3_SQ1_BIT, ADC_SQ_FIELD_WIDTH), FIELD_VAL(ADC1_CH1, SQR3_SQ1_BIT));
    
    /* Clear L[3:0] in SQR1 (1 conversion => L = 0) */
    FIELD_SET(ADC1->SQR1, BIT_MASK(20, 4), FIELD_VAL(0, 20));
    
    /* Enable ADC Module */
    BIT_SET(ADC1->CR2, CR2_ADON_BIT);

    /* Set conversion mode (single or continuous) */
    set_conversion_mode(_adc_mode);
}

/**
 * @brief  Start ADC conversion
 * @param  None
 * @retval None
 * @note   In single conversion mode, this triggers one conversion
 *         In continuous mode, this starts the continuous conversion sequence
 */
void start_conversion(void)
{
    /* Set software start conversion bit */
    BIT_SET(ADC1->CR2, CR2_SWSTART_BIT);
}

/**
 * @brief  Read the latest ADC conversion result
 * @param  None
 * @retval uint32_t: The 12-bit ADC conversion result (0-4095)
 * @note   In single conversion mode, this function waits for conversion to complete
 *         In continuous mode, it returns the most recent conversion result
 */
uint32_t adc_read(void)
{
    /* Wait until end of conversion flag is set */
    while (IS_BIT_CLEAR(ADC1->SR, SR_EOC_BIT)) {}

    /* Return conversion result */
    return (uint32_t)ADC1->DR;
}
