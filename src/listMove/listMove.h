#ifndef LIST_MOVE_H
#define LIST_MOVE_H

#include <stdint.h>

typedef struct Member_list_move *ptrListMove;
struct Member_list_move
{
	ptrListMove next;
	int coor;
};

typedef struct ListMove ListMove;
struct ListMove
{	
	ptrListMove listMove;
	int dpt;
	int size;
};

ListMove initListMove(int dpt);
int ListMove_pushBack(ListMove  *list, int coor);
void ListMove_clear(ListMove  *list);
#endif