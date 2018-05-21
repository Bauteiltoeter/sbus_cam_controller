#ifndef __BMMCC_H
#define __BMMCC_H

#include <stdint.h>

typedef enum 
{
	IRIS_f3_5 = 400,
	IRIS_f3_7 = 450,
	IRIS_f4   = 500,
	IRIS_f4_5 = 550,
	IRIS_f4_8 = 600,
	IRIS_f5_2 = 700,
	IRIS_f5_6 = 750,
	IRIS_f6_2 = 800,
	IRIS_f6_7 = 900,
	IRIS_f7_3 = 950,
	IRIS_f8   =1000,
	IRIS_f8_7 =1050,
	IRIS_f9_5 =1100,
	IRIS_f10  =1200,
	IRIS_f11  =1250,
    IRIS_f12  =1300,
	IRIS_f14  =1350,
	IRIS_f15  =1400,
	IRIS_f16  =1500,
	IRIS_f17  =1550,
	IRIS_f19  =1600,
	IRIS_f21  =1650,
	IRIS_f22  =1700
} iris_t;

typedef enum
{
	fps_50 = 1200,
	fps_59_94 = 1400,
	fps_60 = 1600
} framerate_t;

void bmmcc_init(void);
void bmmcc_run(void);
void bmmcc_setIris(iris_t iris);
void bmmcc_setFocus(uint16_t focus);
void bmmcc_setAudiolevel(uint16_t level);
void bmmcc_setFramerate(framerate_t framerate);
void bmmcc_ISO(int8_t updown);
void bmmcc_WB(int8_t updown);
void bmmcc_SA(int8_t updown);
void bmmcc_zoom(int8_t farnear);
#endif
