#ifndef __user_interrupts
#define __user_interrupts

// interrupts defined by the "user" and that are called from
// interrupts.c -- the "user" needs to insert these into
// interrupts.c because it, of course, doesn't know which
// interrupt handlers you would like to call

//My example program uses these two timer interrupts
void timer0_int_handler();

void timer1_int_handler();

void adc_int_handler();

// include the handler from my uart code
#include "my_uart.h"

// include the i2c interrupt handler definitions
#include "my_i2c.h"

unsigned char adcbuffer[28];
#endif
