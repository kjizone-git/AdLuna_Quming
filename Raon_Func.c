#define RAON_FUNC_GLOBALS

#include "sdk.h"
#include "image_db.h"
#include "raon_global.h"
#include "raon_func.h"

void Interrupt_Timer0(void)
{
	Time0_10mS++;
}

void Timer_Init(void)
{
	set_interrupt(INTNUM_TIMER0,Interrupt_Timer0);
	set_timer(0, 10);	//10mS간격으로 인터럽트 발생됨.
	enable_interrupt(INTNUM_TIMER0, true);
	Time0_10mS=0;
	cnt_10mS=0;
	Time0_500mS=0;
	Time0_1000mS=0;
	//fg_demo_mode = 1;//시작시 데모모드.....
}

void Variable_Init(void)
{
	dbg_Timer_2S=0;
	
	Time0_10mS=0;
	uart_rx_pt=0;
}

void inline spi_wait_finish_new(U8 ch)
{
    U8 stat;
    do {
        stat = *R_SPISTAT(ch);
    }
    while(!(stat & SPISTAT_SPIF));
}

void spi_master_xfer_new(U8 ch, U8 *wbuf, int wlength, U8 *rbuf, int rlength, int continue_xfer)
{
	int i;
    int rcnt = 0, rlen;
    int wcnt = 0, wlen;
    U8  flush;

    if(wlength > SPI_MAX_WFIFO_new)
        wlen = SPI_MAX_WFIFO_new;
    else
        wlen = wlength;

    if(rlength > SPI_MAX_WFIFO_new)
        rlen = SPI_MAX_WFIFO_new;
    else
        rlen = rlength;

    *R_SSXCON(ch) = 0; // SPI nSS Low

    while(wcnt < wlength)
    {
        for(i = 0; i < wlen;)
        {
            *R_SPIDATA(ch) = wbuf[i];
            i++;
        }
        spi_wait_finish_new(ch);

        for(i = 0; i < wlen; i++) flush = *R_SPIDATA(ch); // flush garbage

        wbuf += wlen;
        wcnt += wlen;
        if((wlength - wcnt) < SPI_MAX_WFIFO_new)
            wlen = wlength - wcnt;
    }

    while(rcnt < rlength)
    {
        for(i = 0; i < rlen;)
        {
            *R_SPIDATA(ch) = 0xaa;
            spi_wait_finish_new(ch);
            flush   = *R_SPIDATA(ch);
            rbuf[i] = flush;
            i++;
        }

        rbuf += rlen;
        rcnt += rlen;
        if((rlength - rcnt) < SPI_MAX_RFIFO)
            rlen = rlength - rcnt;
    }

    if(continue_xfer == 0)
        *R_SSXCON(ch) = 1; // SPI nSS High
}


void LCD_DC_gpio_write(uint8_t value)
{
    if (value)
    {
        *R_GPOHIGH(1) = 1 << 3;
    }
    else
    {
        *R_GPOLOW(1) = 1 << 3;
    }

//    return 0;
}

void LCD_RST_gpio_write(uint8_t value)
{
    if (value)
    {
        *R_GPOHIGH(1) = 1 << 4;
    }
    else
    {
        *R_GPOLOW(1) = 1 << 4;
    }

//    return 0;
}

void LCD_BL_gpio_write(uint8_t value)
{
    if (value)
    {
        *R_GPOHIGH(4) = 1 << 0;
    }
    else
    {
        *R_GPOLOW(4) = 1 << 0;
    }

//    return 0;
}
void Write_REG_Index(uint8_t data)
{
	spi_buf[0]=data;
	spi_buf_len=1;
	LCD_DC_gpio_write(0);
	spi_master_xfer(SPI_CH, spi_buf, spi_buf_len, NULL, 0, 0);
	LCD_DC_gpio_write(0);
}

void Write_REG_Data(uint8_t data)
{
	spi_buf[0]=data;
	spi_buf_len=1;
	LCD_DC_gpio_write(1);
	spi_master_xfer(SPI_CH, spi_buf, spi_buf_len, NULL, 0, 0);
	LCD_DC_gpio_write(0);
}

void TFT_LCD_225Inch_Init_frida(void)
{
	//unsigned char i;
	
	LCD_RST_gpio_write(1);
	LCD_RST_gpio_write(0);
	delayms(30);
	LCD_RST_gpio_write(1);
	delayms(120);
	Write_REG_Index(0x11);	//Sleep Out
	delayms(120);
	
	Write_REG_Index(0xB1);
	Write_REG_Data(0x05); //RTNA=0x01	
	Write_REG_Data(0x10); //FPA=0x08	
	Write_REG_Data(0x10); //BPA=0x05
	
	Write_REG_Index(0xB2);
	Write_REG_Data(0x05);	
	Write_REG_Data(0x3C);	
	Write_REG_Data(0x3C);		

	Write_REG_Index(0xB3);
	Write_REG_Data(0x05);	
	Write_REG_Data(0x3C);	
	Write_REG_Data(0x3C);		
	Write_REG_Data(0x05);	
	Write_REG_Data(0x3C);	
	Write_REG_Data(0x3C);		

	Write_REG_Index(0xB4);
	Write_REG_Data(0x00);

	
	Write_REG_Index(0x3A);
	Write_REG_Data(0x06); //18bit-1Pixel(6Bit->1Pixel)	
	//Write_REG_Data(0x05); //16bit-1Pixel

	Write_REG_Index(0xC0);
	Write_REG_Data(0xE4);	//AVDD=5.1V,GVDD=4.8V	
	Write_REG_Data(0x04);	//GVCL=4.8V	
	Write_REG_Data(0x07);	//VRHP[5] and VRHN[5]=1		

	Write_REG_Index(0xC1);
	Write_REG_Data(0xCE);	//VGH=3*AVDD-0.5=14.8V,VGL=-10V	

	Write_REG_Index(0xC2);
	Write_REG_Data(0x0D);	//Normal Mode,Large:Amount of Current in OPA 
	Write_REG_Data(0x00);

	Write_REG_Index(0xC3);
	Write_REG_Data(0x8D);
	Write_REG_Data(0x6A);

	Write_REG_Index(0xC4);
	Write_REG_Data(0x8D);
	Write_REG_Data(0xEE);

	Write_REG_Index(0xC5);
	Write_REG_Data(0x00);	//VCOM=-0.55V, 0x0C VCOM=-0.75V

	Write_REG_Index(0xE0);
	Write_REG_Data(0x04);
	Write_REG_Data(0x15);
	Write_REG_Data(0x06);
	Write_REG_Data(0x05);
	Write_REG_Data(0x0F);
	Write_REG_Data(0x08);
	Write_REG_Data(0x04);
	Write_REG_Data(0x0A);	
	Write_REG_Data(0x0E);	
	Write_REG_Data(0x15);	
	Write_REG_Data(0x30);	
	Write_REG_Data(0x3F);	
	Write_REG_Data(0x00);	
	Write_REG_Data(0x09);	
	Write_REG_Data(0x25);	

	Write_REG_Index(0xE1);
	Write_REG_Data(0x04); ///Variable resistor VRHN02/61
	Write_REG_Data(0x15); //Variable resistor VRLP61/02
	Write_REG_Data(0x06); //V60
	Write_REG_Data(0x05); //V56
	Write_REG_Data(0x0F); //V52
	Write_REG_Data(0x08); //V44
	Write_REG_Data(0x04); //V36
	Write_REG_Data(0x0A); //V28
	Write_REG_Data(0x0E); //V20
	Write_REG_Data(0x15); //V12
	Write_REG_Data(0x30); //V4
	Write_REG_Data(0x3F); //V3
	Write_REG_Data(0x00); //V63
	Write_REG_Data(0x03); //V62
	Write_REG_Data(0x09); //V01
	Write_REG_Data(0x25); //V00
	
	//Write_REG_Index(0x36);
#if 1
	//Write_REG_Data(0xC8); 
#else
	Write_REG_Data(0x08);
#endif
	
}


void Clear_Frame_Buffer(void)
{
	memset(spi_lcd_save_buf,0,sizeof(spi_lcd_save_buf));
}
void Set_Frame_Buffer(void)
{
	memset(spi_lcd_save_buf,0xff,sizeof(spi_lcd_save_buf));
}

void GRAY_TEST(void)
{
	U8 y_s_addr,cnt,j,i;
	U8 gray_step=15;

	LCD_BL_gpio_write(1);
	Write_REG_Index(0x29);
	
	for(i=0; i<gray_step; i++)
	{
		for(y_s_addr=0;y_s_addr<96;y_s_addr++)
		{
			//X축 Start - End
			Write_REG_Index(0x2A);
			Write_REG_Data(0x00);
			Write_REG_Data(0x17);	//23
			Write_REG_Data(0x00);
			Write_REG_Data(0x6D); //Write_REG_Data(0x6C);	//108	

			//Y축 Start - End
			Write_REG_Index(0x2B);
			Write_REG_Data(0x00);
			Write_REG_Data(0x21+y_s_addr);	//33
			Write_REG_Data(0x00);
			Write_REG_Data(0x80);			//128
			
			Write_REG_Index(0x2C);//

			for(cnt=0; cnt<32; cnt++)
			{
				for(j=0;j<8;j++)
				{
					//temp2=0xFC;
					spi_buf[j]=0xFC-(0x10*i);
				}
				spi_buf_len=8;
				LCD_DC_gpio_write(1);
				spi_master_xfer_new(SPI_CH, spi_buf, spi_buf_len, NULL, 0, 0);
				LCD_DC_gpio_write(0);
			}
			spi_buf[0]=0x0;
			spi_buf[1]=0x0;
			spi_buf[2]=0x0;
			spi_buf_len=3;
			LCD_DC_gpio_write(1);
			spi_master_xfer_new(SPI_CH, spi_buf, spi_buf_len, NULL, 0, 0);
			LCD_DC_gpio_write(0);
		}
		delayms(1000);
		debugprintf("Gray Test:%d",i);
	}
}

