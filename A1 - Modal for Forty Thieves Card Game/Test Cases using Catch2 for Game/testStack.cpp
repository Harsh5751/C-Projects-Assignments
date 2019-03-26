//Harsh Patel
#include "catch.h"

#include "Stack.h"
#include "CardTypes.h"
#include "CardStack.h"

#include <vector>
#include <iostream>

//Compares two cards to see if they are the same
bool structCardEquals(CardT card1, CardT card2) {
	if ((card1.r == card2.r) && (card2.s == card1.s)) {
		return true;
	}
	return false;
}

TEST_CASE("tests for Stack", "[Stack]") {

	//Test Empty Constructor
	SECTION("Test Constructor builds Empty Stack; Empty Vector") {
		//An empty vector
		std::vector<CardT> CardSeq;
		//An empty vector in a stack = empty stack
		CardStackT cardStack(CardSeq);

		//Test size of vector and stack to see if its empty
		REQUIRE(CardSeq.size() == 0);
		REQUIRE(cardStack.size() == 0);
	}

	//Initialize and push a card
	SECTION("Push one card onto the stack") {
		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);
		CardStackT cardStack2 = cardStack.push({ Diamond, 3 });
		
		//top card = pushed card
		REQUIRE(structCardEquals(CardT{Diamond, 3}, cardStack2.top()));
	}

	SECTION("Push multiple cards onto the stack") {
		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };
		CardT card3{ Spade, QUEEN };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT c1 = cardStack.push(card1);
		CardStackT c2 = c1.push(card2);
		CardStackT finalStack = c2.push(card3);
		

		//test top card of stack to see if it is equal to last one pushed
		REQUIRE(structCardEquals(card3, finalStack.top()));

	}


	SECTION("test push does not change original stack's size") {
		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };
		CardT card3{ Spade, QUEEN };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT c1 = cardStack.push(card1);
		REQUIRE(c1.size() == 1);
		CardStackT c2 = c1.push(card2);
		REQUIRE(c1.size() == 1);
		CardStackT finalStack = c2.push(card3);
		REQUIRE(c1.size() == 1);

		REQUIRE(finalStack.size() == 3);
		REQUIRE(c1.size() == 1);
		REQUIRE(c2.size() == 2);
	}

	SECTION("test push increases size of new object") {
		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };
		CardT card3{ Spade, QUEEN };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT c1 = cardStack.push(card1);
		CardStackT c2 = c1.push(card2);
		CardStackT finalStack = c2.push(card3);

		REQUIRE(finalStack.size() == 3);
		REQUIRE(c1.size() == 1);
		REQUIRE(c2.size() == 2);
	
	}

	SECTION("test push changes top of new stack") {
		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };
		CardT card3{ Spade, QUEEN };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT c1 = cardStack.push(card1);
		REQUIRE(structCardEquals(card1, c1.top()));
		CardStackT c2 = c1.push(card2);
		REQUIRE(structCardEquals(card2, c2.top()));
		CardStackT finalStack = c2.push(card3);
		REQUIRE(structCardEquals(card3, finalStack.top()));
	}

	SECTION("test push does not change top of original stack") {
		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };
		CardT card3{ Spade, QUEEN };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT c1 = cardStack.push(card1);
		REQUIRE(structCardEquals(card1, c1.top()));
		CardStackT c2 = c1.push(card2);
		REQUIRE(structCardEquals(card1, c1.top()));
		CardStackT finalStack = c2.push(card3);
		REQUIRE(structCardEquals(card1, c1.top()));
	
	}

	SECTION("Calling only .push doesn't push card to stack") {
		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };
		CardT card3{ Spade, QUEEN };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT c1 = cardStack.push(card1);
		c1.push(card2);
		REQUIRE(structCardEquals(card1, c1.top()));
	}

	SECTION("Pop stack with one card to return empty stack") {
		CardT card1{ Diamond, 3 };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push card onto stack and pop the same card
		cardStack = cardStack.push(card1);
		cardStack = cardStack.pop();

		REQUIRE(cardStack.size() == 0);
	}

	SECTION("Pop stack with multiple cards to return stack of size") {
		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };
		CardT card3{ Spade, QUEEN };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT cardStack2 = cardStack.push(card1);
		CardStackT cardStack3 = cardStack2.push(card2);
		CardStackT cardStack4 = cardStack3.push(card3);

		//pop cards
		CardStackT cardPop = cardStack4.pop();
		CardStackT cardPop2 = cardPop.pop(); 

		//Check size after popping
		REQUIRE(cardPop2.size() == 1);
		
		//Check top card after pop
		REQUIRE(structCardEquals(cardPop2.top(), card1));
	}

	SECTION("test pop changes top of new stack") {
		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };
		CardT card3{ Spade, QUEEN };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT cardStack2 = cardStack.push(card1);
		CardStackT cardStack3 = cardStack2.push(card2);
		CardStackT cardStack4 = cardStack3.push(card3);

		//pop cards
		REQUIRE(structCardEquals(cardStack4.top(), card3));
		CardStackT cardPop = cardStack4.pop();
		REQUIRE(structCardEquals(cardPop.top(), card2));
		CardStackT cardPop2 = cardPop.pop();
		REQUIRE(structCardEquals(cardPop2.top(), card1));
	
	}

	SECTION("test pop decreases size of new stack") {
		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };
		CardT card3{ Spade, QUEEN };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT cardStack2 = cardStack.push(card1);
		CardStackT cardStack3 = cardStack2.push(card2);
		CardStackT cardStack4 = cardStack3.push(card3);

		//pop cards
		REQUIRE(cardStack4.size() == 3);
		CardStackT cardPop = cardStack4.pop();
		REQUIRE(cardPop.size() == 2);
		CardStackT cardPop2 = cardPop.pop();
		REQUIRE(cardPop2.size() == 1);
	}

	SECTION("Calling only .pop doesn't pop card to stack") {
		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };
		CardT card3{ Spade, QUEEN };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT cardStack2 = cardStack.push(card1);
		CardStackT cardStack3 = cardStack2.push(card2);
		CardStackT cardStack4 = cardStack3.push(card3);

		//pop cards
		cardStack4.pop();
		REQUIRE(!(structCardEquals(cardStack4.top(), card2)));
	
	}

	SECTION("Pop from empty stack to return exception") {
		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		REQUIRE_THROWS_AS(cardStack.pop(), std::out_of_range);
	}

	SECTION("test pop does not change original stack's size") {
		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };
		CardT card3{ Spade, QUEEN };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT cardStack2 = cardStack.push(card1);
		CardStackT cardStack3 = cardStack2.push(card2);
		CardStackT cardStack4 = cardStack3.push(card3);

		//pop cards
		CardStackT cardPop = cardStack4.pop();
		REQUIRE(cardStack4.size() == 3);
		CardStackT cardPop2 = cardPop.pop();
		REQUIRE(cardPop.size() == 2);
	
	
	}

	SECTION("Keep poping until stack is empty and raise exception") {
		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT cardStack2 = cardStack.push(card1);
		CardStackT cardStack3 = cardStack2.push(card2);

		//pop cards
		CardStackT cardPop = cardStack3.pop();
		CardStackT cardPop2 = cardPop.pop();

		REQUIRE_THROWS_AS(cardPop2.pop(), std::out_of_range);
	}

	SECTION("Check top card of Stack with one card") {
		//Define cards
		CardT card1{ Diamond, ACE };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT cardStack2 = cardStack.push(card1);

		REQUIRE(structCardEquals(card1, cardStack2.top()));
	}

	SECTION("Top of an empty Stack") {
		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		REQUIRE_THROWS_AS(cardStack.top(), std::out_of_range);
	}

	SECTION("Size of Stack") {
		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };
		CardT card3{ Spade, QUEEN };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT cardStack2 = cardStack.push(card1);
		CardStackT cardStack3 = cardStack2.push(card2);
		CardStackT cardStack4 = cardStack3.push(card3);

		REQUIRE(cardStack4.size() == 3);
	}

	SECTION("Size of Empty Stack") {
		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		REQUIRE(cardStack.size() == 0);
	}

	SECTION("test toSeq returns correct sequence") {

		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };
		CardT card3{ Spade, QUEEN };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT cardStack2 = cardStack.push(card1);
		CardStackT cardStack3 = cardStack2.push(card2);
		CardStackT cardStack4 = cardStack3.push(card3);

		//
		std::vector<CardT> Seq = cardStack4.toSeq();

		REQUIRE(structCardEquals(Seq[0], card1));
		REQUIRE(structCardEquals(Seq[1], card2));
		REQUIRE(structCardEquals(Seq[2], card3));
	}

	SECTION("test Sequence of new Stack not same as old Stack") {
		//Define cards
		CardT card1{ Diamond, ACE };
		CardT card2{ Heart, KING };
		CardT card3{ Spade, QUEEN };

		std::vector<CardT> CardSeq;
		CardStackT cardStack(CardSeq);

		//push the cards
		CardStackT cardStack2 = cardStack.push(card1);
		CardStackT cardStack3 = cardStack2.push(card2);
		CardStackT cardStack4 = cardStack3.push(card3);

		//
		std::vector<CardT> Seq = cardStack4.toSeq();
		std::vector<CardT> Seq2 = cardStack3.toSeq();

		REQUIRE(!(structCardEquals(cardStack4.top(), cardStack3.top())));
	}
}


