
#include "Display.hpp"

using namespace std;

///////////////////////////////////// Display ////////////////////////////////////////
//
// Constructor de un objeto Display.
//
//////////////////////////////////////////////////////////////////////////////////////

Display::Display(float _displayWidth, float _displayHeight, ALLEGRO_COLOR color)
{
	displayWidth = _displayWidth;		//cargar tamanio de display
	displayHeight = _displayHeight;
	
	bg = nullptr;

	valid = true;	//es true siempre y cuando no haya un error en la inicializacion de allegro
					//si se encuentra un error, se lo indica en esta variable y se llaman a las 
					//funciones de finalizacion correspondientes
		
	display = al_create_display(displayWidth, displayHeight);

	if(display == nullptr)		//si no se cargo correctamente el display, valid = false. caso contrario, valid == true
	{
		valid = false;
	}
	else
	{
		al_set_target_backbuffer(display);
	}


	this->color = color;	//guardar el color de fondo
}


///////////////////////////// Display::drawBackground ////////////////////////////////
//
// Dibuja en pantalla el fondo del display
//
//////////////////////////////////////////////////////////////////////////////////////

void Display::drawBackground()
{
	//TODO:
}


///////////////////////////// Display::drawBackground ////////////////////////////////
//
// Pinta todo el display de un color
//
//////////////////////////////////////////////////////////////////////////////////////

void Display::colorBackground()
{
	al_clear_to_color( color );
}


///////////////////////////////// Display::isValid ///////////////////////////////////
//
// Indica si el objeto se contruyo de forma correcta
//
//////////////////////////////////////////////////////////////////////////////////////

bool Display::isValid()
{
	return valid;
}


///////////////////////////// Display::showChanges ///////////////////////////////////
//
// Muestra en pantalla los cambios dibujados
//
//////////////////////////////////////////////////////////////////////////////////////

void Display::showChanges()
{
	al_flip_display();
}


/////////////////////////////// Display::getDisplay ///////////////////////////////////
//
// Getter del ALLEGRO_DISPLAY* display.
//
//////////////////////////////////////////////////////////////////////////////////////

ALLEGRO_DISPLAY* Display::getDisplay()
{
	return display;
}



