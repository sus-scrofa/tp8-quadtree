#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include "EDAlist.h"
#include "Tile.h"
#include "Point.h"
#include "Display.hpp"
#include "Board.h"
#include "directory.h"
#include "quadtree.h"
#include "lodepng.h"

#include "genericEvent.h"
#include "events.h"
#include "eventGenerator.h"

#include "compilationSwitch.h"
extern "C"
{
#include "parseCmdLine.h"
#include "parserCallback.h"
}


using namespace std;

int main(int argc, char *argv[])
{
	cmdLineParserData_t data;
	//queda feooooooooooooooooooooooooooooooo
	data.path = NULL;
#if MODE == COMPRESS
	data.fidelity = 0;
#endif
	if (parseCmdLine(argc, argv, parserCallback, &data) == -1)
	{
		exit(4);
	}


	string tPath;
	directory dirPath(data.path);
	unsigned int threshold = 90;
#if MODE == COMPRESS
	threshold = data.fidelity;
#endif


	al_init();
	//falta el parser
	if (!al_init_image_addon())
		cout << "no se inicializo img addon" << endl;
	if (!al_init_primitives_addon())
	{
		cout << "no se inicializo primitives addon" << endl;
		al_shutdown_image_addon();
	}
	
	if (!al_init_font_addon())
	{
		cout << "no se inicializo font addon" << endl;
	}

	if (!al_init_ttf_addon())
	{
		cout << "no se inicializo ttf addon" << endl;
	}

	ALLEGRO_FONT * font = al_load_ttf_font("ttf.ttf", 12, 0);//falta chequear si se inicializo correctamente
	Display dis(500, 500, al_map_rgb(200, 200, 0));

	dis.colorBackground();
	dis.showChanges();
	unsigned int size = 200;

	Board b(500,500,font, al_map_rgb(200, 0, 0));

	//geteo los path
#if MODE == COMPRESS
	while (!((tPath = dirPath.getNextPath("png")).empty()))
#endif
#if MODE == DECOMPRESS
	while (!((tPath = dirPath.getNextPath("eda")).empty()))
#endif
	{
		b.addTile(tPath);
	}
		
	genericEvent * events = NULL;
	eventGenerator eg;

	if (eg.getIsError())
	{
		std::cout << "hubo error al inicializar el generador de eventos" << std::endl;
	}
	
	do
	{
		delete events;
		events = eg.getNextEvent();

		switch (events->getType())
		{
		case TOGGLE:
			
			b.toggleSelectTile(((Toggle*)events)->getNumber() - 1);
			break;
		case CHANGE_PAGE:
			
			if (!((changePage *)events)->getIsNextPage())
			{
				b.nextPage();
			}
			else
			{
				b.prevPage();
			}
			break;
		case SELECT_ALL:
			
			for (unsigned long int n = 0; n < b.getListSize(); n++)
				b.selectTile(n);
			
			break;
		case DESELECT_ALL:
			for (unsigned long int n = 0; n < b.getListSize(); n++)
				b.deselectTile(n);
			break;
		case _COMPRESS:
			
			for (unsigned long int n = 0; n < b.getListSize(); n++)
			{
				if ((b.getTile(n)).isSelected())
				{
					qtCompress((b.getTile(n)).getFileName().c_str(), threshold);
				}
			}
			break;
		case _DECOMPRESS:
			for (unsigned long int n = 0; n < b.getListSize(); n++)
			{
				if ((b.getTile(n)).isSelected())
				{
					qtDecompress((b.getTile(n)).getFileName().c_str(), 16);
				}
			}
			break;
		default:
			break;
		}
		dis.colorBackground();
		b.draw();
		dis.showChanges();


	} while (events->getType() != _COMPRESS && events->getType() != _DECOMPRESS);
	

	al_destroy_display(dis.getDisplay());

	return 0;
}