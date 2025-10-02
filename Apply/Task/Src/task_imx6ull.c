#include "task_imx6ull.h"

static uint8_t IMX6ULL_ReceBuf[100];
static uint8_t IMX6ULL_ReceNum = 0;

static char LongitudeStr[11] = {0};  //经度字符串
static char LatitudeStr[10] = {0};   //纬度字符串

static uint8_t StartClpt[] = "StartClpt";     //i.mx6ull板启动完成提示

tagGPSinfo_T GPS;

/**
 * @brief IMX6ULL处理函数
 * @param Null
 */
void Task_IMX6ULL_Handle(void)
{
    IMX6ULL_ReceNum = Drv_Uart_Receive_DMA(&Uart4,IMX6ULL_ReceBuf);
    if(IMX6ULL_ReceNum != 0)
    {
        //Drv_Uart_Transmit(&Uart1,IMX6ULL_ReceBuf,IMX6ULL_ReceNum);

        if(!strcmp((char *)IMX6ULL_ReceBuf,(char *)StartClpt))      //I.MX6ull启动后会发送StartClpt表示自己启动完成
            printf("I.MX6ull Start\r\n");

        uint8_t ret = 0;
        //字符串解析
        ret = sscanf((char *)IMX6ULL_ReceBuf,"$GNRMC,%*10[^,],%c,%10s,%c,%11s,%c,%*.1f,%*.1f,%*6d,,,%*4s",
                    &GPS.Status,
                    LatitudeStr,
                    &GPS.NS,  
                    LongitudeStr,
                    &GPS.WE  
        );

        //字符串转化为float类型
        GPS.Latitude = strtof(LatitudeStr,NULL);
        GPS.Longitude = strtof(LongitudeStr,NULL);

        UNUSED(ret);           
#ifdef DEBUG_PRINTF    
        printf("%d %c %4.5f %c %5.5f %c\n",ret,GPS.Status,GPS.Latitude,GPS.NS,GPS.Longitude,GPS.WE);
#endif
        //将GPS信息放入报告缓存区内
        memcpy(&ReportDataBuffer[GPS_BASE                                    ],&GPS.WE,UINT8_T_SIZE);
        memcpy(&ReportDataBuffer[GPS_BASE +     UINT8_T_SIZE                 ],&GPS.Longitude,FLOAT_SIZE);
        memcpy(&ReportDataBuffer[GPS_BASE +     UINT8_T_SIZE +     FLOAT_SIZE],&GPS.NS,UINT8_T_SIZE);
        memcpy(&ReportDataBuffer[GPS_BASE + 2 * UINT8_T_SIZE +     FLOAT_SIZE],&GPS.Latitude,FLOAT_SIZE);
        memcpy(&ReportDataBuffer[GPS_BASE + 2 * UINT8_T_SIZE + 2 * FLOAT_SIZE],&GPS.Status,UINT8_T_SIZE);

        IMX6ULL_ReceNum = 0;
    }
}
