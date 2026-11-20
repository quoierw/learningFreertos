/* 在中断场合，临界段可以嵌套    */
{
    uint32_t ulReturn;
    /* 进入临界段，临界段可以嵌套    */
    ulReturn = taskENTER_CRITICAL_FROM_ISR();

    /* 临界段代码    */

    /* 退出临界段    */
     taskEXIT_CRITICAL_FROM_ISR( ulReturn ); 
}
/* 在非中断场合，临界段不能嵌套 */
{
    /* 进入临界段    */
    taskENTER_CRITICAL();

    /* 临界段代码    */

    /* 退出临界段*/
    taskEXIT_CRITICAL();
}