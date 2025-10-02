#ifndef __TASK_HANDLEMODE_H_
#define __TASK_HANDLEMODE_H_

#include "drv_hal_conf.h"
#include "config.h"
#include "usercode.h"
#include "task_conf.h"

/* �ֶ�ģʽ��Ϣ�ṹ�� */
typedef struct 
{
    uint8_t ModeChange;             //ģʽ�л���־
    float JoystickInfo[2];          //����ֱ�����
	uint8_t key;					//����ֱ��������
    bool keyPressed;
}HandleModeInfo;

void Task_HandleMode_Process(HandleModeInfo *HMInfo);

#endif
