
#include "system.h"


#define ADDR_SFREQ              1
#define ADDR_DMODE              2
#define ADDR_VOLUME             3



/*
 * app_Sampling_Freq_set() - Transmitt sampling freq
 */
void app_Sampling_Freq_set( const eUSB_SAMPLING_FREQ sfreq )
{ 
    if (sfreq & 0x1)
        OSCSEL_SET_LOW();  // Set 48kHz clock domain
    else
        OSCSEL_SET_HIGH(); // Set 44.1kHz clock domain
    
    uint8_t mssg[2];    
    mssg[0] = ADDR_SFREQ;
    mssg[1] = sfreq;
    
    // add data to uart fifo
    uart_tx_fifo_add( mssg, 2 );
}

/*
 * app_DataMode_set() - Transmitt Data width in bits
 */
void app_DataMode_set( const eDATA_MODE dmode )
{
    uint8_t mssg[2];    
    mssg[0] = ADDR_DMODE;
    mssg[1] = dmode;
    
    // add data to uart fifo
    uart_tx_fifo_add( mssg, 2 );
}

/*
 * app_Volume_set() - Transmitt System volume & mute from 0 to 100
 */
void app_Volume_set( const uint8_t volume )
{
    uint8_t mssg[2];    
    mssg[0] = ADDR_VOLUME;
    mssg[1] = volume;
    
    // add data to uart fifo
    uart_tx_fifo_add( mssg, 2 );
}

/*
 * app_init() - 
 */
void app_init( void )
{
    app_DataMode_set( MODE_2CH_32bit );
    app_Sampling_Freq_set( USB_SFREQ_48k );
    app_Volume_set( 100 );
}
