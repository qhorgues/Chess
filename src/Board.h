#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
 
#define SIZE_BOARD 8

/**
 * @enum Type_piece
 * @brief Stocke le code ASCII de la lettre de la piece associé
 */
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

/**
 * @enum Value_piece
 * @brief Enumeration de la valeur numerique de chaque piece
 */
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

/**
 * @struct Coor
 * @brief Conserve une coordonnees x et y sur le plateau
 */
struct Coor
{
	uint8_t x;
	uint8_t y;
};

/**
 * @struct Piece
 * @brief Les informations d'une piece
 * @details  La structure d'une piece contenant son type, sa valeur,
 * sa couleur (1 <Blanc>, -1 <Noir>) un booleen pour determiner si
 * le pion peut etre pris en prise en passant (le booleen est inutilisé)
 * pour les autres pieces et un booleen pour determiner si une piece a deja
 * bouge, pour le roque ou le double mouvement du pion notamment.
 */
struct Piece
{
    enum Type_piece type;
    enum Value_piece value;
    int8_t color;
    bool prise_pass;
    bool moved;
};

/**
 * @struct Board
 * @brief La structure contenant le plateau, les mailboxs et le tableau des elimines
 * @details Contient la grille du jeu, la mailbox 120 permettant de gerer les debordements de plateau
 * lors des mouvements et la mailbox 64 permettant de localiser la case de depart d'un mouvement sur
 * la mailbox 120, le tableau des pieces blaches et noirs eliminees et enfin le nombre de piece eliminee respectivement
 * 
 */
struct Board
{
    /**
     * @brief La grille principale du jeu
    */
    struct Piece grid[SIZE_BOARD][SIZE_BOARD];
    
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
    const uint8_t mailbox_64[64];

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
    const int8_t mailbox_120[120];
    
    /**
     * @brief Le tableau de toutes les pieces blanches eliminees 
     */
    struct Piece eliminate_white[15];
    
    /**
     * @brief Le tableau de toutes les pieces noirs eliminees 
     */
    struct Piece eliminate_black[15];

    /**
     * @brief Le nombre de piece blanche eliminees permettant de toujours indexer a des valeurs initialisees 
     */
    size_t nb_white_eliminate;

    /**
     * @brief Le nombre de piece noir eliminees permettant de toujours indexer a des valeurs initialisees 
     */
    size_t nb_black_eliminate;

};

extern void reset_grid(struct Piece (*restrict grid)[SIZE_BOARD]);
extern struct Board Init_Board(void);
extern void move(struct Board *restrict board, const int x_dpt, const int y_dpt, const int x_arv, const int y_arv);
int print_board(const struct Board *restrict board, FILE *restrict out);

#endif