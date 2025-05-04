#include "brd.h"
#include "config.h"

void brd_init(void)
{
    #ifdef STM32_F401E
    drv_init();
    #endif
}

void toggle_led(void)
{
    toggle_bit(&(GPIOA->ODR),ODR5_BIT);
}

void set_led_high(void)
{
    set_bit(&(GPIOA->ODR), ODR5_BIT);
}

void set_led_low(void)
{
    clear_bit(&(GPIOA->ODR), ODR5_BIT);
}