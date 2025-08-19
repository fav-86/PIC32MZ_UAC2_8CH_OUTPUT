#ifndef _UART_H_    /* Guard against multiple inclusion */
#define _UART_H_


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
    
#define     _UartByteTransmitt(d)   U1TXREG = d

    
    
void uart_init (const uint32_t datarate);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _UART_H_ */


