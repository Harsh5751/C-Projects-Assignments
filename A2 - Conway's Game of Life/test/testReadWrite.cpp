//Harsh Patel
#include <algorithm>
#include <iostream>
#include <vector>

#include "Gameboard.h"
#include "GameboardTypes.h"
#include "ReadWrite.h"
#include "catch.h"

using namespace std;
// Tests if vectors are equal
bool sameVector(vector<char> v1, vector<char> v2) {
	if (v1.size() != v2.size()) {
		return false;
	}
	for (unsigned int i = 0; i < v1.size(); i++) {
		if (v1[i] != v2[i]) {
			return false;
		}
	}
	return true;
}

TEST_CASE("tests for ReadWrite", "[ReadWrite]") {
	SECTION("Read returns correct vector") {
		vector<char> fileContent = readFile("Initial_Universe.txt");
		vector<char> fileCopy = {'-', '*', '-', '-', '*', '*', '-', '-', '-', '-', '-', '*', '-', '*', '-', '*'};
		REQUIRE(sameVector(fileContent, fileCopy));
	}

	SECTION("When file not found raise exception") {
		REQUIRE_THROWS_AS(readFile("NOT_HERE.txt"), runtime_error);
	}

	SECTION("Writing to file has correct state to file") {
		boardUniverse boardT("Initial_Universe.txt");
		writeFile("TestWrite.txt", boardT.getUniverse());
		vector<char> fileContent = readFile("TestWrite.txt");
		vector<char> fileCopy = { '-', '*', '-', '-', '*', '*', '-', '-', '-', '-', '-', '*', '-', '*', '-', '*' };
		REQUIRE(sameVector(fileContent, fileCopy));
	}

}