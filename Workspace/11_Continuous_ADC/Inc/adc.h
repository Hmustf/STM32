/******************************************************************************
 * @file    adc.h
 * @author  Moustafa Hassanein
 * @brief   ADC driver header file
 * @version 1.0
 * @date    2025-05-13
 *
 * @details
 * This file provides the interface for the ADC (Analog-to-Digital Converter) 
 * driver for STM32F4 microcontrollers. It includes functions for initializing
 * the ADC, starting conversions, and reading conversion results.
 *
 * @note
 * - The ADC is configured to use PA0 (ADC1_IN0) as the analog input channel
 * - The ADC can be configured in single or continuous conversion mode
 * - Default ADC configuration: 12-bit resolution, right-aligned data
 *
 ******************************************************************************/

#ifndef ADC_H
#define ADC_H
#include <stdint.h>

/**
 * @brief  ADC conversion mode enumeration
 * @note   Defines the available ADC conversion modes
 */
typedef enum
{
    CONV_SINGLE = 0,    /**< Single conversion mode: ADC performs one conversion when triggered */
    CONV_CONTINUOUS     /**< Continuous conversion mode: ADC continuously performs conversions */
} conv_mode_t;

/**
 * @brief  Initialize the ADC peripheral
 * @param  _adc_mode: ADC conversion mode (CONV_SINGLE or CONV_CONTINUOUS)
 * @retval None
 * @note   This function configures ADC1 with the specified conversion mode
 *         and sets up PA0 as the analog input channel
 */
void adc_init(conv_mode_t _adc_mode);

/**
 * @brief  Start ADC conversion
 * @param  None
 * @retval None
 * @note   In single conversion mode, this triggers one conversion
 *         In continuous mode, this starts the continuous conversion sequence
 */
void start_conversion(void);

/**
 * @brief  Read the latest ADC conversion result
 * @param  None
 * @retval uint32_t: The 12-bit ADC conversion result (0-4095)
 * @note   In single conversion mode, this function waits for conversion to complete
 *         In continuous mode, it returns the most recent conversion result
 */
uint32_t adc_read(void);

#endif // ADC_H
