#include "list.h"
#include "FreeRTOS.h"
#include "portable.h"
#include "task.h"

TaskHandle_t HandleTask1;
TaskHandle_t HandleTask2;

TCB_t Task1TCB;
TCB_t Task2TCB;

uint32_t flag1, flag2;

#define TASK1_STACK_SIZE 20
#define TASK2_STACK_SIZE 20

StackType_t Task1StackBuff[TASK1_STACK_SIZE];
StackType_t Task2StackBuff[TASK2_STACK_SIZE];


void Delay(uint32_t time);
void task1Code(void *arg);
void task2Code(void *arg);


int main(void)
{	
    prvInitialiseTaskLists();
    HandleTask1 = xTaskCreateStatic(task1Code, "task1", TASK1_STACK_SIZE, NULL, Task1StackBuff, &Task1TCB);
    vListInsertEnd(&pxReadyTasksLists[1], &Task1TCB.xStateListItem);
    HandleTask2 = xTaskCreateStatic(task2Code, "task2", TASK2_STACK_SIZE, NULL, Task2StackBuff, &Task2TCB);
    vListInsertEnd(&pxReadyTasksLists[2], &Task2TCB.xStateListItem);
	vTaskStartScheduler();
	while(1)
    {

    }
}

void task1Code(void *arg)
{
    while(1)
    {
        flag1 = 1;
        Delay(1000);
        flag1 = 0;
        Delay(1000);
        taskYIELD();
    }
}

void task2Code(void *arg)
{
    while(1)
    {
        flag2 = 1;
        Delay(1000);
        flag2 = 0;
        Delay(1000);
        taskYIELD();
    }
}

void Delay(uint32_t time)
{
    for(;time != 0; time--)
    {
        
    }

}
