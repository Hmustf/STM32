#include <stdint.h>

#define _IO                 volatile
#define REGES_TYPE         (_IO uint32_t *)

#define PERIPH_BASE        (0x40000000UL)
#define AHB1PERIPH_OFFSET  (0x00020000UL)
#define AHB1PERIPH_BASE    (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET       (0x0000UL)
#define GPIOA_BASE         (AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET         (0x3800UL)
#define RCC_BASE           (AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIOAEN_BIT        (0U)
#define ODR5_BIT           (5U) 
#define MODER5_R_BIT       (10U)
#define MODER5_L_BIT       (11U)

typedef struct
{
  _IO uint32_t DUMMY[12];
  _IO uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,   Address offset: 0x30 */
} RCC_TypeDef;

typedef struct
{
	_IO uint32_t MODER;       /*!< GPIO port mode register,                 Address offset: 0x00 */
	_IO uint32_t DUMMY[4];
	_IO uint32_t ODR;         /*!< GPIO port output data register,          Address offset: 0x14 */
} GPIO_TypeDef;

#define RCC    ((RCC_TypeDef* )   RCC_BASE)
#define GPIOA  ((GPIO_TypeDef*) GPIOA_BASE)

void drv_init(void);
