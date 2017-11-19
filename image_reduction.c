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
    for(row = 0; row < image->height; row++) {
    	free(image->bitmapPixels[row]);
    }
    free(image->bitmapPixels);

    for(row = 0; row < image->reducedHeight; row++) {
    	free(image->reducedBitmapPixels[row]);
    }
    free(image->reducedBitmapPixels);

    free(image->bitmapInfoHeader);
}

void image_reduction_init(Image * image, int method) {

	// Ancho y altura de imagen al reducir	
	if (method ==1){
		//Valor de la nueva cantidad de columnas en la reducción
		int reductionCols = image->width / image->pixelAverage;
		image->reducedWidth = reductionCols;
		image->reducedHeight = image->height;
	}else{
		//Valor de la nueva cantidad de columnas en la reducción
		int reductionRows = image->height / image->pixelAverage;
		image->reducedWidth = image->width;
		image->reducedHeight = reductionRows; 
	}
	
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
	/*
	int i, k, j, indexNewColumn = 0;
	//Contador para determinar cuando toque sacar el promedio porque se alcanzan los m pixeles
	int count_pixels = image->pixelAverage;
	//Contador para sumar el valor de los pixeles
	int sumR = 0,sumG = 0,sumB = 0;
	int averageR = 0,averageG = 0,averageB = 0;

	//Valor del exceso o resto de pixeles que son igual o menor que el valor de m
	int remaining_pixels = image->width % image->pixelAverage;

	//Inicialización de matriz de 
	image_reduction_init(image,1);

	i = 0;
	j = 0;
	k = 0;
	do
	{	
		if( i % 2 == 0){
			//Si recorro de izq a der
			while( j < image-> width ){
				if( j == image->width - 1 - remaining_pixels && remaining_pixels != 0){
					//Si llego al primer pixel restante, porque faltan pixeles hasta el borde
					//Reinicio de sumas
					sumR = 0;
					sumG = 0;
					sumB = 0;
					k = 0;
					for (k = j; k < image->width; k++)
					{
						//Suma de RED
						sumR = sumR + image->bitmapPixels[i][k].R;
						//Suma de GREEN
						sumG = sumG + image->bitmapPixels[i][k].G;
						//Suma de BLUE
						sumB = sumB + image->bitmapPixels[i][k].B;	
					}

					averageR = sumR/remaining_pixels;
					averageG = sumG/remaining_pixels;
					averageB = sumB/remaining_pixels;
					for(k = 0; k <  ( image->pixelAverage - remaining_pixels ); k++ ){
						sumR = sumR + averageR;
						sumG = sumG + averageG;
						sumB = sumB + averageB;
					}

					averageR = sumR/image->pixelAverage;
					averageG = sumG/image->pixelAverage;
					averageB = sumB/image->pixelAverage;

					image->reducedBitmapPixels[i][indexNewColumn].R = averageR;
					image->reducedBitmapPixels[i][indexNewColumn].G = averageG;
					image->reducedBitmapPixels[i][indexNewColumn].B = averageB;

					//Salgo del ciclo
					j = image->width;

					//Reinicio sumas
					sumR = 0;
					sumG = 0;
					sumB = 0;
					//Reinicio del contador de pixeles;
					count_pixels = image->pixelAverage;
	
				}else{
					//Para todos los demás pixeles, serían los agrupables y reducibles por m pixels
					//Suma de RED
					sumR = sumR + image->bitmapPixels[i][j].R;
					//Suma de GREEN
					sumG = sumG + image->bitmapPixels[i][j].G;
					//Suma de BLUE
					sumB = sumB + image->bitmapPixels[i][j].B;	
					
					//Disminución del contador de pixeles;
					count_pixels--;

					if( count_pixels == 0 ){
						
						//Promedio de RED
						averageR = sumR/image->pixelAverage;
						//Promedio de GREEN
						averageG = sumG/image->pixelAverage;
						//Promedio de BLUE
						averageB = sumB/image->pixelAverage;
						
						averageR = sumR + (remaining_pixels * averageR);
						
						averageG = sumG + (remaining_pixels * averageG);
						
						averageB = sumB + (remaining_pixels * averageB);
					
						
	printf("%d\n", indexNewColumn);
						image->reducedBitmapPixels[i][indexNewColumn].R = averageR;
						image->reducedBitmapPixels[i][indexNewColumn].G = averageG;
						image->reducedBitmapPixels[i][indexNewColumn].B = averageB;
						
						//Reinicio sumas
						sumR = 0;
						sumG = 0;
						sumB = 0;
						//Reinicio del contador de pixeles;
						count_pixels = image->pixelAverage;

						indexNewColumn++;
						
					}
				}
				j++;
			}

			j = image->width - 1;

		}else{
			//Si recorro de der a izq
			while( j >= 0){

				if( j == remaining_pixels && remaining_pixels != 0){
					//Si llego al primer pixel restante, porque faltan pixeles hasta el borde
					
					//Reinicio de sumas
					sumR = 0;
					sumG = 0;
					sumB = 0;

					k = 0;
					for (k = j; k >= 0; k--)
					{
						//Suma de RED
						sumR = sumR + image->bitmapPixels[i][k].R;
						//Suma de GREEN
						sumG = sumG + image->bitmapPixels[i][k].G;
						//Suma de BLUE
						sumB = sumB + image->bitmapPixels[i][k].B;	
					}

					averageR = sumR/remaining_pixels;
					averageG = sumG/remaining_pixels;
					averageB = sumB/remaining_pixels;

					for(k = 0; k <  ( image->pixelAverage - remaining_pixels ); k++ ){
						sumR = sumR + averageR;
						sumG = sumG + averageG;
						sumB = sumB + averageB;
					}

					averageR = sumR/image->pixelAverage;
					averageG = sumG/image->pixelAverage;
					averageB = sumB/image->pixelAverage;

					image->reducedBitmapPixels[i][indexNewColumn].R = averageR;
					image->reducedBitmapPixels[i][indexNewColumn].G = averageG;
					image->reducedBitmapPixels[i][indexNewColumn].B = averageB;
					
					//Salgo del ciclo
					j = -1;

					//Reinicio sumas
					sumR = 0;
					sumG = 0;
					sumB = 0;

					//Reinicio del contador de pixeles;
					count_pixels = image->pixelAverage;
	
				}else{
					//Para todos los demás pixeles, serían los agrupables y reducibles por m pixels
					
					//Suma de RED
					sumR = sumR + image->bitmapPixels[i][j].R;
					//Suma de GREEN
					sumG = sumG + image->bitmapPixels[i][j].G;
					//Suma de BLUE
					sumB = sumB + image->bitmapPixels[i][j].B;	
					
					//Disminución del contador de pixeles;
					count_pixels--;

					if( count_pixels == 0 ){
						
						//Promedio de RED
						averageR = sumR/image->pixelAverage;
						//Promedio de GREEN
						averageG = sumG/image->pixelAverage;
						//Promedio de BLUE
						averageB = sumB/image->pixelAverage;
						
						averageR = sumR + (remaining_pixels * averageR);
						
						averageG = sumG + (remaining_pixels * averageG);
						
						averageB = sumB + (remaining_pixels * averageB);
					
						
						image->reducedBitmapPixels[i][indexNewColumn].R = averageR;
						image->reducedBitmapPixels[i][indexNewColumn].G = averageG;
						image->reducedBitmapPixels[i][indexNewColumn].B = averageB;
						
						//Reinicio sumas
						sumR = 0;
						sumG = 0;
						sumB = 0;
						//Reinicio del contador de pixeles;
						count_pixels = image->pixelAverage;

						indexNewColumn--;
						
					}
				}
				j--;
			}
			j = 0;
		}
		i++;
	} while ( i < image->width );*/

	int i, k, j, c;

	int averageR, averageB, averageG;
	image_reduction_init(image,1);

	for(i = 0; i < image->reducedHeight; i++) {
		if(i % 2 == 0) {
			for(j = 0; j < image->reducedWidth; j++) {
				averageR = 0, averageB = 0, averageG = 0;
				for(k = j*image->pixelAverage, c = 0; c < image->pixelAverage; c++, k++) {
					if(k >= image->width || k < 0) {
						averageR += 125;
						averageG += 125;
						averageB += 125;
						continue;
					}
					averageR += image->bitmapPixels[i][k].R;
					averageG += image->bitmapPixels[i][k].G;
					averageB += image->bitmapPixels[i][k].B;
				}
				averageR /= image->pixelAverage;
				averageG /= image->pixelAverage;
				averageB /= image->pixelAverage;

				pixel_init(&(image->reducedBitmapPixels[i][j]), averageR, averageG, averageB);
			}
		} else if(i % 2 == 1) {
			for(j = image->reducedWidth-1; j >= 0; j--) {
				averageR = 0, averageB = 0, averageG = 0;
				for(k = (j*image->pixelAverage) + image->pixelAverage - 1, c = 0; c < image->pixelAverage; c++, k--) {
					if(k >= image->width || k < 0) {
						averageR += 125;
						averageG += 125;
						averageB += 125;
						continue;
					}
					averageR += image->bitmapPixels[i][k].R;
					averageG += image->bitmapPixels[i][k].G;
					averageB += image->bitmapPixels[i][k].B;
				}
				averageR /= image->pixelAverage;
				averageG /= image->pixelAverage;
				averageB /= image->pixelAverage;

				pixel_init(&(image->reducedBitmapPixels[i][j]), averageR, averageG, averageB);
			}
		}
	}
}

