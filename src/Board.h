#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#define SIZE_BOARD 8

enum type_piece
{
    None,
    Pawn,
    Bishop,
    Knight,
    Rook,
    Queen,
    King
};

enum value_piece 
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
    enum type_piece type;
    enum value_piece value;
    int8_t color;
    _Bool prise_pass;
    _Bool moved;

};

struct Board
{
    struct Piece grid[SIZE_BOARD][SIZE_BOARD];
    const uint8_t mailbox_64[64];
    const int8_t mailbox_120[120];
};

extern void reset_grid(struct Piece (*restrict grid)[SIZE_BOARD]);
struct Board Init_Board(void);

#endif