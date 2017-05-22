#ifndef QUADTREE_H
#define QUADTREE_H

/*
	Instituto Tecnológico de Buenos Aires
	22.08 - Algoritmos y Estructuras de Datos
	Trabajo Práctico n° 8 - Listas y árboles
	Grupo 2:	- Parra, Rocío					- legajo 57.669
				- Pierdominici, Matías Nicolás	- legajo 57.498
				- Stewart Harris, María Luz		- legajo 57.676
**************************************************************************************************
	Compresor / descompresor de imágenes de formato PNG basado en el algoritmo Quad Tree.
*/






#define MAX_NAME_LEN	20
//	longitud maxima para el nombre de un archivo que crean estan funciones (sin la extension). si el path recibido tiene
//una longitud superior a este parametro, el nombre del archivo se truncara. por ejemplo, si MAX_NAME_LEN esta definido 
//como 3 y recibo el archivo "nombre.png", el archivo comprimido se llamara "nom.eda"
//	a su vez, si el nombre del archivo recibido contiene una secuencia de caracteres igual a su extension, se recortara
//hasta ese punto. por ejemplo, si descomprimo el archivo "nombre.eda.eda", se creara un archivo llamado "nombre.png"

bool qtCompress(char * path, float fidelity);
/*		recibe el path de una IMAGEN CUADRADA EN FORMATO PNG, cuyo lado en pixeles es una potencia de 2, y genera un
	archivo con el mismo nombre con extension ".eda" con esa imagen comprimida segun el algoritmo Quad Tree. Devuelve true 
	si pudo comprimir exitosamente y false en caso contrario.
		el parametro 'fidelity' determinara que tanto se comprimira la imagen: cuanto mas alto, mas calidad se conservara 
	y menos se comprimira y viceversa. debe ser un numero mayor que 0 y menor que 100 (~=porcentaje de calidad de la imagen
	que se obtendra)
*/

bool qtDecompress(char * path, unsigned int size);
/*		realiza la operacion inversa a qtCompress(). recibe el path del archivo .eda que se desea descomprimir, y crea una
	archivo de tipo .png con la imagen descomprimida, de tamano size x size en pixeles. size debe ser una potencia de 2 
		devuelve true si pudo realizar la descompresion y viceversa. */


#endif //QUADTREE_H
