#ifndef __TASK_H
#define __TASK_H

#include "FreeRTOS.h"
extern List_t pxReadyTasksLists[configMAX_PRIORITIES];
extern TCB_t * volatile pxCurrentTCB;
void vTaskSwitchText(void);

typedef void * TaskHandle_t;

TaskHandle_t xTaskCreateStatic(
    TaskFunction_t pxTaskCode,
    const char * const pcTaskName,
    const uint32_t ulStackDepth,
    void * const pvParameters,
    StackType_t * const puxStackbuffer,
    TCB_t * const pxTaskBuffer
);

#define taskYIELD() portYIELD()



void prvInitialiseTaskLists(void);
void vTaskStartScheduler(void);

#endif
	