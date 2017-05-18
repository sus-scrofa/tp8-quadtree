#pragma once
#include <iostream>

#define DEBUG

template <typename T> class EDAlist
{
public:
	EDAlist() { size = 0; firstNode = lastNode = nullptr; }
	void addElement(T element, unsigned long position);
	void removeElement(unsigned long position);
	T getElement(unsigned long position);
	unsigned int getSize();
#ifdef DEBUG
	void print();
#endif // DEBUG

private:
	template <typename T> struct Node
	{
		T data;
		Node * nextNode;
	};
	Node <T> * firstNode;
	Node <T> * lastNode;
	unsigned long size;
};

