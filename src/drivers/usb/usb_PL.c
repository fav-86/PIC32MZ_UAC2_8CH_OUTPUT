
#include "../../app/system.h"
#include "usb_Descriptors.h"
#include "usb_PL.h"




/*****************************************************************************
 Data Types
 ****************************************************************************/
typedef struct{ // feedback freq values in 16.16 format
    uint32_t nom;   // nominal frequency value
    uint32_t lo;    // low limit frequency
    uint32_t hi;    // high limit frequency
}tFbSettFreq;

/*****************************************************************************
 Constatnt data
 ****************************************************************************/
// Output stream frequency set
static const tUSB_AUDIO_REQ_L3_PARAM_BLOCK tRangeFreqOutput __attribute__ ((aligned (4))) = {   
        (USB_SFREQ_768k+1),
        {
            {44100, 44100, 0}, {48000, 48000, 0},
            {88200, 88200, 0}, {96000, 96000, 0},
            {176400, 176400, 0}, {192000, 192000, 0}, {352800, 352800, 0},
            {384000, 384000, 0}, {705600, 705600, 0}, {768000, 768000, 0},
        }
    };

// Sampling Frequency List
static const uint32_t aFreqCtrl[] = {44100, 48000, 88200, 96000, 176400, 192000, 352800, 384000, 705600, 768000};

/* 
 * tFeedBackFreq - Frequences array to feedback with +/-400ppm limits 
 */
static const tFbSettFreq tFeedBackFreq[USB_FREQ_NUM] = { 
    {
     _FB_FREQ_VAL_GET(PULL_FREQ_NOM_44k, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_LOW_44k, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_HI_44k, EP1RX_PULL_TIME_mS)
 }, {
     _FB_FREQ_VAL_GET(PULL_FREQ_NOM_48k, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_LOW_48k, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_HI_48k, EP1RX_PULL_TIME_mS)
 }, {
     _FB_FREQ_VAL_GET(PULL_FREQ_NOM_44k * 2, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_LOW_44k * 2, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_HI_44k * 2, EP1RX_PULL_TIME_mS)
 }, {
     _FB_FREQ_VAL_GET(PULL_FREQ_NOM_48k * 2, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_LOW_48k * 2, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_HI_48k * 2, EP1RX_PULL_TIME_mS)
 }, {
     _FB_FREQ_VAL_GET(PULL_FREQ_NOM_44k * 4, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_LOW_44k * 4, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_HI_44k * 4, EP1RX_PULL_TIME_mS)
 }, {
     _FB_FREQ_VAL_GET(PULL_FREQ_NOM_48k * 4, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_LOW_48k * 4, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_HI_48k * 4, EP1RX_PULL_TIME_mS)
 }, {
     _FB_FREQ_VAL_GET(PULL_FREQ_NOM_44k * 8, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_LOW_44k * 8, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_HI_44k * 8, EP1RX_PULL_TIME_mS)
 }, {
     _FB_FREQ_VAL_GET(PULL_FREQ_NOM_48k * 8, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_LOW_48k * 8, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_HI_48k * 8, EP1RX_PULL_TIME_mS)
 }, {
     _FB_FREQ_VAL_GET(PULL_FREQ_NOM_44k * 16, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_LOW_44k * 16, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_HI_44k * 16, EP1RX_PULL_TIME_mS)
 }, {
     _FB_FREQ_VAL_GET(PULL_FREQ_NOM_48k * 16, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_LOW_48k * 16, EP1RX_PULL_TIME_mS),
     _FB_FREQ_VAL_GET(PULL_FREQ_HI_48k * 16, EP1RX_PULL_TIME_mS)
 } };

/* 
 * I2S clock dividers array to I2S sclk output frequency control
 */
#ifdef I2S_MCLK_512Fs
static const uint8_t i2sClkDiv[USB_FREQ_NUM] = {2, 2, 1, 1, 0, 0, 0, 0, 0, 0};
#endif

