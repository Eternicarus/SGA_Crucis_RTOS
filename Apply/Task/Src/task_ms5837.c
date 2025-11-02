#include "task_ms5837.h"

volatile float TargetDepth = 0.0f; // 目标深度

/**
 * @brief MS5837处理函数
 * @param Null
 */
void Task_MS5837_Handle(void)
{
    OCD_MS5837_GetData(&MS5837);
    if(MS5837.fDepth == 153150.250000)  //未接MS5837的错误数据
        MS5837.fDepth = 0;
#ifdef DEBUG_PRINTF
    printf("M %0.2f\r\n",MS5837.fDepth);
#endif
    memcpy(&ReportDataBuffer[DEPTH_BASE],&MS5837.fDepth,FLOAT_SIZE);

    /* 定深PID示例 */
    // MSInfo.StcStatus.DepthSys = Algo_PID_Calculate(&DepthPID,MS5837.fDepth,TargetDepth);
    // printf("Depth:%f Target:%f PID:%d\r\n",MS5837.fDepth,TargetDepth,MSInfo.StcStatus.DepthSys);
    rt_sem_release(MotorSys_Sem);
}


