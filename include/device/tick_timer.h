#pragma once
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
#include "typedef.h"
#define R_TTMRST ((volatile unsigned int*)0xffff1000)
#define R_TTMCON ((volatile unsigned int*)0xffff1004)
#define R_TTMCNT0 ((volatile unsigned int*)0xffff1008)
#define R_TTMCNT1 ((volatile unsigned int*)0xffff100c)

void tick_timer_init();
U32 get_tick_count();
U64 get_tick_count64();
U32 get_one_tick_time();//return nano seconds.

/*
delayus takes 16us ( system clock : 100Mhz )
If you want less time than 16us, use delay_tick_count()
*/
BOOL delayus(U32 us);
BOOL delayms(U32 ms);

/*
delay_tick_count takes 1us ( system clock : 100Mhz )
U32 tickcnt = (us - 1)  * 1000 / get_one_tick_time();
delay_tick_count(tickcnt);
*/
bool delay_tick_count(U32 cnt);
