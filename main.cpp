#include <iostream>
extern "C" {
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include "parseCmdLine.h"
#include "parserCallback.h"
}


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


using namespace std;

#if		MODE == COMPRESS
#define PARSER_SHOULD_RETURN 2
#elif	MODE == DECOMPRESS
#define PARSER_SHOULD_RETURN 1
#else
#error	"The MODE of this program must be either COMPRESS or DECOMPRESS"
#endif




int main(int argc, char *argv[])
{
	cmdLineParserData_t data;
	data.path = NULL;
#if MODE == COMPRESS
	data.fidelity = 0;
#endif
	//chequeo que los paramtero resividos por linea de comando sean correctos
	if (parseCmdLine(argc, argv, parserCallback, &data) != PARSER_SHOULD_RETURN)
	{
		cout << "Argumentos de linea de comando no validos" << endl;
		return EXIT_FAILURE;
	}

	al_init();
	if (!al_init_image_addon())
	{
		std::cout << "no se inicializo img addon" << std::endl;
		return EXIT_FAILURE;
	}

	if (!al_init_primitives_addon())
	{
		std::cout << "no se inicializo primitives addon" << std::endl;
		al_shutdown_image_addon();
		return EXIT_FAILURE;
	}

	if (!al_init_font_addon())
	{
		return EXIT_FAILURE;
	}

	if (!al_init_ttf_addon())
	{
		std::cout << "no se inicializo ttf addon" << std::endl;
		return EXIT_FAILURE;
	}

	string tPath;
	directory dirPath(data.path);

#if MODE == COMPRESS
	unsigned threshold = data.fidelity;
#endif




	ALLEGRO_FONT * font = al_load_ttf_font("ttf.ttf", 40, 0);//falta chequear si se inicializo correctamente
	
	Display dis(al_map_rgb(200, 200, 0),1000, 600);

	dis.colorBackground();
	dis.showChanges();
	

	Board b(1000,600,font, al_map_rgb(200, 0, 0));

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
			
			b.selectAll();
			
			break;
		case DESELECT_ALL:
			b.clearSelection();
			break;

		case ENTER:
			
			for (unsigned long int n = 0; n < b.getListSize(); n++)
			{
				if ((b.getTile(n)).isSelected())
				{
#if MODE == COMPRESS
					qtCompress((b.getTile(n)).getFileName().c_str(), threshold);
#else
					qtDecompress((b.getTile(n)).getFileName().c_str(), 512);
#endif
				}
			}
			break;

		default:
			break;
		}
		dis.colorBackground();
		b.draw();
		dis.showChanges();


	} while (events->getType() != ENTER);
	

	al_destroy_display(dis.getDisplay());

	return 0;
}