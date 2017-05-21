#include "Board.h"

Board::Board() 
{ 
	pageNumber = 0; 
}

Board::~Board() 
{
	tiles.removeAll();
}

bool Board::addTile(std::string fileName)
{
	Tile* newTile = new Tile(fileName, TILE_SIDE);
	if (newTile->isValid())
	{
		tiles.addElement(*newTile, tiles.getSize());
		return true;
	}
	return false;
}

Tile & Board::getTile(unsigned long tileNumber)
{
	return (tiles.getElement(tileNumber));
}

void Board::removeTile(unsigned long tileNumber)
{
	tiles.removeElement(tileNumber);
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

void Board::selectTile(unsigned int tileNumber)
{
	tiles.getElement(pageNumber*TILESXPAGE + tileNumber).select();
}

void Board::deselectTile(unsigned int tileNumber)
{
	tiles.getElement(pageNumber*TILESXPAGE + tileNumber).deselect();
}

void Board::draw()
{
	for (int i = 0; i < TILESXPAGE && i < (tiles.getSize() - TILESXPAGE * pageNumber); i++)
	{
		tiles.getElement(pageNumber*TILESXPAGE + i).draw(Point(MARGIN + (i%COLS)*(MARGIN+TILE_SIDE), MARGIN +  (int)(i/COLS)*(MARGIN+TILE_SIDE)));
	}
}

unsigned long Board::getListSize()
{
	return(tiles.getSize());
}

bool Board::isLastPage()
{
	if (!tiles.getSize())	//si la lista esta vacia, va a haber siempre una sola pagina
	{
		return true;
	}
	return ((int)((int)(tiles.getSize() - 1) / TILESXPAGE) == pageNumber);
}