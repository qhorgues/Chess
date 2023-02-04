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
	int ( *pushBack)(ListMove *, int coor);
	void ( *clear)(ListMove *);
	
	ptrListMove listMove;
	int dpt;
	int size;
};

extern ListMove initListMove(int dpt);

#endif