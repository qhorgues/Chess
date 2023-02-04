/**
 * @file Board.c
 * @author Quentin Horgues (you@domain.com)
 * @brief Diverse foonction de gestion de l'echequier
 * @version 0.1
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022 par Quentin Horgues
 *
 */

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../include/Board.h"
#include "../include/except.h"



 /**
  * \~english @def MAILBOX_64
  * \~english @brief contains the prototype of the mailbox 64
  * \~english @details Mailbox 64 for locating the starting square of a movement on mailbox 120
  *
  * \~french @def MAILBOX_64
  * \~french @brief contient le prototype de la mailbox 64
  * \~french @details La mailbox 64 pérméttant de localiser la case de départ d'un mouvement sur la mailbox 120
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

  /**
   * \~english @def MAILBOX_120
   * \~english @brief contains the prototype of the mailbox 120
   * \~english @brief The mailbox 120 allows you to manage tray overflows during movements
   *
   * \~french @def MAILBOX_120
   * \~french @brief contient le prototype de la mailbox 120
   * \~french @details La mailbox 120 permet de gérer les débordements de plateau lors des mouvements
   */
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

#if defined(_DEBUG) // In the release version the three functions are built statically with a macro function

   /**
	* \~english @brief returns a one-dimensional index from x and y index for an array of size 64 (8*8)
	* \~english @param x x index
	* \~english @param y y index
	* \~english @return int one-dimensional index
	*
	* \~french @brief renvoie un indice unidimensionnelle à partir des indices x et y pour un tableau de taille 64 (8*8)
	* \~french @param x indice x
	* \~french @param y indice y
	* \~french @return int indice unidimensionnelle
	*/
int offSet(uint8_t const x, uint8_t const y)
{
	assert(x <= WIDTH_BOARD && "x out of grid");
	assert(y <= WIDTH_BOARD && "y out of grid");
	return y * WIDTH_BOARD + x;
}

/**
 * \~english @brief Apartir d'un indice unidimensionnelle récupere l'indice multidimensionel x pour un tableau de taille 64 (8*8)
 * \~english @param coor indice unidimensionnelle
 * \~english @return int indice x
 *
 * \~french @brief Apartir d'un indice unidimensionnelle récupere l'indice multidimensionel x pour un tableau de taille 64 (8*8)
 * \~french @param coor indice unidimensionnelle
 * \~french @return int indice x
 */
int getX(uint8_t const coor)
{
	assert(coor <= SIZE_BOARD && "coor out of grid");
	return coor % WIDTH_BOARD;
}

/**
 * \~english @brief Apartir d'un indice unidimensionnelle récupere l'indice multidimensionel y pour un tableau de taille 64 (8*8)
 * \~english @param coor indice unidimensionnelle
 * \~english @return int indice y
 *
 * \~french @brief Apartir d'un indice unidimensionnelle récupere l'indice multidimensionel y pour un tableau de taille 64 (8*8)
 * \~french @param coor indice unidimensionnelle
 * \~french @return int indice y
 */
int getY(uint8_t const coor)
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
 * \~english @param[in] minI The start of the X positioning
 * \~english @param[in] maxI The end of the X-positioning
 * \~english @param[in] increaseI The difference in positioning between the parts in X
 * \~english @param[in] minJ The start of positioning in Y
 * \~english @param[in] maxJ The end of the positioning in Y
 * \~english @param[in] increaseJ The positional difference between the pieces in Y
 *
 * \~english @warning passing a grid size smaller than 8*8 or an invalid pointer causes an error
 *
 * \~french @brief Construit toutes les piéces d'un type sur la grille
 * \~french @details Permet de construire en série une même pièce sur une grille
 * \~french lors de l'INITIALISATION car les couleurs sont déterminéé en fonction de la position
 *
 * \~french @param[out] grid Le plateau ou positionner les pièces
 * \~french @param[in] type Le type de la pièce
 * \~french @param[in] value La valeur de la pièce
 * \~french @param[in] minI Le départ du positionement en X
 * \~french @param[in] maxI La fin du positionement en X
 * \~french @param[in] increaseI L'ecart de positionement entre les pièces en X
 * \~french @param[in] minJ Le départ du positionement ven Y
 * \~french @param[in] maxJ La fin du positionement en Y
 * \~french @param[in] increaseJ L'ecart de positionement entre les pièces en Y
 *
 * \~french @warning passer une grille de taille inferieur a 8*8 ou un pointeur invalide provoque une erreur
 *
 */
