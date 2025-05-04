
#include "brd.h"
#include "uti.h"


int main(void)
{
    brd_init();

    while (1)
    {
        set_led_high();
        counter_delay(100000);
        set_led_low();
        counter_delay(100000);
    }
    
}
