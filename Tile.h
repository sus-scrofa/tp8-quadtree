#pragma once

#include <string>

#include <allegro5\allegro_font.h>
#include <allegro5\allegro_color.h>

#include "Point.h"

#include "compilationSwitch.h"




class Tile
{

public:

	Tile() {};

	Tile(const Tile& other);

	Tile(std::string fileName, float side, ALLEGRO_FONT * font, ALLEGRO_COLOR color);

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
	void draw(Point p, ALLEGRO_FONT * font, ALLEGRO_COLOR color);
	
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
	unsigned int side;

	#if MODE == COMPRESS
	ALLEGRO_BITMAP* img;

	#elif MODE == DECOMPRESS
	ALLEGRO_FONT * font;	//fuente a usar
	ALLEGRO_COLOR color;	//color de la fuente
	//gif selectedAnim;		//gif que indica que esta seleccionado

	#else
	//TODO: cout?
	#endif
};