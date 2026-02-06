/******************************************************************************
 Copyright (C) 2013      Seminix(http://www.seminix.com)
 Author : Software Team.
******************************************************************************/
#if 1
#define UART_CMD_START	0x52//'R'aon
#define UART_CMD_2ND	0x41//r'A'on

U8 FW_Version[2]={
	0x00,
	0x00
};
#define SPI_MAX_WFIFO_new 8
#define SPI_CH 1
#define PWM_CH 1

enum //UART DATA_IDX
{
 	CMD_START_IDX,//0
	CMD_2ND_IDX,
	CMD_SCNID_MSB_IDX,
	CMD_SCNID_LSB_IDX,
	CMD_LENGTH_IDX,
	CMD_SUB1_IDX,
	CMD_SUB2_IDX,
	CMD_SUB3_IDX,
	CMD_SUB4_IDX,	
	CMD_SUB5_IDX,
	CMD_SUB6_IDX,
	CMD_SUB7_IDX,
	CMD_SUB8_IDX,	
	CMD_SUB9_IDX,
	CMD_SUB10_IDX,	
	CMD_SUB11_IDX,	
	CMD_SUB12_IDX,		
};

enum //SCENE_IDX
{
 	SCN_INTRO = 0x0000,//0
	SCN_HOME,// = 0x0001, //홈화면
	SCN_MODE,// = 0x0002,//운전모드 모화면
	SCN_SET_OFFTIME=0x0100,//OFF RSV	
	SCN_ILLUM_MODE,//조명모드.
	SCN_ILLUM_STEP,//0x0102,	//조도STEP
	SCN_BRIGHT,// 0x0103, //밝기STEP
	SCN_SOUND_MODE,//0x0104,	//소리모드.
	SCN_SOUND_STEP,// 0x0105,//소리조절. 
	SCN_FILTER_STEP,//0x0106 //먼지센서 감도.
	SCN_FILTER_ALARM,//0x0107	//필터교체 알림.
	SCN_FILT_POPUP = 0x0200,//필터알람팝업
	SCN_NORM_POPUP = 0x0201,//일반 팝업.
	SCN_FILT_CLEAR = 0x0202,//필터초기화	
	SCN_ERR_POPUP = 0x0203,//에러팝업.
	SCN_DEMO = 0xFF00,//데모모드.
	SCN_TEST,//검정화면
	SCN_LCD_EN, 
	SCN_BKCTRL_BK,
	SCN_TMODE_VER = 0xFF10,	//VERSION
	SCN_TMODE_RPM,//RPM
	SCN_TMODE_SNR,//SENSOR
	SCN_TMODE_FILT,//FILTER	
	SCN_TMODE_LED,//FILTER		
};

U16 spi_buf_len;

U8 spi_buf[256]={
};

U8 dbg_Timer_2S,dbg_flag;

U8 Time0_10mS;
U16 cnt_10mS;
U16 cnt_500mS;
U16 Time0_500mS;
U16 Time0_1000mS;
U16 Pre_Time0_1000mS;
bool ServiceTimer500ms;

U8 uart_rx_data[64],uart_rx_data_temp[64],uart_rx_pt ;
U8 grayscale_mode; 
U8 fg_demo_mode;

U16 prev_pol_val;
U8 prev_pol_stat;
U8 prev_mode;
U8 prev_lock;
U8 prev_filter;
U8 prev_timer;
U8 prev_pol_step;

U16 Prev_Scene_ID;
U16 Curr_Scene_ID;
U16 Curr_PWM_Dudy;
U8 fg_blink_mode;
U8 fg_blink_is_on;

U8 disp_free;
U8 disp_pet;
U8 disp_com;

#else
//#define	FIRM_VERSION	"17/07/24"
#define FIRM_YEAR 17
#define FIRM_MON 9
#define FIRM_DAY 25

//#define LCD_TYPE 480
//#define DISP_NANDVERSION

//#define LCD_BACK_CONT_PWM
#define PWM_10KHZ 160
//#define COM_UART_CH 1

#define UART_CMD_START	0x53//'S'K
#define UART_CMD_ENDT	0x4D//'M'AGIC

//#define UART_DATA_START_IDX	0
//#define UART_DATA_LENGTH_IDX 1
//#define UART_DATA_CUR_HR_IDX	2
//#define UART_DATA_CUR_MIN_IDX	3
#define UART_DATA_DOOR_SND_IDX	4
#define UART_DATA_WIFI_IDX	5
#define UART_DATA_POPUP_IDX	6
#define UART_DATA_DEPTH_IDX	7
#define UART_DATA_MAIN_MENU_IDX	8

