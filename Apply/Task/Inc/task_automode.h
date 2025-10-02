#ifndef __TASK_AUTOMODE_H_
#define __TASK_AUTOMODE_H_

#include "drv_hal_conf.h"

/* �Զ�ģʽ��Ϣ�ṹ�� */
typedef struct 
{
    uint8_t ModeChange;             //ģʽ�л���־
    float Yaw;                      //�����
    float Depth;                    //���ֵ
}AutoModeInfo;

#define STOP_PWM_VALUE 1500

void Task_AutoMode_Process(AutoModeInfo *AMInfo);

#endif
