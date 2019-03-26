/**
 * \file GameBoard.cpp
 * \author Harsh Patel
 */


#include "GameBoard.h"
#include <iostream>
#include <vector>
using namespace std;

BoardT::BoardT(vector<CardT> deck) {
	CardStackT CardStack(deck);
	vector<CardT> empty;

	this->W = CardStackT(empty);
	this->T = tab_deck(deck);
	this->F = init_seq(8);

	for (int i = 40; i < 104; i++) {
		D = (this->D).push(deck[i]);
	}

	if (!(two_decks(init_seq(10), init_seq(8), CardStack, W))) {
		throw invalid_argument("Game does not have two decks.");
	}
}


bool BoardT::is_valid_tab_mv(CategoryT c, nat n1, nat n2) {
	if (c == Tableau) {
		if (!(is_valid_pos(Tableau, n1) && is_valid_pos(Tableau, n2))) {
			throw out_of_range("Position of Tableau is not in range from 0 to 9.");
		}
		return valid_tab_tab(n1, n2);
	}
	else if (c == Foundation) {
		if (!(is_valid_pos(Tableau, n1) && is_valid_pos(Foundation, n2))) {
			throw out_of_range("Position of Tableau or Foundation is not in range.");
		}
		return valid_tab_foundation(n1, n2);
	}
	else {
		return false;
	}
}

bool BoardT::is_valid_waste_mv(CategoryT c, nat n) {
	if (W.size() == 0) {
		throw invalid_argument("Waste is currently empty.");
	}
	if (c == Tableau) {
		if (!(is_valid_pos(Tableau, n))) {
			throw out_of_range("Tableau position entered is out of range.");
		}
		return valid_waste_tab(n);
	}
	else if (c == Foundation) {
		if (!(is_valid_pos(Foundation, n))) {
			throw out_of_range("Foundation position entered is out of range.");
		}
		return valid_waste_foundation(n);
	}
	else {
		return false;
	}
}

bool BoardT::is_valid_deck_mv() {
	return (D).size() > 0;
}

void BoardT::tab_mv(CategoryT c, nat n1, nat n2) {
	if (!(is_valid_tab_mv(c, n1, n2))) {
		throw invalid_argument("Tableau move is illeagal.");
	}
	else {
		if (c == Tableau) {
			(T)[n2] = (T)[n2].push((T)[n1].top());
			(T)[n1] = (T)[n1].pop();
		}
		else if (c == Foundation) {
			(T)[n2] = (F)[n2].push((T)[n1].top());
			(F)[n1] = (T)[n1].pop();
		}
	}
}

void BoardT::waste_mv(CategoryT c, nat n) {
	if (!(is_valid_waste_mv(c, n))) {
		throw invalid_argument("Not a valid waste move.");
	}
	else {
		if (c == Tableau) {
			(T)[n] = (T)[n].push((W).top());
			(W) = (W).pop();
		}
		else if (c == Foundation) {
			(F)[n] = (F)[n].push((W).top());
			(W) = (W).pop();
		}
	}
}

void BoardT::deck_mv() {
	if(!(is_valid_deck_mv())){
		throw invalid_argument("Not a valid deck move.");
	}
	W = (W).push(D.top());
	D = (D).pop();
}

CardStackT BoardT::get_tab(nat i) {
	if (!(is_valid_pos(Tableau, i))) {
		throw out_of_range("Tableau position selected is out of range.");
	}
	return (T)[i];
}

CardStackT BoardT::get_foundation(nat i) {
	if (!(is_valid_pos(Foundation, i))) {
		throw out_of_range("Foundation position selected is out of range.");
	}
	return (F)[i];
}

CardStackT BoardT::get_deck() {
	return (D);
}

CardStackT BoardT::get_waste() {
	return (W);
}

