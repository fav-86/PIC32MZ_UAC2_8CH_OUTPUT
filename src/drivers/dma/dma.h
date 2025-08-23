#ifndef _DMA_H_    /* Guard against multiple inclusion */
#define _DMA_H_


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

    
/******************* Output transfer defines ********************************/
#define _DMA_OutputSourceAddress_Set(adr)            {  DCH4SSA = adr; DCH5DSA = adr;}
    
#define DMA_OUTPUT_TRANSFET_PTR                         DCH4SPTR
    



// DMA initialization
void dma_init (void);

// DMA control
void dma_output_2ch32_start (const uint16_t size);
void dma_output_2ch16_start (const uint16_t size);
void dma_output_8ch32_start (const uint16_t size);
void dma_output_8ch16_start (const uint16_t size);
void dma_output_stop (void);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DMA_H_ */


