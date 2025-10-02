#ifndef	__USERCODE_H_
#define	__USERCODE_H_

#include "drv_hal_conf.h"

//#define TEST

void UserLogic_Code(void);

extern rt_sem_t JY901S_Sem;
extern rt_sem_t CmdFromIPC_Sem;

extern rt_mq_t AutoModemq;
extern rt_mq_t HandleModemq;

extern rt_thread_t TestThread_t;
extern rt_thread_t ReportDataThread_t;
extern rt_thread_t JY901Thread_t;
extern rt_thread_t MS5837Thread_t;
extern rt_thread_t AD4111Thread_t;
extern rt_thread_t IPCcmdThread_t;
extern rt_thread_t IMX6ULLThread_t;
extern rt_thread_t DS1337Thread_t;
extern rt_thread_t AutoModeThread_t;
extern rt_thread_t HandleModeThread_t;

#endif
