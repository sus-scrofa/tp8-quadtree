#pragma once

#include <iostream>
#include <string>

#include "EDAlist.h"
#include "Tile.h"
#include "Display.hpp" //TODO: dejamos esto o lo hacemos de otra manera?


#define TILE_SIDE 100
#define MARGIN 20
#define COLS 3
#define ROWS 3
#define TILESXPAGE (COLS*ROWS)


class Board
{
private:
	EDAlist<Tile> tiles;
	
	unsigned int pageNumber;	//0 para la primer pagina

	bool isLastPage()
	{
		if (!tiles.getSize())	//si la lista esta vacia, va a haber siempre una sola pagina
		{
			return true;
		}
		return ((int)((int)(tiles.getSize() - 1) / TILESXPAGE) == pageNumber);
	}

public:
	Board() { pageNumber = 0; }
	
	~Board() {/*TODO: delete de las tiles*/}
	
	void addTile(std::string fileName) 
	{
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_flip_display();

		Tile* newTile = new Tile(fileName, TILE_SIDE);
		if (newTile->isValid())
		{
			tiles.addElement(*newTile, tiles.getSize());
		}
	}

	void nextPage()
	{
		if (!isLastPage())
		{
			pageNumber++;
		}
	}

	void prevPage()
	{
		if (pageNumber > 0)
		{
			pageNumber-- ;
		}
	}

	void toggleSelectTile(unsigned int tileNumber)
	{
		tiles.getElement(pageNumber*TILESXPAGE + tileNumber).toggleSelect();
	}

	void draw() 
	{
		tiles.getElement(0).draw(Point(0, 0));

		for (int i = 0; i < TILESXPAGE; i++) 
		{
				//TODO: dibujar la tile donde corresponde
		}
	}
};