static void posPiece(struct Piece* const restrict grid, enum TypePiece const type, enum ValuePiece const value, uint8_t const minX, uint8_t const maxX, uint8_t const increaseX, uint8_t const minY, uint8_t const maxY, uint8_t const increaseY)
{
	assert(grid != NULL && "grid cannot be NULL");
	for (uint8_t i = minX; i < maxX; i += increaseX)
	{
		for (uint8_t j = minY; j < maxY; j += increaseY)
		{
			grid[offSet(i, j)].type = type;
			grid[offSet(i, j)].value = value;
			if (j <= 1)
				grid[offSet(i, j)].color = Black;
			else if (j >= 6)
				grid[offSet(i, j)].color = White;
			else
				grid[offSet(i, j)].color = NoColor;
			grid[offSet(i, j)].prise_pass = false;
			grid[offSet(i, j)].moved = false;
		}
	}
}

/**
 * \~english @brief Reset the starting grid on failure
 * \~english @details Resets the grid by recreating the pieces to their initial position at check
 * \~english @details allows to (re)start a game (The function takes as parameter the grid to be reiitialized)
 *
 * \~english @param[out] grid The board to (re)initialize
 *
 * \~english @warning passing a grid of size inferior to 8*8 or an invalid pointer causes an error
 *
 * \~english Example:
 * @code
 * struct Piece grid[SIZE_BOARD][SIZE_BOARD];
 * resetGrid(grid);
 * @endcode
 * \~english Modifies the grid by resetting it to the starting status of a failure board
 *
 * \~french @brief renvoi la grille de départ au échec
 * \~french @details Réinitialise la grille en recréen les pieces a leur position initiale au echec
 * \~french permet ainsi de (re)lancer une partie (La fonction prend en parametre la grille a reiitialiser)
 *
 * \~french @param[out] grid Le plateau a (re)initialiser
 *
 * \~french @warning passer une grille de taille inferieur a 8*8 ou un pointeur invalide provoque un unadressable access
 *
 * \~french Exemple:
 * @code
 * struct Piece grid[SIZE_BOARD][SIZE_BOARD];
 * resetGrid(grid);
 * @endcode
 * \~french Modifie la grille en la reinitialisant au statut de depart d'un plateau d'echec
 */
void resetGrid(struct Piece(* const restrict grid))
{
	assert(grid != NULL && "The pointer on the grid must not be NULL");
	posPiece(grid, None, Val_None, 0, 8, 1, 2, 6, 1);
	posPiece(grid, Pawn, Val_Pawn, 0, 8, 1, 1, 7, 5);
	posPiece(grid, Rook, Val_Rook, 0, 8, 7, 0, 8, 7);
	posPiece(grid, Knight, Val_Knight, 1, 7, 5, 0, 8, 7);
	posPiece(grid, Bishop, Val_Bishop, 2, 6, 3, 0, 8, 7);
	posPiece(grid, Queen, Val_Queen, 3, 4, 1, 0, 8, 7);
	posPiece(grid, King, Val_King, 4, 5, 1, 0, 8, 7);
}

/**
 * \~english @brief Initailise the structure board
 *
 * \~english @return The structure board initializes
 *
 * \~french @brief Initailise la structure board
 *
 * \~french @return La structure board initialise
 */
struct Board initBoard(void)
{
	struct Board board = { .mailbox_64 = MAILBOX_64, .mailbox_120 = MAILBOX_120, .nb_white_eliminate = 0, .nb_black_eliminate = 0 };
	resetGrid(board.grid);
	return board;
}

