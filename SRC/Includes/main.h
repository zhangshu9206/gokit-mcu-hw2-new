/*********************************************************************** 
*    Copyright(C)          烟台启能电子科技有限公司 
*               Yan Tai Chinon Electronic Technology Co.,Ltd 
*   文件名：  main.h
*   作  者：  谭业超
*   版  本：  Ver1.0
*   日  期：  20130516
*   描  述：  
*   历  史：  无
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

