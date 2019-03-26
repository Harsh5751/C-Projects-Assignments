/**
 * \file Stack.h
 * \author Harsh Patel
 * \brief Provides an abstract data type (ADT) for a first-in-last-out data
 *   structure to store a sequence of a certain type.
 */

#ifndef A3_STACK_H_
#define A3_STACK_H_

#include <vector>
#include <iostream>
#include "CardTypes.h"

 /**
  * \type definition of unsigned int to nat (natural number).
  */
typedef unsigned int nat;

/**
 * \brief ADT for a first-in-last-out data structure using vector.
 */
template<class T>
class Stack {
	private:
		std::vector<T> S;
	public:
		/**
		 * \brief Default constructor for Stack. This Stack cannot take any
		 * parameters.
		 *
		 * \details This is a needed to inialize an empty stacks for gameboard setup. 
		 */
		Stack();

		/**
		 * \brief Constructs a new Stack instance with a sequence vector.
		 * \param s A vector of type T used to represent the sequence of the stack.
		 */
		Stack(std::vector<T> s);

		/**
		 * \brief Adds an item to the top of the stack.
		 * \param e The item of type T to add to the top of the stack.
		 * \returns A new stack with the added element at the top.
		 */
		Stack push(T e);

		/**
		 * \brief Removes the element that is at the top of the stack.
		 * \throws out_of_range if the stack does not contain any items.
		 * \returns A new stack with the element at the top removed.
		 */
		Stack pop();

		/**
		 * \brief Retrieves the top element on the stack.
		 * \throws out_of_range if the stack does not contain any items.
		 * \returns The element of type T on the top of the stack.
		 */
		T top();

		/**
		 * \brief Returns number of elements in the stack sequence.
		 * \returns Size of the stack. Number of elements in the stack.
		 */
		nat size();

		/**
		 * \brief Returns a sequence of the members of this stack.
		 * \returns The sequence fn the stack.
		 */
		std::vector<T> toSeq();
};
#endif
