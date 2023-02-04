#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "../listMove/listMove.h"

#define SIZE_BOARD 64
#define WIDTH_BOARD 8
#define UNDEFINED_COORDINATES 64

/**
 * @enum PlayerColor
 * @brief Représente la couleur d'un joueur -1 pour Black et 1 pour White
 * 
 */
enum PlayerColor
{
    Black = -1,
    NoColor = 0,
    White = 1
};

/**
 * @enum TypePiece
 * @brief Stocke le code ASCII de la lettre de la piece associé
 */
enum TypePiece
{
    None = 32,
    Pawn = 80,
    Bishop = 66,
    Knight = 78,
    Rook = 82,
    Queen = 81,
    King = 75
};

/**
 * @enum ValuePiece
 * @brief Enumeration de la valeur numerique de chaque piece
 */
enum ValuePiece 
{
    Val_None = 0,
    Val_Pawn = 1,
    Val_Bishop = 3,
    Val_Knight = 3,
    Val_Rook = 5,
    Val_Queen = 9,
    Val_King = 255
};

/**
 * @struct Piece
 * @brief Les informations d'une piece
 * @details  La structure d'une piece contenant son type, sa valeur,
 * sa couleur (1 <Blanc>, -1 <Noir>) un booléen pour determiner si
 * le pion peut etre pris en prise en passant pour les autres pieces le booléen est inutilisé 
 * et un booléen pour determiner si une piece a deja
 * bouge, pour le roque ou le double mouvement du pion notamment.
 */
struct Piece
{
    enum TypePiece type;
    enum ValuePiece value;
    enum PlayerColor color;
    bool prise_pass;
    bool moved;
};

/**
 * @struct Board
 * @brief La structure contenant le plateau, les mailboxs et le tableau des elimines
 * @details Contient la grille du jeu, la mailbox 120 permettant de gerer les debordements de plateau
 * lors des mouvements et la mailbox 64 permettant de localiser la case de depart d'un mouvement sur
 * la mailbox 120, le tableau des pieces blanches et noirs eliminées et enfin le nombre de piece eliminée respectivement
 * 
 */
struct Board
{
    /**
     * @brief La grille principale du jeu
    */
    struct Piece grid[SIZE_BOARD];
    
    /**
     * @brief La mailbox 64 permettant de localiser la case de depart d'un mouvement sur la mailbox 120
     * @code
     * 21, 22, 23, 24, 25, 26, 27, 28,
     * 31, 32, 33, 34, 35, 36, 37, 38,
     * 41, 42, 43, 44, 45, 46, 47, 48,
     * 51, 52, 53, 54, 55, 56, 57, 58,
     * 61, 62, 63, 64, 65, 66, 67, 68,
     * 71, 72, 73, 74, 75, 76, 77, 78,
     * 81, 82, 83, 84, 85, 86, 87, 88,
     * 91, 92, 93, 94, 95, 96, 97, 98 
     * @endcode
     */
    uint8_t const mailbox_64[64];

    /**
     * 
     * @brief La mailbox 120 permet de gerer les debordements de plateau lors des mouvements
     * @code
     * -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     * -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     * -1,  0,  1,  2,  3,  4,  5,  6,  7, -1,        
     * -1,  8,  9, 10, 11, 12, 13, 14, 15, -1,  
     * -1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
     * -1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
     * -1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
     * -1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
     * -1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
     * -1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
     * -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     * -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
     * @endcode
     */
    int8_t const mailbox_120[120];
    
    /**
     * @brief Le tableau de toutes les pieces blanches eliminées 
     */
    struct Piece eliminate_white[15];
    
    /**
     * @brief Le tableau de toutes les pieces noirs eliminées 
     */
    struct Piece eliminate_black[15];

    /**
     * @brief Le nombre de piece blanche eliminées permettant de toujours indexer a des valeurs initialisées 
     */
    uint8_t nb_white_eliminate;

    /**
     * @brief Le nombre de piece noir eliminées permettant de toujours indexer a des valeurs initialisées 
     */
    uint8_t nb_black_eliminate;

};

extern void resetGrid(struct Piece *const restrict grid);
extern struct Board initBoard(void);
extern void move(struct Board *const restrict board, uint8_t const dpt, uint8_t const arv);
extern int printBoard(struct Board const *const restrict board, FILE *restrict out);
extern void getListMove(struct Board const *const restrict board, ListMove *const restrict list);
extern bool check(struct Board *const restrict board, enum PlayerColor color, uint8_t coorKing);


#if defined(_DEBUG)
	extern int offSet(uint8_t const x, uint8_t const y);
	extern int getX(uint8_t const coor);
	extern int getY(uint8_t const coor);
#else
	#define offSet(x, y) (y * WIDTH_BOARD + x)
	#define getX(coor) (coor % WIDTH_BOARD)
	#define getY(coor) (coor / WIDTH_BOARD)
#endif

#endif