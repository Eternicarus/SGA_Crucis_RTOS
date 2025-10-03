#include "task_motorsys.h"

/**
 * @brief ���ϵͳ��ʼ������
 * @param Null
 */
void Task_MotorSys_Init(void)
{
    Drv_PWM_Init(PWM,11);   /* ��ʼ��PWM */
    Drv_Delay_Ms(10000);
}

/* �ƽ����ߵ�ƽʱ��1.5msͣת */
#define STOP_PWM_HIGHTIME 1500

/**
 * @brief �ƽ���ת�������Ӻ���
 * @param index ѡ�񼸺��ƽ���
 * @param _highTime �ߵ�ƽʱ���С	_highTime������Ϊ500-2500,1500ֹͣ
							500-1500 ��ʱ����ת 1500-2500˳ʱ����ת
 * @retval null
*/
void Task_MotorSys_Thruster_SpeedSet(uint8_t index,uint16_t _highTime)
{
	Drv_PWM_HighLvTimeSet(&PWM[index], _highTime);
}

/**
 * @brief �����ƽ�����ͬת�����ú���
 * @param _highTime �ߵ�ƽʱ���С	_highTime������Ϊ500-2500,1500ֹͣ
							500-1500 ��ʱ����ת 1500-2500˳ʱ����ת
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
 * @brief �ƽ�����ʼ����
 * @param index ѡ�񼸺��ƽ���
 * @param _highTime �ߵ�ƽʱ���С
 * @retval null
*/
void Task_MotorSys_Thruster_Start(uint8_t index,uint16_t _highTime)
{
	/* �ƽ��������ٶ����� */
	Task_MotorSys_Thruster_SpeedSet(index,_highTime);
}

/**
 * @brief �����ƽ�����ʼ����
 * @param *adress ����ĸ��ƽ����ķ���������׵�ַ
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
 * @brief �ƽ���ֹͣ����
 * @param index ѡ�񼸺��ƽ���
 * @param _fVal ռ�ձȴ�С
 * @retval null
*/
void Task_MotorSys_Thruster_Stop(uint8_t index)
{
	/* �ƽ��������ٶ����� */
	Drv_PWM_HighLvTimeSet(&PWM[index], STOP_PWM_HIGHTIME);
}

/**
 * @brief �����ƽ���ֹͣ����
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

/*180����
    0.5ms----------------0�ȣ�          2.5%
    1ms -----------------45�ȣ�         5%
    1.5ms----------------90�ȣ�         7.5%
    2ms -----------------135�ȣ�        10%
    2.5ms ---------------180��          12.5% */

#define ANGLE_0_PWM_HIGHTIME        500
#define ANGLE_90_PWM_HIGHTIME       1500
#define ANGLE_180_PWM_HIGHTIME      2500

/**
 * @brief ���ת�Ǻ���
 * @param index ѡ�񼸺Ŷ�� 
 * @param ang �Ƕȣ�0�ȡ���180�ȣ�
 * @retval null
*/
void Task_MotorSys_Steer_Angle_Set(uint8_t index, uint8_t ang)
{
    // ��ӽǶȷ�Χ����
    if(ang > 180) ang = 180;
    
    // ʹ�ø�����ȷ������
    float pulse_us = 500.0f + (ang / 180.0f) * 2000.0f;
    
    Drv_PWM_HighLvTimeSet(&PWM[index], (uint32_t)pulse_us);
}

/**
 * @brief ���ж��ת�Ǻ���
 * @param ang �Ƕȣ�0�ȡ���180�ȣ�
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
 * @brief �����0�Ⱥ���
 * @param index ѡ�񼸺Ŷ�� 
 * @retval null
*/
void Task_MotorSys_Steer_0Angle(uint8_t index)
{
    Drv_PWM_HighLvTimeSet(&PWM[index],ANGLE_0_PWM_HIGHTIME);
}

/**
 * @brief ���ж����0�Ⱥ���
 * @param NULL
 * @retval null
*/
void Task_MotorSys_AllSteer_0Angle(void)
{
    Task_MotorSys_Steer_0Angle(A_2);
    Task_MotorSys_Steer_0Angle(B_2);
    Task_MotorSys_Steer_0Angle(C_2);
    Task_MotorSys_Steer_0Angle(D_2);
    //Drv_Delay_Ms(500);//��ʱ500ms���ת��,��ʱʱ�������
}

/**
 * @brief �����90�Ⱥ���
 * @param index ѡ�񼸺Ŷ�� 
 * @retval null
*/
void Task_MotorSys_Steer_90Angle(uint8_t index)
{
    Drv_PWM_HighLvTimeSet(&PWM[index],ANGLE_90_PWM_HIGHTIME);
}

/**
 * @brief ���ж����90�Ⱥ���
 * @param NULL
 * @retval null
*/
void Task_MotorSys_AllSteer_90Angle(void)
{
    Task_MotorSys_Steer_90Angle(A_2);
    Task_MotorSys_Steer_90Angle(B_2);
    Task_MotorSys_Steer_90Angle(C_2);
    Task_MotorSys_Steer_90Angle(D_2);
    //Drv_Delay_Ms(500);//��ʱ500ms���ת��
}

/**
 * @brief �����180�Ⱥ���
 * @param index ѡ�񼸺Ŷ�� 
 * @retval null
*/
void Task_MotorSys_Steer_180Angle(uint8_t index)
{
    Drv_PWM_HighLvTimeSet(&PWM[index],ANGLE_180_PWM_HIGHTIME);
}

