#pragma once
#include "EDAlist.h"
#include "Tile.h"

class Board
{
private:
	EDAlist<Tile> tiles;
	unsigned int pageNumber;
public:
	Board();
	~Board();
	void addTile();
	void nextPage();
	void prevPage();
	void toggleSelectTile(unsigned int tileNumber);
	void draw();
};