#ifdef I2S_MCLK_1024Fs
static const uint8_t i2sClkDiv[USB_FREQ_NUM] = {4, 4, 2, 2, 1, 1, 0, 0, 0, 0};
#endif


/*****************************************************************************
 Local variables
 ****************************************************************************/
static tUSB_CON_STAT tUsbControlStatus = {0};

// EP0 buffer and control variables
static uint8_t ep0buf[64] __attribute__((aligned (4)));
static uint8_t statusAnswer[] = {0x00, 0x00}; // Double Zero

// EP1_OUT buffer and control variables
static uint8_t ep1buf[OUTPUT_TRANSFER_FIFO_SIZE] __attribute__((coherent)) __attribute__((aligned (16)));
static tFbSettFreq tFreqLims;
static tFIFO_CONTROL tEp1Fifo;


/*****************************************************************************
 Global variables
 ****************************************************************************/


/*
    usb_PL_init()
 */
void usb_PL_init (void)
{  
    // EP-OUT data buffer initialisation
    tEp1Fifo.adr = KVA_TO_PA(ep1buf);
    // EP-FeedBack variables initialisation
    tFreqLims = tFeedBackFreq[USB_SFREQ_48k];
    
    tUsbControlStatus.streamSamplingFreq[eSTREAM_OUTPUT] = USB_SFREQ_48k;
    
    _CLK_I2S_Div_Set( i2sClkDiv[USB_SFREQ_48k] );    
    _DMA_OutputSourceAddress_Set(tEp1Fifo.adr);
    
    usb_LL_Init();
}

/*
    usb_PL_InterfaceState_Update()
 */
static inline void usb_PL_InterfaceState_Update ( USB_SETUP_PACKET *p )
{    
    tUsbControlStatus.streamInterfaceAltsetting[eSTREAM_OUTPUT] = p->bAltID;

    if (p->bAltID == USB_AUDIO_OUTPUT_ALTSET_OFF) {
        dma_output_stop();
    }
    else {
        // Calculate buffer length in dependence of sampling frequency
        tEp1Fifo.len = sizeof(ep1buf) >> ( (USB_SFREQ_768k - tUsbControlStatus.streamSamplingFreq[eSTREAM_OUTPUT]) >> 1 );
        
        switch (p->bAltID) {
            case USB_AUDIO_OUTPUT_ALTSET_2CH16_ON:
                tEp1Fifo.len >>= 1;
                dma_output_2ch16_start(tEp1Fifo.len);                
                break;
            
            case USB_AUDIO_OUTPUT_ALTSET_2CH24_ON:
            case USB_AUDIO_OUTPUT_ALTSET_2CH32_ON:
                dma_output_2ch32_start(tEp1Fifo.len);
                break;
                
            case USB_AUDIO_OUTPUT_ALTSET_8CH16_ON:
                tEp1Fifo.len >>= 1;
                dma_output_8ch16_start(tEp1Fifo.len);                
                break;
            
            case USB_AUDIO_OUTPUT_ALTSET_8CH24_ON:
            case USB_AUDIO_OUTPUT_ALTSET_8CH32_ON:
                dma_output_8ch32_start(tEp1Fifo.len);
                break;
        }
        
        tEp1Fifo.min = tEp1Fifo.len >> 4;
        tEp1Fifo.max = tEp1Fifo.len >> 3;
        tEp1Fifo.ptr = tEp1Fifo.len >> 1;
        tEp1Fifo.rem = 0;
            
        _EP1_FeedBack_Data_Send(tFreqLims.nom);
    }
}

/*
    usb_PL_SamplingFreq_Set()
 */
