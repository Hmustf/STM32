#include "uart.h"

int main(void)
{
	uart2_init();

	while(1)
	{
		uart2_write_string("Hello, world!\n");	
		for (volatile int i = 0; i < 100000; ++i);
	}
}

