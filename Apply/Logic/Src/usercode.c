#include "usercode.h"		/* usercode头文件 */
#include "drv_hal_conf.h"   /* SGA库头文件配置 */
#include "task_conf.h"      /* task层头文件配置 */
#include "ocd_conf.h"       /* OCD层头文件配置 */
#include "dev_conf.h"		/* Dev层头文件配置 */
#include "algo_conf.h"		/* Algo层头文件配置 */
#include "config.h"			/* I/O配置头文件配置 */

/* 线程句柄 */
rt_thread_t TestThread_t = RT_NULL;
rt_thread_t ReportDataThread_t = RT_NULL;
rt_thread_t JY901Thread_t = RT_NULL;
rt_thread_t MS5837Thread_t = RT_NULL;
rt_thread_t AD4111Thread_t = RT_NULL;
rt_thread_t IPCcmdThread_t = RT_NULL;
rt_thread_t IMX6ULLThread_t = RT_NULL;
rt_thread_t DS1337Thread_t = RT_NULL;
rt_thread_t AutoModeThread_t = RT_NULL;
rt_thread_t HandleModeThread_t = RT_NULL;

/* 信号量句柄 */
rt_sem_t JY901S_Sem = RT_NULL;			//JY901S数据信号量
rt_sem_t CmdFromIPC_Sem = RT_NULL;		//上位机命令信号量

/*消息队列句柄*/
rt_mq_t AutoModemq = RT_NULL;		//自动模式消息队列
rt_mq_t HandleModemq = RT_NULL;		//手动模式消息队列

/* 用户逻辑代码 */
void UserLogic_Code(void)
{
	/* 创建信号量 */
	JY901S_Sem = rt_sem_create("JY901Sem",0,RT_IPC_FLAG_FIFO);
	CmdFromIPC_Sem = rt_sem_create("CmdFromIPC_Sem",0,RT_IPC_FLAG_FIFO);

	/* 创建消息队列 */
	AutoModemq = rt_mq_create("AutoModemq",50,50,RT_IPC_FLAG_FIFO);
	HandleModemq = rt_mq_create("HandleModemq",50,50,RT_IPC_FLAG_FIFO);

	/* 创建线程 */
	TestThread_t 		= rt_thread_create("DataFromIPC",TestThread,NULL,1024,15,20);
	ReportDataThread_t  = rt_thread_create("ReportDataThread",ReportDataThread,NULL,512,2,20);
	JY901Thread_t 		= rt_thread_create("JY901Thread",JY901Thread,NULL,512,7,20);
	MS5837Thread_t 		= rt_thread_create("MS5837Thread",MS5837Thread,NULL,512,8,20);
	AD4111Thread_t 		= rt_thread_create("AD4111Thread",AD4111Thread,NULL,512,8,20);
	IPCcmdThread_t 		= rt_thread_create("IPCcmdThread",IPCcmdThread,NULL,512,1,20);
	IMX6ULLThread_t 	= rt_thread_create("IMX6ULLThread",IMX6ULLThread,NULL,1024,4,20);
	DS1337Thread_t 		= rt_thread_create("DS1337Thread",DS1337Thread,NULL,512,9,20);
	HandleModeThread_t 	= rt_thread_create("HandleModeThread",HandleModeThread,NULL,512,5,20);
	AutoModeThread_t 	= rt_thread_create("AutoModeThread",AutoModeThread,NULL,512,5,20);

#define TEST

#ifdef TEST
	rt_thread_startup(TestThread_t);			//测试线程

#else
	rt_thread_startup(ReportDataThread_t);		//报告数据线程
	rt_thread_startup(JY901Thread_t);			//JY901线程
	rt_thread_startup(MS5837Thread_t);			//MS5837线程
	rt_thread_startup(AD4111Thread_t);			//AD4111线程
	rt_thread_startup(IPCcmdThread_t);			//上位机命令线程
	rt_thread_startup(IMX6ULLThread_t);			//I.MX6ull线程
	rt_thread_startup(DS1337Thread_t);			//DS1337线程
	rt_thread_startup(HandleModeThread_t);		//手动线程
	rt_thread_startup(AutoModeThread_t);		//自动线程
#endif // TEST
}
