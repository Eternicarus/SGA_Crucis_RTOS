#ifndef __CONFIG_H_
#define __CONFIG_H_

#include "drv_hal_conf.h"
#include "ocd_conf.h"
#include "algo_conf.h"
#include "dev_conf.h"

/* 用户句柄声明包含区 */

extern tagGPIO_T LED[];

extern tagGPIO_T SYNC;

extern tagUART_T Uart1;

extern tagJY901_T JY901S;

extern tagUART_T Uart3;

extern tagUART_T Uart4;

extern tagAD24BIT_T AD4111_1;

extern tagAD24BIT_T AD4111_2;

extern tagPWM_T PWM[];

extern tagMS5837_T MS5837;

extern tagDS3231_T DS1337;

/* 推进器和舵机在板上的标记 其中1为推进器 2为舵机 */
#define     A_1      0
#define     A_2      1
#define     B_1      2
#define     B_2      3
#define     C_1      4
#define     C_2      5
#define     D_1      6
#define     D_2      7

#endif
