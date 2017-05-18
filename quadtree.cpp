#include "quadtree.h"
#include "lodepng.h"
#include <cstring>
#include <fstream>

using namespace std;

#define MAX(a,b) ( (a)>(b) ? (a) : (b) )
#define MIN(a,b) ( (a)<(b) ? (a) : (b) )

enum colors {R, G, B, ALPHA, PIXEL_SIZE};

typedef struct 
{
	unsigned char * start;	//donde empieza la rawData del .png
	unsigned int imgSide;	//ancho/alto de la imagen total

	unsigned int side;		//pixeles que contiene el lado del cuadrante que se esta procesando
	unsigned int x;			//n de pixel correspondiente a la coordenada inicial del cuadrante en el ancho
	unsigned int y;			//n de pixel correspondiente a la coordenada inicial del cuadrante en el alto

	ofstream * out;			//archivo .eda donde quedara la imagen comprimida
	unsigned char threshold;
} comp_t;

typedef struct {} dec_t;



void quadtree(comp_t c);	//compresion recursiva

void quadtree(dec_t d);		//decompresion recursiva


bool qtCompress(char * path, unsigned int threshold)
{
	if (path == NULL || threshold > 255 || threshold == 0 )
		return false;	//verificar validez de los parametros

	char * endName = strstr(path, ".png");
	if (endName == NULL)
		return false;

	char edaPath[MAX_NAME_LEN+5];	// long max del nombre + .eda(4) + terminador
	strncpy(edaPath, path, MAX_NAME_LEN);
	if(endName - path >= MAX_NAME_LEN)
		strcpy(&edaPath[MAX_NAME_LEN], ".eda");	
	else
		strcpy(&edaPath[endName - path], ".eda");

	ofstream eda(edaPath);
	if (!eda.good()) 
		return false;
	
	unsigned char * rawData;
	unsigned int width, height;

	if (lodepng_decode32_file(&rawData, &width, &height, path) != 0 || width == 0 || (width != height) 
		|| (width & (width - 1)) != 0 ) {	//verificar que no se devuelva error, que la imagen sea cuadrada y
		eda.close();													//que su tamano sea una potencia de 2
		return false;					
	}
	comp_t c = {rawData, width, width, 0, 0, &eda, (unsigned char)threshold};

	quadtree(c);

	eda.close();
	free(rawData);
	return true;
}

void quadtree(comp_t c)
{
	float rmed = 0, gmed = 0, bmed = 0;
	unsigned char rmin = 255, gmin = 255, bmin = 255, rmax = 0, gmax = 0, bmax = 0;
	unsigned char * p; // "puntero a pixel" (auxiliar)

	//recorrer el cuadrante entero de a un pixel por vez, calculando maximos, minimos y promedio para c/color
	for (unsigned int i = c.x; i < c.x + c.side; i++) 
		for (unsigned int j = c.y; j < c.y+c.side; j++) {
			p = c.start + (PIXEL_SIZE * (i*c.imgSide +j) ); //apunto al pixel i,j

			rmin = MIN(rmin, p[R]);		rmax = MAX(rmax, p[R]);		rmed+=p[R];
			gmin = MIN(gmin, p[G]);		gmax = MAX(gmax, p[G]);		gmed+=p[G];
			bmin = MIN(bmin, p[B]);		bmax = MAX(bmax, p[B]);		bmed+=p[B];
		}

	if( rmax - rmin + gmax - gmin + bmax - bmin < c.threshold || c.side == 1 ) { //caso base!
		//escribir "0RGB" con los promedios
		rmed /= c.side*c.side;	gmed /= c.side*c.side;	bmed /= c.side*c.side;
		*(c.out) << '0' << (unsigned char)rmed << (unsigned char)gmed << (unsigned char)bmed;
		return;
	}
	else { //continuar la recursion
		*(c.out) << '1'; //indicar que se hizo una division mas de este cuadrante de la imagen
		
		c.side/=2;
		quadtree(c); //primer cuadrante: mismas coords init, pero hasta la mitad del cuadrante

		c.x+=c.side;
		quadtree(c); //2do cuad: misma altura, corro x hasta la mitad del cuadrante que recibi

		c.x-=c.side;	c.y+=c.side;
		quadtree(c); //3er cuad: vuelvo x a donde estaba, corro y hasta la mitad del cuadrante

		c.x+=c.side;
		quadtree(c); //4to cuad: a x0 e y0 hay que correrlos hasta la mitad del cuadrante
	}
}



bool qtDecompress(char * path, unsigned int size)
{
	if (path == NULL || size == 0 || (size & (size-1)) != 0 )
		return false;

	return true;
}




void quadtree(dec_t d)
{
	return;
}