static inline void usb_PL_SamplingFreq_Set ( void )
{
    uint32_t freq;
    usb_LL_Ep0_BulkRead( &freq, sizeof(freq) );

    eUSB_SAMPLING_FREQ sfreq;

    switch (freq) {
        case 44100: sfreq = USB_SFREQ_44k; break;
        case 48000: sfreq = USB_SFREQ_48k; break;
        case 88200: sfreq = USB_SFREQ_88k; break;
        case 96000: sfreq = USB_SFREQ_96k; break;
        case 176400: sfreq = USB_SFREQ_176k; break;
        case 192000: sfreq = USB_SFREQ_192k; break;
        case 352800: sfreq = USB_SFREQ_352k; break;
        case 384000: sfreq = USB_SFREQ_384k; break;
        case 705600: sfreq = USB_SFREQ_705k; break;
        case 768000: sfreq = USB_SFREQ_768k; break;
        default: return;
    }

    uint8_t freq_chng = sfreq ^ tUsbControlStatus.streamSamplingFreq[eSTREAM_OUTPUT];
    tUsbControlStatus.streamSamplingFreq[eSTREAM_OUTPUT] = sfreq;

    if (freq_chng) {
        tFreqLims = tFeedBackFreq[sfreq];
          
        if (freq_chng & 0xE) {   // if frequency oversampling is chainged
            // Set clock divider for I2S output modules
            _CLK_I2S_OFF();
            _CLK_I2S_Div_Set( i2sClkDiv[sfreq] );
            _CLK_I2S_ON();
        }
        
        if (freq_chng & 0x1) {   // if frequency domain is chainged
            if (sfreq & 0x1) OSCSEL_SET_LOW();  // Set 48kHz clock domain
            else OSCSEL_SET_HIGH(); // Set 44.1kHz clock domain
        }
    }
    
    _UartByteTransmitt( sfreq+1 );   //Setting UART enum Freq
}

/*
    usb_PL_GetDescriptor()
 */
static inline int usb_PL_GetDescriptor ( USB_SETUP_PACKET *p, const void **dp )
{
    int len = 0;
    
    switch (p->bDescriptorType)
    {
        case USB_DESCRIPTOR_DEVICE:
            *dp = tUsbDescriptors.device.p;
            len = tUsbDescriptors.device.size;
            break;
            
        case USB_DESCRIPTOR_CONFIGURATION:
            *dp = tUsbDescriptors.configuration.p;
            len = tUsbDescriptors.configuration.size;
            break;
            
        case USB_DESCRIPTOR_STRING:
            if (p->bDscIndex < STRING_DESCRIPTORS_NUM) {
                *dp = tUsbDescriptors.string[p->bDscIndex].p;
                len = tUsbDescriptors.string[p->bDscIndex].size;
            }
            break;
            
        case USB_DESCRIPTOR_DEVICE_QUALIFIER:
            *dp = tUsbDescriptors.qualifier.p;
            len = tUsbDescriptors.qualifier.size;
            break;
    }

    return len;
}
 
//uint64_t DebugCmd[256] = {0};     // Debug array to logging control cmd
//int DebugOffset = 0;
/*
    usb_PL_ReqProcess()
 */
