/******************************************************************************
 Copyright (C) 2011      Advanced Digital Chips Inc. 
						http://www.adc.co.kr
 Author : Software Team.

******************************************************************************/
#include "sdk.h"
void main();

/// <summary>
/// PLL initialize
/// </summary>
void pll_init()
{
	//use external clock
	//SYSCON_REG_WRITE(SYSCON_WREN_BIT_CLKCON, R_SYSCON_CLKCON, 1<<1); //XIN/1
	
	U32 pllval;
	//pllval = ((2 - 1) << 24) | (3 << 16) | 50; // 100Mhz;
	pllval = ((2 - 1) << 24) | (3 << 16) | 48; // 96Mhz;
	//pllval = ((2 - 1) << 24) | (3 << 16) | 24; // 48Mhz;
	//pllval = ((2 - 1) << 24) | (3 << 16) | 36; // 72Mhz;
	SYSCON_REG_WRITE(SYSCON_WREN_BIT_PLL, R_SYSCON_PLLCON, pllval);

	int k = 10000;
	while (k--)
	{
		asm("nop");
	}

	SYSCON_REG_WRITE(SYSCON_WREN_BIT_CLKCON, R_SYSCON_CLKCON, 1); //XIN/1, PLL selected
	SYSCON_REG_WRITE(SYSCON_WREN_BIT_HCLK_DIV, R_SYSCON_HCLKDIV, 0);// hclk = pll/1;
}

void syscon_divider_init()
{
	// CLKXX source selects "pll0"
	SYSCON_REG_WRITE(SYSCON_WREN_BIT_ADD_CLOCK_DIV, R_SYSCON_CLKDCON, 0x55500);// CLKxxx's source = PLL0
	SYSCON_REG_WRITE(SYSCON_WREN_BIT_CLK16, R_SYSCON_CLK16DIV, 0); // CLK16 =  CLK16's source/1
	
	//A default value of "Peri Clock selection registsrs"  is 0(Xin).

	// Timer Async
	int i = 0;
	for(i=0;i<5;i++)
		*(U32*)TMCLK_ADDR(i) = 3; 
	
	//UART 0- 6 Async
	SYSCON_REG_WRITE(SYSCON_WREN_BIT_SW_RESET, R_SYSCON_SWRUSC, 0);
}
void sound_clock_init()
{
	U32 val;
	val = (1 << 28) |0<<24; // mixer clock source selects CLK16 and divide 1, PLL/1
	//val = (1 << 28); // mixer clock source selects CLK16 and divide 1, PLL/1
	val |= (1 << 20) | (4<<16); // speaker clock source selects CLK16 and divide 5, PLL/5
	SYSCON_REG_WRITE(SYSCON_WREN_BIT_PERI2, R_SYSCON_PERI2, val);
}

void usb_clock_init()
{
	U32 val = *R_SYSCON_CLKCON;
	val |= 0xc;
	SYSCON_REG_WRITE(SYSCON_WREN_BIT_CLKCON, R_SYSCON_CLKCON, val); //XIN/1, PLL selected, USB Source Clock / 2 , USB clock on

	val = *R_SYSCON_USBPHYCON;
	val |= 0x11;
	SYSCON_REG_WRITE(SYSCON_WREN_BIT_USB_PHY, R_SYSCON_USBPHYCON, val); // USB Receive Enable bit, DP Pull up enable
	
}

/*
defined at linker-script.
*/
extern unsigned int _rom_data_start[];
extern unsigned int _ram_data_start[];
extern unsigned int _ram_data_end[];

extern unsigned int _bss_start[];
extern unsigned int _bss_end[];

/*!
* \brief
* Write brief comment for crt0main here.
*
* Data, ISPM, DSPM copy
* BSS initialize
* C++ constructor
*/

//void crt0main() __attribute__((weak)) __attribute__((section(".ispm")));

static void crt0main()
{
	register unsigned int* src;
	register unsigned int* dest;
	register unsigned int* destend;
	register int len;

	/* data copy */
	if (_rom_data_start < (U32*)0x10000000)
	{
		src = _rom_data_start;
		dest = _ram_data_start;
		destend = _ram_data_end;
		len = (unsigned int)destend - (unsigned int)dest;
		memcpy((void*)dest, (void*)src, (int)len);
	}

	/* BSS init
	*/
	dest = _bss_start;
	destend = _bss_end;
	len = (unsigned int)destend - (unsigned int)dest;
	if (len > 0)
		memset(dest, 0, len);


	//for C++

	typedef void(*pfunc) ();
	extern pfunc __ctors[];
	extern pfunc __ctors_end[];
	pfunc *p;
	for (p = __ctors_end; p > __ctors;)
		(*--p) ();

}

