#include "includes.h"

//���ȼ�0���жϷ������������� OS_IntQTask()
//���ȼ�1��ʱ�ӽ������� OS_TickTask()
//���ȼ�2����ʱ���� OS_TmrTask()
//���ȼ�3����ʼ���� START_Task()
//���ȼ�4��LED0���� LED0_Task()
//���ȼ�5��LED1���� LED1_Task()
//���ȼ�6��Beep���� Beep_Task()
//���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
//���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()

//�������ȼ�
#define START_TASK_PRIO		3
#define LED0_TASK_PRIO		4
#define LED1_TASK_PRIO		5
#define Beep_TASK_PRIO		6

//�����ջ��С	
#define START_STK_SIZE 		512
#define LED0_STK_SIZE 		128
#define LED1_STK_SIZE 		128
#define Beep_STK_SIZE 		128

//������ƿ�
OS_TCB START_TCB;
OS_TCB LED0_TCB;
OS_TCB LED1_TCB;
OS_TCB Beep_TCB;

//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
CPU_STK LED1_TASK_STK[LED1_STK_SIZE];
CPU_STK Beep_TASK_STK[Beep_STK_SIZE];

//������
void START_Task(void *p_arg);
void LED0_Task(void *p_arg);
void LED1_Task(void *p_arg);
void Beep_Task(void *p_arg);

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
    BSP_Init(); // �����ʼ��
	
	OSInit(&err);		 //��ʼ��UCOSIII
	OS_CRITICAL_ENTER(); //�����ٽ���
    
	//������ʼ����
	OSTaskCreate((OS_TCB 	* ) &START_TCB,		                           //������ƿ�
				 (CPU_CHAR	* ) "START_Task", 		                       //��������
                 (OS_TASK_PTR ) START_Task, 			                   //������
                 (void		* ) 0,					                       //���ݸ��������Ĳ���
                 (OS_PRIO	  ) START_TASK_PRIO,                           //�������ȼ�
                 (CPU_STK   * ) &START_TASK_STK[0],	                       //�����ջ����ַ
                 (CPU_STK_SIZE) START_STK_SIZE/10,	                       //�����ջ�����λ
                 (CPU_STK_SIZE) START_STK_SIZE,		                       //�����ջ��С
                 (OS_MSG_QTY  ) 0,					                       //�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  ) 0,					                       //��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* ) 0,					                       //�û�����Ĵ洢��
                 (OS_OPT      ) OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* ) &err);				                       //��Ÿú�������ʱ�ķ���ֵ
                 
	OS_CRITICAL_EXIT();	//�˳��ٽ���	 
	OSStart(&err);      //����UCOSIII
                 
	while(1);
}

//��ʼ������
void START_Task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
#endif		
	
	OS_CRITICAL_ENTER(); //�����ٽ���
    
	//����LED0����
	OSTaskCreate((OS_TCB 	* ) &LED0_TCB,		                           //������ƿ�
				 (CPU_CHAR	* ) "LED0_Task", 		                       //��������
                 (OS_TASK_PTR ) LED0_Task, 			                       //������
                 (void		* ) 0,					                       //���ݸ��������Ĳ���
                 (OS_PRIO	  ) LED0_TASK_PRIO,                            //�������ȼ�
                 (CPU_STK   * ) &LED0_TASK_STK[0],	                       //�����ջ����ַ
                 (CPU_STK_SIZE) LED0_STK_SIZE/10,	                       //�����ջ�����λ
                 (CPU_STK_SIZE) LED0_STK_SIZE,		                       //�����ջ��С
                 (OS_MSG_QTY  ) 0,					                       //�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  ) 0,					                       //��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* ) 0,					                       //�û�����Ĵ洢��
                 (OS_OPT      ) OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* ) &err);				                       //��Ÿú�������ʱ�ķ���ֵ				
				 		 
    //����LED1����
	OSTaskCreate((OS_TCB 	* ) &LED1_TCB,		                           //������ƿ�
				 (CPU_CHAR	* ) "LED1_Task", 		                       //��������
                 (OS_TASK_PTR ) LED1_Task, 			                       //������
                 (void		* ) 0,					                       //���ݸ��������Ĳ���
                 (OS_PRIO	  ) LED1_TASK_PRIO,                            //�������ȼ�
                 (CPU_STK   * ) &LED1_TASK_STK[0],	                       //�����ջ����ַ
                 (CPU_STK_SIZE) LED1_STK_SIZE/10,	                       //�����ջ�����λ
                 (CPU_STK_SIZE) LED1_STK_SIZE,		                       //�����ջ��С
                 (OS_MSG_QTY  ) 0,					                       //�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  ) 0,					                       //��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* ) 0,					                       //�û�����Ĵ洢��
                 (OS_OPT      ) OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* ) &err);				                       //��Ÿú�������ʱ�ķ���ֵ	

    //����Beep����
	OSTaskCreate((OS_TCB 	* ) &Beep_TCB,		                           //������ƿ�
				 (CPU_CHAR	* ) "Beep_Task", 		                       //��������
                 (OS_TASK_PTR ) Beep_Task, 			                       //������
                 (void		* ) 0,					                       //���ݸ��������Ĳ���
                 (OS_PRIO	  ) Beep_TASK_PRIO,                            //�������ȼ�
                 (CPU_STK   * ) &Beep_TASK_STK[0],	                       //�����ջ����ַ
                 (CPU_STK_SIZE) Beep_STK_SIZE/10,	                       //�����ջ�����λ
                 (CPU_STK_SIZE) Beep_STK_SIZE,		                       //�����ջ��С
                 (OS_MSG_QTY  ) 0,					                       //�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  ) 0,					                       //��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* ) 0,					                       //�û�����Ĵ洢��
                 (OS_OPT      ) OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* ) &err);				                       //��Ÿú�������ʱ�ķ���ֵ	
                 
	OS_CRITICAL_EXIT();	//�˳��ٽ���
    
    OSTaskDel((OS_TCB 	* ) 0,
              (OS_ERR 	* ) &err); // ɾ����ʼ����
}

//LED0������
void LED0_Task(void *p_arg){
    
	OS_ERR err;
	p_arg = p_arg;
    
	while(1){
        
		LED0 = ~LED0; // LED0��ת
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ200ms
	}
}

//LED1������
void LED1_Task(void *p_arg){
    
	OS_ERR err;
	p_arg = p_arg;
    
	while(1){
        
		LED1 = ~LED1; // LED1��ת
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ200ms
	}
}

//Beep������
void Beep_Task(void *p_arg){
    
	OS_ERR err;
	p_arg = p_arg;
    
	while(1){
        
		Beep = 1; // Beep��
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ200ms
        Beep = 0; // Beep����
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ1s
	}
}