void TFT_LCD_225Inch_SPI_TX(unsigned char gray_scale)
{
	U8 y_s_addr,cnt,j,temp1,temp2;

	for(y_s_addr=0;y_s_addr<96;y_s_addr++)
	{
#if 1	
		//X축 Start - End
		Write_REG_Index(0x2A);
		Write_REG_Data(0x00);
		Write_REG_Data(0x17);	//23
		Write_REG_Data(0x00);
		Write_REG_Data(0x6D); //Write_REG_Data(0x6C);	//108	

		//Y축 Start - End
		Write_REG_Index(0x2B);
		Write_REG_Data(0x00);
		Write_REG_Data(0x21+y_s_addr);	//33
		Write_REG_Data(0x00);
		Write_REG_Data(0x80);			//128
		
		Write_REG_Index(0x2C);//
#endif
		for(cnt=0; cnt<32; cnt++)
		{
			for(j=0;j<8;j++)
			{
				temp1=spi_lcd_save_buf[y_s_addr][(cnt*8)+j];
				temp2=0;
				switch(gray_scale)
				{
					case 1:
						temp2=temp1*255;												
						break;
					case 2:
						temp2=temp1*21;
						break;
					case 4:
						temp2=temp1*4;
						break;
					default:
						temp2=temp1&0xfc;
						break;
				}
				spi_buf[j]=(temp2<<2);
			}

			spi_buf_len=8;
			LCD_DC_gpio_write(1);
			spi_master_xfer_new(SPI_CH, spi_buf, spi_buf_len, NULL, 0, 0);
			LCD_DC_gpio_write(0);
		}
#if 1
		spi_buf[0]=0x0;
		spi_buf[1]=0x0;
		spi_buf[2]=0x0;
		spi_buf_len=3;
		LCD_DC_gpio_write(1);
		spi_master_xfer_new(SPI_CH, spi_buf, spi_buf_len, NULL, 0, 0);
		LCD_DC_gpio_write(0);
#endif			
	}
}

void TFT_LCD_225Inch_all_black_fill(void)
{
	unsigned char y;
	unsigned int x;
	for(y=0;y<96;y++)
	{
		for(x=0;x<260;x++)
		{
			spi_lcd_save_buf[y][x]=0x0;
		}
	}
	TFT_LCD_225Inch_SPI_TX(0);
}

void Load_Image_FrameBuffer_2GRAY(const U8 *db_buf, U16 start_x,U8 start_y,U16 size_x, U8 size_y)
{
	unsigned int x,x_offset;
	unsigned char y,temp1;

	x=0;
	for(y=0;y<size_y;y++)
	{
		x_offset=0;

		while(1)
		{
			temp1=db_buf[x];
			x++;
		
			spi_lcd_save_buf[(start_y)+y][(start_x)+x_offset]=(temp1>>6)&0x3;
			x_offset++;
			if(x_offset>=size_x) break;
		
			spi_lcd_save_buf[(start_y)+y][(start_x)+x_offset]=(temp1>>4)&0x3;
			x_offset++;
			if(x_offset>=size_x) break;
		
			spi_lcd_save_buf[(start_y)+y][(start_x)+x_offset]=(temp1>>2)&0x3;
			x_offset++;
			if(x_offset>=size_x) break;
			spi_lcd_save_buf[(start_y)+y][(start_x)+x_offset]=(temp1>>0)&0x3;
			x_offset++;
			if(x_offset>=size_x) break; 	
		}
	}
}

void Load_Image_FrameBuffer_4GRAY(const U8 *db_buf, U16 start_x,U8 start_y,U16 size_x, U8 size_y)
{
	unsigned int x,x_offset;
	unsigned char y,temp1;

	x=0;
	for(y=0;y<size_y;y++)
	{
		x_offset=0;

		while(1)
		{
			temp1=db_buf[x];
			x++;
			spi_lcd_save_buf[(start_y-1)+y][(start_x-1)+x_offset]|=(temp1>>4)&0x0f;
			x_offset++;
			if(x_offset>=size_x) break;
			spi_lcd_save_buf[(start_y-1)+y][(start_x-1)+x_offset]|=temp1&0x0f;
			x_offset++; 				
			if(x_offset>=size_x) break;
		}

	}
}



void raon_display_demo_mode(U8 scene_idx)
{
	Clear_Frame_Buffer();
	switch(scene_idx)
	{
		case 1: Load_Image_FrameBuffer_2GRAY(IMG_LOGO_QM_G2,67,32,124,34);
				break;
		case 2: Load_Image_FrameBuffer_2GRAY(IMG_LARGE_M00,0,0,256,96);
				break;
		case 3: Load_Image_FrameBuffer_2GRAY(IMG_S0300,0,0,256,96);
				break;				
		case 4: Load_Image_FrameBuffer_2GRAY(IMG_S0400,0,0,256,96);
				break;				
		case 5: Load_Image_FrameBuffer_2GRAY(IMG_S0500,0,0,256,96);
				break;
		case 6: Load_Image_FrameBuffer_2GRAY(IMG_S0600,0,0,256,96);
				break;				
		case 7: Load_Image_FrameBuffer_2GRAY(IMG_S0701_BASE,0,0,256,96);
				break;
		case 8: Load_Image_FrameBuffer_2GRAY(IMG_D00,0,0,256,96);
				break;				
		case 9: Load_Image_FrameBuffer_2GRAY(IMG_P00,0,0,256,96);
				break;				
		default: Load_Image_FrameBuffer_2GRAY(IMG_S0200,0,0,256,96);
				break;
	}
	TFT_LCD_225Inch_SPI_TX(2);
	LCD_BL_gpio_write(1);		
	Write_REG_Index(0x29);
}

void Load_Set_Alarm(U8 disp_data)
{
	//U8 disp_free, disp_pet, disp_com;

	fg_blink_mode = disp_data&0x03;

	if(fg_blink_mode !=0)
		cnt_500mS = 50;

	
	fg_blink_is_on = true;

	disp_free = (disp_data>>2)&0x03;
	disp_pet = (disp_data>>4)&0x03;
	disp_com = (disp_data>>6)&0x03;

#if 1
	//Display BASE Image
	Load_Image_FrameBuffer_2GRAY(IMG_S0701_BASE,0,0,256,96);
	

	//Display FREE Filter
	if(disp_free == 1)//GRAY
		Load_Image_FrameBuffer_2GRAY(IMG_S07_FREE_G,35,69,60,22);
	else if(disp_free == 2)//WHITE
		Load_Image_FrameBuffer_2GRAY(IMG_S07_FREE_W,35,69,60,22);					
	else//Black
		Load_Image_FrameBuffer_2GRAY(IMG_S07_FREE_B,35,69,60,22);		

	//Display PET Filter
	if(disp_pet == 1)//GRAY
		Load_Image_FrameBuffer_2GRAY(IMG_S07_PET_G,98,69,60,22);
	else if(disp_pet == 2)//WHITE
		Load_Image_FrameBuffer_2GRAY(IMG_S07_PET_W,98,69,60,22);					
	else//Black
		Load_Image_FrameBuffer_2GRAY(IMG_S07_PET_B,98,69,60,22); 	

	//Display COMPLEX Filter
	if(disp_com == 1)//GRAY
		Load_Image_FrameBuffer_2GRAY(IMG_S07_COM_G,161,69,60,22);
	else if(disp_com == 2)//WHITE
		Load_Image_FrameBuffer_2GRAY(IMG_S07_COM_W,161,69,60,22);	
	else//Black
		Load_Image_FrameBuffer_2GRAY(IMG_S07_COM_B,161,69,60,22);
#else
	//Load_Image_FrameBuffer_2GRAY(IMG_0701_BASE_NEW,0,0,256,96);

	//Display FREE Filter
	if(disp_free == 1)//GRAY
		Load_Image_FrameBuffer_2GRAY(IMG_G_FREE,39,70,34,17);
	else if(disp_free == 2)//WHITE
		Load_Image_FrameBuffer_2GRAY(IMG_W_FREE,39,70,34,17);					
	else//Black
		Load_Image_FrameBuffer_2GRAY(IMG_BLK,39,70,34,17);		

	//Display PET Filter
	if(disp_pet == 1)//GRAY
		Load_Image_FrameBuffer_2GRAY(IMG_G_PET,111,70,34,17);
	else if(disp_pet == 2)//WHITE
		Load_Image_FrameBuffer_2GRAY(IMG_W_PET,111,70,34,17);					
	else//Black
		Load_Image_FrameBuffer_2GRAY(IMG_BLK,111,70,34,17); 	

	//Display COMPLEX Filter
	if(disp_com == 1)//GRAY
		Load_Image_FrameBuffer_2GRAY(IMG_G_COM,182,70,34,17);
	else if(disp_com == 2)//WHITE
		Load_Image_FrameBuffer_2GRAY(IMG_W_COM,182,70,34,17);					
	else//Black
		Load_Image_FrameBuffer_2GRAY(IMG_BLK,182,70,34,17);			
#endif	
}

void Load_Set_FilterPopup(U8 disp_data)
{
	//U8 disp_free, disp_pet, disp_com;

	fg_blink_mode = disp_data&0x03;

	if(fg_blink_mode !=0)
		cnt_500mS = 50;

	
	fg_blink_is_on = true;

	disp_free = (disp_data>>2)&0x03;
	disp_pet = (disp_data>>4)&0x03;
	disp_com = (disp_data>>6)&0x03;

	//Display BASE Image
	Load_Image_FrameBuffer_2GRAY(IMG_0200_BASE,0,0,256,96);

	//Display FREE Filter
	if(disp_free == 1)//GRAY
		Load_Image_FrameBuffer_2GRAY(IMG_G_FREE,39,67,34,17);
	else if(disp_free == 2)//WHITE
		Load_Image_FrameBuffer_2GRAY(IMG_W_FREE,39,67,34,17);					
	else//Black
		Load_Image_FrameBuffer_2GRAY(IMG_BLK,39,67,34,17);		

	//Display PET Filter
	if(disp_pet == 1)//GRAY
		Load_Image_FrameBuffer_2GRAY(IMG_G_PET,111,67,34,17);
	else if(disp_pet == 2)//WHITE
		Load_Image_FrameBuffer_2GRAY(IMG_W_PET,111,67,34,17);					
	else//Black
		Load_Image_FrameBuffer_2GRAY(IMG_BLK,111,67,34,17); 	

	//Display COMPLEX Filter
	if(disp_com == 1)//GRAY
		Load_Image_FrameBuffer_2GRAY(IMG_G_COM,182,67,34,17);
	else if(disp_com == 2)//WHITE
		Load_Image_FrameBuffer_2GRAY(IMG_W_COM,182,67,34,17);					
	else//Black
		Load_Image_FrameBuffer_2GRAY(IMG_BLK,182,67,34,17);			
}	

