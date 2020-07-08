#include "task.h"
#include "task_list.h"

/*
*********************************************************************************************************
*                                            Task: LED_Task
*********************************************************************************************************
*/

/************************** Configuration *************************************/
/* Task Priority      */ #define LED0_TASK_PRIO 4 
/* Tasj Stack Size    */ #define LED0_STK_SIZE  128
/* Task Control Block */ OS_TCB  LED0TaskTCB;
/* Task Stack         */ CPU_STK LED0TaskStack[LED0_STK_SIZE];
/* Task Handler       */ void    LED0_Handler(void *p_arg);

/************************** Task Initialize ***********************************/
void LED0_TaskInit(void){
    
    Task_TypeDef *Task_InitStruct;
    OS_ERR err;
    
    Task_InitStruct -> p_tcb       = &LED0TaskTCB;
    Task_InitStruct -> p_name      = "LED0_Handler";
    Task_InitStruct -> p_task      = LED0_Handler;
    Task_InitStruct -> p_arg       = 0;
    Task_InitStruct -> prio        = LED0_TASK_PRIO;
    Task_InitStruct -> p_stk_base  = &LED0TaskStack[0];
    Task_InitStruct -> stk_limit   = LED0_STK_SIZE / 10;
    Task_InitStruct -> stk_size    = LED0_STK_SIZE;
    Task_InitStruct -> time_quanta = 0;
    Task_InitStruct -> p_ext       = 0;
    Task_InitStruct -> opt         = OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR; 
    Task_InitStruct -> p_err       = &err;
    
    OS_TaskCreate(Task_InitStruct);    
}

/************************** Task Handler **************************************/
void LED0_Handler(void *p_arg){
    
	OS_ERR err;
	p_arg = p_arg;
    
	while(1){      
        
		LED0 = ~LED0;
		OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err); 
	}
}

/*
*********************************************************************************************************
*                                            StartItem
*********************************************************************************************************
*/

void StartItem(void){
    
    LED0_TaskInit();
}
