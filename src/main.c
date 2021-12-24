#include <stdio.h>
#include "Board.h"
#include "list_move.h"


int main(void)
{
	struct Board board = Init_Board();
    move(&board, off_set( 5, 1), off_set(5, 3));
    move(&board, off_set( 4, 6), off_set(4, 3));
	board.grid[off_set(5, 3)].prise_pass = true;
    print_board(&board, stdout);
	List_move list = init_list_move(off_set(4, 3));
	get_list_move(&board, &list);
	ptr_list_move ptr_list = list.list_move;
	while (ptr_list != NULL)
	{
		printf("%d/%d\n", get_x(ptr_list->coor), get_y(ptr_list->coor));
		ptr_list = ptr_list->next;
	}
	list.clear(&list);

    return 0;
}