/*********************************************************************** 
*    Copyright(C)          ��̨���ܵ��ӿƼ����޹�˾ 
*               Yan Tai Chinon Electronic Technology Co.,Ltd 
*   �ļ�����  main.h
*   ��  �ߣ�  ̷ҵ��
*   ��  ����  Ver1.0
*   ��  �ڣ�  20130516
*   ��  ����  
*   ��  ʷ��  ��
*************************************************************************/ 
#ifndef MAIN__H__
#define MAIN__H__

typedef struct{
	uint8 HostOrSeleve;
	uint8 run;
	uint8 reset;
}run_param_t;

typedef struct{
	uint8 dev_err_times[30];
}zigbee_dev_online_t;
void delay(uint32 us);

#endif

