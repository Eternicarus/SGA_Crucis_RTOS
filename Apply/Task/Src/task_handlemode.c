#include "task_handlemode.h"



/**
 * @brief 手动模式处理函数
 * @param HMInfo 手动模式信息结构体指针
 * @note 目前是没有加PID控制的，后续加上的话把转向和升降的部分改成更改PID预期值即可
 */
void Task_HandleMode_Process(HandleModeInfo *HMInfo)
{
	static MotorSysInfo MSInfo = {0};
    //非0数据显示
    if(HMInfo->JoystickInfo[0] != 0.0f && HMInfo->JoystickInfo[1] != 0.0f)
        printf("%f %f\r\n",HMInfo->JoystickInfo[0],HMInfo->JoystickInfo[1]);
//    printf("%d\r\n",(*HMInfo).key);
	//手柄数据处理
	switch((*HMInfo).key)
	{
		//平移
		case 0:
			if(HMInfo->keyPressed)
			{
				MSInfo.StcStatus.DirectSys[0] = -SPEED_DIRECT;
				MSInfo.StcStatus.DirectSys[1] = -SPEED_DIRECT;
				MSInfo.StcStatus.DirectSys[2] = -SPEED_DIRECT;
				MSInfo.StcStatus.DirectSys[3] = -SPEED_DIRECT;
			}
			else
				memset(MSInfo.StcStatus.DirectSys, 0, sizeof(MSInfo.StcStatus.DirectSys));
			rt_mq_send(MotorSysmq, &MSInfo, sizeof(MotorSysInfo));
			break;
		case 3:
			if(HMInfo->keyPressed)
			{
				// printf("data:%d\r\n",MSInfo.StcStatus.DirectSys[0]);				
				MSInfo.StcStatus.DirectSys[0] = SPEED_DIRECT;
				MSInfo.StcStatus.DirectSys[1] = SPEED_DIRECT;
				MSInfo.StcStatus.DirectSys[2] = SPEED_DIRECT;
				MSInfo.StcStatus.DirectSys[3] = SPEED_DIRECT;
			}
			else
				memset(MSInfo.StcStatus.DirectSys, 0, sizeof(MSInfo.StcStatus.DirectSys));
			rt_mq_send(MotorSysmq, &MSInfo, sizeof(MotorSysInfo));
			break;
		//转向
		case 1:
			if(HMInfo->keyPressed)
				MSInfo.StcStatus.YawSys = -SPEED_YAW;
				//TargetYaw = -SPEED_YAW;
			else
				MSInfo.StcStatus.YawSys = 0;
			rt_mq_send(MotorSysmq, &MSInfo, sizeof(MotorSysInfo));
			break;
		case 2:
			if(HMInfo->keyPressed)
				MSInfo.StcStatus.YawSys = SPEED_YAW;
				//TargetYaw = -SPEED_YAW;
			else
				MSInfo.StcStatus.YawSys = 0;
			rt_mq_send(MotorSysmq, &MSInfo, sizeof(MotorSysInfo));
			break;
		//升降
		case 4:
			if(HMInfo->keyPressed)
				MSInfo.StcStatus.DepthSys = SPEED_DEPTH;
				//TargetDepth = SPEED_DEPTH;
			else
				MSInfo.StcStatus.DepthSys = 0;
			rt_mq_send(MotorSysmq, &MSInfo, sizeof(MotorSysInfo));
			break;
		case 5:
			if(HMInfo->keyPressed)
				MSInfo.StcStatus.DepthSys = -SPEED_DEPTH;
				// TargetDepth = -SPEED_DEPTH;
			else
				MSInfo.StcStatus.DepthSys = 0;
			rt_mq_send(MotorSysmq, &MSInfo, sizeof(MotorSysInfo));
			break;
	}

    //手柄数据清零，防止重复使用
    HMInfo->JoystickInfo[0] = 0.0f;
    HMInfo->JoystickInfo[1] = 0.0f;
	HMInfo->key = -1;
}
