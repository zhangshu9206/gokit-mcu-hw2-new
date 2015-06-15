#ifndef SYS_DELAY__H__
#define SYS_DELAY__H__

#include "hw_lib.h"
typedef struct _sys_delay_t
{
	void (* init)(void);
	void (* tick)(uint32 tick);
	void (* usecond)(uint32 us);
	void (* msecond)(uint16 ms);
	void (* second)(uint16 s);	
}system_delay_t;

extern system_delay_t system_delay;

#endif 
