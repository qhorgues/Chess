#ifndef LIST_MOVE_H
#define LIST_MOVE_H

#include <stdint.h>

typedef struct Member_list_move *ptrListMove;
struct Member_list_move
{
	ptrListMove next;
	unsigned char coor;
};

typedef struct ListMove ListMove;
struct ListMove
{
	int (*const pushBack)(ListMove *const, unsigned char const coor);
	void (*const clear)(ListMove *const);
	
	ptrListMove listMove;
	unsigned char const dpt;
	unsigned char size;
};

extern ListMove initListMove(unsigned char const dpt);

#endif