#pragma once
#include <string>
#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <algorithm>
#include "Point.h"


class Tile
{
public:

	Tile();
	Tile(const Tile& other);
	Tile(std::string fileName, unsigned int side );

	/***************************************************
	Destructor
	Si se cargo el bitmap, liberar la memoria que ocupa
	****************************************************/
	~Tile();

	/***********************************************
	Funcion Tile::toggleSelect

	Si la tile esta seleccionada, la deselecciona.
	Si no esta seleccionada, la selecciona
	************************************************/
	void toggleSelect();

	/**************
	Funcion Tile::select

	Selecciona la tile
	*******************/
	void select();

	/**************
	Funcion Tile::deselect

	Deselecciona la tile
	*******************/
	void deselect();
	
	/*************************************
	Funcion Tile::isSelected()

	Devuelve:
	true si la tile esta seleccionada
	false si la tile no esta seleccionada
	**************************************/
	bool isSelected();
	
	/********************************
	Funcion getFileName

	Devuelve:
	string con el nombre del archivo
	*********************************/
	std::string getFileName();
	
	/*********************************************************************************
	Funcion Tile::draw

	Dibuja la imagen cambiando su tamanio para que entre en un cuadrado de lado side

	Recibe:
	Point p: punto correspondiente a la esquina superior izquierda de la imagen 
	**********************************************************************************/
	void draw(Point p);
	
	/*************************************************
	Funcion Tile::isValid

	Devuelve:
	true si no hubieron errores en la inicializacion
	false si hubieron errores en la inicializacion
	*************************************************/
	bool isValid();

private:

	bool valid;
	std::string fileName;
	bool selected;
	ALLEGRO_BITMAP* img;
	unsigned int side;
};

