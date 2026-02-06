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

extern int critical_ref_counter;
// back up interrupt status, disable interrupt
#define CRITICAL_ENTER()	do{asm("set 8"); asm("sync"); critical_ref_counter++;} while (0)
// restore interrupt status
#define CRITICAL_EXIT() do{\
							if(critical_ref_counter>0){\
								critical_ref_counter--;\
							}\
							if(critical_ref_counter==0){\
								asm("clr 8"); asm("sync");\
							}\
							} while (0)

#define INTERRUPT_ENABLE	asm("set 13");
#define INTERRUPT_DISABLE	asm("clr 13");
#define NMI_ENABLE			asm("set 14");
#define NMI_DISABLE			asm("clr 14");
#define SETVECTORED			asm("set 12");

// Interrupt Pending Clear Register
#define R_INTPENDCLR		((volatile unsigned int*)0xFFFF0000)

// External Interrupt Mode and External PIN Level Register
#define R_EINTMOD		((volatile unsigned int*)0xFFFF0004)

#define F_EINTMOD_0ST			(1<<3)
#define F_EINTMOD_0MOD_LOW		(0<<0)
#define F_EINTMOD_0MOD_HIGH		(1<<0)
#define F_EINTMOD_0MOD_FEDGE	(2<<0)
#define F_EINTMOD_0MOD_REDGE	(3<<0)
#define F_EINTMOD_0MOD_AEDGE	(4<<0)
							
#define F_EINTMOD_1ST			(1<<7)
#define F_EINTMOD_1MOD_LOW		(0<<4)
#define F_EINTMOD_1MOD_HIGH		(1<<4)
#define F_EINTMOD_1MOD_FEDGE	(2<<4)
#define F_EINTMOD_1MOD_REDGE	(3<<4)
#define F_EINTMOD_1MOD_AEDGE	(4<<4)

// Internal Interrupt Mode Register
#define R_IINTMOD	((volatile unsigned int*)0xFFFF0008)

// Interrupt Pending Register
#define R_INTPEND	((volatile unsigned int*)0xFFFF000C)

// Interrupt Enable Register
#define R_INTEN		((volatile unsigned int*)0xFFFF0010)

// Interrupt Mask Set Register
#define R_INTMASKSET	((volatile unsigned int*)0xFFFF0014)

// Interrupt Mask Status Register
#define R_INTMASK	((volatile unsigned int*)0xFFFF0014)

// Interrupt Mask Clear Register
// R_INTMASKCLR
#define R_INTMASKCLR	((volatile unsigned int*)0xFFFF0018)

// Programmable Interrupt Priority Enable Register
#define R_PIPENR	((volatile unsigned int*)(0xFFFF001C)

#define F_PIPENR_ENABLE			(1<<0)			// Programmable Priority Enable
#define F_PIPENR_DISABLE		(0<<0)			// Programmable Priority Disable

// Interrupt Priority Vector Register
#define R_IPVR(n)	((volatile unsigned int*)(0xFFFF0020+(n*4)))

typedef enum 
{
	INTNUM_SWD=0,
	INTNUM_TICKTIMER,
	INTNUM_TIMER0,
	INTNUM_SOUND,

	INTNUM_GPIO2=4,
	INTNUM_TIMER2,
	INTNUM_DMA0,
	INTNUM_GPIO0=7,
	INTNUM_CAP_OVER_2=7,
	
	INTNUM_UART0,	// 0x8
	INTNUM_DMA1,
	INTNUM_TIMER1=10,
	INTNUM_GPIO8 = 10,	
	INTNUM_GPIO1 = 11,
	
	INTNUM_DMA2,	// 0xC
	INTNUM_ADC,
	INTNUM_USB,
	INTNUM_UART3,
	
	INTNUM_UART1=16,	// 0x10
	INTNUM_DMA3,
	INTNUM_SPI0=18,
	INTNUM_UART5=18,
	INTNUM_GPIO6 = 19,  
	INTNUM_CAP_OVER4 = 19,

	INTNUM_SPI1,	
	INTNUM_UART2,
	INTNUM_PDBG = 22,
	INTNUM_GPIO5 = 22,
	INTNUM_WATCHDOG = 23,
	
	INTNUM_TIMER3=24,	// 0x18
	INTNUM_UART4,	
	INTNUM_TWI0 = 26,
	INTNUM_GPIO3 = 26,	
	
	INTNUM_TIMER4=28,	// 0x1C
	INTNUM_GPIO7 = 28,
	INTNUM_CAP_OVER0 = 29,
	INTNUM_GPIO4 = 29,
	INTNUM_TWI1,
	INTNUM_PMC,	
	
	INTNUM_MAX
}INTERRUPT_TYPE;

void init_interrupt();
BOOL set_interrupt(INTERRUPT_TYPE intnum,void (*fp)());
void* get_interrupt(INTERRUPT_TYPE intnum);
void enable_interrupt(INTERRUPT_TYPE num,BOOL b);

// priority
void interrupt_swap_priority(INTERRUPT_TYPE a, INTERRUPT_TYPE b);
int interrupt_set_priority(INTERRUPT_TYPE a, int prio);
int interrupt_get_priority(INTERRUPT_TYPE a);
