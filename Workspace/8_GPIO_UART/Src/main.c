/******************************************************************************
 * @file    main.c
 * @author  Moustafa Hassanein
 * @brief   Main application
 * @version 1.0
 * @date    2024-10-01
 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "system.h"

char rchar;
int8_t btnstatus;

int main(void)
{
    sys_init();

    while (1)
    {
        // 1. Check button periodically (non-blocking)
        if (onboard_btn_status())
        {
            onboard_led_toggle();
            while (onboard_btn_status());  // crude debounce
        }

    }
}

