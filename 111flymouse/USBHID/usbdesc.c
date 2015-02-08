/*----------------------------------------------------------------------------
 * U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 * Name:    usbdesc.c
 * Purpose: USB Descriptors
 * Version: V1.20
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------
 * History:
 *          V1.20 Changed string descriptor handling
 *                Changed HID Report Descriptor
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/

#include "type.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbdesc.h"

#include "hid.h"

/*------------------------------------------------------------------------------
  HID Report Descriptor
 *------------------------------------------------------------------------------*/


#define HID_INPUT_REPORT_BYTES       1              /* size of report in Bytes */
#define HID_OUTPUT_REPORT_BYTES      1              /* size of report in Bytes */
#define HID_FEATURE_REPORT_BYTES     1              /* size of report in Bytes */

const U8 HID_ReportDescriptor[] = {

//-------------?????????----------------
    //????????????
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)

    //???????
    0x09, 0x06,                    // USAGE (Keyboard)
    
    //??????,????END_COLLECTION????,????END_COLLECTION
    0xa1, 0x01,                    // COLLECTION (Application)
    
    //??ID(??ID 0????)
    0x85, 0x01, //Report ID (1)
    
    //????????
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)

    //?????,????ctrl?
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    //?????,????GUI?,?window?
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    //??????0
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    //??????1
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    //????(????????)?1bit,???????????0,??????1
    0x75, 0x01,                    //   REPORT_SIZE (1)
    //??????8,????8?bits
    0x95, 0x08,                    //   REPORT_COUNT (8)
    //???,??,?,????????????????,
    //??????????????,????????
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    //?????????????????,???8?bits,??bit??????
    //????ctrl???GUI???8?bits????????,????????????
    //?????,?bit-0????ctrl?,??????????1,????ctrl????,
    //??,?ctrl?????????,?bit-7???GUI?????????????,
    //????HID??????????(HID Usage Tables)????????????
    //???,??ctrl,shift,del?? 

    //?????????1
    0x95, 0x01,                    //   REPORT_COUNT (1)
    //??????8bits
    0x75, 0x08,                    //   REPORT_SIZE (8)
    //???,??,?,???
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    
    //???8?bit???,??????0

    //?????????5
    0x95, 0x05,                    //   REPORT_COUNT (5)
    //??????1bit
    0x75, 0x01,                    //   REPORT_SIZE (1)
    //???LED,?????????LED??,????????????
    0x05, 0x08,                    //   USAGE_PAGE (LEDs)
    //??????Num Lock,???????
    0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)
    //??????Kana,???????????^_^
    0x29, 0x05,                    //   USAGE_MAXIMUM (Kana)
    //?????,?????????,????LED???,?,????
    //1????,0????
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)

    //?????????1
    0x95, 0x01,                    //   REPORT_COUNT (1)
    //??????3bits
    0x75, 0x03,                    //   REPORT_SIZE (3)
    //???,??,?,??
    0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs)    
    //????????,?????LED????5?bit,
    //????????3???bit,??????
 

    //?????6//////////////////////////////////////////////////////////////////////////////////////////
    0x95, 0x06,                    //   REPORT_COUNT (6)
    //??????8bits
    0x75, 0x08,                    //   REPORT_SIZE (8)
    //?????0
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    //?????255
    0x25, 0xFF,                    //   LOGICAL_MAXIMUM (255)
    //??????
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    //??????0
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    //??????0x65
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
    //???,??,??,???
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    //?????6?8bit????,??8bit(?????)????????,??????
    //?6?????????????,????0?????????,????????
    //???????,?????0x01,?6?0x01?????????,??6???????
    //?????????(??????HID Usage Tables),???????,??1?2??
    //??????????,?????

    //???,??????
    0xc0 ,                          // END_COLLECTION

    
    //-----------------------?????????----------------------------
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x02,                    // USAGE (Mouse)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, 0x02,               // ??ID (2)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    0x29, 0x03,                    //     USAGE_MAXIMUM (Button 3)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x75, 0x05,                    //     REPORT_SIZE (5)
    0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //     USAGE (X)
    0x09, 0x31,                    //     USAGE (Y)
    0x09, 0x38,                    //     USAGE (Wheel)
    0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
    0xc0,                          //   END_COLLECTION
    0xc0                           // END_COLLECTION
};

const U16 HID_ReportDescSize = sizeof(HID_ReportDescriptor);


