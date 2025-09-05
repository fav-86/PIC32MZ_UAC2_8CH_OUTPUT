
#include "../../app/system.h"
#include "uart.h"

static uint8_t uart_tx_fifo[256] = {0};   // fifo array
static uint8_t fifoPtrRd = 0;   // fifo read pointer
static uint8_t fifoPtrWr = 0;   // fifo write pointer

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

/*
 * uart_tx_fifo_add() - load "size" bytes from "ptr" pointer to uart FIFO
 */
void uart_tx_fifo_add (const void *ptr, uint8_t size)
{
    const uint8_t *p = ptr;
    
    while (size--)
        uart_tx_fifo[fifoPtrWr++] = *p++;
    
    _System_Task_Set( SYS_TASK_UART_FIFO_ADD );
}


/*
 * uart_tasks() - 
 */
void uart_tasks (void)
{   
    // while uart FIFO is not empty
    while (fifoPtrWr != fifoPtrRd)
    {
        // if uart1 tx fifo buffer is full
        if (U1STAbits.UTXBF)
            break; // break load data
        
        // transmitt byte to uart1
        U1TXREG = uart_tx_fifo[fifoPtrRd++];
        
        // if uart FIFO is empty
        if (fifoPtrWr == fifoPtrRd)
            _System_Task_Clr( SYS_TASK_UART_FIFO_ADD ); // cleare system task
    }
}


