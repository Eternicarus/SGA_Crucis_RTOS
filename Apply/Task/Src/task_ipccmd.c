#include "task_ipccmd.h"

/**
 * @brief 上位机命令处理函数
 * @param Null
 */
void Task_IPCcmd_Handle(void)
{
    uint8_t IPC_ReceBuf[100];
    uint8_t IPC_ReceNum = 0;

    HandleModeInfo HMInfo = {0};        //手动模式消息
    AutoModeInfo AMInfo = {0};          //自动模式消息

    //串口一和串口三都要接收，因为不确定是哪个发送指令
    if(rt_sem_take(CmdFromIPC_Sem,RT_WAITING_FOREVER) == RT_EOK)
    {
        IPC_ReceNum = Drv_Uart_Receive_DMA(&Uart1,IPC_ReceBuf);
        if(IPC_ReceNum != 0)
        {
            printf("u1 %s\r\n",IPC_ReceBuf);    //根据通信协议校验
            goto CmdAnalysis;
        }
        IPC_ReceNum = Drv_Uart_Receive_DMA(&Uart3,IPC_ReceBuf);
        if(IPC_ReceNum != 0)
        {
            printf("u3 %s\r\n",IPC_ReceBuf);    //根据通信协议校验
            goto CmdAnalysis;
        }

CmdAnalysis:
        /* 帧头帧尾校验 */
        if(IPC_ReceBuf[0] == '@' && IPC_ReceBuf[IPC_ReceNum - 1] == '$')
        {
            /* 时间同步 @TS */
            if(IPC_ReceBuf[1] == 'T' && IPC_ReceBuf[2] == 'S')
            {
                Task_DS1337_SYNC(IPC_ReceBuf);
            }
            /* PID调整 @AP */
            else if(IPC_ReceBuf[1] == 'A' && IPC_ReceBuf[2] == 'P')
            {
                // 定义变量
                int PID_NO;
                float P,I,D;
                char *token;

                // 使用strtok()函数进行分割
                token = strtok((char *)IPC_ReceBuf, " "); // 获取第一个 "@AP"
                token = strtok(NULL, " "); // 获取 PID_NO
                PID_NO = atoi(token); // 转换为整数并赋值给 PID_NO
                token = strtok(NULL, " "); // 获取 P
                P = atof(token); // 转换为浮点数并赋值给 P
                token = strtok(NULL, " "); // 获取 I
                I = atof(token); // 转换为浮点数并赋值给 I
                token = strtok(NULL, " "); // 获取 D
                D = atof(token); // 转换为浮点数并赋值给 D
#ifdef DEBUG_PRINTF 
                // 打印结果
                printf("PID_NO: %d", PID_NO);
                printf("P: %f", P);
                printf("I: %f", I);
                printf("D: %f", D);
#endif
                UNUSED(PID_NO);UNUSED(P);UNUSED(I);UNUSED(D);
                //根据PID编号更改
                if(PID_NO == 1){
                    //修改深度PID
                }else if(PID_NO == 2){
                    //修改艏向PID
                }
            }
            /* 模式控制命令 @SM */
            else if(IPC_ReceBuf[1] == 'S' && IPC_ReceBuf[2] == 'M')
            {
                if(!strncmp((char*)IPC_ReceBuf + 3,"AUTO", 4))
                {
                    printf("AUTO\r\n");     //切换自动模式
                    //挂起手柄控制模式，启动自动模式
                    HMInfo.ModeChange = 1;
                    rt_mq_send(HandleModemq,&HMInfo,sizeof(HandleModeInfo));
                }
                else if(!strncmp((char*)IPC_ReceBuf + 3,"MANU", 4))
                {
                    printf("MANU\r\n");     //切换手动模式
                    //挂起自动模式，启动手柄控制模式
                    AMInfo.ModeChange = 1;
                    rt_mq_send(AutoModemq,&AMInfo,sizeof(AutoModeInfo));
                }
            }
            /* 手柄信息 @HCV和@HCB */
            else if(IPC_ReceBuf[1] == 'H' && IPC_ReceBuf[2] == 'C')
            {
                char *token;
                // 使用strtok()函数进行分割
                token = strtok((char *)IPC_ReceBuf, " "); // 获取第一个 "@HCV"或者"@HCB"
                if(IPC_ReceBuf[3] == 'V')
                {
                    token = strtok(NULL, " "); // 获取摇杆角度
                    HMInfo.JoystickInfo[0] = atof(token); // 角度
                    token = strtok(NULL, " "); // 获取摇杆力度
                    HMInfo.JoystickInfo[1] = atof(token); // 力度
                    //printf("Joystick %f %f\r\n",HMInfo.JoystickInfo[0],HMInfo.JoystickInfo[1]);
                    rt_mq_send(HandleModemq,&HMInfo,sizeof(HandleModeInfo));
                }
                else if(IPC_ReceBuf[3] == 'B')
                {
                    token = strtok(NULL, " "); // 获取按键编号
                    HMInfo.key = strtod(token,NULL); // 按键编号
                    printf("NO.%d",HMInfo.key);
                    token = strtok(NULL, " "); // 获取按下状态
                    if(!rt_strcmp(token,"Press")){
                        printf("Press\r\n");
                        HMInfo.keyPressed = true;
                    }else{
                        printf("Release\r\n");
                        HMInfo.keyPressed = false;
                    }
                    rt_mq_send(HandleModemq,&HMInfo,sizeof(HandleModeInfo));
                }
            }
            /* 定航控制 @FY */
            else if(IPC_ReceBuf[1] == 'F' && IPC_ReceBuf[2] == 'Y')
            {
                float ProposedYaw;      //拟定的航向角
                char *token;

                // 使用strtok()函数进行分割
                token = strtok((char *)IPC_ReceBuf, " "); // 获取第一个 "@FY"
                token = strtok(NULL, " "); // 获取拟定航向角
                ProposedYaw = atof(token); // 转换为浮点数并赋值给ProposedYaw
#ifdef DEBUG_PRINTF
                // 打印结果
                printf("ProposedYaw: %f\r\n", ProposedYaw);
#endif
                AMInfo.Yaw = ProposedYaw;
                rt_mq_send(AutoModemq,&AMInfo,sizeof(AutoModeInfo));
            }            
            /* 定深控制 @FD */
            else if(IPC_ReceBuf[1] == 'F' && IPC_ReceBuf[2] == 'D')
            {
				
				
                float ProposedDepth;      //拟定的航向角
                char *token;

                // 使用strtok()函数进行分割
                token = strtok((char *)IPC_ReceBuf, " "); // 获取第一个 "@FD"
                token = strtok(NULL, " "); // 获取拟定航向角
                ProposedDepth = atof(token); // 转换为浮点数并赋值给ProposedDepth
#ifdef DEBUG_PRINTF
                // 打印结果
                printf("ProposedDepth: %f\r\n", ProposedDepth);
#endif
                AMInfo.Depth = ProposedDepth;
                rt_mq_send(AutoModemq,&AMInfo,sizeof(AutoModeInfo));
            }
            /* 停止命令 @STOP */
            else if(IPC_ReceBuf[1] == 'S' && IPC_ReceBuf[2] == 'T' && IPC_ReceBuf[3] == 'O' && IPC_ReceBuf[4] == 'P')
            {
                printf("STOP!\r\n");
                Task_MotorSys_Thruster_SpeedSet(A_1,1500);
                Task_MotorSys_Thruster_SpeedSet(B_1,1500);
                Task_MotorSys_Thruster_SpeedSet(C_1,1500);
                Task_MotorSys_Thruster_SpeedSet(D_1,1500);          
            }
            
            
//不在通信协议中           
            /* 垂直运动 */
            else if(IPC_ReceBuf[1] == 'A' && IPC_ReceBuf[2] == 'B')
            {
                Task_MotorSys_Steer_Angle_Set(A_2,90);
                Drv_Delay_Ms(500);
                Task_MotorSys_Steer_Angle_Set(B_2,90);
                Drv_Delay_Ms(500);
                Task_MotorSys_Steer_Angle_Set(C_2,90);
                Drv_Delay_Ms(500);
                Task_MotorSys_Steer_Angle_Set(D_2,90);
                Drv_Delay_Ms(500);
                Task_MotorSys_Thruster_SpeedSet(A_1,1350);
                Task_MotorSys_Thruster_SpeedSet(B_1,1350);
                Task_MotorSys_Thruster_SpeedSet(C_1,1350);
                Task_MotorSys_Thruster_SpeedSet(D_1,1650);
                Drv_Delay_Ms(10000);
                Task_MotorSys_Thruster_SpeedSet(A_1,1500);
                Task_MotorSys_Thruster_SpeedSet(B_1,1500);
                Task_MotorSys_Thruster_SpeedSet(C_1,1500);
                Task_MotorSys_Thruster_SpeedSet(D_1,1500);
            }
            /* 水平运动 */
            else if(IPC_ReceBuf[1] == '1' && IPC_ReceBuf[2] == '2')
            {
                Task_MotorSys_Steer_Angle_Set(A_2,0);
                Drv_Delay_Ms(500);
                Task_MotorSys_Steer_Angle_Set(B_2,0);
                Drv_Delay_Ms(500);
                Task_MotorSys_Steer_Angle_Set(C_2,0);
                Drv_Delay_Ms(500);
                Task_MotorSys_Steer_Angle_Set(D_2,0);
                Drv_Delay_Ms(500);
                Task_MotorSys_Thruster_SpeedSet(A_1,1450);
                Drv_Delay_Ms(500);
                Task_MotorSys_Thruster_SpeedSet(B_1,1450);
                Drv_Delay_Ms(500);
                Task_MotorSys_Thruster_SpeedSet(C_1,1450);
                Drv_Delay_Ms(500);
                Task_MotorSys_Thruster_SpeedSet(D_1,1550);
                Drv_Delay_Ms(10000);      
                Task_MotorSys_Thruster_SpeedSet(A_1,1500);
                Task_MotorSys_Thruster_SpeedSet(B_1,1500);
                Task_MotorSys_Thruster_SpeedSet(C_1,1500);
                Task_MotorSys_Thruster_SpeedSet(D_1,1500);   

//                Task_MotorSys_Thruster_SpeedSet(A_1,1620);
//                Drv_Delay_Ms(2000);
//                Task_MotorSys_Thruster_SpeedSet(B_1,1620);
//                Drv_Delay_Ms(2000);
//                Task_MotorSys_Thruster_SpeedSet(C_1,1620);
//                Drv_Delay_Ms(2000);
//                Task_MotorSys_Thruster_SpeedSet(D_1,1620);
//                Drv_Delay_Ms(2000);      
//                Task_MotorSys_Thruster_SpeedSet(A_1,1500);
//                Task_MotorSys_Thruster_SpeedSet(B_1,1500);
//                Task_MotorSys_Thruster_SpeedSet(C_1,1500);
//                Task_MotorSys_Thruster_SpeedSet(D_1,1500);                 
            }
            /* 舵机垂向调整 */
            else if(IPC_ReceBuf[1] == 'C' && IPC_ReceBuf[2] == 'D')
            {
				char *token;
				token = strtok((char *)IPC_ReceBuf, " "); // 获取第一个 "@CD"
				token = strtok(NULL, " "); // 获取舵机位置值
				printf("%d\r\n",atoi(token));
                Task_MotorSys_Steer_Angle_Set(A_2,atoi(token));
                Drv_Delay_Ms(500);
                Task_MotorSys_Steer_Angle_Set(B_2,atoi(token));
                Drv_Delay_Ms(500);
                Task_MotorSys_Steer_Angle_Set(C_2,atoi(token));
                Drv_Delay_Ms(500);
                Task_MotorSys_Steer_Angle_Set(D_2,atoi(token));
                Drv_Delay_Ms(500);
            }
            /* 舵机水平调整 */
            else if(IPC_ReceBuf[1] == 'E' && IPC_ReceBuf[2] == 'F')
            {
                Task_MotorSys_Steer_Angle_Set(A_2,0);
                Drv_Delay_Ms(500);
                Task_MotorSys_Steer_Angle_Set(B_2,0);
                Drv_Delay_Ms(500);
                Task_MotorSys_Steer_Angle_Set(C_2,0);
                Drv_Delay_Ms(500);
                Task_MotorSys_Steer_Angle_Set(D_2,0);
                Drv_Delay_Ms(500);
            }
        }
//不在通信协议中      

        IPC_ReceNum = 0;
    }
}


