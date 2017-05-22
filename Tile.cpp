#include "Tile.h"

//TODO: constructor sin parametros, que cargue quizas una imagen de error? kcyo


Tile::Tile(std::string fileName, float side, ALLEGRO_FONT * font, ALLEGRO_COLOR color)
{
	selected = false;
	this->fileName = fileName;

#if MODE == COMPRESS	//cargar el lado y el bitmap del png
	this->side = side;

	valid = true;
	if (!(img = al_load_bitmap(fileName.c_str())))
	{
		valid = false;
	}

#elif MODE == DECOMPRESS	//cargar la ttf font y el color

	this->font = font;
	this->color = color;
	valid = true;

#else
	//TODO: cout?
#endif

}

Tile::Tile(const Tile& other)
{
#if MODE == COMPRESS
	img = al_clone_bitmap(other.img);

#elif MODE == DECOMPRESS
	
#else
	//TODO: COUT?
#endif
}

Tile::~Tile()
{
#if MODE == COMPRESS
	if (img != nullptr)
	{
		al_destroy_bitmap(img);
	}
#elif MODE == DECOMPRESS
#else
	//TODO:
#endif
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

bool Tile::isValid()
{
	return valid;
}

void Tile::draw(Point p, ALLEGRO_FONT * font, ALLEGRO_COLOR color)
{
#if MODE == COMPRESS
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
			al_draw_rectangle(p.getX(), p.getY(),				//esquina sup izquierda
				p.getX() + w*resize, p.getY() + h*resize,		//esquina inf derecha
				color, 1);										//color y grosor
		}
	}
	else;
	//TODO: GJKLAHGRELSZ

#elif MODE == DECOMPRESS
	al_draw_text(font, color, p.getX(), p.getY(), 0, fileName.c_str());

#else
	//TODO:
#endif
}





