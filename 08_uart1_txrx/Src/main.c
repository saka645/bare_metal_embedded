#include <stm32f0xx.h>
#include <stdio.h>
#include <uart1.h>



char read_char=0;
int main()
{
	uart1_tx_init();
	printf("hello please enter A\n");
	while(1)
	{
		read_char = uart1_read();
		if(read_char=='A')
		printf("you pressed A\n");
	}
}

