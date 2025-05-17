/******************************************************************************
 * @file    drvdfn.h
 * @author  Moustafa Hassanein
 * @brief   Driver definitions header file
 * @version 1.0
 * @date    2025-05-13
 *
 * @details
 * This file provides common definitions and constants used by various
 * peripheral drivers in the STM32F4 microcontroller. It includes GPIO mode
 * definitions, alternate function values, and register field width constants.
 *
 ******************************************************************************/

#ifndef DRVDFN_H
#define DRVDFN_H

/**
 * @brief  GPIO pin mode: Input mode
 * @note   Corresponds to MODER register value 0b00
 */
#define INPUT                 (uint32_t)0b00

/**
 * @brief  GPIO pin mode: Output mode
 * @note   Corresponds to MODER register value 0b01
 */
#define OUTPUT                (uint32_t)0b01

/**
 * @brief  GPIO pin mode: Alternate function mode
 * @note   Corresponds to MODER register value 0b10
 */
#define ALTERNATE             (uint32_t)0b10

/**
 * @brief  GPIO pin mode: Analog mode
 * @note   Corresponds to MODER register value 0b11
 */
#define ANALOG                (uint32_t)0b11

/**
 * @brief  GPIO alternate function 7 (USART1-3)
 * @note   Corresponds to AFR register value 0b0111
 */
#define AF7                   (uint32_t)0b0111

/**
 * @brief  Width of each field in the GPIO MODER register
 * @note   Each pin's mode requires 2 bits in the MODER register
 */
#define MODER_FIELD_WIDTH      2

/**
 * @brief  Width of each field in the GPIO AFR register
 * @note   Each pin's alternate function requires 4 bits in the AFR register
 */
#define AFR_FIELD_WIDTH        4

#endif // DRVDFN_H
