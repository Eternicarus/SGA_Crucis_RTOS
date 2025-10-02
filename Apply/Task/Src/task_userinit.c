#include "task_conf.h"
#include "ocd_conf.h"
#include "config.h"

/* 外设初始化函数 */
void Task_UserInit(void)
{
    uint8_t ret = 0;

	Drv_GPIO_Init(LED, 3);

	Drv_GPIO_Init(&SYNC,1);			/* 初始化AD4111的SYNC引脚 */
    
    Drv_Uart_DMAInit(&Uart1);       /* 初始化串口1 DAP接口 有线RS232接口 */
    OCD_JY901_DMAInit(&JY901S);     /* 初始化JY901S 使用串口2 */
    Drv_Uart_DMAInit(&Uart3);       /* 初始化串口3 无线电台 */
	Drv_Uart_DMAInit(&Uart4);       /* 初始化串口4 I.MX6ull */

	OCD_DS3231_Init(&DS1337);		/* 初始化片外RTC */
    
    ret = OCD_AD24BIT_Init(&AD4111_1);  /* 24位AD初始化 */
	if (ret != 0)
	{
		printf("##AD init fail, error code:%d!!!\r\n",ret);
		while(1);  //程序报错stop	
	}
    ret = OCD_AD24BIT_Init(&AD4111_2);  /* 24位AD初始化 */
	if (ret != 0)
	{
		printf("##AD init fail, error code:%d!!!\r\n",ret);
		while(1);  //程序报错stop	
	}
    
    Task_MotorSys_Init();       /* 初始化电机系统 */
    
    if(OCD_MS5837_Init(&MS5837) == 0)	/* 初始化MS5837 */
        printf("MS5837 error\r\n");
}
