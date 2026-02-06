#include "sdk.h"
#include "raon_func.h"

extern U8 Time0_10mS;
extern U16 cnt_10mS;
extern U16 cnt_500mS;
extern U16 Time0_500mS;
extern U16 Time0_1000mS;
extern bool ServiceTimer500ms;
int main()
{
	raon_portinit();
	raon_systeminit();
	
	uart_tx_message(0,0);

	while(1)
	{
		if(Time0_10mS)
		{
			Time0_10mS = 0;
			cnt_10mS++;
			
			if(cnt_500mS)
				cnt_500mS--;			

			if(cnt_500mS == 0)
			{
				ServiceTimer500ms=TRUE;
			}
			if(cnt_10mS > 300)//3초에 한번으로 테스트....
			{
				cnt_10mS=0;
				Time0_1000mS++;
				//debugprintf("Timer 1sec set.%d\r\n",Time0_1000mS);
			}
		}
		uart_rx_message();		
	}
    return 0;
}
