#include "quadtree.h"
#include "lodepng.h"
#include <cstring>
#include <fstream>

using namespace std;

#define MAX(a,b) ( (a)>(b) ? (a) : (b) )
#define MIN(a,b) ( (a)<(b) ? (a) : (b) )

enum colors {R, G, B, ALPHA, PIXEL_SIZE};	//posicion dentro del pixel de cada componente en el formato RGBA

//DATOS CONSTANTES EN LA FUNCION RECURSIVA QUADTREE PARA COMPRIMIR
typedef struct 
{
	unsigned char  * start;		//donde empieza la rawData del .png
	unsigned int imgSide;		//ancho/alto de la imagen
	
	ofstream * out;				//archivo .eda donde quedara la imagen comprimida
	unsigned char threshold;	//maximo puntaje que puede tener un cuadrante para que se guarde su promedio en lugar de dividirlo
} comp_t;

//DATOS CONSTANTES EN LA FUNCION RECURSIVA QUADTREE PARA DESCOMPRIMIR
typedef struct
{
	unsigned char * start;	//posicion a partir de la cual se guardara la rawData
	unsigned int imgSide;	//tamano final que debe tener la imagen que se creara

	ifstream * in;			//archivo .eda donde esta la imagen comprimida
} dec_t;

void quadtree(comp_t * c, unsigned int side, unsigned int x, unsigned int y);
bool quadtree(dec_t * d, unsigned int side, unsigned int x, unsigned int y);	
/* 
	Funcion quadtree()
	
	Segun si recibe un puntero a dec_t o comp_t, descomprime o comprime una imagen utilizando el algoritmo quad tree.
	Reciben un puntero a los datos que seran constantes durante toda la recursion (para no llenar demasiado el stack), 
asi como el lado del tamano que se esta procesando actualmente (size) y la columna y fila donde empieza el mismo (x e
y respectivamente).
	En el caso de la compresion, siempre se devuelve true, porque no hay forma de saber si la informacion que se esta
leyendo es efectivamente rawData RGBA o no, ya que cualquier bloque de memoria puede leerse como tal. En cambio, el ar-
chivo que recibe la descompresion debe tener un formato predeterminado, (debido a las indicaciones de que se vuelve a 
dividir el cuadrante o no), con lo cual si en algun momento no se sigue ese formato devuelve false.

*/



bool qtCompress(char * path, float fidelity)
{
	if (path == NULL || fidelity >= 100 || fidelity <= 0 )
		return false;	//verificar validez de los parametros

	char * endName = strstr(path, ".png");
	if (endName == NULL)	// verificar que el path recibido corresponde a un archivo .png
		return false;		//si contiene el string .png pero no es un archivo de ese tipo, lodepng devolvera error

	char edaPath[MAX_NAME_LEN+5];	// obtengo el path del .eda, de longitud = long max + .eda(4) + terminador
	strncpy(edaPath, path, MAX_NAME_LEN);	//escribo el nombre
	if(endName - path >= MAX_NAME_LEN)		//cambio la extension
		strcpy(&edaPath[MAX_NAME_LEN], ".eda");	
	else
		strcpy(&edaPath[endName - path], ".eda");

	ofstream eda(edaPath, ios_base::binary);
	if (!eda.good())	//si no puedo crear el archivo .eda, no sigo
		return false;
	
	unsigned char * rawData;
	unsigned int width, height;

	if (lodepng_decode32_file(&rawData, &width, &height, path) != 0 || width == 0 || (width != height) 
		|| (width & (width - 1)) != 0 ) {	//verificar que no se devuelva error, que la imagen sea cuadrada y
		eda.close();													//que su tamano sea una potencia de 2
		remove(edaPath);	//el archivo .eda quedo vacio, lo borro
		return false;					
	}

	//para obtener el threshold: llevo el porcentaje a un numero entre 0 y 255, considerando ademas que cuanto 
	//mas grande sea el porcentaje mas chico tiene que ser el threshold ( p ej fid == 100% => thres == 0)
	comp_t c = {rawData, width, &eda, 255 - (unsigned char)(fidelity*255.0/100.0)};
	quadtree(&c, width, 0, 0);	//la compresion comienza en el pixel (0,0), tomando el ancho total de la imagen como lado

	eda.close();
	free(rawData);
	return true;
}

