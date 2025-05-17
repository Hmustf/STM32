/******************************************************************************
 * @file    drv.c
 * @author  Moustafa Hassanein
 * @brief   Driver initialization source file for STM32F4
 * @version 1.0
 * @date    2024-10-01
 *
 * @details
 * This file implements the initialization sequence for all device drivers
 * used in the system, including GPIO, UART, ADC, and timer configurations.
 * It provides a centralized point for initializing all peripheral drivers
 * in the correct sequence.
 *
 * @note
 * - All peripheral drivers are initialized here in the correct sequence
 * - The initialization order is important to ensure proper operation
 * - GPIO must be initialized first as other peripherals depend on it
 *
 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "drv.h"

/******************************************************************************
 * Function Definitions
 ******************************************************************************/

/**
 * @brief  Initialize all device drivers
 * @param  None
 * @retval None
 * @note   This function must be called at the beginning of the application
 *         before using any peripheral functionality
 *
 * The initialization sequence is:
 * 1. GPIO - Basic pin configurations
 * 2. UART2 - Communication interface
 * 3. ADC - Analog-to-digital converter in continuous mode
 * 4. Timer - System timing functions
 */
void drv_init(void)
{
    /* Initialize GPIO pins */
    gpio_init(); 
    
    /* Initialize UART2 for communication */
    uart2_init();
    
    /* Initialize ADC in continuous conversion mode */
    adc_init(CONV_CONTINUOUS);
    
    /* Initialize timer for timing operations */
    timer_init();
}
