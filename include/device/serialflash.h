/*****************************************************************************
*
* Copyright (C) 2018      Advanced Digital Chips, Inc. All Rights Reserved.
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
#define FLASH_CTRL_BASE 0x80000000

#define R_FLMOD(N)		((volatile unsigned int*)(FLASH_CTRL_BASE+0+(N*0x2400)))
#define R_FLBRT(N)		((volatile unsigned int*)(FLASH_CTRL_BASE+4+(N*0x2400)))
#define R_FLCSH(N)		((volatile unsigned int*)(FLASH_CTRL_BASE+8+(N*0x2400)))
#define R_FLPEM(N)		((volatile unsigned int*)(FLASH_CTRL_BASE+0xc+(N*0x2400)))
#define R_FLCMD(N)		((volatile unsigned char*)(FLASH_CTRL_BASE+0x10+(N*0x2400)))
#define R_FLSTS(N)		((volatile unsigned char*)(FLASH_CTRL_BASE+0x14+(N*0x2400)))
#define R_FLSEA(N)		((volatile unsigned int*)(FLASH_CTRL_BASE+0x18+(N*0x2400)))
#define R_FLBEA(N)		((volatile unsigned int*)(FLASH_CTRL_BASE+0x1c+(N*0x2400)))
#define R_FLDAT(N)		((volatile unsigned int*)(FLASH_CTRL_BASE+0x20+(N*0x2400)))
#define R_FLWCP(N)		((volatile unsigned int*)(FLASH_CTRL_BASE+0x24+(N*0x2400)))
#define R_FLCKDLY(N)	((volatile unsigned int*)(FLASH_CTRL_BASE+0x28+(N*0x2400)))
#define R_FLSTS2(N)		((volatile unsigned int*)(FLASH_CTRL_BASE+0x2c+(N*0x2400)))
#define R_FLIDR(N)		((volatile unsigned int*)(FLASH_CTRL_BASE+0x30+(N*0x2400)))
#define R_FLMSIZE(N)	((volatile unsigned int*)(FLASH_CTRL_BASE+0x34+(N*0x2400)))
#define R_FLCFG(N)	((volatile unsigned int*)(FLASH_CTRL_BASE+0x38+(N*0x2400)))
#define R_FLVER(N)	((volatile unsigned int*)(FLASH_CTRL_BASE+0x3c+(N*0x2400)))

void sflash_erase_sector(int dev_num,int sector,int sector_cnt);
void sflash_write(U32 addr, BYTE* buf, int len);
void sflash_dev_write(U32 dev_num,U32 addr, BYTE* buf, int len);
int sflash_read(U32 addr, BYTE* buf, int len);
int sflash_dev_read(int dev_num,U32 addr, BYTE* buf, int len);
int sflash_get_size(int dev_num);
int sflash_get_sector_size(int dev_num);
int sflash_get_sector_count(int dev_num);
void sflash_init(int dev_num);
void sflash_info_dump(int dev_num);
U32 sflash_custom_read(int dev_num, U8 cmd, U32 addr, U32 addr_byte_len,int dummy_cnt, U8* buf, U32 readlen);
void sflash_custom_write(int dev_num, U8 cmd, U32 address, U8* buf, U32 buflen);
void sflash_protect_write(int dev_num, BOOL b_enable_protect);
void sflash_write_status(int dev_num, U8 cmd, U8 data);

