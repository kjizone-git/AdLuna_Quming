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
// Timer Pre-scale Control Registers (TPxCTRL)

#define F_TPCTRL_CNTCLR			(1 << 1)		// Pre-scale Counter and Timer Counter Reset
#define F_TPCTRL_CLKSEL_CAP0	(1 << 0)		// Pre-scale Clock Selection - CAP0
#define F_TPCTRL_CLKSEL_SCLK	(0 << 0)		// Pre-scale Clock Selection - System Clock
//======================================================================================================================

//======================================================================================================================
// Timer Control Registers (TMxCTRL)

#define F_TMCTRL_TMOD_TIMER		(0 <<14)		// Timer/Counter Mode - TIMER
#define F_TMCTRL_TMOD_PWM		(1 <<14)		// Timer/Counter Mode - PWM
#define F_TMCTRL_TMOD_CAP		(2 <<14)		// Timer/Counter Mode - Capture
#define F_TMCTRL_OVST			(1 <<12)		// Capture Overflow Status bit
#define F_TMCTRL_CAPMOD_LH		(0 << 8)		// Capture Mode Selection - Low/High Pulse
#define F_TMCTRL_CAPMOD_LP		(2 << 8)		// Capture Mode Selection - Low Pulse
#define F_TMCTRL_CAPMOD_HP		(3 << 8)		// Capture Mode Selection - High Pulse
#define F_TMCTRL_CAPMOD_FF		(4 << 8)		// Capture Mode Selection - Falling to Falling Period
#define F_TMCTRL_CAPMOD_RR		(6 << 8)		// Capture Mode Selection - Rising to Rising Period
#define F_TMCTRL_IUE				(1<<7) 			// Immediately Update Enable
#define F_TMCTRL_PWMO			(1 << 6)		// PWM Output One Period Generation - Enable
#define F_TMCTRL_PWML_HIGH		(1 << 5)		// PWM Output Start Level - High
#define F_TMCTRL_PWML_LOW		(0 << 5)		// PWM Output Start Level - Low
#define F_TMCTRL_TMOUT			(1 << 4)		// Timer Wave Output Generation - Enable
#define F_TMCTRL_PFSEL_2		(0 << 1)		// Pre-scale Factor Selection - 1/2
#define F_TMCTRL_PFSEL_8		(1 << 1)		// Pre-scale Factor Selection - 1/8
#define F_TMCTRL_PFSEL_32		(2 << 1)		// Pre-scale Factor Selection - 1/32
#define F_TMCTRL_PFSEL_128		(3 << 1)		// Pre-scale Factor Selection - 1/128
#define F_TMCTRL_PFSEL_512		(4 << 1)		// Pre-scale Factor Selection - 1/512
#define F_TMCTRL_PFSEL_2048		(5 << 1)		// Pre-scale Factor Selection - 1/2048
#define F_TMCTRL_PFSEL_8192		(6 << 1)		// Pre-scale Factor Selection - 1/8192
#define F_TMCTRL_PFSEL_32768	(7 << 1)		// Pre-scale Factor Selection - 1/32768
#define F_TMCTRL_TMEN			(1 << 0)		// Timer/Counter or PWM Enable
//======================================================================================================================

#define TIMER_BASE_ADDR	0x80030800

#define TPCTRL_ADDR(ch) (ch==0?0x80030800:ch==1?0x80030820:ch==2?0x80040800:ch==3?0x80040820:0x80020000)
#define TMCTRL_ADDR(ch) (TPCTRL_ADDR(ch) + 4)
#define TMCNT_ADDR(ch) (TPCTRL_ADDR(ch) + 8)
#define TMDUT_ADDR(ch) (TPCTRL_ADDR(ch) + 0xc)
#define TMPUL_ADDR(ch) (TPCTRL_ADDR(ch) + 0x10)
#define TMCLK_ADDR(ch) (TPCTRL_ADDR(ch) + 0x14)
#define TMUPDATE_ADDR(ch) (TPCTRL_ADDR(ch) + 0x18)

#define MAX_TIMER_CHANNEL 4

#define TIMER_REG_WRITE(bAsync, ch, addr, data)        \
    do {                                               \
        *(vU32 *)addr = data;                          \
        if(bAsync)                                     \
        {                                              \
            while(!((*(vU32 *)TMUPDATE_ADDR(ch)) & 1)) \
                ;                                      \
            *(vU32 *)TMUPDATE_ADDR(ch) = 1;            \
        }                                              \
    }                                                  \
    while(0);

#define TIMER_REG_READ(bAsync, ch, addr, data)          \
    do {                                                \
        data = *(vU32 *)addr;                           \
        if(bAsync)                                      \
        {                                               \
            while(!((*(vU32 *)TMUPDATE_ADDR(ch)) & 2))  \
                ;                                       \
            data                       = *(vU32 *)addr; \
            *(vU32 *)TMUPDATE_ADDR(ch) = 2;             \
        }                                               \
    }                                                   \
    while(0);

BOOL set_timer(int nCh,U32 ms);
BOOL stop_timer(int nCh);

int set_pwm(int nCh, int hz, int number, bool bperiod, bool en);
/*
"period_clock_cnt" must be greater than 3.
"duty_clock_cnt" must be greater than 2.
if async mode and Xin is 12Mhz, Timer Input Clock is 12Mhz/2(prescale)=6Mhz
Therefore, the maximum frequency is 6Mhz/3, which is 2Mhz.
*/
int set_pwm_ex(int nCh,int period_clock_cnt,int duty_clock_cnt,bool start_level,int interrupt_pluse_number,bool one_time);
