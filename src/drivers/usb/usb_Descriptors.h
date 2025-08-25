
#ifndef _USB_DESCRIPTORS_H_    /* Guard against multiple inclusion */
#define _USB_DESCRIPTORS_H_




/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <string.h>
#include <wchar.h>

#include "usb_audio_v1_0.h"
#include "usb_audio_v2_0.h"
#include "usb_chapter_9.h"
#include "usbd_def.h"
#include "usbd_audio_core.h"

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif





//#define USB_VID 0x16C0
//#define USB_PID 0x05DF
//#define USB_VID 0x2207
//#define USB_PID 0x0019
//#define USB_VID 0x16D0
//#define USB_PID 0x070A
    
// Microchip VID/PID
#define USB_VID 0x04D8
#define USB_PID 0x0064

    
    
    
    
/*** USB Device Stack Configuration ***/

#define STRING_DESCRIPTORS_NUM                      18
    
#define USB_STRING(name, str)\
static const struct name{\
        uint8_t  bLength;\
        uint8_t  bDescriptorType;\
        uint16_t bString[(sizeof(str) - 2) / 2];\
}name __attribute__ ((aligned (4))) = {sizeof(name), 0x03, str}


typedef struct{
    const void *p;
    int size;
}tUSB_DESC;

    
typedef struct{
    tUSB_DESC device;
    tUSB_DESC qualifier;
    tUSB_DESC configuration;
    tUSB_DESC string[STRING_DESCRIPTORS_NUM];
}tUSB_DEVICE_DESCRIPTORS;


    

/*******************************************
 * USB Device Layer Descriptors
 *******************************************/

/*******************************************
 *  USB Device Descriptor 
 *******************************************/
static const uint8_t deviceDescriptor[] __attribute__ ((aligned (4))) =
{
    0x12,                       /*bLength */
    USB_DESC_TYPE_DEVICE,       /*bDescriptorType*/
    0x00,0x02,                  /*bcdUSB */    
    0x00,                       /*bDeviceClass*/
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    USB_MAX_EP0_SIZE,           /*bMaxPacketSize*/
    LOBYTE(USB_VID),            /*idVendor*/
    HIBYTE(USB_VID),            /*idVendor*/
    LOBYTE(USB_PID),            /*idProduct*/
    HIBYTE(USB_PID),            /*idProduct*/
    0x00,0x02,                  /*bcdDevice rel. 2.00*/    
    USBD_IDX_MFC_STR,           /*Index of manufacturer  string*/
    USBD_IDX_PRODUCT_STR,       /*Index of product string*/
    USBD_IDX_SERIAL_STR,        /*Index of serial number string*/
    USBD_MAX_NUM_CONFIGURATION  /*bNumConfigurations*/
};

/*******************************************
 *  USB Device Qualifier Descriptor for this
 *  demo.
 *******************************************/
static const uint8_t deviceQualifierDescriptor[] __attribute__ ((aligned (4))) =
{
    0x0A,                               // Device Qualifier Descriptor Size
    USB_DESCRIPTOR_DEVICE_QUALIFIER,    // Device Qualifier Type
    0x00,0x02,                            
    0x00,                               // Class Code
    0x00,                               // Subclass code
    0x00,                               // Protocol code
    USB_MAX_EP0_SIZE,                   // Maximum packet size for endpoint 0
    USBD_MAX_NUM_CONFIGURATION,         // Number of possible configurations
    0x00                                // Reserved for future use.
}; // */

/*******************************************
 *  Configuration Descriptor
 *******************************************/
