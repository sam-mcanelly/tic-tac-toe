/****************************************
 * 
 * Ultrasonic Flaw Detector - UTStack
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 ****************************************/

#include "UTStack.h"

// Constructor to initialize stack
template <class X>
UTStack<X>::UTStack(int size)
{
	arr = new X[size];
	capacity = size;
	top = -1;
}

// function to add an element x in the stack
template <class X>
void UTStack<X>::push(X x)
{
	if (isFull())
	{
		exit(EXIT_FAILURE);
	}
	arr[++top] = x;
}

// function to pop top element from the stack
template <class X>
X UTStack<X>::pop()
{
	// check for stack underflow
	if (isEmpty())
	{
		exit(EXIT_FAILURE);
	}

	// decrease stack size by 1 and (optionally) return the popped element
	return arr[top--];
}

// function to return top element in a stack
template <class X>
X UTStack<X>::peek()
{
	if (!isEmpty())
		return arr[top];
	else
		exit(EXIT_FAILURE);
}

// Utility function to return the size of the stack
template <class X>
int UTStack<X>::size()
{
	return top + 1;
}

// Utility function to check if the stack is empty or not
template <class X>
bool UTStack<X>::isEmpty()
{
	return top == -1;	// or return size() == 0;
}

// Utility function to check if the stack is full or not
template <class X>
bool UTStack<X>::isFull()
{
	return top == capacity - 1;	// or return size() == capacity;
}

template <class X>
const X& UTStack<X>::getAll() {
	return arr;
}
