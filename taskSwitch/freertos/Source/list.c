#if 1
#include "list.h"

void vListInitialiseITEM(ListItem_t * const pxListItem)
{
    pxListItem->pvContainer = NULL;
}

void vListInitialise(List_t * const pxList)
{
    pxList->pxIndex = (ListItem_t *)&(pxList->xListEnd);

    pxList->pxIndex->pxNext = (ListItem_t *)&(pxList->xListEnd);
    pxList->pxIndex->pxPrevious = (ListItem_t *)&(pxList->xListEnd);
    pxList->pxIndex->xItemValue = portMAX_DELAY;
    
    pxList->uxNumberOfItems = 0;
}

void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem)
{
    ListItem_t *const pxIndex = pxList->pxIndex;

    pxNewListItem->pxPrevious = pxIndex->pxPrevious;
    pxNewListItem->pxNext = pxIndex;
    pxNewListItem->pxPrevious->pxNext = pxNewListItem;
    pxNewListItem->pxNext->pxPrevious = pxNewListItem;

    pxNewListItem->pvContainer = pxList;
    (pxList->uxNumberOfItems)++;
}

void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem)
{
    ListItem_t * pxIterator;
    UBaseType_t xnumberOfInsertion = pxNewListItem->xItemValue;

    if(xnumberOfInsertion == portMAX_DELAY)
    {
        pxIterator = pxList->pxIndex->pxPrevious;
    }
    else
    {
        for(pxIterator = (ListItem_t *)&(pxList->xListEnd);
            pxIterator->pxNext->xItemValue <= xnumberOfInsertion;
            pxIterator = pxIterator->pxNext
            )
        {

        }
    }

    pxNewListItem->pxNext = pxIterator->pxNext;
    pxNewListItem->pxPrevious = pxIterator;
    pxNewListItem->pxPrevious->pxNext = pxNewListItem;
    pxNewListItem->pxNext->pxPrevious = pxNewListItem;


    pxNewListItem->pvContainer = pxList;
    (pxList->uxNumberOfItems)++;
}


UBaseType_t uxListRemove(ListItem_t * const pxItemToRemove)
{
    List_t *const pxList = pxItemToRemove->pvContainer;
    if(pxList != NULL)
    {
        pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;
        pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
        pxItemToRemove->pvContainer = NULL;
    }
    if(pxList->pxIndex == pxItemToRemove)
    {
        pxList->pxIndex = pxItemToRemove->pxPrevious;
    }

    (pxList->uxNumberOfItems)--;
    return pxList->uxNumberOfItems;
}

#else

#include "list.h"

void vListInitialiseITEM(ListItem_t * const pxListItem)
{
    pxListItem->pvContainer = NULL;
}

void vListInitialise(List_t * const pxList)
{
    pxList->pxIndex = (ListItem_t * )&(pxList->xListEnd);
    pxList->xListEnd.xItemValue = portMAX_DELAY;
    pxList->xListEnd.pxNext = (ListItem_t * )&(pxList->xListEnd);
    pxList->xListEnd.pxPrevious = (ListItem_t * )&(pxList->xListEnd);
    
    pxList->uxNumberOfItems = (UBaseType_t)0U;
}

void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem)
{
    ListItem_t * pxIndex = pxList->pxIndex;

    pxNewListItem->pxPrevious = pxIndex->pxPrevious;
    pxNewListItem->pxNext = pxIndex;
    pxNewListItem->pxPrevious->pxNext = pxNewListItem;
    pxNewListItem->pxNext->pxPrevious = pxNewListItem;

    pxNewListItem->pvContainer = (void *)pxList;
    (pxList->uxNumberOfItems)++;
}

void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem)
{
    ListItem_t * pxIterator;
    const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;
    if(xValueOfInsertion == portMAX_DELAY)
    {
        pxIterator = pxList->xListEnd.pxPrevious;
    }
    else
    {
        for(pxIterator = (ListItem_t *)&(pxList->xListEnd);  pxIterator->pxNext->xItemValue <= xValueOfInsertion; pxIterator = pxIterator->pxNext);
    }

    pxNewListItem->pxNext = pxIterator->pxNext;
    pxNewListItem->pxPrevious = pxIterator;
    pxNewListItem->pxPrevious->pxNext = pxNewListItem;
    pxNewListItem->pxNext->pxPrevious = pxNewListItem;   

    pxNewListItem->pvContainer = (void *)pxList;
    (pxList->uxNumberOfItems)++;
}

UBaseType_t uxListRemove(ListItem_t * const pxItemToRemove)
{
    List_t * const pxList = pxItemToRemove->pvContainer;

    pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;
    pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;

    if(pxList->pxIndex == pxItemToRemove)
    {
        pxList->pxIndex = pxItemToRemove->pxPrevious;
    }


    pxItemToRemove->pvContainer = NULL;
    (pxList->uxNumberOfItems)--;

    return pxList->uxNumberOfItems;
}




#endif



