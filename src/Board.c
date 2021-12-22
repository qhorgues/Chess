#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "Board.h"
#include "except.h"

/**
 * @def MAILBOX_64
 * @brief contient le prototype de la mailbox 64
 * 
 */
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
            -1,  0,  1,  2,  3,  4,  5,  6,  7, -1, \
            -1,  8,  9, 10, 11, 12, 13, 14, 15, -1, \
            -1, 16, 17, 18, 19, 20, 21, 22, 23, -1, \
            -1, 24, 25, 26, 27, 28, 29, 30, 31, -1, \
            -1, 32, 33, 34, 35, 36, 37, 38, 39, -1, \
            -1, 40, 41, 42, 43, 44, 45, 46, 47, -1, \
            -1, 48, 49, 50, 51, 52, 53, 54, 55, -1, \
            -1, 56, 57, 58, 59, 60, 61, 62, 63, -1, \
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, \
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1  \
    }

int off_set(uint8_t const x, uint8_t const y)
{
	assert(x <= WEIGHT_BOARD && "x out of grid");
	assert(y <= WEIGHT_BOARD && "y out of grid");
	return y * WEIGHT_BOARD + x;
}

int get_x(uint8_t const coor)
{
	return coor % WEIGHT_BOARD;
}

int get_y(uint8_t const coor)
{
	return coor / WEIGHT_BOARD;
}

/**
 * @brief Construit toutes les pieces d'un type sur la grille
 * @details Permet de construire en serie une meme piece sur une grille
 * lors de l'INITIALISATION car les couleurs sont determinee en fonction de la position
 * 
 * @param[out] grid Le plateau ou positionner les pieces
 * @param[in] type Le type de la piece
 * @param[in] value La valeur de la piece
 * @param[in] min_i Le depart du positionement en X
 * @param[in] max_i La fin du positionement en X
 * @param[in] increase_i L'ecart de positionement entre les pieces en X
 * @param[in] min_j Le depart du positionement ven Y
 * @param[in] max_j La fin du positionement en Y
 * @param[in] increase_j L'ecart de positionement entre les pieces en Y
 *  
 * @warning passer une grille de taille inferieur a 8*8 ou un pointeur invalide provoque une erreur
 * 
 */
static void pos_piece(struct Piece (*const restrict grid), enum Type_piece const type, enum Value_piece const value, uint8_t const min_x, uint8_t const max_x, uint8_t const increase_x, uint8_t const min_y, uint8_t const max_y, uint8_t const increase_y)
{
    for (uint8_t i = min_x; i < max_x; i+=increase_x)
    {
        for (uint8_t j = min_y; j < max_y; j+=increase_y)
        {
            grid[off_set(i, j)].type = type;
            grid[off_set(i, j)].value = value;
            if (j <= 1)
                grid[off_set(i, j)].color = -1;
            else if (j >= 6)
                grid[off_set(i, j)].color = 1;
            else
                grid[off_set(i, j)].color = 0;
            grid[off_set(i, j)].prise_pass = false;
            grid[off_set(i, j)].moved = false;
        }
    }
}

/**
 * @brief renvoi la grille de depart au echec
 * @details Réinitialise la grille en recreen les pieces a leur position initiale au echec
 * permet ainsi de (re)lancer une partie (La fonction prend en parametre la grille a reiitialiser)
 * 
 * @param[out] grid Le plateau a (re)initialiser
 * 
 * @warning passer une grille de taille inferieur a 8*8 ou un pointeur invalide provoque une erreur
 * 
 * Exemple:
 * @code
 * struct Piece grid[SIZE_BOARD][SIZE_BOARD];
 * reset_grid(grid);
 * @endcode
 * Modifie la grille en la reinitialisant au statut de depart d'un plateau d'echec
 * 
 */
