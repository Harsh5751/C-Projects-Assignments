/**
 * \file Stack.cpp
 * \author Harsh Patel
 */

#include "Stack.h"
#include <vector>
#include <iostream>

using namespace std;

//empty constructor
template <class T>
Stack<T>::Stack() {
}

//Constructs stack with vector<type>
template <class T>
Stack<T>::Stack(vector<T> s)
{
	this->S = s;
}

//Adds element <type> e to the top of the stack
template <class T>
Stack<T> Stack<T>::push(T e) {
	std::vector<T> new_(this->S);
	(new_).push_back(e);
	return Stack<T>(new_);
}

//Removes element at top of the stack
template <class T>
Stack<T> Stack<T>::pop() {
	//checks if Stack is empty
	if ((this->S).size() == 0) {
		throw out_of_range("Stack is empty. No elements to remove.");
	}
	std::vector<T> new_(this->S);
	(new_).pop_back();
	return Stack<T>(new_);
}

//Returns element at top of the stack
template <class T>
T Stack<T>::top() {
	//Checks if Stack is empty
	if ((this->S).size() == 0) {
		throw out_of_range("Stack is empty. No element at the top of the stack.");
	}
	return (this->S).back();
}

//Returns size of the stack
template <class T>
nat Stack<T>::size() {
	return (this->S).size();
}

//Returns the sequence used to represent the stack
template <class T>
vector<T> Stack<T>::toSeq() {
	return (this->S);
}

// Keep this at bottom
template class Stack<CardT>;
