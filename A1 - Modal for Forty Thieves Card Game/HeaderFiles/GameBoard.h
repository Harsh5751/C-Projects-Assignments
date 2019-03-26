/**
 * \file GameBoard.h
 * \author Harsh Patel
 * \brief Provides an ADT representing a model for the game of Forty Thieves.
 *   including game board state and its transitions.
 */

#ifndef A3_GAME_BOARD_H_
#define A3_GAME_BOARD_H_

#include "CardStack.h"
#include "CardTypes.h"
#include <vector>
#include <iostream>

typedef std::vector<CardStackT> SeqCrdStckT;

 /**
  * \brief Represents the state of a Forty Thieves game.
  * \details The board consists of card stacks and sequences of card stacks
  *   from which inidvidual cards can be moved depending on the state of other card stacks.
  */
class BoardT {
	private:
		SeqCrdStckT T;
		SeqCrdStckT F;
		CardStackT D;
		CardStackT W;

		//Local Functions

		/**
		 * \brief Determines whether the total cards in the game consist of 104 cards
		 *   with each suit and rank appearing twice in the deck.
		 */
		bool two_decks(SeqCrdStckT T, SeqCrdStckT F, CardStackT D, CardStackT W);

		/**
		 * \brief Initializes a sequence of card stacks with a given capacity
		 *   for the gameboard setup.
		 */
		SeqCrdStckT init_seq(nat n);

		/**
		 * \brief Fills the Tableau component of the gameboard with forty cards.
		 *   Four cards are placed on each of the 10 stacks in the seqeunce.
		 */
		SeqCrdStckT tab_deck(std::vector<CardT> deck);

		/**
		 * \brief Determines whether the position card being placed is within the 
		 *   the size of the Foundation and Tableau.
		 */
		bool is_valid_pos(CategoryT c, nat n);

		/**
		 * \brief Checks if its possible to move a card from one stack in 
		 *   the tableau to another stack in the tableau. 
		 */
		bool valid_tab_tab(nat n1, nat n2);

		/**
		 * \brief Checks if its possible to move a card from the Tableau to 
		 *   the Foundation.
		 */
		bool valid_tab_foundation(nat n1, nat n2);

		/**
		 * \brief Determines whether its possible to move a card from the Waste
		 *   to the Tableau.
		 */
		bool valid_waste_tab(nat n);

		/**
		 * \brief Determines whether its possible to move a card from the Waste to 
		 *   the Foundation.
		 */
		bool valid_waste_foundation(nat n);

		/**
		 * \brief Determines whether a card is placeable on a stack of the Tableau.
		 */
		bool tab_placeable(CardT c, CardT d);

		/**
		 * \brief Determines whether a card is placeable on a stack of the Foundation.
		 */
		bool foundation_placeable(CardT c, CardT d);

	public:
		/**
		* \brief Constructs a new GameT instance with a given board state.
		* \param deck Vector sequence of type cardT repreenting the game deck.
		* \throws invalid_argument If there aren't two decks used in the game.
		*/
		BoardT(std::vector<CardT> deck);

		/**
		* \brief Checks if a Tableau move is possible.
		* \param c Represents the category of the game to check such as Foundation or Tableau.
		* \param n1 Represents card stack of the card being moved.
		* \param n2 Position of the card stack to which the card is being moved to.
		* \throws out_of_range if position of card stack which the card is in
		*   and position of card stack which the card is being moved to is not in
		*   in the sequence of cardstacks.
		* \returns Boolean representing if the move is valid. 
		*/
		bool is_valid_tab_mv(CategoryT c, nat n1, nat n2);


		/**
		* \brief Checks if its possible to move a card from Waste to Foundation or Tableau.
		* \param c Represents the category of the game to check such as Foundation or Tableau.
		* \param n Position of the card stack to which the card is being moved to in Foundation or Tableau.
		* \throws out_of_range if position of card stack which the card is in
		*   and position of card stack which the card is being moved to is not in
		*   in the sequence of cardstacks.
		* \throws invalid_argument If Waste stack is empty
		* \returns Boolean representing if the move is valid.
		*/
		bool is_valid_waste_mv(CategoryT c, nat n);

		/**
		* \brief Checks if a deck move of moving card from Deck to Waste is possibe.
		* \returns Boolean representing if the move is valid if deck size is more than 0.
		*/
		bool is_valid_deck_mv();

		/**
		* \brief Moves Card from one position of tableau to another position of the Tableau or Foundation.
		* \param c Represents the category of the game to check such as Foundation or Tableau.
		* \param n1 Represents card stack of the card being moved.
		* \param n2 Position of the card stack to which the card is being moved to.
		* \throws out_of_range if position of card stack which the card is in
		*   and position of card stack which the card is being moved to is not in
		*   in the sequence of cardstacks.
		* \throws invalid_argument If a valid Tableau moves returns False.
		*/
		void tab_mv(CategoryT c, nat n1, nat n2);

		/**
		* \brief Moves Card from Waste stack to a stack position of the Tableau or Foundation.
		* \param c Represents the category of the game to check such as Foundation or Tableau.
		* \param n Position of Foundation or Tableau stack to which the card is being moved to.
		* \throws out_of_range if position of card stack which the card is in
		*   and position of card stack which the card is being moved to is not in
		*   in the sequence of cardstacks.
		* \throws invalid_argument If a valid waste move is not possible.
		*/
		void waste_mv(CategoryT c, nat n);

		/**
		* \brief Moves Card from Deck stack to the Waste stack.
		* \throws invalid_argument If a valid deck move is not possible(deck empty).
		*/
		void deck_mv();

		/**
		* \brief Gets stack of cards at position i in Tableau.
		* \param i Position of the card stack to be returned.
		* \throws out_of_range If  postion i is not in range of 0 to 9.
		* \returns Card stack at position i of the Tableau.
		*/
		CardStackT get_tab(nat i);

		/**
		* \brief Gets stack of cards at position i in Foundation.
		* \param i Position of the card stack to be returned.
		* \throws out_of_range If  postion i is not in range of 0 to 7.
		* \returns Card stack at position i of the Foundation.
		*/
		CardStackT get_foundation(nat i);

		/**
		* \brief Gets stack of cards representing the Deck.
		* \returns Card stack of the Deck.
		*/
		CardStackT get_deck();

		/**
		* \brief Gets stack of cards representing the waste.
		* \returns Card stack of the waste.
		*/
		CardStackT get_waste();

		/**
		* \brief Checks if a valid move on the gameboard exists. 
		* \details Checks Foundation, Tableau, and Waste to see if a valid 
		*   move exists of changing the states of Foundation, Waste, or Tableau.
		* \returns Boolean indicating if the game has been won.
		*/
		bool valid_mv_exists();

		/**
		* \brief Checks if the player has won the game.
		* \details Checks each of the stacks in Foundation to see if the 
		*   stacks are more than size 0, and the top card of each stack is
		*   of rank King.
		* \returns Boolean indicating if the game has been won.
		*/
		bool is_win_state();
};
#endif