void Load_Set_FilterClear(U8 disp_data)
{
	//U8 disp_free, disp_pet, disp_com;

	fg_blink_mode = disp_data&0x03;

	if(fg_blink_mode !=0)
		cnt_500mS = 50;

	
	fg_blink_is_on = true;

	disp_free = (disp_data>>2)&0x03;
	disp_pet = (disp_data>>4)&0x03;
	disp_com = (disp_data>>6)&0x03;

	//Display BASE Image
	Load_Image_FrameBuffer_2GRAY(IMG_0202_BASE,0,0,256,96);

	//Display FREE Filter
	if(disp_free == 1)//GRAY
		Load_Image_FrameBuffer_2GRAY(IMG_G_FREE,39,67,34,17);
	else if(disp_free == 2)//WHITE
		Load_Image_FrameBuffer_2GRAY(IMG_W_FREE,39,67,34,17);					
	else//Black
		Load_Image_FrameBuffer_2GRAY(IMG_BLK,39,67,34,17);		

	//Display PET Filter
	if(disp_pet == 1)//GRAY
		Load_Image_FrameBuffer_2GRAY(IMG_G_PET,111,67,34,17);
	else if(disp_pet == 2)//WHITE
		Load_Image_FrameBuffer_2GRAY(IMG_W_PET,111,67,34,17);					
	else//Black
		Load_Image_FrameBuffer_2GRAY(IMG_BLK,111,67,34,17); 	

	//Display COMPLEX Filter
	if(disp_com == 1)//GRAY
		Load_Image_FrameBuffer_2GRAY(IMG_G_COM,182,67,34,17);
	else if(disp_com == 2)//WHITE
		Load_Image_FrameBuffer_2GRAY(IMG_W_COM,182,67,34,17);					
	else//Black
		Load_Image_FrameBuffer_2GRAY(IMG_BLK,182,67,34,17); 		
}	

void Load_Image_Set_Offtime(unsigned char offset)
{
	unsigned int index;

#if 0
//	Image size H = 177	  V = 29
//	Convert to Gray 2bit/pixel	Total : 1305 Bytes
	if(offset>12)//0~12시간.
		index = 0;
	else
		index = offset * 1305;
	
	Load_Image_FrameBuffer_2GRAY(&IMG_F00T12[index],39,55,177,29);
#else
//Image size H = 150	  V = 23
//Convert to Gray 2bit/pixel		Total : 874 Bytes

	if(offset>12)//0~12시간.
		index = 0;
	else
		index = offset * 874;
	
	Load_Image_FrameBuffer_2GRAY(&IMG_S00UT00_12[index],53,59,150,22);
#endif
}

void Load_Image_Test_Mode_Led(void)
{
	U16 offset;
	U16 snr_led;
	

	//Display MCU VERSION		 
	Load_Image_FrameBuffer_2GRAY(IMG_RGB,0,0,256,96);

	//Image size H = 14  V = 23
	//Convert to Gray 2bit/pixel	 Total : 92 Bytes							
	//RGB 1  이용한 3자리수로 표시.

	//Display RGB _R.
	snr_led = uart_rx_data[CMD_SUB1_IDX];

	offset = ((snr_led/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],121,6,14,23);

	offset = ((snr_led/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],135,6,14,23);

	offset = (snr_led%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],149,6,14,23);

	//Display RGB _G.
	snr_led = uart_rx_data[CMD_SUB2_IDX];

	offset = ((snr_led/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],121,36,14,23);

	offset = ((snr_led/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],135,36,14,23);

	offset = (snr_led%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],149,36,14,23);

	//Display RGB _B.
	snr_led = uart_rx_data[CMD_SUB3_IDX];

	offset = ((snr_led/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],121,66,14,23);

	offset = ((snr_led/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],135,66,14,23);

	offset = (snr_led%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],149,66,14,23);	
	
}

void Load_Image_Test_Mode_Filter(void)
{
	U16 offset;
	U16 snr_time;
	

	//Display MCU VERSION		 
	Load_Image_FrameBuffer_2GRAY(IMG_Filter,0,0,256,96);

	//Image size H = 14  V = 23
	//Convert to Gray 2bit/pixel	 Total : 92 Bytes							
	//시간 2바이트를 이용한 5자리수로 표시.

	//Display 프리필터 사용시간.
	snr_time = uart_rx_data[CMD_SUB1_IDX];
	snr_time = snr_time <<8;
	snr_time = snr_time+uart_rx_data[CMD_SUB2_IDX];

	offset = ((snr_time/10000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],121,6,14,23);
	
	offset = ((snr_time/1000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],135,6,14,23);

	offset = ((snr_time/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],149,6,14,23);

	offset = ((snr_time/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],163,6,14,23);

	offset = (snr_time%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],177,6,14,23);

	Load_Image_FrameBuffer_2GRAY(IMG_TMODE_HOUR,191,6,14,23);

	//Display 프리필터 사용분.
	snr_time = uart_rx_data[CMD_SUB3_IDX];
	snr_time = snr_time <<8;
	snr_time = snr_time+uart_rx_data[CMD_SUB4_IDX];

	offset = ((snr_time/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],215,6,14,23);

	offset = (snr_time%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],229,6,14,23);

	//Display 펫 필터 사용시간.
	snr_time = uart_rx_data[CMD_SUB5_IDX];
	snr_time = snr_time <<8;
	snr_time = snr_time+uart_rx_data[CMD_SUB6_IDX];

	offset = ((snr_time/10000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],121,36,14,23);
	
	offset = ((snr_time/1000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],135,36,14,23);

	offset = ((snr_time/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],149,36,14,23);

	offset = ((snr_time/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],163,36,14,23);

	offset = (snr_time%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],177,36,14,23);

	Load_Image_FrameBuffer_2GRAY(IMG_TMODE_HOUR,191,36,14,23);

	//Display 펫 필터 사용분.
	snr_time = uart_rx_data[CMD_SUB7_IDX];
	snr_time = snr_time <<8;
	snr_time = snr_time+uart_rx_data[CMD_SUB8_IDX];

	offset = ((snr_time/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],215,36,14,23);

	offset = (snr_time%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],229,36,14,23);	

	//Display 복합필터 사용시간.
	snr_time = uart_rx_data[CMD_SUB9_IDX];
	snr_time = snr_time <<8;
	snr_time = snr_time+uart_rx_data[CMD_SUB10_IDX];

	offset = ((snr_time/10000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],121,66,14,23);
	
	offset = ((snr_time/1000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],135,66,14,23);

	offset = ((snr_time/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],149,66,14,23);

	offset = ((snr_time/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],163,66,14,23);

	offset = (snr_time%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],177,66,14,23);

	Load_Image_FrameBuffer_2GRAY(IMG_TMODE_HOUR,191,66,14,23);

	//Display 복합필터 사용분.
	snr_time = uart_rx_data[CMD_SUB11_IDX];
	snr_time = snr_time <<8;
	snr_time = snr_time+uart_rx_data[CMD_SUB12_IDX];

	offset = ((snr_time/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],215,66,14,23);

	offset = (snr_time%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],229,66,14,23);		
	
}


void Load_Image_Test_Mode_Sensor(void)
{
	U16 offset;
	U16 snr_display;
	

	//Display MCU VERSION		 
	Load_Image_FrameBuffer_2GRAY(IMG_SENSOR,0,0,256,96);

	//Image size H = 14  V = 23
	//Convert to Gray 2bit/pixel	 Total : 92 Bytes							
	//4자리수로 표시.

	//Display PM1.0
	snr_display = uart_rx_data[CMD_SUB1_IDX];
	snr_display = snr_display <<8;
	snr_display = snr_display+uart_rx_data[CMD_SUB2_IDX];
	
	offset = ((snr_display/1000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],130,0,14,23);

	offset = ((snr_display/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],144,0,14,23);

	offset = ((snr_display/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],158,0,14,23);

	offset = (snr_display%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],172,0,14,23);

	//Display PM2.5
	snr_display = uart_rx_data[CMD_SUB3_IDX];
	snr_display = snr_display <<8;
	snr_display = snr_display+uart_rx_data[CMD_SUB4_IDX];
	
	offset = ((snr_display/1000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],130,24,14,23);

	offset = ((snr_display/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],144,24,14,23);

	offset = ((snr_display/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],158,24,14,23);

	offset = (snr_display%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],172,24,14,23);

	//Display PM10
	snr_display = uart_rx_data[CMD_SUB5_IDX];
	snr_display = snr_display <<8;
	snr_display = snr_display+uart_rx_data[CMD_SUB6_IDX];
	
	offset = ((snr_display/1000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],130,48,14,23);

	offset = ((snr_display/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],144,48,14,23);

	offset = ((snr_display/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],158,48,14,23);

	offset = (snr_display%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],172,48,14,23);	

	//Display CO2
	snr_display = uart_rx_data[CMD_SUB7_IDX];
	snr_display = snr_display <<8;
	snr_display = snr_display+uart_rx_data[CMD_SUB8_IDX];

	offset = ((snr_display/1000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],57,72,14,23);

	offset = ((snr_display/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],71,72,14,23);

	offset = ((snr_display/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],85,72,14,23);

	offset = (snr_display%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],99,72,14,23);	

	//Display CAS
	snr_display = uart_rx_data[CMD_SUB9_IDX];
	snr_display = snr_display <<8;
	snr_display = snr_display+uart_rx_data[CMD_SUB10_IDX];

	offset = ((snr_display/1000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],179,72,14,23);

	offset = ((snr_display/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],193,72,14,23);

	offset = ((snr_display/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],207,72,14,23);

	offset = (snr_display%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],221,72,14,23);	
	
}

