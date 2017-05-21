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
	~Tile();

	void toggleSelect();
	bool isSelected();
	std::string getFileName();
	void draw(Point p);
	bool isValid();

private:

	bool valid;
	std::string fileName;
	bool selected;
	ALLEGRO_BITMAP* img;
	unsigned int side;
};

