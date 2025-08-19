#ifndef _I2S_H_    /* Guard against multiple inclusion */
#define _I2S_H_


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


    
#define     _I2S_Mode32_set()                   {   SPI1CONbits.MODE32 = 1; SPI1CONbits.MODE16 = 0;\
                                                    SPI2CONbits.MODE32 = 1; SPI2CONbits.MODE16 = 0;\
                                                    SPI3CONbits.MODE32 = 1; SPI3CONbits.MODE16 = 0;\
                                                    SPI4CONbits.MODE32 = 1; SPI4CONbits.MODE16 = 0; }
    
#define     _I2S_Mode16_set()                   {   SPI1CONbits.MODE16 = 1; SPI1CONbits.MODE32 = 0;\
                                                    SPI2CONbits.MODE16 = 1; SPI2CONbits.MODE32 = 0;\
                                                    SPI3CONbits.MODE16 = 1; SPI3CONbits.MODE32 = 0;\
                                                    SPI4CONbits.MODE16 = 1; SPI4CONbits.MODE32 = 0; }
    

void i2s_init (void);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _I2S_H_ */