void Load_Image_Test_Mode_RPM(void)
{
	U16 offset;
	U16 rpm_display;
	
	rpm_display = uart_rx_data[CMD_SUB1_IDX];
	rpm_display = rpm_display <<8;
	rpm_display = rpm_display+uart_rx_data[CMD_SUB2_IDX];

	//Display MCU VERSION		 
	Load_Image_FrameBuffer_2GRAY(IMG_RPM,0,0,256,96);

	//Image size H = 14  V = 23
	//Convert to Gray 2bit/pixel	 Total : 92 Bytes							
	//5자리수로 표시.
	//Display Tartget RPM
	offset = ((rpm_display/10000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],114,20,14,23);

	offset = ((rpm_display/1000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],128,20,14,23);

	offset = ((rpm_display/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],142,20,14,23);

	offset = ((rpm_display/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],156,20,14,23);

	offset = (rpm_display%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],170,20,14,23);

	//Display Current RPM
	rpm_display = uart_rx_data[CMD_SUB3_IDX];
	rpm_display = rpm_display <<8;
	rpm_display = rpm_display+uart_rx_data[CMD_SUB4_IDX];
	
	offset = ((rpm_display/10000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],114,52,14,23);

	offset = ((rpm_display/1000)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],128,52,14,23);

	offset = ((rpm_display/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],142,52,14,23);

	offset = ((rpm_display/10)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],156,52,14,23);

	offset = (rpm_display%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],170,52,14,23);
}

void Load_Image_Test_Mode_Version(void)
{
	U16 offset;

	//Display MCU VERSION		 
	Load_Image_FrameBuffer_2GRAY(IMG_VERSION,0,0,256,96);

#if 1//000.000표시.
	//VER MSB
	//Image size H = 14  V = 23
	//Convert to Gray 2bit/pixel	 Total : 92 Bytes							
	//DIGIG 100
	offset = ((uart_rx_data[CMD_SUB1_IDX]/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],112,20,14,23);
	//DIGIG 10
	offset = ((uart_rx_data[CMD_SUB1_IDX]%100)/10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],126,20,14,23);
	//DIGIG 1
	offset = (uart_rx_data[CMD_SUB1_IDX]%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],140,20,14,23);
	
	//DOT
	Load_Image_FrameBuffer_2GRAY(IMG_DOT,154,20,7,23);
	
	//LSB
	//DIGIG 100
	offset = ((uart_rx_data[CMD_SUB2_IDX]/100)%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],161,20,14,23);							

	//DIGIG 10
	offset = ((uart_rx_data[CMD_SUB2_IDX]%100)/10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],175,20,14,23);

	//DIGIG 1
	offset = (uart_rx_data[CMD_SUB2_IDX]%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],189,20,14,23);
	

	//Display LCD VERSION 00.00.00
	//VER YEAR 	
	offset = (LCD_VER_YEAR/10)*92; 
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],93,53,14,23);	
	offset = (LCD_VER_YEAR%10)*92; 
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],107,53,14,23);	
	//DOT
	Load_Image_FrameBuffer_2GRAY(IMG_DOT,121,53,7,23);

	//VER MON
	offset = (LCD_VER_MON/10)*92; 
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],128,53,14,23);	
	offset = (LCD_VER_MON%10)*92; 
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],142,53,14,23);	
	//DOT
	Load_Image_FrameBuffer_2GRAY(IMG_DOT,156,53,7,23);

	//VER DATE
	offset = (LCD_VER_DATE/10)*92; 
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],163,53,14,23);	
	offset = (LCD_VER_DATE%10)*92; 
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],177,53,14,23);	
#else//0.0표시.
	//VER MSB
	//Image size H = 14  V = 23
	//Convert to Gray 2bit/pixel	 Total : 92 Bytes							
	offset = (uart_rx_data[CMD_SUB1_IDX]%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],112,20,14,23);
	//DOT
	Load_Image_FrameBuffer_2GRAY(IMG_DOT,126,20,7,23);
	//LSB
	offset = (uart_rx_data[CMD_SUB2_IDX]%10)*92;
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],133,20,14,23); 							
	
	//Display LCD VERSION
	//VER MSB
	offset = (FW_Version[0]%10)*92;	
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],93,53,14,23);
	//DOT
	Load_Image_FrameBuffer_2GRAY(IMG_DOT,107,53,7,23);
	//LSB
	offset = (FW_Version[1]%10)*92;		
	Load_Image_FrameBuffer_2GRAY(&IMG_STNUM[offset],114,53,14,23);	
#endif
}
void Load_Image_Home_New(void)
{
	//오염도2 bytes, 대기질1, 오염도단위1, 운전모드1, 잠금표시1	
	U8 cur_pol_stat,cur_mode,cur_lock,cur_pol_step,cur_filter,cur_timer;
	U16 cur_pol_val;
	U16 offset;

	
	cur_pol_val = uart_rx_data[5];
	cur_pol_val = cur_pol_val <<8;
	cur_pol_val = cur_pol_val+uart_rx_data[6];

	cur_pol_stat = uart_rx_data[7];
	cur_pol_step = uart_rx_data[8];
	cur_mode = uart_rx_data[9];

	cur_lock = uart_rx_data[10]&0x01;
	cur_timer = uart_rx_data[10]&0x02;
	cur_filter = uart_rx_data[10]&0x04;	
//	if(prev_pol_val != cur_pol_val)
	{
		prev_pol_val = cur_pol_val;
		
		//display 1xx Size = 38*52
		offset = ((cur_pol_val/100)%10)*520;
		if(cur_pol_val<100)//표시안함.
			;//Load_Image_FrameBuffer_2GRAY(&IMG_LHOMENUM[offset],20,22,38,52);		
		else
			Load_Image_FrameBuffer_2GRAY(&IMG_LHOMENUM[offset],20,22,38,52);
		
		//display x1x		
		offset = ((cur_pol_val/10)%10)*520;
		if(cur_pol_val<10)
			;//10보다 작으면 자릿수 표시안함....
		else
			Load_Image_FrameBuffer_2GRAY(&IMG_LHOMENUM[offset],60,22,38,52);				
		
		//display xx1
		offset = (cur_pol_val%10)*520;		
		Load_Image_FrameBuffer_2GRAY(&IMG_LHOMENUM[offset],100,22,38,52);
	}

//	if(prev_pol_stat != cur_pol_stat)
	{
		prev_pol_stat = cur_pol_stat;

		switch(cur_pol_stat)
		{
			case 0:	Load_Image_FrameBuffer_2GRAY(IMG_AIR00,148,17,70,18);//GOOD
					break;
			case 1: Load_Image_FrameBuffer_2GRAY(IMG_AIR01,148,17,70,18);//NOR
					break;
			case 2: Load_Image_FrameBuffer_2GRAY(IMG_AIR02,148,17,70,18);//BAD
					break;					
			case 3: Load_Image_FrameBuffer_2GRAY(IMG_AIR03,148,17,70,18);//WORST
					break;	
			default: 
					break;
		}
	}

//	if(prev_mode != cur_mode)
	{
		prev_mode = cur_mode;
		//clear
		//Load_Image_FrameBuffer_2GRAY(IMG_0001_0100B,152,45,42,14);
		switch(cur_mode)
		{
			case 0: Load_Image_FrameBuffer_2GRAY(IMG_MODE_00,148,41,70,18);//자동
					break;
			case 1: Load_Image_FrameBuffer_2GRAY(IMG_MODE_01,148,41,70,18);//약
					break;
			case 2: Load_Image_FrameBuffer_2GRAY(IMG_MODE_02,148,41,70,18);//강
					break;					
			case 3: Load_Image_FrameBuffer_2GRAY(IMG_MODE_03,148,41,70,18);//터보.
					break;
			case 4: Load_Image_FrameBuffer_2GRAY(IMG_MODE_04,148,41,70,18);//수면.
					break;						
			case 5: Load_Image_FrameBuffer_2GRAY(IMG_MODE_05,148,41,70,18);//수유.
					break;					
			default: break;
		}		
	}

//	if(prev_pol_step != cur_pol_step)
	{
		prev_pol_step = cur_pol_step;
		//clear
		//Load_Image_FrameBuffer_2GRAY(IMG_0001_0200B,152,59,37,14);
		switch(cur_pol_step)
		{
			case 0: Load_Image_FrameBuffer_2GRAY(IMG_PM1_0,148,65,52,14);//1.0
					break;
			case 1: Load_Image_FrameBuffer_2GRAY(IMG_PM2_5,148,65,52,14);//2.5
					break;
			case 2: Load_Image_FrameBuffer_2GRAY(IMG_PM10,148,65,52,14);//10			
					break;					
			default: break;
		}
	}	


//	if(prev_filter != cur_filter)
	{
		prev_filter = cur_filter;
		//clear
		if(cur_filter)
			Load_Image_FrameBuffer_2GRAY(IMG_H_FILTER,223,17,15,17);
		else
			Load_Image_FrameBuffer_2GRAY(IMG_H_FILTER_OFF,223,17,15,17);
	}

	prev_timer = cur_timer;
	//clear
	if(cur_timer)
		Load_Image_FrameBuffer_2GRAY(IMG_H_TIMER,223,40,15,15);
	else
		Load_Image_FrameBuffer_2GRAY(IMG_H_TIMER_OFF,223,40,15,15);

//	if(prev_lock != cur_lock)
	{
		prev_lock = cur_lock;
		//clear
		if(cur_lock)
			Load_Image_FrameBuffer_2GRAY(IMG_H_LOCK,223,61,15,18);//Black으로 표시하도록 변경 260115
		else
			Load_Image_FrameBuffer_2GRAY(IMG_H_LOCK_OFF,223,61,15,18);
	}
	

}

