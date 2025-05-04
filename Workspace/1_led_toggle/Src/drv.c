#include "drv.h"
#include "uti.h"

void drv_init(void)
{ 
    set_bit(&(RCC->AHB1ENR)  ,  GPIOAEN_BIT);
    set_bit(&(GPIOA->MODER)  , MODER5_R_BIT);
    clear_bit(&(GPIOA->MODER), MODER5_L_BIT);
}