/* USB Standard Device Descriptor */
const U8 USB_DeviceDescriptor[] = {
  USB_DEVICE_DESC_SIZE,              /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,        /* bDescriptorType */
  WBVAL(0x0200), /* 2.00 */          /* bcdUSB */
  0x00,                              /* bDeviceClass */
  0x00,                              /* bDeviceSubClass */
  0x00,                              /* bDeviceProtocol */
  USB_MAX_PACKET0,                   /* bMaxPacketSize0 */
  WBVAL(0x0829),                     /* idVendor */
  WBVAL(0x2017),                     /* idProduct */
  WBVAL(0x0200), /* 1.00 */          /* bcdDevice */
  0x01,                              /* iManufacturer */
  0x02,                              /* iProduct */
  0x03,                              /* iSerialNumber */
  0x01                               /* bNumConfigurations: one possible configuration*/
};

/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor) */
const U8 USB_ConfigDescriptor[] = {
/* Configuration 1 */
  USB_CONFIGUARTION_DESC_SIZE,       /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType */
  WBVAL(                             /* wTotalLength */
    (USB_CONFIGUARTION_DESC_SIZE +
    USB_INTERFACE_DESC_SIZE     +
    HID_DESC_SIZE               +
    USB_ENDPOINT_DESC_SIZE)
  ),
  0x01,                              /* bNumInterfaces */
  0x01,                              /* bConfigurationValue: 0x01 is used to select this configuration */
  0x00,                              /* iConfiguration: no string to describe this configuration */
  USB_CONFIG_BUS_POWERED /*|*/       /* bmAttributes */
/*USB_CONFIG_REMOTE_WAKEUP*/,
  USB_CONFIG_POWER_MA(100),          /* bMaxPower, device power consumption is 100 mA */

/* Interface 0, Alternate Setting 0, HID Class */
  USB_INTERFACE_DESC_SIZE,           /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,     /* bDescriptorType */
  0x00,                              /* bInterfaceNumber */
  0x00,                              /* bAlternateSetting */
  0x01,                              /* bNumEndpoints *//////////////////////////////////////////////////////////////
  USB_DEVICE_CLASS_HUMAN_INTERFACE,  /* bInterfaceClass */
  HID_SUBCLASS_NONE,                 /* bInterfaceSubClass */
  HID_PROTOCOL_KEYBOARD,                 /* bInterfaceProtocol */
  0x04,                              /* iInterface */
/* HID Class Descriptor */
/* HID_DESC_OFFSET = 0x0012 */
  HID_DESC_SIZE,                     /* bLength */
  HID_HID_DESCRIPTOR_TYPE,           /* bDescriptorType */
  WBVAL(0x0100), /* 1.00 */          /* bcdHID */
  0x00,                              /* bCountryCode */
  0x01,                              /* bNumDescriptors */
  HID_REPORT_DESCRIPTOR_TYPE,        /* bDescriptorType */
  WBVAL(HID_REPORT_DESC_SIZE),       /* wDescriptorLength */
/* Endpoint, HID Interrupt In */
  USB_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType */
  USB_ENDPOINT_IN(1),                /* bEndpointAddress */
  USB_ENDPOINT_TYPE_INTERRUPT,       /* bmAttributes */
  WBVAL(0x0020),                     /* wMaxPacketSize */
  0x08,          /* 32ms */          /* bInterval */
/* Terminator */
};


/* USB String Descriptor (optional) */
const U8 USB_StringDescriptor[] = {
/* Index 0x00: LANGID Codes */
  0x04,                              /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  WBVAL(0x0409), /* US English */    /* wLANGID */
/* Index 0x01: Manufacturer */
  (13*2 + 2),                        /* bLength (13 Char + Type + lenght) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  'K',0,
  'e',0,
  'i',0,
  'l',0,
  ' ',0,
  'S',0,
  'o',0,
  'f',0,
  't',0,
  'w',0,
  'a',0,
  'r',0,
  'e',0,
/* Index 0x02: Product */
  (16*2 + 2),                        /* bLength (16 Char + Type + lenght) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  'K',0,
  'e',0,
  'i',0,
  'l',0,
  ' ',0,
  'M',0,
  'C',0,
  'B',0,
  '1',0,
  '7',0,
  '0',0,
  '0',0,
  ' ',0,
  'H',0,
  'I',0,
  'D',0,
/* Index 0x03: Serial Number */
  (12*2 + 2),                        /* bLength (12 Char + Type + lenght) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  '0',0,                             /* allowed characters are       */
  '0',0,                             /*   0x0030 - 0x0039 ('0'..'9') */
  '0',0,                             /*   0x0041 - 0x0046 ('A'..'F') */
  '1',0,                             /*   length >= 26               */
  'A',0,
  '0',0,
  '0',0,
  '0',0,
  '0',0,
  '0',0,
  '0',0,
  '0',0,
/* Index 0x04: Interface 0, Alternate Setting 0 */
  ( 3*2 + 2),                        /* bLength (3 Char + Type + lenght) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  'H',0,
  'I',0,
  'D',0,
};
