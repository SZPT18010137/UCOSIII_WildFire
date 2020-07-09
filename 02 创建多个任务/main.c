#include "includes.h"

//优先级0：中断服务服务管理任务 OS_IntQTask()
//优先级1：时钟节拍任务 OS_TickTask()
//优先级2：定时任务 OS_TmrTask()
//优先级3：开始任务 START_Task()
//优先级4：LED0任务 LED0_Task()
//优先级5：LED1任务 LED1_Task()
//优先级6：Beep任务 Beep_Task()
//优先级OS_CFG_PRIO_MAX-2：统计任务 OS_StatTask()
//优先级OS_CFG_PRIO_MAX-1：空闲任务 OS_IdleTask()

//任务优先级
#define START_TASK_PRIO		3
#define LED0_TASK_PRIO		4
#define LED1_TASK_PRIO		5
#define Beep_TASK_PRIO		6

//任务堆栈大小	
#define START_STK_SIZE 		512
#define LED0_STK_SIZE 		128
#define LED1_STK_SIZE 		128
#define Beep_STK_SIZE 		128

//任务控制块
OS_TCB START_TCB;
OS_TCB LED0_TCB;
OS_TCB LED1_TCB;
OS_TCB Beep_TCB;

//任务堆栈	
CPU_STK START_TASK_STK[START_STK_SIZE];
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
CPU_STK LED1_TASK_STK[LED1_STK_SIZE];
CPU_STK Beep_TASK_STK[Beep_STK_SIZE];

//任务函数
void START_Task(void *p_arg);
void LED0_Task(void *p_arg);
void LED1_Task(void *p_arg);
void Beep_Task(void *p_arg);

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
    BSP_Init(); // 外设初始化
	
	OSInit(&err);		 //初始化UCOSIII
	OS_CRITICAL_ENTER(); //进入临界区
    
	//创建开始任务
	OSTaskCreate((OS_TCB 	* ) &START_TCB,		                           //任务控制块
				 (CPU_CHAR	* ) "START_Task", 		                       //任务名字
                 (OS_TASK_PTR ) START_Task, 			                   //任务函数
                 (void		* ) 0,					                       //传递给任务函数的参数
                 (OS_PRIO	  ) START_TASK_PRIO,                           //任务优先级
                 (CPU_STK   * ) &START_TASK_STK[0],	                       //任务堆栈基地址
                 (CPU_STK_SIZE) START_STK_SIZE/10,	                       //任务堆栈深度限位
                 (CPU_STK_SIZE) START_STK_SIZE,		                       //任务堆栈大小
                 (OS_MSG_QTY  ) 0,					                       //任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  ) 0,					                       //当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* ) 0,					                       //用户补充的存储区
                 (OS_OPT      ) OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* ) &err);				                       //存放该函数错误时的返回值
                 
	OS_CRITICAL_EXIT();	//退出临界区	 
	OSStart(&err);      //开启UCOSIII
                 
	while(1);
}

//开始任务函数
void START_Task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
#endif		
	
	OS_CRITICAL_ENTER(); //进入临界区
    
	//创建LED0任务
	OSTaskCreate((OS_TCB 	* ) &LED0_TCB,		                           //任务控制块
				 (CPU_CHAR	* ) "LED0_Task", 		                       //任务名字
                 (OS_TASK_PTR ) LED0_Task, 			                       //任务函数
                 (void		* ) 0,					                       //传递给任务函数的参数
                 (OS_PRIO	  ) LED0_TASK_PRIO,                            //任务优先级
                 (CPU_STK   * ) &LED0_TASK_STK[0],	                       //任务堆栈基地址
                 (CPU_STK_SIZE) LED0_STK_SIZE/10,	                       //任务堆栈深度限位
                 (CPU_STK_SIZE) LED0_STK_SIZE,		                       //任务堆栈大小
                 (OS_MSG_QTY  ) 0,					                       //任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  ) 0,					                       //当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* ) 0,					                       //用户补充的存储区
                 (OS_OPT      ) OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* ) &err);				                       //存放该函数错误时的返回值				
				 		 
    //创建LED1任务
	OSTaskCreate((OS_TCB 	* ) &LED1_TCB,		                           //任务控制块
				 (CPU_CHAR	* ) "LED1_Task", 		                       //任务名字
                 (OS_TASK_PTR ) LED1_Task, 			                       //任务函数
                 (void		* ) 0,					                       //传递给任务函数的参数
                 (OS_PRIO	  ) LED1_TASK_PRIO,                            //任务优先级
                 (CPU_STK   * ) &LED1_TASK_STK[0],	                       //任务堆栈基地址
                 (CPU_STK_SIZE) LED1_STK_SIZE/10,	                       //任务堆栈深度限位
                 (CPU_STK_SIZE) LED1_STK_SIZE,		                       //任务堆栈大小
                 (OS_MSG_QTY  ) 0,					                       //任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  ) 0,					                       //当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* ) 0,					                       //用户补充的存储区
                 (OS_OPT      ) OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* ) &err);				                       //存放该函数错误时的返回值	

    //创建Beep任务
	OSTaskCreate((OS_TCB 	* ) &Beep_TCB,		                           //任务控制块
				 (CPU_CHAR	* ) "Beep_Task", 		                       //任务名字
                 (OS_TASK_PTR ) Beep_Task, 			                       //任务函数
                 (void		* ) 0,					                       //传递给任务函数的参数
                 (OS_PRIO	  ) Beep_TASK_PRIO,                            //任务优先级
                 (CPU_STK   * ) &Beep_TASK_STK[0],	                       //任务堆栈基地址
                 (CPU_STK_SIZE) Beep_STK_SIZE/10,	                       //任务堆栈深度限位
                 (CPU_STK_SIZE) Beep_STK_SIZE,		                       //任务堆栈大小
                 (OS_MSG_QTY  ) 0,					                       //任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  ) 0,					                       //当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* ) 0,					                       //用户补充的存储区
                 (OS_OPT      ) OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* ) &err);				                       //存放该函数错误时的返回值	
                 
	OS_CRITICAL_EXIT();	//退出临界区
    
    OSTaskDel((OS_TCB 	* ) 0,
              (OS_ERR 	* ) &err); // 删除开始任务
}

//LED0任务函数
void LED0_Task(void *p_arg){
    
	OS_ERR err;
	p_arg = p_arg;
    
	while(1){
        
		LED0 = ~LED0; // LED0翻转
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //延时200ms
	}
}

//LED1任务函数
void LED1_Task(void *p_arg){
    
	OS_ERR err;
	p_arg = p_arg;
    
	while(1){
        
		LED1 = ~LED1; // LED1翻转
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //延时200ms
	}
}

//Beep任务函数
void Beep_Task(void *p_arg){
    
	OS_ERR err;
	p_arg = p_arg;
    
	while(1){
        
		Beep = 1; // Beep响
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //延时200ms
        Beep = 0; // Beep不响
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //延时1s
	}
}
