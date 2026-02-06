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

//======================================================================================================================
// Watchdog Timer Contorl Register (WDTCTRL)

#define _WDT_BASE_ 0x80032400
#define R_WDTCTRL  ((volatile unsigned int*)_WDT_BASE_)

#define F_WDTCTRL_HALTEN		(1 << 7)		// Watchdog timer halt enable bit
#define F_WDTCTRL_BRKEN			(1 << 6)		// Watchdog timer core break enable bit
#define F_WDTCTRL_WDTST			(1 << 4)		// Watchdog timer status bit - 0 No Watchdog / 1 Watchdog reset or interrupt
#define F_WDTCTRL_WDTMOD_RST	(0 << 1)		// Watchdog timer mode select bit - 0 Reset Mode / 1 Interrupt Mode
#define F_WDTCTRL_WDTMOD_INT	(1 << 1)		// Watchdog timer mode select bit - 0 Reset Mode / 1 Interrupt Mode
#define F_WDTCTRL_WDTEN_DISABLE	(0 << 0)		// Watchdog timer enable bit - 0 Disable / 1 Enable
#define F_WDTCTRL_WDTEN_ENABLE	(1 << 0)		// Watchdog timer enable bit - 0 Disable / 1 Enable
//======================================================================================================================

//======================================================================================================================
// Watchdog Timer Counter Value Register (WDTCNT)

#define R_WDTCNT  ((volatile unsigned int*)(_WDT_BASE_+4))
//======================================================================================================================


#define R_WDTLCK	((volatile unsigned int*)(_WDT_BASE_+8))
