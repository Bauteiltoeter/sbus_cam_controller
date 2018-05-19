#include <avr/io.h>
#include "uart.h"
#include <util/delay.h>
#include "avr/interrupt.h"

int main(void)
{
	uint16_t sbus_values[18];
	uint8_t sbus_raw[25];

	uart_init(UART_BAUD_SELECT(9600,F_CPU) );


	uart1_init(UART_BAUD_SELECT(100000,F_CPU) );
	UCSR1C |= (1<<UPM11); //even parity
	UCSR1C &=~(1<<UPM10);

	UCSR1C |= (1<<USBS0); //2 stop bit
	sei();

	DDRB |= (1<<0);

	for(int i=0; i < 18; i++)
		sbus_values[i] =0;

	for(int i=0; i < 25; i++)
				sbus_raw[i] =0;

	uint16_t counter=0;

#define IRIS 0//         400=f3.5 450=f3.7 500=f4 550=f4.5 600=f4.8 700=f5.2 750=f5.6 800=f6.2 900=f6.7 950=f7.3 1000=f8 1050=f8.7 1100=f9.5 1200=f10 1250=f11 1300=f12 1350=f14 1400=f15 1500=f16 1550=f17 1600=f19 1650=f21 1700=f22 
#define FOCUS 1
#define AF 2
#define ZOOM 3
#define ISO 4
#define SHUTTER 5
#define WHITEBALANCE 6
#define AUDIOLEVEL 7 
#define FRAMERATE 8  //1200=50  1400=59.94 1600=60
#define REC 17




	while(1)
	{	

		counter++;
		


sbus_values[FRAMERATE]=1200;
sbus_values[IRIS]=800;





		sbus_raw[0] = 0xF0; //Startbyte
		sbus_raw[1] = (uint8_t) (sbus_values[0] & 0x07FF);
		sbus_raw[2] = (uint8_t) ((sbus_values[0] & 0x07FF)>>8 | (sbus_values[1] & 0x07FF)<<3);
		sbus_raw[3] = (uint8_t) ((sbus_values[1] & 0x07FF)>>5 | (sbus_values[2] & 0x07FF)<<6);
		sbus_raw[4] = (uint8_t) ((sbus_values[2] & 0x07FF)>>2);
		sbus_raw[5] = (uint8_t) ((sbus_values[2] & 0x07FF)>>10 | (sbus_values[3] & 0x07FF)<<1);
		sbus_raw[6] = (uint8_t) ((sbus_values[3] & 0x07FF)>>7 | (sbus_values[4] & 0x07FF)<<4);
		sbus_raw[7] = (uint8_t) ((sbus_values[4] & 0x07FF)>>4 | (sbus_values[5] & 0x07FF)<<7);
		sbus_raw[8] = (uint8_t) ((sbus_values[5] & 0x07FF)>>1);
		sbus_raw[9] = (uint8_t) ((sbus_values[5] & 0x07FF)>>9 | (sbus_values[6] & 0x07FF)<<2);
		sbus_raw[10] = (uint8_t) ((sbus_values[6] & 0x07FF)>>6 | (sbus_values[7] & 0x07FF)<<5);
		sbus_raw[11] = (uint8_t) ((sbus_values[7] & 0x07FF)>>3);
		sbus_raw[12] = (uint8_t) ((sbus_values[8] & 0x07FF));
		sbus_raw[13] = (uint8_t) ((sbus_values[8] & 0x07FF)>>8 | (sbus_values[9] & 0x07FF)<<3);
		sbus_raw[14] = (uint8_t) ((sbus_values[9] & 0x07FF)>>5 | (sbus_values[10] & 0x07FF)<<6);  
		sbus_raw[15] = (uint8_t) ((sbus_values[10] & 0x07FF)>>2);
		sbus_raw[16] = (uint8_t) ((sbus_values[10] & 0x07FF)>>10 | (sbus_values[11] & 0x07FF)<<1);
		sbus_raw[17] = (uint8_t) ((sbus_values[11] & 0x07FF)>>7 | (sbus_values[12] & 0x07FF)<<4);
		sbus_raw[18] = (uint8_t) ((sbus_values[12] & 0x07FF)>>4 | (sbus_values[13] & 0x07FF)<<7);
		sbus_raw[19] = (uint8_t) ((sbus_values[13] & 0x07FF)>>1);
		sbus_raw[20] = (uint8_t) ((sbus_values[13] & 0x07FF)>>9 | (sbus_values[14] & 0x07FF)<<2);
		sbus_raw[21] = (uint8_t) ((sbus_values[14] & 0x07FF)>>6 | (sbus_values[15] & 0x07FF)<<5);
		sbus_raw[22] = (uint8_t) ((sbus_values[15] & 0x07FF)>>3);

	   // packet[23] = stateByte; //Flags byte

		for(int i=0; i<25; i++)
			uart1_putc(sbus_raw[i]);

		PORTB^=(1<<0);


	_delay_ms(20);




	}
}
