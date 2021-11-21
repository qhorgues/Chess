#include <stdio.h>
#include <assert.h>
#include "Board.h"
#include "except.h"

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

#define OFF_SET(x, y) (y*SIZE_BOARD+x)

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
static inline void pos_piece(struct Piece (*restrict grid)[SIZE_BOARD], const enum Type_piece type, const enum Value_piece value, const int min_i, const int max_i, const int increase_i, const int min_j, const int max_j, const int increase_j)
{
    for (int i = min_i; i < max_i; i+=increase_i)
    {
        for (int j = min_j; j < max_j; j+=increase_j)
        {
            grid[j][i].type = type;
            grid[j][i].value = value;
            if (j <= 1)
                grid[j][i].color = -1;
            else if (j >= 6)
                grid[j][i].color = 1;
            else
                grid[j][i].color = 0;
            grid[j][i].prise_pass = 0;
            grid[j][i].moved = 0;
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
 * @return La structure board initialise
 */
struct Board Init_Board(void)
{
    struct Board board = {.mailbox_64=MAILBOX_64, .mailbox_120= MAILBOX_120, .nb_white_eliminate = 0, .nb_black_eliminate = 0};
    reset_grid(board.grid);
    return board;
}

void move(struct Board *restrict board, const int x_dpt, const int y_dpt, const int x_arv, const int y_arv)
{
    assert(x_dpt >= 0 && x_dpt < SIZE_BOARD && "Starting x-coordinate outside the grid");
    assert(y_dpt >= 0 && y_dpt < SIZE_BOARD && "Starting y-coordinate outside the grid");
    assert(x_arv >= 0 && x_arv < SIZE_BOARD && "Ending x-coordinate outside the grid");
    assert(y_arv >= 0 && y_arv < SIZE_BOARD && "Ending y-coordinate outside the grid");
    assert(board != NULL && "The board structure cannot be NULL");
    
    if (board->grid[y_arv][x_arv].color == 1)
    {
        board->eliminate_white[board->nb_white_eliminate] = board->grid[y_arv][x_arv];
        board->nb_white_eliminate++;
    }
    else if (board->grid[y_arv][x_arv].color == -1)
    {
        board->eliminate_black[board->nb_black_eliminate] = board->grid[y_arv][x_arv];
        board->nb_black_eliminate++;
    }
    board->grid[y_arv][x_arv] = board->grid[y_dpt][x_dpt];
    board->grid[y_dpt][x_dpt] = (struct Piece){.color = 0, .type = None, .value = Val_None, .prise_pass = 0, .moved = 0};
}

static inline char player_color(const int player)
{
    if (player == 1)
        return 'W';
    else if (player == -1)
        return 'B';
    return ' ';
}

/**
 * @brief 
 * 
 * @param board La structure board du plateau du jeu
 * @param out La sortie ou ecrire le plateau
 * @return int retoure en cas d'erreur -1 sinon 0
 * 
 * @exception fprintf
 */
int print_board(const struct Board *restrict board, FILE *restrict out)
{
    for (int i = 0; i < SIZE_BOARD; i++)
    {
        for (int j = 0; j < SIZE_BOARD; j++)
        {
            fprintf( out, " %c%c ", player_color(board->grid[i][j].color), board->grid[i][j].type);
            return_except(-1);
        }
        fputc('\n', out);
    }
}