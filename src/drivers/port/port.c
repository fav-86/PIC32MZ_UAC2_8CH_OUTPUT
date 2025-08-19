
#include "../../app/system.h"
#include "port.h"



/*
 port_init() - mcu port power up initialisation
 */
void port_init (void)
{ 
    OSCSEL_SET_LOW();                      // set oscsel to 48k domain
    
    /*Configure ports direction. 1 - input, 0 - output*/
    TRISDCLR = _BIT(1) | _BIT(3) | _BIT(4)  // I2S output pons
            | _BIT(5)                       // oscsel port
            ;
    TRISBCLR = 0
            | _BIT(3)                       // Uart1 TX output
            | _BIT(5) | _BIT(8)             // FS[1:0] outputs to control ADC sempling frequency
            | _BIT(9) | _BIT(14) | _BIT(15) // I2S3 DSD output
            ;    
    TRISECLR = 0
            | _BIT(5)                       // REFCLKO1
            | _BIT(3)                       // SSO4
            ;
    
    ANSELECLR = _BIT(3) | _BIT(5);
    ANSELGCLR = _BIT(6) | _BIT(7) | _BIT(9);// Switch Off Analog Function for I2S inputs
            
    /*Configure ports Pull Up. 1 - pull enable*/
    CNPUFSET = _BIT(3); // USBID input Pull-Up
           
    /*Configure ports Pull Down. 1 - pull enable*/
    CNPDBSET = _BIT(2) | _BIT(3) | _BIT(4) | _BIT(6) | _BIT(7) | _BIT(10) | _BIT(11) | _BIT(12) | _BIT(13) | _BIT(15);
    CNPDCSET = _BIT(13);
    CNPDDSET = _BIT(0) | _BIT(2) | _BIT(9) | _BIT(10) | _BIT(11);
    CNPDESET = _BIT(0) | _BIT(1) | _BIT(2) | _BIT(4) | _BIT(6) | _BIT(7);
    CNPDFSET = _BIT(0) | _BIT(1) | _BIT(4) | _BIT(5);
    CNPDGSET = _BIT(8);
    
    /************ Remappable pins *******************/    
    REFCLKI1Rbits.REFCLKI1R = 0x07; // RPC14  REFCLKI1 input
    RPE5R = 0xf;    // 1111 = REFCLKO1
    
    // I2S1 remappable outputs
    RPD3R = 0x5;    // 0101 = SDO1
    RPD4R = 0x5;    // 0101 = SS1out
    
    // I2S2 remappable inputs
    SDI2R = 0x1;    // 0001 = RPG7 - SDI2
    SS2R = 0x1;     // 0001 = RPG9 - SS2in
    
    // I2S3 remappable outputs
    RPB9R = 0x7;    // 0111 = SDO3
    RPB15R = 0x7;   // 0111 = SS3
    
    // I2S4 remappable outputs
    RPE3R = 0x8;    // 1000 = SS4    
    
    // UART1 remappable output
    RPB3R = 0x1;    // 0001 = U1TX
}


