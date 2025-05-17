/******************************************************************************
 * @file    uart.c
 * @author  Moustafa Hassanein
 * @brief   UART driver implementation for STM32F4
 * @version 1.0
 * @date    2024-10-01
 *
 * @details
 * This file implements the UART driver functionality for STM32F4 devices,
 * including initialization, configuration and data transmission/reception
 * operations using USART2 peripheral.
 *
 * @note
 * - Currently supports UART2 on PA2 (TX) and PA3 (RX)
 * - Default configuration: 115200 baud rate, 8-bit data, no parity, 1 stop bit
 *
 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "uart.h"
#include "bit_utils.h"
#include "stm32f4xx.h"
#include "drvdfn.h"
#include <stdio.h>
#include <stdarg.h>

/******************************************************************************
 * Defines
 ******************************************************************************/
#define GPIOAEN_BIT            0       /**< GPIO Port A clock enable bit in AHB1ENR register */
#define MODER2_BIT             (2*MODER_FIELD_WIDTH)  /**< Mode register bit position for PA2 */
#define MODER3_BIT             (3*MODER_FIELD_WIDTH)  /**< Mode register bit position for PA3 */
#define AFRL2_BIT              (2*AFR_FIELD_WIDTH)    /**< Alternate function register bit position for PA2 */
#define AFRL3_BIT              (3*AFR_FIELD_WIDTH)    /**< Alternate function register bit position for PA3 */
#define UART2EN_BIT            17      /**< USART2 clock enable bit in APB1ENR register */
#define CR1_TE_BIT		       3       /**< Transmitter enable bit in CR1 register */
#define CR1_RE_BIT		       2       /**< Receiver enable bit in CR1 register */
#define CR1_UE_BIT             13      /**< USART enable bit in CR1 register */
#define SR_TXE_BIT             7       /**< Transmit data register empty bit in SR register */
#define SR_RXNE_BIT            5       /**< Read data register not empty bit in SR register */

#define SYS_FREQ               16000000  /**< System clock frequency in Hz (16 MHz) */
#define APB1_CLK	           SYS_FREQ  /**< APB1 peripheral clock frequency in Hz */
#define UART_BAUDRATE		   115200    /**< UART baud rate in bits per second */

/******************************************************************************
 * Function Prototypes
 ******************************************************************************/
/**
 * @brief  Configure GPIO pins for UART2 (PA2 as TX, PA3 as RX)
 * @param  None
 * @retval None
 */
static void uart2_gpio_config(void);

/**
 * @brief  Enable clock for UART2 peripheral
 * @param  None
 * @retval None
 */
static void uart2_clock_enable(void);

/**
 * @brief  Configure UART2 baudrate
 * @param  USARTx: Pointer to USART_TypeDef structure
 * @param  PeriphClk: Peripheral clock frequency in Hz
 * @param  BaudRate: Desired baud rate in bits per second
 * @retval None
 */
static void uart2_baudrate_config(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);

/**
 * @brief  Enable UART2 transmitter
 * @param  None
 * @retval None
 */
static void uart2_enable_tx(void);

/**
 * @brief  Enable UART2 receiver
 * @param  None
 * @retval None
 */
static void uart2_enable_rx(void);

/**
 * @brief  Enable UART2 peripheral
 * @param  None
 * @retval None
 */
static void uart2_enable(void);

/**
 * @brief  Compute UART baudrate register value
 * @param  PeriphClk: Peripheral clock frequency in Hz
 * @param  BaudRate: Desired baud rate in bits per second
 * @retval uint16_t: Value to be written to BRR register
 */
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

/******************************************************************************
 * Function Definitions
 ******************************************************************************/

/**
 * @brief  Configure GPIO pins for UART2 (PA2 as TX, PA3 as RX)
 * @note   Sets PA2 and PA3 to alternate function mode with AF7 (USART2)
 * @param  None
 * @retval None
 */