bool BoardT::valid_mv_exists() {
	if (is_valid_deck_mv() == true) {
		return true;
	}
	bool valid_tab_mv = false;
	bool valid_waste_mv = false;

	const CategoryT arr[] = { Tableau, Foundation };

	for (CategoryT i : arr) {
		for (int j = 0; j < 10; j++) {

			for (int h = 0; h < 10; h++) {
				if (is_valid_pos(Tableau, static_cast<nat> (j)) && is_valid_pos(i, static_cast<nat> (h))) {
					valid_tab_mv = is_valid_tab_mv(i, static_cast<nat> (j), static_cast<nat> (h));
					if (valid_tab_mv == true) {
						return true;
					}
				}
			}

			if (is_valid_pos(i, static_cast<nat>(j))) {
				valid_waste_mv = is_valid_waste_mv(i, j);

				if (valid_waste_mv == true) {
					return true;
				}
			}
		}
	}

	return false;
}

bool BoardT::is_win_state() {
	for (int i = 0; i < 7; i++) {
		if (!(((F)[i].size() > 0) && ((F)[i].top().r == KING))) {
			return false;
		}
	}
	return true;
}

//Local functions
bool BoardT::two_decks(SeqCrdStckT T, SeqCrdStckT F, CardStackT D, CardStackT W) {
	const SuitT suit[] = { Heart, Diamond, Club, Spade };

	for (nat i = ACE; i <= KING; i++) {
		int countPair = 0;
		for (SuitT j : suit) {

			//Check Tableau
			for (nat t = 0; t < 10; t++) {
				vector<CardT> tab = T[t].toSeq();
				for (CardT card : tab) {
					if (card.r == i && card.s == j) {
						countPair++;
					}
				}
			}

			//Check Foundation
			for (nat f = 0; f < 8; f++) {
				vector<CardT> found = F[f].toSeq();
				for (CardT card : found) {
					if (card.r == i && card.s == j) {
						countPair++;
					}
				}
			}

			//Check Deck
			for (CardT card : D.toSeq()) {
				if (card.r == i && card.s == j) {
					countPair++;
				}
			}

			//Check Waste
			for (CardT card : W.toSeq()) {
				if (card.r == i && card.s == j) {
					countPair++;
				}
			}

		}
		if (countPair != 8) {
			return false;
		}
	}
	return true;
}

SeqCrdStckT BoardT::init_seq(nat n) {
	SeqCrdStckT s;
	for (nat i = 0; i < n; i++) {
		s.push_back(CardStackT());
	}
	return s;
}

SeqCrdStckT BoardT::tab_deck(vector<CardT> deck) {
	SeqCrdStckT T;
	for (nat i = 0; i < 10; i++) {
		CardStackT tab;
		for (nat j = 0; j < 4; j++) {
			tab = tab.push(deck[4 * i + j]);
		}
		T.push_back(tab);
	}
	return T;
}

bool BoardT::is_valid_pos(CategoryT c, nat n) {
	if (c == Tableau) {
		if (n <= 9) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (c == Foundation) {
		if (n <= 7) {
			return true;
		}
		else {
			return false;
		}
	}
	return true;

}

bool BoardT::valid_tab_tab(nat n1, nat n2) {
	if (T[n1].size() > 0) {
		if (T[n2].size() > 0) {
			return tab_placeable(T[n1].top(), T[n2].top());
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

bool BoardT::valid_tab_foundation(nat n1, nat n2) {
	if (T[n1].size() > 0) {
		if (F[n2].size() > 0) {
			return foundation_placeable(T[n1].top(), F[n2].top());
		}
		else {
			return (T[n1].top().r == ACE);
		}
	}
	else {
		return false;
	}
}

bool BoardT::valid_waste_tab(nat n) {
	if (T[n].size() > 0) {
		return tab_placeable(W.top(), T[n].top());
	}
	return true;
}

bool BoardT::valid_waste_foundation(nat n) {
	if (F[n].size() > 0) {
		return foundation_placeable(W.top(), F[n].top());
	}
	return (W.top().r == ACE);
}

bool BoardT::tab_placeable(CardT c, CardT d) {
	return ((c.s == d.s) && (c.r == (d.r - 1)));
}

bool BoardT::foundation_placeable(CardT c, CardT d) {
	return ((c.s == d.s) && (c.r == (d.r + 1)));
}


