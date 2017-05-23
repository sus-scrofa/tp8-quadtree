#include "events.h"


Toggle::Toggle(unsigned int Number)
{
	Type = TOGGLE;
	this->Number = Number;
}

unsigned int Toggle::getNumber()
{
	return Number;
}

changePage::changePage(bool isNextPage)
{
	this->isNextPage = isNextPage;
	Type = CHANGE_PAGE;
}

bool changePage::getIsNextPage()
{
	return isNextPage;
}

selectAll::selectAll()
{
	Type = SELECT_ALL;
}

clearSelection::clearSelection()
{
	Type = DESELECT_ALL;
}

enter::enter()
{
	Type = ENTER;
}


empty::empty()
{
	Type = EMPTY_EVENT;
}


	
