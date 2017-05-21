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
		cout << "no se inicializo primitives addon" << endl;

	//EDAlist<char> list;

	//list.addElement('h', list.getSize());
	//list.addElement('o', list.getSize());
	//list.addElement('l', list.getSize());
	//list.addElement('a', list.getSize());
	//list.addElement(' ', list.getSize());
	//list.addElement('m', list.getSize());
	//list.addElement('u', list.getSize());
	//list.addElement('n', list.getSize());
	//list.addElement('d', list.getSize());
	//list.addElement('o', list.getSize());

	//list.addElement('X', 0);

	//list.print();

	Display dis(500, 500, al_map_rgb(200, 200, 0));

	dis.colorBackground();
	dis.showChanges();

	std::string f1 = "png1.png";
	std::string f2 = "png2.png";
	unsigned int size = 200;

	Board b;
	b.addTile(f1);
	b.draw();

	dis.showChanges();

	al_destroy_display(dis.getDisplay());

	return 0;
}