static void spm_init()
{
	asm("push %r0");
// SPM configuration, I:2K, D:78K
    asm("ldi  0x700,    %r0");
    asm("mvtc 0x0,      %r3");
	asm("nop			   ");
	//asm("ldi  0x501501,  %r0");
	asm("ldi  0x10100521,  %r0");
    asm("mvtc 0x0,      %r4");
	asm("nop			   ");

	//ISPM Setting..
	//START address 
    asm("ldi  0x702, %r0	  ");
    asm("mvtc 0x0,   %r3	  ");
	asm("nop				  ");
    asm("ldi  0x10000000,  %r0");
    asm("mvtc 0x0,   %r4	  ");
	asm("nop				  ");

	//END address : 
	asm("ldi  0x703, %r0				");
	asm("mvtc 0x0,   %r3				");
	asm("nop							");
	asm("ldi  0x100007ff,  %r0			");
	asm("mvtc 0x0,   %r4				");
	asm("nop							");

	//setting config reg 
	asm("ldi  0x701, %r0				");
	asm("mvtc 0x0,   %r3				");
	asm("ldi  0x111, %r0				");
	asm("mvtc 0x0,   %r4				");
	asm("nop							");

	//DSPM Setting..			
	//START address 
	asm("ldi  0x705, %r0				");
	asm("mvtc 0x0,   %r3				");
	asm("nop							");
	asm("ldi  0x10000800,   %r0			");
	asm("mvtc 0x0,   %r4				");
	asm("nop							");
	
	//END address 					
	asm("ldi  0x706, %r0				");
	asm("mvtc 0x0,   %r3				");
	asm("nop							");
	asm("ldi  0x10007fff,  %r0			");
	asm("mvtc 0x0,   %r4				");
	asm("nop							");
	
	//setting config reg 
	asm("ldi  0x704, %r0				");
	asm("mvtc 0x0,   %r3				");
	asm("nop							");
	asm("ldi  0x111, %r0				");
	asm("mvtc 0x0,   %r4				");
	asm("nop							");	
	
	//START address 
	asm("ldi  0x715, %r0				");
	asm("mvtc 0x0,   %r3				");
	asm("nop							");
	asm("ldi  0x10008000,   %r0			");
	asm("mvtc 0x0,   %r4				");
	asm("nop							");

	//END address 					
	asm("ldi  0x716, %r0				");
	asm("mvtc 0x0,   %r3				");
	asm("nop							");
	asm("ldi  0x1000ffff,  %r0			");
	asm("mvtc 0x0,   %r4				");
	asm("nop							");
	
	//setting config reg 
	asm("ldi  0x714, %r0				");
	asm("mvtc 0x0,   %r3				");
	asm("nop							");
	asm("ldi  0x111, %r0				");
	asm("mvtc 0x0,   %r4				");
	asm("nop							");

	//START address 
	asm("ldi  0x725, %r0				");
	asm("mvtc 0x0,   %r3				");
	asm("nop							");
	asm("ldi  0x10010000,   %r0			");
	asm("mvtc 0x0,   %r4				");
	asm("nop							");

	//END address 					
	asm("ldi  0x726, %r0				");
	asm("mvtc 0x0,   %r3				");
	asm("nop							");
	asm("ldi  0x10013fff,  %r0			");
	asm("mvtc 0x0,   %r4				");
	asm("nop							");

	//setting config reg 
	asm("ldi  0x724, %r0				");
	asm("mvtc 0x0,   %r3				");
	asm("nop							");
	asm("ldi  0x111, %r0				");
	asm("mvtc 0x0,   %r4				");
	asm("nop							");	

	asm("pop %r0");
}
extern unsigned int _rom_ispm_start[];
extern unsigned int _ram_ispm_start[];
extern unsigned int _ram_ispm_end[];
static void spm_load()
{
	register unsigned int* src;
	register unsigned int* dest;
	register unsigned int* destend;
	register int len;
	/* SPM copy */
	src = _rom_ispm_start;
	dest = _ram_ispm_start;
	destend = _ram_ispm_end;
	len = (unsigned int)destend - (unsigned int)dest;
	if (len > 0)
		memcpy(dest, src, len);
}

//#define USING_EXT_FLASH
void _startup()
{
	*R_FLMSIZE(0) = 7;    // serial flash size : 4MByte *R_FLMSIZE(0) = 7;    // serial flash size : 4MByte

	SYSCON_REG_WRITE(SYSCON_WREN_BIT_FLASHSIZE, R_SYSCON_FLASHSIZE, 4);  // serial flash size : 4MByte
#ifdef USING_EXT_FLASH
	*R_PAF(1) = 0; //for external flash
	
	*R_FLMSIZE(0) = 7;    // serial flash size : 4MByte
#endif
	spm_init();
	spm_load();
	pll_init();
	CacheInit();
	crt0main();
	init_interrupt();
	tick_timer_init();
	syscon_divider_init();
	sflash_init(0);
#ifdef USING_EXT_FLASH
	sflash_init(1);
#endif
	main();
}
