// This is where the "user" interrupts handlers should go
// The *must* be declared in "user_interrupts.h"

#include "maindefs.h"
#ifndef __XC8
#include <timers.h>
#else
#include <plib/timers.h>
#endif
#include "user_interrupts.h"
#include "messages.h"

// A function called by the interrupt handler
// This one does the action I wanted for this program on a timer0 interrupt

void timer0_int_handler() {
    WriteTimer0(0);
//    unsigned int val;
//    int length, msgtype;

    // toggle an LED
#ifdef __USE18F2680
    LATBbits.LATB0 = !LATBbits.LATB0;
#endif
    // reset the timer
    
    // try to receive a message and, if we get one, echo it back
//    length = FromMainHigh_recvmsg(sizeof(val), (unsigned char *)&msgtype, (void *) &val);
//    if (length == sizeof (val)) {
//        ToMainHigh_sendmsg(sizeof (val), MSGT_TIMER0, (void *) &val);
//    }

    uartTimeOut++;
    //ConvertADC();
    //while( BusyADC()) {
        //LATBbits.LATB1 = 1;
    //}
    //LATBbits.LATB1 = 0;

    
}

// A function called by the interrupt handler
// This one does the action I wanted for this program on a timer1 interrupt

void timer1_int_handler() {
    //unsigned int result;

    // read the timer and then send an empty message to main()
#ifdef __USE18F2680
    LATBbits.LATB1 = !LATBbits.LATB1;
#endif

    //result = ReadTimer1();
    //ToMainLow_sendmsg(0, MSGT_TIMER1, (void *) 0);

    // reset the timer
    WriteTimer1(0);
}

void adc_int_handler(){

    if(adcbuffer[0] < 27)                 // increment counter
        adcbuffer[0] = adcbuffer[0] + 1;
//    else {                               // shift out first value
//        for (int i = 1; i < 27; i++)
//        {
//            adcbuffer[i] = adcbuffer[i+1];
//        }
//    }
    adcbuffer[adcbuffer[0]] = ADRESH;    // put value in current count
}