void image_reduction_method2(Image* image) {
	int i, k, j, c;
	//Contador para sumar el valor de los pixeles
	int averageR = 0,averageG = 0,averageB = 0;

	//Inicialización de matriz de 
	image_reduction_init(image,2);

	for(j = 0; j < image->reducedWidth; j++) {
		for(i = 0, k = 0; i < image->reducedHeight; i++) {
			averageR = 0, averageB = 0, averageG = 0;
			for(k = i*image->pixelAverage, c = 0; c < image->pixelAverage; c++, k++) {
				if(k >= image->height) {
					averageR += 125;
					averageG += 125;
					averageB += 125;
				}
				averageR += image->bitmapPixels[k][j].R;
				averageG += image->bitmapPixels[k][j].G;
				averageB += image->bitmapPixels[k][j].B;
			}
			averageR /= image->pixelAverage;
			averageG /= image->pixelAverage;
			averageB /= image->pixelAverage;

			pixel_init(&(image->reducedBitmapPixels[i][j]), averageR, averageG, averageB);
		}
	}
}

void image_write(Image * image, char* filename) {
	save_bitmap_file(filename, image->bitmapInfoHeader, image->bitmapPixels, image->height, image->width);
}

void image_write_reduction(Image * image, char * filename){
	save_bitmap_file(filename, image->bitmapInfoHeader, image->reducedBitmapPixels, image->reducedHeight, image->reducedWidth);
}