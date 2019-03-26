/**
 * \file CardTypes.h
 * \author Harsh Patel
 * \brief Provides type definition and enumerations for a game forty thieves.
 */

#ifndef A3_CARD_TYPES_H_
#define A3_CARD_TYPES_H_

/**
 * \brief Describes the rank of a card.
 */
typedef unsigned short int RankT;

/**
 * \brief RankT for an Ace.
 */
#define ACE    1

/**
 * \brief RankT for an Jack.
 */
#define JACK   11

/**
 * \brief RankT for a Queen.
 */
#define QUEEN  12

/**
 * \brief RankT for a King.
 */
#define KING   13

/**
 * \brief total cards in the game.
 */
#define TOTAL_CARDS  104;

 /**
  * \brief Possible card suits.
  */
enum SuitT { Heart, Diamond, Club, Spade };

/**
 * \brief Describes the valid types of columns of cards on the board.
 */
enum CategoryT { Tableau, Foundation, Deck, Waste };

/**
 * \brief Structure of a Card
 */
struct CardT
{
	SuitT s;
	RankT r;
};

#endif
