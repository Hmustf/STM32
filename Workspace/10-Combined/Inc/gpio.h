/******************************************************************************
 * @file    gpio.h
 * @author  Moustafa Hassanein
 * @brief   GPIO driver header file
 * @version 1.0
 * @date    2024-10-01
 ******************************************************************************/

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

void gpio_init(void);
void onboard_led_set(uint8_t state);
void onboard_led_toggle(void);
int8_t onboard_btn_pressed(void);
int8_t onboard_btn_status(void);

#endif // GPIO_H
