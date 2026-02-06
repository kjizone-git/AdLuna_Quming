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

#define SPI_MAX_WFIFO   	8
#define SPI_MAX_RFIFO   	8
#define SPI_BASE_ADDR		0x80001800
#define R_SPICON(ch)      		((volatile unsigned int*)(SPI_BASE_ADDR + (ch * 0x1000)))

#define SPICON_MSBF        	(1 << 2)
#define SPICON_CPHA        		(1 << 3)
#define SPICON_CPOL        		(1 << 4)
#define SPICON_MSTR        	(1 << 5)
#define SPICON_WOMP        	(1 << 6)
#define SPICON_EN          		(1 << 7)

#define	R_SPIBAUD(ch)		((volatile unsigned int*)(SPI_BASE_ADDR+4 + (ch * 0x1000)))

#define R_SPISTAT(ch)			((volatile unsigned int*)(SPI_BASE_ADDR+8 + (ch * 0x1000)))

#define SPISTAT_SRXE     (1 << 0)
#define SPISTAT_SRXF     (1 << 1)
#define SPISTAT_STXE     (1 << 2)
#define SPISTAT_STXF     (1 << 3)
#define SPISTAT_SSX      (1 << 4)
#define SPISTAT_MODF   (1 << 5)
#define SPISTAT_WCOL   (1 << 6)
#define SPISTAT_SPIF     (1 << 7)

#define R_SPIDATA(ch) 	    ((volatile unsigned char*)(SPI_BASE_ADDR+0xc + (ch * 0x1000)))
#define R_SPIDATA16(ch)    ((volatile unsigned short*)(SPI_BASE_ADDR+0xc + (ch * 0x1000)))
#define R_SPIDATA32(ch)    ((volatile unsigned int*)(SPI_BASE_ADDR+0xc + (ch * 0x1000)))

#define R_SSXCON(ch) 	    ((volatile unsigned int*)(SPI_BASE_ADDR+0x10 + (ch * 0x1000)))
#define SSXCR_SSXCON    (1 << 0)

#define R_SPIINT(ch)	    ((volatile unsigned int*)(SPI_BASE_ADDR+0x14 + (ch * 0x1000)))
#define SIMK_SRXEE     (1 << 0)
#define SIMK_SRXFE     (1 << 1)
#define SIMK_STXEE     (1 << 2)
#define SIMK_STXFE     (1 << 3)
#define SIMK_SSXE      (1 << 4)
#define SIMK_MODFE   (1 << 6)
#define SIMK_SPIFE     (1 << 7)

#define SPI_FIFOSIZE    64

#define SPI_BAUD(clk)     ((get_apb_clock()  / (2*clk))-1)
#define SPI_SCK(baud)    (get_apb_clock()  / (2*(baud+1)))

#define SPI_MASTER      0
#define SPI_SLAVE       1

#define SPI_MASTER_MAXFREQ      (get_apb_clock()/2)
#define SPI_SLAVE_MAXFREQ       (get_apb_clock()/4)

#define SPI_CS_LOW   
#define SPI_CS_HIGH  

void spi_master_init(U8 ch);
int spi_set_freq (U8 ch, int mode, U32 freq);
void spi_master_xfer (U8 ch, U8 *wbuf, int wlength, U8 *rbuf, int rlength, int continue_xfer);
void spi_wait_empty_fifo (U8 ch);

