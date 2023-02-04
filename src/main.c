#include <stdio.h>
#include "Board/Board.h"
#include "listMove/listMove.h"


int main(void)
{
	int a;
	struct Board board = initBoard();
    move(&board, offSet( 5, 1), offSet(5, 3));
    move(&board, offSet( 4, 6), offSet(4, 3));
	board.grid[offSet(5, 3)].prise_pass = true;
    printBoard(&board, stdout);
	ListMove list = initListMove(offSet(4, 3));
	getListMove(&board, &list);
	ptrListMove ptr_list = list.listMove;
	while (ptr_list != NULL)
	{
		printf("%d/%d\n", getX(ptr_list->coor), getY(ptr_list->coor));
		ptr_list = ptr_list->next;
	}
	list.clear(&list);

	printf("check 1 : %d\n", check(&board, Black, UNDEFINED_COORDINATES));
	move(&board, offSet( 3, 7), offSet(3, 0));
	printf("check 2 : %d\n", check(&board, Black, UNDEFINED_COORDINATES));
	printBoard(&board, stdout);
    return 0;
}