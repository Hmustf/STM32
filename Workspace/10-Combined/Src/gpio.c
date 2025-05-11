/******************************************************************************
 * @file    gpio.c
 * @author  Moustafa Hassanein
 * @brief   GPIO driver implementation for STM32F4
 * @version 1.0
 * @date    2024-10-01
 *
 * @details
 * This file implements GPIO driver functionality for the STM32F4 microcontroller,
 * including initialization and control of the onboard LED.
 *
 * @note
 * - Currently supports basic GPIO configuration for the onboard LED (PA5)
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


#define GPIOAEN_BIT             0
#define GPIOCEN_BIT             2

#define PIN5                    5
#define PIN13                   13
#define LED_PIN                 PIN5
#define BTN_PIN                 PIN13

#define MODER5_BIT              (PIN5*MODER_FIELD_WIDTH)
#define MODER13_BIT             (PIN13*MODER_FIELD_WIDTH)


void gpio_init(void)
{
    /* Enable clock access to GPIOA */
    BIT_SET(RCC->AHB1ENR, GPIOAEN_BIT);
    BIT_SET(RCC->AHB1ENR, GPIOCEN_BIT);
    /* Set PA5 to output mode (MODER5 = 0b01) */
    FIELD_SET(GPIOA->MODER, BIT_MASK(MODER5_BIT, MODER_FIELD_WIDTH), FIELD_VAL(OUTPUT, MODER5_BIT));
    /* Set PC13 to input mode (MODER5 = 0b00) */
    FIELD_SET(GPIOC->MODER, BIT_MASK(MODER13_BIT, MODER_FIELD_WIDTH), FIELD_VAL(INPUT, MODER13_BIT));
}

void onboard_led_set(uint8_t state)
{
    if(state)
    {
        GPIO_PIN_SET(GPIOA, PIN5);
    }
    else
    {
        GPIO_PIN_RESET(GPIOA, PIN5);
    }

}

void onboard_led_toggle(void)
{
    GPIO_PIN_TOGGLE(GPIOA, PIN5);
}

int8_t onboard_btn_pressed(void)
{
    return IS_BIT_CLEAR(GPIOC->IDR, BTN_PIN);
}

int8_t onboard_btn_status(void)
{
    return IS_BIT_SET(GPIOC->IDR, BTN_PIN);
}
