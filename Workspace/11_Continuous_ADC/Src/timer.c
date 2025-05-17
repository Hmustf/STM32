/******************************************************************************
 * @file    timer.c
 * @author  Moustafa Hassanein
 * @brief   timer driver implementation for STM32F4
 * @version 1.0
 * @date    2024-11-01
 *
 *
 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "stm32f4xx.h"
#include "timer.h"
#include "bit_utils.h"
#include "drvdfn.h"

/******************************************************************************
 * Defines
 ******************************************************************************/
#define TIM2EN_BIT	(0)    /**< Timer 2 clock enable bit in APB1ENR register */
#define CR1_CEN_BIT	(0)    /**< Counter enable bit in CR1 register */
#define SR_UIF_BIT  (0)    /**< Update interrupt flag in SR register */

#define SYS_FREQ    16000000  /**< System clock frequency in Hz (16 MHz) */
#define TIM_PSC     1600      /**< Timer prescaler value */
#define TIM_ARR     10000     /**< Timer auto-reload value */

/******************************************************************************
 * Function Definitions
 ******************************************************************************/

/**
 * @brief  Initialize Timer 2 with 1Hz frequency
 * @note   Configures TIM2 to generate a 1Hz timebase
 * @param  None
 * @retval None
 */
void tim2_1hz_init(void)
{
	/* Enable clock access to tim2 */
	BIT_SET(RCC->APB1ENR, TIM2EN_BIT);

	/* Set prescaler value */
	TIM2->PSC = TIM_PSC - 1;  //  16 000 000 / 1 600 = 10 000
	
	/* Set auto-reload value */
	TIM2->ARR = TIM_ARR - 1;  // 10 000 / 10 000 = 1
	
	/* Clear counter */
	TIM2->CNT = 0;

	/* Enable timer */
	BIT_SET(TIM2->CR1, CR1_CEN_BIT);
}

/**
 * @brief  Initialize all timers used in the application
 * @note   Currently only initializes TIM2 with 1Hz frequency
 * @param  None
 * @retval None
 */
void timer_init(void)
{
    tim2_1hz_init();
}

/**
 * @brief  Blocking delay function for 1 second using TIM2
 * @note   This function blocks until TIM2 update event occurs (1 second)
 *         and then clears the update flag
 * @param  None
 * @retval None
 */
void tim2_1sec_wait(void)
{
	/* Wait until update event flag is set */
	while(IS_BIT_CLEAR(TIM2->SR, SR_UIF_BIT)){}
	
	/* Clear update event flag */
	BIT_CLEAR(TIM2->SR, SR_UIF_BIT);
}