static const uint8_t ConfigurationDescriptor[] __attribute__ ((aligned (4))) = 
{
    /* Configuration descriptor 
     * The interface descriptor is immediately after the descriptor. The interface 
     * descriptor indicates the type of interface and the number of corresponding endpoints */
    0x09,                                           /* bLength */
    USB_DESC_TYPE_CONFIGURATION,                    /* bDescriptorType */
    LOBYTE(USB_AUDIO_CONFIG_DESC_SIZ),              /* wTotalLength  187 bytes*/
    HIBYTE(USB_AUDIO_CONFIG_DESC_SIZ),
    (AUDIO_INTERFACES_COUNT),                       /* bNumInterfaces */
    0x01,                                           /* bConfigurationValue */
    USBD_IDX_CONFIG_STR,                            /* iConfiguration */
    0x80,                                           /* bmAttributes: Bus Powered according to user configuration */
    USBD_MAX_POWER,                                 /* bMaxPower = 100 mA */
    /* 09 byte */
    
        /* Interface Association descriptor 
         * USB composite devices are generally implemented with Interface Association Descriptor (IAD), 
         * which is to add IAD descriptor before the interface to be merged */
        USB_AUDIO_IAD_DESC_SIZE,                /* bLength */
        USB_DESC_TYPE_IAD,                      /* bDescriptorType */
        AUDIO_FIRST_INTERFACE_NUM,              /* bFirstInterface */
        AUDIO_INTERFACES_COUNT,                 /* bInterfaceCount */
        USB_DEVICE_CLASS_AUDIO,                 /* bFunctionClass */
        USB_AUDIO_V2_FUNCTION_SUBCLASS_UNDEFINED, /* bFunctionSubClass */
        USB_AUDIO_V2_AF_VERSION_02_00,          /* bFunctionProtocol */
        0x05,                                   /* iFunction - USB Audio 2.0 */
        /* 08 byte */

            /* Interface descriptor */
            AUDIO_INTERFACE_DESC_SIZE,              /* bLength */
            USB_DESC_TYPE_INTERFACE,                /* bDescriptorType */
            AUDIO_CONTROL_INTERFACE_NUM,            /* bInterfaceNumber */
            0x00,                                   /* bAlternateSetting */
            0x00,                                   /* bNumEndpoints */
            USB_AUDIO_V2_CLASS_CODE,                /* bInterfaceClass */
            USB_AUDIO_V2_AUDIOCONTROL,              /* bInterfaceSubClass */
            USB_AUDIO_V2_IP_VERSION_02_00,          /* bInterfaceProtocol */
            0x06,                                   /* iInterface - Topology Control */
            /* 09 byte */

                /* AudioControl Interface Descriptor
                 * The audio device interface header should contain a class-specific AC interface header descriptor,
                 * which is used to define other functional ports of the interface.
                 * Class-specific AC interface header descriptor (AC interface header)
                 *******************************************************************/
                AUDIO_INTERFACE_DESC_SIZE,              /* bLength */
                USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                USB_AUDIO_V2_HEADER,                    /* bDescriptorSubtype */
                0x00,0x02,          /* 2.00 */          /* bcdADC */
                USB_AUDIO_V2_IO_BOX,                    /* bCategory */
                0x2E,0x00,                              /* wTotalLength = 46 Total length of digital connection, including standard interface length */
                0x00,                                   /* bmControls */
                /* 09 byte */
    
                    /* AudioControl Interface Descriptor
                     * Audio device frequency description Clock source for OUT traffic */
                    0x08,                                   /* bLength */
                    USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                    USB_AUDIO_V2_CLOCK_SOURCE,              /* bDescriptorSubtype */
                    AUDIO_SCLOCK_TERMINAL_OUTPUT,           /* bClockID */
                    0x00,                                   /* bmAttributes - 0 - External clock cource, 1 - Internal fixed clock, 3 - Internal programmable clock */
                    0x03,                                   /* bmControls - Clock Frequency Control (read/write) */
                    0x00,                                   /* bAssocTerminal - Constant corresponding output port ID */
                    0x00,                                   /* iClockSource -  */
                    /* 08 byte */
    
                    /* AudioControl Interface Descriptor
                     * USB Input Terminal for OUTPUT Descriptor */
                    0x11,                                   /* bLength */
                    USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                    USB_AUDIO_V2_INPUT_TERMINAL,            /* bDescriptorSubtype */
                    AUDIO_IN_TERMINAL_OUTPUT,               /* bTerminalID */
                    0x01,0x01,                              /* wTerminalType AUDIO_TERMINAL_USB_STREAMING  0x0101 */
                    0x00,                                   /* bAssocTerminal */
                    AUDIO_SCLOCK_TERMINAL_OUTPUT,           /* bCSourceID */
                    0x00,                                   /* bNrChannels */
                    0x00,0x00,0x00,0x00,                    /* bmChannelConfig 0x00000000  all channels control */
                    0x00,0x00,                              /* bmControls - 0x0003 Copy Protect Control (read/write) */
                    0x00,                                   /* iChannelNames */
                    0x00,                                   /* iTerminal - USBH Out */
                    /* 17 byte */

                    /* AudioControl Interface Descriptor
                     * USB Output Terminal for OUTPUT Descriptor */
                    0x0C,                                   /* bLength */
                    USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                    USB_AUDIO_V2_OUTPUT_TERMINAL,           /* bDescriptorSubtype */
                    AUDIO_OUT_TERMINAL_OUTPUT,              /* bTerminalID */
                    0x02,0x06,                              /* wTerminalType - A generic digital audio interface */
                    0x00,                                   /* bAssocTerminal */
                    AUDIO_IN_TERMINAL_OUTPUT,               /* bSourceID */
                    AUDIO_SCLOCK_TERMINAL_OUTPUT,           /* bCSourceID */
                    0x00,0x00,                              /* bmControls - 0x0003 Copy Protect Control (read/write) */
                    0x00,                                   /* iTerminal - USBD In */
                    /* 12 byte */
                    /*****************************************************
                     *****************************************************************/

            /* Interface Descriptor - Audio Streaming OUT Interface - Alt0 */
            AUDIO_INTERFACE_DESC_SIZE,              /* bLength */
            USB_DESC_TYPE_INTERFACE,                /* bDescriptorType */
            AUDIO_STREAMING_OUTPUT_INTERFACE_NUM,   /* bInterfaceNumber */
            USB_AUDIO_OUTPUT_ALTSET_OFF,            /* bAlternateSetting */
            0x00,                                   /* bNumEndpoints */
            USB_AUDIO_V2_CLASS_CODE,                /* bInterfaceClass */
            USB_AUDIO_V2_AUDIOSTREAMING,            /* bInterfaceSubClass */
            USB_AUDIO_V2_IP_VERSION_02_00,          /* bInterfaceProtocol */
            0x00,                                   /* iInterface - Playback Inactive */
            /* 09 byte */
    
            /* Interface Descriptor - Audio Streaming OUT Interface - Alt1 */
            AUDIO_INTERFACE_DESC_SIZE,              /* bLength */
            USB_DESC_TYPE_INTERFACE,                /* bDescriptorType */
            AUDIO_STREAMING_OUTPUT_INTERFACE_NUM,   /* bInterfaceNumber */
            USB_AUDIO_OUTPUT_ALTSET_2CH16_ON,         /* bAlternateSetting */
            0x02,                                   /* bNumEndpoints */
            USB_AUDIO_V2_CLASS_CODE,                /* bInterfaceClass */
            USB_AUDIO_V2_AUDIOSTREAMING,            /* bInterfaceSubClass */
            USB_AUDIO_V2_IP_VERSION_02_00,          /* bInterfaceProtocol */
            0x00,                                   /* iInterface - Playback Active */
            /* 09 byte */

                /* AudioStreaming Interface Descriptor - Audio Stream OUT Interface Desc */
                /* Interface 1, Alternate Setting 1                                           */
                0x10,                                   /* bLength */
                USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                USB_AUDIO_V2_AS_GENERAL,                /* bDescriptorSubtype */
                AUDIO_IN_TERMINAL_OUTPUT,               /* bTerminalLink */
                0x00,                                   /* bmControls */
                USB_AUDIO_V2_FORMAT_TYPE_I,             /* bFormatType */
                0x01,0x00,0x00,0x00,                    /* bmFormats D0 - PCM */
                0x02,                                   /* bNrChannels */
                0x03,0x00,0x00,0x00,                    /* bmChannelConfig 0x00000003 driver choose channels */
                0x00,                                   /* iChannelNames */
                /* 16 byte */

                /* AudioStreaming Interface Descriptor - Audio USB_OUT Format */
                0x6,                                    /* bLength */
                USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                AUDIO_STREAMING_FORMAT_TYPE,            /* bDescriptorSubtype */
                USB_AUDIO_V2_FORMAT_TYPE_I,             /* bFormatType */
                0x02,                                   /* bSubslotSize :  2 Bytes per frame (32bits) */
                16,                                     /* bBitResolution (16-bits per sample) */
                /* 06 byte */ 
 
                /* Endpoint Descriptor - STD AS ISO OUT Endpoint */
                0x07,                                   /* bLength */
                USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType */
                AUDIO_OUT_EP,                           /* bEndpointAddress 1 out endpoint */
                0x05,                                   /* bmAttributes Asynchronous Isochronous mode */
                0x00,0x04,                              /* wMaxPacketSize in Bytes 1024 per micro-frame */
                0x01,                                   /* bInterval (Frames/Subframes) 2^(1-1)=1 */
                /* 07 byte */
    
                    /* AudioControl Endpoint Descriptor - CS AS ISO OUT Endpoint */
                    0x08,                                   /* bLength */
                    USB_AUDIO_V2_CS_ENDPOINT,               /* bDescriptorType */
                    USB_AUDIO_V2_EP_GENERAL,                /* bDescriptorSubtype */
                    0x00,                                   /* bmAttributes */
                    0x00,                                   /* bmControls */
                    0x00,                                   /* bLockDelayUnits - Undefined */
                    0x00,0x00,                              /* wLockDelay */
                    /* 08 byte */
    
                /* Endpoint Descriptor - STD AS ISO Feedback Endpoint */
                0x07,                                   /* bLength */
                USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType */
                AUDIO_FB_EP,                            /* bEndpointAddress 1 int endpoint */
                0x11,                                   /* bmAttributes FeedBack Isochronous mode */
                0x04,0x00,                              /* wMaxPacketSize in Bytes 4 per micro-frame */
                0x03,                                   /* bInterval (Frames/Subframes) 2^(3-1)=4 */
                /* 07 byte */
    
            /* Interface Descriptor - Audio Streaming OUT Interface - Alt2 */
            AUDIO_INTERFACE_DESC_SIZE,              /* bLength */
            USB_DESC_TYPE_INTERFACE,                /* bDescriptorType */
            AUDIO_STREAMING_OUTPUT_INTERFACE_NUM,   /* bInterfaceNumber */
            USB_AUDIO_OUTPUT_ALTSET_2CH24_ON,       /* bAlternateSetting */
            0x02,                                   /* bNumEndpoints */
            USB_AUDIO_V2_CLASS_CODE,                /* bInterfaceClass */
            USB_AUDIO_V2_AUDIOSTREAMING,            /* bInterfaceSubClass */
            USB_AUDIO_V2_IP_VERSION_02_00,          /* bInterfaceProtocol */
            0x00,                                   /* iInterface - Playback Active */
            /* 09 byte */

                /* AudioStreaming Interface Descriptor - Audio Stream OUT Interface Desc */
                /* Interface 1, Alternate Setting 1                                           */
                0x10,                                   /* bLength */
                USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                USB_AUDIO_V2_AS_GENERAL,                /* bDescriptorSubtype */
                AUDIO_IN_TERMINAL_OUTPUT,               /* bTerminalLink */
                0x00,                                   /* bmControls */
                USB_AUDIO_V2_FORMAT_TYPE_I,             /* bFormatType */
                0x01,0x00,0x00,0x00,                    /* bmFormats D0 - PCM */
                0x02,                                   /* bNrChannels */
                0x03,0x00,0x00,0x00,                    /* bmChannelConfig 0x00000003 driver choose channels */
                0x00,                                   /* iChannelNames */
                /* 16 byte */

                /* AudioStreaming Interface Descriptor - Audio USB_OUT Format */
                0x6,                                    /* bLength */
                USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                AUDIO_STREAMING_FORMAT_TYPE,            /* bDescriptorSubtype */
                USB_AUDIO_V2_FORMAT_TYPE_I,             /* bFormatType */
                0x04,                                   /* bSubslotSize :  4 Bytes per frame (32bits) */
                24,                                     /* bBitResolution (24-bits per sample) */
                /* 06 byte */ 
 
                /* Endpoint Descriptor - STD AS ISO OUT Endpoint */
                0x07,                                   /* bLength */
                USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType */
                AUDIO_OUT_EP,                           /* bEndpointAddress 1 out endpoint */
                0x05,                                   /* bmAttributes Asynchronous Isochronous mode */
                0x00,0x04,                              /* wMaxPacketSize in Bytes 1024 per micro-frame */
                0x01,                                   /* bInterval (Frames/Subframes) 2^(1-1)=1 */
                /* 07 byte */
    
                    /* AudioControl Endpoint Descriptor - CS AS ISO OUT Endpoint */
                    0x08,                                   /* bLength */
                    USB_AUDIO_V2_CS_ENDPOINT,               /* bDescriptorType */
                    USB_AUDIO_V2_EP_GENERAL,                /* bDescriptorSubtype */
                    0x00,                                   /* bmAttributes */
                    0x00,                                   /* bmControls */
                    0x00,                                   /* bLockDelayUnits - Undefined */
                    0x00,0x00,                              /* wLockDelay */
                    /* 08 byte */
    
                /* Endpoint Descriptor - STD AS ISO Feedback Endpoint */
                0x07,                                   /* bLength */
                USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType */
                AUDIO_FB_EP,                            /* bEndpointAddress 1 int endpoint */
                0x11,                                   /* bmAttributes FeedBack Isochronous mode */
                0x04,0x00,                              /* wMaxPacketSize in Bytes 4 per micro-frame */
                0x03,                                   /* bInterval (Frames/Subframes) 2^(3-1)=4 */
                /* 07 byte */
    
            /* Interface Descriptor - Audio Streaming OUT Interface - Alt3 */
            AUDIO_INTERFACE_DESC_SIZE,              /* bLength */
            USB_DESC_TYPE_INTERFACE,                /* bDescriptorType */
            AUDIO_STREAMING_OUTPUT_INTERFACE_NUM,   /* bInterfaceNumber */
            USB_AUDIO_OUTPUT_ALTSET_2CH32_ON,       /* bAlternateSetting */
            0x02,                                   /* bNumEndpoints */
            USB_AUDIO_V2_CLASS_CODE,                /* bInterfaceClass */
            USB_AUDIO_V2_AUDIOSTREAMING,            /* bInterfaceSubClass */
            USB_AUDIO_V2_IP_VERSION_02_00,          /* bInterfaceProtocol */
            0x00,                                   /* iInterface - Playback Active */
            /* 09 byte */

                /* AudioStreaming Interface Descriptor - Audio Stream OUT Interface Desc */
                /* Interface 1, Alternate Setting 1                                           */
                0x10,                                   /* bLength */
                USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                USB_AUDIO_V2_AS_GENERAL,                /* bDescriptorSubtype */
                AUDIO_IN_TERMINAL_OUTPUT,               /* bTerminalLink */
                0x00,                                   /* bmControls */
                USB_AUDIO_V2_FORMAT_TYPE_I,             /* bFormatType */
                0x01,0x00,0x00,0x00,                    /* bmFormats D0 - PCM */
                0x02,                                   /* bNrChannels */
                0x03,0x00,0x00,0x00,                    /* bmChannelConfig 0x00000003 driver choose channels */
                0x00,                                   /* iChannelNames */
                /* 16 byte */

                /* AudioStreaming Interface Descriptor - Audio USB_OUT Format */
                0x6,                                    /* bLength */
                USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                AUDIO_STREAMING_FORMAT_TYPE,            /* bDescriptorSubtype */
                USB_AUDIO_V2_FORMAT_TYPE_I,             /* bFormatType */
                0x04,                                   /* bSubslotSize :  4 Bytes per frame (32bits) */
                32,                                     /* bBitResolution (32-bits per sample) */
                /* 06 byte */
 
                /* Endpoint Descriptor - STD AS ISO OUT Endpoint */
                0x07,                                   /* bLength */
                USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType */
                AUDIO_OUT_EP,                           /* bEndpointAddress 1 out endpoint */
                0x05,                                   /* bmAttributes Asynchronous Isochronous mode */
                0x00,0x04,                              /* wMaxPacketSize in Bytes 1024 per micro-frame */
                0x01,                                   /* bInterval (Frames/Subframes) 2^(1-1)=1 */
                /* 07 byte */
    
                    /* AudioControl Endpoint Descriptor - CS AS ISO OUT Endpoint */
                    0x08,                                   /* bLength */
                    USB_AUDIO_V2_CS_ENDPOINT,               /* bDescriptorType */
                    USB_AUDIO_V2_EP_GENERAL,                /* bDescriptorSubtype */
                    0x00,                                   /* bmAttributes */
                    0x00,                                   /* bmControls */
                    0x00,                                   /* bLockDelayUnits - Undefined */
                    0x00,0x00,                              /* wLockDelay */
                    /* 08 byte */
    
                /* Endpoint Descriptor - STD AS ISO Feedback Endpoint */
                0x07,                                   /* bLength */
                USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType */
                AUDIO_FB_EP,                            /* bEndpointAddress 1 int endpoint */
                0x11,                                   /* bmAttributes FeedBack Isochronous mode */
                0x04,0x00,                              /* wMaxPacketSize in Bytes 4 per micro-frame */
                0x03,                                   /* bInterval (Frames/Subframes) 2^(3-1)=4 */
                /* 07 byte */ 
    
    
            /* Interface Descriptor - Audio Streaming OUT Interface - Alt4 */
            AUDIO_INTERFACE_DESC_SIZE,              /* bLength */
            USB_DESC_TYPE_INTERFACE,                /* bDescriptorType */
            AUDIO_STREAMING_OUTPUT_INTERFACE_NUM,   /* bInterfaceNumber */
            USB_AUDIO_OUTPUT_ALTSET_8CH16_ON,       /* bAlternateSetting */
            0x02,                                   /* bNumEndpoints */
            USB_AUDIO_V2_CLASS_CODE,                /* bInterfaceClass */
            USB_AUDIO_V2_AUDIOSTREAMING,            /* bInterfaceSubClass */
            USB_AUDIO_V2_IP_VERSION_02_00,          /* bInterfaceProtocol */
            0x00,                                   /* iInterface - Playback Active */
            /* 09 byte */

                /* AudioStreaming Interface Descriptor - Audio Stream OUT Interface Desc */
                /* Interface 1, Alternate Setting 2                                           */
                0x10,                                   /* bLength */
                USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                USB_AUDIO_V2_AS_GENERAL,                /* bDescriptorSubtype */
                AUDIO_IN_TERMINAL_OUTPUT,               /* bTerminalLink */
                0x00,                                   /* bmControls */
                USB_AUDIO_V2_FORMAT_TYPE_I,             /* bFormatType */
                0x01,0x00,0x00,0x00,                    /* bmFormats D0 - PCM */
                0x08,                                   /* bNrChannels */
                0x3F,0x06,0x00,0x00,                    /* bmChannelConfig 0x0000063F  all channels control */
                0x00,                                   /* iChannelNames */
                /* 16 byte */

                /* AudioStreaming Interface Descriptor - Audio USB_OUT Format */
                0x6,                                    /* bLength */
                USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                AUDIO_STREAMING_FORMAT_TYPE,            /* bDescriptorSubtype */
                USB_AUDIO_V2_FORMAT_TYPE_I,             /* bFormatType */
                0x02,                                   /* bSubslotSize :  4 Bytes per frame (32bits) */
                16,                                     /* bBitResolution (32-bits per sample) */
                /* 06 byte */ 
 
                /* Endpoint Descriptor - STD AS ISO OUT Endpoint */
                0x07,                                   /* bLength */
                USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType */
                AUDIO_OUT_EP,                           /* bEndpointAddress 1 out endpoint */
                0x05,                                   /* bmAttributes Asynchronous Isochronous mode */
                0x00,0x04,                              /* wMaxPacketSize in Bytes 1024 per micro-frame */
                0x01,                                   /* bInterval (Frames/Subframes) 2^(1-1)=1 */
                /* 07 byte */
    
                    /* AudioControl Endpoint Descriptor - CS AS ISO OUT Endpoint */
                    0x08,                                   /* bLength */
                    USB_AUDIO_V2_CS_ENDPOINT,               /* bDescriptorType */
                    USB_AUDIO_V2_EP_GENERAL,                /* bDescriptorSubtype */
                    0x00,                                   /* bmAttributes */
                    0x00,                                   /* bmControls */
                    0x00,                                   /* bLockDelayUnits - Undefined */
                    0x00,0x00,                              /* wLockDelay */
                    /* 08 byte */
    
                /* Endpoint Descriptor - STD AS ISO Feedback Endpoint */
                0x07,                                   /* bLength */
                USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType */
                AUDIO_FB_EP,                            /* bEndpointAddress 1 int endpoint */
                0x11,                                   /* bmAttributes FeedBack Isochronous mode */
                0x04,0x00,                              /* wMaxPacketSize in Bytes 4 per micro-frame */
                0x03,                                   /* bInterval (Frames/Subframes) 2^(3-1)=4 */
                /* 07 byte */
    
            /* Interface Descriptor - Audio Streaming OUT Interface - Alt5 */
            AUDIO_INTERFACE_DESC_SIZE,              /* bLength */
            USB_DESC_TYPE_INTERFACE,                /* bDescriptorType */
            AUDIO_STREAMING_OUTPUT_INTERFACE_NUM,   /* bInterfaceNumber */
            USB_AUDIO_OUTPUT_ALTSET_8CH24_ON,       /* bAlternateSetting */
            0x02,                                   /* bNumEndpoints */
            USB_AUDIO_V2_CLASS_CODE,                /* bInterfaceClass */
            USB_AUDIO_V2_AUDIOSTREAMING,            /* bInterfaceSubClass */
            USB_AUDIO_V2_IP_VERSION_02_00,          /* bInterfaceProtocol */
            0x00,                                   /* iInterface - Playback Active */
            /* 09 byte */

                /* AudioStreaming Interface Descriptor - Audio Stream OUT Interface Desc */
                /* Interface 1, Alternate Setting 2                                           */
                0x10,                                   /* bLength */
                USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                USB_AUDIO_V2_AS_GENERAL,                /* bDescriptorSubtype */
                AUDIO_IN_TERMINAL_OUTPUT,               /* bTerminalLink */
                0x00,                                   /* bmControls */
                USB_AUDIO_V2_FORMAT_TYPE_I,             /* bFormatType */
                0x01,0x00,0x00,0x00,                    /* bmFormats D0 - PCM */
                0x08,                                   /* bNrChannels */
                0x3F,0x06,0x00,0x00,                    /* bmChannelConfig 0x0000063F  all channels control */
                0x00,                                   /* iChannelNames */
                /* 16 byte */

                /* AudioStreaming Interface Descriptor - Audio USB_OUT Format */
                0x6,                                    /* bLength */
                USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                AUDIO_STREAMING_FORMAT_TYPE,            /* bDescriptorSubtype */
                USB_AUDIO_V2_FORMAT_TYPE_I,             /* bFormatType */
                0x04,                                   /* bSubslotSize :  4 Bytes per frame (32bits) */
                24,                                     /* bBitResolution (32-bits per sample) */
                /* 06 byte */ 
 
                /* Endpoint Descriptor - STD AS ISO OUT Endpoint */
                0x07,                                   /* bLength */
                USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType */
                AUDIO_OUT_EP,                           /* bEndpointAddress 1 out endpoint */
                0x05,                                   /* bmAttributes Asynchronous Isochronous mode */
                0x00,0x04,                              /* wMaxPacketSize in Bytes 1024 per micro-frame */
                0x01,                                   /* bInterval (Frames/Subframes) 2^(1-1)=1 */
                /* 07 byte */
    
                    /* AudioControl Endpoint Descriptor - CS AS ISO OUT Endpoint */
                    0x08,                                   /* bLength */
                    USB_AUDIO_V2_CS_ENDPOINT,               /* bDescriptorType */
                    USB_AUDIO_V2_EP_GENERAL,                /* bDescriptorSubtype */
                    0x00,                                   /* bmAttributes */
                    0x00,                                   /* bmControls */
                    0x00,                                   /* bLockDelayUnits - Undefined */
                    0x00,0x00,                              /* wLockDelay */
                    /* 08 byte */
    
                /* Endpoint Descriptor - STD AS ISO Feedback Endpoint */
                0x07,                                   /* bLength */
                USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType */
                AUDIO_FB_EP,                            /* bEndpointAddress 1 int endpoint */
                0x11,                                   /* bmAttributes FeedBack Isochronous mode */
                0x04,0x00,                              /* wMaxPacketSize in Bytes 4 per micro-frame */
                0x03,                                   /* bInterval (Frames/Subframes) 2^(3-1)=4 */
                /* 07 byte */
    
            /* Interface Descriptor - Audio Streaming OUT Interface - Alt6 */
            AUDIO_INTERFACE_DESC_SIZE,              /* bLength */
            USB_DESC_TYPE_INTERFACE,                /* bDescriptorType */
            AUDIO_STREAMING_OUTPUT_INTERFACE_NUM,   /* bInterfaceNumber */
            USB_AUDIO_OUTPUT_ALTSET_8CH32_ON,       /* bAlternateSetting */
            0x02,                                   /* bNumEndpoints */
            USB_AUDIO_V2_CLASS_CODE,                /* bInterfaceClass */
            USB_AUDIO_V2_AUDIOSTREAMING,            /* bInterfaceSubClass */
            USB_AUDIO_V2_IP_VERSION_02_00,          /* bInterfaceProtocol */
            0x00,                                   /* iInterface - Playback Active */
            /* 09 byte */

                /* AudioStreaming Interface Descriptor - Audio Stream OUT Interface Desc */
                /* Interface 1, Alternate Setting 2                                           */
                0x10,                                   /* bLength */
                USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                USB_AUDIO_V2_AS_GENERAL,                /* bDescriptorSubtype */
                AUDIO_IN_TERMINAL_OUTPUT,               /* bTerminalLink */
                0x00,                                   /* bmControls */
                USB_AUDIO_V2_FORMAT_TYPE_I,             /* bFormatType */
                0x01,0x00,0x00,0x00,                    /* bmFormats D0 - PCM */
                0x08,                                   /* bNrChannels */
                0x3F,0x06,0x00,0x00,                    /* bmChannelConfig 0x0000063F  all channels control */
                0x00,                                   /* iChannelNames */
                /* 16 byte */

                /* AudioStreaming Interface Descriptor - Audio USB_OUT Format */
                0x6,                                    /* bLength */
                USB_AUDIO_V2_CS_INTERFACE,              /* bDescriptorType */
                AUDIO_STREAMING_FORMAT_TYPE,            /* bDescriptorSubtype */
                USB_AUDIO_V2_FORMAT_TYPE_I,             /* bFormatType */
                0x04,                                   /* bSubslotSize :  4 Bytes per frame (32bits) */
                32,                                     /* bBitResolution (32-bits per sample) */
                /* 06 byte */ 
 
                /* Endpoint Descriptor - STD AS ISO OUT Endpoint */
                0x07,                                   /* bLength */
                USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType */
                AUDIO_OUT_EP,                           /* bEndpointAddress 1 out endpoint */
                0x05,                                   /* bmAttributes Asynchronous Isochronous mode */
                0x00,0x04,                              /* wMaxPacketSize in Bytes 1024 per micro-frame */
                0x01,                                   /* bInterval (Frames/Subframes) 2^(1-1)=1 */
                /* 07 byte */
    
                    /* AudioControl Endpoint Descriptor - CS AS ISO OUT Endpoint */
                    0x08,                                   /* bLength */
                    USB_AUDIO_V2_CS_ENDPOINT,               /* bDescriptorType */
                    USB_AUDIO_V2_EP_GENERAL,                /* bDescriptorSubtype */
                    0x00,                                   /* bmAttributes */
                    0x00,                                   /* bmControls */
                    0x00,                                   /* bLockDelayUnits - Undefined */
                    0x00,0x00,                              /* wLockDelay */
                    /* 08 byte */
    
                /* Endpoint Descriptor - STD AS ISO Feedback Endpoint */
                0x07,                                   /* bLength */
                USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType */
                AUDIO_FB_EP,                            /* bEndpointAddress 1 int endpoint */
                0x11,                                   /* bmAttributes FeedBack Isochronous mode */
                0x04,0x00,                              /* wMaxPacketSize in Bytes 4 per micro-frame */
                0x03,                                   /* bInterval (Frames/Subframes) 2^(3-1)=4 */
                /* 07 byte */
};

