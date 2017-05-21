#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

#include "EDAlist.h"
#include "Tile.h"
#include "Point.h"
#include "Display.hpp"
#include "Board.h"

#include "quadtree.h"
#include "lodepng.h"

using namespace std;

int main()
{
	al_init();
	if (!al_init_image_addon())
		cout << "no se inicializo img addon" << endl;
	if (!al_init_primitives_addon())
	{
		cout << "no se inicializo primitives addon" << endl;
		al_shutdown_image_addon();
	}

	Display dis(500, 500, al_map_rgb(200, 200, 0));

	dis.colorBackground();
	dis.showChanges();

	std::string f1 = "png1.png";
	std::string f2 = "png2.png";
	std::string f3 = "png3.png";
	std::string f4 = "png4.png";
	std::string f5 = "png5.png";
	std::string f6 = "png6.png";
	std::string f7 = "png7.png";
	std::string f8 = "png8.png";
	std::string f9 = "png9.png";
	std::string f10 = "png10.png";
	unsigned int size = 200;

	Board b;
	b.addTile("png1.png");
	b.addTile(f2);
	b.addTile(f3);
	b.addTile(f4);
	b.addTile(f5);
	b.addTile(f6);
	b.addTile(f7);
	b.addTile(f8);
	b.addTile(f9);
	b.addTile(f10);

	b.draw();
	dis.showChanges();

	dis.colorBackground();
	b.nextPage();
	b.draw();
	dis.showChanges();

	al_destroy_display(dis.getDisplay());

	return 0;
}