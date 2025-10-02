#include "task_automode.h"

/* 深度控制函数，需要当前深度和期望深度 */
void task_DepthControl_Process(float Curr,float Exp)
{
//    float PIDOut = 0.0;         //PID计算后的结果

//    PIDOut = Algo_PID_Calculate(&DepthPID,Curr,Exp);

//    //printf("%f",PIDOut);
//    Task_MotorSys_Thruster_SpeedSet(A_1,-PIDOut + STOP_PWM_VALUE);
//    Task_MotorSys_Thruster_SpeedSet(B_1,-PIDOut + STOP_PWM_VALUE);
//    Task_MotorSys_Thruster_SpeedSet(C_1,-PIDOut + STOP_PWM_VALUE);
//    Task_MotorSys_Thruster_SpeedSet(D_1,-PIDOut + STOP_PWM_VALUE);
//    Drv_Delay_Ms(2000);
//    Task_MotorSys_Thruster_SpeedSet(A_1,1500);
//    Task_MotorSys_Thruster_SpeedSet(B_1,1500);
//    Task_MotorSys_Thruster_SpeedSet(C_1,1500);
//    Task_MotorSys_Thruster_SpeedSet(D_1,1500);

//    //实测大于1500ms为上浮
//    PWMInfo.PWMout[LeftVThruster] = -PIDOut + STOP_PWM_VALUE;

//    //限幅
//    if(PWMInfo.PWMout[LeftVThruster] < 1350)  PWMInfo.PWMout[LeftVThruster] = 1350;
//    if(PWMInfo.PWMout[LeftVThruster] > 1650)  PWMInfo.PWMout[LeftVThruster] = 1650;

//    PWMInfo.PWMout[RightVThruster] = PWMInfo.PWMout[LeftVThruster];

//    Task_Thruster_SpeedSet(LeftVThruster,PWMInfo.PWMout[LeftVThruster]);
//    Task_Thruster_SpeedSet(RightVThruster,PWMInfo.PWMout[RightVThruster]);

}

/**
 * @brief 自动模式处理函数
 * @param AMInfo 自动模式信息结构体指针
 */
void Task_AutoMode_Process(AutoModeInfo *AMInfo)
{
//    if(!AMInfo->Depth)
//    {
//        task_DepthControl_Process(MS5837.fDepth,AMInfo->Depth);
//    }else{

//    }
}
