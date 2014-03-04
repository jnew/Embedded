#ifndef __my_uart_h
#define __my_uart_h

#include "messages.h"

#define MAXUARTBUF 5
#if (MAXUARTBUF > MSGLEN)
#define MAXUARTBUF MSGLEN
#endif
typedef struct __uart_comm {
    unsigned char buffer[MAXUARTBUF];
    unsigned char buflen;
    unsigned char txBuff[MAXUARTBUF];
    unsigned char txBuflen;
    unsigned char txBufind;
} uart_comm;

void init_uart_recv(uart_comm *);
void uart_recv_int_handler(void);

void uart_trans(unsigned char, unsigned char *);
void uart_trans_int_handler();

#endif
