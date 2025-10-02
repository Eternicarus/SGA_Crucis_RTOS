#ifndef __TASK_AUTOMODE_H_
#define __TASK_AUTOMODE_H_

#include "drv_hal_conf.h"

/* 自动模式信息结构体 */
typedef struct 
{
    uint8_t ModeChange;             //模式切换标志
    float Yaw;                      //航向角
    float Depth;                    //深度值
}AutoModeInfo;

#define STOP_PWM_VALUE 1500

void Task_AutoMode_Process(AutoModeInfo *AMInfo);

#endif
