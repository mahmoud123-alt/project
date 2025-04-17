//	This is an updated version of code originally
//  created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT stack: Array-based implementation.
 @file ArrayStack.h */

#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include "StackADT.h"
#include "iostream"
using namespace std;
 //Unless spesificed by the stack user, the default size is 100
template<typename T>
class ArrayStack : public StackADT<T>
{
	enum { MAX_SIZE = 100 };
private:
	T items[MAX_SIZE];		// Array of stack items
	int top;

protected:
	                 // Index to top of stack
	int count;//same as top + 1
public:

	ArrayStack():count(0)
	{
		top = -1;
	}  // end default constructor

	bool isEmpty() const
	{
		return top == -1;
	}  // end isEmpty

	bool push(const T& newEntry)
	{
		if (top == MAX_SIZE - 1) return false;	//Stack is FULL

		top++;
		items[top] = newEntry;
		count++;
		return true;
	}  // end push

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		top--;
		count--;
		return true;
	}  // end pop

	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		return true;
	}  // end peek
	void print() const
	{
		// or top + 1
		for (int i = 0;i < count;i++)
		{
			if (i == count - 1) {
				cout << items[i];
				continue;
		}

			cout << items[i]<<", ";
		} 
		cout << "\n";
	}
	int get_count() const {
		return count;

	}
	void decCount()
	{
		if (count == 0)
			return;
		count--;
	}



}; // end ArrayStack

#endif
