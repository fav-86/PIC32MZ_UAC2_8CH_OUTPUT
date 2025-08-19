
#include "../../app/system.h"
#include "uart.h"



/*
 * uart_init() - 
 */
void uart_init (const uint32_t datarate)
{
    const uint32_t baudrate = (((sysFreqHz / 2) / datarate) / 16) - 1;
            
    U1BRG = baudrate;
    U1STA = 0;
    U1MODEbits.ON = 1;
    U1STAbits.UTXEN = 1;
}









