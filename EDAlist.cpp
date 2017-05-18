#include "EDAlist.h"

using namespace std;

template<typename T>
void EDAlist<T>::addElement(T element, unsigned long position)
{
	if (position <= size)
	{
		if (firstNode == nullptr)
		{
			Node <T> * tempNode = new Node <T>;
			tempNode->data = element;
			tempNode->nextNode = nullptr;
			firstNode = lastNode = tempNode;	//lo de lastNode es dudoso, chequear
		}
		else
		{
			if (position > 0)	//si no se eligio la primer posicion
			{
				Node <T> * currentNode = firstNode;
				for (int i = 1; i < position; i++)
					currentNode = currentNode->nextNode;
				Node <T> * tempNode = new Node<T>;
				tempNode->nextNode = currentNode->nextNode;
				currentNode->nextNode = tempNode;
				tempNode->data = element;
				if (position == size)
					lastNode = tempNode;
			}
			else	//si se eligio la primer posicion
					//esto no esta copiado de agustin, CHEQUEAR
			{
				Node <T> * tempNode = new Node <T>;
				tempNode->data = element;
				tempNode->nextNode = firstNode;
				firstNode = tempNode;
			}
		}
		size++;
	}
	else
	{
		//LOCO FLASHEASTE CON LA POSICION
	}
}

template<typename T>
void EDAlist<T>::removeElement(unsigned long position) 
{
	if (position < size) 
	{
		Node <T> * currentNode = firstNode;
		if (position > 0)
		{
			for (int j = 0; j < (position - 1); j++)	//moverse hasta el nodo anterior del nodo a eliminar
				currentNode = currentNode->nextNode;
			Node <T> * deleteNode = currentNode->nextNode;	//puntero al nodo a eliminar
			currentNode->nextNode = deleteNode->nextNode;	//"saltearse" el nodo a eliminar con el puntero del nodo anterior
			delete deleteNode;
			if (position == size)
				lastNode = currentNode;	//si se elimino al ultimo, lastNode debe apuntar al anterior.
		}
		else	//si position == 0
		{
			currentNode = firstNode;
			firstNode = firstNode->nextNode;
			delete currentNode;
		}
		size--;
	}
	else 
	{
		//GIL QUERES ELIMINAR ALGO QUE NO EXISTE
	}
}

template<typename T>
T EDAlist<T>::getElement(unsigned long position) 
{
	Node <T> * currentNode = firstNode;

	if (position < size)
	{
		for (int k = 0; k < position; k++)		//moverse hasta el nodo correspondiente
			currentNode = currentNode->nextNode;
	}
	return currentNode->data;
}

template<typename T>
unsigned int EDAlist<T>::getSize() 
{ 
	return size; 
}

#ifdef DEBUG
template<typename T>
void EDAlist<T>::print()
{
	for (Node <T> * currentNode = firstNode; currentNode != nullptr; currentNode = currentNode->nextNode)
		cout << currentNode->data;

//	cout << "Size " << size << endl;
}
#endif // DEBUG