#define HOME_BTN 0	//단축번호.
#define HOME_DISP 1	//요리
#define ADD_FUNC 2	//부가기능
#define SYSTEM_SET 3	//설정.
#define RANGE_SET 4	//레인지
#define FAVOR_DISP 5	//즐겨찾기 
#define MY_COOK_DISP 6	//나만의 요리

#define COOK_ING 10
#define POPUP_DISP 11
#define ERR_DISP 15
#define HELP_DISP 16
#define CHECK_DISP 17
#define TEST_DISP	18
#define LOGO_DISP 20
#define LCD_OFF 21

#define MANAGER_MODE 30
#define LINETEST_MODE 31

#define OK_UART_DATA		0
#define ERR_UART_DATA		1

#define MENU_IDX_OVEN_BASE	1
#define MENU_IDX_GRILL_BASE	51
#define MENU_IDX_STEAM_BASE	69
#define MENU_IDX_FRY_BASE	97
#define MENU_IDX_RANGE_BASE	112
#define MENU_IDX_DRY_BASE	118
#define MENU_IDX_FER_BASE	124

#define main_menu_x	0
#define main_menu_y	0

#define range_min_10x	231
#define range_min_10y	65 
#define range_min_1x	(range_min_10x+32)		
#define range_min_1y	65
#define range_sec_10x	309	
#define range_sec_10y	65
#define range_sec_1x	(range_sec_10x+32)
#define range_sec_1y	65

#define cooking_digit_44x 176
#define cooking_digit_44y 82
#define cooking_digit_44y_1line 114


#define cooking_digit_34x	(cooking_digit_44x+24)
#define cooking_digit_34y	cooking_digit_44y

#define cooking_digit_dotx	(cooking_digit_44x+24+24)
#define cooking_digit_doty	cooking_digit_44y

#define cooking_digit_24x	(cooking_digit_44x+24+24+17)
#define cooking_digit_24y	cooking_digit_44y

#define cooking_digit_14x	(cooking_digit_44x+24+24+17+24)
#define cooking_digit_14y	cooking_digit_44y

#define cooking_digit4_minsecx	294
#define cooking_digit4_minsecy	101
#define cooking_digit4_minsecy_1line	133


#define cooking_digit_22x	214
#define cooking_digit_22y	82

#define cooking_digit_12x	(cooking_digit_22x+24)
#define cooking_digit_12y	cooking_digit_22y

#define cooking_digit2_minsecx	268
#define cooking_digit2_minsecy	101

#define cooking_temp_base_x	196
#define cooking_temp_base_y	150

#define cooking_temp_2base_x	214
#define cooking_temp_2base_y	150

#define cooking_range_heat_2base_x	214
#define cooking_range_heat_2base_y	114
#define cooking_range_heat_2base_sec_x	268
#define cooking_range_heat_2base_sec_y	133

#define cooking_2line_menu_name_x 165//164
#define cooking_2line_menu_name_y 80

#define cooking_2line_status_name_x 190
#define cooking_2line_status_name_y 152

#define cooking_1line_status_name_x 190
#define cooking_1line_status_name_y 119

#define check_line_y_offset 50
#define check_1line_y	30
#define check_2line_y	(check_1line_y+check_line_y_offset)
#define check_3line_y	(check_2line_y+check_line_y_offset)
#define check_4line_y	(check_3line_y+check_line_y_offset)
#define check_5line_y   (check_4line_y+check_line_y_offset)


//총 32바이트로 제한 (START(1)+LEN(1)+DATA(28)+END(1)+CHECKSUM(1))
enum //DATA_IDX
{
	SYS_CUR_HR_IDX=0,
	SYS_CUR_MIN_IDX,
	SYS_DOOR_VOICE_IDX,
	SYS_WIFI,
	SYS_POPUP_IDX,
	CMD_DEPTH_IDX,//5
	CMD_MAIN_MENU_IDX,
	CMD_SUB1_IDX,
	CMD_SUB2_IDX,
	CMD_SUB3_IDX,
	CMD_SUB4_IDX,//10
	CMD_SUB5_IDX,
	CMD_SUB6_IDX,
	CMD_SUB7_IDX,
	CMD_SUB8_IDX,
	CMD_SUB9_IDX,//15
	CMD_SUB10_IDX,
	CMD_SUB11_IDX,
	CMD_SUB12_IDX,
	CMD_SUB13_IDX,
	CMD_SUB14_IDX,//20
	CMD_SUB15_IDX,
	CMD_SUB16_IDX,
	CMD_SUB17_IDX,
	CMD_SUB18_IDX,
	CMD_SUB19_IDX,//25
	CMD_SUB20_IDX,
	CMD_SUB21_IDX,//27	
};

