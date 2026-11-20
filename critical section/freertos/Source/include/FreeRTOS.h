#ifndef __FREERTOS_H
#define __FREERTOS_H
#include "portmacro.h"
#include "list.h"
#include "projdefs.h"

typedef struct tskTaskControlBlock
{
    volatile StackType_t * pxTopOfStack;
    ListItem_t xStateListItem;
    StackType_t * pxStack;
    char pcTaskName[configMAX_TASK_NAME_LEN];
}tskTCB;
typedef tskTCB TCB_t;



#endif /* __FREERTOS_H__ */
