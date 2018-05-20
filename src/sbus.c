#include "sbus.h"
#include "uart.h"

static uint16_t sbus_values[18];

void sbus_init(void)
{
	uart1_init(UART_BAUD_SELECT(100000,F_CPU) );
	UCSR1C |= (1<<UPM11); //even parity
	UCSR1C &=~(1<<UPM10);

	UCSR1C |= (1<<USBS0); //2 stop bit

	for(uint8_t i=0; i < 18; i++)
		sbus_values[i] =0;
}

void sbus_run(void)
{
	uint8_t sbus_raw[25];

	for(uint8_t i=0; i < 25; i++)
		sbus_raw[i]=0;

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
}

void sbus_setvalue(uint8_t channel, uint16_t value)
{
	if(channel < 18)
		sbus_values[channel]=value;
}