enum //UART_ERR_IDX
{
	ERR_START_CMD=0,
	ERR_START_BIT,
	ERR_LENGTH_TIMEOUT,
	ERR_CHECKSUM,
	ERR_DATA_LENGTH,
};

enum //LANG_IDX
{
	LANG_KOR=0,
	LANG_ENG,
	LANG_CHN,
};

enum //COLOR_IDX
{
	COLOR_GRAY=0,
	COLOR_RED,
	COLOR_BLACK,
};

U16 firm_ver_main[8][2]={
	{112,116},//year digit4
	{112+26,116},//year digit3
	{112+26+26,116},//year digit 2
	{112+26+26+26,116},//year digit 1
	{240,116},//mon digit 2
	{240+26,116},//mon digit 1
	{306,116},//day digit 2
	{306+26,116},//day digit 1	
};

U16 firm_ver_main_2line[8][2]={
	{164,90},//year digit4
	{164+22,90},//year digit3
	{164+22+22,90},//year digit 2
	{164+22+22+22,90},//year digit 1
	{164+22+22+22+22+16,90},//mon digit 2
	{164+22+22+22+22+16+22,90},//mon digit 1
	{164+22+22+22+22+16+22+22+16,90},//day digit 2
	{164+22+22+22+22+16+22+22+16+22,90},//day digit 1	
};

U16 firm_ver_lcd_2line[8][2]={
	{164,146},//year digit4
	{164+22,146},//year digit3
	{164+22+22,146},//year digit 2
	{164+22+22+22,146},//year digit 1
	{164+22+22+22+22+16,146},//mon digit 2
	{164+22+22+22+22+16+22,146},//mon digit 1
	{164+22+22+22+22+16+22+22+16,146},//day digit 2
	{164+22+22+22+22+16+22+22+16+22,146},//day digit 1	
};


U16 voice_offset_idx[16][2]={
	{0,0},//DUMMY
	{11,106},
	{11,157},
	{11,208},
	{103,106},
	{103,157},
	{103,208},
	{195,106},
	{195,157},
	{195,208},
	{286,106},
	{286,157},
	{286,208},
	{378,106},
	{378,157},
	{378,208},
};




int home_time_xy_table[6][2]={
	{404,3},//AM,PM
	{432,3},//HOUR 10
	{432+9,3},//HOUR 1
	{452+2,3},//MIN 10
	{452+2+9,3},//MIN 1
	{452,3},//Colon	
};

int set_time_xy_table[7][2]={
	{87,99},//AM,PM
	{168,104},//HOUR 10
	{200,104},//HOUR 1
	{165,168},//시 BAR
	{300,104},//MIN 10
	{332,104},//MIN 1
	{298,168},//분 BAR
};


int cooking_cur_step_xy_table[36][2]={
	{0,0},//0 DUMMY
	{124+92,20+10},
	{124+76,20+14},
	{124+60,20+22},
	{124+46,20+32},
	{124+32,20+45},//5
	{124+22,20+60},
	{124+15,20+75},
	{124+11,20+90},
	{124+9,20+108},
	{124+11,20+126},//10
	{124+15,20+143},
	{124+22,20+159},
	{124+32,20+172},
	{124+45,20+184},
	{124+60,20+193},//15
	{124+74,20+201},
	{124+91,20+206},
	{124+109,20+206},
	{124+125,20+206},
	{124+142,20+201},//20
	{124+158,20+193},
	{124+172,20+184},
	{124+184,20+172},
	{124+194,20+159},
	{124+201,20+143},//25
	{124+205,20+126},
	{124+207,20+108},
	{124+205,20+90},
	{124+201,20+75},
	{124+194,20+60},//30
	{124+184,20+45},
	{124+172,20+32},
	{124+158,20+22},
	{124+142,20+14},
	{124+126,20+10},//35
};