static inline void usb_PL_ReqProcess ( void *pbuf )
{
    USB_SETUP_PACKET *p = pbuf;
//    if (DebugOffset < (sizeof(DebugCmd)/8)) DebugCmd[DebugOffset++] = *(uint64_t*)pbuf;
    if (p->DataDir == USB_SETUP_REQUEST_DIRECTION_HOST_TO_DEVICE)
    {
        switch (p->bmbRequest)
        {
            /***************************************************/
            /************ Standart requests ********************/
            /***************************************************/
            case STDREQ_CLEARE_FEATURE_DEVICE:            
            case STDREQ_CLEARE_FEATURE_INTERFACE:            
            case STDREQ_CLEARE_FEATURE_ENDPOINT:
                USBE0CSR0bits.STALL = 1;
                break;

            case STDREQ_SET_CONFIGURATION:
                tUsbControlStatus.configuration = p->bConfigurationValue;
                break;

            case STDREQ_SET_FEATURE_DEVICE:
                tUsbControlStatus.setFeature[USB_SETUP_REQUEST_RECIPIENT_DEVICE] = p->bFeature;
                break;

            case STDREQ_SET_FEATURE_INTERFACE:
                tUsbControlStatus.setFeature[USB_SETUP_REQUEST_RECIPIENT_INTERFACE] = p->bFeature;
                break;

            case STDREQ_SET_FEATURE_ENDPOINT:
                tUsbControlStatus.setFeature[USB_SETUP_REQUEST_RECIPIENT_ENDPOINT] = p->bFeature;
                break;

            case STDREQ_SET_INTERFACE:
                usb_PL_InterfaceState_Update( p );
                break;

            /***************************************************/
            /********** Audio Device - specific requests *******/
            /***************************************************/
            case CSREQ_SET_CURR_INTERFACE:                
                switch (p->bIntfID_H)
                {
                    case AUDIO_SCLOCK_TERMINAL_OUTPUT:
                        switch (p->W_Value.byte.HB)
                        {
                            case USB_AUDIO_SAMPLING_FREQ_CONTROL: usb_PL_SamplingFreq_Set( ); break;
                            default: USBE0CSR0bits.STALL = 1; break;
                        }
                        break;

                    default: USBE0CSR0bits.STALL = 1; break;
                }
                break;
                
                
            default:
                USBE0CSR0bits.STALL = 1;
                break;
        }
    }
    else // p->DataDir == USB_SETUP_REQUEST_DIRECTION_DEVICE_TO_HOST
    {
        switch (p->bmbRequest)
        {
            /***************************************************/
            /************ Standart requests ********************/
            /***************************************************/
            case STDREQ_GET_CONFIGURATION:
                usb_LL_Ep0_BulkWrite( &tUsbControlStatus.configuration, sizeof(tUsbControlStatus.configuration) );
                break;

            case STDREQ_GET_DESCRIPTOR:
                {
                    const void *dp = NULL;
                    int len = usb_PL_GetDescriptor( p, &dp );
                    // If the descriptor is longer than the wLength field,
                    // only the initial bytes of the descriptor are returned
                    if (len > p->wLength)
                        len = p->wLength;
                   
                    if (len) usb_LL_Ep0_BulkWrite( dp, len );
                    else USBE0CSR0bits.STALL = 1;
                }
                break;

            case STDREQ_GET_INTERFACE:
                switch (p->bIntfID) {
                    case AUDIO_STREAMING_OUTPUT_INTERFACE_NUM: 
                        usb_LL_Ep0_BulkWrite( &tUsbControlStatus.streamInterfaceAltsetting[eSTREAM_OUTPUT], 
                                            sizeof(tUsbControlStatus.streamInterfaceAltsetting[eSTREAM_OUTPUT]) );
                        break;
                }
                break;

            case STDREQ_GET_STATUS_DEVICE:
            case STDREQ_GET_STATUS_INTERFACE:
            case STDREQ_GET_STATUS_ENDPOINT:
                usb_LL_Ep0_BulkWrite( statusAnswer, sizeof(statusAnswer) );
                break;

            /***************************************************/
            /********** Audio Device - specific requests *******/
            /***************************************************/
            case CSREQ_GET_RANGE_INTERFACE:
            {
                int len = 0;
                const void *ptRange = NULL;
                
                switch (p->bIntfID_H)
                {
                    case AUDIO_SCLOCK_TERMINAL_OUTPUT:                        
                        switch (p->W_Value.byte.HB)
                        {
                            case USB_AUDIO_SAMPLING_FREQ_CONTROL: ptRange = &tRangeFreqOutput; len = sizeof(tRangeFreqOutput); break;
                            default: USBE0CSR0bits.STALL = 1; break;
                        }                        
                        break;

                    default: USBE0CSR0bits.STALL = 1; break;
                }

                if (p->wLength < len)
                    len = p->wLength;

                usb_LL_Ep0_BulkWrite( ptRange, len );
            }
            break;
                
            case CSREQ_GET_CURR_INTERFACE:
            {
                int len = 0;
                const void *pCurr = NULL;
                
                switch (p->bIntfID_H)
                {
                    case AUDIO_SCLOCK_TERMINAL_OUTPUT:                        
                        switch (p->W_Value.byte.HB)
                        {
                            case USB_AUDIO_SAMPLING_FREQ_CONTROL: pCurr = &aFreqCtrl[tUsbControlStatus.streamSamplingFreq[eSTREAM_OUTPUT]]; len = 4; break;
                            default: USBE0CSR0bits.STALL = 1; break;
                        }                        
                        break;

                    default: USBE0CSR0bits.STALL = 1; break;
                }

                if (p->wLength < len)
                    len = p->wLength;

                usb_LL_Ep0_BulkWrite( pCurr, len );
            }
            break;

            default:
                USBE0CSR0bits.STALL = 1;
                break;
        }
    }
}

