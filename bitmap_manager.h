/*
	HEADERS DE FUNCIONES PARA MANEJADOR DE IMAGENES
*/

#ifndef _BITMAP_MANAGER_H
#define _BITMAP_MANAGER_H

#include "util.h"
#include "pixel.h"

typedef unsigned int DWORD;
typedef unsigned short WORD;
typedef int LONG;

#pragma pack(push, 1)

typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;	/* Especifica el tipo de archivo. */
    DWORD bfSize;	/* Especifica el tamaño en bytes del archivo bitmap. */
    WORD bfReserved1;/* Reservado; en estos casos debe ser 0. */
    WORD bfReserved2;/* Reservado; en estos casos debe ser 0. */
    DWORD bfOffBits;  /* Indica el offset en bytres desde este header hasta los bits del bitmap. */
}BITMAPFILEHEADER;


typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;	/* Especifica el numero de bytes que necesita esta estructura. */
    LONG biWidth;	/* Indica el ancho en pixeles. */
    LONG biHeight;	/* Indica la altura en pixeles. */
    WORD biPlanes;	/* Indica la cantidad de niveles de colores, debe ser 1. */
    WORD biBitCount;	/* Indica la cantidad de bits por pixel. */
    DWORD biCompression;/* Especifica el tipo de compresion. */
    DWORD biSizeImage;	/* Tamaño de la imagen en bytes. */
    LONG biXPelsPerMeter;/* Cantidad de pixeles por metro en el eje x. */
    LONG biYPelsPerMeter;/* Cantidad de pixeles por metro en el eje y. */
    DWORD biClrUsed;	/* Cantidad de colores utilizados por el bitmap. */
    DWORD biClrImportant;/* Numero de colores que son importantes. */
}BITMAPINFOHEADER;

#pragma pack(pop)

/**
 * Funcion que carga una imagen en formato bmp y la retorna como un matriz de pixeles RGB,
 * y su header (parametro).
 * 
 * Entrada:
 *	filename		- Nombre del archivo de la imagen a cargar.
 *	bitmapInfoHeader- Donde se almacena la informacion del header de la imagen.
 * 
 * Salida: Matriz de pixeles con los pixeles de la imagen.
 */
Pixel** load_bitmap_file(char *filename, BITMAPINFOHEADER* bitmapInfoHeader);

/**
 * Funcion que almacena una imagen en formato bitmap, con el nombre filename, de acuerdo
 * a la informacion almacenada en el header original y a la nueva matriz reducida de pixeles.
 * 
 * Entrada:
 *	filename		- Nombre del archivo a crear y donde se guarda la imagen.
 *	bitmapInfoHeader- Informacion sobre el header original de la imagen en formato bitmap.
 *	bitmapPixels 	- La matriz de pixeles que se quiere guardar.
 * 	height 			- Altura en pixeles de la matriz de pixeles del bitmap.
 * 	width 			- Largo en pixeles de la matriz de pixeles del bitmap.
 * 
 * Salida: 
 */
void save_bitmap_file(char* filename, BITMAPINFOHEADER* bitmapInfoHeader, Pixel** bitmapPixels, int height, int width);

/**
 * Funcion que transforma una matriz de pixeles (su uso normal es la imagen reducida), en un
 * arreglo de unsigned char (pixeles en BGR), que es el formato que utilizan los bitmaps para
 * almancenar su informacion sobre los pixeles, hay que tener en cuenta que como el bmp utilizado
 * usa 24 bits, se debe rellenar las columnas con 0s hasta que se llegue a un multiplo de 4 bytes.
 * 
 * Entrada:
 *	bitmapPixels- Matriz de pixeles que se obtiene principalmente al cargar una imagen.
 *	width 		- Largo (columnas) que posee la matriz de pixeles.
 *	height 		- Altura (filas) que posee la matriz de pixeles.
 * 
 * Salida: Arreglo de unsigned char que poseen la informacion de la matriz de pixeles en
 * un formato que usa para almacenarlo en un archivo en formato bmp.
 */
unsigned char* unload_pixels(Pixel** bitmapPixels, int width, int height);

/**
 * Metodo que copia los datos de un BITMAPINFOHEADER en otro BITMAPINFOHEADER.
 * 
 * Entrada:
 *	dest	- BITMAPINFOHEADER donde se guarda una copia del otro BITMAPINFOHEADER.
 *	src 	- BITMAPINFOHEADER de donde se copian los datos.
 */
void bitmap_header_copy(BITMAPINFOHEADER* dest, BITMAPINFOHEADER* src);

#endif