/******************************************************************************
 * @file    uart.h
 * @author  Moustafa Hassanein
 * @brief   UART driver header file
 * @version 1.0
 * @date    2025-05-13
 ******************************************************************************/

#ifndef UART_H
#define UART_H

#include "stdint.h"

void uart2_init(void);
char uart2_read(void);
void uart2_write(const char ch);
void uart2_write_string(const char* str);
void uart2_printf(const char *format, ...);

#endif // UART_H
