#include <stdio.h>
#include "Board.h"

static inline char player_color(const int player)
{
    if (player == 1)
        return 'W';
    else if (player == -1)
        return 'B';
    return ' ';
}

int main(void)
{
    struct Board board = Init_Board();
    for (int i = 0; i < SIZE_BOARD; i++)
    {
        for (int j = 0; j < SIZE_BOARD; j++)
        {
            printf(" %c%c ", player_color(board.grid[j][i].color), board.grid[j][i].type);
        }
        puts("");
    }
    return 0;
}