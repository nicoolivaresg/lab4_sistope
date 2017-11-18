#include "image_reduction.h"

void image_read_initialize(Image* image, char* filename, int m) {
	BITMAPINFOHEADER bitmapInfoHeader;
	image->bitmapPixels = load_bitmap_file(filename, &bitmapInfoHeader);

	image->bitmapInfoHeader = malloc(sizeof(*(image->bitmapInfoHeader)));
	bitmap_header_copy(image->bitmapInfoHeader, &bitmapInfoHeader);

	image->height = bitmapInfoHeader.biHeight;
	image->width = bitmapInfoHeader.biWidth;

	image->pixelAverage = m;
}

void image_free(Image* image) {
	int row;
    for(row = 0; row < image->bitmapInfoHeader->biHeight; row++) {
    	free(image->bitmapPixels[row]);
    }
    free(image->bitmapPixels);

    free(image->bitmapInfoHeader);
}

void image_reduction_init(Image * image) {
	
	image->reducedBitmapPixels = (Pixel **)malloc(image->reducedHeight *sizeof(Pixel *));
	
	int i,j;
	for (i = 0; i < image->reducedHeight; i++ ) {
		
		image->reducedBitmapPixels[i] = (Pixel *)malloc(image->reducedWidth * sizeof(Pixel)); 
		
		for ( j = 0; j < image->reducedWidth; j++){
			pixel_init(&image->reducedBitmapPixels[i][j],0,0,0);
		}
	}
}



void image_reduction_method1(Image* image) {
	int i = 0, j, indexNewColumn = 0;
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
	

	image_reduction_init(image);

	int salir = 0;
	//Recorrer filas desde i = 0 : height-1
	//while ( i < image->height){
			j = 0;
			//Recorrer pixeles hasta el pixel m
			while( j < image->width && salir != 1){
				if( count_pixels == 0 ){
					
					//Promedio de RED
					averageR = sumR/image->pixelAverage;
					//Promedio de GREEN
					averageG = sumG/image->pixelAverage;
					//Promedio de BLUE
					averageB = sumB/image->pixelAverage;
				

					image->reducedBitmapPixels[i][indexNewColumn].R = averageR;
					image->reducedBitmapPixels[i][indexNewColumn].G = averageG;
					image->reducedBitmapPixels[i][indexNewColumn].B = averageB;
					printf("En la posición I(%d,%d) reduce a R(%d,%d) = [%d,%d,%d]\n", i,j,i,indexNewColumn,image->reducedBitmapPixels[i][indexNewColumn].R,image->reducedBitmapPixels[i][indexNewColumn].G,image->reducedBitmapPixels[i][indexNewColumn].B);
					//Reinicio sumas
					sumR = 0;
					sumG = 0;
					sumB = 0;
					//Reinicio del contador de pixeles;
					count_pixels = image->pixelAverage;

					//Fila con indice par va de izquierda a derecha y fila con indice impar va de derecha a izquierda
					if( i % 2 == 0){
						indexNewColumn++;
					}else{
						indexNewColumn--;
					}
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
				//printf("Datos iteración");
				//getchar();
				

				if( (i % 2 == 0) && (j == image->width - remaining_pixels ) ){
					i++;
					printf("i:%d j:%d NC:%d\n", i,j,indexNewColumn);
					if(i == image->height){
						printf("%d\n", salir);
						salir = 1;
					}
				}else if ( (i % 2 != 0) && (j == 0) ){
					i++;
					if(i == image->height){
						printf("%d\n", salir);
						salir = 1;
					}
				}
			}
	//	i++;
	//}
}

void image_reduction_method2(Image* image) {
	
}


void image_write(Image * image, char* filename) {
	save_bitmap_file(filename, image->bitmapInfoHeader, image->bitmapPixels, image->height, image->width);
}