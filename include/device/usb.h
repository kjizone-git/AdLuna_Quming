/*****************************************************************************
*
* Copyright (C) 2014      Advanced Digital Chips, Inc. All Rights Reserved.
*						http://www.adc.co.kr
*
* THIS SOFTWARE IS PROVIDED BY ADCHIPS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
* EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ADCHIPS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE
*
*****************************************************************************/

#pragma once

/* USB Controller */
#define __USBBASE           		0xA0001800 
#define __USBFA_REG				(__USBBASE + 0x00)
#define __USBPM_REG			(__USBBASE + 0x04)
#define __USBEI_REG				(__USBBASE + 0x08)
#define __USBUI_REG				(__USBBASE + 0x10)
#define __USBEIE_REG			(__USBBASE + 0x14)
#define __USBUIE_REG			(__USBBASE + 0x18)
#define __USBLBFN_REG			(__USBBASE + 0x1C)
#define __USBHBFN_REG		(__USBBASE + 0x20)
#define __USBIND_REG			(__USBBASE + 0x24)
#define __USBMAXP_REG		(__USBBASE + 0x28)
#define __USBE0C_REG			(__USBBASE + 0x2C)
#define __USBIC1_REG			(__USBBASE + 0x2C)
#define __USBIC2_REG			(__USBBASE + 0x30)
#define __USBOC1_REG			(__USBBASE + 0x38)
#define __USBOC2_REG			(__USBBASE + 0x3C)
#define __USBLBOWC_REG		(__USBBASE + 0x40)
#define __USBHBOWC_REG	(__USBBASE + 0x44)
#define __USBEP0D_REG		(__USBBASE + 0x48)
#define __USBEP1D_REG		(__USBBASE + 0x4C)
#define __USBEP2D_REG		(__USBBASE + 0x50)
#define __USBEP3D_REG		(__USBBASE + 0x54)
#define __USBEP4D_REG		(__USBBASE + 0x58)

//----------------------------------
// Interrupt Register Bit Masks
//----------------------------------
#define EP0_IRQ			    0x01
#define EP1_IRQ			    0x02
#define EP2_IRQ			    0x04
#define EP3_IRQ			    0x08
#define EP4_IRQ			    0x10

#define DMA_DONE			0x10
#define SOF_DONE			0x20

#define USB_SUSPEND_IRQ     0x01
#define USB_RESUME_IRQ      0x02
#define USB_RESET_IRQ       0x04

#define USB_RESET_DONE		0x40

#define EP0_LEN 			16		// EP0 MaxPktSize 
#define EP1_LEN 		    64	    // EP1 MaxPktSize 
#define EP2_LEN 			64		// EP2 MaxPktSize 
#define EP3_LEN 			16	    // EP3 MaxPktSize 
#define EP4_LEN 			16	    // EP4 MaxPktSize 
	
// R_USBFA Bit Definitions
#define USBFA_ADDUP		(1<<7)
// #define USBFA_FUNADD	

// R_USBPM Bit Definitions
#define USBPM_RST		(1<<3)	// Reset Bit
#define USBPM_RSM		(1<<2)	// Resume Bit
#define USBPM_SSPD_MD	(1<<1)	// Suspend Mode Bit
#define USBPM_SSPD_EA	(1<<0)	// Enable Suspend Mode Bit

// R_USBEPI Bit Definitions
#define USBEPI_EP4		(1<<4)	// EP4 Interrupt Bit
#define USBEPI_EP3		(1<<3)	// EP3 Interrupt Bit
#define USBEPI_EP2		(1<<2)	// EP2 Interrupt Bit
#define USBEPI_EP1		(1<<1)	// EP1 Interrupt Bit
#define USBEPI_EP0		(1<<0)	// EP0 Interrupt Bit

// R_USBINT Bit Definitions
#define USBINT_RST		(1<<2)	// Reset Interrupt Bit
#define USBINT_RSM		(1<<1)	// Resume Interrupt Bit
#define USBINT_SSPD		(1<<0)	// Suspend Interrupt Bit

// R_USBPIEN Bit Definitions
#define USBEPIEN_EP4	(1<<4)	// Endpoint 4 Interrupt Enable Bit
#define USBEPIEN_EP3	(1<<3)	// Endpoint 3 Interrupt Enable Bit
#define USBEPIEN_EP2	(1<<2)	// Endpoint 2 Interrupt Enable Bit
#define USBEPIEN_EP1	(1<<1)	// Endpoint 1 Interrupt Enable Bit
#define USBEPIEN_EP0	(1<<0)	// Endpoint 0 Interrupt Enable Bit

// R_USBINTEN Bit Definitions
#define USBINTEN_RST	(1<<2)	// Reset Interrupt Enable Bit
#define USBINTEN_SSPD	(1<<0)	// Suspend Interrupt Enable Bit

