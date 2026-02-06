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

#define GPIO_BASE	0xffff3000

#define R_GPDIR(ch) ((volatile unsigned int*)(GPIO_BASE+(0x40*(ch))))

// Port Direction Output Mode Setting Registers
#define R_GPODIR(ch) ((volatile unsigned int*)(GPIO_BASE+(0x40*(ch))))

// Port Direction Input Mode Setting Registers
#define R_GPIDIR(ch) ((volatile unsigned int*)(GPIO_BASE+4+(0x40*(ch))))

//Port Output Data Level Registers
#define R_GPOLEV(ch) ((volatile unsigned int*)(GPIO_BASE+8+(0x40*(ch))))

// Port Output Data Registers
#define R_GPDOUT(ch) ((volatile unsigned char*)(GPIO_BASE+8+(0x40*(ch))))
 
//Port Output Data High Level Setting Registers
#define R_GPOHIGH(ch) ((volatile unsigned int*)(GPIO_BASE+8+(0x40*(ch))))

//Port Output Data Low Level Setting Registers
#define R_GPOLOW(ch) ((volatile unsigned int*)(GPIO_BASE+0xc+(0x40*(ch))))

//Port Input Data Level Registers
#define R_GPILEV(ch) ((volatile unsigned int*)(GPIO_BASE+0x10+(0x40*(ch))))

//Port Pull-up Enable Registers
#define R_GPPUEN(ch) ((volatile unsigned int*)(GPIO_BASE+0x14+(0x40*(ch))))

//Port Pull-down Enable Registers
#define R_GPPDEN(ch) ((volatile unsigned int*)(GPIO_BASE+0x18+(0x40*(ch))))

//Port Rising-Edge Detect Registers
#define R_GPRED(ch) ((volatile unsigned int*)(GPIO_BASE+0x1c+(0x40*(ch))))

//Port Falling-Edge Detect Registers
#define R_GPFED(ch) ((volatile unsigned int*)(GPIO_BASE+0x20+(0x40*(ch))))

//Port Edge Status Registers
#define R_GPEDS(ch) ((volatile unsigned int*)(GPIO_BASE+0x24+(0x40*(ch))))

//Port Open Drain Mode Control Registers
#define R_GPODM(ch) ((volatile unsigned int*)(GPIO_BASE+0x28+(0x40*(ch))))

//Port schmitt input enable registers
#define R_GPSCHMT(ch) ((volatile unsigned int*)(GPIO_BASE+0x2c+(0x40*(ch))))

// Port Interrupt Request Mode Registers
#define R_GPIRQMODE(ch) ((volatile unsigned int*)(GPIO_BASE+0x30+(0x40*(ch))))

// Port Interrupt Request Enable Registers
#define R_GPIRQEN(ch) ((volatile unsigned int*)(GPIO_BASE+0x34+(0x40*(ch))))

// Port Interrupt Request Enable Registers
#define R_GPPATHSEL(ch) ((volatile unsigned int*)(GPIO_BASE+0x38+(0x40*(ch))))

#define R_PAF(N) ((volatile unsigned int*)(0x80043400+(N*4)))

//======================================================================================================================
#define F_PAF0_0_TIMER0_PWM	(0 << 0)
#define F_PAF0_0_GP0				(3 << 0)

#define F_PAF0_1_UART2_RX       (0 << 2)
#define F_PAF0_1_TIMER0_CAP	(1 << 2)
#define F_PAF0_1_GP1				(3 << 2)

#define F_PAF0_2_UART2_TX		(0 << 4)
#define F_PAF0_2_GP2				(3 << 4)

#define F_PAF0_3_UART3_RX		(0 << 6)
#define F_PAF0_3_TIMER2_CAP	(1 << 6)
#define F_PAF0_3_GP3				(3 << 6)

#define F_PAF0_4_UART3_TX		(0 << 8)
#define F_PAF0_4_TIMER1_CAP	(1 << 8)
#define F_PAF0_4_GP4				(3 << 8)

#define F_PAF0_5_UART0_RX		(0 <<10)
#define F_PAF0_5_TWI0_SDA		(1 <<10)
#define F_PAF0_5_GP5				(3 <<10)

#define F_PAF0_6_UART0_TX		(0 <<12)
#define F_PAF0_6_TWI0_SCL		(1 <<12)
#define F_PAF0_6_GP6				(3 <<12)

#define F_PAF0_7_TIMER1_PWM	(0 <<14)
#define F_PAF0_7_I2S_LRCLK		(1 <<14)
#define F_PAF0_7_GP7				(3 <<14)
//======================================================================================================================

//======================================================================================================================
#define F_PAF1_0_SF_CS				(0 << 0)
#define F_PAF1_0_SPI0_CS			(1 << 0)
#define F_PAF1_0_GP0				(3 << 0)

#define F_PAF1_1_SF_DQ1			(0 << 2)
#define F_PAF1_1_SPI0_DO			(1 << 2)
#define F_PAF1_1_GP1				(3 << 2)

#define F_PAF1_2_SF_DQ2			(0 << 4)
#define F_PAF1_2_TWI1_SDA		(1 << 4)
#define F_PAF1_2_TIMER3_CAP		(2 << 4)
#define F_PAF1_2_GP2				(3 << 4)

