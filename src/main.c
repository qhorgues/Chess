#include <stdio.h>
#include "Board.h"



int main(void)
{
    struct Board board = Init_Board();
    move(&board, 3, 7, 4, 0);
    print_board(&board, stdout);
    return 0;
}