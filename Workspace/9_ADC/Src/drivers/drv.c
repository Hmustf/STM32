/******************************************************************************
 * @file    drv.c
 * @author  Moustafa Hassanein
 * @brief   Driver initialization source file for STM32F4
 * @version 1.0
 * @date    2024-10-01
 *
 * @details
 * This file implements the initialization sequence for all device drivers
 * used in the system, including GPIO and UART configurations.
 *
 * @note
 * - All peripheral drivers are initialized here in the correct sequence
 *
 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "gpio.h"
#include "uart.h"
#include "adc.h"

void drv_init(void)
{
    gpio_init();
    uart2_init();
    adc_init();
}