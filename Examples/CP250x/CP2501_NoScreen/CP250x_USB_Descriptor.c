//-----------------------------------------------------------------------------
// CP250x_USB_Descriptor.c
//-----------------------------------------------------------------------------
// Copyright 2010 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Target: CP2501
//
// Tool chain: Raisonance
//
// Contains USB descriptors
//
// This file is dynamically generated by the CP250x Configuration Wizard.
// Do not edit this file.

//-----------------------------------------------------------------------------
// Header Files
//-----------------------------------------------------------------------------

#include "compiler_defs.h"
#include "CP250x_Configuration.h"

//-----------------------------------------------------------------------------
// Descriptor Declarations
//-----------------------------------------------------------------------------
code U8 HidDeviceDesc[] =
{
   18,                  // bLength
   0x01,                // bDescriptorType
   0x00,                // bcdUSB Low
   0x02,                // bcdUSB High
   0x00,                // bDeviceClass
   0x00,                // bDeviceSubClass
   0x00,                // bDeviceProtocol
   0x40,                // bMaxPacketSize0
   0xC4,                // idVendor Low
   0x10,                // idVendor High
   0xA0,                // idProduct Low
   0xEA,                // idProduct High
   0x00,                // bcdDevice Low
   0x01,                // bcdDevice High
   0x01,                // iManufacturer
   0x02,                // iProduct
   0x03,                // iSerialNumber
   0x01                 // bNumConfigurations
};

// From "USB Device Class Definition for Human Interface Devices (HID)".
// Section 7.1:
// "When a Get_Descriptor(Configuration) request is issued,
// it returns the Configuration descriptor, all Interface descriptors,
// all Endpoint descriptors, and the HID descriptor for each interface."
code U8 HidConfigDesc[] =
{
   // Configuration Descriptor
   0x09,                // Length
   0x02,                // Type
   0x22,                // Totallength (= 9+9+9+7+7) Low
   0x00,                // Totallength (= 9+9+9+7+7) High
   0x01,                // NumInterfaces
   0x01,                // bConfigurationValue
   0x00,                // iConfiguration
   0x80,                // bmAttributes
   0x32,                // MaxPower (in 2mA units)

   // Interface Descriptor
   0x09,                // bLength
   0x04,                // bDescriptorType
   0x00,                // bInterfaceNumber
   0x00,                // bAlternateSetting
   0x01,                // bNumEndpoints
   0x03,                // bInterfaceClass (3 = HID)
   0x00,                // bInterfaceSubClass
   0x00,                // bInterfaceProcotol
   0x00,                // iInterface

   // Class Descriptor
   0x09,                // bLength
   0x21,                // bDescriptorType
   0x11,                // bcdHID Low
   0x01,                // bcdHID High
   0x00,                // bCountryCode
   0x01,                // bNumDescriptors
   0x22,                // bDescriptorType
   0xF1,                // wItemLength (length of report descriptor) Low
   0x00,                // wItemLength (length of report descriptor) High

   // IN endpoint (mandatory for HID)
   // Endpoint Descriptor
   0x07,                // bLength
   0x05,                // bDescriptorType
   0x81,                // bEndpointAddress
   0x03,                // bmAttributes
   0x40,                // MaxPacketSize Low
   0x00,                // MaxPacketSize High
   0x01                 // bInterval
};

code U8 StringDesc[] =
{
   // String 1 descriptor (126 bytes) "Silicon Laboratories"
   0x2A,0x03, 'S', 0x00, 'i', 0x00, 'l', 0x00, 'i', 0x00, 'c', 0x00, 'o', 0x00, 'n', 0x00,
   ' ', 0x00, 'L', 0x00, 'a', 0x00, 'b', 0x00, 'o', 0x00, 'r', 0x00, 'a', 0x00, 't', 0x00,
   'o', 0x00, 'r', 0x00, 'i', 0x00, 'e', 0x00, 's', 0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
   0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
   0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
   0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
   0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
   0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 

   // String 2 descriptor (126 bytes) "CP250x No Screen Example"
   0x32,0x03, 'C', 0x00, 'P', 0x00, '2', 0x00, '5', 0x00, '0', 0x00, 'x', 0x00, ' ', 0x00,
   'N', 0x00, 'o', 0x00, ' ', 0x00, 'S', 0x00, 'c', 0x00, 'r', 0x00, 'e', 0x00, 'e', 0x00,
   'n', 0x00, ' ', 0x00, 'E', 0x00, 'x', 0x00, 'a', 0x00, 'm', 0x00, 'p', 0x00, 'l', 0x00,
   'e', 0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
   0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
   0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
   0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
   0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
};

