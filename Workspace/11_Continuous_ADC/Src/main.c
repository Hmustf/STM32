/******************************************************************************
 * @file    main.c
 * @author  Moustafa Hassanein
 * @brief   Main application
 * @version 1.0
 * @date    2024-10-01
 *
 * @details
 * This file contains the main application entry point and the main program loop.
 * It initializes all system components and implements a simple demonstration of
 * timer, LED control, and UART communication functionality.
 *
 * @note
 * - The system runs in an infinite loop, toggling the LED every second
 * - UART messages are sent at 1Hz to indicate timing
 * - This serves as a basic demonstration of peripheral functionality
 *
 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "system.h"

/******************************************************************************
 * Function Definitions
 ******************************************************************************/

/**
 * @brief  Main application entry point
 * @param  None
 * @retval int: Program return value (never returns in embedded applications)
 * @note   This function initializes the system and enters an infinite loop
 *         that demonstrates timer, LED, and UART functionality
 */
int main(void)
{
    /* Initialize all system components */
    sys_init();

    /* Main program loop */
	while(1)
	{
        /* Wait for 1 second using Timer2 */
        tim2_1sec_wait();
        
        /* Toggle the onboard LED state */
        onboard_led_toggle();
        
        /* Send status message via UART */
        uart2_printf("One second passed!\r\n");
    }
}

