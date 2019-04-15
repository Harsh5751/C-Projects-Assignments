#include <iostream>
#include <vector>
#include "GameboardTypes.h"
#include "Gameboard.h"
#include "DisplayGen.h"
#include "ReadWrite.h"

using namespace std;



int main() {

	boardUniverse boardT = boardUniverse("Initial_Universe.txt");
	std::vector<std::vector<CellT>> Universe = boardT.getUniverse();

	showUniverse(Universe);
	boardT.NextUniverse();
	showUniverse(boardT.getUniverse());
	writeFile("Output_Universe.txt", boardT.getUniverse());

	boardT.NextUniverse();
	showUniverse(boardT.getUniverse());
	writeFile("Output_Universe.txt", boardT.getUniverse());

	boardT.NextUniverse();
	showUniverse(boardT.getUniverse());
	boardT.NextUniverse();
	showUniverse(boardT.getUniverse());

	if (boardT.gameOver()) {
		cout << endl;
		cout << "All cells are dead no more valid moves. Universe has died." << endl;
	}
	return 0;
};