/**************************************
 *  String descriptors.
 *************************************/
/*********************************************************************
Language ID Descriptor
*********************************************************************/
static const unsigned char string0[] __attribute__ ((aligned (4))) = {	
/* 	Descriptor Length                       */	4, /* 4 or 0x04 */
/*  DescriptorType: STRING  				*/	0x03,
/* 	Language ID: English					*/	0x09,0x04
}; // 0x0409

/********************************************************************
String Descriptor: "Your Company Name"
*********************************************************************/
USB_STRING(string1, u"Diy Audio");

/*********************************************************************
 String Descriptor (Product Name): "USB Speaker Example"
 *********************************************************************/
USB_STRING(string2, u"PIC32MZ Composite USB Device");

/*********************************************************************
 String Descriptor (Serial Number): "123-4567"
 *********************************************************************/
USB_STRING(string3, u"0100");

/*********************************************************************
 String Descriptor 4
 *********************************************************************/
USB_STRING(string4, u"Configuration");

/*********************************************************************
 String Descriptor 5
 *********************************************************************/
USB_STRING(string5, u"PIC32MZ USB Audio 2.0");

/*********************************************************************
 String Descriptor 6
 *********************************************************************/
USB_STRING(string6, u"Topology Control");

/*********************************************************************
 String Descriptor 7 - Audio Interface Describtion
 *********************************************************************/
