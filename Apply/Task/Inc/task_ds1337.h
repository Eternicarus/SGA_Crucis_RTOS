#ifndef __TASK_DS1337_H__
#define __TASK_DS1337_H__

#include "drv_hal_conf.h"
#include "config.h"
#include "usercode.h"
#include "task_reportdata.h"

void Task_DS1337_Handle(void);
void Task_DS1337_SYNC(uint8_t *DateCMD);

#endif // !__TASK_DS1337_H__