static void uart2_gpio_config(void)
{
    /* Enable clock access to GPIOA */
    BIT_SET(RCC->AHB1ENR, GPIOAEN_BIT);

    /* Set PA2 to Alternate Function mode (MODER2 = 0b10) */
    FIELD_SET(GPIOA->MODER, BIT_MASK(MODER2_BIT, MODER_FIELD_WIDTH), FIELD_VAL(ALTERNATE, MODER2_BIT));
    /* Set PA2 AF to AF7 (USART2_TX) → AFR[0] bits 11:8 = 0111 */
    FIELD_SET(GPIOA->AFR[0], BIT_MASK(AFRL2_BIT, AFR_FIELD_WIDTH), FIELD_VAL(AF7, AFRL2_BIT));
    /* Set PA3 to Alternate Function mode (MODER2 = 0b10) */
    FIELD_SET(GPIOA->MODER, BIT_MASK(MODER3_BIT, MODER_FIELD_WIDTH), FIELD_VAL(ALTERNATE, MODER3_BIT));
    /* Set PA3 AF to AF7 (USART2_RX) → AFR[0] bits 15:12 = 0111 */
    FIELD_SET(GPIOA->AFR[0], BIT_MASK(AFRL3_BIT, AFR_FIELD_WIDTH), FIELD_VAL(AF7, AFRL3_BIT));
}

/**
 * @brief  Enable clock for UART2 peripheral
 * @param  None
 * @retval None
 */
static void uart2_clock_enable(void)
{
	/*Enable clock access to uart2 */
    BIT_SET(RCC->APB1ENR, UART2EN_BIT);
}

/**
 * @brief  Compute UART baudrate register value
 * @param  PeriphClk: Peripheral clock frequency in Hz
 * @param  BaudRate: Desired baud rate in bits per second
 * @retval uint16_t: Value to be written to BRR register
 */
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

/**
 * @brief  Configure UART2 baudrate
 * @param  USARTx: Pointer to USART_TypeDef structure
 * @param  PeriphClk: Peripheral clock frequency in Hz
 * @param  BaudRate: Desired baud rate in bits per second
 * @retval None
 */
static void uart2_baudrate_config(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate)
{
    /*Configure baudrate*/
    USARTx->BRR =  compute_uart_bd(PeriphClk, BaudRate);

}

/**
 * @brief  Enable UART2 transmitter
 * @param  None
 * @retval None
 */
static void uart2_enable_tx(void)
{
	/*Configure the transfer direction*/
	BIT_SET(USART2->CR1, CR1_TE_BIT);
}

/**
 * @brief  Enable UART2 receiver
 * @param  None
 * @retval None
 */
static void uart2_enable_rx(void)
{
	/*Configure the transfer direction*/
	BIT_SET(USART2->CR1, CR1_RE_BIT);
}

/**
 * @brief  Enable UART2 peripheral
 * @param  None
 * @retval None
 */
static void uart2_enable(void)
{
    /*Enable uart module*/
    BIT_SET(USART2->CR1, CR1_UE_BIT);
}

/**
 * @brief  Initialize UART2 peripheral
 * @note   Configures UART2 with 115200 baud rate, 8-bit data, no parity, 1 stop bit
 * @param  None
 * @retval None
 */
void uart2_init(void)
{
    uart2_gpio_config();
    uart2_clock_enable();
    uart2_baudrate_config(USART2, APB1_CLK, UART_BAUDRATE);
    uart2_enable_tx();
    uart2_enable_rx();
    uart2_enable();
}

/**
 * @brief  Read a character from UART2
 * @note   This function blocks until data is available
 * @param  None
 * @retval char: Received character
 */
char uart2_read(void)
{
    /*Make sure the receive data register is empty*/
    while (IS_BIT_CLEAR(USART2->SR, SR_RXNE_BIT)) {}

    return (char)USART2->DR;
}

/**
 * @brief  Write a character to UART2
 * @note   This function blocks until the transmit buffer is empty
 * @param  ch: Character to be transmitted
 * @retval None
 */
void uart2_write(const char ch)
{
    /*Make sure the transmit data register is empty*/
    while (IS_BIT_CLEAR(USART2->SR, SR_TXE_BIT)) {}

    /*Write to transmit data register*/
    USART2->DR	=  (ch & 0xFF);
}

/**
 * @brief  Write a null-terminated string to UART2
 * @param  str: Pointer to the string to be transmitted
 * @retval None
 */
void uart2_write_string(const char* str)
{
    while (*str)
    {
        uart2_write(*str++);
    }
}

/**
 * @brief  Print formatted output to UART2
 * @note   This function uses a fixed buffer size of 128 bytes
 * @param  format: Format string (printf style)
 * @param  ...: Variable arguments
 * @retval None
 */
void uart2_printf(const char *format, ...)
{
    char buffer[128];  // Adjust size as needed
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    uart2_write_string(buffer);
}