//Harsh Patel
#include <algorithm>
#include <iostream>
#include <vector>

#include "Gameboard.h"
#include "catch.h"

using namespace std;

// Tests if vectors are equal
bool sameVector(vector<vector<CellT>> v1, vector<vector<CellT>> v2) {
	if (v1.size() != v2.size()) {
		return false;
	}
	for (unsigned int i = 0; i < v1.size(); i++) {
		for (unsigned int j = 0; j < v1.size(); j++) {
			if (v1[i][j] != v2[i][j]) {
				return false;
			}
		}
	}
	return true;
}

TEST_CASE("tests for GameBoard", "[GameBoard]") {
	
	SECTION("Initialize Gameboard and test size") {
		boardUniverse boardT("Test_file1.txt");
		vector<vector<CellT>> UniverseUsed = { {Alive, Dead, Dead, Dead, Alive},
												{Alive, Alive, Alive, Dead, Dead},
												{Alive, Alive, Alive, Dead, Alive},
												{Alive, Alive, Dead, Dead, Dead},
												{Alive, Dead, Alive, Dead, Alive} };
		REQUIRE(sameVector(boardT.getUniverse(), UniverseUsed));
		REQUIRE(boardT.getRows() == boardT.getCols());
		REQUIRE(((int)boardT.getRows() == (int)boardT.getUniverse().size()));
		REQUIRE(((int)boardT.getCols() == (int)boardT.getUniverse().size()));
	}

	SECTION("Initializing a gameboard bigger then MAX SIZE throws exception") {
		REQUIRE_THROWS_AS(boardUniverse("TooBigTest.txt"), out_of_range);
	}

	SECTION("overSize() - Row and column are in range of MAX SIZE") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(!(boardT.overSize(boardT.getRows(), boardT.getCols())));
	}

	SECTION("overSize() - Row and column same as MAX SIZE return false") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.overSize(20, 20) == false);
	}

	SECTION("Row number is within Rows and not less then 0 returns true") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.rowInBound(2));
	}

	SECTION("Row number is negative should return false") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.rowInBound(-2) == false);
	}

	SECTION("Row number is larger then rows return false") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.rowInBound(20) == false);
	}

	SECTION("Row number is equal to rows return false") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.rowInBound(boardT.getRows()) == false);
	}

	SECTION("Column number is within Columns and not less then 0 returns true") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.colInBound(2));
	}

	SECTION("Column number is negative should return false") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.colInBound(-2) == false);
	}

	SECTION("Column number is larger then columns return false") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.colInBound(20) == false);
	}

	SECTION("Column number is equal to columns return false") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.colInBound(boardT.getCols()) == false);
	}

	SECTION("Get rows returns correct number of rows") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.getRows() == 5);
	}

	SECTION("Get colums returns correct number of columns") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.getCols() == 5);
	}

	SECTION("Get Universe returns correct universe") {
		boardUniverse boardT("Test_file1.txt");
		vector<vector<CellT>> UniverseUsed = { {Alive, Dead, Dead, Dead, Alive},
												{Alive, Alive, Alive, Dead, Dead},
												{Alive, Alive, Alive, Dead, Alive},
												{Alive, Alive, Dead, Dead, Dead},
												{Alive, Dead, Alive, Dead, Alive} };
		REQUIRE(sameVector(boardT.getUniverse(), UniverseUsed));
	}

	SECTION("Check cell state at row and column is Alive") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.cellState(2,2) == Alive);
	}

	SECTION("Check cell state at row and column is Dead") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.cellState(3, 4) == Dead);
	}

	SECTION("Check cell state at row that is out of bound throws exception") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE_THROWS_AS(boardT.cellState(30, 4), out_of_range);
	}

	SECTION("Check cell state at column out of bound throws exception") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE_THROWS_AS(boardT.cellState(1, 400), out_of_range);
	}

	SECTION("Check cell state at row and column out of bound throws exception") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE_THROWS_AS(boardT.cellState(1000, 400), out_of_range);
	}

	SECTION("TEST number of neighbors alive") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.numAliveNeighbors(1,1) == 6);
	}

	SECTION("TEST number of neighbors alive of corner to make sure no wrap around") {
		boardUniverse boardT("Test_file1.txt");
		REQUIRE(boardT.numAliveNeighbors(1, 4) == 2);
	}

	SECTION("TEST number of neighbors alive of all dead gameboard") {
		boardUniverse boardT("AllDead.txt");
		REQUIRE(boardT.numAliveNeighbors(1, 4) == 0);
	}

	SECTION("Calling next Universe produces correct output") {
		boardUniverse boardT("Initial_Universe.txt");
		vector<vector<CellT>> oldUniverse = boardT.getUniverse();
		boardT.NextUniverse();
		boardT.NextUniverse();
		vector<vector<CellT>> currectUniverse = { {Alive, Dead, Alive, Dead}, {Dead, Dead, Alive, Dead}, {Alive, Dead, Dead, Dead}, {Dead, Alive, Dead, Dead} };
		REQUIRE(!(sameVector(oldUniverse, boardT.getUniverse())));
		
	}

	SECTION("Gall gameOver when Alive cells returns false") {
		boardUniverse boardT("Initial_Universe.txt");
		vector<vector<CellT>> oldUniverse = boardT.getUniverse();
		boardT.NextUniverse();
		boardT.NextUniverse();
		REQUIRE(boardT.gameOver() == false);
	}

	SECTION("Gall gameOver when no Alive cells returns True") {
		boardUniverse boardT("Initial_Universe.txt");
		vector<vector<CellT>> oldUniverse = boardT.getUniverse();
		boardT.NextUniverse();
		boardT.NextUniverse();
		boardT.NextUniverse();
		boardT.NextUniverse();
		REQUIRE(boardT.gameOver() == true);
	}


}

