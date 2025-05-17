/******************************************************************************
 * @file    config.h
 * @author  Moustafa Hassanein
 * @brief   Configuration header file
 * @version 1.0
 * @date    2025-05-13
 *
 * @details
 * This file contains global configuration settings and feature flags for the
 * entire project. It defines macros that control conditional compilation
 * of hardware-specific code and feature sets.
 *
 * @note
 * - This file should be included in all source files that require
 *   configuration-dependent behavior
 * - Modify this file to enable or disable features for different hardware targets
 *
 ******************************************************************************/

#ifndef CONFIG_H
#define CONFIG_H

/**
 * @brief  STM32 Nucleo board configuration flag
 * @note   When defined, enables Nucleo board specific code
 *         - Enables GPIO pin manipulation macros specific to STM32 hardware
 *         - Configures peripherals according to Nucleo board connections
 */
#define STM32_NUC

#endif // CONFIG_H
