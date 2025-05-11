#include "uart.h"
#include "bit_utils.h"
#include "stm32f4xx.h"

#define GPIOAEN_BIT            0
#define MODER_BIT_SIZE         2
#define MODER2_BIT             (2*MODER_BIT_SIZE)
#define MODER3_BIT             (3*MODER_BIT_SIZE)
#define AFR_BIT_SIZE           4
#define AFRL2_BIT              (2*AFR_BIT_SIZE)
#define AFRL3_BIT              (3*AFR_BIT_SIZE)
#define UART2EN_BIT            17
#define CR1_TE_BIT		       3
#define CR1_UE_BIT             13
#define SR_TXE_BIT             7

#define ALTERNATE             (uint32_t)0b10
#define AF7                   (uint32_t)0b0111


#define SYS_FREQ		16000000
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE		115200

static void uart2_gpio_config(void);
static void uart2_clock_enable(void);
static void uart2_baudrate_config(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate);
static void uart2_enable_tx(void);
static void uart2_enable(void);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

static void uart2_gpio_config(void)
{
    /* Enable clock access to GPIOA */
    BIT_SET(RCC->AHB1ENR, GPIOAEN_BIT);

    /* Set PA2 to Alternate Function mode (MODER2 = 0b10) */
    FIELD_SET(GPIOA->MODER, BIT_MASK(MODER2_BIT, MODER_BIT_SIZE), FIELD_VAL(ALTERNATE, MODER2_BIT));
    /* Set PA2 AF to AF7 (USART2_TX) → AFR[0] bits 11:8 = 0111 */
    FIELD_SET(GPIOA->AFR[0], BIT_MASK(AFRL2_BIT, AFR_BIT_SIZE), FIELD_VAL(AF7, AFRL2_BIT));
    /* Set PA3 to Alternate Function mode (MODER2 = 0b10) */
    FIELD_SET(GPIOA->MODER, BIT_MASK(MODER3_BIT, MODER_BIT_SIZE), FIELD_VAL(ALTERNATE, MODER3_BIT));
    /* Set PA3 AF to AF7 (USART2_RX) → AFR[0] bits 15:12 = 0111 */
    FIELD_SET(GPIOA->AFR[0], BIT_MASK(AFRL2_BIT, AFR_BIT_SIZE), FIELD_VAL(AF7, AFRL2_BIT));
}

static void uart2_clock_enable(void)
{
	/*Enable clock access to uart2 */
    BIT_SET(RCC->APB1ENR, UART2EN_BIT);   
}

static void uart2_baudrate_config(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate)
{
    /*Configure baudrate*/
    USARTx->BRR =  compute_uart_bd(PeriphClk, BaudRate);

}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

static void uart2_enable_tx(void)
{
	/*Configure the transfer direction*/
	BIT_SET(USART2->CR1, CR1_TE_BIT);   
}

static void uart2_enable(void)
{
    /*Enable uart module*/
    BIT_SET(USART2->CR1, CR1_UE_BIT);
}

void uart2_init(void)
{
    uart2_gpio_config();
    uart2_clock_enable();
    uart2_baudrate_config(USART2, APB1_CLK, UART_BAUDRATE);
    uart2_enable_tx();
    uart2_enable();
}

void uart2_write(const char ch)
{
    /*Make sure the transmit data register is empty*/
    while (IS_BIT_CLEAR(USART2->SR, SR_TXE_BIT)) {}

    /*Write to transmit data register*/
    USART2->DR	=  (ch & 0xFF);
}

void uart2_write_string(const char* str)
{
    while (*str)
    {
        uart2_write(*str++);
    }
}