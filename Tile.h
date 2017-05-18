#pragma once
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

class Tile
{
public:
	Tile(std::string path);
	~Tile();
	void toggleSelect();
	bool isSelected();
	std::string getFileName();
	void draw(unsigned int x, unsigned int y);
private:
	std::string fileName;
	bool selected;
	ALLEGRO_BITMAP* img;
};

