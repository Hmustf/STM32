/******************************************************************************
 * @file    gpio.c
 * @author  Moustafa Hassanein
 * @brief   GPIO driver implementation for STM32F4
 * @version 1.0
 * @date    2024-10-01
 *
 * @details
 * This file implements GPIO driver functionality for the STM32F4 microcontroller,
 * including initialization and control of the onboard LED (PA5) and button (PC13).
 * It provides functions to configure, set, toggle, and read GPIO pins.
 *
 * @note
 * - Currently supports basic GPIO configuration for the onboard LED (PA5)
 * - Provides support for the onboard user button (PC13)
 * - The button is active low (returns 1 when pressed)
 *
 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "gpio.h"
#include "drvdfn.h"
#include "bit_utils.h"
#include "stm32f4xx.h"
#include <stdint.h>

/******************************************************************************
 * Defines
 ******************************************************************************/
#define GPIOAEN_BIT             0       /**< GPIO Port A clock enable bit in AHB1ENR register */
#define GPIOCEN_BIT             2       /**< GPIO Port C clock enable bit in AHB1ENR register */

#define PIN5                    5       /**< GPIO pin number for PA5 (onboard LED) */
#define PIN13                   13      /**< GPIO pin number for PC13 (onboard button) */
#define LED_PIN                 PIN5    /**< Alias for onboard LED pin */
#define BTN_PIN                 PIN13   /**< Alias for onboard button pin */

#define MODER5_BIT              (PIN5*MODER_FIELD_WIDTH)    /**< Mode register bit position for PA5 */
#define MODER13_BIT             (PIN13*MODER_FIELD_WIDTH)   /**< Mode register bit position for PC13 */

/******************************************************************************
 * Function Definitions
 ******************************************************************************/

/**
 * @brief  Initialize GPIO pins for onboard LED and button
 * @param  None
 * @retval None
 * @note   Configures PA5 as output (onboard LED) and PC13 as input (onboard button)
 */
void gpio_init(void)
{
    /* Enable clock access to GPIOA */
    BIT_SET(RCC->AHB1ENR, GPIOAEN_BIT);
    
    /* Enable clock access to GPIOC */
    BIT_SET(RCC->AHB1ENR, GPIOCEN_BIT);
    
    /* Set PA5 to output mode (MODER5 = 0b01) */
    FIELD_SET(GPIOA->MODER, BIT_MASK(MODER5_BIT, MODER_FIELD_WIDTH), FIELD_VAL(OUTPUT, MODER5_BIT));
    
    /* Set PC13 to input mode (MODER13 = 0b00) */
    FIELD_SET(GPIOC->MODER, BIT_MASK(MODER13_BIT, MODER_FIELD_WIDTH), FIELD_VAL(INPUT, MODER13_BIT));
}

/**
 * @brief  Set the state of the onboard LED
 * @param  state: Desired LED state (0 = off, non-zero = on)
 * @retval None
 * @note   Controls the onboard LED connected to PA5
 */
void onboard_led_set(uint8_t state)
{
    if(state)
    {
        /* Turn LED on */
        GPIO_PIN_SET(GPIOA, PIN5);
    }
    else
    {
        /* Turn LED off */
        GPIO_PIN_RESET(GPIOA, PIN5);
    }
}

/**
 * @brief  Toggle the state of the onboard LED
 * @param  None
 * @retval None
 * @note   Toggles the onboard LED connected to PA5
 */
void onboard_led_toggle(void)
{
    /* Toggle LED state */
    GPIO_PIN_TOGGLE(GPIOA, PIN5);
}

/**
 * @brief  Check if the onboard button is currently pressed
 * @param  None
 * @retval int8_t: 1 if button is pressed, 0 if not pressed
 * @note   The button on PC13 is active low (reads as 0 when pressed)
 */
int8_t onboard_btn_pressed(void)
{
    /* Button is active low, so we check if the pin is clear */
    return IS_BIT_CLEAR(GPIOC->IDR, BTN_PIN);
}

/**
 * @brief  Get the current logical status of the onboard button pin
 * @param  None
 * @retval int8_t: 1 if pin is high, 0 if pin is low
 * @note   This returns the raw pin state, not the logical button state
 *         (button is pressed when pin is low)
 */
int8_t onboard_btn_status(void)
{
    /* Return the raw pin state (1 = high, 0 = low) */
    return IS_BIT_SET(GPIOC->IDR, BTN_PIN);
}
