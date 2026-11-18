



#ifndef __LIST_H
#define __LIST_H
#include "portmacro.h"

struct xLIST_ITEM{
    TickType_t xItemValue;
    struct xLIST_ITEM* pxNext;
    struct xLIST_ITEM* pxPrevious;
    void * pvContainer;
    void * pvOwner;
};
typedef struct xLIST_ITEM  ListItem_t;


struct xMINI_LIST_ITEM{
    TickType_t xItemValue;
    struct xLIST_ITEM* pxNext;
    struct xLIST_ITEM* pxPrevious;
};
typedef struct xMINI_LIST_ITEM  MiniListItem_t;

struct xLIST{
    UBaseType_t uxNumberOfItems;
    ListItem_t * pxIndex;
    MiniListItem_t xListEnd;
};
typedef struct xLIST  List_t;



#define listSET_LIST_ITEM_OWNER(pxListItem,pxOwner)     ((pxListItem)->pvOwner = pxOwner)
#define listGET_LIST_ITEM_OWNER(pxListItem)             ((pxListItem)->pvOwner)

#define listSET_LIST_ITEM_VALUE(pxListItem,xVaule)     ((pxListItem)->xItemValue = xVaule)
#define listGET_LIST_ITEM_VALUE(pxListItem)             ((pxListItem)->xItemValue)

#define listGET_ITEM_VALUE_OF_HEAD_ENTRY(pxList)        (((pxList)->xListEnd).pxNext->xItemValue)

#define listGET_HEAD_ENTRY(pxList)                      (((pxList)->xListEnd).pxNext)
#define listGET_END_MARKER(pxList)                      ((ListItem_t *)(&((pxList)->xListEnd)))

#define listGET_NEXT(pxListItem)                        ((pxListItem)->pxNext)

#define listLIST_IS_EMPTY(pxList)                   ((BaseType_t)(((pxList)->uxNumberOfItems) == (UBaseType_t)0))

#define listCURRENT_LIST_LENGTH(pxList)             ((pxList)->uxNumberOfItems)

#define listGET_OWNER_OF_HEAD_ENTRY(pxList)         ((&((pxList)->xListEnd))->pxNext->pvOwner)

#define listGET_OWNER_OF_NEXT_ENTRY(pxTCB, pxList)\
{\
    List_t *const pxConstList = (pxList);\
    (pxConstList)->pxIndex = (pxConstList)->pxIndex->pxNext;\
    if((void * )(pxConstList)->pxIndex == (void * )&((pxConstList)->xListEnd))\
    {\
        (pxConstList)->pxIndex = (pxConstList)->pxIndex->pxNext;\
    }\
    (pxTCB) = (pxConstList)->pxIndex->pvOwner;\
}

void vListInitialiseITEM(ListItem_t * const pxListItem);
void vListInitialise(List_t * const pxList);
void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem);
void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem);
UBaseType_t uxListRemove(ListItem_t * const pxItemToRemove);

#endif
