// #include <stdio.h>
#include "Board.h"

#define MAILBOX_64                          \
    {                                       \
        21, 22, 23, 24, 25, 26, 27, 28,     \
            31, 32, 33, 34, 35, 36, 37, 38, \
            41, 42, 43, 44, 45, 46, 47, 48, \
            51, 52, 53, 54, 55, 56, 57, 58, \
            61, 62, 63, 64, 65, 66, 67, 68, \
            71, 72, 73, 74, 75, 76, 77, 78, \
            81, 82, 83, 84, 85, 86, 87, 88, \
            91, 92, 93, 94, 95, 96, 97, 98  \
    }

#define MAILBOX_120                                 \
    {                                               \
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,     \
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, \
            -1, 0, 1, 2, 3, 4, 5, 6, 7, -1,         \
            -1, 8, 9, 10, 11, 12, 13, 14, 15, -1,   \
            -1, 16, 17, 18, 19, 20, 21, 22, 23, -1, \
            -1, 24, 25, 26, 27, 28, 29, 30, 31, -1, \
            -1, 32, 33, 34, 35, 36, 37, 38, 39, -1, \
            -1, 40, 41, 42, 43, 44, 45, 46, 47, -1, \
            -1, 48, 49, 50, 51, 52, 53, 54, 55, -1, \
            -1, 56, 57, 58, 59, 60, 61, 62, 63, -1, \
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, \
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1  \
    }


/**
 * @brief Construit toutes les pieces d'un type sur la grille
 * 
 * @param[out] grid Le plateau ou positionner les pieces
 * @param[in] type Le type de la piece
 * @param[in] value La valeur de la piece
 * @param[in] min_i Le depart du positionement en X
 * @param[in] max_i La fin du positionement en X
 * @param[in] increase_i L'ecart de positionement entre les pieces en X
 * @param[in] min_j Le depart du positionement en Y
 * @param[in] max_j La fin du positionement en Y
 * @param[in] increase_j L'ecart de positionement entre les pieces en Y
 */
static inline void pos_piece(struct Piece (*restrict grid)[SIZE_BOARD], const enum type_piece type, const enum value_piece value, const int min_i, const int max_i, const int increase_i, const int min_j, const int max_j, const int increase_j)
{
    for (int i = min_i; i < max_i; i+=increase_i)
    {
        for (int j = min_j; j < max_j; j+=increase_j)
        {
            grid[i][j].type = type;
            grid[i][j].value = value;
            if (j <= 1)
                grid[i][j].color = -1;
            else
                grid[i][j].color = 1;
            grid[i][j].prise_pass = 0;
            grid[i][j].moved = 0;
        }
    }
}

/**
 * @brief renvoi la grille de depart au echec
 * @param[out] grid Le plateau a (re)initialiser
 * 
 */
void reset_grid(struct Piece (*restrict grid)[SIZE_BOARD])
{
    pos_piece(grid, None, Val_None, 0, 8, 1, 2, 6, 1);
    pos_piece(grid, Pawn, Val_Pawn, 0, 8, 1, 1, 7, 5);
    pos_piece(grid, Rook, Val_Rook, 0, 8, 7, 0, 8, 7);
    pos_piece(grid, Knight, Val_Knight, 1, 7, 5, 0, 8, 7);
    pos_piece(grid, Bishop, Val_Bishop, 2, 6, 3, 0, 8, 7);
    pos_piece(grid, Queen, Val_Queen, 3, 4, 1, 0, 8, 7);
    pos_piece(grid, King, Val_King, 4, 5, 1, 0, 8, 7);
}

/**
 * @brief Initailise la structure board
 * 
 * @return struct Board 
 */
struct Board Init_Board(void)
{
    struct Board board = {.mailbox_64=MAILBOX_64, .mailbox_120= MAILBOX_120};
    reset_grid(board.grid);
    return board;
}