/**
 * \file ReadWrite.h
 * \author Harsh Patel
 * \brief Reading text file to build game grid and state, 
 *   and outputting current state of game grid to text fie.
 */

#ifndef READ_WRITE_H_
#define READ_WRITE_H_

#include <iostream>
#include <vector>
#include <string>
#include "GameboardTypes.h"

 /**
  * \brief Reading game grid and cells from text file.
  * \param f File name to read.
  * \throws Runtime_error If file not found.
  * \returns Vector Representing state of cell at each column and row.
  */
std::vector<char> readFile(std::string f);

/**
  * \brief Output game grid and cells to text file.
  * \param f File name to write to.
  * \param s Grid to be outputted to the text file.
  * \throws Runtime_error If file not found.
  */
void writeFile(std::string f, std::vector<std::vector<CellT>> s);

#endif