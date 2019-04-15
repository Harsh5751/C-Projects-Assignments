/**
 * \file ReadWrite.cpp
 * \author Harsh Patel
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "ReadWrite.h"

using namespace std;

vector<char> readFile(string f) {
	vector<char> data;
	char s;
	ifstream file_(f);
	if (!(file_)) {
		throw runtime_error("File not found");
	}
	if (file_.is_open()) {
		while (file_ >> s) {
			data.push_back(s);
		}
		file_.close();
	}
	return data;
}

void writeFile(string f, vector<vector<CellT>> s) {

	ofstream myFile(f);
	if (!(myFile)) {
		throw runtime_error("File not found");
	}
	for (unsigned int i = 0; i < s.size(); i++) {
		for (unsigned int j = 0; j < s.size(); j++) {
			if (j == s.size() - 1) {
				if (s[i][j] == Dead) {
					myFile << "-\n";
				}
				else {
					myFile << "*\n";
				}
			}
			else {
				if (s[i][j] == Dead) {
					myFile << "- ";
				}
				else {
					myFile << "* ";
				}
			}
		}
	}
	myFile.close();
	cout << endl;
	cout << "The current Generation of grid/universe has been written to output.txt" << endl;
	cout << endl;
}