/**
 * \~english @brief Function to move a piece between two squares on the board
 * \~english @details Function that tests if the coordinates are in the board ( \c assert \c) and moves a piece from one square to another
 * \~english (does not test if the move for the chosen piece is valid) and if the move kills a piece in the board.
 * \~english If the move kills an opponent's piece, that piece is added to the opponent's lost pieces table
 *
 * \~english @param[in,out] board The board structure
 * \~english @param[in] dpt Start coordinate
 * \~english @param[in] arv Arrival coordinate
 *
 * \~english @warning the pointer to the board structure must not be invalid
 * \~english @warning the content of the board structure must be valid
 *
 * \~english Example :
 * @code
 * int main(void)
 * {
 * struct Board board = initBoard();
 * move(&board, COOR(3, 7), COOR(4, 0));
 * printBoard(&board, stdout);
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
 * \~french @details Fonction testant si les coordonnées sont dans le plateau ( \c assert \c) et deplace une piece d'une case
 * \~french a une autre selon les coordonnes (ne teste pas si le mouvement pour la piece choisit est valide) et si le
 * \~french mouvement tue une piece de l'adversaire, cette piece est ajoute au tableau des pieces perdue de l'adversaire
 *
 * \~french @param[in,out] board La structure du plateau
 * \~french @param[in] dpt Coordonnée de depart
 * \~french @param[in] arv Coordonnée d'arrive
 * \~french
 * \~french @warning le pointeur sur la structure Board ne doit pas etre invalide
 * \~french @warning le contenu de la structure board doit etre valide
 *
 * \~french Exemple :
 * @code
 * int main(void)
 * {
 *     struct Board board = initBoard();
 *     move(&board, COOR(3, 7), COOR(4, 0));
 *     printBoard(&board, stdout);
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
void move(struct Board* const restrict board, uint8_t const dpt, uint8_t const arv)
{
	assert(dpt < SIZE_BOARD && "Starting coordinate outside the grid");
	assert(arv < SIZE_BOARD && "Ending coordinate outside the grid");
	assert(board != NULL && "The board structure cannot be NULL");

	if (board->grid[arv].color == White)
	{
		board->eliminate_white[board->nb_white_eliminate] = board->grid[arv];
		board->nb_white_eliminate++;
	}
	else if (board->grid[arv].color == Black)
	{
		board->eliminate_black[board->nb_black_eliminate] = board->grid[arv];
		board->nb_black_eliminate++;
	}
	board->grid[arv] = board->grid[dpt];
	board->grid[arv].moved = true;
	board->grid[dpt] = (struct Piece){ .color = NoColor, .type = None, .value = Val_None, .prise_pass = false, .moved = false };
}

/**
 * \~english @brief Returns the colour associated with the player
 * \~english Returns the colour associated with the player, i.e. 'W' for entry 1 and 'B' for entry -1 and otherwise the space character (ASCII 32)
 *
 * \~english @param[in] player the player number (white:1, black:-1, none:0)
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
 * \~french @details Renvoie la couleur associe au joueur soit 'W' pour l'entrée 1 et 'B' pour l'entrée -1 et sinon le caractere espace (ASCII 32)
 *
 * \~french @param[in] player le numero du joueur (blanc:1, noir:-1, aucun:0)
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
static inline char playerColor(enum PlayerColor const player)
{
	assert(player >= -1 && player <= 1 && "player can only be -1, 0 or 1");
	if (player == White)
	{
		return 'W';
	}
	else if (player == Black)
	{
		return 'B';
	}
	return ' ';
}

/**
 * \~english @brief Displays the ladder in the stream indicated in parameter
 *
 * \~english @param[in] board The board structure of the game board
 * \~english @param[out] out The output or write board
 * \~english @return int returns on error -1 otherwise 0
 *
 * \~english @warning the pointer to the board structure must not be invalid
 * \~english @warning the content of the board structure must be valid
 *
 * \~english @exception EILSEQ A wide character code that does not match a valid character has been detected ( \c fprint )
 * \~english @exception EINVAL Insufficient arguments ( \c fprintf )
 * \~english @exception ENOMEM Insufficient storage space ( \c fprintf )
 * \english @exception EOVERFLOW The value of n is greater than 2147483647 or the number of bytes needed to hold
 * \~english @exception EOVERFLOW The value of n is greater than 2147483647 or the number of bytes required to contain the output excluding
 * \~english the null termination value is greater than 2147483647 ( \c fprintf )
 *
 *
 * \~french  @brief Affiche l'echequier dans le flux indiqué en parametre
 *
 * \~french @param[in] board La structure board du plateau du jeu
 * \~french @param[out] out La sortie ou ecrire le plateau
 * \~french @return int retoure en cas d'erreur -1 sinon 0
 *
 * \~french @warning le pointeur sur la structure Board ne doit pas etre invalide
 * \~french @warning le contenu de la structure board doit etre valide
 *
 * \~french @exception EILSEQ Un code de caractères larges qui ne correspond pas à un caractère valide a été détecté ( \c fprintf )
 * \~french @exception EINVAL Les arguments sont insuffisants ( \c fprintf )
 * \~french @exception ENOMEM Espace de stockage insuffisant ( \c fprintf )
 * \~french @exception EOVERFLOW La valeur de n est supérieure à 2147483647 ou le nombre d’octets nécessaires pour contenir
 * \~french la sortie à l’exclusion de la valeur null de terminaison est supérieur à 2147483647 ( \c fprintf )
 */
