#include "list.h"

List_t list_test;
ListItem_t list_item1;
ListItem_t list_item2;
ListItem_t list_item3;

int main(void)
{	
  vListInitialise(&list_test);
	
	
  vListInitialiseITEM(&list_item1);
  list_item1.xItemValue = 1;
  vListInsert(&list_test,&list_item1);

  vListInitialiseITEM(&list_item2);
  list_item2.xItemValue = 2;
  vListInsert(&list_test,&list_item2);

  vListInitialiseITEM(&list_item3);
  list_item3.xItemValue = 3;
  vListInsert(&list_test,&list_item3);
	
	for(;;)
	{
		
	}
}
