/**
 * \file DisplayGen.cpp
 * \author Harsh Patel
 */

#include <iostream>
#include <vector>
#include "DisplayGen.h"

using namespace std;

void showUniverse(vector<vector<CellT>> Universe) {
	
	cout << "This is the current Generation of Grid/Universe " << endl;
	
	for (unsigned int i = 0; i < Universe.size(); i++) {
		for (unsigned int j = 0; j < Universe.size(); j++) {
			if (j == (Universe.size() - 1)) {
				if (Universe[i][j] == Alive) {
					cout << "*" << endl;
				}
				else if (Universe[i][j] == Dead) {
					cout << "-" << endl;
				}
			}
			else {
				if (Universe[i][j] == Alive) {
					cout << "* ";
				}
				else if (Universe[i][j] == Dead) {
					cout << "- ";
				}
			}
		}
	}
}

