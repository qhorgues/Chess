#ifndef COOR_H
#define COOR_H
#include <stdint.h>

#define COOR(x, y) ((struct Coor){x, y})

/**
 * @struct Coor
 * @brief Conserve une coordonnees x et y sur le plateau
 */
struct Coor
{
	uint8_t x;
	uint8_t y;
};

#endif