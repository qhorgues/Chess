#ifndef LIST_MOVE_H
#define LIST_MOVE_H

#include "coor.h"

typedef struct Member_list_move
{
	struct Member_list_move* next;
	struct Coor coor;
} *ptr_list_move;

typedef struct List_move
{
	struct Member_list_move* list_move;
	struct Coor dpt;
	size_t size;
} List_move;

extern int push_list_move(List_move *const list, struct Coor coor);
extern void delete_list_move(List_move *const list);

#endif