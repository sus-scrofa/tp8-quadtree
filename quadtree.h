#ifndef QUADTREE_H
#define QUADTREE_H

#define MAX_NAME_LEN	2
//	longitud maxima para el nombre de un archivo que crean estan funciones (sin la extension). si el path recibido tiene
//una longitud superior a este parametro, el nombre del archivo se truncara. por ejemplo, si MAX_NAME_LEN esta definido 
//como 3 y recibo el archivo "nombre.png", el archivo comprimido se llamara "nom.eda"
//	a su vez, si el nombre del archivo recibido contiene una secuencia de caracteres igual a su extension, se recortara
//hasta ese punto. por ejemplo, si descomprimo el archivo "nombre.eda.eda", se creara un archivo llamado "nombre.png"

bool qtCompress(char * path, unsigned int threshold);
/*		recibe el path de una IMAGEN CUADRADA EN FORMATO PNG, y genera un archivo con el mismo nombre con extension ".eda"
	con esa imagen comprimida segun el algoritmo Quad Tree. Devuelve true si pudo comprimir exitosamente y false en caso
	contrario.
		el parametro 'threshold' determinara que tanto se comprimira la imagen: cuanto mas alto, mas calidad se conservara 
	y menos se comprimira y viceversa. debe ser un numero mayor a 0 y menor a 255.
		size debe ser una potencia de 2 
		*/

bool qtDecompress(char * path, unsigned int size);
/*		realiza la operacion inversa a qtCompress(). recibe el path del archivo .eda que se desea descomprimir, y crea una
	archivo de tipo .png con la imagen descomprimida, de tamano size x size en pixeles. size debe ser una potencia de 2 
		devuelve true si pudo realizar la descompresion y viceversa. */


#endif //QUADTREE_H