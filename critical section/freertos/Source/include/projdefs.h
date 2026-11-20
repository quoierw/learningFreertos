#ifndef __PROJDEFS_H
#define __PROJDEFS_H

#include "portmacro.h"
typedef void(* TaskFunction_t)(void *argument);

#define pdFALSE ((BaseType_t)0)
#define pdTRUE ((BaseType_t)1)

#define pdFAIL (pdFALSE)
#define pdPASS (pdTRUE)

#endif
