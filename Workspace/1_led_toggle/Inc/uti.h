#ifndef UTI_H
#define UTI_H

#include <stddef.h>
#include <stdint.h>

void counter_delay(size_t counter);
void set_bit(volatile uint32_t *reg_addr, uint8_t bit_pos);
void clear_bit(volatile uint32_t *reg_addr, uint8_t bit_pos);
void toggle_bit(volatile uint32_t *reg_addr, uint8_t bit_pos);

#endif