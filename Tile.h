#pragma once
#include <string>
#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <algorithm>
#include "Point.h"

class Tile
{
public:
	Tile()
	{
		
	}
	Tile(std::string fileName, unsigned int side )
	{
		this->fileName = fileName;
		this->side = side;
		selected = false;
		
		valid = true;
		if ( !(img = al_load_bitmap(fileName.c_str())) )
		{
			valid = false;
#ifdef DEBUG
			std::cout << "Error cargando el archivo " << fileName << std::endl;
#endif // DEBUG
		}
		al_draw_bitmap(img, 0, 0, 0);
		al_flip_display();
	};

	~Tile() 
	{
		if (img != nullptr)
			al_destroy_bitmap(img);
	}

	void toggleSelect() { selected = !selected; }

	bool isSelected() { return selected; }

	std::string getFileName() { return fileName; }
	
	void draw(Point p) 
	{
		if (img != nullptr)	//si la imagen esta cargada, dibujar
		{
			float w = (float)al_get_bitmap_width(img);	
			float h = (float)al_get_bitmap_height(img);

			float resize = 1.0;
			//float resize = ((float)side / (float)std::max(w, h));	//hallar el valor por el cual debo modificar las 
																	//dimensiones de la imagen para que entre en el 
								
			al_draw_bitmap(img, 0, 0, 0);
				//espacio de la tile, y dibujar escalado.
			//al_draw_scaled_bitmap(img, 
				//				  0, 0, w, h,						//origen, ancho y alto original
					//			  p.getX(), p.getY(), w*resize, h*resize,	//origen, ancho y alto escalado
						//		  0);
			if (selected)
			{
				al_draw_rectangle(p.getX(), p.getY(),						//esquina sup izquierda
								  p.getX()+w*resize, p.getY()+h*resize,		//esquina inf derecha
								  al_map_rgb(2,255,255), 1);				//color y grosor
			}
		}
		else;
			//TODO: GJKLAHGRELSZ
	};

	bool isValid() { return valid; }

private:
	bool valid;
	std::string fileName;
	bool selected;
	ALLEGRO_BITMAP* img;
	unsigned int side;
};

