// USBDESC_H

#pragma once

#define WORD_TO_BYTE(x) ((x)&0xFF),(((x)>>8)&0xFF)

#define USB_BUS_POWER	0x40

// USB MAX Power 500mA
#define USB_MAX_POWER	0xFA

////////////////
// Virtual Com
///////////////

#define VIRTUAL_COM_PORT_DATA_SIZE              64
#define VIRTUAL_COM_PORT_INT_SIZE               16

#define VIRTUAL_COM_PORT_SIZ_DEVICE_DESC        18
#define VIRTUAL_COM_PORT_SIZ_CONFIG_DESC        67
#define VIRTUAL_COM_PORT_SIZ_STRING_LANGID      4
#define VIRTUAL_COM_PORT_SIZ_STRING_VENDOR      48
#define VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT     50
#define VIRTUAL_COM_PORT_SIZ_STRING_SERIAL      26

//=====================================================================
//
// MAXIMUM REPORT_BYTES 255(0xFF)


/////////////////
// HID
/////////////////

#define HID_OUTPUT_REPORT_BYTES      (64)	// PC -> EVM
#define HID_INPUT_REPORT_BYTES       (64)	// PC <- EVM
#define HID_FEATURE_REPORT_BYTES     (1)

#define USB_HID_IN_REPORT_ID		(1)
#define USB_HID_OUT_REPORT_ID		(2)
//
//=====================================================================

//====================================================================
// USB Standard Request Code
// bRequest
//
#define REQUEST_CODE_GET_STATUS			0x00
#define REQUEST_CODE_CLEAR_FEATURE		0x01
#define REQUEST_CODE_SET_FEATURE		0x03
#define REQUEST_CODE_SET_ADDRESS		0x05
#define REQUEST_CODE_GET_DESCRIPTOR		0x06
#define REQUEST_CODE_SET_DESCRIPTOR		0x07
#define REQUEST_CODE_GET_CONFIGURATION	0x08
#define REQUEST_CODE_SET_CONFIGURATION	0x09
#define REQUEST_CODE_GET_INTERFACE		0x0A
#define REQUEST_CODE_SET_INTERFACE		0x0B
#define REQUEST_CODE_SYNCH_FRAME		0x0C
#define REQUEST_CODE_SET_SEL			0x30
#define REQUEST_CODE_ISOCHRONOUS_DELAY	0x31
//
//====================================================================


//====================================================================
// USB Descriptor Type
//
#define DESCRIPTOR_TYPE_DEVICE							0x01
#define DESCRIPTOR_TYPE_CONFIGURATION					0x02
#define DESCRIPTOR_TYPE_STRING							0x03
#define DESCRIPTOR_TYPE_INTERFACE						0x04
#define DESCRIPTOR_TYPE_ENDPOINT						0x05
#define DESCRIPTOR_TYPE_DEVICE_QUALIFIER				0x06
#define DESCRIPTOR_TYPE_OTHER_SPEED_CONFIGURATION		0x07
#define DESCRIPTOR_TYPE_INTERFACE_POWER					0x08
#define DESCRIPTOR_TYPE_OTG								0x09
#define DESCRIPTOR_TYPE_DEBUG							0x0A
#define DESCRIPTOR_TYPE_INTERFACE_ASSOCIATION			0x0B
#define DESCRIPTOR_TYPE_SECURITY						0x0C
#define DESCRIPTOR_TYPE_KEY								0x0D
#define DESCRIPTOR_TYPE_ENCRYPTION						0x0E
#define DESCRIPTOR_TYPE_BOS								0x0F
#define DESCRIPTOR_TYPE_DEVICE_CAPABILITY				0x10
#define DESCRIPTOR_TYPE_WIRELESS_ENDPOINT_COMPANION		0x11
#define DESCRIPTOR_TYPE_SUPERSPEED_ENDOPOINT_COMPANION	0x30
//
//=====================================================================


