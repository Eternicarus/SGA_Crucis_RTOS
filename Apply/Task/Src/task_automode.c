#include "task_automode.h"

/* ��ȿ��ƺ�������Ҫ��ǰ��Ⱥ�������� */
void task_DepthControl_Process(float Curr,float Exp)
{
//    float PIDOut = 0.0;         //PID�����Ľ��

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

//    //ʵ�����1500msΪ�ϸ�
//    PWMInfo.PWMout[LeftVThruster] = -PIDOut + STOP_PWM_VALUE;

//    //�޷�
//    if(PWMInfo.PWMout[LeftVThruster] < 1350)  PWMInfo.PWMout[LeftVThruster] = 1350;
//    if(PWMInfo.PWMout[LeftVThruster] > 1650)  PWMInfo.PWMout[LeftVThruster] = 1650;

//    PWMInfo.PWMout[RightVThruster] = PWMInfo.PWMout[LeftVThruster];

//    Task_Thruster_SpeedSet(LeftVThruster,PWMInfo.PWMout[LeftVThruster]);
//    Task_Thruster_SpeedSet(RightVThruster,PWMInfo.PWMout[RightVThruster]);

}

/**
 * @brief �Զ�ģʽ������
 * @param AMInfo �Զ�ģʽ��Ϣ�ṹ��ָ��
 */
void Task_AutoMode_Process(AutoModeInfo *AMInfo)
{
//    if(!AMInfo->Depth)
//    {
//        task_DepthControl_Process(MS5837.fDepth,AMInfo->Depth);
//    }else{

//    }
}
