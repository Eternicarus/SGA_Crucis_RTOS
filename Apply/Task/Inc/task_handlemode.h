#ifndef __TASK_HANDLEMODE_H_
#define __TASK_HANDLEMODE_H_

#include "drv_hal_conf.h"
#include "config.h"
#include "usercode.h"
#include "task_conf.h"

/* 手动模式信息结构体 */
typedef struct 
{
    uint8_t ModeChange;             //模式切换标志
    float JoystickInfo[2];          //存放手柄数据
	uint8_t key;					//存放手柄按键编号
    bool keyPressed;
}HandleModeInfo;

void Task_HandleMode_Process(HandleModeInfo *HMInfo);

#endif