void reset_grid(struct Piece (*const restrict grid))
{
    assert(grid != NULL && "The pointer on the grid must not be NULL");
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

/**
 * @brief Fonction permettant de deplacer une piece entre deux case de l'echequier
 * @details Fonction testant si les coordonnees sont dans le plateau (assert) et deplace une piece d'une case
 * a une autre selon les coordonnes (ne teste pas si le mouvement pour la piece choisit est valide) et si le
 * mouvement tue une piece de l'adversaire, cette piece est ajoute au tableau des pieces perdue de l'adversaire 
 * 
 * @param[in,out] board La structure du plateau
 * @param[in] dpt Coordonnee de depart
 * @param[in] arv Coordonnee d'arrive
 * 
 * @warning le pointeur sur la structure Board ne doit pas etre invalide
 * @warning le contenu de la structure board doit etre valide
 * 
 * Exemple : 
 * @code
 * int main(void)
 * {
 *     struct Board board = Init_Board();
 *     move(&board, COOR(3, 7), COOR(4, 0));
 *     print_board(&board, stdout);
 * }
 * @endcode
 * affiche : 
 * @code
 *  BR  BN  BB  BQ  WQ  BB  BN  BR 
 *  BP  BP  BP  BP  BP  BP  BP  BP 
 *
 *
 * 
 *
 *  WP  WP  WP  WP  WP  WP  WP  WP
 *  WR  WN  WB      WK  WB  WN  WR
 * @endcode
 * On voit que la dame en D1 (3, 7) est deplace en E8 (4, 0)
 */
void move(struct Board *const restrict board, uint8_t const dpt, uint8_t const arv)
{
    assert(dpt < SIZE_BOARD && "Starting coordinate outside the grid");
    assert(arv < SIZE_BOARD && "Ending coordinate outside the grid");
    assert(board != NULL && "The board structure cannot be NULL");
    
    if (board->grid[arv].color == 1)
    {
        board->eliminate_white[board->nb_white_eliminate] = board->grid[arv];
        board->nb_white_eliminate++;
    }
    else if (board->grid[arv].color == -1)
    {
        board->eliminate_black[board->nb_black_eliminate] = board->grid[arv];
        board->nb_black_eliminate++;
    }
    board->grid[arv] = board->grid[dpt];
	board->grid[arv].moved = true;
    board->grid[dpt] = (struct Piece){.color = 0, .type = None, .value = Val_None, .prise_pass = false, .moved = false};
}

/**
 * @brief Renvoie la couleur associe au joueur
 * @details Renvoie la couleur associe au joueur soit 'W' pour l'entree 1 et 'B' pour l'entree -1 sinon ' ' 
 * 
 * @param[in] player 
 * @return La caractrere associe a la couleur du joueur parmis ('B', 'W', ' ')
 * 
 * Exemple :
 * @code
 * printf("Color : %c, %c, %c...", player_color(1), player_color(-1), player_color(23);
 * @endcode
 * affiche
 * @code
 * W, B,  ...
 * @endcode
 */
static inline char player_color(int const player)
{
    if (player == 1)
	{
        return 'W';
	}
	else if (player == -1)
	{
		return 'B';
	}
	return ' ';
}


/**
 * @brief 
 * 
 * @param[in] board La structure board du plateau du jeu
 * @param[out] out La sortie ou ecrire le plateau
 * @return int retoure en cas d'erreur -1 sinon 0
 * 
 * @exception exception associe a fprintf
 */
int print_board(struct Board const *const restrict board, FILE *const restrict out)
{
    for (uint8_t i = 0; i < SIZE_BOARD; i++)
    {
        fprintf( out, " %c%c ", player_color(board->grid[i].color), board->grid[i].type);
        return_except(-1);
		if ( (i+1) % 8 == 0)
		{
			fputc('\n', out);
			return_except(-1);
		}
    }
    return 0;
}

static void get_piece_move(struct Board const *const restrict board, List_move *const restrict list, int const *const tab_move, uint8_t const size_tab)
{
	for (int i = 0; i < size_tab; i++)
	{
		int8_t actu = board->mailbox_64[list->dpt]+tab_move[i];
		while (board->mailbox_120[actu] != -1)
		{
			if (board->grid[board->mailbox_120[actu]].color == 0)
			{
				list->push_back(list, board->mailbox_120[actu]);
				actu += tab_move[i];
			}
			else if (board->grid[board->mailbox_120[actu]].color == board->grid[list->dpt].color * -1)
			{
				list->push_back(list, board->mailbox_120[actu]);
				break;
			}
            else
            {
                break;
            }
		}
	}
}

void get_list_move(struct Board const *const restrict board, List_move *const restrict list)
{
	assert(list->dpt < SIZE_BOARD && "invalide coordinate list.dpt");
	switch (board->grid[list->dpt].type)
	{
	case Rook:;
		int const move_tower[4] = {-10, -1, 1, 10};
		get_piece_move(board, list, move_tower, 4);
		break;
	case Knight:
		break;
	case Bishop:;
		int const move_bishop[4] = {-11, -9, 9, 11};
		get_piece_move(board, list, move_bishop, 4);
		break;
	case Queen:;
		int const move_queen[8] = {-11, -10, -9, -1, 1, 9, 10, 11};
		get_piece_move(board, list, move_queen, 8);
		break;
	case King:
		break;
	case Pawn:
		break;
	default:
		break;
	}
}