int cooking_cur_100step_xy_table[100][2]={
	{124+116,20+10},
	{124+109,20+10},
	{124+102,20+10},
	{124+96,20+11},
	{124+90,20+12},//5
	{124+83,20+14},
	{124+77,20+16},
	{124+71,20+19},
	{124+65,20+22},
	{124+59,20+25},//10
	{124+54,20+28},
	{124+48,20+32},
	{124+43,20+36},
	{124+39,20+41},
	{124+34,20+46},//15
	{124+30,20+51},
	{124+26,20+57},
	{124+23,20+62},
	{124+20,20+68},
	{124+17,20+74},//20
	{124+15,20+80},
	{124+13,20+86},
	{124+12,20+93},
	{124+11,20+99},
	{124+10,20+106},//25
	{124+10,20+113},
	{124+10,20+119},
	{124+10,20+125},
	{124+11,20+130},
	{124+12,20+136},//30
	{124+14,20+142},
	{124+16,20+148},
	{124+19,20+153},
	{124+22,20+159},
	{124+25,20+164},//35
	{124+28,20+169},
	{124+32,20+173},
	{124+36,20+178},
	{124+41,20+182},
	{124+46,20+186},//40
	{124+51,20+190},
	{124+57,20+194},
	{124+62,20+197},
	{124+68,20+200},
	{124+74,20+202},//45
	{124+80,20+204},
	{124+86,20+206},
	{124+93,20+208},
	{124+99,20+209},
	{124+106,20+209},//50
	{124+113,20+209},
	{124+119,20+209},
	{124+125,20+209},
	{124+130,20+208},
	{124+136,20+207},//55
	{124+142,20+205},
	{124+148,20+203},
	{124+153,20+201},
	{124+158,20+198},
	{124+164,20+195},//60
	{124+169,20+192},
	{124+173,20+188},
	{124+178,20+184},
	{124+182,20+180},
	{124+186,20+176},//65
	{124+190,20+171},
	{124+193,20+166},
	{124+197,20+161},
	{124+200,20+156},
	{124+202,20+150},//70
	{124+204,20+145},
	{124+206,20+139},
	{124+207,20+133},
	{124+209,20+127},
	{124+209,20+122},//75
	{124+209,20+116},
	{124+209,20+109},
	{124+209,20+102},
	{124+208,20+96},
	{124+207,20+89},//80
	{124+205,20+83},
	{124+203,20+77},
	{124+201,20+71},
	{124+198,20+65},
	{124+195,20+59},//85
	{124+192,20+54},
	{124+188,20+48},
	{124+184,20+43},
	{124+180,20+39},
	{124+176,20+34},//90
	{124+171,20+30},
	{124+166,20+26},
	{124+161,20+23},
	{124+156,20+20},
	{124+150,20+17},//95
	{124+145,20+15},
	{124+139,20+13},
	{124+133,20+12},
	{124+127,20+10},
	{124+121,20+10},//100		
};


typedef struct _tagUartCmd
{
	U8 data[32];
}RX_COMMAND;

typedef struct _getUartCommand
{
	U8 cmd_total_length;
	U8 cmd_data_length;	
	U8 cmd_data_buf[30];
	U8 cmd_data_buf1[32];
}info_UartCommand;

typedef struct _moving_scent
{
	U16 start_scene_num;
	U16 end_scene_num;	
	U16 scene_total_num;	
}info_Cur_Moving_Scene;

//U16	dimming_table[8]={7,10,50,90,130,140,150,159};
U16	dimming_table[6]={0,10,50,90,130,159};

U16 timer_tick=0;
U8	fg_toggle_on=0;
U8	fg_time_tick=0;
U8  fg_white_time_color=0;
U8	prev_dimm_idx=0;
U8  fg_stat_bar_disp;

U8	fg_lcd_on;

U16	cnt_uart_error;
U16	cnt_uart_error1;
U16	cnt_uart_error2;
U16	cnt_uart_error3;
U16	cnt_uart_error4;

U16	fg_uart_err_time;
U16	cnt_uart_err_time_check;

U8	display_on;
U16	g_cur_frame_idx;
U16	g_frame_cnt;

static RX_COMMAND uart_cmd;
static info_UartCommand CUR_UART_CMD;
static info_UartCommand PRE_UART_CMD;
unsigned char enable_moving_scene;
unsigned char fg_pre_moving_scene;//이전명령어가 동영상이였음을 나타내는 변수이며,반드시 동영상시작전에 CLR해야함.

info_Cur_Moving_Scene CUR_MOVING_SCENE;
SURFACE* frame;
SURFACE* frame2;
EGL_FONT* font;
EGL_FONT* w_font;


static unsigned char current_frame;


U8 spi_rdata[512];

U16 write_idx;
U16 read_idx;
U16 cmd_buf_idx;
U8 spi_cmd_data[32];
U8 spi_rsp_data[32];

U8 spi_cmd_status;
U16 cmd_buf_idx;
U16 rsp_buf_idx;
U16 rsp_buf_size;
U16 rsp_buf_idx;
#endif

