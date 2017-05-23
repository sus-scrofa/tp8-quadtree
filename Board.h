#pragma once

#include <string>
#include "Tile.h"
#include "EDAlist.h"

#include <allegro5\allegro_font.h>
#include <allegro5\allegro_color.h>

#define TILE_SIDE 100
#define MARGIN 50
#define COLS 3
#define ROWS 3
#define TILESXPAGE (COLS*ROWS)
#define FONTSIZE MARGIN


class Board
{

public:
	Board(float w,float h, ALLEGRO_FONT * font, ALLEGRO_COLOR color);	//TODO: PONER DEFAULT FONT Y DEFAULT COLOR
	~Board();
	
	/*************************************************************************
	Funcion Board::addTile

	Crea una nueva tile a partir del nombre del archivo recibido.
	Si se pudo crear exitosamente, se agrega al final de la lista.

	Recibe:
	string fileName: nombre del archivo de la imagen de la tile. Debe ser png
	
	Devuelve:
	true si la tile se creo y agrego a la lista exitosamente
	false si hubo un error en la creacion de la tile
	******************************************************************************/
	bool addTile(std::string fileName);

	/*

	*/
	Tile & getTile(unsigned long tileNumber);

	/**
	
	**/
	void removeTile(unsigned long tileNumber);

	/***********************************************************************
	Funcion nextPage

	Si no se encuentra en la ultima pagina, aumenta el indicador de pagina
	Si se encuentra en la ultima pagina, el indicador no avanza
	************************************************************************/
	void nextPage();

	/***********************************************************************
	Funcion prevPage

	Si no se encuentra en la primera pagina, decrementa el indicador de pagina
	Si se encuentra en la primera pagina, el indicador no avanza
	************************************************************************/
	void prevPage();

	/********************************************************
	 Funcion Board::toggleSelectTile

	 Si la tile esta deseleccionada, la selecciona
	 Si la tile esta seleccionada, la deseleccionada

	 Recibe:
	 unsigned int tileNumber: el numero de la tile que se quiere modificar
	*********************************************************/
	void toggleSelectTile(unsigned int tileNumber);

	///********************************************************************
	//Funcion Board::selectTile

	//Marca una tile como seleccionada

	//Recibe:
	//unsigned int tileNumber: el numero de la tile que se quiere modificar
	//*********************************************************************/
	//void selectTile(unsigned int tileNumber);

	///********************************************************************
	//Funcion Board::deselectTile

	//Marca una tile como deseleccionada

	//Recibe:
	//unsigned int tileNumber: el numero de la tile que se quiere modificar
	//*********************************************************************/
	//void deselectTile(unsigned int tileNumber);

	/******************************************************************
	Funcion Board::draw

	Dibuja las tiles correspondiente a la pagina actual.
	La imagen de las tiles se escalan de manera que tengan el mayor 
	tamanio posible sin excederse de un cuadrado de lado side.
	La grilla de imagenes dibujada es de ROWS filas y de COLS columnas
	La primer imagen se dibuja en la posicion mas arriba mas a la 
	izquierda, y las siguientes a la derecha de la anterior, hasta que 
	se termine la fila. Luego, se repite el orden empezando por la fila 
	inferior. De haber menos imagenes en la pagina que el maximo, se 
	dejan los espacios vacios

	********************************************************************/
	void draw();

	/*****************************************
	Funcion Board::isLastPage()

	Devuelve:
	true si se esta en la ultima pagina
	false si no se esta en la ultima pagina
	*****************************************/
	bool isLastPage();

	/**
	
	**/
	unsigned long getListSize();

	void selectAll();
	void clearSelection();

	ALLEGRO_FONT * font;
	ALLEGRO_COLOR color;

private:

	EDAlist<Tile> tiles;

	unsigned int pageNumber;	//0 para la primer pagina
	unsigned int margin;
	unsigned int tileSide;

};

