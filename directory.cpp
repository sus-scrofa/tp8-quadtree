#include "directory.h"

directory::directory(const char * dir): p(dir), iterator(p)
{
	error = false;
	//chequeo si el path que ingresaron corresponde a algo existente y si es un directorio
	if (boost::filesystem::exists(p) && boost::filesystem::is_directory(p))
	{
		error = false;
	}
	else
	{
		error = true;
	}
}

directory::~directory()
{
}

//getNextPath(std::string extension)
//recive: la extension de los archivos que se quieran
//devuelve: el path de cada archivo cada vez que se lo llama, hasta que no halla archivos con esa extension
//y en ese caso devuelve un string vacio.
//
std::string directory::getNextPath(std::string extension)
{
	std::string temp;
	while ((iterator != boost::filesystem::directory_iterator()) && !validateExtension(iterator->path().string(), extension))
	{
		iterator++;
	}

	if (iterator != boost::filesystem::directory_iterator())
	{
		temp = iterator->path().string();
		iterator++;
	}

	return temp;
}

//isError()
//devuelve: true, si hubo error en la inicializacion, en caso
//contrario devuelvw false
bool directory::isError()
{
	return error;
}

//
//devuelve true si la extension coincide con la del path, false
//en el caso contrario
bool directory::validateExtension(std::string path,std::string Extension)
{

	if (path.find('.' + Extension) != std::string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
