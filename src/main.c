#include <avr/io.h>
#include "uart.h"
#include <util/delay.h>
int main(void)
{
	uint16_t sbus_values[18];
	uint8_t sbus_raw[25];


	uart_init(UART_BAUD_SELECT(100000,F_CPU) );
	UCSR0C |= (1<<UPM01); //even parity
	UCSR0C &=~(1<<UPM00);

	UCSR0C |= (1<<USBS0); //2 stop bit



while(1)
{	
	for(int i=0; i < 25; i++)
		sbus_raw[i] =0;

	sbus_raw[0] = 0xF0; //Startbyte

	 sbus_raw[1] = 0x00;
	 sbus_raw[2] = 0x00;

	 for(int i=0; i<25; i++)
		 uart_putc(sbus_raw[i]);

	 _delay_ms(14);
}
}
