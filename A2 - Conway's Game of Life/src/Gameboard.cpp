/**
 * \file Gameboard.cpp
 * \author Harsh Patel
 */

#include <iostream>
#include <cmath>
#include "Gameboard.h"

using namespace std;


boardUniverse::boardUniverse(string f) {
	this->Universe = initUniverse(f);
	this->cols = Universe.size();
	this->rows = Universe.size();
	if (overSize(rows, cols)) {
		throw out_of_range("number of rows exceeds max rows or number of columns exceeds max columns.");
	}
}

bool boardUniverse::overSize(int rows, int cols) {
	if (cols > MAX_COLS || rows > MAX_ROWS) {
		return true;
	}
	return false;
}

bool boardUniverse::rowInBound(int row) {
	if (row >= this->rows || row < 0) {
		return false;
	}
	return true;
}

bool boardUniverse::colInBound(int col) {
	if (col >= this->cols || col < 0) {
		return false;
	}
	return true;
}

int boardUniverse::getRows() {
	return this->rows;
}

int boardUniverse::getCols() {
	return this->cols;
}

vector<vector<CellT>> boardUniverse::getUniverse() {
	return this->Universe;
}

CellT boardUniverse::cellState(int row, int col) {
	CellT state;
	if (!(rowInBound(row) && colInBound(col))) {
		throw out_of_range("The row or column entered exceeds the column or row of the grid.");
	}
	else if (this->Universe[row][col] == Alive) {
		state = Alive;
	}
	else {
		state = Dead;
	}
	return state;
}

int boardUniverse::numAliveNeighbors(int row, int col) {
	int countNeighbors = 0;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (i != 0 || j != 0) {
				if (rowInBound(row + i) && colInBound(col + j)) {
					if (cellState(i + row, j + col) == Alive) {
						countNeighbors += 1;
					}
				}
			}
		}
	}

	return countNeighbors;
}

void boardUniverse::NextUniverse() {
	vector<vector<CellT>> newUniverse = getUniverse();

	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			int aliveNeighbors = numAliveNeighbors(i, j);

			CellT currentCellState = cellState(i, j);

			if ((aliveNeighbors < 2 || aliveNeighbors > 3)) {
				newUniverse[i][j] = Dead;
			}
			else if(currentCellState == Dead && aliveNeighbors == 3) {
				newUniverse[i][j] = Alive;
			}
			else {
				newUniverse[i][j] = this->Universe[i][j];
			}
			
		}
	}
	this->Universe = newUniverse;
}

bool boardUniverse::gameOver() {
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			if (this->Universe[i][j] == Alive) {
				return false;
			}
		}
	}
	return true;
}

//local function
vector<vector<CellT>> boardUniverse::initUniverse(string file) {
	vector<char> readIn = readFile(file);
	int rows, cols;

	rows = sqrt(readIn.size());
	cols = sqrt(readIn.size());

	if (floor(rows) != ceil(rows) || floor(cols) != ceil(cols) || cols != rows) {
		throw invalid_argument("number of rows and number of columns to be used in grid are not whole numbers or equal");
	}

	vector<vector<CellT>> UniverseVect;
	int count = 0;

	for (int i = 0; i < rows; i++) {

		vector<CellT> cell;

		for (int j = 0; j < cols; j++) {

			if (readIn[count] != '-' && readIn[count] != '*') {
				throw invalid_argument("ASCII symbol from file does not represent CellT state. Only * and - accepted.");
			}

			else if (readIn[count] == '-') {
				cell.push_back(Dead);
				count++;
			}
			else {
				cell.push_back(Alive);
				count++;
			}
		}

		UniverseVect.push_back(cell);
	}
	return UniverseVect;
}


