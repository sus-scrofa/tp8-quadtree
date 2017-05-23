#include "Board.h"
#include <algorithm>

Board::Board(float w, float h, ALLEGRO_FONT * font, ALLEGRO_COLOR color) 
{ 
	//se calcula que la suma de los margenes ocupa el 20% del alto o del ancho de la pantalla, lo que sea menor
	if (h < w)	//si la altura es menor que el ancho
	{
		margin = h * 0.2 / (float)(ROWS + 1);
		tileSide = h * 0.8 / (float)(ROWS);
	}
	else	//si el ancho es menor o igual al alto
	{
		margin = w * 0.2 / (float)(COLS + 1);
		tileSide = w * 0.8 / (float)(COLS);
	}

	pageNumber = 0; 
	this->font = font;
	this->color = color;
}

Board::~Board() 
{
	tiles.removeAll();
}

bool Board::addTile(std::string fileName)
{
	Tile* newTile = new Tile(fileName, tileSide, font, color);

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
	if (pageNumber*TILESXPAGE + tileNumber < tiles.getSize())
		tiles.getElement(pageNumber*TILESXPAGE + tileNumber).toggleSelect();
}
//
//void Board::selectTile(unsigned int tileNumber)
//{
//	if (pageNumber*TILESXPAGE + tileNumber < tiles.getSize())
//		tiles.getElement(pageNumber*TILESXPAGE + tileNumber).select();
//}
//
//void Board::deselectTile(unsigned int tileNumber)
//{
//	if (pageNumber*TILESXPAGE + tileNumber < tiles.getSize())
//		tiles.getElement(pageNumber*TILESXPAGE + tileNumber).deselect();
//}

void Board::draw()
{
	for (unsigned int i = 0; i < TILESXPAGE && i < (tiles.getSize() - TILESXPAGE * pageNumber); i++)
	{
		float x = margin + (i%COLS)*(margin + tileSide);
		float y = margin + (int)(i / COLS)*(margin + tileSide);
		tiles.getElement(pageNumber*TILESXPAGE + i).draw(Point(x, y), font, color);
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

void Board :: selectAll()
{
	for (unsigned int i = 0; i<tiles.getSize(); i++)
		tiles.getElement(i).select();
}

void Board :: clearSelection()
{
	for (unsigned int i = 0; i<tiles.getSize(); i++)
		tiles.getElement(i).deselect();
}