/**
 * @brief ���ж����180�Ⱥ���
 * @param NULL
 * @retval null
*/
void Task_MotorSys_AllSteer_180Angle(void)
{
    Task_MotorSys_Steer_180Angle(A_2);
    Task_MotorSys_Steer_180Angle(B_2);
    Task_MotorSys_Steer_180Angle(C_2);
    Task_MotorSys_Steer_180Angle(D_2);
    //Drv_Delay_Ms(500);//��ʱ500ms���ת��
}

/**
 * @brief ���������
 * @param MSInfo ����ٶ���Ϣ�ṹ��ָ��
 * @retval null
 */
void Task_MotorSys_Handle(MotorSysInfo *MSInfo)
{
    float fx, fy;
    float angf;
    float speedf;

    // A
    fx = (float)MSInfo->StcStatus.YawSys;
    fy = (float)(MSInfo->StcStatus.DepthSys + MSInfo->StcStatus.RollSys + MSInfo->StcStatus.PitchSys);
    angf = atan2f(fy, fx) * RAD2DEG;
    speedf = hypotf(fx, fy);
    MSInfo->StcAngle.Angle_A  = (int16_t)(fabsf(angf));         // �������Ƕ�
    MSInfo->StcSpeed.usSpeed_A = (int16_t)(speedf * (angf < 0 ? -1.0f : 1.0f)); // ����Ϊ���� speed ȡ��

    // B
    fx = (float)MSInfo->StcStatus.YawSys;
    fy = (float)(MSInfo->StcStatus.DepthSys + MSInfo->StcStatus.RollSys - MSInfo->StcStatus.PitchSys);
    angf = atan2f(fy, fx) * RAD2DEG;
    speedf = hypotf(fx, fy);
    MSInfo->StcAngle.Angle_B  = (int16_t)(fabsf(angf));
    MSInfo->StcSpeed.usSpeed_B = (int16_t)(speedf * (angf < 0 ? -1.0f : 1.0f));

    // C
    fx = (float)MSInfo->StcStatus.YawSys;
    fy = (float)(MSInfo->StcStatus.DepthSys - MSInfo->StcStatus.RollSys - MSInfo->StcStatus.PitchSys);
    angf = atan2f(fy, fx) * RAD2DEG;
    speedf = hypotf(fx, fy);
    MSInfo->StcAngle.Angle_C  = (int16_t)(fabsf(angf));
    MSInfo->StcSpeed.usSpeed_C = (int16_t)(speedf * (angf < 0 ? -1.0f : 1.0f));

    // D
    fx = (float)MSInfo->StcStatus.YawSys;
    fy = (float)(MSInfo->StcStatus.DepthSys - MSInfo->StcStatus.RollSys + MSInfo->StcStatus.PitchSys);
    angf = atan2f(fy, fx) * RAD2DEG;
    speedf = hypotf(fx, fy);
    MSInfo->StcAngle.Angle_D  = (int16_t)(fabsf(angf));
    MSInfo->StcSpeed.usSpeed_D = (int16_t)(speedf * (angf < 0 ? -1.0f : 1.0f));

    // ��������
    if(MSInfo->StcSpeed.usSpeed_A < 0) MSInfo->StcSpeed.usSpeed_A = MSInfo->StcSpeed.usSpeed_A * MOTOR_SPEED_AMP;
    if(MSInfo->StcSpeed.usSpeed_B < 0) MSInfo->StcSpeed.usSpeed_B = MSInfo->StcSpeed.usSpeed_B * MOTOR_SPEED_AMP;
    if(MSInfo->StcSpeed.usSpeed_C < 0) MSInfo->StcSpeed.usSpeed_C = MSInfo->StcSpeed.usSpeed_C * MOTOR_SPEED_AMP;
    if(MSInfo->StcSpeed.usSpeed_D < 0) MSInfo->StcSpeed.usSpeed_D = MSInfo->StcSpeed.usSpeed_D * MOTOR_SPEED_AMP;
    
    // �޷�
    if(MSInfo->StcSpeed.usSpeed_A > MOTOR_MAX_SPEED) MSInfo->StcSpeed.usSpeed_A = MOTOR_MAX_SPEED;
    if(MSInfo->StcSpeed.usSpeed_A < MOTOR_MIN_SPEED) MSInfo->StcSpeed.usSpeed_A = MOTOR_MIN_SPEED;
    if(MSInfo->StcSpeed.usSpeed_B > MOTOR_MAX_SPEED) MSInfo->StcSpeed.usSpeed_B = MOTOR_MAX_SPEED;
    if(MSInfo->StcSpeed.usSpeed_B < MOTOR_MIN_SPEED) MSInfo->StcSpeed.usSpeed_B = MOTOR_MIN_SPEED;
    if(MSInfo->StcSpeed.usSpeed_C > MOTOR_MAX_SPEED) MSInfo->StcSpeed.usSpeed_C = MOTOR_MAX_SPEED;
    if(MSInfo->StcSpeed.usSpeed_C < MOTOR_MIN_SPEED) MSInfo->StcSpeed.usSpeed_C = MOTOR_MIN_SPEED;
    if(MSInfo->StcSpeed.usSpeed_D > MOTOR_MAX_SPEED) MSInfo->StcSpeed.usSpeed_D = MOTOR_MAX_SPEED;
    if(MSInfo->StcSpeed.usSpeed_D < MOTOR_MIN_SPEED) MSInfo->StcSpeed.usSpeed_D = MOTOR_MIN_SPEED;
}