int printBoard(struct Board const* const restrict board, FILE* const restrict out)
{
	assert(board != NULL && "board cannot be NULL");
	assert(out != NULL && "out cannot be NULL");
	for (uint8_t i = 0; i < SIZE_BOARD; i++)
	{
		fprintf(out, " %c%c ", playerColor(board->grid[i].color), board->grid[i].type);
		returnExcept(-1);
		if ((i + 1) % 8 == 0)
		{
			fputc('\n', out);
			returnExcept(-1);
		}
	}
	return 0;
}

/**
 * \~english @brief Complete the move list for a piece with in-line or diagonal moves
 * \~english @details Adds to the end of the list the moves in line, column and diagonal as long as there is no obstacle or enemy player:
 * \~english * If it is a piece of the same player we have finished testing this row/column/diagonal
 * \~english * If it is an enemy piece we add it to the list and finish testing this line/column/diagonal
 * \~english * Otherwise we add the move to the list and test the next square
 *
 * \~english @param[in] board A pointer to the board structure
 * \~english @param[in, out] list The list of moves that will be modified by the function, it must be initialized with the starting move before calling the function
 * \~english @param[in] tabMove The array of moves relative to mailbox 120, e.g. [-10, -1, 1, 10] for rows and columns (tower move)
 * \~english @param[in] sizeTabMove The size of the motion array
 *
 * \~english @warning the pointer to the Board structure must not be invalid
 * \~english @warning the content of the Board structure must be valid
 *
 * \~french @brief Completer la liste de mouvement pour une piece ayant des mouvements en ligne ou diagonal
 * \~french @details Ajoute a la fin de la liste les mouvements en ligne, colonne et diagonal tant qu'il n'y a ni obstacle ni joueur ennemi :
 * \~french * Si c'est une piece du meme joueur on a terminer de tester cette ligne/colonne/diagonal
 * \~french * Si c'est une piece ennemi on l'ajoute a la liste et on a terminer de tester cette ligne/colonne/diagonal
 * \~french * Sinon on ajoute le mouvement a la liste et on va tester la case suivante
 *
 * \~french @param[in] board Un pointeur sur la structure board
 * \~french @param[in, out] list La liste de mouvement qui sera modifie par la fonction, la doit etre initialise au prealable avec le mouvement de depart avant l'appel de la fonction
 * \~french @param[in] tabMove Le tableau de deplacement par rapport a la mailbox 120, par exemple [-10, -1, 1, 10] pour les lignes et les colonnes (mouvement de la tour)
 * \~french @param[in] sizeTabMove La taille du tableau de mouvement
 *
 * \~french @warning le pointeur sur la structure Board ne doit pas etre invalide
 * \~french @warning le contenu de la structure Board doit etre valide
 */
static void getPieceMove(struct Board const* const restrict board, ListMove* const restrict list, int8_t const* const tabMove, uint8_t const sizeTabMove)
{
	assert(board != NULL && "board cannot be NULL");
	assert(list != NULL && "list cannot be NULL");
	assert(tabMove != NULL && "tabMove cannot be NULL");
	for (int i = 0; i < sizeTabMove; i++)
	{
		int8_t actu = board->mailbox_64[list->dpt] + tabMove[i];
		while (board->mailbox_120[actu] != -1)
		{
			if (board->grid[board->mailbox_120[actu]].color == 0)
			{
				list->pushBack(list, board->mailbox_120[actu]);
				try
				{
					catch (ERROR_NOT_ENOUGH_SPACE) :
						perror("In getPieceMove to the pushBack call");
					list->clear(list);
					break;
				catchAllExcept:
					perror("In getPieceMove to the pushBack call");
					break;
				} endTry;
				actu += tabMove[i];
			}
			else if (board->grid[board->mailbox_120[actu]].color == board->grid[list->dpt].color * -1)
			{
				list->pushBack(list, board->mailbox_120[actu]);
				try
				{
					catch (ERROR_NOT_ENOUGH_SPACE) :
						perror("In getPieceMove to the pushBack call");
					list->clear(list);
					break;
				catchAllExcept:
					perror("In getPieceMove to the pushBack call");
					break;
				} endTry;
				break;
			}
			else
			{
				break;
			}
		}
	}
}

