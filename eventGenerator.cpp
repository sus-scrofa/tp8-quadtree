#include "eventGenerator.h"
#include "compilationSwitch.h"
eventGenerator::eventGenerator()
{
	isError = false;
	//inicializo keyboard
	if (!al_install_keyboard()) 
	{
		isError = true;
	}
	eventQueue=al_create_event_queue();
	if (!eventQueue)
	{
		isError = true;
	}
	if (!isError)
	{
		al_register_event_source(eventQueue, al_get_keyboard_event_source());
	}
	
}

eventGenerator::~eventGenerator()
{
	al_destroy_event_queue(eventQueue);
}

genericEvent * eventGenerator::getNextEvent()
{
	ALLEGRO_EVENT events;
	genericEvent * ev = NULL;
	if (al_get_next_event(eventQueue, &events)&&(events.type== ALLEGRO_EVENT_KEY_UP))
	{
		switch (events.keyboard.keycode)
		{
		case ALLEGRO_KEY_1:case ALLEGRO_KEY_2:case ALLEGRO_KEY_3:
		case ALLEGRO_KEY_4:case ALLEGRO_KEY_5:case ALLEGRO_KEY_6:
		case ALLEGRO_KEY_7:case ALLEGRO_KEY_8:case ALLEGRO_KEY_9:
			ev = new Toggle(events.keyboard.keycode - ALLEGRO_KEY_0);
			break;
		
		case ALLEGRO_KEY_LEFT:
			ev = new changePage(true);
			break;

		case ALLEGRO_KEY_RIGHT:
			ev = new changePage(false);
			break;
		case ALLEGRO_KEY_A:
			ev = new selectAll;
			break;
		case ALLEGRO_KEY_N:
			ev = new clearSelection;
			break;
		case ALLEGRO_KEY_ENTER:
			//falta flag de compilacion
#if MODE == COMPRESS
			ev = new compress;
#endif
#if MODE ==DECOMPRESS
			ev = new decompress;
#endif
			break;
		default:
			ev = new empty;
			break;
		}



	}
	else
	{
		ev = new empty;
	}
	
	return ev;
}

bool eventGenerator::getIsError()
{
	return isError;
}