USB_STRING(string7, u"Audio Interface Describtion");

/*********************************************************************
 String Descriptor 8
 *********************************************************************/
USB_STRING(string8, u"44100");

/*********************************************************************
 String Descriptor 9
 *********************************************************************/
USB_STRING(string9, u"USBH Out");

/*********************************************************************
 String Descriptor 10
 *********************************************************************/
USB_STRING(string10, u"USBD Out");

/*********************************************************************
 String Descriptor 11
 *********************************************************************/
USB_STRING(string11, u"USBH Input");

/*********************************************************************
 String Descriptor 12
 *********************************************************************/
USB_STRING(string12, u"USBD Input");

/*********************************************************************
 String Descriptor 13
 *********************************************************************/
USB_STRING(string13, u"Playback Inactive");

/*********************************************************************
 String Descriptor 14
 *********************************************************************/
USB_STRING(string14, u"Playback Active");

/*********************************************************************
 String Descriptor 15
 *********************************************************************/
USB_STRING(string15, u"Capture Inactive");

/*********************************************************************
 String Descriptor 16
 *********************************************************************/
USB_STRING(string16, u"PIC32MZ CDC");

/*********************************************************************
 String Descriptor 17
 *********************************************************************/
USB_STRING(string17, u"PIC32MZ CDC Device");


const tUSB_DEVICE_DESCRIPTORS tUsbDescriptors = {
    {deviceDescriptor, sizeof(deviceDescriptor)},
    {deviceQualifierDescriptor, sizeof(deviceQualifierDescriptor)},
    {ConfigurationDescriptor, sizeof(ConfigurationDescriptor)},
    {
        {string0 ,sizeof(string0)},
        {&string1 ,sizeof(string1)},
        {&string2 ,sizeof(string2)},
        {&string3 ,sizeof(string3)},
        {&string4 ,sizeof(string4)},
        {&string5 ,sizeof(string5)},
        {&string6 ,sizeof(string6)},
        {&string7 ,sizeof(string7)},
        {&string8 ,sizeof(string8)},
        {&string9 ,sizeof(string9)},
        {&string10 ,sizeof(string10)},
        {&string11 ,sizeof(string11)},
        {&string12 ,sizeof(string12)},
        {&string13 ,sizeof(string13)},
        {&string14 ,sizeof(string14)},
        {&string15 ,sizeof(string15)},
        {&string16 ,sizeof(string16)},
        {&string17 ,sizeof(string17)},
    }
};


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _USB_DESCRIPTORS_H_ */

/* *****************************************************************************
 End of File
 */
