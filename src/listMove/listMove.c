#include <malloc.h>
#include <assert.h>
#include <stdint.h>
#include "../include/except.h"
#include "listMove.h"

int ListMove_pushBack(ListMove  *list, int coor)
{
	assert(list != NULL && "list cannot be NULL");
	
	ptrListMove new = malloc(sizeof *new);
	returnExcept(-1);
	new->coor = coor;
	new->next = NULL;
	list->size++;
	if (list->listMove == NULL)
	{
		list->listMove = new;
		return 0;
	}
	ptrListMove member = list->listMove;
	while (member->next != NULL)
	{
		member = member->next;
	}
	member->next = new;
	return 0;
}

void ListMove_clear(ListMove  *list)
{
	ptrListMove next = list->listMove;
	while (next != NULL) 
	{
		ptrListMove member = next;
		next = next->next;
		free(member);
	}
	list->listMove = NULL;
	list->size = 0;
}

ListMove initListMove(int dpt)
{
	return (ListMove){NULL, dpt, 0};
}