/**
 * \~english @brief Complete la liste passe en parametre
 * \~english @details Complete la liste passe en parametre des mouvements de la piece indique a la coordonnes assigne lors de l'appelle de la fonction \c initListMove au prealable
 * \~english @param[in] board Un pointeur sur la structure board
 * \~english @param[in, out] list Un liste initialisée vide que la fonction va completer
 *
 * \~english @warning le pointeur sur la structure Board ne doit pas etre invalide
 * \~english @warning le contenu de la structure Board doit etre valide
 *
 * @code
 * struct Board board = InitBoard();
 * ListMove list = initListMove(offSet(6, 4));
 * getListMove(&board, &list);
 * @endcode
 *
 *
 * \~french @brief Complete la liste passe en parametre
 * \~french @details Complete la liste passe en parametre des mouvements de la piece indique a la coordonnes assigne lors de l'appelle de la fonction \c initListMove au prealable
 * \~french @param[in] board Un pointeur sur la structure board
 * \~french @param[in, out] list Un liste initialisée vide que la fonction va completer
 *
 * \~french @warning le pointeur sur la structure Board ne doit pas etre invalide
 * \~french @warning le contenu de la structure Board doit etre valide
 *
 * @code
 * struct Board board = InitBoard();
 * ListMove list = initListMove(offSet(6, 4));
 * getListMove(&board, &list);
 * @endcode
 */
