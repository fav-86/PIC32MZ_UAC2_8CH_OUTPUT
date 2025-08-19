/* 
 * File:   main.c
 * Author: Dortonyan (Aliaksei Fisko)
 *
 */

#include "system.h"


/*
 * 
 */
void main (void) 
{    
    sysFreqHz = sysclk_value_get(PRIMARY_CRYSTAL_FREQUENCY_Hz, SECONDARY_CRYSTAL_FREQUENCY_Hz);
    sys_init(sysFreqHz);    
    usb_PL_init();
    port_init();
    dma_init();
    i2s_init();
    uart_init( 9600 );
    
#ifdef PIC32MZxxxxEC
    /*
        When enabling the USB PLL, add a three second (For MI32MZxxxEC only!)
        delay before turning on the USB module  */
    tmr_Task_Delayed_mS_set(SYS_TASK_USB_CONNECT, 3000);
#else
    _System_Task_Set( SYS_TASK_USB_CONNECT );
#endif
    
    // Enable Global Interrupts
    __builtin_enable_interrupts();
    
    // Main Loop
    while (true)
    {
        if (_System_Task_Get() == 0)   // If no more system tasks
        {
            GO_TO_IDLE();              // go to idle mode with clocks enabled
        }
        else
        {
            usb_PL_tasks();
        }
    }
}

