#ifndef UTStack_h
#define UTStack_h

#include <cstdlib>
using namespace std;

// define default capacity of stack
#define SIZE 10

// Class for stack
template <class X>
class UTStack
{
	X *arr;
	int top;
	int capacity;

public:
	UTStack(int size = SIZE);	// constructor

	void push(X);
	X pop();
	X peek();

	int size();
	bool isEmpty();
	bool isFull();

	const X& getAll();
};

#endif