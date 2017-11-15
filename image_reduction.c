#include "image_reduction.h"

void image_read_initialize(Image* image, char* filename, int m) {
	BITMAPINFOHEADER bitmapInfoHeader;
	image->bitmapPixels = load_bitmap_file(filename, &bitmapInfoHeader);
	image->bitmapInfoHeader = &bitmapInfoHeader;
	image->height = bitmapInfoHeader.biHeight;
	image->width = bitmapInfoHeader.biWidth;

	image->pixelAverage = m;
}


void image_reduction_method1(Image* image) {
	int i = 0, j, newColumn;
	//Contador para determinar cuando toque sacar el promedio porque se alcanzan los m pixeles
	int count_pixels = image->pixelAverage;
	//Contador para sumar el valor de los pixeles
	int sumR = 0,sumG = 0,sumB = 0;
	int averageR = 0,averageG = 0,averageB = 0;

	//Valor de la nueva cantidad de columnas en la reducción
	int reductionCols = image->width / image->pixelAverage + 1;
	image->reducedWidth = reductionCols;
	//Valor del exceso o resto de pixeles que son igual o menor que el valor de m
	int remaining_pixels = image->height % image->pixelAverage;
	image->reducedHeight = image->width;

	//Recorrer filas desde i = 0 : rows-1
	while ( i < image->height ){
			j = 0;
			//Recorrer pixeles hasta el pixel m
			while( j < image->width ){
				if( count_pixels == 0 ){
					//Fila con indice par va de izquierda a derecha y fila con indice impar va de derecha a izquierda
					if( i % 2 == 0){

					}else{

					}
					//Promedio de RED
					averageR = sumR/image->pixelAverage;
					//Promedio de GREEN
					averageG = sumG/image->pixelAverage;
					//Promedio de BLUE
					averageB = sumB/image->pixelAverage;

					//Asignación de promedio a reducción
					newColumn = j - image->pixelAverage + 1;

					image->reducedBitmapPixels[i][newColumn].R = averageR;
					image->reducedBitmapPixels[i][newColumn].G = averageG;
					image->reducedBitmapPixels[i][newColumn].B = averageB;
					printf("En la posición I(%d,%d) reduce a R(%d,%d) = [%d,%d,%d]\n", i,j,i,newColumn,averageR,averageG,averageB);
					//Reinicio sumas
					sumR = 0;
					sumG = 0;
					sumB = 0;
					//Reinicio del contador de pixeles;
					count_pixels = image->pixelAverage;
				}
				//Suma de RED
				sumR = sumR + image->bitmapPixels[i][j].R;
				//Suma de GREEN
				sumG = sumG + image->bitmapPixels[i][j].G;
				//Suma de BLUE
				sumB = sumB + image->bitmapPixels[i][j].B;
				//Disminución del contador de pixeles;
				count_pixels--;
				//Fila con indice par va de izquierda a derecha y fila con indice impar va de derecha a izquierda
				if( i % 2 == 0){
					j++;
				}else{
					j--;
				}
			}

		
		
		i++;
	}
}

void image_reduction_method2(Image* image) {
	
}


void image_write(Image * image, char* filename) {
	save_bitmap_file(filename, image->bitmapInfoHeader, image->bitmapPixels, image->height, image->width);
}