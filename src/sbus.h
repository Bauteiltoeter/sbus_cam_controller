#ifndef __SBUS_H
#define __SBUS_H

#include <stdint.h>

void sbus_init(void);
void sbus_run(void);
void sbus_setvalue(uint8_t channel, uint16_t value);

#endif
