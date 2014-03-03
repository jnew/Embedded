#include "maindefs.h"
#ifndef __XC8
#include <usart.h>
#else
#include <plib/usart.h>
#endif
#include "my_uart.h"

static uart_comm *uc_ptr;

void uart_recv_int_handler() {
#ifdef __USE18F26J50
    if (DataRdy1USART()) {
        uc_ptr->buffer[uc_ptr->buflen] = Read1USART();
#else
#ifdef __USE18F46J50
    if (DataRdy1USART()) {
        uc_ptr->buffer[uc_ptr->buflen] = Read1USART();
#else
    if (DataRdyUSART()) {
        uc_ptr->buffer[uc_ptr->buflen] = ReadUSART();
#endif
#endif

        uc_ptr->buflen++;
        // check if a message should be sent
        if (uc_ptr->buflen == MAXUARTBUF) {
            ToMainLow_sendmsg(uc_ptr->buflen, MSGT_UART_DATA, (void *) uc_ptr->buffer);
            uc_ptr->buflen = 0;
        }
    }
#ifdef __USE18F26J50
    if (USART1_Status.OVERRUN_ERROR == 1) {
#else
#ifdef __USE18F46J50
    if (USART1_Status.OVERRUN_ERROR == 1) {
#else
    if (USART_Status.OVERRUN_ERROR == 1) {
#endif
#endif
        // we've overrun the USART and must reset
        // send an error message for this
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
        ToMainLow_sendmsg(0, MSGT_OVERRUN, (void *) 0);
    }
}

void init_uart_recv(uart_comm *uc) {
    //INTCONbits.GIE = 1;
    //INTCONbits.PEIE = 1;
    uc_ptr = uc;
    uc_ptr->buflen = 0;
}

void uart_trans(unsigned char length, unsigned char *data){
    // load up the buffer with the data
    for (uc_ptr->txBuflen = 0; uc_ptr->txBuflen < length; uc_ptr->txBuflen++) {
        uc_ptr->txBuff[uc_ptr->txBuflen] = data[uc_ptr->txBuflen];
    }
    uc_ptr->txBufind = 0;
    PIE1bits.TX1IE = 1;
}


void uart_trans_int_handler(){

    if(TXSTAbits.TRMT){
        if(uc_ptr->txBufind < uc_ptr->txBuflen){
           TXREG = uc_ptr->txBuff[uc_ptr->txBufind];
           uc_ptr->txBufind++;
        } else
            PIE1bits.TX1IE = 0; // reset because we are done
    }
}