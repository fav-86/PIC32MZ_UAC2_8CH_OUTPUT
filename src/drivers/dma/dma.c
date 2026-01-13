
#include "../../app/system.h"
#include "dma.h"


#define SPI_TX_VECTOR(SPIPTR)  (    (SPIPTR == &SPI1BUF) ? _SPI1_TX_VECTOR :\
                                    (SPIPTR == &SPI2BUF) ? _SPI2_TX_VECTOR :\
                                    (SPIPTR == &SPI3BUF) ? _SPI3_TX_VECTOR : _SPI4_TX_VECTOR )


// One sample 8-ch DMA buffer to channels separation
static uint32_t dmabuf[8] __attribute__((coherent));
// data source to fifo cleare
static uint32_t dwclr __attribute__((coherent));
// Buffer data pointer
static void *pBuf;
/*
 * dma_init()
 */
void dma_init (void)
{    
    DMACONbits.ON = 1;                          // Enable DMA controller
    // Set pointer to data buffer
    pBuf = dmabuf;

    /**************************************************************************/
    /* Channel 0 config - to copy data from dmabuf buffer to I2S12 module     */
    /**************************************************************************/
    DCH0SSA = KVA_TO_PA( pBuf );                // Source data start address
    DCH0DSA = KVA_TO_PA( &I2SBUF_CH12 );        // Destination address (I2S FIFO buffer)
    DCH0CONbits.CHAEN = 1;                      // Channel is continuously enabled, and not automatically disabled after a block transfer is complete
    DCH0CONbits.CHPRI = 2;                      // Set channel priority higher than ch0
    // Only separate fields support!!!!
    DCH0ECONbits.CHSIRQ = SPI_TX_VECTOR(&I2SBUF_CH12); // Channel Transfer Start IRQ
    DCH0ECONbits.SIRQEN = 1;                    // Enable transfer IRQ
    
    /**************************************************************************/
    /* Channel 1 config - to copy data from dmabuf buffer to I2S34 module     */
    /**************************************************************************/
    DCH1DSA = KVA_TO_PA( &I2SBUF_CH34 );        // Destination address (I2S FIFO buffer)
    DCH1CONbits.CHAEN = 1;                      // Channel is continuously enabled, and not automatically disabled after a block transfer is complete
    DCH1CONbits.CHPRI = 2;                      // Set channel priority higher than ch0
    // Only separate fields support!!!!
    DCH1ECONbits.CHSIRQ = SPI_TX_VECTOR(&I2SBUF_CH34); // Channel Transfer Start IRQ
    DCH1ECONbits.SIRQEN = 1;                    // Enable transfer IRQ

    /**************************************************************************/
    /* Channel 2 config - to copy data from dmabuf buffer to I2S56 module     */
    /**************************************************************************/
    DCH2DSA = KVA_TO_PA( &I2SBUF_CH56 );        // Destination address (I2S FIFO buffer)
    DCH2CONbits.CHAEN = 1;                      // Channel is continuously enabled, and not automatically disabled after a block transfer is complete
    DCH2CONbits.CHPRI = 2;                      // Set channel priority higher than ch0
    // Only separate fields support!!!!
    DCH2ECONbits.CHSIRQ = SPI_TX_VECTOR(&I2SBUF_CH56); // Channel Transfer Start IRQ
    DCH2ECONbits.SIRQEN = 1;                    // Enable transfer IRQ
    
    /**************************************************************************/
    /* Channel 3 config - to copy data from dmabuf buffer to I2S78 module     */
    /**************************************************************************/
    DCH3DSA = KVA_TO_PA( &I2SBUF_CH78 );        // Destination address (I2S FIFO buffer)
    DCH3CONbits.CHAEN = 1;                      // Channel is continuously enabled, and not automatically disabled after a block transfer is complete
    DCH3CONbits.CHPRI = 2;                      // Set channel priority higher than ch0
    // Only separate fields support!!!!
    DCH3ECONbits.CHSIRQ = SPI_TX_VECTOR(&I2SBUF_CH78); // Channel Transfer Start IRQ
    DCH3ECONbits.SIRQEN = 1;                    // Enable transfer IRQ
    
    /**************************************************************************/
    /* Channel 4 config - to copy data from EP1 FIFO to dmabuf                */
    /**************************************************************************/
    DCH4DSA = KVA_TO_PA( pBuf );                // Destination address
    DCH4CONbits.CHAEN = 1;                      // Channel is continuously enabled, and not automatically disabled after a block transfer is complete
    DCH4CONbits.CHPRI = 1;                      // Set channel priority higher than ch0
    // Only separate fields support!!!!
    DCH4ECONbits.CHSIRQ = SPI_TX_VECTOR(&I2SBUF_CH12); // Channel Transfer Start IRQ
    DCH4ECONbits.SIRQEN = 1;                    // Enable transfer IRQ
    
    /**************************************************************************/
    /* Channel 5 config - to cleare fifo buf                                  */
    /**************************************************************************/
    dwclr = 0;
    DCH5SSA = KVA_TO_PA( &dwclr );              // Source data start address
    DCH5SSIZ = 4;                               // Source size
    DCH5CONbits.CHAEN = 1;                      // Channel is continuously enabled, and not automatically disabled after a block transfer is complete
    // Only separate fields support!!!!
    DCH5ECONbits.CHSIRQ = SPI_TX_VECTOR(&I2SBUF_CH12);  // Channel Transfer Start IRQ
    DCH5ECONbits.SIRQEN = 1;                    // Enable transfer IRQ
}

