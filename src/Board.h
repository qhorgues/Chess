#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#define SIZE_BOARD 8

enum Type_piece
{
    None = 32,
    Pawn = 80,
    Bishop = 66,
    Knight = 78,
    Rook = 82,
    Queen = 81,
    King = 75
};

enum Value_piece 
{
    Val_None = 0,
    Val_Pawn = 1,
    Val_Bishop = 3,
    Val_Knight = 3,
    Val_Rook = 5,
    Val_Queen = 9,
    Val_King = 255
};

struct Piece
{
    enum Type_piece type;
    enum Value_piece value;
    int8_t color;
    _Bool prise_pass;
    _Bool moved;

};

struct Board
{
    struct Piece grid[SIZE_BOARD][SIZE_BOARD];
    const uint8_t mailbox_64[64];
    const int8_t mailbox_120[120];
    struct Piece eliminate_white[15];
    struct Piece eliminate_black[15];
    size_t nb_white_eliminate;
    size_t nb_black_eliminate;

};

extern void reset_grid(struct Piece (*restrict grid)[SIZE_BOARD]);
extern struct Board Init_Board(void);
extern void move(struct Board *restrict board, const int x_dpt, const int y_dpt, const int x_arv, const int y_arv);
int print_board(const struct Board *restrict board, FILE *restrict out);

#endif