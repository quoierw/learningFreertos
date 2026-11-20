#ifndef PORTABLE_H
#define PORTABLE_H

#include "portmacro.h"
#include "FreeRTOS.h"
#include "task.h"
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters );
BaseType_t xPortStartScheduler(void);

#endif /* PORTABLE_H */
