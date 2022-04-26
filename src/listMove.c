#include <malloc.h>
#include <assert.h>
#include <stdint.h>
#include "except.h"
#include "listMove.h"

static int pushBack(ListMove *const list, uint8_t const coor)
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

static void clear(ListMove *const list)
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

ListMove initListMove(uint8_t const dpt)
{
	return (ListMove){&pushBack, &clear, NULL, dpt, 0};
}