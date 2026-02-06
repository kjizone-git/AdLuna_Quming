/*****************************************************************************
*
* Copyright (C) 2023      Advanced Digital Chips, Inc. All Rights Reserved.
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

 이 파일을 수정 함으로써 전체 실행파일 사이즈와 메모리 사용량을 줄일 수도 있다.
 하지만 줄어든 만큼 성능의 저하가 발생 할 경우도 있다.
 제거 하고자 하는 기능은 0 으로 설정 함으로써 제거된다.

******************************************************************************/
#pragma once

// #define NESTED_INTERRUPT_ENABLE

/******************************************************************************
	INTERNAL TIME OUT
******************************************************************************/
/*
	Max count for TWI Function
*/
#define TWI_RESP_TIME_OUT_COUNT (7200 * 100) // About 100ms @ AHB 101MHz

/******************************************************************************
	Serial Flash
******************************************************************************/

// #define SF_SUPPORTS_SFDP
/*
if define SF_SUPPORTS_SFDP ( Serial Flash Discoverable Parameters)
	RAM Usage : 750 byte
	CODE Usage : 750 Bye
*/

/******************************************************************************
	UART Config
******************************************************************************/
/*
	인터럽트 모드일 경우 	uart 송/수신 data 를 임시로 저장 할 버퍼의 사이즈이다.
*/
#define UART_BUF_SIZE 128
#define CONFIG_UART_RX_INTERRUPT
// #define CONFIG_UART_TX_INTERRUPT

/*
	debugstring, debugprintf 함수의  최종 출력 채널
*/
#define DEBUG_CHANNEL 0///3
#define MAIN_CHANNEL 2//0

/******************************************************************************
	SYSTEM CLOCK
******************************************************************************/
/*
	external OSC
*/

#define OSC_CLOCK 12000000

/******************************************************************************
 *	SOUND Mixer
 ******************************************************************************/
/*
	버퍼 사이즈를 줄이면 메모리 사용량은 줄어 들지만
	인터럽트 발생 횟수가 늘어 난다.
*/
#define WAVE_BUF_MAX (5 * 1024)
#define WAVE_RELOAD_BUF_MAX (1024 * 5)
#define DEFAULT_VOLUME 255 // max 255

/*
	최종 출력 sample rate
*/
#define SND_OUTPUT_HZ 48000
// #define SND_OUTPUT_CHANNEL 3 //Internal Speaker Driver
#define SND_OUTPUT_CHANNEL 2 // SOUDN PWM

/******************************************************************************
 * supports FAT File Systems
 ******************************************************************************/
#define SUPPORTS_FS 1
#define FS_START_SECTOR 256 // 1Mbyte reserved for application

