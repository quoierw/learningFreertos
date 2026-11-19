#include "task.h"
#include "portable.h"
extern TCB_t Task1TCB;
extern TCB_t Task2TCB;
List_t pxReadyTasksLists[configMAX_PRIORITIES];
TCB_t * volatile pxCurrentTCB = NULL;

void vTaskStartScheduler(void)
{
    pxCurrentTCB = &Task1TCB;
    if(xPortStartScheduler() != pdFALSE)
    {

    }
}



void prvInitialiseTaskLists(void)
{
    UBaseType_t x;
    for(x = 0; x < configMAX_PRIORITIES; x++)
    {
        vListInitialise(&pxReadyTasksLists[x]);
    }
}

static void prvInitialiseNewTask(
    TaskFunction_t pxTaskCode,
    const char * const pcTaskName,
    const uint32_t ulStackDepth,
    void * const pvParameters,
    TaskHandle_t* const xReturn,
    TCB_t * pxNewTCB
)
{
    UBaseType_t x = 0;
    StackType_t * pxTopOfStack;
    pxTopOfStack = pxNewTCB->pxStack + (ulStackDepth  - 1);
    pxTopOfStack = (StackType_t * )(((uint32_t)pxTopOfStack) & (~0x07));

    for(x = 0; x < configMAX_TASK_NAME_LEN; x++)
    {
        pxNewTCB->pcTaskName[x] = pcTaskName[x];
        if(pcTaskName[x] == 0)
            break;
    }
    pxNewTCB->pcTaskName[configMAX_TASK_NAME_LEN - 1] = '\0';
    vListInitialiseITEM(&pxNewTCB->xStateListItem);
    listSET_LIST_ITEM_OWNER(&pxNewTCB->xStateListItem, pxNewTCB);
    
    pxNewTCB->pxTopOfStack = pxPortInitialiseStack(pxTopOfStack, pxTaskCode, pvParameters);



    if((void *)xReturn != NULL)
    {
        *xReturn = pxNewTCB;
    }

}


#if (configSUPPORT_STATIC_ALLOCATION == 1)

TaskHandle_t xTaskCreateStatic(
    TaskFunction_t pxTaskCode,
    const char * const pcTaskName,
    const uint32_t ulStackDepth,
    void * const pvParameters,
    StackType_t * const puxStackbuffer,
    TCB_t * const pxTaskBuffer
)
{
    TCB_t * pxNewTCB;
    TaskHandle_t xReturn;
    if((pxTaskBuffer != NULL) && (puxStackbuffer != NULL))
    {
        pxNewTCB = pxTaskBuffer;
        pxNewTCB->pxStack = puxStackbuffer;
        prvInitialiseNewTask(
            pxTaskCode,
            pcTaskName,
            ulStackDepth,
            pvParameters,
            &xReturn, 
            pxNewTCB
        );

    }
    else
    {
        xReturn = NULL;
    }
    return xReturn;
}
#endif 


void vTaskSwitchText(void)
{
    if(pxCurrentTCB == &Task1TCB)
    {
        pxCurrentTCB = &Task2TCB;
    }
    else
    {
        pxCurrentTCB = &Task1TCB;
    }
}
