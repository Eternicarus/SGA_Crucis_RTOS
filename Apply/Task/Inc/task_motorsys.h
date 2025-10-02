#ifndef __TASK_MOTORSYS_H__
#define __TASK_MOTORSYS_H__

#include "drv_hal_conf.h"
#include "config.h"
#include "usercode.h"

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

#endif // !__TASK_MOTORSYS_H__