// HID Report Descriptor
code U8 HidReportDesc[] =
{
   // Begin Header
   0x06, 0x00, 0xFF,                      // USAGE_PAGE (Vendor Defined Page 1)
   0x09, 0x01,                            // USAGE (Vendor Usage 1)
   0xA1, 0x01,                            // COLLECTION (Application)

   0x75, 0x08,                            // REPORT_SIZE (8)
   0x26, 0xFF, 0x00,                      // LOGICAL_MAXIMUM (255)
   0x15, 0x00,                            // LOGICAL_MINIMUM (0)

   0x85, ID_SET_RESET_DEVICE,             // REPORT_ID
   0x95, SIZE_SET_RESET_DEVICE,           //   REPORT_COUNT ()
   0x09, 0x01,                            //   USAGE (Vendor Usage 1)
   0xB1, 0x02,                            //   FEATURE (Data,Var,Abs)

   0x85, ID_GET_BL_VER,                   // REPORT_ID
   0x95, SIZE_GET_BL_VER,                 //   REPORT_COUNT ()
   0x09, 0x01,                            //   USAGE (Vendor Usage 1)
   0xB1, 0x02,                            //   FEATURE (Data,Var,Abs)

   0x85, ID_GET_APP_VER,                  // REPORT_ID
   0x95, SIZE_GET_APP_VER,                //   REPORT_COUNT ()
   0x09, 0x01,                            //   USAGE (Vendor Usage 1)
   0xB1, 0x02,                            //   FEATURE (Data,Var,Abs)

   0x85, ID_GET_SET_BL_MODE,              // Report ID
   0x95, SIZE_GET_SET_BL_MODE,            //   REPORT_COUNT ()
   0x09, 0x01,                            //   USAGE (Vendor Usage 1)
   0xB1, 0x02,                            //   FEATURE (Data,Var,Abs

   0x85, ID_GETSET_USB_CONTROL,           // REPORT_ID
   0x95, SIZE_GETSET_USB_CONTROL,         //   REPORT_COUNT ()
   0x09, 0x01,                            //   USAGE (Vendor Usage 1)
   0xB1, 0x02,                            //   FEATURE (Data,Var,Abs)

   0xC0,                                  // END_COLLECTION
   // End Header

   // Begin Touch Report Definition
   0x05, 0x0D,	                          // USAGE_PAGE (Digitizers)
   0x09, 0x04,	                          // USAGE (Touch Screen)
   0xA1, 0x01,                            // COLLECTION (Application)
   0x85, ID_TOUCH_DATA,                   //   REPORT_ID (Touch)
   0x09, 0x22,                            //   USAGE (Finger)
   0xA1, 0x02,                            //     COLLECTION (Logical)
   0x09, 0x42,                            //       USAGE (Tip Switch)
   0x15, 0x00,                            //       LOGICAL_MINIMUM (0)
   0x25, 0x01,                            //       LOGICAL_MAXIMUM (1)
   0x75, 0x01,                            //       REPORT_SIZE (1)
   0x95, 0x01,                            //       REPORT_COUNT (1)
   0x81, 0x02,                            //       INPUT (Data,Var,Abs)
   0x09, 0x32,	                           //       USAGE (In Range)
   0x81, 0x02,                            //       INPUT (Data,Var,Abs)
   0x09, 0x47,	                           //       USAGE (Confidence)
   0x81, 0x02,                            //       INPUT (Data,Var,Abs)
   0x95, 0x05,                            //       REPORT_COUNT (5)
   0x81, 0x03,                            //       INPUT (Cnst,Ary,Abs)
   0x75, 0x08,                            //       REPORT_SIZE (8)
   0x09, 0x51,                            //       USAGE (Contact Identifier)
   0x95, 0x01,                            //       REPORT_COUNT (1)
   0x81, 0x02,                            //       INPUT (Data,Var,Abs)
   0x05, 0x01,                            //       USAGE_PAGE (Generic Desktop)
   0x65, 0x11,                            //       UNITS (SI Linear : Distance)
   0x55, 0x0F,                            //       UNIT_EXPONENT (-1)
   0x35, 0x00,                            //       PHYSICAL MINIMUM (0)
   0x46, 0x72, 0x01,                      //       PHYSICAL MAXIMUM (370)
   0x26, X_RES_LSB, X_RES_MSB,            //       LOGICAL_MAXIMUM (1280)
   0x75, 0x10,                            //       REPORT_SIZE (16)
   0x09, 0x30,                            //       USAGE (X)
   0x81, 0x02,                            //       INPUT (Data,Var,Abs)
   0x46, 0x31, 0x01,                      //       PHYSICAL MAXIMUM (305)
   0x26, Y_RES_LSB, Y_RES_MSB,            //       LOGICAL_MAXIMUM (1024)
   0x09, 0x31,                            //       USAGE (Y)
   0x81, 0x02,                            //       INPUT (Data,Var,Abs)
/*
   0x09, 0x48,                            //       USAGE (Width)
   0x46, 0xAD, 0x00,                      //       PHYSICAL MAXIMUM (173)
   0x26, 0x32, 0x00,                      //       LOGICAL_MAXIMUM (50)
   0x81, 0x02,                            //       INPUT (Data,Var,Abs)
   0x09, 0x49,                            //       USAGE (Height)
   0x46, 0xA8, 0x00,                      //       PHYSICAL MAXIMUM (168)
   0x26, 0x32, 0x00,                      //       LOGICAL_MAXIMUM (50)
   0x81, 0x02,                            //       INPUT (Data,Var,Abs)

/*
   0x09, 0x30,                            //       USAGE (Pressure)
   0x65, 0x00,                            //       UNITS (None)
   0x45, 0x00,                            //       PHYSICAL MAXIMUM (0)
   0x26, 0xFF, 0x7F,                      //       LOGICAL_MAXIMUM (100)
   0x81, 0x02,                            //       INPUT (Data,Var,Abs)
*/
   0xC0,                                  //     END_COLLECTION
   0x05, 0x0D,	                          //     USAGE_PAGE (Digitizers)
   0x85, ID_GET_TOUCH_MAX_COUNT,          //     REPORT_ID (Feature)
   0x95, 0x01,                            //     REPORT_COUNT (1)
   0x75, 0x08,                            //     REPORT_SIZE (8)
   0x09, 0x55,                            //     USAGE(Maximum Count)
   0x25, 0x02,                            //     LOGICAL_MAXIMUM (2)
   0xB1, 0x02,                            //     FEATURE (Data,Var,Abs)
   0xC0,                                  //   END_COLLECTION

   0x09, 0x0E,                            //   USAGE (Device Configuration)
   0xa1, 0x01,                            //   COLLECTION (Application)
   0x85, ID_GETSET_TOUCH_CONFIGURATION,   //     REPORT_ID (Configuration)
   0x09, 0x23,                            //     USAGE (Device Settings)
   0xa1, 0x02,                            //     COLLECTION (Logical)
   0x09, 0x52,                            //       USAGE (Device Mode)
   0x09, 0x53,                            //       USAGE (Device Identifier)
   0x15, 0x00,                            //       LOGICAL_MINIMUM (0)
   0x25, 0x0A,                            //       LOGICAL_MAXIMUM (10)
   0x75, 0x08,                            //       REPORT_SIZE (8)
   0x95, SIZE_GETSET_TOUCH_CONFIGURATION, //       REPORT_COUNT (2)
   0xb1, 0x02,                            //       FEATURE (Data,Var,Abs)
   0xc0,                                  //     END_COLLECTION
   0xc0,                                  //   END_COLLECTION
   // End Touch Report Definition


   // Begin Mouse Report Definition
   0x05, 0x01,                         // USAGE_PAGE (Generic Desktop)
   0x09, 0x02,                         // USAGE (Mouse)
   0xa1, 0x01,                         //   COLLECTION (Application)
   0x09, 0x01,                         //   USAGE (Pointer)
   0xa1, 0x00,                         //     COLLECTION (Physical)
   0x85, ID_MOUSE_DATA,                //       REPORT_ID (Touch)
   0x05, 0x09,                         //       USAGE_PAGE (Button)
   0x19, 0x01,                         //         USAGE_MINIMUM (Button 1)
   0x29, 0x02,                         //         USAGE_MAXIMUM (Button 2)
   0x15, 0x00,                         //         LOGICAL_MINIMUM (0)
   0x25, 0x01,                         //         LOGICAL_MAXIMUM (1)
   0x95, 0x02,                         //         REPORT_COUNT (2)
   0x75, 0x01,                         //         REPORT_SIZE (1)
   0x81, 0x02,                         //         INPUT (Data,Variable,Absolute)
   0x95, 0x01,                         //         REPORT_COUNT (1)
   0x75, 0x06,                         //         REPORT_SIZE (6)
   0x81, 0x01,                         //         INPUT (Constant)
   0x05, 0x01,                         //         USAGE_PAGE (Generic Desktop)
   0x65, 0x11,                         //         UNITS (SI Linear : Distance)
   0x55, 0x0F,                         //         UNIT_EXPONENT (-1)
   0x09, 0x30,                         //         USAGE (X)
   0x26, X_RES_LSB, X_RES_MSB,         //         LOGICAL_MAXIMUM (1280)
   0x35, 0x00,                         //         PHYSICAL MINIMUM (0)
   0x46, 0x72, 0x01,                   //         PHYSICAL MAXIMUM (370)
   0x75, 0x10,                         //         REPORT_SIZE (16)
   0x95, 0x01,                         //         REPORT_COUNT (1)
   0x81, 0x02,                         //         INPUT (Data,Variable, Absolute)
   0x09, 0x31,                         //         USAGE (Y)
   0x26, Y_RES_LSB, Y_RES_MSB,         //         LOGICAL_MAXIMUM (1024)
   0x35, 0x00,                         //         PHYSICAL MINIMUM (305)
   0x46, 0x31, 0x01,                   //         PHYSICAL MAXIMUM (302)
   0x81, 0x02,                         //         INPUT (Data,Variable, Absolute)
   0xc0,                               //       END_COLLECTION
   0xc0                                //     END_COLLECTION
   // End Mouse Report Definition


};

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------