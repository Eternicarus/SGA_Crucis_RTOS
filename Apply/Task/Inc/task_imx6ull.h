#ifndef __TASK_IMX6ULL_H__
#define __TASK_IMX6ULL_H__

#include "drv_hal_conf.h"
#include "config.h"
#include "usercode.h"
#include "task_reportdata.h"

typedef struct 
{
    char NS;                //南北纬
    float Latitude;         //维度
    char WE;                //东西经
    float Longitude;        //经度

    char Status;            //定位有效性
}tagGPSinfo_T;

void Task_IMX6ULL_Handle(void);

#endif // !__TASK_IMX6ULL_H__