void Load_Image_Home(void)
{
	//오염도2 bytes, 대기질1, 오염도단위1, 운전모드1, 잠금표시1	
	U8 cur_pol_stat,cur_mode,cur_lock,cur_pol_step;
	U16 cur_pol_val;
	U16 offset;

	
	cur_pol_val = uart_rx_data[5];
	cur_pol_val = cur_pol_val <<8;
	cur_pol_val = cur_pol_val+uart_rx_data[6];

	cur_pol_stat = uart_rx_data[7];
	cur_pol_step = uart_rx_data[8];
	cur_mode = uart_rx_data[9];
	cur_lock = uart_rx_data[10];	
	
//	if(prev_pol_val != cur_pol_val)
	{
		prev_pol_val = cur_pol_val;
		//display 1xx
		offset = ((cur_pol_val/100)%10)*441;
		Load_Image_FrameBuffer_2GRAY(&IMG_HOMENUM[offset],37,25,35,49);		
		//display x1x
		offset = ((cur_pol_val/10)%10)*441;
		Load_Image_FrameBuffer_2GRAY(&IMG_HOMENUM[offset],74,25,35,49);				
		//display xx1
		offset = (cur_pol_val%10)*441;		
		Load_Image_FrameBuffer_2GRAY(&IMG_HOMENUM[offset],112,25,35,49);
	}

//	if(prev_pol_stat != cur_pol_stat)
	{
		prev_pol_stat = cur_pol_stat;
		//clear
		//Load_Image_FrameBuffer_2GRAY(IMG_0001_0000B,152,23,60,15);
		switch(cur_pol_stat)
		{
			case 0: Load_Image_FrameBuffer_2GRAY(IMG_0001_0000,152,23,59,16);//GOOD
					break;
			case 1: Load_Image_FrameBuffer_2GRAY(IMG_0001_0001,152,23,59,16);//NOR
					break;
			case 2: Load_Image_FrameBuffer_2GRAY(IMG_0001_0002,152,23,59,16);//BAD
					break;					
			case 3: Load_Image_FrameBuffer_2GRAY(IMG_0001_0003,152,23,59,16);//WORST
					break;	
			default: break;
		}
	}

//	if(prev_mode != cur_mode)
	{
		prev_mode = cur_mode;
		//clear
		//Load_Image_FrameBuffer_2GRAY(IMG_0001_0100B,152,45,42,14);
		switch(cur_mode)
		{
			case 0: Load_Image_FrameBuffer_2GRAY(IMG_0001_0100,152,45,41,14);//자동
					break;
			case 1: Load_Image_FrameBuffer_2GRAY(IMG_0001_0101,152,45,41,14);//약
					break;
			case 2: Load_Image_FrameBuffer_2GRAY(IMG_0001_0102,152,45,41,14);//강
					break;					
			case 3: Load_Image_FrameBuffer_2GRAY(IMG_0001_0103,152,45,41,14);//터보.
					break;
			case 4: Load_Image_FrameBuffer_2GRAY(IMG_0001_0104,152,45,41,14);//수면.
					break;						
			case 5: Load_Image_FrameBuffer_2GRAY(IMG_0001_0105,152,45,41,14);//수유.
					break;					
			default: break;
		}		
	}

//	if(prev_pol_step != cur_pol_step)
	{
		prev_pol_step = cur_pol_step;
		//clear
		//Load_Image_FrameBuffer_2GRAY(IMG_0001_0200B,152,59,37,14);
		switch(cur_pol_step)
		{
			case 0: Load_Image_FrameBuffer_2GRAY(IMG_0001_0200,152,59,36,14);//1.0
					break;
			case 1: Load_Image_FrameBuffer_2GRAY(IMG_0001_0201,152,59,36,14);//2.5
					break;
			case 2: Load_Image_FrameBuffer_2GRAY(IMG_0001_0202,152,59,36,14);//10			
					break;					
			default: break;
		}
	}	

//	if(prev_lock != cur_lock)
	{
		prev_lock = cur_lock;
		//clear
		if(cur_lock)
			Load_Image_FrameBuffer_2GRAY(IMG_UNLOCK,199,45,17,28);
		else
			Load_Image_FrameBuffer_2GRAY(IMG_LOCK,199,45,17,28);
	}
}
void raon_dispaly_service(void)
{
	//load & display ICON scene
//	U16 Scene_ID;
	U16 cnt_pwm;

	Curr_Scene_ID = uart_rx_data[CMD_SCNID_MSB_IDX];
	Curr_Scene_ID = Curr_Scene_ID<<8;
	Curr_Scene_ID += uart_rx_data[CMD_SCNID_LSB_IDX];
	
	debugprintf("Scene_ID: 0x%4x.\r\n",Curr_Scene_ID);

	fg_blink_mode = 0;
	
	if(Curr_Scene_ID == SCN_DEMO)
	{
		fg_demo_mode = true;		
		cnt_10mS = 0;
		Time0_1000mS = 0;
		Pre_Time0_1000mS=0;
	}
	else
		fg_demo_mode = false;		

	switch(Curr_Scene_ID)
	{
		case SCN_INTRO:	Clear_Frame_Buffer();
						if(uart_rx_data[CMD_SUB1_IDX]==1)
							Load_Image_FrameBuffer_2GRAY(IMG_01_25696,0,0,256,96);							
						else if(uart_rx_data[CMD_SUB1_IDX]==2)
							Load_Image_FrameBuffer_2GRAY(IMG_02_25696,0,0,256,96);
						else if(uart_rx_data[CMD_SUB1_IDX]==3)
							Load_Image_FrameBuffer_2GRAY(IMG_03_25696,0,0,256,96);		
						else if(uart_rx_data[CMD_SUB1_IDX]==4)
							Load_Image_FrameBuffer_2GRAY(IMG_QR,0,0,256,96);								
						else
							Load_Image_FrameBuffer_2GRAY(IMG_LOGO_QM,0,0,256,96);//Load_Image_FrameBuffer_2GRAY(IMG_LOGO_QM_G2,67,32,124,34);						
						break;
						
		case SCN_MODE:	Clear_Frame_Buffer();//30% 적용.
						if(uart_rx_data[CMD_SUB1_IDX]==1)
							Load_Image_FrameBuffer_2GRAY(IMG_D01,0,0,256,96);
						else if(uart_rx_data[CMD_SUB1_IDX]==2)
							Load_Image_FrameBuffer_2GRAY(IMG_D02,0,0,256,96);
						else if(uart_rx_data[CMD_SUB1_IDX]==3)
							Load_Image_FrameBuffer_2GRAY(IMG_D03,0,0,256,96);
						else if(uart_rx_data[CMD_SUB1_IDX]==4)
							Load_Image_FrameBuffer_2GRAY(IMG_D04,0,0,256,96);						
						else if(uart_rx_data[CMD_SUB1_IDX]==5)
							Load_Image_FrameBuffer_2GRAY(IMG_D05,0,0,256,96);
						else
							Load_Image_FrameBuffer_2GRAY(IMG_D00,0,0,256,96);						
						break;
						
		case SCN_DEMO:	Clear_Frame_Buffer();
						//Display 1st Image in Demo Mode.
						Load_Image_FrameBuffer_2GRAY(IMG_LOGO_QM_G2,67,32,124,34);
						break;						
		case SCN_HOME:	//if(Prev_Scene_ID != Scene_ID)//전체 클리어 필요체크.
							Clear_Frame_Buffer();
						#if 1
							//Load_Image_Home();	
							Load_Image_Home_New();	
						#else
								//Display 1st Image in Demo Mode.
								Load_Image_FrameBuffer_2GRAY(IMG_M00,0,0,256,96);
						#endif						
								break;		
		case SCN_SET_OFFTIME:	Clear_Frame_Buffer();
								//Display Base Image
								//Load_Image_FrameBuffer_2GRAY(IMG_T0100_BASE,0,0,256,96);
								Load_Image_FrameBuffer_2GRAY(IMG_S0000,0,0,256,96);
								Load_Image_Set_Offtime(uart_rx_data[CMD_SUB1_IDX]);							
								break;
								
		case SCN_ILLUM_MODE:	Clear_Frame_Buffer();
								if(uart_rx_data[CMD_SUB1_IDX]==1)
									Load_Image_FrameBuffer_2GRAY(IMG_S0101,0,0,256,96);//오염도.
								else
									Load_Image_FrameBuffer_2GRAY(IMG_S0100,0,0,256,96);//무드등.
								break;				
		case SCN_ILLUM_STEP:	Clear_Frame_Buffer();
								if(uart_rx_data[CMD_SUB1_IDX]==1)
									Load_Image_FrameBuffer_2GRAY(IMG_S0201,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==2)
									Load_Image_FrameBuffer_2GRAY(IMG_S0202,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==3)
									Load_Image_FrameBuffer_2GRAY(IMG_S0203,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==4)
									Load_Image_FrameBuffer_2GRAY(IMG_S0204,0,0,256,96);//수유
								else if(uart_rx_data[CMD_SUB1_IDX]==5)
									Load_Image_FrameBuffer_2GRAY(IMG_S0205,0,0,256,96);//수면.
								else
									Load_Image_FrameBuffer_2GRAY(IMG_S0200,0,0,256,96);								
								break;
		case SCN_BRIGHT:		Clear_Frame_Buffer();
								if(uart_rx_data[CMD_SUB1_IDX]==1)								
									Load_Image_FrameBuffer_2GRAY(IMG_S0301,0,0,256,96);//STEP2
								else if(uart_rx_data[CMD_SUB1_IDX]==2)								
									Load_Image_FrameBuffer_2GRAY(IMG_S0302,0,0,256,96);//STEP3
								else if(uart_rx_data[CMD_SUB1_IDX]==3)								
									Load_Image_FrameBuffer_2GRAY(IMG_S0303,0,0,256,96);//수유
								else if(uart_rx_data[CMD_SUB1_IDX]==4)								
									Load_Image_FrameBuffer_2GRAY(IMG_S0304,0,0,256,96);//수면.
								else			
									Load_Image_FrameBuffer_2GRAY(IMG_S0300,0,0,256,96);//STEP 1
								//밝기 조절....
								
								break;
		case SCN_SOUND_MODE:	Clear_Frame_Buffer();
								if(uart_rx_data[CMD_SUB1_IDX]==1)								
									Load_Image_FrameBuffer_2GRAY(IMG_S0401,0,0,256,96);//효과음.
								else if(uart_rx_data[CMD_SUB1_IDX]==2)								
									Load_Image_FrameBuffer_2GRAY(IMG_S0402,0,0,256,96);//수유
								else if(uart_rx_data[CMD_SUB1_IDX]==3)								
									Load_Image_FrameBuffer_2GRAY(IMG_S0403,0,0,256,96);//수면.	
								else
									Load_Image_FrameBuffer_2GRAY(IMG_S0400,0,0,256,96);//음성안내.
								break;			
		case SCN_SOUND_STEP:	Clear_Frame_Buffer();
								if(uart_rx_data[CMD_SUB1_IDX]==1)
									Load_Image_FrameBuffer_2GRAY(IMG_S0501,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==2)
									Load_Image_FrameBuffer_2GRAY(IMG_S0502,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==3)
									Load_Image_FrameBuffer_2GRAY(IMG_S0503,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==4)
									Load_Image_FrameBuffer_2GRAY(IMG_S0504,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==5)
									Load_Image_FrameBuffer_2GRAY(IMG_S0505,0,0,256,96);								
								else 
									Load_Image_FrameBuffer_2GRAY(IMG_S0500,0,0,256,96);//무음.								
								break;
		case SCN_FILTER_STEP:		Clear_Frame_Buffer();
								if(uart_rx_data[CMD_SUB1_IDX]==1)
									Load_Image_FrameBuffer_2GRAY(IMG_S0601,0,0,256,96);//보통 
								else if(uart_rx_data[CMD_SUB1_IDX]==2)
									Load_Image_FrameBuffer_2GRAY(IMG_S0602,0,0,256,96);//민감.
								else
									Load_Image_FrameBuffer_2GRAY(IMG_S0600,0,0,256,96);//둔감.
								break;
		case SCN_FILTER_ALARM:	Clear_Frame_Buffer();
								#if 1
								Load_Set_Alarm(uart_rx_data[CMD_SUB1_IDX]);
								#else								
								if(uart_rx_data[CMD_SUB1_IDX]==1)
									Load_Image_FrameBuffer_2GRAY(IMG_0701,0,0,256,96);//프리
								else if(uart_rx_data[CMD_SUB1_IDX]==2)
									Load_Image_FrameBuffer_2GRAY(IMG_0702,0,0,256,96);//펫
								else if(uart_rx_data[CMD_SUB1_IDX]==3)
									Load_Image_FrameBuffer_2GRAY(IMG_0703,0,0,256,96);//복합.
								else
									Load_Image_FrameBuffer_2GRAY(IMG_0700,0,0,256,96);//미선택.
								#endif
								break;
		case SCN_FILT_POPUP:	Clear_Frame_Buffer();
								#if 1
								Load_Set_FilterPopup(uart_rx_data[CMD_SUB1_IDX]);
								#else
								//Display 1st Image in Demo Mode.
								if(uart_rx_data[CMD_SUB1_IDX]==1)
									Load_Image_FrameBuffer_2GRAY(IMG_0200_01,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==2)
									Load_Image_FrameBuffer_2GRAY(IMG_0200_02,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==3)
									Load_Image_FrameBuffer_2GRAY(IMG_0200_03,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==4)
									Load_Image_FrameBuffer_2GRAY(IMG_0200_04,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==5)
									Load_Image_FrameBuffer_2GRAY(IMG_0200_05,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==6)
									Load_Image_FrameBuffer_2GRAY(IMG_0200_06,0,0,256,96);								
								else if(uart_rx_data[CMD_SUB1_IDX]==7)
									Load_Image_FrameBuffer_2GRAY(IMG_0200_07,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==8)
									Load_Image_FrameBuffer_2GRAY(IMG_0200_08,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==9)
									Load_Image_FrameBuffer_2GRAY(IMG_0200_09,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==10)
									Load_Image_FrameBuffer_2GRAY(IMG_0200_10,0,0,256,96);
								else 
									Load_Image_FrameBuffer_2GRAY(IMG_0200_00,0,0,256,96);
								#endif
								break;
		case SCN_NORM_POPUP:	Clear_Frame_Buffer();
								//Display 1st Image in Demo Mode.
								if(uart_rx_data[CMD_SUB1_IDX]==1)
									//Load_Image_FrameBuffer_2GRAY(IMG_0201_01,0,0,256,96);
									Load_Image_FrameBuffer_2GRAY(IMG_0201_01_NEW,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==2)
									Load_Image_FrameBuffer_2GRAY(IMG_0201_02,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==3)
									Load_Image_FrameBuffer_2GRAY(IMG_0201_03,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==4)
									Load_Image_FrameBuffer_2GRAY(IMG_0201_04,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==5)
									Load_Image_FrameBuffer_2GRAY(IMG_0201_05,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==6)
									Load_Image_FrameBuffer_2GRAY(IMG_N0201_06,0,0,256,96);//Load_Image_FrameBuffer_2GRAY(IMG_0201_06,0,0,256,96);								
								else if(uart_rx_data[CMD_SUB1_IDX]==7)
									Load_Image_FrameBuffer_2GRAY(IMG_0201_07,0,0,256,96);								
								else if(uart_rx_data[CMD_SUB1_IDX]==8)
									Load_Image_FrameBuffer_2GRAY(IMG_0201_08,0,0,256,96);								
								else if(uart_rx_data[CMD_SUB1_IDX]==9)
									Load_Image_FrameBuffer_2GRAY(IMG_0201_09,0,0,256,96);																
								else if(uart_rx_data[CMD_SUB1_IDX]==10)
									Load_Image_FrameBuffer_2GRAY(IMG_0201_10,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==11)
									Load_Image_FrameBuffer_2GRAY(IMG_0201_11,0,0,256,96);								
								else 
									Load_Image_FrameBuffer_2GRAY(IMG_0201_00,0,0,256,96);
								break;	
								
		case SCN_FILT_CLEAR:	Clear_Frame_Buffer();
								Load_Set_FilterClear(uart_rx_data[CMD_SUB1_IDX]);
								break;		
								
		case SCN_ERR_POPUP:		Clear_Frame_Buffer();
								if(uart_rx_data[CMD_SUB1_IDX]==2)
									Load_Image_FrameBuffer_2GRAY(IMG_E0203_02,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==3)
									Load_Image_FrameBuffer_2GRAY(IMG_E0203_03,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==4)
									Load_Image_FrameBuffer_2GRAY(IMG_E0203_04,0,0,256,96);
								else if(uart_rx_data[CMD_SUB1_IDX]==5)
									Load_Image_FrameBuffer_2GRAY(IMG_E0203_05,0,0,256,96);
								else
									Load_Image_FrameBuffer_2GRAY(IMG_E0203_01,0,0,256,96);
								break;
			
		case SCN_TEST:		if(uart_rx_data[CMD_SUB1_IDX])//Display White
								Set_Frame_Buffer();
							else
								Clear_Frame_Buffer();//Display Black
							//Load_Image_FrameBuffer_2GRAY(IMG_WHITEREG_1010,0,0,12,10);
							break;
						
		case SCN_LCD_EN:	debugprintf("LCD Enable Command:%d(0:0x28(OFF), else:0x29(ON)).\r\n",uart_rx_data[CMD_SUB1_IDX]);
							if(uart_rx_data[CMD_SUB1_IDX])
								Write_REG_Index(0x29);
							else
								Write_REG_Index(0x28);
							break;
							
		case SCN_BKCTRL_BK: if(uart_rx_data[CMD_SUB1_IDX]>100)//0~100
								cnt_pwm= 0;
							else
								cnt_pwm = 300-(uart_rx_data[CMD_SUB1_IDX]*3);

							debugprintf("LCD BackLight PWM Duty: %d(%%).\r\n",uart_rx_data[CMD_SUB1_IDX]);
							//set_pwm_ex(PWM_CH, 600, cnt_pwm, 0, false, false); // PWM channel 1, 60Hz, pulse count 100 -> occur interrupt.
							set_pwm_ex(PWM_CH, 300, cnt_pwm, 0, false, false);// 6MHz/300=20KHz
							Curr_PWM_Dudy = uart_rx_data[CMD_SUB1_IDX];
							break;
							
		case SCN_TMODE_VER: Clear_Frame_Buffer();
							Load_Image_Test_Mode_Version();
							break; 
		case SCN_TMODE_RPM: Clear_Frame_Buffer();
							Load_Image_Test_Mode_RPM();		
							break;
		case SCN_TMODE_SNR: Clear_Frame_Buffer();
							Load_Image_Test_Mode_Sensor();		
							break;
		case SCN_TMODE_FILT: Clear_Frame_Buffer();
							Load_Image_Test_Mode_Filter();		
							break;
		case SCN_TMODE_LED: Clear_Frame_Buffer();
							Load_Image_Test_Mode_Led();		
							break;			
		default: 		break;
	}

	Prev_Scene_ID = Curr_Scene_ID;

	if(Curr_Scene_ID != SCN_LCD_EN) 	
	{
		TFT_LCD_225Inch_SPI_TX(2);
		LCD_BL_gpio_write(1);		
		Write_REG_Index(0x29);	
	}
}

