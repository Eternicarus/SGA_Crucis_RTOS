#ifndef __TASK_JY901_H__
#define __TASK_JY901_H__

#include "drv_hal_conf.h"
#include "config.h"
#include "usercode.h"
#include "task_reportdata.h"
#include "task_motorsys.h"

extern volatile int16_t TargetYaw;      // 目标偏航角
extern volatile int16_t TargetPitch;    // 目标俯仰角
extern volatile int16_t TargetRoll;     // 目标横滚角

void Task_JY901_Handle(void);

#endif // !__TASK_JY901_H__


