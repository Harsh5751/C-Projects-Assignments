/**
 * \file DisplayGen.h
 * \author Harsh Patel
 * \brief Printing the current grid universe and cell states.
 *   to the console.
 */


#ifndef DISPLAY_GEN_H_
#define DISPLAY_GEN_H_

#include <iostream>
#include <vector>
#include "GameboardTypes.h"


 /**
  * \brief Printing the current grid universe and cell states to the console.
  * \param Universe Current grid of the game of life.
  */
void showUniverse(std::vector<std::vector<CellT>> Universe);

#endif