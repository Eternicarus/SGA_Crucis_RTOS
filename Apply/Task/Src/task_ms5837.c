#include "task_ms5837.h"

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
}


