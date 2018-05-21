#include "bmmcc.h"
#include "sbus.h"

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

static int8_t sa_request;
static int8_t wb_request;
static int8_t iso_request;

static void handle_sa(void);
static void handle_wb(void);
static void handle_iso(void);


void bmmcc_init(void)
{
	sbus_init();
	sbus_setvalue(SHUTTER,1024);
	sbus_setvalue(WHITEBALANCE,1024);
	sbus_setvalue(ISO,1024);
	sbus_setvalue(ZOOM, 992);
}

void bmmcc_run(void)
{
	handle_sa();
	handle_wb();
	handle_iso();
	sbus_run();	
}

void bmmcc_setIris(iris_t iris)
{
	sbus_setvalue(IRIS, iris);
}


void bmmcc_setFramerate(framerate_t framerate)
{
	sbus_setvalue(FRAMERATE, framerate);
}

void bmmcc_setFocus(uint16_t focus)
{
	sbus_setvalue(FOCUS, focus);
}


void bmmcc_setAudiolevel(uint16_t level)
{
	sbus_setvalue(AUDIOLEVEL, level);
}	

void bmmcc_ISO(int8_t updown)
{
	iso_request+=updown;
}

void bmmcc_WB(int8_t updown)
{
	wb_request+=updown;
}

void bmmcc_SA(int8_t updown)
{
	sa_request+=updown;
}

void handle_sa(void)
{
	static uint8_t state=0;
	
	if(state==0)
	{
		if(sa_request>0)
		{
			state=1;
			sa_request--;
			sbus_setvalue(SHUTTER, 1800);
		}
		else if(sa_request<0)
		{
			state=1;
			sa_request++;
			sbus_setvalue(SHUTTER,200);
		}
	}
	else if(state==1)
	{
		state=0;
		sbus_setvalue(SHUTTER,1024);
	}
}

void handle_wb(void)
{
	static uint8_t state=0;
	
	if(state==0)
	{
		if(wb_request>0)
		{
			state=1;
			wb_request--;
			sbus_setvalue(WHITEBALANCE, 1800);
		}
		else if(wb_request<0)
		{
			state=1;
			wb_request++;
			sbus_setvalue(WHITEBALANCE,200);
		}
	}
	else if(state==1)
	{
		state=0;
		sbus_setvalue(WHITEBALANCE,1024);
	}
}

void handle_iso(void)
{
	static uint8_t state=0;
	
	if(state==0)
	{
		if(iso_request>0)
		{
			state=1;
			iso_request--;
			sbus_setvalue(ISO, 1800);
		}
		else if(iso_request<0)
		{
			state=1;
			iso_request++;
			sbus_setvalue(ISO,200);
		}
	}
	else if(state==1)
	{
		state=0;
		sbus_setvalue(ISO,1024);
	}
}


void bmmcc_zoom(int8_t farnear)
{
sbus_setvalue(ZOOM, 500);

	if(farnear==1)
	{
		
	}
}

