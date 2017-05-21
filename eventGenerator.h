#pragma once
#include "events.h"
#include <allegro5/allegro.h>
class eventGenerator
{
public:
	eventGenerator();
	~eventGenerator();
	genericEvent * getNextEvent();
	bool getIsError();
private:
	ALLEGRO_EVENT_QUEUE *eventQueue;
	bool isError;
};
