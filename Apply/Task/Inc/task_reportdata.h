#ifndef __TASK_REPORTDATA_H__
#define __TASK_REPORTDATA_H__

#include "drv_hal_conf.h"
#include "config.h"

//数据类型占用空间
#define FLOAT_SIZE                  sizeof(float)
#define UINT16_T_SIZE               sizeof(uint16_t)
#define UINT8_T_SIZE                sizeof(uint8_t)

//各种数据类型在数据帧的中的起始位置
#define FRAMESTART_BASE             0
#define DATA_BASE                   4
#define GRADIENTMAGNET_BASE         DATA_BASE
#define THRUSTER_BASE               (GRADIENTMAGNET_BASE + 12 * FLOAT_SIZE)
#define SERVO_BASE                  (THRUSTER_BASE + 4 * UINT16_T_SIZE)
#define GPS_BASE                    (SERVO_BASE + 4 * UINT16_T_SIZE)
#define DEPTH_BASE                  (GPS_BASE + 3 * UINT8_T_SIZE + 2 * FLOAT_SIZE)
#define DATE_BASE                   (DEPTH_BASE + FLOAT_SIZE)
#define ANGLE_BASE                  (DATE_BASE + 6 * UINT8_T_SIZE)
#define MAG_BASE                    (ANGLE_BASE + 3 * FLOAT_SIZE)
#define ACCEL_BASE                  (MAG_BASE + 3 * FLOAT_SIZE)
#define GYRO_BASE                   (ACCEL_BASE + 3 * FLOAT_SIZE)
#define FRAMEEND_BASE               (GYRO_BASE + 3 * FLOAT_SIZE)

extern uint8_t ReportDataBuffer[FRAMEEND_BASE + 1];

void Task_ReportData_Handle(void);

#endif // !__TASK_REPORTDATA_H__
