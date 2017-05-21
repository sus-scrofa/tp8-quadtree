#include "Tile.h"
#include <allegro5\allegro_primitives.h>

//TODO: constructor sin parametros, que cargue quizas una imagen de error? kcyo

Tile::Tile() {};

Tile::Tile(const Tile& other)
{
	if (!(img = al_clone_bitmap(other.img)))
	{
		valid = false;
#ifdef DEBUG
		std::cout << "Error copiando bitmap" << std::endl;
#endif // DEBUG

	}
}

Tile::Tile(std::string fileName, unsigned int side)
{
	this->fileName = fileName;
	this->side = side;
	selected = false;

	valid = true;
	if (!(img = al_load_bitmap(fileName.c_str())))
	{
		valid = false;
#ifdef DEBUG
		std::cout << "Error cargando el archivo " << fileName << std::endl;
#endif // DEBUG
	}
};


Tile::~Tile()
{
	if (img != nullptr)
	{
		al_destroy_bitmap(img);
	}
}


void Tile::toggleSelect() 
{ 
	selected = !selected; 
}

void Tile::select()
{
	selected = true;
}

void Tile::deselect()
{
	selected = false;
}

bool Tile::isSelected() 
{ 
	return selected; 
}

std::string Tile::getFileName() 
{ 
	return fileName; 
}

void Tile::draw(Point p)
{
	if (img != nullptr)	//si la imagen esta cargada, dibujar
	{
		float w = (float)al_get_bitmap_width(img);
		float h = (float)al_get_bitmap_height(img);

		//float resize = 1.0;
		float resize = ((float)side / (float)std::max(w, h));	//hallar el valor por el cual debo modificar las 
																//dimensiones de la imagen para que entre en el 
																//espacio de la tile, y dibujar escalado.

		al_draw_scaled_bitmap(img,
			0, 0, w, h,								//origen, ancho y alto original
			p.getX(), p.getY(), w*resize, h*resize,	//origen, ancho y alto escalado
			0);
		if (selected)
		{
			al_draw_rectangle(p.getX(), p.getY(),						//esquina sup izquierda
				p.getX() + w*resize, p.getY() + h*resize,		//esquina inf derecha
				al_map_rgb(2, 255, 255), 1);				//color y grosor
		}
	}
	else;
	//TODO: GJKLAHGRELSZ
};

bool Tile::isValid() 
{ 
	return valid; 
}