#include "drv.h"
#include "uti.h"

/*
* (1U << 10)  // set bit 10 to 1
* &= ~(1U << 11) // set bit 11 to 0
*/

/* 1. Enable clock access to GPIOA
*  2. Set PA5 as output pin 
*  3. Set PA5 high
*/

void sys_init(void)
{
    set_bit(&RCC_AHB1EN_R, GPIOAEN_BIT);
    //RCC_AHB1EN_R |= GPIOAEN;
    set_bit(&GPIOA_MODE_R, MODER5_R_BIT);
    //GPIOA_MODE_R |= (1U << 10);
    clear_bit(&GPIOA_MODE_R,MODER5_L_BIT);
    //GPIOA_MODE_R &= ~(1U << 11);

}

void toggle_led(void)
{
    //GPIOA_OD_R |= LED_PIN;
    toggle_bit(&GPIOA_OD_R,ODR5_BIT);
    //GPIOA_OD_R ^= LED_PIN;
}

void set_led_high(void)
{
    set_bit(&GPIOA_OD_R, ODR5_BIT);
    //GPIOA_OD_R |= LED_PIN;
}

void set_led_low(void)
{
    clear_bit(&GPIOA_OD_R, ODR5_BIT);
    //GPIOA_OD_R &= ~LED_PIN;
}