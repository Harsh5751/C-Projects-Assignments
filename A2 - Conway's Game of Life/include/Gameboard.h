/**
 * \file Gameboard.h
 * \author Harsh Patel
 * \brief Provides an ADT representing a model for the game of life by Conway
 *   including game board state and its transitions.
 */
#ifndef A4_GAME_BOARD_H_
#define A4_GAME_BOARD_H_

#include <iostream>
#include "GameboardTypes.h"
#include "ReadWrite.h"
#include <vector>


 /**
  * \brief Represents the state of a Game of life.
  * \details The board consists of a n by n grid with cells having state alive or dead
  *   from which the current grid creates the next state of the cells.
  */
class boardUniverse {
private:
	int rows;
	int cols;
	std::vector<std::vector<CellT>> Universe;

	//Local Functions
	/**
	 * \brief Initialize the current grid by filling it with dead or alive cells
	 *   from input text file.
	 * \param file File name containing initial gameboard state
	 * \throws invalid_argument If rows and columns are not integers or not equal to each other
     */
	std::vector<std::vector<CellT>> initUniverse(std::string file);

	public:

		/**
		* \brief Constructs a new Grid with n rows and n columns intialized each cell to be
		*   of type CellT(dead or alive).
		* \param f File name containing initial gameboard state
		* \throws out_of_range If the number of rows of columns exceed the max rows or max columns
		*   defined for the game.
		*/
		boardUniverse(std::string f);

		/**
		* \brief Checks if grid's rows or columns exceed the maximum limit set.
		* \param rows Represents number of rows of the game grid.
		* \param cols Represents number of columns of the game grid.
		* \returns Boolean representing if row or column exceed maximum limit set.
		*/
		bool overSize(int rows, int cols);

		/**
		* \brief Checks if grid's row number is a positive number and doesn't exceed the 
		*   gird's total number of rows.
		* \param row Represents specific row of the game grid.
		* \returns Boolean representing if row is in bound of the game grid.
		*/
		bool rowInBound(int row);

		/**
		* \brief Checks if grid's column number is a positive number and doesn't exceed the
		*   gird's total number of columns.
		* \param col Represents specific column of the game grid.
		* \returns Boolean representing if column is in bound of the game grid.
		*/
		bool colInBound(int col);

		/**
		* \brief Gets total number of rows to define game grid.
		* \returns Integer representing total number of rows in game grid.
		*/
		int getRows();

		/**
		* \brief Gets total number of columns to define game grid.
		* \returns Integer representing total number of columns in game grid.
		*/
		int getCols();

		/**
		* \brief Gets game grid with cell states.
		* \returns Vector of CellT representing game grid with cell states.
		*/
		std::vector<std::vector<CellT>> getUniverse();

		/**
		* \brief Gets cell state of specific cell on game grid.
		* \param row Represents specific row of the game grid.
		* \param col Represents specific column of the game grid.
		* \throws out_of_range If column and row are out of bounds of game grid.
		* \returns CellT representing state of cell at that row and column.
		*/
		CellT cellState(int row, int col);

		/**
		* \brief Gets number of neighbors in state Alive of current cell.
		* \param row Represents specific row of the game grid.
		* \param col Represents specific column of the game grid.
		* \returns Integer representing number of cells in state Alive 
		*   that are neighbors to cell at row and column.
		*/
		int numAliveNeighbors(int row, int col);

		/**
		* \brief Uses the state of the cells of the current grid to create a new grid state 
		* \details Uses the state of the cells of the current grid to create a new grid with 
		*   required changes to the state of certain cells and assigns the new grid as the current
		*   grid of the game.
		*/
		void NextUniverse();

		/**
		* \brief Checks to see if game is over by checking if all cells of the grid
		*   are in state Dead.
		* \returns Boolean representing if all cells are Dead and game is over.
		*/
		bool gameOver();
};

#endif