void raon_portinit(void)
{
	//*R_PAF(0) = F_PAF0_0_GP0 | F_PAF0_1_GP1 | F_PAF0_2_GP2 | F_PAF0_3_GP3 | F_PAF0_4_UART3_TX| F_PAF0_5_TWI0_SDA | F_PAF0_6_TWI0_SCL | F_PAF0_7_TIMER1_PWM;
	*R_PAF(0) = F_PAF0_0_GP0 | F_PAF0_1_UART2_RX| F_PAF0_2_UART2_TX| F_PAF0_3_GP3 | F_PAF0_4_GP4| F_PAF0_5_TWI0_SDA | F_PAF0_6_TWI0_SCL | F_PAF0_7_TIMER1_PWM;
#if 1
	*R_PAF(1) = F_PAF1_0_SF_CS | F_PAF1_1_SF_DQ1 | F_PAF1_2_SF_DQ2 | F_PAF1_3_GP3 | F_PAF1_4_GP4  | F_PAF1_5_SF_DQ3 | F_PAF1_6_GP6 | F_PAF1_7_GP7;
#else
	//*R_PAF(1) = F_PAF1_0_SF_CS | F_PAF1_1_SF_DQ1 | F_PAF1_2_SF_DQ2 | F_PAF1_3_SF_DQ0 | F_PAF1_4_SF_CLK  | F_PAF1_5_SF_DQ3 | F_PAF1_6_GP6 | F_PAF1_7_GP7;
#endif	
	*R_PAF(2) = F_PAF2_0_GP0 | F_PAF2_1_GP1 | F_PAF2_2_GP2| F_PAF2_3_GP3;	
	*R_PAF(4) = F_PAF4_0_GP0	 | F_PAF4_1_SPWM_P0 | F_PAF4_2_GP2 | F_PAF4_3_GP3;
	*R_PAF(5) = F_PAF5_0_UART0_TX | F_PAF5_1_UART0_RX | F_PAF5_2_GP2 | F_PAF5_3_GP3 | F_PAF5_4_SPI1_CS | F_PAF5_5_SPI1_SDO | F_PAF5_6_GP6 | F_PAF5_7_SPI1_CLK;
	*R_PAF(6) = F_PAF6_0_GP0 | F_PAF6_1_GP1 | F_PAF6_2_GP2;
	*R_PAF(7) = F_PAF7_0_GP0 | F_PAF7_1_GP1;

	*R_GPODIR(1) |= 1<<3 ;	// LCD Data/Cmd
	*R_GPODIR(1) |= 1<<4 ;	// LCD RESET
	*R_GPODIR(4) |= 1<<0 ;	// LCD BackLight EN
	*R_GPOLOW(4) = 1<<0;	//LCD BackLight Pin = "L"
}