/*
 * dma_output_2ch32_start()
 */
void dma_output_2ch32_start (const uint16_t size)
{
    // Config channel to stereo output
    DCH0DSIZ = 4;                           // Destination size    
    DCH0SSIZ = 8;                           // Source size
    DCH0CSIZ = 8;                           // Cell data size
    
    // Config buffer transfer
    DCH4SSIZ = size;                        // Source size    
    DCH4DSIZ = 8;                           // Destination size
    DCH4CSIZ = 8;                           // Cell data size
        
    // Config fifo cleare
    DCH5DSIZ = size;                        // Destination size
    DCH5CSIZ = 8;                           // Cell data size
    
    // Enable DMA channel
    DCH0CONbits.CHEN = 1;
    DCH4CONbits.CHEN = 1;
    DCH5CONbits.CHEN = 1;
}

/*
 * dma_output_2ch16_start()
 */
void dma_output_2ch16_start (const uint16_t size)
{
    // Channel 12 config
    DCH0DSIZ = 2;                           // Destination size    
    DCH0SSIZ = 4;                           // Source size
    DCH0CSIZ = 4;                           // Cell data size
    
    // Config buffer transfer to stereo output
    DCH4SSIZ = size;                        // Source size    
    DCH4DSIZ = 4;                           // Destination size
    DCH4CSIZ = 4;                           // Cell data size
        
    // Config fifo cleare
    DCH5DSIZ = size;                        // Destination size
    DCH5CSIZ = 4;                           // Cell data size

    // Enable DMA channel
    DCH0CONbits.CHEN = 1;
    DCH4CONbits.CHEN = 1;
    DCH5CONbits.CHEN = 1;
}

/*
 * dma_output_8ch32_start()
 */
