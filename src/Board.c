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

#if !defined(NDEBUG) // En version release les trois fonction sont construite statiquement avec une macro-fonction

int off_set(uint8_t const x, uint8_t const y)
{
	assert(x <= WIDTH_BOARD && "x out of grid");
	assert(y <= WIDTH_BOARD && "y out of grid");
	return y * WIDTH_BOARD + x;
}

int get_x(uint8_t const coor)
{
	assert(coor <= SIZE_BOARD && "coor out of grid");
	return coor % WIDTH_BOARD;
}

int get_y(uint8_t const coor)
{
	assert(coor <= SIZE_BOARD && "coor out of grid");
	return coor / WIDTH_BOARD;
}

#endif

/**
 * \~english @brief Builds all pieces of a type on the grid
 * \~english @details Allows to build in series a same piece on a grid
 * \~english during the INITIALISATION because the colours are determined according to the position
 *
 * \~english @param[out] grid The board where to position the pieces
 * \~english @param[in] type The type of the piece
 * \~english @param[in] value The value of the part
 * \~english @param[in] min_i The start of the X positioning
 * \~english @param[in] max_i The end of the X-positioning
 * \~english @param[in] increase_i The difference in positioning between the parts in X
 * \~english @param[in] min_j The start of positioning in Y
 * \~english @param[in] max_j The end of the positioning in Y
 * \~english @param[in] increase_j The positional difference between the pieces in Y
 *
 * \~english @warning passing a grid size smaller than 8*8 or an invalid pointer causes an error
 *
 * \~french @brief Construit toutes les pieces d'un type sur la grille
 * \~french @details Permet de construire en serie une meme piece sur une grille
 * \~french lors de l'INITIALISATION car les couleurs sont determinee en fonction de la position
 *
 * \~french @param[out] grid Le plateau ou positionner les pieces
 * \~french @param[in] type Le type de la piece
 * \~french @param[in] value La valeur de la piece
 * \~french @param[in] min_i Le depart du positionement en X
 * \~french @param[in] max_i La fin du positionement en X
 * \~french @param[in] increase_i L'ecart de positionement entre les pieces en X
 * \~french @param[in] min_j Le depart du positionement ven Y
 * \~french @param[in] max_j La fin du positionement en Y
 * \~french @param[in] increase_j L'ecart de positionement entre les pieces en Y
 *
 * \~french @warning passer une grille de taille inferieur a 8*8 ou un pointeur invalide provoque une erreur
 *
 */