#define F_PAF1_3_SF_DQ0			(0 << 6)
#define F_PAF1_3_SPI0_DI			(1 << 6)
#define F_PAF1_3_GP3				(3 << 6)

#define F_PAF1_4_SF_CLK			(0 << 8)
#define F_PAF1_4_SPI0_CLK		(1 << 8)
#define F_PAF1_4_TIMER3_PWM	(2 << 8)
#define F_PAF1_4_GP4				(3 << 8)

#define F_PAF1_5_SF_DQ3			(0 <<10)
#define F_PAF1_5_TWI1_SCL			(1 <<10)
#define F_PAF1_5_GP5				(3 <<10)

#define F_PAF1_6_UART1_TX		(0 <<12)
#define F_PAF1_6_SPI1_CS			(1 <<12)
#define F_PAF1_6_GP6				(3 <<12)

#define F_PAF1_7_UART1_RX		(0 <<14)
#define F_PAF1_7_SPI1_SDO		(1 <<14)
#define F_PAF1_7_GP7				(3 <<14)
//======================================================================================================================

//======================================================================================================================
#define F_PAF2_0_UART4_TX		(0 << 0)
#define F_PAF2_0_SPI1_SDI			(1 << 0)
#define F_PAF2_0_GP0				(3 << 0)

#define F_PAF2_1_UART4_RX		(0 << 2)
#define F_PAF2_1_SPI1_CLK		(1 << 2)
#define F_PAF2_1_GP1				(3 << 2)

#define F_PAF2_2_UART5_RX		(0 << 4)
#define F_PAF2_2_TIMER4_CAP	(1 << 4)
#define F_PAF2_2_GP2				(3 << 4)

#define F_PAF2_3_UART5_TX		(0 << 6)
#define F_PAF2_3_GP3				(3 << 6)

//======================================================================================================================

//======================================================================================================================
#define F_PAF3_0_SWD_SCK		(0 << 0)
#define F_PAF3_0_UART5_RX		(1 << 0)
#define F_PAF3_0_GP0				(3 << 0)

#define F_PAF3_1_SWD_SDA		(0 << 2)
#define F_PAF3_1_UART5_TX		(1 << 2)
#define F_PAF3_1_GP1				(3 << 2)

//======================================================================================================================

//======================================================================================================================
    
#define F_PAF4_0_SPWM_N0 		(0 << 0)		
#define F_PAF4_0_TIMER2_PWM	(1 << 0)		
#define F_PAF4_0_I2S_SDO			(2 << 0)
#define F_PAF4_0_GP0				(3 << 0)

#define F_PAF4_1_SPWM_P0		(0<<2)
#define F_PAF4_1_I2S_SCLK		(2<<2)
#define F_PAF4_1_GP1				(3<<2)

#define F_PAF4_2_SPWM_N1		(0<<4)
#define F_PAF4_2_GP2				(3<<4)

#define F_PAF4_3_SPWM_P1	 	(0<<6)
#define F_PAF4_3_TIMER4_PWM	(1<<6)
#define F_PAF4_3_I2S_SDI			(2<<6)
#define F_PAF4_3_GP3				(3<<6)

//======================================================================================================================

//======================================================================================================================

#define F_PAF5_0_UART0_TX		(0<<0)
#define F_PAF5_0_GP0				(3<<0)

#define F_PAF5_1_UART0_RX		(0<<2)
#define F_PAF5_1_GP1			(3<<2)

#define F_PAF5_2_GP2			(3<<4)

#define F_PAF5_3_GP3			(3<<6)

#define F_PAF5_4_SPI1_CS			(0<<8)
#define F_PAF5_4_GP4			(3<<8)

#define F_PAF5_5_SPI1_SDO			(0<<10)
#define F_PAF5_5_GP5			(3<<10)

#define F_PAF5_6_SPI1_SDI			(0<<12)
#define F_PAF5_6_GP6				(3<<12)

#define F_PAF5_7_SPI1_CLK		(0<<14)
#define F_PAF5_7_GP7			(3<<14)
//======================================================================================================================

//======================================================================================================================

#define F_PAF6_0_GP0			(3<<0)

#define F_PAF6_1_TWI1_SDA				(0<<2)
#define F_PAF6_1_GP1			(3<<2)

#define F_PAF6_2_TWI1_SCL				(0<<4)
#define F_PAF6_2_GP2			(3<<4)

//======================================================================================================================

//======================================================================================================================

#define F_PAF7_0_SWD_SDA	(0<<0)
#define F_PAF7_0_UART1_RX	(1<<0)
#define F_PAF7_0_GP0			(3<<0)

#define F_PAF7_1_SWD_SCK	(0<<2)
#define F_PAF7_1_UART1_TX	(1<<2)
#define F_PAF7_1_GP1			(3<<2)

//======================================================================================================================

//======================================================================================================================

#define F_PAF8_0_GP0			(3<<0)
#define F_PAF8_1_GP1			(3<<2)
#define F_PAF8_2_GP2			(3<<4)
#define F_PAF8_3_GP3			(3<<6)
#define F_PAF8_4_GP4			(3<<8)
#define F_PAF8_5_GP5			(3<<10)
#define F_PAF8_6_GP6			(3<<12)
#define F_PAF8_7_GP7			(3<<14)

//======================================================================================================================