/*
    usb_PL_tasks()
 */
void usb_PL_tasks (void)
{
    if (_System_Task_Check( SYS_TASK_USB_CONNECT )) {
         
        _USB_SOFT_CONNECT();        // The USB D+/D- lines are enabled and active  
        _System_Task_Clr( SYS_TASK_USB_CONNECT );
    }
    
    if (_System_Task_Check( SYS_TASK_USB_EP0_ISR )) {
   
        usb_PL_ReqProcess( ep0buf ); // Process request

        if (USBE0CSR0bits.SETEND)
            USBE0CSR0bits.SETENDC = 1;  
        
        _System_Task_Clr( SYS_TASK_USB_EP0_ISR ); 
    }
}

/* 
 * USB_Interrupt()
 */
void __ISR(_USB_VECTOR, ipl3SRS) USB_Interrupt(void)
{
    /* 
     * Read interrupt flags registers
     * Reading from USBCSRx registers directly can reset some interrupt flags!!!
     */
    uint32_t usbcsr0 = USBCSR0;
    uint32_t usbcsr1 = USBCSR1;
    uint32_t usbcsr2 = USBCSR2;

    if (usbcsr2 & _USBCSR2_RESETIF_MASK) {
        usb_LL_initReset();
    }
    
    /* Control Endpoint 0 Requests Handler */
    if (usbcsr0 & _USBCSR0_EP0IF_MASK) {
        if (tUsbControlStatus.adr_pending == true) { // Set Address, upon first IN transaction
            USBCSR0bits.FUNC = tUsbControlStatus.adr;
            tUsbControlStatus.adr_pending = false;
        }
        
        if (_System_Task_Check(SYS_TASK_USB_EP0_ISR) == 0) // if no request processing
        if (USBE0CSR0bits.RXRDY) // if received control packet
        {   // read control cmd
            _EP0_Control_Cmd_Read( ep0buf );
            // Fast checking "set address" request (2mS processing timeout)
            if (((USB_SETUP_PACKET*)ep0buf)->bmbRequest == STDREQ_SET_ADDRESS) {
                tUsbControlStatus.adr = ((USB_SETUP_PACKET*)ep0buf)->bDevADR;
                tUsbControlStatus.adr_pending = true;
            }
            else
                _System_Task_Set( SYS_TASK_USB_EP0_ISR );   // Set delayed task
        }
        
        USBCSR0bits.EP0IF = 0;      // Clear the USB EndPoint 0 Interrupt Flag.
    }
    
    /* Endpoint 1 RX Interrupt Handler */
    if (usbcsr1 & _USBCSR1_EP1RXIF_MASK) {
        if (USBE1CSR1bits.RXPKTRDY)
        { // ISOCHRONOUS Endpoint 1 Received A Packet
            uint16_t rxcnt = USBE1CSR2bits.RXCNT;           // Load received data count
            uint32_t adr = tEp1Fifo.adr + tEp1Fifo.ptr;     // Calculate USB DMA1 memory address            
            tEp1Fifo.ptr += rxcnt;                          // Buffer pointer increment

            if (tEp1Fifo.ptr >= tEp1Fifo.len) { // if not anoth space if data buffer - receive part only
                tEp1Fifo.rem = tEp1Fifo.ptr - tEp1Fifo.len; // Calculate remain value
                tEp1Fifo.ptr = tEp1Fifo.rem;                // Set pointer to remain value
                rxcnt -= tEp1Fifo.rem;                      // Set USB DMA1 data lenght
            }
            
            _USBDMA_EP1RX_Transfer_Start(adr, rxcnt);
        }
    }
    
    /* EP1 Errors Processing */
    /*  Flush the next packet to be read from the endpoint RX FIFO. 
        The FIFO pointer is reset and the RXPKTRDY bit is cleared. 
        This should only be used when RXPKTRDY is set. If the FIFO is doublebuffered,
        FLUSH may need to be set twice to completely clear the FIFO. */
    if (USBE1CSR1bits.FIFOFULL) {
        while (USBE1CSR1bits.RXPKTRDY)
            USBE1CSR1bits.FLUSH = 1;    // Flush FIFO
    }    
    if (USBE1CSR1bits.ERROR) {      // An OUT packet cannot be loaded into the RX FIFO
        USBE1CSR1bits.ERROR = 0;    // Clear the OVERRUN 
    }
    if (USBE1CSR1bits.DERRNAKT) {   // The data packet has a CRC or bit-stuff error
    }
    if (USBE1CSR0bits.UNDERRUN) {   // An IN token has been received when TXPKTRDY is not set
        USBE1CSR0bits.UNDERRUN = 0; // Clear the TX UNDERRUN
    }
    
    /* Interrupt Flags Processing */
    if (USBCSR2 & 0x00ff0000) {
        USBCSR2 &= ~(0x00ff0000);
    }
    
    IFS4CLR = _IFS4_USBIF_MASK;             // Clear the USB interrupt flag
}

