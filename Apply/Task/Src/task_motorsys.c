#include "task_motorsys.h"

/**
 * @brief 电机系统初始化函数
 * @param Null
 */
void Task_MotorSys_Init(void)
{
    Drv_PWM_Init(PWM,11);   /* 初始化PWM */
    Drv_Delay_Ms(10000);
}

/* 推进器高电平时间1.5ms停转 */
#define STOP_PWM_HIGHTIME 1500

/**
 * @brief 推进器转速设置子函数
 * @param index 选择几号推进器
 * @param _highTime 高电平时间大小	_highTime可设置为500-2500,1500停止
							500-1500 逆时针旋转 1500-2500顺时针旋转
 * @retval null
*/
void Task_MotorSys_Thruster_SpeedSet(uint8_t index,uint16_t _highTime)
{
	Drv_PWM_HighLvTimeSet(&PWM[index], _highTime);
}

/**
 * @brief 所有推进器相同转速设置函数
 * @param _highTime 高电平时间大小	_highTime可设置为500-2500,1500停止
							500-1500 逆时针旋转 1500-2500顺时针旋转
 * @retval null
*/
void Task_MotorSys_AllThruster_SpeedSet(uint16_t _highTime)
{
	Drv_PWM_HighLvTimeSet(&PWM[A_1], _highTime);
	Drv_PWM_HighLvTimeSet(&PWM[B_1], _highTime);
	Drv_PWM_HighLvTimeSet(&PWM[C_1], _highTime);
	Drv_PWM_HighLvTimeSet(&PWM[D_1], _highTime);
}	

/**
 * @brief 推进器开始工作
 * @param index 选择几号推进器
 * @param _highTime 高电平时间大小
 * @retval null
*/
void Task_MotorSys_Thruster_Start(uint8_t index,uint16_t _highTime)
{
	/* 推进器运行速度设置 */
	Task_MotorSys_Thruster_SpeedSet(index,_highTime);
}

/**
 * @brief 所有推进器开始工作
 * @param *adress 存放四个推进器的分量数组的首地址
 * @retval null
*/
void Task_MotorSys_AllThruster_Start(float *adress)
{
	Task_MotorSys_Thruster_Start(A_1,*adress+STOP_PWM_HIGHTIME);
	Task_MotorSys_Thruster_Start(B_1,*(adress+1)+STOP_PWM_HIGHTIME);
	Task_MotorSys_Thruster_Start(C_1,*(adress+2)+STOP_PWM_HIGHTIME);
	Task_MotorSys_Thruster_Start(D_1,*(adress+3)+STOP_PWM_HIGHTIME);
}

/**
 * @brief 推进器停止工作
 * @param index 选择几号推进器
 * @param _fVal 占空比大小
 * @retval null
*/
void Task_MotorSys_Thruster_Stop(uint8_t index)
{
	/* 推进器运行速度设置 */
	Drv_PWM_HighLvTimeSet(&PWM[index], STOP_PWM_HIGHTIME);
}

/**
 * @brief 所有推进器停止工作
 * @param null
 * @retval null
*/
void Task_MotorSys_AllThruster_Stop(void)
{
	Task_MotorSys_Thruster_Stop(A_1);
	Task_MotorSys_Thruster_Stop(B_1);
	Task_MotorSys_Thruster_Stop(C_1);
	Task_MotorSys_Thruster_Stop(D_1);
}

/*180°舵机
    0.5ms----------------0度；          2.5%
    1ms -----------------45度；         5%
    1.5ms----------------90度；         7.5%
    2ms -----------------135度；        10%
    2.5ms ---------------180度          12.5% */

#define ANGLE_0_PWM_HIGHTIME        500
#define ANGLE_90_PWM_HIGHTIME       1500
#define ANGLE_180_PWM_HIGHTIME      2500

/**
 * @brief 舵机转角函数
 * @param index 选择几号舵机 
 * @param ang 角度（0度——180度）
 * @retval null
*/
void Task_MotorSys_Steer_Angle_Set(uint8_t index, uint8_t ang)
{
    // 添加角度范围保护
    if(ang > 180) ang = 180;
    
    // 使用浮点数确保精度
    float pulse_us = 500.0f + (ang / 180.0f) * 2000.0f;
    
    Drv_PWM_HighLvTimeSet(&PWM[index], (uint32_t)pulse_us);
}

/**
 * @brief 所有舵机转角函数
 * @param ang 角度（0度——180度）
 * @retval null
*/
void Task_MotorSys_All_Steer_Angle_Set(uint8_t ang)
{
	Task_MotorSys_Steer_Angle_Set(A_2,ang);
    Drv_Delay_Ms(100);
    Task_MotorSys_Steer_Angle_Set(B_2,ang);
    Drv_Delay_Ms(100);
    Task_MotorSys_Steer_Angle_Set(C_2,ang);
    Drv_Delay_Ms(100);
    Task_MotorSys_Steer_Angle_Set(D_2,ang);
    Drv_Delay_Ms(100);
}

/**
 * @brief 舵机定0度函数
 * @param index 选择几号舵机 
 * @retval null
*/
void Task_MotorSys_Steer_0Angle(uint8_t index)
{
    Drv_PWM_HighLvTimeSet(&PWM[index],ANGLE_0_PWM_HIGHTIME);
}

/**
 * @brief 所有舵机定0度函数
 * @param NULL
 * @retval null
*/
void Task_MotorSys_AllSteer_0Angle(void)
{
    Task_MotorSys_Steer_0Angle(A_2);
    Task_MotorSys_Steer_0Angle(B_2);
    Task_MotorSys_Steer_0Angle(C_2);
    Task_MotorSys_Steer_0Angle(D_2);
    //Drv_Delay_Ms(500);//延时500ms完成转动,延时时间待测试
}

/**
 * @brief 舵机定90度函数
 * @param index 选择几号舵机 
 * @retval null
*/
void Task_MotorSys_Steer_90Angle(uint8_t index)
{
    Drv_PWM_HighLvTimeSet(&PWM[index],ANGLE_90_PWM_HIGHTIME);
}

/**
 * @brief 所有舵机定90度函数
 * @param NULL
 * @retval null
*/
void Task_MotorSys_AllSteer_90Angle(void)
{
    Task_MotorSys_Steer_90Angle(A_2);
    Task_MotorSys_Steer_90Angle(B_2);
    Task_MotorSys_Steer_90Angle(C_2);
    Task_MotorSys_Steer_90Angle(D_2);
    //Drv_Delay_Ms(500);//延时500ms完成转动
}

/**
 * @brief 舵机定180度函数
 * @param index 选择几号舵机 
 * @retval null
*/
void Task_MotorSys_Steer_180Angle(uint8_t index)
{
    Drv_PWM_HighLvTimeSet(&PWM[index],ANGLE_180_PWM_HIGHTIME);
}

/**
 * @brief 所有舵机定180度函数
 * @param NULL
 * @retval null
*/
void Task_MotorSys_AllSteer_180Angle(void)
{
    Task_MotorSys_Steer_180Angle(A_2);
    Task_MotorSys_Steer_180Angle(B_2);
    Task_MotorSys_Steer_180Angle(C_2);
    Task_MotorSys_Steer_180Angle(D_2);
    //Drv_Delay_Ms(500);//延时500ms完成转动
}