//====================================================================
// USB Device Class Code
//
#define DEVICE_CLASS_RESERVED              0x00
#define DEVICE_CLASS_AUDIO                 0x01
#define DEVICE_CLASS_COMMUNICATIONS        0x02
#define DEVICE_CLASS_HUMAN_INTERFACE       0x03
#define DEVICE_CLASS_MONITOR               0x04
#define DEVICE_CLASS_PHYSICAL_INTERFACE    0x05
#define DEVICE_CLASS_POWER                 0x06
#define DEVICE_CLASS_PRINTER               0x07
#define DEVICE_CLASS_STORAGE               0x08
#define DEVICE_CLASS_HUB                   0x09
#define DEVICE_CLASS_MISCELLANEOUS         0xEF
#define DEVICE_CLASS_VENDOR_SPECIFIC       0xFF
//
//=====================================================================


//=====================================================================
// USB Device Descriptor
// 18 Bytes
//
typedef struct _USB_DEVICE_DESCRIPTOR {
	U8  bLength;
	U8  bDescriptorType;
	__attribute__ ((packed)) U16 bcdUSB;
	U8  bDeviceClass;
	U8  bDeviceSubClass;
	U8  bDeviceProtocol;
	U8  bMaxPacketSize0;
	__attribute__ ((packed)) U16 idVendor;
	__attribute__ ((packed)) U16 idProduct;
	__attribute__ ((packed)) U16 bcdDevice;
	U8  iManufacturer;
	U8  iProduct;
	U8  iSerialNumber;
	U8  bNumConfigurations;
} USB_DEVICE_DESCRIPTOR;

#define DESCRIPTOR_SIZE_DEVICE (sizeof(USB_DEVICE_DESCRIPTOR))
//=====================================================================


//=====================================================================
//
// USB Configuration Descriptor
// 9 Bytes
//
typedef struct _USB_CONFIGURATION_DESCRIPTOR{
	U8  bLength;
	U8  bDescriptorType;
	__attribute__ ((packed)) U16 wTotalLength;
	U8  bNumInterfaces;
	U8  bConfigurationValue;
	U8  iConfiguration;
	U8  bmAttributes;
	U8  bMaxPower;
} USB_CONFIGURATION_DESCRIPTOR;

#define DESCRIPTOR_SIZE_CONFIGURATION (sizeof(USB_CONFIGURATION_DESCRIPTOR))
//=====================================================================


//=====================================================================
//
// USB Interface Descriptor
// 9 Bytes
//
typedef struct _USB_INTERFACE_DESCRIPTOR {
	U8  bLength;
	U8  bDescriptorType;
	U8  bInterfaceNumber;
	U8  bAlternateSetting;
	U8  bNumEndpoints;
	U8  bInterfaceClass;
	U8  bInterfaceSubClass;
	U8  bInterfaceProtocol;
	U8  iInterface;
} USB_INTERFACE_DESCRIPTOR;

#define DESCRIPTOR_SIZE_INTERFACE (sizeof(USB_INTERFACE_DESCRIPTOR))
//=====================================================================


//=====================================================================
//
// USB EndPoint Descriptor
// 7 Bytes
//
typedef struct _USB_ENDPOINT_DESCRIPTOR {
	U8  bLength;
	U8  bDescriptorType;
	U8  bEndpointAddress;
	U8  bmAttributes;
	__attribute__ ((packed)) U16 wMaxPacketSize;
	U8  bInterval;
} USB_ENDPOINT_DESCRIPTOR;

#define DESCRIPTOR_SIZE_ENDPOINT (sizeof(USB_ENDPOINT_DESCRIPTOR))
//=====================================================================



//=====================================================================
//
// USB STRING Descriptor
// 4 Bytes
//
typedef struct _USB_STRING_DESCRIPTOR {
  U8  bLength;
  U8  bDescriptorType;
  __attribute__ ((packed)) U16 bString;
} USB_STRING_DESCRIPTOR;

#define DESCRIPTOR_SIZE_STRING	(sizeof(USB_STRING_DESCRIPTOR))
//=====================================================================

