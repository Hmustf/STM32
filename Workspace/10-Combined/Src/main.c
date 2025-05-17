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

uint32_t sensor_value;

int main(void)
{
    sys_init();

    while (1)
    {
        sensor_value = adc_get_sample();
        uart2_printf("[SENSOR] ADC CH1 = %lu\r\n", sensor_value);
        for (volatile int i = 0; i < 100000; ++i);
    }
}

