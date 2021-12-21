#include <stdio.h>
#include "Board.h"
#include "list_move.h"


int main(void)
{
	struct Board board = Init_Board();
    move(&board, COOR( 0, 7), COOR(3, 4));
    print_board(&board, stdout);
	
	/* struct List_move list = init_list_move(COOR(0, 0));
	list.push_back(&list, COOR(2, 3));
	list.push_back(&list, COOR(3, 4));
	list.push_back(&list, COOR(7, 3));
	list.push_back(&list, COOR(2, 4));
	*/
	List_move list = init_list_move(COOR(3, 4));
	get_list_move(&board, &list);
	ptr_list_move ptr_list = list.list_move;
	while (ptr_list != NULL)
	{
		printf("%d/%d\n", ptr_list->coor.x, ptr_list->coor.y);
		ptr_list = ptr_list->next;
	}
	list.clear(&list);
    return 0;
}