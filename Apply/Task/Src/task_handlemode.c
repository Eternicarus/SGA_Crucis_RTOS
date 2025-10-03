#include "task_handlemode.h"

/**
 * @brief �ֶ�ģʽ������
 * @param HMInfo �ֶ�ģʽ��Ϣ�ṹ��ָ��
 */
void Task_HandleMode_Process(HandleModeInfo *HMInfo)
{
	MotorSysInfo MSInfo;
    //��0������ʾ
    if(HMInfo->JoystickInfo[0] != 0.0f && HMInfo->JoystickInfo[1] != 0.0f)
        printf("%f %f\r\n",HMInfo->JoystickInfo[0],HMInfo->JoystickInfo[1]);
    printf("%d\r\n",(*HMInfo).key);
	//�ֱ����ݴ���
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

	//�޷�
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

    //�ֱ��������㣬��ֹ�ظ�ʹ��
    HMInfo->JoystickInfo[0] = 0.0f;
    HMInfo->JoystickInfo[1] = 0.0f;
}