static void pos_piece(struct Piece(*const restrict grid), enum Type_piece const type, enum Value_piece const value, uint8_t const min_x, uint8_t const max_x, uint8_t const increase_x, uint8_t const min_y, uint8_t const max_y, uint8_t const increase_y)
{
	for (uint8_t i = min_x; i < max_x; i += increase_x)
	{
		for (uint8_t j = min_y; j < max_y; j += increase_y)
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
 * \~english @brief renvoi la grille de depart au echec
 * \~english @details Réinitialise la grille en recreen les pieces a leur position initiale au echec
 * \~english permet ainsi de (re)lancer une partie (La fonction prend en parametre la grille a reiitialiser)
 *
 * \~english @param[out] grid Le plateau a (re)initialiser
 *
 * \~english @warning passer une grille de taille inferieur a 8*8 ou un pointeur invalide provoque une erreur
 *
 * \~english Exemple:
 * @code
 * struct Piece grid[SIZE_BOARD][SIZE_BOARD];
 * reset_grid(grid);
 * @endcode
 * \~english Modifie la grille en la reinitialisant au statut de depart d'un plateau d'echec
 *
 * \~french @brief renvoi la grille de depart au echec
 * \~french @details Réinitialise la grille en recreen les pieces a leur position initiale au echec
 * \~french permet ainsi de (re)lancer une partie (La fonction prend en parametre la grille a reiitialiser)
 *
 * \~french @param[out] grid Le plateau a (re)initialiser
 *
 * \~french @warning passer une grille de taille inferieur a 8*8 ou un pointeur invalide provoque une erreur
 *
 * \~french Exemple:
 * @code
 * struct Piece grid[SIZE_BOARD][SIZE_BOARD];
 * reset_grid(grid);
 * @endcode
 * \~french Modifie la grille en la reinitialisant au statut de depart d'un plateau d'echec
 */
void reset_grid(struct Piece(*const restrict grid))
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
	struct Board board = {.mailbox_64 = MAILBOX_64, .mailbox_120 = MAILBOX_120, .nb_white_eliminate = 0, .nb_black_eliminate = 0};
	reset_grid(board.grid);
	return board;
}

/**
 * \~english @brief Function to move a piece between two squares on the board
 * \~english @details Function that tests if the coordinates are in the board (assert) and moves a piece from one square to another
 * \~english (does not test if the move for the chosen piece is valid) and if the move kills a piece in the board.
 * \~english If the move kills an opponent's piece, that piece is added to the opponent's lost pieces table
 *
 * \~english @param[in,out] board The board structure
 * \~english @param[in] dpt Start coordinate
 * \~english @param[in] arv Arrival coordinate
 * \~english
 * \~english @warning the pointer to the board structure must not be invalid
 * \~english @warning the content of the board structure must be valid
 *
 * \~english Example :
 * @code
 * int main(void)
 * {
 * struct Board board = Init_Board();
 * move(&board, COOR(3, 7), COOR(4, 0));
 * print_board(&board, stdout);
 * }
 * @endcode
 * \~english display :
 * @code
 * BR BN BB BQ WQ BB BN BR
 * BP BP BP BP BP BP BP BP
 *
 *
 *
 *
 * WP WP WP WP WP WP WP WP
 * WR WN WB WK WB WN WR
 * @endcode
 * \~english We see that the lady in D1 (3, 7) is moved to E8 (4, 0)
 *
 * \~french @brief Fonction permettant de deplacer une piece entre deux case de l'echequier
 * \~french @details Fonction testant si les coordonnees sont dans le plateau (assert) et deplace une piece d'une case
 * \~french a une autre selon les coordonnes (ne teste pas si le mouvement pour la piece choisit est valide) et si le
 * \~french mouvement tue une piece de l'adversaire, cette piece est ajoute au tableau des pieces perdue de l'adversaire
 *
 * \~french @param[in,out] board La structure du plateau
 * \~french @param[in] dpt Coordonnee de depart
 * \~french @param[in] arv Coordonnee d'arrive
 * \~french
 * \~french @warning le pointeur sur la structure Board ne doit pas etre invalide
 * \~french @warning le contenu de la structure board doit etre valide
 *
 * \~french Exemple :
 * @code
 * int main(void)
 * {
 *     struct Board board = Init_Board();
 *     move(&board, COOR(3, 7), COOR(4, 0));
 *     print_board(&board, stdout);
 * }
 * @endcode
 * \~french affiche :
 * @code
 * BR  BN  BB  BQ  WQ  BB  BN  BR
 * BP  BP  BP  BP  BP  BP  BP  BP
 *
 *
 *
 *
 * WP  WP  WP  WP  WP  WP  WP  WP
 * WR  WN  WB      WK  WB  WN  WR
 * @endcode
 * \~french On voit que la dame en D1 (3, 7) est deplace en E8 (4, 0)
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
 * \~english @brief Returns the colour associated with the player
 * \~english Returns the colour associated with the player, i.e. 'W' for entry 1 and 'B' for entry -1 and otherwise the space character (ASCII 32)
 *
 * \~english @param[in] player
 * \~english @return The character associated with the colour of the player among ('B', 'W', ' ')
 *
 * \~english Example :
 * @code
 * printf("Color: %c, %c, %c...", player_color(1), player_color(-1), player_color(23);
 * @endcode
 * \~english displays :
 * @code
 * W, B, ...
 * @endcode
 *
 * \~french @brief Renvoie la couleur associe au joueur
 * \~french @details Renvoie la couleur associe au joueur soit 'W' pour l'entree 1 et 'B' pour l'entree -1 et sinon le caractere espace (ASCII 32)
 *
 * \~french @param[in] player
 * \~french @return La caractrere associe a la couleur du joueur parmis ('B', 'W', ' ')
 *
 * \~french Exemple :
 * @code
 * printf("Color : %c, %c, %c...", player_color(1), player_color(-1), player_color(23);
 * @endcode
 * \~french affiche :
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
 * \~english @brief Displays the ladder in the stream indicated in parameter
 *
 * \english @param[in] board The board structure of the game board
 * \english @param[out] out The output or write board
 * \english @return int returns on error -1 otherwise 0
 *
 * \english @exception EILSEQ A wide character code that does not match a valid character has been detected (fprintf)
 * \~english @exception EINVAL Insufficient arguments (fprintf)
 * \~english @exception ENOMEM Insufficient storage space (fprintf)
 * \english @exception EOVERFLOW The value of n is greater than 2147483647 or the number of bytes needed to hold 
 * \~english @exception EOVERFLOW The value of n is greater than 2147483647 or the number of bytes required to contain the output excluding 
 * \~english the null termination value is greater than 2147483647 (fprintf)
 * 
 * 
 * \~french  @brief Affiche l'echequier dans le flux indiqué en parametre
 *
 * \~french @param[in] board La structure board du plateau du jeu
 * \~french @param[out] out La sortie ou ecrire le plateau
 * \~french @return int retoure en cas d'erreur -1 sinon 0
 *
 * \~french @exception EILSEQ Un code de caractères larges qui ne correspond pas à un caractère valide a été détecté (fprintf)
 * \~french @exception EINVAL Les arguments sont insuffisants (fprintf)
 * \~french @exception ENOMEM Espace de stockage insuffisant (fprintf)
 * \~french @exception EOVERFLOW La valeur de n est supérieure à 2147483647 ou le nombre d’octets nécessaires pour contenir 
 * \~french la sortie à l’exclusion de la valeur null de terminaison est supérieur à 2147483647 (fprintf)
 */
int print_board(struct Board const *const restrict board, FILE *const restrict out)
{
	for (uint8_t i = 0; i < SIZE_BOARD; i++)
	{
		fprintf(out, " %c%c ", player_color(board->grid[i].color), board->grid[i].type);
		return_except(-1);
		if ((i + 1) % 8 == 0)
		{
			fputc('\n', out);
			return_except(-1);
		}
	}
	return 0;
}

static void get_piece_move(struct Board const *const restrict board, List_move *const restrict list, int8_t const *const tab_move, uint8_t const size_tab)
{
	for (int i = 0; i < size_tab; i++)
	{
		int8_t actu = board->mailbox_64[list->dpt] + tab_move[i];
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
		int8_t const move_tower[4] = {-10, -1, 1, 10};
		get_piece_move(board, list, move_tower, 4);
		break;
	case Knight:;
		int8_t const move_knight[8] = {-21, -19, -12, -8, 8, 12, 19, 21};
		for (int i = 0; i < 8; i++)
		{
			int8_t const actu = board->mailbox_64[list->dpt] + move_knight[i];
			if (board->mailbox_120[actu] != -1 && board->grid[board->mailbox_120[actu]].color != board->grid[list->dpt].color)
			{
				list->push_back(list, board->mailbox_120[actu]);
			}
		}
		break;
	case Bishop:;
		int8_t const move_bishop[4] = {-11, -9, 9, 11};
		get_piece_move(board, list, move_bishop, 4);
		break;
	case Queen:;
		int8_t const move_queen[8] = {-11, -10, -9, -1, 1, 9, 10, 11};
		get_piece_move(board, list, move_queen, 8);
		break;
	case King:;
		int8_t const move_king[8] = {-11, -10, -9, -1, 1, 9, 10, 11};
		for (int i = 0; i < 8; i++)
		{
			int8_t const actu = board->mailbox_64[list->dpt] + move_king[i];
			if (board->mailbox_120[actu] != -1 && board->grid[board->mailbox_120[actu]].color != board->grid[list->dpt].color)
			{
				list->push_back(list, board->mailbox_120[actu]);
			}
		}
		break;
	case Pawn:;

		int8_t const color = board->grid[list->dpt].color;
		uint8_t const dpt = board->mailbox_64[list->dpt];
		uint8_t const advance = dpt + color * (-10);
		uint8_t const eat[2] = {board->mailbox_64[list->dpt] + color * (-11), board->mailbox_64[list->dpt] + color * (-9)};
		if (board->mailbox_120[advance] != -1 && board->grid[board->mailbox_120[advance]].color == 0)
		{
			list->push_back(list, board->mailbox_120[advance]);
			if (board->grid[list->dpt].moved == false && board->grid[board->mailbox_120[advance + color * (-10)]].color == 0)
			{
				list->push_back(list, board->mailbox_120[advance + color * (-10)]);
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (board->mailbox_120[eat[i]] != -1 && board->grid[board->mailbox_120[eat[i]]].color == color * -1)
			{
				list->push_back(list, board->mailbox_120[eat[i]]);
			}
			else if (board->mailbox_120[eat[i]] != -1 && board->grid[board->mailbox_120[eat[i]]].color == 0 && board->grid[board->mailbox_120[eat[i] + 10 * color]].prise_pass == true)
			{
				list->push_back(list, board->mailbox_120[eat[i]]);
			}
		}
		break;
	default:
		break;
	}
}