#include <stm32f0xx.h>
#include <stdio.h>
#include "adc.h"
#include "uart2.h"




uint32_t sensor_value = 0;
char key = 0;


int main()
{
	uart2_tx_init();
	puts("press letter A\n");
	while(1)
	{
		key = uart2_read();
		if(key == 'A')
		printf("you pressed A\n");
	}
}
