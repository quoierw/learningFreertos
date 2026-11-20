#include "../../../include/portable.h"


#define portINITIAL_XPSR			        ( 0x01000000 )
#define portSTART_ADDRESS_MASK				( ( StackType_t ) 0xfffffffeUL )
#define portNVIC_SYSPRI2_REG				( * ( ( volatile uint32_t * ) 0xe000ed20 ) )
#define portNVIC_PENDSV_PRI					( ( ( uint32_t ) configKERNEL_INTERRUPT_PRIORITY ) << 16UL )
#define portNVIC_SYSTICK_PRI				( ( ( uint32_t ) configKERNEL_INTERRUPT_PRIORITY ) << 24UL )
static UBaseType_t uxCriticalNesting = 0xAAAAAAAA;

void prvStartFirstTask(void);

BaseType_t xPortStartScheduler(void)
{
    portNVIC_SYSPRI2_REG |= portNVIC_PENDSV_PRI;
    portNVIC_SYSPRI2_REG |= portNVIC_SYSTICK_PRI;
    
    prvStartFirstTask();
    return 0;
}


static void prvTaskExitError(void * pvParameters)
{
    for(;;)
    {

    }
}


StackType_t * pxPortInitialiseStack(
    StackType_t * pxTopOfStack, 
    TaskFunction_t pxTaskCode, 
    void * pvParameters)
{
    pxTopOfStack--;
    *pxTopOfStack = portINITIAL_XPSR;
    pxTopOfStack--;
    *pxTopOfStack = (StackType_t)pxTaskCode & portSTART_ADDRESS_MASK;
    pxTopOfStack--;
    *pxTopOfStack = (StackType_t)prvTaskExitError;
    pxTopOfStack -= 5;
    *pxTopOfStack = (StackType_t)pvParameters;
    pxTopOfStack -= 8;

    return pxTopOfStack;
}

__asm void prvStartFirstTask(void)
{
    PRESERVE8

    ldr r0,=0xE000ED08
    ldr r0, [r0]
    ldr r0, [r0]

    msr msp, r0

    cpsie i
    cpsie f
    

    dsb
    isb

    svc 0

    nop
    nop
}

__asm void vPortSVCHandler(void)
{
    extern pxCurrentTCB;
    PRESERVE8

    ldr r3,=pxCurrentTCB
    ldr r1,[r3]
    ldr r0,[r1]
    ldmia r0!, {r4-r11}
    msr psp, r0
    isb 
    mov r0, #0
    msr basepri, r0
    orr r14, #0xd
    bx r14
}

__asm void xPortPendSVHandler(void)
{
    extern pxCurrentTCB;
    extern vTaskSwitchText;
    PRESERVE8

    mrs r0, psp
    isb 

    ldr r3,=pxCurrentTCB
    ldr r2,[r3]
    stmdb r0!, {r4-r11}
    str r0,[r2]

    stmdb sp!,{r3,r14}
    
    mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
    msr basepri, r0
    dsb 
    isb 
    bl vTaskSwitchText
    mov r0, #0
    msr basepri, r0

    ldmia sp!, {r3,r14}

    ldr r1, [r3]
    ldr r0, [r1]
    ldmia r0!, {r4-r11}
    msr psp, r0

    isb 
    bx r14
    nop
}

void vPortEnterCritical(void)
{
    portDISABLE_INTERRUPTS();
    uxCriticalNesting++;
    if(uxCriticalNesting == 1)
    {
        // configASSERT((portNVIC_INT_CTRL_REG & portVECTACTIVE_MASK) == 0);
    }
}

void vPortExitCritical(void)
{
    // configASSERT(uxCriticalNesting);
    uxCriticalNesting--;
    if (uxCriticalNesting == 0)
    {
        portENABLE_INTERRUPTS();
    }
}