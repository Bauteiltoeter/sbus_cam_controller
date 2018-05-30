#include <avr/io.h>
#include "uart.h"
#include <util/delay.h>
#include "avr/interrupt.h"
#include "bmmcc.h"

void process_cccb(void);

int main(void)
{
	DDRA|= (1<<0);
	PORTA&=~(1<<0);

	DDRD|= (1<<7);
	PORTD|=(1<<7);



	bmmcc_init();
    uart_init(UART_BAUD_SELECT(9600,F_CPU) );
	sei();

	DDRB |= (1<<0);

	uint16_t counter=0;

    bmmcc_setFramerate(fps_50);

	while(1)
	{	
		process_cccb();



		counter++;

		if(counter >100)
		{
			counter=0;
			
		}		
		
		bmmcc_run();

		//muss noch weg, alles mit ordentlich und so
		_delay_ms(14);
	}
}

void cccb_decode(uint8_t c);
void process_cccb(void)
{
	unsigned int c;

do
{
	c=uart_getc();

        if ( c & UART_NO_DATA )
        {
            /* 
             * no data available from UART 
             */
        }
        else
        {
            /*
             * new data available from UART
             * check for Frame or Overrun error
             */
            if ( c & UART_FRAME_ERROR )
            {
                /* Framing Error detected, i.e no stop bit detected */
                uart_puts_P("UART Frame Error: ");
            }
            if ( c & UART_OVERRUN_ERROR )
            {
                /* 
                 * Overrun, a character already present in the UART UDR register was 
                 * not read by the interrupt handler before the next character arrived,
                 * one or more received characters have been dropped
                 */
                uart_puts_P("UART Overrun Error: ");
            }
            if ( c & UART_BUFFER_OVERFLOW )
            {
                /* 
                 * We are not reading the receive buffer fast enough,
                 * one or more received character have been dropped 
                 */
                uart_puts_P("Buffer overflow error: ");
            }
            /* 
             * send received character back
             */
			cccb_decode((unsigned char)c);
           
        }
} while(!(c & UART_NO_DATA));
	     
}

typedef enum 
{
	WAITING_START,
	WAIT_FOCUS_HIGH,
	WAIT_FOCUS_LOW,
	WAIT_IRIS,
	WAIT_WB,
	WAIT_SA,
	WAIT_ISO,
	WAIT_ZOOM,

} cccb_state_t;


void cccb_decode(uint8_t c)
{
	static cccb_state_t state = WAITING_START;
	static uint16_t focus;
	static uint8_t iris;
	static int8_t wb;
	static int8_t sa;
	static int8_t iso;
	static int8_t zoom;

	switch(state)
	{
		case WAITING_START: 
			if(c==0xAA)
			{
				state=WAIT_FOCUS_HIGH;

			}
			//else
				//PORTD^=(1<<7);

		break;
		case WAIT_FOCUS_HIGH: 
			focus=(uint16_t)c<<8;
			state=WAIT_FOCUS_LOW;
		break;
		case WAIT_FOCUS_LOW:
			focus|=c;
			state=WAIT_IRIS;
		break;
		case WAIT_IRIS:
			iris=c;
			state=WAIT_WB;
			break;
		case WAIT_WB:
			wb=c;
			state=WAIT_SA;
			break;
		case WAIT_SA:
			sa=c;
			state=WAIT_ISO;
			break;
		case WAIT_ISO:
			iso=c;
			state=WAIT_ZOOM;
			break;

		case WAIT_ZOOM:
			zoom=*((int8_t*)&c);
			state=WAITING_START;


			apply_values(focus, iris,wb,sa,iso,zoom);
		break;
			
	}
	

}

void apply_values(uint16_t focus, uint8_t iris,int8_t wb,int8_t sa,int8_t iso,int8_t zoom)
{
	switch(iris)
        {
        case 0: bmmcc_setIris(IRIS_f3_5); break;
        case 1: bmmcc_setIris(IRIS_f3_7); break;
        case 2: bmmcc_setIris(IRIS_f4); break;
        case 3: bmmcc_setIris(IRIS_f4_5); break;
        case 4: bmmcc_setIris(IRIS_f4_8); break;
        case 5: bmmcc_setIris(IRIS_f5_2); break;
        case 6: bmmcc_setIris(IRIS_f5_6); break;
        case 7: bmmcc_setIris(IRIS_f6_2); break;
        case 8: bmmcc_setIris(IRIS_f6_7); break;
        case 9: bmmcc_setIris(IRIS_f7_3); break;
        case 10: bmmcc_setIris(IRIS_f8); break;
        case 11: bmmcc_setIris(IRIS_f8_7); break;
        case 12: bmmcc_setIris(IRIS_f9_5); break;
        case 13: bmmcc_setIris(IRIS_f10); break;
        case 14: bmmcc_setIris(IRIS_f11); break;
        case 15: bmmcc_setIris(IRIS_f12); break;
        case 16: bmmcc_setIris(IRIS_f14); break;
        case 17: bmmcc_setIris(IRIS_f15); break;
        case 18: bmmcc_setIris(IRIS_f16); break;
        case 19: bmmcc_setIris(IRIS_f17); break;
        case 20: bmmcc_setIris(IRIS_f19); break;
        case 21: bmmcc_setIris(IRIS_f21); break;
        case 22: bmmcc_setIris(IRIS_f22); break;
	};

	bmmcc_setFocus(focus);
	bmmcc_ISO(iso);
	bmmcc_WB(wb);
	bmmcc_SA(sa);
	bmmcc_setZoom(zoom);
	




}

