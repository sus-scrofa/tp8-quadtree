#include "Board.h"

bool Board::isLastPage()
{
	if (!tiles.getSize())	//si la lista esta vacia, va a haber siempre una sola pagina
	{
		return true;
	}
	return ((int)((int)(tiles.getSize() - 1) / TILESXPAGE) == pageNumber);
}

Board::Board() { pageNumber = 0; }

Board::~Board() {/*TODO: delete de las tiles*/ }

void Board::addTile(std::string fileName)
	{
		Tile* newTile = new Tile(fileName, TILE_SIDE);
		if (newTile->isValid())
		{
			tiles.addElement(*newTile, tiles.getSize());
		}
	}

void Board::nextPage()
	{
		if (!isLastPage())
		{
			pageNumber++;
		}
	}

void Board::prevPage()
	{
		if (pageNumber > 0)
		{
			pageNumber--;
		}
	}

void Board::toggleSelectTile(unsigned int tileNumber)
	{
		tiles.getElement(pageNumber*TILESXPAGE + tileNumber).toggleSelect();
	}

void Board::draw()
	{
		for (int i = 0; i < TILESXPAGE && i < (tiles.getSize() - TILESXPAGE * pageNumber); i++)
		{
			tiles.getElement(pageNumber*TILESXPAGE + i).draw(Point(MARGIN + (i%COLS)*(MARGIN+TILE_SIDE), MARGIN +  (int)(i/COLS)*(MARGIN+TILE_SIDE)));
		}
	}