
#include <stdint.h>


// Where is LED connected (Port - Pin)
// Port : A
// Pin  : 5



#define REGES_TYPE         (volatile uint32_t *)
#define PERIPH_BASE        (0x40000000UL)
#define AHB1PERIPH_OFFSET  (0x00020000UL)
#define AHB1PERIPH_BASE    (PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET       (0x0000UL)

#define GPIOA_BASE         (AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET         (0x3800UL)
#define RCC_BASE           (AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET    (0x30UL)
#define RCC_AHB1EN_R       (*REGES_TYPE(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET      (0x00UL)
#define GPIOA_MODE_R       (*REGES_TYPE(GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET        (0x14UL)
#define GPIOA_OD_R         (*REGES_TYPE(GPIOA_BASE + OD_R_OFFSET))


#define GPIOAEN            (1U<<0)    // 0b 0000 0000 0000 0000 0000 0000 0000 0001 

#define GPIOAEN_BIT        (0U)

#define PIN5               (1U<<5)
#define LED_PIN            PIN5

#define ODR5_BIT           (5U) 

#define MODER5_R_BIT       (10U)
#define MODER5_L_BIT       (11U)




void sys_init(void);
void toggle_led(void);
void set_led_low(void);
void set_led_high(void);