void raon_systeminit(void)
{
	
	//01.UART Init
	set_debug_channel(DEBUG_CHANNEL);

    uart_config(DEBUG_CHANNEL, 115200, DATABITS_8, STOPBITS_1, UART_PARNONE);	 
	uart_config(MAIN_CHANNEL, 38400, DATABITS_8, STOPBITS_1, UART_PARNONE);
	
	debugstring("\r\n==========================================================================\r\n");
    debugprintf("SMX_Quming_2.25Inch_FW:[V%02d.%02d.%02d 38400bps][Build Date:%s]\r\n", LCD_VER_YEAR, LCD_VER_MON, LCD_VER_DATE,__DATE__);
	debugstring("==========================================================================\r\n");

	//02.SPI Init
	spi_master_init(SPI_CH);
    //spi_set_freq(SPI_CH, SPI_MASTER, 10000000);	//12MHz
	//spi_set_freq(SPI_CH, SPI_MASTER, 9000000);	//9.6MHz
	spi_set_freq(SPI_CH, SPI_MASTER, 8000000);	//8.0MHz
	//spi_set_freq(SPI_CH, SPI_MASTER, 6000000);	//6.0MHz	
	//spi_set_freq(SPI_CH, SPI_MASTER, 1000000);	//1.0MHz	

	//03.Timer Init
	Variable_Init();
	Timer_Init();

	//04.Set PWM
	//set_pwm_ex(PWM_CH, 600, 180, 0, false, false); // PWM channel 1, 60Hz, pulse count 100 -> occur interrupt.	
	//set_pwm_ex(PWM_CH, 300, 150, 0, false, false);// 6MHz/300=20KHz Duty 300/150=50%
	set_pwm_ex(PWM_CH, 300, 300, 0, false, false);// 6MHz/300=20KHz Duty 300-300=0% OFF
	Curr_PWM_Dudy=0;

	//05.SPI LCD Register Init(ST7735)
	TFT_LCD_225Inch_Init_frida();
	
	//06.Clear FrameBuffer
	TFT_LCD_225Inch_all_black_fill();
	
}

void uart_tx_message(unsigned char mode, unsigned char err_num)
{
	unsigned char i;
	unsigned char buf[10];
	unsigned char cnt;	
	unsigned int checksum=0;

	if(mode==0)//TEST OK=>  52 41 FF FF 02 4F 4B D3
	{
		cnt=9;//8->9  Add PWM Value
		buf[0]=UART_CMD_START;
		buf[1]=UART_CMD_2ND;//LEN
		buf[2]=0xFF;
		buf[3]=0xFF;
		buf[4]=0x03;
		buf[5]='O';
		buf[6]='K';				
		buf[7]=Curr_PWM_Dudy;//PWM %Value 0~100

		for(i=0; i<8; i++)
			checksum += buf[i];

//		debugprintf("sum checksum: 0x%x.\r\n",checksum);

		checksum = checksum & 0x00FF;
//		debugprintf("sum checksum1: 0x%x.\r\n",checksum);
		
		checksum = 0x100 - checksum;			
		buf[8]= checksum;//Check Sum		
//		debugprintf("sum checksum2: 0x%x.\r\n",checksum);
		
	}
	else //TEST ERR => 52 41 FF FF  04 45 52 52 30  XX
	{
		cnt = 10;
		buf[0]=UART_CMD_START;
		buf[1]=UART_CMD_2ND;
		buf[2]=0xFF;		
		buf[3]=0xFF;
		buf[4]=4;//LEN
		buf[5]='E';
		buf[6]='R';
		buf[7]='R';		
		buf[8]=0x30+err_num;
		buf[9]=0x52-err_num;		
	}

	for(i=0; i<cnt; i++)
	{
		uart_putch(MAIN_CHANNEL, buf[i] );
	}
}

void raon_blinkdisp_setfilter_service_new(void)//Add 260212
{
//	debugprintf("display_blink_filter_setup_mode(%d,%d).\r\n",fg_blink_mode,fg_blink_is_on);
	
	fg_blink_is_on = !fg_blink_is_on;
	if(fg_blink_mode == 1)//FREE TOGGLE
	{
		if(fg_blink_is_on)
		{
			//White & Gray 표시.
			if(disp_free == 1)//GRAY
				Load_Image_FrameBuffer_2GRAY(IMG_S07_FREE_G,35,69,60,22);
			else if(disp_free == 2)//WHITE
				Load_Image_FrameBuffer_2GRAY(IMG_S07_FREE_W,35,69,60,22);					
			else//Black
				Load_Image_FrameBuffer_2GRAY(IMG_S07_FREE_B,35,69,60,22);										
		}
		else
		{
			//Black  표시.				
			Load_Image_FrameBuffer_2GRAY(IMG_S07_FREE_B,35,69,60,22);														
		}
	}
	else if(fg_blink_mode == 2)//PET TOGGLE
	{
		if(fg_blink_is_on)
		{
			//White & Gray 표시.
			if(disp_pet == 1)//GRAY
				Load_Image_FrameBuffer_2GRAY(IMG_S07_PET_G,98,69,60,22);
			else if(disp_pet == 2)//WHITE
				Load_Image_FrameBuffer_2GRAY(IMG_S07_PET_W,98,69,60,22);					
			else//Black
				Load_Image_FrameBuffer_2GRAY(IMG_S07_PET_B,98,69,60,22); 									
		}
		else
		{
			//Black  표시.				
			Load_Image_FrameBuffer_2GRAY(IMG_S07_PET_B,98,69,60,22);													
		}
	}			
	else if(fg_blink_mode == 3)//COMPLEX TOGGLE
	{
		if(fg_blink_is_on)
		{
			//White & Gray 표시.
			if(disp_com == 1)//GRAY
				Load_Image_FrameBuffer_2GRAY(IMG_S07_COM_G,161,69,60,22);
			else if(disp_com == 2)//WHITE
				Load_Image_FrameBuffer_2GRAY(IMG_S07_COM_W,161,69,60,22);					
			else//Black
				Load_Image_FrameBuffer_2GRAY(IMG_S07_COM_B,161,69,60,22);									
		}
		else
		{
			//Black  표시.				
			Load_Image_FrameBuffer_2GRAY(IMG_S07_COM_B,161,69,60,22);													
		}
	}	
	else
		;//
	
	TFT_LCD_225Inch_SPI_TX(2);
	LCD_BL_gpio_write(1);		
	Write_REG_Index(0x29);

}

void raon_blinkdisp_setfilter_service(void)
{
//	debugprintf("display_blink_filter_setup_mode(%d,%d).\r\n",fg_blink_mode,fg_blink_is_on);
	
	fg_blink_is_on = !fg_blink_is_on;
	if(fg_blink_mode == 1)//FREE TOGGLE
	{
		if(fg_blink_is_on)
		{
			//White & Gray 표시.
			if(disp_free == 1)//GRAY
				Load_Image_FrameBuffer_2GRAY(IMG_G_FREE,39,70,34,17);
			else if(disp_free == 2)//WHITE
				Load_Image_FrameBuffer_2GRAY(IMG_W_FREE,39,70,34,17);					
			else//Black
				Load_Image_FrameBuffer_2GRAY(IMG_BLK,39,70,34,17);										
		}
		else
		{
			//Black  표시.				
			Load_Image_FrameBuffer_2GRAY(IMG_BLK,39,70,34,17);															
		}
	}
	else if(fg_blink_mode == 2)//PET TOGGLE
	{
		if(fg_blink_is_on)
		{
			//White & Gray 표시.
			if(disp_pet == 1)//GRAY
				Load_Image_FrameBuffer_2GRAY(IMG_G_PET,111,70,34,17);
			else if(disp_pet == 2)//WHITE
				Load_Image_FrameBuffer_2GRAY(IMG_W_PET,111,70,34,17);					
			else//Black
				Load_Image_FrameBuffer_2GRAY(IMG_BLK,111,70,34,17); 									
		}
		else
		{
			//Black  표시.				
			Load_Image_FrameBuffer_2GRAY(IMG_BLK,111,70,34,17); 														
		}
	}			
	else if(fg_blink_mode == 3)//COMPLEX TOGGLE
	{
		if(fg_blink_is_on)
		{
			//White & Gray 표시.
			if(disp_com == 1)//GRAY
				Load_Image_FrameBuffer_2GRAY(IMG_G_COM,182,70,34,17);
			else if(disp_com == 2)//WHITE
				Load_Image_FrameBuffer_2GRAY(IMG_W_COM,182,70,34,17);					
			else//Black
				Load_Image_FrameBuffer_2GRAY(IMG_BLK,182,70,34,17); 									
		}
		else
		{
			//Black  표시.				
			Load_Image_FrameBuffer_2GRAY(IMG_BLK,182,70,34,17); 														
		}
	}	
	else
		;//
	
	TFT_LCD_225Inch_SPI_TX(2);
	LCD_BL_gpio_write(1);		
	Write_REG_Index(0x29);

}

