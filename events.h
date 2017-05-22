#pragma once
#include "genericEvent.h"
enum { TOGGLE, CHANGE_PAGE,SELECT_ALL, DESELECT_ALL,_COMPRESS,_DECOMPRESS,EMPTY_EVENT };

class Toggle : public genericEvent
{
public:
	//el cosntructor resive el numero que se desea toggle
	Toggle(unsigned int Number);
	//devuelve el numero seleccionado
	unsigned int getNumber();

private:
	unsigned int Number;
};

class changePage : public genericEvent
{
public:
	//resive si se desea pasar a la proxima pagina(isNextPage=true) 
	//o ir a la pagina anterior(isNextPage=false)
	changePage(bool isNextPage);

	bool getIsNextPage();
private:
	bool isNextPage;
};

class selectAll : public genericEvent
{
	public:
		selectAll();
};

class clearSelection : public genericEvent
{
public:
	clearSelection();
};

class compress : public genericEvent
{
public:
	compress();
};

class decompress : public genericEvent
{
public:
	decompress();
};

class empty : public genericEvent
{
public:
	empty();
};