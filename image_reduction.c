#include "image_reduction.h"

void image_read_initialize(Image* image, char* filename, int m) {
	FILE* input = fopen(filename, "r");

	image->mPixels = m;

	// Somehow read image and allocate memory for matrix, reduction and N, M


	fclose(input);
}


void image_reduction_method1(Image* image) {
	int i = 0, j;
	//Contador para determinar cuando toque sacar el promedio porque se alcanzan los m pixeles
	int count_pixels = image->mPixels;
	//Contador para sumar el valor de los pixeles
	int sumR = 0,sumG = 0,sumB = 0;
	int averageR = 0,averageG = 0,averageB = 0;

	//Valor de la nueva cantidad de columnas en la reducción
	int reduction_rows = image->cols / image->mPixels + 1;
	//Valor del exceso o resto de pixeles que son igual o menor que el valor de m
	int remaining_pixels = image->rows % image->mPixels;

	//Recorrer filas desde i = 0 : rows-1
	while ( i < image->rows ){
		//Fila con indice par va de izquierda a derecha y fila con indice impar va de derecha a izquierda
		if( i % 2 == 0){
			j = 0;
			//Recorrer pixeles hasta el pixel m
			while( j < image->cols ){
				if( count_pixels == 0 ){
					//Promedio de RED
					averageR = sumR/image->mPixels;
					//Promedio de GREEN
					averageG = sumG/image->mPixels;
					//Promedio de BLUE
					averageB = sumB/image->mPixels;

					//Asignación de promedio a reducción
					newColumn = j - image->mPixels + 1;

					image->reduction[i][newColumn][0] = averageR;
					image->reduction[i][newColumn][1] = averageG;
					image->reduction[i][newColumn][2] = averageB;
					printf("En la posición I(%d,%d) reduce a R(%d,%d) = [%d,%d,%d]\n", i,j,i,newColumn,averageR,averageG,averageB);
					//Reinicio sumas
					sumR = 0;
					sumG = 0;
					sumB = 0;
					//Reinicio del contador de pixeles;
					count_pixels = image->mPixels;
				}
				//Suma de RED
				sumR = sumR + image->matrix[i][j][0];
				//Suma de GREEN
				sumG = sumG + image->matrix[i][j][1];
				//Suma de BLUE
				sumB = sumB + image->matrix[i][j][2];
				//Disminución del contador de pixeles;
				count_pixels--;
				j++;	
			}

		}else{
			j = image->cols;
			//Recorrer pixeles hasta el pixel m
			while( j > 0 ){
				if( count_pixels == 0 ){
					//Promedio de RED
					averageR = sumR/image->mPixels;
					//Promedio de GREEN
					averageG = sumG/image->mPixels;
					//Promedio de BLUE
					averageB = sumB/image->mPixels;

					//Asignación de promedio a reducción
					newColumn = j - image->mPixels + 1;

					image->reduction[i][newColumn][0] = averageR;
					image->reduction[i][newColumn][1] = averageG;
					image->reduction[i][newColumn][2] = averageB;
					printf("En la posición I(%d,%d) reduce a R(%d,%d) = [%d,%d,%d]\n", i,j,i,newColumn,averageR,averageG,averageB);
					//Reinicio sumas
					sumR = 0;
					sumG = 0;
					sumB = 0;
					//Reinicio del contador de pixeles;
					count_pixels = image->mPixels;
				}
				//Suma de RED
				sumR = sumR + image->matrix[i][j][0];
				//Suma de GREEN
				sumG = sumG + image->matrix[i][j][1];
				//Suma de BLUE
				sumB = sumB + image->matrix[i][j][2];
				//Disminución del contador de pixeles;
				count_pixels--;
				j--;	
			}
		}
		
		i++;
	}
}

void image_reduction_method2(Image* image) {
	
}


void image_write(Image * image, char* filename) {
	FILE* output = fopen(filename, "w");

	// Somehow write image to file using fwrite

	fclose(output);
}