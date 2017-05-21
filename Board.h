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

	bool isLastPage();

public:
	Board();

	~Board();
	
	void addTile(std::string fileName);

	void nextPage();

	void prevPage();

	void toggleSelectTile(unsigned int tileNumber);

	void draw();
};

