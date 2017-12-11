/*
	HEADERS DE FUNCIONES PARA MANEJADOR DE IMAGENES
*/

#ifndef _PIXEL_H
#define _PIXEL_H

#include "util.h"

/**
 * Estructura para los pixeles, almacena el RGB (Red, Green, Blue) para un pixel.
 */
typedef struct pixel {
	unsigned char R, G, B;
} Pixel;

/**
 * Inicializa un pixel con los datos entregados en los parametros.
 *
 * Entrada:
 *	R 	- Color Rojo del pixel.
 *	G 	- Color Verde del pixel.
 *	B 	- Color Azul del pixel.
 */
void pixel_init(Pixel* pixel, unsigned char Red, unsigned char Green, unsigned char Blue);

#endif