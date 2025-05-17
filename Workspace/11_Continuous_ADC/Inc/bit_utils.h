/******************************************************************************
 * @file    bit_utils.h
 * @author  Moustafa Hassanein
 * @brief   Bit manipulation utilities header file
 * @version 1.0
 * @date    2025-05-13
 *
 * @details
 * This file provides bit manipulation macros for register access and
 * bit-level operations commonly used in embedded systems programming.
 * It includes macros for setting, clearing, toggling, and checking bits,
 * as well as field manipulation in registers.
 *
 ******************************************************************************/

#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include <stdint.h>
#include "config.h"

/**
 * @brief  Create a bitmask with a single bit set at position n
 * @param  n: Bit position (0-31)
 * @retval Bitmask with the nth bit set
 */
#define BIT(n)                     (1U << (n))

/**
 * @brief  Create a bitmask for a field of bits
 * @param  start: Starting bit position of the field
 * @param  len: Length of the field in bits
 * @retval Bitmask covering the specified bit field
 */
#define BIT_MASK(start, len)       (((1U << (len)) - 1) << (start))

/**
 * @brief  Position a value at a specific bit position
 * @param  val: Value to position
 * @param  start: Starting bit position
 * @retval Value shifted to the specified bit position
 */
#define FIELD_VAL(val, start)      ((uint32_t)(val) << (start))

/**
 * @brief  Set a specific bit in a register
 * @param  reg: Register to modify
 * @param  bit: Bit position to set
 * @retval None (modifies reg directly)
 */
#define BIT_SET(reg, bit)          ((reg) |= BIT(bit))

/**
 * @brief  Clear a specific bit in a register
 * @param  reg: Register to modify
 * @param  bit: Bit position to clear
 * @retval None (modifies reg directly)
 */
#define BIT_CLEAR(reg, bit)        ((reg) &= ~BIT(bit))

/**
 * @brief  Toggle a specific bit in a register
 * @param  reg: Register to modify
 * @param  bit: Bit position to toggle
 * @retval None (modifies reg directly)
 */
#define BIT_TOGGLE(reg, bit)       ((reg) ^= BIT(bit))

/**
 * @brief  Write a value (0 or 1) to a specific bit in a register
 * @param  reg: Register to modify
 * @param  bit: Bit position to write
 * @param  val: Value to write (0 or non-zero)
 * @retval None (modifies reg directly)
 */
#define BIT_WRITE(reg, bit, val)   \
                                   ((val) ? BIT_SET((reg), (bit)) : BIT_CLEAR((reg), (bit)))

/**
 * @brief  Set a field of bits in a register to a specific value
 * @param  reg: Register to modify
 * @param  mask: Bitmask defining the field
 * @param  val: Value to write to the field (should be pre-shifted to match mask)
 * @retval None (modifies reg directly)
 */
#define FIELD_SET(reg, mask, val)  \
                                   ((reg) = ((reg) & ~(mask)) | ((val) & (mask)))

/**
 * @brief  Check if a specific bit is set in a register
 * @param  reg: Register to check
 * @param  bit: Bit position to check
 * @retval Non-zero if bit is set, 0 if bit is clear
 */
#define IS_BIT_SET(reg, bit)       (((reg) & BIT(bit)) != 0)

/**
 * @brief  Check if a specific bit is clear in a register
 * @param  reg: Register to check
 * @param  bit: Bit position to check
 * @retval Non-zero if bit is clear, 0 if bit is set
 */
#define IS_BIT_CLEAR(reg, bit)     (!IS_BIT_SET(reg, bit))

#ifdef STM32_NUC
/**
 * @brief  Set a specific GPIO pin to high level
 * @param  port: GPIO port (e.g., GPIOA, GPIOB)
 * @param  pin: Pin number (0-15)
 * @retval None (modifies port directly)
 * @note   Uses STM32 BSRR register for atomic bit setting
 */
#define GPIO_PIN_SET(port, pin)    ((port)->BSRR = BIT(pin))

/**
 * @brief  Reset a specific GPIO pin to low level
 * @param  port: GPIO port (e.g., GPIOA, GPIOB)
 * @param  pin: Pin number (0-15)
 * @retval None (modifies port directly)
 * @note   Uses STM32 BSRR register for atomic bit clearing
 */
#define GPIO_PIN_RESET(port, pin)  ((port)->BSRR = BIT((pin) + 16))

/**
 * @brief  Toggle a specific GPIO pin
 * @param  port: GPIO port (e.g., GPIOA, GPIOB)
 * @param  pin: Pin number (0-15)
 * @retval None (modifies port directly)
 * @note   Uses XOR operation on ODR register
 */
#define GPIO_PIN_TOGGLE(port, pin) ((port)->ODR ^= BIT(pin))
#endif

#endif // BIT_UTILS_H
