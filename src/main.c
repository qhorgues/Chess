#include <stdio.h>
#include "Board.h"



int main(void)
{
    struct Board board = Init_Board();
    print_board(&board, stdout);

    move(&board, 3, 7, 4, 0);
    return 0;
}