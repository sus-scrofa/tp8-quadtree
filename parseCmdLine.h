//////////////////////////////////////////////////////////////////////////////////////////////////////////////														
//																											//
//		Instituto Tecnológico de Buenos Aires.																//
//														   /////////////// 									//
//		22.08 - Algoritmos y Estructura de Datos.		  // CALLBACKS //									//
//														 ///////////////									//	
//		Trabajo Práctico n° 1.																				//
//																											//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////														
//																											//
//																											//
//	Consigna: 																								//
//																											//
//	Se pide diseñar una librería que procese los argumentos recibidos por línea de 							//										
//	comando usando un callback. 																			//
//																											//
//	El diseño debe cumplir con las siguientes pautas: 														//
//																											//
//		a. Debe poder procesar opciones. Una opción consiste de dos argumentos: el 							//									
//		primero comienza con un guion (“-”) y se denomina clave, y el segundo se 							//
//		denomina valor. Un ejemplo: webserver -maxclients 4.  												//
//																											//
//		b. Debe poder procesar parámetros, que es un argumento aislado que no 								//
//		comienza con guion. Un ejemplo: copyfile archivo1.c.												//
//																											//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																											//
//	GRUPO 5																									//
//																											//
//	************************************																	//
//	||		AUTORES		 ||  LEGAJO   ||																		//
//	************************************																	//
//	|| Álvarez, Lisandro ||  57.771   ||																	//
//	|| Lago, Valentina   ||  57.249   ||																	//
//	|| Parra, Rocío      ||  57.669   ||																	//
//	************************************																	//
//																											//
//	Fecha de entrega: martes 14 de marzo de 2017.															//
//																											//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PARSECMDLINE_H
#define PARSECMDLINE_H



typedef int(*pCallback) (char *, char*, void *);
/* 
 *  El callback que recibe el parser:
 *
 *	- Recibe:
 *  
 *		-> El string correspondiente a la clave de una opcion, o un puntero a null si se trata de un 
 *   		parametro.
 *
 * 		-> El string correspondiente al valor de una opcion o a un parametro.
 *
 * 		-> La direccion inicial de donde se deben almacenar los argumentos parseados (de ser validos).
 *	
 *	- Devuelve:
 *    
 *		-> 1, si el contenido recibido es valido.
 *
 *		-> 0, si el contenido recibido es INvalido.
 *
 */


int parseCmdLine(int argc, char *argv[], pCallback p, void *userData);
/*  
 *  Parser de linea de comando:
 *
 *	- Recibe:
 *
 * 		-> Los argumentos recibidos por el main (contador y vector de argumentos).
 *
 *		-> Un puntero al callback que valida el contenido parseado 
 *
 * 		-> Un puntero a la posicion de memoria a partir de la cual se desea que dicho callback almacene los datos.
 *
 *	Se valida la forma y el contenido de la linea de comando y devuelve:
 *  
 *		-> La suma de opciones y parametros procesados si estos fueron validos.
 *
 *		-> (-1) si hubo un error en los datos procesados.
 *
 */

#endif //PARSECMDLINE_H