void raon_blinkdisp_popfilter_service(void)
{
//	debugprintf("display_blink_filter_popup_mode(%d,%d).\r\n",fg_blink_mode,fg_blink_is_on);
	
	fg_blink_is_on = !fg_blink_is_on;
	if(fg_blink_mode == 1)//FREE TOGGLE
	{
		if(fg_blink_is_on)
		{
			//White & Gray 표시.
			if(disp_free == 1)//GRAY
				Load_Image_FrameBuffer_2GRAY(IMG_G_FREE,39,67,34,17);
			else if(disp_free == 2)//WHITE
				Load_Image_FrameBuffer_2GRAY(IMG_W_FREE,39,67,34,17);					
			else//Black
				Load_Image_FrameBuffer_2GRAY(IMG_BLK,39,67,34,17);										
		}
		else
		{
			//Black  표시.				
			Load_Image_FrameBuffer_2GRAY(IMG_BLK,39,67,34,17);															
		}
	}
	else if(fg_blink_mode == 2)//PET TOGGLE
	{
		if(fg_blink_is_on)
		{
			//White & Gray 표시.
			if(disp_pet == 1)//GRAY
				Load_Image_FrameBuffer_2GRAY(IMG_G_PET,111,67,34,17);
			else if(disp_pet == 2)//WHITE
				Load_Image_FrameBuffer_2GRAY(IMG_W_PET,111,67,34,17);					
			else//Black
				Load_Image_FrameBuffer_2GRAY(IMG_BLK,111,67,34,17); 									
		}
		else
		{
			//Black  표시.				
			Load_Image_FrameBuffer_2GRAY(IMG_BLK,111,67,34,17); 														
		}
	}			
	else if(fg_blink_mode == 3)//COMPLEX TOGGLE
	{
		if(fg_blink_is_on)
		{
			//White & Gray 표시.
			if(disp_com == 1)//GRAY
				Load_Image_FrameBuffer_2GRAY(IMG_G_COM,182,67,34,17);
			else if(disp_com == 2)//WHITE
				Load_Image_FrameBuffer_2GRAY(IMG_W_COM,182,67,34,17);					
			else//Black
				Load_Image_FrameBuffer_2GRAY(IMG_BLK,182,67,34,17); 									
		}
		else
		{
			//Black  표시.				
			Load_Image_FrameBuffer_2GRAY(IMG_BLK,182,67,34,17); 														
		}
	}	
	else
		;//
	
	TFT_LCD_225Inch_SPI_TX(2);
	LCD_BL_gpio_write(1);		
	Write_REG_Index(0x29);

}

void raon_blinkdisp_clrfilter_service(void)
{
//	debugprintf("display_blink_filter_clear_mode(%d,%d).\r\n",fg_blink_mode,fg_blink_is_on);
	
	fg_blink_is_on = !fg_blink_is_on;
	if(fg_blink_mode == 1)//FREE TOGGLE
	{
		if(fg_blink_is_on)
		{
			//White & Gray 표시.
			if(disp_free == 1)//GRAY
				Load_Image_FrameBuffer_2GRAY(IMG_G_FREE,39,67,34,17);
			else if(disp_free == 2)//WHITE
				Load_Image_FrameBuffer_2GRAY(IMG_W_FREE,39,67,34,17);					
			else//Black
				Load_Image_FrameBuffer_2GRAY(IMG_BLK,39,67,34,17);										
		}
		else
		{
			//Black  표시.				
			Load_Image_FrameBuffer_2GRAY(IMG_BLK,39,67,34,17);															
		}
	}
	else if(fg_blink_mode == 2)//PET TOGGLE
	{
		if(fg_blink_is_on)
		{
			//White & Gray 표시.
			if(disp_pet == 1)//GRAY
				Load_Image_FrameBuffer_2GRAY(IMG_G_PET,111,67,34,17);
			else if(disp_pet == 2)//WHITE
				Load_Image_FrameBuffer_2GRAY(IMG_W_PET,111,67,34,17);					
			else//Black
				Load_Image_FrameBuffer_2GRAY(IMG_BLK,111,67,34,17); 									
		}
		else
		{
			//Black  표시.				
			Load_Image_FrameBuffer_2GRAY(IMG_BLK,111,67,34,17); 														
		}
	}			
	else if(fg_blink_mode == 3)//COMPLEX TOGGLE
	{
		if(fg_blink_is_on)
		{
			//White & Gray 표시.
			if(disp_com == 1)//GRAY
				Load_Image_FrameBuffer_2GRAY(IMG_G_COM,182,67,34,17);
			else if(disp_com == 2)//WHITE
				Load_Image_FrameBuffer_2GRAY(IMG_W_COM,182,67,34,17);					
			else//Black
				Load_Image_FrameBuffer_2GRAY(IMG_BLK,182,67,34,17); 									
		}
		else
		{
			//Black  표시.				
			Load_Image_FrameBuffer_2GRAY(IMG_BLK,182,67,34,17); 														
		}
	}	
	else
		;//
	
	TFT_LCD_225Inch_SPI_TX(2);
	LCD_BL_gpio_write(1);		
	Write_REG_Index(0x29);

}

void uart_rx_message(void)
{	
	unsigned char rx_data[64];
	unsigned int rx_len,i,tmp_len;
	U8 check_sum,ch;

	rx_len = uart_getdata(MAIN_CHANNEL, rx_data, 64);	

	if(rx_len != 0) 
	{
		debugprintf("1st rx_cmd_length:%d.\r\n",rx_len);	
		delayms(5);		
		tmp_len = uart_getdata(MAIN_CHANNEL, &rx_data[rx_len], 64-rx_len);
		rx_len = rx_len+tmp_len;		
		debugprintf("tatal rx_cmd_length:%d.\r\n",rx_len);	

		if(rx_data[0]==UART_CMD_START && rx_data[1]==UART_CMD_2ND)//4바이트 이상이고 START BYTE가 OK인 경우.
		{
			//01.한번에 모든데이터를 얻음.
			if(rx_data[4]+6 == rx_len)//Total Length = Data Num + (Header2, Cmd2,Length1,CheckSum1)
			{
				//02.CheckSum
DATA_OK:		check_sum=0;
				for(i=0; i<rx_len; i++)
				{
					check_sum += rx_data[i];
					//return;
				}
				if(check_sum ==0)
				{
					//01.Copy OK Data
					memcpy(uart_rx_data, rx_data,rx_len);
					
					//02.Check Prev Command
					if(memcmp(uart_rx_data,uart_rx_data_temp,rx_len))//
					{
						debugprintf("display_service..\r\n");						
						memcpy(uart_rx_data_temp, rx_data,rx_len);					
						//03.Service Display							
						raon_dispaly_service();
					}
					else
					{
						debugprintf("same_display_command..\r\n");											
					}					
					//04. Data OK Send
					uart_tx_message(0,0);//uart_putstring(1,"OK");//Data OK						
					//GRAY_TEST();
				}
				else
				{
					uart_tx_message(1,2);//err checksum data	
					return;
				}
			}
			else if(rx_data[4]+6 < rx_len)//여러개의 명령어가 동시에 들어온 경우....
			{
				rx_len = rx_data[4]+6;//1st 명령어만 체크하도록 동작.
				goto DATA_OK;			
			}
			else
			{
				ch=rx_len;//1차로 받은 데이터 저장.
				i = rx_data[4]+6 - rx_len;//남은 데이터 수 확인.
				delayms(10);
				tmp_len = uart_getdata(MAIN_CHANNEL, &rx_data[rx_len],32);
				if(i>=tmp_len)
				{
					rx_len = ch+i;//총 길이를 수정...
					goto DATA_OK;
				}
				else
				{
					uart_tx_message(1,3);//err length timeout
					return;
				}
			}
		}
		else
		{
			uart_tx_message(1,0);//err header
			return;
		}
	}
	else
	{
		if(fg_demo_mode == true && Time0_1000mS > 0 && Pre_Time0_1000mS != Time0_1000mS)
		{
			Pre_Time0_1000mS = Time0_1000mS;
			debugprintf("display_demo_mode.%d.\r\n",Time0_1000mS);	
			raon_display_demo_mode(Pre_Time0_1000mS%10);
		}

		if(fg_blink_mode != 0 && ServiceTimer500ms==TRUE)
		{
			cnt_500mS= 50;
			ServiceTimer500ms = FALSE;

			if(Curr_Scene_ID == SCN_FILTER_ALARM)
				raon_blinkdisp_setfilter_service_new();//Add 260212 //raon_blinkdisp_setfilter_service(); 
			else if(Curr_Scene_ID == SCN_FILT_POPUP)
				raon_blinkdisp_popfilter_service();				
			else if(Curr_Scene_ID == SCN_FILT_CLEAR)
				raon_blinkdisp_clrfilter_service();	
			else
				;//
		}
	}
}


