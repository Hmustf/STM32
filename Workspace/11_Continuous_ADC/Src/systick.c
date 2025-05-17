/******************************************************************************
 * @file    systick.c
 * @author  Moustafa Hassanein
 * @brief   Systick driver implementation for STM32F4
 * @version 1.0
 * @date    2024-05-13
 *
 * @details
 * This file implements the systick driver functionality for STM32F4 devices.
 * It configures the SysTick timer to provide millisecond-level delay functions
 * using the system clock as the time base.
 *
 * @note
 * - The SysTick timer is configured to use the processor clock (16 MHz)
 * - Each tick represents 1 millisecond
 * - The implementation uses polling (blocking) to measure elapsed time
 *
 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "drvdfn.h"
#include "bit_utils.h"
#include "stm32f4xx.h"
#include "systick.h"
#include <stdint.h>

/******************************************************************************
 * Defines
 ******************************************************************************/
/**
 * @brief  SysTick reload value for 1ms timing
 * @note   Based on 16MHz system clock, this gives 1ms period
 */
#define SYSTICK_LOAD_VAL    16000

/**
 * @brief  SysTick control register bit positions
 */
#define CTRL_EN_BIT         0       /**< SysTick counter enable bit */
#define CTRL_CLKSRC_BIT     2       /**< Clock source selection bit (0=AHB/8, 1=processor clock) */
#define CTRL_COUNTFLAG      16      /**< Returns 1 if timer counted to 0 since last read */

/******************************************************************************
 * Function Definitions
 ******************************************************************************/

/**
 * @brief  Generate a delay in milliseconds using SysTick timer
 * @param  ms: Number of milliseconds to delay
 * @retval None
 * @note   This is a blocking function that waits for the specified time
 *         before returning. Maximum delay is limited by uint32_t range.
 */
void systickDelayMs(uint32_t ms)
{
    /* Set reload value for 1ms timing */
    SysTick->LOAD = SYSTICK_LOAD_VAL;
    
    /* Clear current value */
    SysTick->VAL = 0;

    /* Enable SysTick counter */
    BIT_SET(SysTick->CTRL, CTRL_EN_BIT);
    
    /* Use processor clock as source (16MHz) */
    BIT_SET(SysTick->CTRL, CTRL_CLKSRC_BIT);

    /* Wait for the requested number of milliseconds */
    for(uint32_t i = 0; i < ms; i++) {
        /* Wait until the COUNTFLAG is set (timer has counted to 0) */
        while (IS_BIT_CLEAR(SysTick->CTRL, CTRL_COUNTFLAG))
            ;
    }
    
    /* Disable SysTick counter when done */
    SysTick->CTRL = 0;
}