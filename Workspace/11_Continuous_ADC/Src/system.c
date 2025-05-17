/******************************************************************************
 * @file    system.c
 * @author  Moustafa Hassanein
 * @brief   System initialization
 * @version 1.0
 * @date    2024-10-01
 *
 * @details
 * This file implements the system initialization sequence for the application.
 * It serves as the top-level initialization module that conditionally
 * initializes hardware drivers based on the target platform configuration.
 *
 * @note
 * - The initialization is platform-dependent and controlled by configuration flags
 * - For STM32 Nucleo boards (STM32_NUC defined), it initializes all drivers
 * - Additional platform support can be added with appropriate conditional blocks
 *
 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "system.h"
#include "config.h"

/******************************************************************************
 * Function Definitions
 ******************************************************************************/

/**
 * @brief  Initialize the system
 * @param  None
 * @retval None
 * @note   This function must be called at the beginning of the application
 *         before any other functionality is used
 *
 * The function performs platform-specific initialization:
 * - For STM32 Nucleo boards: Initializes all hardware drivers
 */
void sys_init(void)
{
    #ifdef STM32_NUC
    /* Initialize all drivers for STM32 Nucleo platform */
    drv_init();
    #endif
}

