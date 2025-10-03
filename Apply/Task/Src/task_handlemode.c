#include "task_handlemode.h"

/**
 * @brief 手动模式处理函数
 * @param HMInfo 手动模式信息结构体指针
 */
void Task_HandleMode_Process(HandleModeInfo *HMInfo)
{
	MotorSysInfo MSInfo;
    //非0数据显示
    if(HMInfo->JoystickInfo[0] != 0.0f && HMInfo->JoystickInfo[1] != 0.0f)
        printf("%f %f\r\n",HMInfo->JoystickInfo[0],HMInfo->JoystickInfo[1]);
    printf("%d\r\n",(*HMInfo).key);
	//手柄数据处理
	switch((*HMInfo).key)
	{
		case 0:
			if(HMInfo->keyPressed)
			{
				MSInfo.StcDirect.Direct_A = -200;
				MSInfo.StcDirect.Direct_B = -200;
				MSInfo.StcDirect.Direct_C = -200;
				MSInfo.StcDirect.Direct_D = -200;
			}
			else
			{
				MSInfo.StcDirect.Direct_A = 0;
				MSInfo.StcDirect.Direct_B = 0;
				MSInfo.StcDirect.Direct_C = 0;
				MSInfo.StcDirect.Direct_D = 0;
			}
			break;
		case 1:
			if(HMInfo->keyPressed)
			{
				MSInfo.StcDirect.Direct_A = -200;
				MSInfo.StcDirect.Direct_B = 200;
				MSInfo.StcDirect.Direct_C = -200;
				MSInfo.StcDirect.Direct_D = 200;
			}
			else
			{
				MSInfo.StcDirect.Direct_A = 0;
				MSInfo.StcDirect.Direct_B = 0;
				MSInfo.StcDirect.Direct_C = 0;
				MSInfo.StcDirect.Direct_D = 0;
			}
			break;
		case 2:
			if(HMInfo->keyPressed)
			{
				MSInfo.StcDirect.Direct_A = 200;
				MSInfo.StcDirect.Direct_B = -200;
				MSInfo.StcDirect.Direct_C = 200;
				MSInfo.StcDirect.Direct_D = -200;
			}
			else
			{
				MSInfo.StcDirect.Direct_A = 0;
				MSInfo.StcDirect.Direct_B = 0;
				MSInfo.StcDirect.Direct_C = 0;
				MSInfo.StcDirect.Direct_D = 0;
			}
			break;
		case 3:
			if(HMInfo->keyPressed)
			{
				MSInfo.StcDirect.Direct_A = 200;
				MSInfo.StcDirect.Direct_B = 200;
				MSInfo.StcDirect.Direct_C = 200;
				MSInfo.StcDirect.Direct_D = 200;
			}
			else
			{
				MSInfo.StcDirect.Direct_A = 0;
				MSInfo.StcDirect.Direct_B = 0;
				MSInfo.StcDirect.Direct_C = 0;
				MSInfo.StcDirect.Direct_D = 0;
			}
			break;
		case 6:
			if(HMInfo->keyPressed)
			{
				Task_MotorSys_Steer_Angle_Set(A_2,0);
				Drv_Delay_Ms(100);
				Task_MotorSys_Steer_Angle_Set(B_2,0);
				Drv_Delay_Ms(100);
				Task_MotorSys_Steer_Angle_Set(C_2,0);
				Drv_Delay_Ms(100);
				Task_MotorSys_Steer_Angle_Set(D_2,0);
				Drv_Delay_Ms(100);
			}
			break;
		case 7:
			if(HMInfo->keyPressed)
			{
				Task_MotorSys_Steer_Angle_Set(A_2,90);
				Drv_Delay_Ms(100);
				Task_MotorSys_Steer_Angle_Set(B_2,90);
				Drv_Delay_Ms(100);
				Task_MotorSys_Steer_Angle_Set(C_2,90);
				Drv_Delay_Ms(100);
				Task_MotorSys_Steer_Angle_Set(D_2,90);
				Drv_Delay_Ms(100);
			}
			break;
	}

	//限幅
//	if(Position_AC >= 180)	Position_AC = 180;
//	if(Position_AC <= 0)	Position_AC = 0;
//	if(Position_BD >= 180)	Position_BD = 180;
//	if(Position_BD <= 0)	Position_BD = 0;

//	if(HMInfo->keyPressed)
//	{
//		printf("%d %d\r\n",Position_AC,Position_BD);
//		Task_MotorSys_Steer_Angle_Set(A_2,Position_AC);
//        Drv_Delay_Ms(100);
//        Task_MotorSys_Steer_Angle_Set(B_2,Position_BD);
//        Drv_Delay_Ms(100);
//        Task_MotorSys_Steer_Angle_Set(C_2,Position_BD);
//        Drv_Delay_Ms(100);
//        Task_MotorSys_Steer_Angle_Set(D_2,Position_AC);
//        Drv_Delay_Ms(100);
//	}

    //手柄数据清零，防止重复使用
    HMInfo->JoystickInfo[0] = 0.0f;
    HMInfo->JoystickInfo[1] = 0.0f;
}