void quadtree(comp_t * c, unsigned int side, unsigned int x, unsigned int y)
{
	float rmed = 0, gmed = 0, bmed = 0; //los promedios empiezan en 0 porque despues voy a ir sumando lo que encuentre
	unsigned char rmin = 255, gmin = 255, bmin = 255, rmax = 0, gmax = 0, bmax = 0;
	//los maximos tienen que empezar en 0 y los minimos en 255 para que no afecte el valor inicial a la comparacion
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

	if( rmax - rmin + gmax - gmin + bmax - bmin < c->threshold || side == 1 ) { //CASO BASE
		//escribir "0RGB" con los promedios
		rmed /= side*side;	gmed /= side*side;	bmed /= side*side;
		*(c->out) << '0' << (unsigned char)rmed << (unsigned char)gmed << (unsigned char)bmed;

		return;
	}
	else { //NO ESTOY EN EL CASO BASE: CONTINUO LA RECURSION
		*(c->out) << '1'; //indicar que se hizo una division mas de este cuadrante de la imagen
		side/=2;		//ahora los cuadrantes tienen la mitad de lado que antes

		quadtree(c, side, x, y); //primer cuadrante: mismas coords init
		quadtree(c, side, x+side, y); //2do cuad: misma altura, corro x hasta la mitad del cuadrante que recibi
		quadtree(c, side, x, y+side); //3er cuad: vuelvo x a donde estaba, corro y hasta la mitad del cuadrante
		quadtree(c, side, x+side, y+side); //4to cuad: a x0 e y0 hay que correrlos hasta la mitad del cuadrante
	}

}



bool qtDecompress(char * path, unsigned int size)
{
	if (path == NULL || size == 0 || (size & (size-1)) != 0 )
		return false;	//verificar los parametros recibidos
	
	char * endName = strstr(path, ".eda");	// verificar que el path corresponde a un archivo .eda
	if (endName == NULL)
		return false;

	char pngPath[MAX_NAME_LEN+5];			// obtengo el nombre del archivo png que se creara
	strncpy(pngPath, path, MAX_NAME_LEN);
	if(endName - path >= MAX_NAME_LEN)
		strcpy(&pngPath[MAX_NAME_LEN], ".png");	
	else 
		strcpy(&pngPath[endName - path], ".png");

	ifstream eda(path, ios_base::binary);						// verifico que el archivo recibido exista
	if(!eda.good())
		return false;

	unsigned char * rawData = new unsigned char[size*size*PIXEL_SIZE]; 
	bool isValid = true;	//codigo de error
	
	dec_t d = {rawData, size, &eda};	
	//la recursion empieza con lado == ancho de la imagen, en el 0,0
	if ( quadtree(&d, size, 0, 0) == false || lodepng_encode32_file(pngPath, rawData, size, size) != 0 )
		isValid = false;	//si no pude descomprimir o pasar a png, devuelvo false

	eda.close();
	return isValid;
}




bool quadtree(dec_t * d, unsigned int side, unsigned int x, unsigned int y)
{
	unsigned char nextChar = d->in->get();	//me fijo si tengo que dividir el cuadrante actual o no
	bool isValid = true;

	switch (nextChar) {
		case '1':	{// se vuelve a dividir la imagen: continuo la recursividad.
			side/=2;

			if (	quadtree(d, side, x, y) == false ||	//primer cuad
					quadtree(d, side, x+side, y) == false ||	//2do cuad
					quadtree(d, side, x, y+side) == false ||	//3er cuad
					quadtree(d, side, x+side, y+side) == false	)	//4to cuad
				isValid = false;	//si cualquiera devuelve error, se devuelve error
		}
		break;

		case '0': { //CASO BASE: leo rgb y lo copio al archivo
			unsigned char * p;	//puntero auxiliar al pixel
			unsigned char rgba[PIXEL_SIZE] = {d->in->get(), d->in->get(), d->in->get(), 255};
			//leo los rgb del archivo y pongo alpha como el maximo

			for (unsigned int  j = y; j<y+side; j++) {
				p = d->start + PIXEL_SIZE * ( j*d->imgSide + x );
				for (unsigned int i = 0; i<side; i++) {
					memcpy(p, rgba, PIXEL_SIZE);	//guardar los RGBA obtenidos en todo el cuadrante
					p+=PIXEL_SIZE;
				}
			}
		}
		break;

		default: 
			isValid = false; //el archivo no respetaba el formato que tenia que tener
	}

	return isValid;	//si llegue hasta aca no hubo error
}