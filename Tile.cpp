#include "Tile.h"
#include <iostream>

using namespace std;

Tile::Tile(string path)
{
	if (!(img = al_load_bitmap(path.c_str())))
		//tirar excepcion o marcar error o algo
		cout << "Error cargando el archivo " << path << endl;
}

Tile::~Tile()
{
}

void Tile::toggleSelect()
{
}

bool Tile::isSelected()
{
	return false;
}

std::string Tile::getFileName()
{
	return std::string();
}

void Tile::draw(unsigned int x, unsigned int y)
{
}