void dma_output_8ch32_start (const uint16_t size)
{
    // Channel 12 config
    DCH0DSIZ = 4;                           // Destination size
    DCH0SSIZ = 8;                           // Source size
    DCH0CSIZ = 8;                           // Cell data size
    
    // Channel 34 config
    DCH1DSIZ = 4;                           // Destination size
    DCH1SSIZ = 8;                           // Source size
    DCH1CSIZ = 8;                           // Cell data size
    DCH1SSA = KVA_TO_PA( pBuf+8 );          // Source data start address
    
    // Channel 56 config
    DCH2DSIZ = 4;                           // Destination size
    DCH2SSIZ = 8;                           // Source size
    DCH2CSIZ = 8;                           // Cell data size
    DCH2SSA = KVA_TO_PA( pBuf+16 );         // Source data start address
    
    // Channel 78 config
    DCH3DSIZ = 4;                           // Destination size
    DCH3SSIZ = 8;                           // Source size
    DCH3CSIZ = 8;                           // Cell data size
    DCH3SSA = KVA_TO_PA( pBuf+24 );         // Source data start address
    
    // Config buffer transfer
    DCH4SSIZ = size;                        // Source size
    DCH4DSIZ = 32;                          // Destination size
    DCH4CSIZ = 32;                          // Cell data size
    
    // Config fifo cleare
    DCH5DSIZ = size;                        // Destination size
    DCH5CSIZ = 32;                          // Cell data size
    
    // Enable DMA chanels
    DCH0CONbits.CHEN = 1;
    DCH1CONbits.CHEN = 1;
    DCH2CONbits.CHEN = 1;
    DCH3CONbits.CHEN = 1;
    DCH4CONbits.CHEN = 1;
    DCH5CONbits.CHEN = 1;
}

/*
 * dma_output_8ch16_start()
 */
void dma_output_8ch16_start (const uint16_t size)
{
    // Channel 12 config
    DCH0DSIZ = 2;                           // Destination size
    DCH0SSIZ = 4;                           // Source size
    DCH0CSIZ = 4;                           // Cell data size
    
    // Channel 34 config
    DCH1DSIZ = 2;                           // Destination size
    DCH1SSIZ = 4;                           // Source size
    DCH1CSIZ = 4;                           // Cell data size
    DCH1SSA = KVA_TO_PA( pBuf+4 );          // Source data start address
    
    // Channel 56 config
    DCH2DSIZ = 2;                           // Destination size
    DCH2SSIZ = 4;                           // Source size
    DCH2CSIZ = 4;                           // Cell data size
    DCH2SSA = KVA_TO_PA( pBuf+8 );          // Source data start address
    
    // Channel 78 config
    DCH3DSIZ = 2;                           // Destination size
    DCH3SSIZ = 4;                           // Source size
    DCH3CSIZ = 4;                           // Cell data size
    DCH3SSA = KVA_TO_PA( pBuf+12 );         // Source data start address
    
    // Config buffer transfer
    DCH4SSIZ = size;                        // Source size
    DCH4DSIZ = 16;                          // Destination size
    DCH4CSIZ = 16;                          // Cell data size
    
    // Config fifo cleare
    DCH5DSIZ = size;                        // Destination size
    DCH5CSIZ = 16;                          // Cell data size
    
    // Enable DMA chanels
    DCH0CONbits.CHEN = 1;
    DCH1CONbits.CHEN = 1;
    DCH2CONbits.CHEN = 1;
    DCH3CONbits.CHEN = 1;
    DCH4CONbits.CHEN = 1;
    DCH5CONbits.CHEN = 1;
}

/*
 * dma_output_stop()
 */
void dma_output_stop (void)
{
    if (DCH0CONbits.CHEN)
        DCH0ECONbits.CABORT = 1;

    if (DCH1CONbits.CHEN)
        DCH1ECONbits.CABORT = 1;

    if (DCH2CONbits.CHEN)
        DCH2ECONbits.CABORT = 1;

    if (DCH3CONbits.CHEN)
        DCH3ECONbits.CABORT = 1;
    
    if (DCH4CONbits.CHEN)
        DCH4ECONbits.CABORT = 1;
    
    if (DCH5CONbits.CHEN)
        DCH5ECONbits.CABORT = 1;

    while (DCH0CONbits.CHBUSY);
    while (DCH1CONbits.CHBUSY);
    while (DCH2CONbits.CHBUSY);
    while (DCH3CONbits.CHBUSY);
    while (DCH4CONbits.CHBUSY);
    while (DCH5CONbits.CHBUSY);
    
    // cleare data buffer
    dmabuf[0] = 0;
    dmabuf[1] = 0;
    dmabuf[2] = 0;
    dmabuf[3] = 0;
    dmabuf[4] = 0;
    dmabuf[5] = 0;
    dmabuf[6] = 0;
    dmabuf[7] = 0;
}



