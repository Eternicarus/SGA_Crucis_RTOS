#include "task_reportdata.h"

uint8_t ReportDataBuffer[FRAMEEND_BASE + 1] = {0};      //报告数据缓存区

uint16_t A_1_HighLvTime = 0;
uint16_t B_1_HighLvTime = 0;
uint16_t C_1_HighLvTime = 0;
uint16_t D_1_HighLvTime = 0;
uint16_t A_2_HighLvTime = 0;
uint16_t B_2_HighLvTime = 0;
uint16_t C_2_HighLvTime = 0;
uint16_t D_2_HighLvTime = 0;

/**
 * @brief 电机高电平时间报告函数
 * @param Null
 */
static void S_PWMHighLvTime_Function(void)
{
    A_1_HighLvTime = PWM[A_1].tPWMHandle.Instance->CCR3;
    B_1_HighLvTime = PWM[B_1].tPWMHandle.Instance->CCR3;
    C_1_HighLvTime = PWM[C_1].tPWMHandle.Instance->CCR1;
    D_1_HighLvTime = PWM[D_1].tPWMHandle.Instance->CCR3;

    A_2_HighLvTime = PWM[A_2].tPWMHandle.Instance->CCR4;
    B_2_HighLvTime = PWM[B_2].tPWMHandle.Instance->CCR4;
    C_2_HighLvTime = PWM[C_2].tPWMHandle.Instance->CCR2;
    D_2_HighLvTime = PWM[D_2].tPWMHandle.Instance->CCR4;

    memcpy(&ReportDataBuffer[THRUSTER_BASE                    ],&A_1_HighLvTime,UINT16_T_SIZE);
    memcpy(&ReportDataBuffer[THRUSTER_BASE +     UINT16_T_SIZE],&B_1_HighLvTime,UINT16_T_SIZE);
    memcpy(&ReportDataBuffer[THRUSTER_BASE + 2 * UINT16_T_SIZE],&C_1_HighLvTime,UINT16_T_SIZE);
    memcpy(&ReportDataBuffer[THRUSTER_BASE + 3 * UINT16_T_SIZE],&D_1_HighLvTime,UINT16_T_SIZE);

    memcpy(&ReportDataBuffer[SERVO_BASE                    ],&A_2_HighLvTime,UINT16_T_SIZE);
    memcpy(&ReportDataBuffer[SERVO_BASE +     UINT16_T_SIZE],&B_2_HighLvTime,UINT16_T_SIZE);
    memcpy(&ReportDataBuffer[SERVO_BASE + 2 * UINT16_T_SIZE],&C_2_HighLvTime,UINT16_T_SIZE);
    memcpy(&ReportDataBuffer[SERVO_BASE + 3 * UINT16_T_SIZE],&D_2_HighLvTime,UINT16_T_SIZE);
}

/**
 * @brief 向外部报告数据处理函数
 * @param Null
 */
void Task_ReportData_Handle(void)
{
    /* 增加帧头帧尾信息 */
    ReportDataBuffer[FRAMESTART_BASE] = '@';
    ReportDataBuffer[FRAMESTART_BASE + 1] = 'D';
    ReportDataBuffer[FRAMESTART_BASE + 2] = 'U';
    ReportDataBuffer[FRAMESTART_BASE + 3] = 'P';
    ReportDataBuffer[FRAMEEND_BASE] = '$';

    while(1)
    {
        S_PWMHighLvTime_Function();
        Drv_Uart_Transmit_DMA(&Uart3,ReportDataBuffer,FRAMEEND_BASE + 1);
        Drv_Delay_Ms(300);
    }
}



