#ifdef   RAON_FUNC_GLOBALS
#define  RAON_FUNC_EXT
#else
#define  RAON_FUNC_EXT  extern
#endif

/********************************************************
*               FUNCTION DECLARATIONS
********************************************************/
RAON_FUNC_EXT void Interrupt_Timer0(void);
RAON_FUNC_EXT void Timer_Init(void);
RAON_FUNC_EXT void Variable_Init(void);
RAON_FUNC_EXT void inline spi_wait_finish_new(U8 ch);
RAON_FUNC_EXT void spi_master_xfer_new(U8 ch, U8 *wbuf, int wlength, U8 *rbuf, int rlength, int continue_xfer);
RAON_FUNC_EXT void LCD_DC_gpio_write(uint8_t value);
RAON_FUNC_EXT void LCD_RST_gpio_write(uint8_t value);
RAON_FUNC_EXT void LCD_BL_gpio_write(uint8_t value);
RAON_FUNC_EXT void Write_REG_Index(uint8_t data);
RAON_FUNC_EXT void Write_REG_Data(uint8_t data);
RAON_FUNC_EXT void TFT_LCD_225Inch_Init_frida(void);
RAON_FUNC_EXT void Clear_Frame_Buffer(void);
RAON_FUNC_EXT void GRAY_TEST(void);
RAON_FUNC_EXT void TFT_LCD_225Inch_SPI_TX(unsigned char gray_scale);
RAON_FUNC_EXT void TFT_LCD_225Inch_all_black_fill(void);
RAON_FUNC_EXT void Load_Image_FrameBuffer_2GRAY(const U8 *db_buf, U16 start_x,U8 start_y,U16 size_x, U8 size_y);
RAON_FUNC_EXT void raon_display_demo_mode(U8 scene_idx);
RAON_FUNC_EXT void raon_dispaly_service(void);
RAON_FUNC_EXT void raon_portinit(void);
RAON_FUNC_EXT void raon_systeminit(void);
RAON_FUNC_EXT void uart_tx_message(unsigned char mode, unsigned char err_num);
RAON_FUNC_EXT void uart_rx_message(void);

