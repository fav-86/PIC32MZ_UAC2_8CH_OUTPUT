#ifndef _PORT_H_    /* Guard against multiple inclusion */
#define _PORT_H_


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    
#define _BIT(bit_num)                   ((uint32_t)(0x01 << (bit_num)))
    
#define OSCSEL_SET_HIGH()               LATDSET = _BIT(5)          // set oscsel to high
#define OSCSEL_SET_LOW()                LATDCLR = _BIT(5)          // set oscsel to low

    
    
    
void port_init (void);




    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _PORT_H_ */


