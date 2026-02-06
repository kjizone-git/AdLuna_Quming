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

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <stdint.h>

#define RAMCODE __attribute__((section(".ramcode")))
#define ISPM __attribute__((section(".ispm")))

#ifdef __GNUG__ // The GNU C++ compiler defines this. Testing it is equivalent to testing (__GNUC__ && __cplusplus).
extern "C"
{
#endif
#include "lib_config.h"
#include "typedef.h"

#include "device/util.h"
#include "device/cacheutil.h"
#include "device/interrupt.h"
#include "device/system_control.h"
#include "device/adc.h"
#include "device/uart.h"
#include "device/timer.h"
#include "device/gpio.h"
#include "device/dma.h"
#include "device/twi.h"
#include "device/usb.h"
#include "device/usbdesc.h"
#include "device/usbhid.h"
#include "device/usb_serial.h"
#include "device/watchdogtimer.h"
#include "device/adLunaInit.h"
#include "device/serialflash.h"
#include "device/spi.h"
#include "device/tick_timer.h"
#include "fatfs/ff.h"
#include "fatfs/serialflash_fs.h"
#include "device/soundmixer.h"

/*
for include binary

example)
INCBIN(testbmp, "test.bmp")
SURFACE = loadbmpp(testbmp_data);
int fsize = testbmp_end - testbmp_data;
*/
#define INCBIN_EXTERN(NAME)                                               \
	extern const __attribute__((aligned(4))) unsigned char NAME##_data[]; \
	extern const unsigned char NAME##_end[];

#define INCBIN(NAME, FILENAME)                  \
	__asm__(".section .rodata\n"                \
			".global _" #NAME "_data\n"         \
			".type _" #NAME "_data ,@object \n" \
			".balign 4\n"                       \
			"_" #NAME "_data:\n"                \
			".incbin \"" FILENAME "\"\n"        \
			".global _" #NAME "_end\n"          \
			".type _" #NAME "_end, @object\n"   \
			"_" #NAME "_end:\n"                 \
			".byte 1\n");                       \
	INCBIN_EXTERN(NAME)

#ifdef __GNUG__
}
#endif
