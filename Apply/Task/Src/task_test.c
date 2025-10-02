#include "task_test.h"

static uint8_t Uart3_ReceiveBuffer[100] = {0};        //用于测试串口3
static uint8_t Uart3_ReceiveNum = 0;

/**
 * @brief 专用于测试串口3无线电台的函数
 * @param Null
 */
static void S_Test_Uart3_Function(void)
{
    Uart3_ReceiveNum = Drv_Uart_Receive_DMA(&Uart3,Uart3_ReceiveBuffer);
    if(Uart3_ReceiveNum != 0)
    {
        Drv_Uart_Transmit(&Uart3,Uart3_ReceiveBuffer,Uart3_ReceiveNum);
        Uart3_ReceiveNum = 0;
    }
}

/**
 * @brief AD4111数据采集函数
 * @param Null
 */
static void S_AD_Acquisition(tagAD24BIT_T* device)
{
    uint8_t ret;
    double V0,V1,V2,V3,V4,V5,V6,V7;

	ret = OCD_AD24bit_GetResult(device, 200);
	if(ret != 0)
	{
	    DBG_ERROR("OCD_AD24bit_GetResult error:%d\r\n",ret);
	}
    
	V0 = device->port[0].result;
	V1 = device->port[1].result;
	V2 = device->port[2].result;
	V3 = device->port[3].result;
	V4 = device->port[4].result;
	V5 = device->port[5].result;
    V6 = device->port[6].result;
    V7 = device->port[7].result;
    
    printf("V0 %f V1 %f V2 %f\r\n",V0,V1,V2);
    printf("V3 %f V4 %f V5 %f\r\n",V3,V4,V5);
    printf("V6 %f V7 %f\r\n\r\n",V6,V7); 
}

/**
 * @brief 专用于测试AD4111的函数
 * @param Null
 */
static void S_Test_AD4111_Function(void)
{
    printf("AD4111_1\r\n");
    S_AD_Acquisition(&AD4111_1);
    printf("AD4111_2\r\n");
    S_AD_Acquisition(&AD4111_2);
	Drv_Delay_Ms(1000);
}

/**
 * @brief 专用于测试MS5837的函数
 * @param Null
 */
static void S_Test_MS5837_Function(void)
{
    //获取MS5837温度和压力数据
	OCD_MS5837_GetData(&MS5837);

	//打印相关数据
	printf("Temp1:%.2fC Press1:%.2fmBar\r\n",MS5837.fTemp1,MS5837.fPress1);
	printf("Temp:%.2fC Press:%.2fmBar\r\n",MS5837.fTemp2,MS5837.fPress2);
	printf("%.2fcm\r\n\r\n",MS5837.fDepth);
}

/**
 * @brief 专用于测试JY901S的函数
 * @param Null
 */
static void S_Test_JY901S_Function(void)
{
    //如果成功处理完成数据
	if(OCD_JY901_DataProcess(&JY901S))
    {
        //数据转换
        OCD_JY901_DataConversion(&JY901S);
        //打印欧拉角
        if(JY901S.tConfig.usType & JY901_OUTPUT_ANGLE)	    
            printf("J Angle %.3f %.3f %.3f\r\n\r\n",
                    JY901S.stcAngle.ConRoll,
                    JY901S.stcAngle.ConPitch,
                    JY901S.stcAngle.ConYaw);
        if(JY901S.tConfig.usType & JY901_OUTPUT_MAG)	    
            printf("J Mag %.3f %.3f %.3f\r\n\r\n",
                    JY901S.stcMag.ConMagX,
                    JY901S.stcMag.ConMagY,
                    JY901S.stcMag.ConMagZ);
        if(JY901S.tConfig.usType & JY901_OUTPUT_ACCEL)	    
            printf("J Accel %.3f %.3f %.3f\r\n\r\n",
                    JY901S.stcAcc.ConAccX,
                    JY901S.stcAcc.ConAccY,
                    JY901S.stcAcc.ConAccZ);
        if(JY901S.tConfig.usType & JY901_OUTPUT_GYRO)	    
            printf("J Gyro %.3f %.3f %.3f\r\n\r\n",
                    JY901S.stcGyro.ConGyroX,
                    JY901S.stcGyro.ConGyroY,
                    JY901S.stcGyro.ConGyroZ);
    }
}

