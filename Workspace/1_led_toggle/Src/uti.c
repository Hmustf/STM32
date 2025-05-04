#include "uti.h"

/**
 * @brief Set a specific bit in a register
 * @param reg_addr Pointer to register
 * @param bit_pos Position of the bit to set
 */
void set_bit(volatile uint32_t *reg_addr, uint8_t bit_pos)
{
    *reg_addr |= (1U << bit_pos);
}

/**
 * @brief Clear a specific bit in a register
 * @param reg_addr Pointer to register
 * @param bit_pos Position of the bit to clear
 */
void clear_bit(volatile uint32_t *reg_addr, uint8_t bit_pos)
{
    *reg_addr &= ~(1U << bit_pos);
}

/**
 * @brief Toggle a specific bit in a register
 * @param reg_addr Pointer to register
 * @param bit_pos Position of the bit to toggle
 */
void toggle_bit(volatile uint32_t *reg_addr, uint8_t bit_pos)
{
    *reg_addr ^= (1U << bit_pos);
}

void counter_delay(size_t counter)
{
    for (size_t i = 0; i < counter; i++)
    ;
}
