#ifndef LIST_MOVE_H
#define LIST_MOVE_H

#include <stdint.h>

typedef struct Member_list_move *ptr_list_move;
struct Member_list_move
{
	ptr_list_move next;
	uint8_t coor;
};

typedef struct List_move List_move;
struct List_move
{
	int (*const push_back)(List_move *const, uint8_t const coor);
	void (*const clear)(List_move *const);
	
	ptr_list_move list_move;
	uint8_t const dpt;
	size_t size;
};

extern List_move init_list_move(uint8_t const dpt);

#endif