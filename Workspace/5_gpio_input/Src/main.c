
#include "stm32f4xx.h"


// PC13 (pin 2)

#define GPIOAEN   (1U<<0)
#define GPIOCEN   (1U<<2)

#define PIN5      (1U<<5)
#define PIN13     (1U<<13)


#define LED_PIN    PIN5
#define BTN_PIN    PIN13

void sysinit(void)
{
	RCC ->AHB1ENR |= GPIOAEN;
	RCC ->AHB1ENR |= GPIOCEN;


	GPIOA->MODER |=  (1U<< 10);
	GPIOA->MODER &= ~(1U<< 11);

	GPIOC->MODER &= ~(1U<< 26);
	GPIOC->MODER &= ~(1U<< 27);

}


int main(void)
{
	sysinit();

	while(1)
	{
		if(GPIOC->IDR & BTN_PIN)
		{
			GPIOA->BSRR = LED_PIN;
		}
		else
		{
			GPIOA->BSRR = (1U<<21);
		}
	}
}
