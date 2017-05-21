#include "quadtree.h"
#include "lodepng.h"
#include <cstring>
#include <fstream>
#include <iostream>

#define DEBUG

using namespace std;

#define MAX(a,b) ( (a)>(b) ? (a) : (b) )
#define MIN(a,b) ( (a)<(b) ? (a) : (b) )

enum colors {R, G, B, ALPHA, PIXEL_SIZE};

typedef struct 
{
	unsigned char * start;	//donde empieza la rawData del .png
	unsigned int imgSide;	//ancho/alto de la imagen total
	
	ofstream * out;			//archivo .eda donde quedara la imagen comprimida
	unsigned char threshold;
} comp_t;

typedef struct
{
	unsigned char * start;
	unsigned int imgSide;

	ifstream * in;			//archivo .eda donde esta la imagen comprimida
} dec_t;



void quadtree(comp_t * c, unsigned int side, unsigned int x, unsigned int y);	//compresion recursiva

bool quadtree(dec_t * d, unsigned int side, unsigned int x, unsigned int y);		//decompresion recursiva


bool qtCompress(char * path, float threshold)
{
	if (path == NULL || threshold >= 100 || threshold <= 0 )
		return false;	//verificar validez de los parametros

	char * endName = strstr(path, ".png");
	if (endName == NULL)
		return false;

	//char edaPath[MAX_NAME_LEN+5];	// long max del nombre + .eda(4) + terminador
	//strncpy(edaPath, path, MAX_NAME_LEN);
	//if(endName - path >= MAX_NAME_LEN)
	//	strcpy(&edaPath[MAX_NAME_LEN], ".eda");	
	//else
	//	strcpy(&edaPath[endName - path], ".eda");
	char edaPath[] = "hola.eda";

	ofstream eda(edaPath);
	if (!eda.good()) 
		return false;
	
	unsigned char * rawData;
	unsigned int width, height;

	if (lodepng_decode32_file(&rawData, &width, &height, path) != 0 || width == 0 || (width != height) 
		|| (width & (width - 1)) != 0 ) {	//verificar que no se devuelva error, que la imagen sea cuadrada y
		eda.close();													//que su tamano sea una potencia de 2
		remove(edaPath);
		return false;					
	}

	comp_t c = {rawData, width, &eda, (unsigned char)(threshold*255.0/100.0)};

	quadtree(&c, width, 0, 0);

	eda.close();
	free(rawData);
	return true;
}

void quadtree(comp_t * c, unsigned int side, unsigned int x, unsigned int y)
{
	float rmed = 0, gmed = 0, bmed = 0;
	unsigned char rmin = 255, gmin = 255, bmin = 255, rmax = 0, gmax = 0, bmax = 0;
	unsigned char * p; // "puntero a pixel" (auxiliar)

	//recorrer el cuadrante entero de a un pixel por vez, calculando maximos, minimos y promedio para c/color
	for (unsigned int j = y; j < y+ side; j++) {
		p = c->start + PIXEL_SIZE * (j * c->imgSide + x);	//apuntar al comienzo de la fila j

		for (unsigned int i = 0; i < side; i++) {
			rmin = MIN(rmin, p[R]);		rmax = MAX(rmax, p[R]);		rmed+=p[R];
			gmin = MIN(gmin, p[G]);		gmax = MAX(gmax, p[G]);		gmed+=p[G];
			bmin = MIN(bmin, p[B]);		bmax = MAX(bmax, p[B]);		bmed+=p[B];

			p += PIXEL_SIZE;		//mover una posicion en x
		}
	}

	if( rmax - rmin + gmax - gmin + bmax - bmin < c->threshold || side == 1 ) { //caso base!
		//escribir "0RGB" con los promedios
		rmed /= side*side;	gmed /= side*side;	bmed /= side*side;
		*(c->out) << '0' << (unsigned char)rmed << (unsigned char)gmed << (unsigned char)bmed;
#ifdef DEBUG
		cout << "escribi 0 y : " << (int)rmed  << ' ' << (int)gmed << ' ' << (int)bmed << endl;
#endif
 		return;
	}
	else { //continuar la recursion
		*(c->out) << '1'; //indicar que se hizo una division mas de este cuadrante de la imagen
#ifdef DEBUG
		cout << "escribi 1. tamano ahora es: " << side/2 << endl << endl;
#endif
		side/=2;
		quadtree(c, side, x, y); //primer cuadrante: mismas coords init, pero hasta la mitad del cuadrante
		quadtree(c, side, x+side, y); //2do cuad: misma altura, corro x hasta la mitad del cuadrante que recibi
		quadtree(c, side, x, y+side); //3er cuad: vuelvo x a donde estaba, corro y hasta la mitad del cuadrante
		quadtree(c, side, x+side, y+side); //4to cuad: a x0 e y0 hay que correrlos hasta la mitad del cuadrante
	}

}



bool qtDecompress(char * path, unsigned int size)
{
	if (path == NULL || size == 0 || (size & (size-1)) != 0 )
		return false;
	
	char * endName = strstr(path, ".eda");	// verificar que el path corresponde a un archivo .eda
	if (endName == NULL)
		return false;

	char pngPath[MAX_NAME_LEN+5];			// obtengo el nombre del archivo png que se creara
	strncpy(pngPath, path, MAX_NAME_LEN);
	if(endName - path >= MAX_NAME_LEN)
		strcpy(&pngPath[MAX_NAME_LEN], ".png");	
	else
		strcpy(&pngPath[endName - path], ".png");

	ifstream eda(path);						// verifico que el archivo recibido exista
	if(!eda.good())
		return false;

	unsigned char * rawData = new unsigned char[size*size*PIXEL_SIZE]; 

	dec_t d = {rawData, size, &eda};


	bool isValid = true;

	if ( quadtree(&d, size, 0, 0) == false || lodepng_encode32_file(pngPath, rawData, size, size) != 0 )
		isValid = false;

	eda.close();
	return isValid;
}




bool quadtree(dec_t * d, unsigned int side, unsigned int x, unsigned int y)
{
	unsigned char nextChar = d->in->get();

	switch (nextChar) {
	
		case '1':	{// se vuelve a dividir la imagen: continuo la recursividad.
			side/=2;
#ifdef DEBUG
			cout<< "encontre un 1"<< endl << endl;
#endif
			if (
    			 quadtree(d, side, x, y) == false ||	//primer cuad
				 quadtree(d, side, x+side, y) == false ||	//2do cuad
				 quadtree(d, side, x, y+side) == false ||	//3er cuad
				 quadtree(d, side, x+side, y+side) == false)	//4to cuad
#ifdef DEBUG
			cout<< "fin del cuadrante"<< endl << endl;
#endif				
			return false;	//si cualquiera devuelve error, se devuelve error
		}
		break;

		case '0': { //leo rgb y lo copio al archivo
			unsigned char * p;	//puntero auxiliar al pixel
			unsigned char rgba[PIXEL_SIZE] = {d->in->get(), d->in->get(), d->in->get(), 255};
#ifdef DEBUG
			cout<< "encontre 0 y " << (int)rgba[0] << (int)rgba[1]<< (int)rgba[2]<< endl;
#endif

			for (unsigned int  j = y; j<y+side; j++) {
				p = d->start + PIXEL_SIZE * ( j*d->imgSide + x );
				for (unsigned int i = 0; i<side; i++) {
					memcpy(p, rgba, PIXEL_SIZE);
					p+=PIXEL_SIZE;
				}
			}
		}
		break;

		default:
			return false; //el archivo no respetaba el formato que tenia que tener
	}

	return true;
}