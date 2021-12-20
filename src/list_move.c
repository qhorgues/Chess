#include <malloc.h>
#include <assert.h>
#include "list_move.h"

int push_list_move(List_move *const list, struct Coor coor)
{
	ptr_list_move new = malloc(sizeof(struct Coor));
	if (new == NULL)
	{
		return -1;
	}
	new->coor = coor;
	new->next = NULL;
	list->size++;
	if (list->list_move == NULL)
	{
		list->list_move = new;
		return 0;
	}
	ptr_list_move member = list->list_move;
	while (member->next != NULL)
	{
		member = member->next;
	}
	member->next = new;
	return 0;
}

void delete_list_move(List_move *const list)
{
	ptr_list_move next = list->list_move;
	while (next != NULL) 
	{
		ptr_list_move member = next;
		next = next->next;
		free(member);
	}
	list->list_move = NULL;
	list->size = 0;
}	