/**
 * @brief 专用于测试DS1337的函数
 * @param Null
 */
static void S_Test_DS1337_Function(void)
{
    tagDS3231Time_T CurrSysTime = {0};

    /* 获取当前时间 */
    if(OCD_DS3231_TimeGetHex(&DS1337,&CurrSysTime))
    {
        printf("Read Time:");
        printf("20%02x/%02x/%02x %02x:%02x:%02x 周%x\r\n",
                CurrSysTime.ucYear,CurrSysTime.ucMonth,CurrSysTime.ucDate,
                CurrSysTime.ucHour,CurrSysTime.ucMinute,CurrSysTime.ucSecond,
                CurrSysTime.ucWeek);
    }
    Drv_Delay_Ms(1000);    
}

/**
 * @brief 专用于测试电机系统的函数
 * @param Null
 */
static void S_Test_Motorsys_Function(void)
{
    //测试推进器转动
//    Task_MotorSys_Thruster_SpeedSet(A_1,1550);
//    Drv_Delay_Ms(2000);
//    Task_MotorSys_Thruster_SpeedSet(A_1,1500);
//    Drv_Delay_Ms(2000);
//    Task_MotorSys_Thruster_SpeedSet(B_1,1550);
//    Drv_Delay_Ms(2000);
//    Task_MotorSys_Thruster_SpeedSet(B_1,1500);
//    Drv_Delay_Ms(2000);
//    Task_MotorSys_Thruster_SpeedSet(C_1,1550);
//    Drv_Delay_Ms(2000);
//    Task_MotorSys_Thruster_SpeedSet(C_1,1500);
//    Drv_Delay_Ms(2000);
//    Task_MotorSys_Thruster_SpeedSet(D_1,1550);
//    Drv_Delay_Ms(2000);
//    Task_MotorSys_Thruster_SpeedSet(D_1,1500);
//    Drv_Delay_Ms(2000);

    Task_MotorSys_Steer_Angle_Set(A_2,0);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(A_2,90);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(A_2,180);
    Drv_Delay_Ms(2000);

    Task_MotorSys_Steer_Angle_Set(B_2,0);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(B_2,90);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(B_2,180);
    Drv_Delay_Ms(2000);

    Task_MotorSys_Steer_Angle_Set(C_2,0);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(C_2,90);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(C_2,180);
    Drv_Delay_Ms(2000);

    Task_MotorSys_Steer_Angle_Set(D_2,0);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(D_2,90);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(D_2,180);
    Drv_Delay_Ms(2000);
    
//                Task_MotorSys_Steer_Angle_Set(A_2,90);
//                Drv_Delay_Ms(1000);
//                Task_MotorSys_Steer_Angle_Set(B_2,90);
//                Drv_Delay_Ms(1000);
//                Task_MotorSys_Steer_Angle_Set(C_2,90);
//                Drv_Delay_Ms(1000);
//                Task_MotorSys_Steer_Angle_Set(D_2,90);
//                Drv_Delay_Ms(1000);
//                Task_MotorSys_Thruster_SpeedSet(A_1,1520);
//                Task_MotorSys_Thruster_SpeedSet(B_1,1520);
//                Task_MotorSys_Thruster_SpeedSet(C_1,1520);
//                Task_MotorSys_Thruster_SpeedSet(D_1,1520);
//                Drv_Delay_Ms(2000);
//                Task_MotorSys_Thruster_SpeedSet(A_1,1500);
//                Task_MotorSys_Thruster_SpeedSet(B_1,1500);
//                Task_MotorSys_Thruster_SpeedSet(C_1,1500);
//                Task_MotorSys_Thruster_SpeedSet(D_1,1500);

//    Task_MotorSys_AllThruster_SpeedSet(1514);
//    Drv_Delay_Ms(2000);
//    Task_MotorSys_AllThruster_SpeedSet(1500);
}

/**
 * @brief 专用于测试的函数
 * @param Null
 */
void Task_Test_Handle(void)
{
    // S_Test_Uart3_Function();

    // S_Test_AD4111_Function();

    // S_Test_MS5837_Function();

    // S_Test_JY901S_Function();

    // S_Test_DS1337_Function();

    S_Test_Motorsys_Function();
	printf("run\r\n");
}

