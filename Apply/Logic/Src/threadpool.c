#include "usercode.h"		/* usercode头文件 */
#include "threadpool.h"		/* threadpool头文件 */
#include "drv_hal_conf.h"   /* SGA库头文件配置 */
#include "task_conf.h"      /* task层头文件配置 */
#include "ocd_conf.h"       /* OCD层头文件配置 */
#include "dev_conf.h"		/* Dev层头文件配置 */
#include "algo_conf.h"		/* Algo层头文件配置 */
#include "config.h"			/* I/O配置头文件配置 */
MotorSysInfo MSInfo = {0};  // 电机系统信息结构体实例
/* 线程入口函数（使用裸机忽略此文件） */
/* 自动线程 */
void AutoModeThread(void* paramenter)
{
    AutoModeInfo AMInfo;
    HandleModeInfo ClearBuf;

    //默认挂起自动模式
    rt_thread_suspend(rt_thread_self());
    rt_schedule();

    while(1)
    {
        if(rt_mq_recv(AutoModemq,&AMInfo,sizeof(AutoModeInfo),RT_WAITING_NO) == RT_EOK)
        {
            //自动控制消息队列接收到数据，将切换到手柄模式
            if(AMInfo.ModeChange)
            {
                AMInfo.ModeChange = 0;
                //将HandleModemq队列中所有内容清空
                while(1)
                {
                    if(rt_mq_recv(HandleModemq,&ClearBuf,sizeof(HandleModeInfo),RT_WAITING_NO) != RT_EOK)
                        break;
                }

                printf("Switch to HANDLE Mode\r\n");
                rt_enter_critical();                    //调度器上锁
                rt_thread_suspend(rt_thread_self());    //挂起本线程
                rt_thread_resume(HandleModeThread_t);   //恢复手动控制线程
                rt_exit_critical();                     //调度器解锁
                rt_schedule();                          //立即执行一次调度
            }
        }
        else
        {
            Task_AutoMode_Process(&AMInfo);
        }
        // printf("AutoMode\r\n");
        // Drv_Delay_Ms(1000);
        rt_thread_yield();
    }
}
/* 手动线程 */
void HandleModeThread(void* paramenter)
{
    HandleModeInfo HMInfo;
    AutoModeInfo ClearBuf;
    // MotorSysInfo MSInfo;

    while(1)
    {
        if(rt_mq_recv(HandleModemq,&HMInfo,sizeof(HandleModeInfo),RT_WAITING_FOREVER) == RT_EOK)
        {
            //手柄控制消息队列接收到数据，将切换到自动模式
            if(HMInfo.ModeChange)
            {
                HMInfo.ModeChange = 0;
                //将AutoModemq消息队列中所有内容清空
                while(1)
                {
                    if(rt_mq_recv(AutoModemq,&ClearBuf,sizeof(AutoModeInfo),RT_WAITING_NO) != RT_EOK)
                        break;
                }
                
                printf("Switch to AUTO Mode\r\n");
                rt_enter_critical();                    //调度器上锁
                rt_thread_suspend(rt_thread_self());    //挂起本线程
                rt_thread_resume(AutoModeThread_t);     //恢复自动控制线程
                rt_exit_critical();                     //调度器解锁
                rt_schedule();                          //立即执行一次调度
            }

            rt_mutex_take(Handle_Mutex,RT_WAITING_FOREVER);
            Task_HandleMode_Process(&HMInfo);
            rt_mutex_release(Handle_Mutex);
        }
    }
}

/* 测试线程 */
void TestThread(void* paramenter)
{
    while(1)
    {
        Task_Test_Handle();
        rt_thread_yield();
    }
}

/* 报告数据线程 */
void ReportDataThread(void* paramenter)
{
    Task_ReportData_Handle();
    Drv_Delay_Ms(1);
}

/* 读取JY901S数据线程 */
void JY901Thread(void* paramenter)
{
    while(1)
    {
        rt_mutex_take(Orientation_Mutex,RT_WAITING_FOREVER);
        Task_JY901_Handle();
        rt_mutex_release(Orientation_Mutex);
        Drv_Delay_Ms(400);
    }
}

/* 读取MS5837数据线程 */
void MS5837Thread(void* paramenter)
{
    while(1)
    {
        rt_mutex_take(Depth_Mutex,RT_WAITING_FOREVER);
        Task_MS5837_Handle();
        rt_mutex_release(Depth_Mutex);
        Drv_Delay_Ms(600);
    }    
}

/* 读取AD4111数据线程 */
void AD4111Thread(void* paramenter)
{
    Task_AD4111_Sync();
    while(1)
    {
        Task_AD4111_Handle();
        Drv_Delay_Ms(500);
    }
}

/* 上位机命令解析线程 */
void IPCcmdThread(void* paramenter)
{
    while(1)
    {
        Task_IPCcmd_Handle();
        Drv_Delay_Ms(1);
    }
}

/* I.MX6ull解析线程 */
void IMX6ULLThread(void* paramenter)
{
    while(1)
    {
        Task_IMX6ULL_Handle();
        Drv_Delay_Ms(1);     
    }
}

/* DS1337解析线程 */
void DS1337Thread(void* paramenter)
{
    while(1)
    {
        Task_DS1337_Handle();
        Drv_Delay_Ms(1000);     
    }
}

/* 电机控制线程 */
void MotorSysThread(void* paramenter)
{
    while(1)
    {
        if(rt_sem_take(MotorSys_Sem,RT_WAITING_FOREVER) == RT_EOK)
        {
            rt_mutex_take(Depth_Mutex,RT_WAITING_FOREVER);
            rt_mutex_take(Orientation_Mutex,RT_WAITING_FOREVER);
            rt_mutex_take(Handle_Mutex,RT_WAITING_FOREVER);

            //收到电机控制消息
            Task_MotorSys_Handle(&MSInfo);

            rt_mutex_release(Handle_Mutex);
            rt_mutex_release(Orientation_Mutex);
            rt_mutex_release(Depth_Mutex);
        }
        // Drv_Delay_Ms(100);
    }
}
