#include <iostream>
#include <allegro5\allegro.h>
#include "EDAlist.h"
#include "EDAlist.cpp"
#include <iostream>

using namespace std;

int main()
{
	EDAlist<char> list;

	list.addElement('h', list.getSize());
	list.addElement('o', list.getSize());
	list.addElement('l', list.getSize());
	list.addElement('a', list.getSize());
	list.addElement(' ', list.getSize());
	list.addElement('m', list.getSize());
	list.addElement('u', list.getSize());
	list.addElement('n', list.getSize());
	list.addElement('d', list.getSize());
	list.addElement('o', list.getSize());

	list.addElement('X', 0);

	list.print();
	for (int i = 1; i; i++) {};
	return 0;
}