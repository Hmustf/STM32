#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include <stdint.h>

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

#endif // BIT_UTILS_H