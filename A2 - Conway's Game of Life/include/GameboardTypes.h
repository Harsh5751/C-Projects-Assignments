/**
 * \file GameboardTypes.h
 * \author Harsh Patel
 * \brief Provides type definition and enumerations for a game grid and cells.
 */

#ifndef A4_GAME_TYPES_H_
#define A4_GAME_TYPES_H_

#include <iostream>

 /**
  * \brief Describes state of cell on game grid.
  */
enum CellT {Dead, Alive};

/**
 * \brief Defines max rows of game grid.
 */
#define MAX_ROWS 20

 /**
  * \brief Defines max columns of game grid.
  */
#define MAX_COLS 20

#endif