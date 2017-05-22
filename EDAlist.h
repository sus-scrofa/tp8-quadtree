#pragma once
#include <iostream>

template <typename T> class EDAlist
{
public:

	EDAlist() 
	{ 
		size = 0; 
		firstNode = lastNode = nullptr; 
	}

	~EDAlist() 
	{
		removeAll();
	}

	/*****************************************************
	Funcion EDAlist::addElement
	Agrega un elemento del tipo T a la lista.

	Recibe:
	Referencia al elemento T a agregar
	unsigned long: posicion de la lista en donde agregar

	*****************************************************/
	void addElement(T& element, unsigned long position)
	{
		if (position <= size)
		{
			if (firstNode == nullptr)
			{
				Node <T> * tempNode = new Node <T>;
				tempNode->data = element;
				tempNode->nextNode = nullptr;
				firstNode = lastNode = tempNode;
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

	/*********************************************************************
	Funcion EDAlist::removeElement
	Elimina un elemento de la lista

	Recibe:
	unsigned long position: posicion del elemento que se quiere eliminar
	*********************************************************************/
	void removeElement(unsigned long position)
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

	/*******************************************************************
	Funcion EDAlist::getElement
	Devuelve un elemento de la lista

	Recibe:
	unsigned long position: posicion del elemento que se quiere obtener

	Devuelve:
	Referencia al elemento de la posicion position
	*******************************************************************/
	T& getElement(unsigned long position)
	{
		Node <T> * currentNode = firstNode;

		if (position < size)
		{
			for (int k = 0; k < position; k++)		//moverse hasta el nodo correspondiente
				currentNode = currentNode->nextNode;
		}
		return currentNode->data;
	}

	/**************************************
	Funcion removeAll

	Elimina todos los elementos de la lista
	***************************************/
	void removeAll()
	{
		while (getSize())	//mientras que no este vacia
		{
			removeElement(0);	//eliminar el primer elemento hasta que no queden mas
		}
	}

	/***********************************************
	Funcion EDAlist::getSize

	Devuelve:
	unsigned int: cantidad de elementos de la lista
	************************************************/
	unsigned int getSize() 
	{ 
		return size; 
	}
	
	/**************************************
	Funcion EDAlist::isEmpty

	Devuelve:
	true si no hay elementos en la lista
	false si no hay elementos en la lista
	**************************************/
	bool isEmpty()
	{
		if (size)
		{
			return false;
		}
		return true;
	}

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

