#ifndef LIST_MOVE_H
#define LIST_MOVE_H

#include <stdint.h>

typedef struct Member_list_move *ptrListMove;
struct Member_list_move
{
	ptrListMove next;
	uint8_t coor;
};

typedef struct ListMove ListMove;
struct ListMove
{
	int (*const pushBack)(ListMove *const, uint8_t const coor);
	void (*const clear)(ListMove *const);
	
	ptrListMove listMove;
	uint8_t const dpt;
	uint8_t size;
};

extern ListMove initListMove(uint8_t const dpt);

#endif