// Debug variables to isocronous feedback check
//unsigned int fbLowCnt = 0;
//unsigned int fbHighCnt = 0;
//unsigned int fbNomCnt = 0;
/* 
 * USBDMA_Interrupt()
 */
void __ISR(_USB_DMA_VECTOR, ipl4SRS) USBDMA_Interrupt(void)
{
    uint32_t dmaInt = USBDMAINT;    // cleare flags on read
    
    if (dmaInt & _USBDMAINT_DMA1IF_MASK)
    {
        if (tEp1Fifo.rem) {
            _USBDMA_EP1RX_Transfer_Start(tEp1Fifo.adr, tEp1Fifo.rem);
            tEp1Fifo.rem = 0;
        }
        else {
            USBE1CSR1bits.RXPKTRDY = 0;                     // Comfirm received data packet
            
            if (!USBE1CSR0bits.TXPKTRDY) { // If previos packet has been transmitted
                int buff_diff = DMA_OUTPUT_TRANSFET_PTR - tEp1Fifo.ptr;  // Calculate Read and Write data difference
                if (buff_diff < 0)
                    buff_diff += tEp1Fifo.len;

                // Write FeedBack data to EP1 TX FIFO
                if (buff_diff < tEp1Fifo.min) {
                    _EP1_FeedBack_Data_Send(tFreqLims.lo);
//                    fbLowCnt++;
                }
                else if (buff_diff > tEp1Fifo.max) {
                    _EP1_FeedBack_Data_Send(tFreqLims.hi);
//                    fbHighCnt++;
                }
                else {
                    _EP1_FeedBack_Data_Send(tFreqLims.nom);
//                    fbNomCnt++;
                }
            }
        }
    }
    
    IFS4CLR = _IFS4_USBDMAIF_MASK;              // Clear the USB DMA interrupt flag.
}