// R_USBIND Bit Definitions
#define USBIND_EP4		(4<<0)	// Index Register Set EP4
#define USBIND_EP3		(3<<0)	// Index Register Set EP3
#define USBIND_EP2		(2<<0)	// Index Register Set EP2
#define USBIND_EP1		(1<<0)	// Index Register Set EP1
#define USBIND_EP0		(0<<0)	// Index Register Set EP0

// R_USBMP Bit Definitions
#define USBMP_64		(8<<0)	// Max FIFO Size 64 Byte
#define USBMP_32		(4<<0)	// Max FIFO Size 32 Byte
#define USBMP_16		(2<<0)	// Max FIFO Size 16 Byte
#define USBMP_8		(1<<0)	// Max FIFO Size 8 Byte

// R_USBEP0C Bit Definitions
#define USBEP0C_SUEC			(1<<7)	// EP0 Set Up End Clear Bit
#define USBEP0C_PRC			(1<<6)	// EP0 Out Packet Ready Clear Bit
#define USBEP0C_SDSTALL	(1<<5)	// EP0 Send Stall Bit
#define USBEP0C_STED			(1<<4)	// EP0 Setup End Bit
#define USBEP0C_DED			(1<<3)	// EP0 Data End Bit
#define USBEP0C_STSTAL		(1<<2)	// EP0 Sent Stall Bit
#define USBEP0C_IPR				(1<<1)	// EP0 In Packet Ready Bit
#define USBEP0C_OPR			(1<<0)	// EP0 Out Packet Ready Bit

// R_USBIC1 Bit Definitions
#define USBIC1_CDT		(1<<6)	// In Control 1 Clear Data Toggle Bit
#define USBIC1_STSTAL	(1<<5)	// In Control 1 Sent Stall Bit
#define USBIC1_SDSTAL	(1<<4)	// In Control 1 Send Stall Bit
#define USBIC1_FFLU		(1<<3)	// In Control 1 FIFO Flush Bit
#define USBIC1_FNE		(1<<1)	// In Control 1 FIFO Not Empty Bit
#define USBIC1_IPR			(1<<0)	// In Control 1 In Packet Ready Bit

// R_USBIC2 Bit Definitions
#define USBIC2_ASET		(1<<7)	// In Control 2 Auto Set Bit
#define USBIC2_MODIN	(1<<5)	// In Control 2 Mode In Bit

// R_USBOC1 Bit Definitions
#define USBOC1_CDT			(1<<7)	// Out Control 1 Clear Data Toggle Bit
#define USBOC1_STSTALL	(1<<6)	// Out Control 1 Sent Stall Bit
#define USBOC1_SDSTALL	(1<<5)	// Out Control 1 Send Stall Bit
#define USBOC1_FFLU			(1<<4)	// Out Control 1 FIFO Flush Bit
#define USBOC1_ERR			(1<<3)	// Out Control 1 Data Error Bit
#define USBOC1_FFUL			(1<<1)	// Out Control 1 FIFO Full Bit
#define USBOC1_OPR			(1<<0)	// Out Control 1 Out Packet Ready Bit

// R_USBOC2 Bit Definitions
#define USBOC2_ACLR		(1<<7)	// Out Control 2 Auto Clear Bit
//
//-----//-----//-----//-----//-----//-----//-----//-----//-----//-----	
	
#define MAXIFCNUM			8		// Maximum of 8 interfaces

#define DEV_LEN		18			// Device Descriptor Length
#define CFG_LEN	    39		    // Configuration Descriptor Length

// CDC Request
#define SEND_ENCAPSULATED_COMMAND   0x00
#define GET_ENCAPSULATED_RESPONSE   0x01
#define SET_COMM_FEATURE            0x02
#define GET_COMM_FEATURE            0x03
#define CLEAR_COMM_FEATURE          0x04
#define SET_LINE_CODING             0x20
#define GET_LINE_CODING             0x21
#define SET_CONTROL_LINE_STATE      0x22
#define SEND_BREAK                  0x23
	
	
void ep0_isr();
void ep4_isr();
void usb_reset(void);
void usb_resume(void);
void usb_suspend(void);

int write_usb(BYTE *data, int len); 
int read_usb(BYTE *xmit_data);//buf size must be bigger than 64

void usb_set_description(BYTE* cfg,BYTE* dev);
//void usb_set_hid_description(BYTE* cfg,BYTE* dev, BYTE* hid,BYTE* string);


typedef enum{
	USB_BULK_MODE = 0,
	USB_VIRTUAL_COM_MODE,
	USB_HID_MODE,	
}USB_MODE;

void usb_init(USB_MODE mode);


