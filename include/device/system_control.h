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


#define R_SYSCON_GLOCK			((volatile unsigned int*)0x80023C00)
#define R_SYSCON_WREN			((volatile unsigned int*)0x80023C04)
#define R_SYSCON_HALT			((volatile unsigned int*)0x80023C08)
#define R_SYSCON_HALT_STATUS  ((volatile unsigned int*)0x80023C0c)
#define R_SYSCON_INT_WAKEUP	((volatile unsigned int*)0x80023C10)
#define R_SYSCON_EVENT_WAKEUP	((volatile unsigned int*)0x80023C14)
#define R_SYSCON_PMC_STATUS	((volatile unsigned int*)0x80023C18)
#define R_SYSCON_OSC	((volatile unsigned int*)0x80023C1c)
#define R_SYSCON_CLKCON  ((volatile unsigned int*)0x80023C20)
#define R_SYSCON_PLLCON		((volatile unsigned int*)0x80023C24)
#define R_SYSCON_CLKDCON	((volatile unsigned int*)0x80023C28)
#define R_SYSCON_HCLKEN	((volatile unsigned int*)0x80023C2c)
#define R_SYSCON_PCLKEN	((volatile unsigned int*)0x80023C30)
#define R_SYSCON_USBPHYCON	((volatile unsigned int*)0x80023C34)
#define R_SYSCON_BODCONF	((volatile unsigned int*)0x80023C38)
#define R_SYSCON_HCLKDIV	((volatile unsigned int*)0x80023C3c)
#define R_SYSCON_CLK16DIV	((volatile unsigned int*)0x80023C40)
#define R_SYSCON_SCR	((volatile unsigned int*)0x80023C4c)
#define R_SYSCON_KVR	((volatile unsigned int*)0x80023C50)
#define R_SYSCON_PSR	((volatile unsigned int*)0x80023C54)
#define R_SYSCON_SWRUSC	((volatile unsigned int*)0x80023C58)
#define R_SYSCON_DMARSR	((volatile unsigned int*)0x80023C5c)
#define R_SYSCON_DFSCON	((volatile unsigned int*)0x80023C60)
#define R_SYSCON_PERI0	((volatile unsigned int*)0x80023C64)
#define R_SYSCON_PERI1	((volatile unsigned int*)0x80023C68)
#define R_SYSCON_PERI2	((volatile unsigned int*)0x80023C6c)
#define R_SYSCON_PERI3	((volatile unsigned int*)0x80023C70)
#define R_SYSCON_SPKCON	((volatile unsigned int*)0x80023C74)
#define R_SYSCON_FLASHSIZE	((volatile unsigned int*)0x80023C78)


//======================================================================================================================


#define SYSCON_REG_WRITE(wren_bit,addr,data) do{\
	*R_SYSCON_GLOCK = 0xe5511acc;\
	*R_SYSCON_WREN= 1<<wren_bit;\
	*(vU32*)addr = data;\
	*R_SYSCON_WREN=0;\
	*R_SYSCON_GLOCK  = 0;\
	}while(0);

typedef enum enum_SYSCON_WREN_BIT
{
	SYSCON_WREN_BIT_HALT = 0,
	SYSCON_WREN_BIT_RESV1,
	SYSCON_WREN_BIT_INT_WAKEUP,
	SYSCON_WREN_BIT_OSC_STABLE,

	SYSCON_WREN_BIT_CLKCON = 8,
	SYSCON_WREN_BIT_PLL,
	SYSCON_WREN_BIT_ADD_CLOCK_DIV,
	SYSCON_WREN_BIT_HCLK,
	SYSCON_WREN_BIT_PCLK,
	SYSCON_WREN_BIT_USB_PHY,
	SYSCON_WREN_BIT_BOD,
	SYSCON_WREN_BIT_HCLK_DIV,
	SYSCON_WREN_BIT_CLK16, //16

	SYSCON_WREN_BIT_PINSEL = 21,
	SYSCON_WREN_BIT_SW_RESET,
	SYSCON_WREN_BIT_DMA,
	SYSCON_WREN_BIT_DFS,
	SYSCON_WREN_BIT_PERI0,
	SYSCON_WREN_BIT_PERI1,
	SYSCON_WREN_BIT_PERI2,
	SYSCON_WREN_BIT_PERI3,
	SYSCON_WREN_BIT_SPEAKER,
	SYSCON_WREN_BIT_FLASHSIZE,
}SYSCON_WREN_BIT;

typedef enum enum_dev_enum
{
	DEV_CLOCK_TIMER_4 = 0,
	DEV_CLOCK_TIMER_0_1,
	DEV_CLOCK_TIMER_2_3,
	DEV_CLOCK_UART_0_1,
	DEV_CLOCK_UART_2_3,
	DEV_CLOCK_UART_4_5,
	DEV_CLOCK_I2S,
	DEV_CLOCK_SPEAKER = 10,
	DEV_CLOCK_MIXER_AMP = 11,
	DEV_CLOCK_MAX
}DEV_CLOCK_TYPE;


#define SYSTEM_HALT(n)	do{*R_SYSCON_HALT = n;}while(0);

U32 get_ahb_clock();
U32 get_apb_clock();
U32 get_clock(DEV_CLOCK_TYPE devnum);
U32 get_pll();

