#include "task.h"
#include "task_list.h"

/*
*********************************************************************************************************
*                                            Task: LED0_Task
*********************************************************************************************************
*/

/************************** Configuration *************************************/
/* Task Priority      */ #define LED0_TaskPrio 4 
/* Task Stack Size    */ #define LED0_StkSize  128
/* Task Control Block */ OS_TCB  LED0_TCB;
/* Task Stack         */ CPU_STK LED0_Stack[LED0_StkSize];
/* Task Handler       */ void    LED0_Handler(void *p_arg);

/************************** Task Initialize ***********************************/
void LED0_TaskInit(void){
    
    Task_TypeDef *Task_InitStruct;
    OS_ERR err;
    
    Task_InitStruct -> p_tcb       = &LED0_TCB;
    Task_InitStruct -> p_name      = "LED0_Handler";
    Task_InitStruct -> p_task      = LED0_Handler;
    Task_InitStruct -> p_arg       = 0;
    Task_InitStruct -> prio        = LED0_TaskPrio;
    Task_InitStruct -> p_stk_base  = &LED0_Stack[0];
    Task_InitStruct -> stk_limit   = LED0_StkSize / 10;
    Task_InitStruct -> stk_size    = LED0_StkSize;
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
*                                            Task: LED1_Task
*********************************************************************************************************
*/

/************************** Configuration *************************************/
/* Task Priority      */ #define LED1_TaskPrio 4 
/* Task Stack Size    */ #define LED1_StkSize  128
/* Task Control Block */ OS_TCB  LED1_TCB;
/* Task Stack         */ CPU_STK LED1_Stack[LED1_StkSize];
/* Task Handler       */ void    LED1_Handler(void *p_arg);

/************************** Task Initialize ***********************************/
void LED1_TaskInit(void){
    
    Task_TypeDef *Task_InitStruct;
    OS_ERR err;
    
    Task_InitStruct -> p_tcb       = &LED1_TCB;
    Task_InitStruct -> p_name      = "LED1_Handler";
    Task_InitStruct -> p_task      = LED1_Handler;
    Task_InitStruct -> p_arg       = 0;
    Task_InitStruct -> prio        = LED1_TaskPrio;
    Task_InitStruct -> p_stk_base  = &LED1_Stack[0];
    Task_InitStruct -> stk_limit   = LED1_StkSize / 10;
    Task_InitStruct -> stk_size    = LED1_StkSize;
    Task_InitStruct -> time_quanta = 0;
    Task_InitStruct -> p_ext       = 0;
    Task_InitStruct -> opt         = OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR; 
    Task_InitStruct -> p_err       = &err;
    
    OS_TaskCreate(Task_InitStruct);    
}

/************************** Task Handler **************************************/
void LED1_Handler(void *p_arg){
    
    OS_ERR err;
    p_arg = p_arg;
    
    while(1){      
        
        LED1 = ~LED1;
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err); 
    }
}

/*
*********************************************************************************************************
*                                            Task: Beep_Task
*********************************************************************************************************
*/

/************************** Configuration *************************************/
/* Task Priority      */ #define Beep_TaskPrio 4 
/* Task Stack Size    */ #define Beep_StkSize  128
/* Task Control Block */ OS_TCB  Beep_TCB;
/* Task Stack         */ CPU_STK Beep_Stack[Beep_StkSize];
/* Task Handler       */ void    Beep_Handler(void *p_arg);

/************************** Task Initialize ***********************************/
void Beep_TaskInit(void){
    
    Task_TypeDef *Task_InitStruct;
    OS_ERR err;
    
    Task_InitStruct -> p_tcb       = &Beep_TCB;
    Task_InitStruct -> p_name      = "Beep_Handler";
    Task_InitStruct -> p_task      = Beep_Handler;
    Task_InitStruct -> p_arg       = 0;
    Task_InitStruct -> prio        = Beep_TaskPrio;
    Task_InitStruct -> p_stk_base  = &Beep_Stack[0];
    Task_InitStruct -> stk_limit   = Beep_StkSize / 10;
    Task_InitStruct -> stk_size    = Beep_StkSize;
    Task_InitStruct -> time_quanta = 0;
    Task_InitStruct -> p_ext       = 0;
    Task_InitStruct -> opt         = OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR; 
    Task_InitStruct -> p_err       = &err;
    
    OS_TaskCreate(Task_InitStruct);    
}

/************************** Task Handler **************************************/
void Beep_Handler(void *p_arg){
    
    OS_ERR err;
    p_arg = p_arg;
    
    while(1){      
        
        Beep_Reverse();
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err); 
    }
}

/*
*********************************************************************************************************
*                                            StartItem
*********************************************************************************************************
*/

void StartItem(void){
    
    LED0_TaskInit();
    LED1_TaskInit();
    Beep_TaskInit();
}
