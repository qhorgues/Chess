#ifndef LIST_MOVE_H
#define LIST_MOVE_H

#include "coor.h"

typedef struct Member_list_move *ptr_list_move;
struct Member_list_move
{
	ptr_list_move next;
	struct Coor coor;
};

typedef struct List_move List_move;
struct List_move
{
	int (*const push_back)(List_move *const, struct Coor coor);
	void (*const clear)(List_move *const);
	
	ptr_list_move list_move;
	struct Coor const dpt;
	size_t size;
};

extern List_move init_list_move(struct Coor const dpt);

#endif