#include <stdio.h>
#include "Board.h"
#include "list_move.h"


int main(void)
{
	/* struct Board board = Init_Board();
    move(&board, 3, 7, 4, 0);
    print_board(&board, stdout); */
	
	struct List_move list = {NULL, (struct Coor){0 ,0}, 0};
	push_list_move(&list, (struct Coor){2, 3});
	push_list_move(&list, (struct Coor){3, 4});
	
	ptr_list_move ptr_list = list.list_move;
	while (ptr_list != NULL)
	{
		printf("%d/%d\n", ptr_list->coor.x, ptr_list->coor.y);
		ptr_list = ptr_list->next;
	}
	delete_list_move(&list);
    return 0;
}