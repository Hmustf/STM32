#ifndef UART_H
#define UART_H

void uart2_init(void);
void uart2_write(const char ch);
void uart2_write_string(const char* str);

#endif // UART_H