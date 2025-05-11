/******************************************************************************
 * @file    bit_utils.h
 * @author  Moustafa Hassanein
 * @brief   Bit manipulation utilities header file
 * @version 1.0
 * @date    2024-10-01
 ******************************************************************************/

#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include <stdint.h>
#include "config.h"

#define BIT(n)                     (1U << (n))
#define BIT_MASK(start, len)       (((1U << (len)) - 1) << (start))
#define FIELD_VAL(val, start)      ((uint32_t)(val) << (start))
#define BIT_SET(reg, bit)          ((reg) |= BIT(bit)) 
#define BIT_CLEAR(reg, bit)        ((reg) &= ~BIT(bit))
#define BIT_TOGGLE(reg, bit)       ((reg) ^= BIT(bit))
#define BIT_WRITE(reg, bit, val)   \
                                   ((val) ? BIT_SET((reg), (bit)) : BIT_CLEAR((reg), (bit)))
#define FIELD_SET(reg, mask, val)  \
                                   ((reg) = ((reg) & ~(mask)) | ((val) & (mask)))
#define IS_BIT_SET(reg, bit)       (((reg) & BIT(bit)) != 0)
#define IS_BIT_CLEAR(reg, bit)     (!IS_BIT_SET(reg, bit))

#ifdef STM32_NUC
#define GPIO_PIN_SET(port, pin)    ((port)->BSRR = BIT(pin))
#define GPIO_PIN_RESET(port, pin)  ((port)->BSRR = BIT((pin) + 16))
#define GPIO_PIN_TOGGLE(port, pin) ((port)->ODR ^= BIT(pin))
#endif

#endif // BIT_UTILS_H