void getListMove(struct Board const* const restrict board, ListMove* const restrict list)
{
	assert(board != NULL && "board cannot be NULL");
	assert(list != NULL && "list cannot be NULL");
	assert(list->dpt < SIZE_BOARD && "invalide coordinate list.dpt");
	switch (board->grid[list->dpt].type)
	{
	case Rook:;
		int8_t const move_tower[4] = { -10, -1, 1, 10 };
		getPieceMove(board, list, move_tower, 4);
		break;
	case Knight:;
		int8_t const move_knight[8] = { -21, -19, -12, -8, 8, 12, 19, 21 };
		for (int i = 0; i < 8; i++)
		{
			int8_t const actu = board->mailbox_64[list->dpt] + move_knight[i];
			if (board->mailbox_120[actu] != -1 && board->grid[board->mailbox_120[actu]].color != board->grid[list->dpt].color)
			{
				list->pushBack(list, board->mailbox_120[actu]);
				try
				{
				catch (ERROR_NOT_ENOUGH_SPACE) :
					perror("In getListMove to the pushBack call");
					list->clear(list);
					return;
				catchAllExcept:
					perror("In getListMove to the pushBack call");
					break;
				} endTry;
			}
		}
		break;
	case Bishop:;
		int8_t const move_bishop[4] = { -11, -9, 9, 11 };
		getPieceMove(board, list, move_bishop, 4);
		break;
	case Queen:;
		int8_t const move_queen[8] = { -11, -10, -9, -1, 1, 9, 10, 11 };
		getPieceMove(board, list, move_queen, 8);
		break;
	case King:;
		int8_t const move_king[8] = { -11, -10, -9, -1, 1, 9, 10, 11 };
		for (int i = 0; i < 8; i++)
		{
			int8_t const actu = board->mailbox_64[list->dpt] + move_king[i];
			if (board->mailbox_120[actu] != -1 && board->grid[board->mailbox_120[actu]].color != board->grid[list->dpt].color)
			{
				list->pushBack(list, board->mailbox_120[actu]);
				try
				{
					catch (ERROR_NOT_ENOUGH_SPACE) :
						perror("In getListMove to the pushBack call");
					list->clear(list);
					return;
				catchAllExcept:
					perror("In getListMove to the pushBack call");
					break;
				} endTry;
			}
		}
		break;
	case Pawn:;

		int8_t const color = board->grid[list->dpt].color;
		uint8_t const dpt = board->mailbox_64[list->dpt];
		uint8_t const advance = dpt + color * (-10);
		uint8_t const eat[2] = { board->mailbox_64[list->dpt] + color * (-11), board->mailbox_64[list->dpt] + color * (-9) };
		if (board->mailbox_120[advance] != -1 && board->grid[board->mailbox_120[advance]].color == 0)
		{
			list->pushBack(list, board->mailbox_120[advance]);
			if (board->grid[list->dpt].moved == false && board->grid[board->mailbox_120[advance + color * (-10)]].color == 0)
			{
				list->pushBack(list, board->mailbox_120[advance + color * (-10)]);
				try
				{
					catch (ERROR_NOT_ENOUGH_SPACE) :
						perror("In getListMove to the pushBack call");
					list->clear(list);
					return;
				catchAllExcept:
					perror("In getListMove to the pushBack call");
					break;
				} endTry;
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (board->mailbox_120[eat[i]] != -1 && board->grid[board->mailbox_120[eat[i]]].color == color * -1)
			{
				list->pushBack(list, board->mailbox_120[eat[i]]);
				try
				{
					catch (ERROR_NOT_ENOUGH_SPACE) :
						perror("In getListMove to the pushBack call");
					list->clear(list);
					return;
				catchAllExcept:
					perror("In getListMove to the pushBack call");
					break;
				} endTry;
			}
			else if (board->mailbox_120[eat[i]] != -1 && board->grid[board->mailbox_120[eat[i]]].color == 0 && board->grid[board->mailbox_120[eat[i] + 10 * color]].prise_pass == true)
			{
				list->pushBack(list, board->mailbox_120[eat[i]]);
				try
				{
					catch (ERROR_NOT_ENOUGH_SPACE) :
						perror("In getListMove to the pushBack call");
					list->clear(list);
					return;
				catchAllExcept:
					perror("In getListMove to the pushBack call");
					break;
				} endTry;
			}
		}
		break;
	default:
		break;
	}
}

uint8_t findKing(struct Board const* const restrict board, enum PlayerColor color)
{
	for (uint8_t i = 0; i < SIZE_BOARD; i++)
	{
		if (board->grid[i].color == color && board->grid[i].type == King)
		{
			return i;
		}
	}
	return UNDEFINED_COORDINATES;
}

bool check(struct Board* const restrict board, enum PlayerColor color, uint8_t coorKing)
{
	if (coorKing >= UNDEFINED_COORDINATES)
	{
		assert(color != NoColor && "It is necessary to define the colour of the king if the coordinates are not defined");
		coorKing = findKing(board, color);
		assert(coorKing != UNDEFINED_COORDINATES && "No king in grid");
	}
	else if (color == NoColor)
	{
		assert(board->grid[coorKing].type == King && "If the square indicated is not a king you must indicate the colour");
		color = board->grid[coorKing].color;
	}
	struct Piece* const currentKing = &board->grid[coorKing];
	enum TypePiece const originalPiece = currentKing->type;
	enum TypePiece const listPiece[6] = { King, Rook, Bishop, Knight, Pawn };
	for (uint8_t i = 0; i < 6; i++)
	{
		currentKing->type = listPiece[i];
		ListMove listCurrentType = initListMove(coorKing);
		getListMove(board, &listCurrentType);

		ptrListMove ptrListCurrentType = listCurrentType.listMove;
		while (ptrListCurrentType != NULL)
		{
			if (board->grid[ptrListCurrentType->coor].color == color * -1)
			{
				struct Piece const* const currentCase = &board->grid[ptrListCurrentType->coor];
				if (listPiece[i] == currentCase->type || ((listPiece[i] == Rook || listPiece[i] == Bishop) && currentCase->type == Queen))
				{
					listCurrentType.clear(&listCurrentType);
					currentKing->type = originalPiece;
					return true;
				}
			}
			ptrListCurrentType = ptrListCurrentType->next;
		}

		listCurrentType.clear(&listCurrentType);
	}
	currentKing->type = originalPiece;
	return false;
}

/**
 * @brief La fonction permettant de completer la liste des mouvements du roi si il peut roquer
 * @details ajoute a la liste de mouvement les cases d'arrivées du roi après un roque
 *
 * @param[in] board La structure board
 * @param[in, out] list La liste à compléter
 *
 */
 /* void castling(struct Board const *const restrict board, ListMove *const restrict list, uint8_t const coorKing)
 {
	 uint8_t const startedPositionKingWhite = 60;
	 uint8_t const startedPositionKingBlack = 4;

	 if ( !Check(...) && (coorKing == startedPositionKingWhite || coorKing == startedPositionKingBlack) && board->grid[coorKing].moved == false)
	 {
		 uint8_t index_min = coorKing+1;
		 uint8_t index_max = coorKing-1;
		 if (!board->grid[coorKing-4].moved)
		 {
			 index_min = coorKing-3;
		 }
		 if (!board->grid[coorKing+3].moved)
		 {
			 index_max = coorKing+2;
		 }
		 uint8_t result = 3;
		 for (uint8_t i = index_min; i <= index_max; i++)
		 {
			 if (board->grid[i].type != None || (i > coorKing-3 && i < coorKing+2 && !Check(..., coorKing) && ) )
			 {
				 if (i < coorKing ||  (i > coorKing-3 && !Check(..., coorKing) ) )
				 {
					 result &= 2; // 1 << 1
					 i = coorKing+1;
					 continue;
				 }
				 else if ()
			 }
		 }
	 }
 } */
