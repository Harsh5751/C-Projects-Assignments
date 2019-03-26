//Harsh Patel
#include <algorithm>
#include <iostream>
#include <vector>

#include "CardStack.h"
#include "CardTypes.h"
#include "GameBoard.h"
#include "Stack.h"
#include "catch.h"

// Produce a new deck (consisting of two standard decks) and shuffle its
  // cards.

std::vector<CardT> InitializeDeck(std::vector<CardT> d) {
	for (RankT rank = ACE; rank <= KING; rank++) {
		for (unsigned int suit = 0; suit < 4; suit++) {
			CardT n = { static_cast<SuitT>(suit), rank };
			d.push_back(n);
			d.push_back(n);
		}
	}
	return d;
}

TEST_CASE("tests for GameBoard", "[GameBoard]") {
	
	SECTION("test size for Waste initialized to 0") {
		std::vector<CardT> d;
		std::vector<CardT> deck = InitializeDeck(d);

		BoardT board(deck);
		CardStackT W = board.get_waste(); 

		REQUIRE((W).size() == 0);
	}

	SECTION("test size for Deck initialized to size 40") {
		std::vector<CardT> d;
		std::vector<CardT> deck = InitializeDeck(d);

		BoardT board(deck);
		CardStackT D = board.get_deck();

		REQUIRE((D).size() == 64);
	}

	SECTION("test size of foundation and tableau stacks when initialized") {
		std::vector<CardT> d;
		std::vector<CardT> deck = InitializeDeck(d);

		BoardT board(deck);

		nat FoundStacks = 0;
		nat TabStacks = 0;

		for (nat i = 0; i < 10; i++) {
			if (i < 8) {
				CardStackT F = board.get_foundation(i);
				FoundStacks++;
			}
			CardStackT T = board.get_tab(i);
			TabStacks++;
		}
	
		REQUIRE(FoundStacks == 8);
		REQUIRE(TabStacks == 10);
	}

	SECTION("if Initialization of gameboard fills tableau with 40 cards") {
		nat tabCards = 0;
		std::vector<CardT> d;
		std::vector<CardT> deck = InitializeDeck(d);

		BoardT board(deck);

		nat i = 0;

		while (i < 10) {
			CardStackT T = board.get_tab(i);
			tabCards += T.size();
			i++;
		}

		REQUIRE(tabCards == 40);

	}
	
	SECTION("When Game doesn't has two decks so one card popped") {
		std::vector<CardT> d;
		std::vector<CardT> deck = InitializeDeck(d);

		deck.pop_back();

		REQUIRE_THROWS_AS(BoardT(deck), std::invalid_argument);
	
	}

	SECTION("Is valid tab move with Category with Tableau and move to another Tableau position") {
		std::vector<CardT> d;

		std::vector<CardT> deck = InitializeDeck(d);
		BoardT board(deck);

		//get tableau at positions
		CardStackT T1 = board.get_tab(1);
		CardStackT T3 = board.get_tab(3);

		//make and push appropriate cards onto Tableau to make game have valid tab move
		CardT card1{ Diamond, 2 };
		CardT card2{ Diamond, 3 };

		T1 = T1.push(card1);
		T3 = T3.push(card2);

		REQUIRE(board.is_valid_tab_mv(Tableau, 1, 3));
	}

	SECTION("Is valid tab move with Category with Foundation and move from Tableau to Foundation") {
		std::vector<CardT> d;

		std::vector<CardT> deck = InitializeDeck(d);
		BoardT board(deck);

		//get tableau and foundations positions
		CardStackT T1 = board.get_tab(1);
		CardStackT F3 = board.get_foundation(3);

		//make and push appropriate cards onto Tableau to make game have valid tab move
		CardT card1{ Diamond, ACE };
		CardT card2{ Diamond, 2 };

		T1 = T1.push(card2);
		F3 = F3.push(card1);

		REQUIRE(board.is_valid_tab_mv(Foundation, 1, 3));
	}

	SECTION("Tableau or Foundation positions are out of range") {
		std::vector<CardT> d;

		std::vector<CardT> deck = InitializeDeck(d);
		BoardT board(deck);
		
		REQUIRE_THROWS_AS(board.is_valid_tab_mv(Tableau, 99, 100), std::out_of_range);
		REQUIRE_THROWS_AS(board.is_valid_tab_mv(Foundation, 99, 100), std::out_of_range);
	}

	SECTION("Have Category be waste or deck should return false") {
		std::vector<CardT> d;

		std::vector<CardT> deck = InitializeDeck(d);
		BoardT board(deck);

		REQUIRE((board.is_valid_tab_mv(Deck, 0, 0)) == false);
		REQUIRE((board.is_valid_tab_mv(Waste, 0, 0)) == false);
	
	}
	
	SECTION("valid waste move when waste is empty should return exception") {
		std::vector<CardT> d;

		std::vector<CardT> deck = InitializeDeck(d);
		BoardT board(deck);

		REQUIRE_THROWS_AS(board.is_valid_waste_mv(Tableau, 0), std::invalid_argument);
	}

	SECTION("has valid move from waste to Tableau and foundation with range out of range") {
		std::vector<CardT> d;

		std::vector<CardT> deck = InitializeDeck(d);
		BoardT board(deck);

		board.deck_mv();

		REQUIRE_THROWS_AS(board.is_valid_waste_mv(Tableau, 11), std::out_of_range);
		REQUIRE_THROWS_AS(board.is_valid_waste_mv(Foundation, 11), std::out_of_range);
	
	}

	SECTION("TEST is valid deck to; deck size should be more then 0 even with a few moves") {
		std::vector<CardT> d;

		std::vector<CardT> deck = InitializeDeck(d);
		BoardT board(deck);

		board.deck_mv();
		board.deck_mv();

		REQUIRE(board.is_valid_deck_mv());
	
	}


	SECTION("Should not be win state") {
		std::vector<CardT> d;

		std::vector<CardT> deck = InitializeDeck(d);
		BoardT board(deck);
		
		REQUIRE(board.is_win_state() == false);
	
	}

	SECTION("Get Deck and Get Waste") {
		std::vector<CardT> d;

		std::vector<CardT> deck = InitializeDeck(d);
		BoardT board(deck);

		CardStackT D = board.get_deck();
		CardStackT W = board.get_waste();

		REQUIRE(D.size() == 64);
		REQUIRE(W.size() == 0);
	
	}
}
