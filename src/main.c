#include <avr/io.h>
#include "uart.h"
#include <util/delay.h>
#include "avr/interrupt.h"
#include "bmmcc.h"

int main(void)
{
	DDRA|= (1<<0);
	DDRA&=~(1<<0);

    uart_init(UART_BAUD_SELECT(115200,F_CPU) );

	bmmcc_init();
	sei();

	DDRB |= (1<<0);

	uint16_t counter=0;

    bmmcc_setFramerate(fps_50);

	while(1)
	{	

		counter++;

		if(counter >100)
		{
			counter=0;
			bmmcc_ISO(1); //mehr ISO!
		}		
		
		bmmcc_run();

		//muss noch weg, alles mit ordentlich und so
		_delay_ms(14);
	}
}
