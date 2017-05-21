#ifndef Background_hpp
#define Background_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#define FLOORY		616		// Coordenada Y del piso donde se apoyan los worms
#define XMIN		701.0	// Borde izquierdo de donde se mueven los worms
#define XMAX		1212.0	// Borde derecho de donde se mueven los worms
#define BGWIDTH		1930	// Ancho imagen de fondo
#define BGHEIGHT	696		// Altura imagen de fondo


//////////////////////////////// Clase: Display //////////////////////////////////////

class Display
{
public:
	Display(float displayWidth = BGWIDTH, float displayHeight = BGHEIGHT, ALLEGRO_COLOR color = { 0,0,0,0 });
	ALLEGRO_DISPLAY* getDisplay();
	void drawBackground();
	void colorBackground();
	void showChanges();
	bool isValid();

	
private:
	bool valid;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP* bg;
	ALLEGRO_COLOR color;
	float displayWidth;
	float displayHeight;
};

#endif /* Background_hpp */