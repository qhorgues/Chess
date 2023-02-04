#include <stdio.h>
#include "Board/Board.h"
#include "listMove/listMove.h"
#include "log/log.h"


int main(void)
{
    open_log();

	struct Board board = initBoard();
    move(&board, offSet( 5, 1), offSet(5, 3));
    move(&board, offSet( 4, 6), offSet(4, 3));

	board.grid[offSet(5, 3)].prise_pass = true;

    int ret_value = printBoard(&board, stdout);
    test(WARN, ret_value != 0, "Fail on print board");

	ListMove list = ListMove_init(offSet(4, 3));

	ListMove_getMove(&board, &list);
	ptrListMove ptr_list = list.listMove;
	while (ptr_list != NULL)
	{
		printf("%d/%d\n", getX(ptr_list->coor), getY(ptr_list->coor));
		ptr_list = ptr_list->next;
	}
	ListMove_clear(&list);

	printf("check 1 : %d\n", check(&board, Black, UNDEFINED_COORDINATES));
	move(&board, offSet( 3, 7), offSet(3, 0));
	printf("check 2 : %d\n", check(&board, Black, UNDEFINED_COORDINATES));
	printBoard(&board, stdout);

    close_log();
    return 0;
}