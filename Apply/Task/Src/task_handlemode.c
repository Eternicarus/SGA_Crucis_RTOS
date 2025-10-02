#include "task_handlemode.h"

/**
 * @brief �ֶ�ģʽ������
 * @param HMInfo �ֶ�ģʽ��Ϣ�ṹ��ָ��
 */
void Task_HandleMode_Process(HandleModeInfo *HMInfo)
{
	static uint8_t Position_AC = 90;               //���AC����Ƕ�λ��
	static uint8_t Position_BD = 90;               //���BD����Ƕ�λ��
	static uint16_t Speed_AC = 1500;                  //���AC�ƽ����ٶ�
	static uint16_t Speed_BD = 1500;                  //���BD�ƽ����ٶ�
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
//				Position_AC += 10;
				Task_MotorSys_Thruster_SpeedSet(A_1,1400);
                Task_MotorSys_Thruster_SpeedSet(B_1,1400);
                Task_MotorSys_Thruster_SpeedSet(C_1,1600);
                Task_MotorSys_Thruster_SpeedSet(D_1,1600);
			}
			else
			{
				Task_MotorSys_AllThruster_Stop();
			}
			break;
		case 1:
			if(HMInfo->keyPressed)
			{
//				Position_BD += 10;
				Task_MotorSys_Thruster_SpeedSet(A_1,1400);
                Task_MotorSys_Thruster_SpeedSet(B_1,1600);
                Task_MotorSys_Thruster_SpeedSet(C_1,1600);
                Task_MotorSys_Thruster_SpeedSet(D_1,1400);
			}
			else
			{
				Task_MotorSys_AllThruster_Stop();
			}
			break;
		case 2:
			if(HMInfo->keyPressed)
			{
//				Position_BD -= 10;
				Task_MotorSys_Thruster_SpeedSet(A_1,1600);
                Task_MotorSys_Thruster_SpeedSet(B_1,1400);
                Task_MotorSys_Thruster_SpeedSet(C_1,1600);
                Task_MotorSys_Thruster_SpeedSet(D_1,1400);
			}
			else
			{
				Task_MotorSys_AllThruster_Stop();
			}
			break;
		case 3:
			if(HMInfo->keyPressed)
			{
//				Position_AC -= 10;
				Task_MotorSys_Thruster_SpeedSet(A_1,1600);
                Task_MotorSys_Thruster_SpeedSet(B_1,1600);
                Task_MotorSys_Thruster_SpeedSet(C_1,1600);
                Task_MotorSys_Thruster_SpeedSet(D_1,1600);
			}
			else
			{
				Task_MotorSys_AllThruster_Stop();
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
