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
#define taskENTER_CRITICAL()        portENTER_CRITICAL()
#define taskEXIT_CRITICAL()            portEXIT_CRITICAL()
#define taskENTER_CRITICAL_FROM_ISR() portSET_INTERRUPTS_MASK_FROM_ISR()
#define taskEXIT_CRITICAL_FROM_ISR(x)  portCLEAR_INTERRUPTS_MASK_FROM_ISR(x)


void prvInitialiseTaskLists(void);
void vTaskStartScheduler(void);

#endif
	