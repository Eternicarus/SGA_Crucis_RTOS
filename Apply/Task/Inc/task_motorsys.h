#ifndef __TASK_MOTORSYS_H__
#define __TASK_MOTORSYS_H__

#include "drv_hal_conf.h"
#include "config.h"
#include "usercode.h"


#define STOP_PWM_HIGHTIME 1500                          // 推进器高电平时间1.5ms停转
#define RAD2DEG (180.0f / 3.14159265358979323846f)      // 弧度转角度
#define MOTOR_MAX_SPEED 100                             // 推进器最大速度
#define MOTOR_MIN_SPEED -100                            // 推进器最小速度
#define MOTOR_MAX_ANGLE 180                             // 舵机最大转角
#define MOTOR_SPEED_AMP 1.1                             // 推进器速度反向增幅

typedef struct 
{
    int16_t Speed_A;
    int16_t Speed_B;
    int16_t Speed_C;
    int16_t Speed_D;
}SpeedInfo;

typedef struct 
{
    int16_t Angle_A;
    int16_t Angle_B;
    int16_t Angle_C;
    int16_t Angle_D;
}AngleInfo;

typedef struct 
{
    int16_t RollSys;
    int16_t PitchSys;
    int16_t YawSys;
    int16_t DepthSys;
    int16_t DirectSys[4];
}StatusInfo;

typedef struct 
{
    SpeedInfo StcSpeed;
    AngleInfo StcAngle;
    StatusInfo StcStatus;
}MotorSysInfo;

void Task_MotorSys_Init(void);
void Task_MotorSys_Thruster_SpeedSet(uint8_t index,uint16_t _highTime);
void Task_MotorSys_AllThruster_SpeedSet(uint16_t _highTime);
void Task_MotorSys_Thruster_Start(uint8_t index,uint16_t _highTime);
void Task_MotorSys_AllThruster_Start(float *adress);
void Task_MotorSys_Thruster_Stop(uint8_t index);
void Task_MotorSys_AllThruster_Stop(void);
void Task_MotorSys_Steer_Angle_Set(uint8_t index,uint8_t ang);
void Task_MotorSys_Steer_0Angle(uint8_t index);
void Task_MotorSys_AllSteer_0Angle(void);
void Task_MotorSys_Steer_90Angle(uint8_t index);
void Task_MotorSys_AllSteer_90Angle(void);
void Task_MotorSys_Steer_180Angle(uint8_t index);
void Task_MotorSys_AllSteer_180Angle(void);
void Task_MotorSys_Handle(MotorSysInfo *MSInfo);

#endif // !__TASK_MOTORSYS_H__




