#include "util.h"
#include "image_reduction.h"
#include <time.h>

int main(int  argc, char ** argv){
	int i, j;
	int iflag = 0;//Flag nombre de archivo de entrada
	int sflag = 0;//Flag nombre de archivo de salida metodo 1
	int gflag = 0;//Flag nombre de archivo de salida metodo 2
	int nflag = 0;//Flag cantidad de veces a implementar la reduccion
	int mflag = 0;//Flag cantidad de pixeles a promediar
	int oflag = 0;//Flag del metodo a implementar
	int dflag = 0;//Flag mostrar resultados por pantalla
	char * input_file = NULL;
	char * output_method1_file = NULL;
	char * output_method2_file = NULL;
	int iterations = 0;
	int pixels_to_average = 0;
	int methods_to_execute = 0;
	int c;
	opterr=0;
	while((c = getopt(argc,argv,"i:s:g:n:m:o:d")) != -1){
		switch(c){
			case 'i':
				iflag = 1;
				input_file = malloc(strlen(optarg)+1);
				strcpy(input_file,optarg);
				break;
			case 's':
				sflag = 1;
				output_method1_file = malloc(strlen(optarg)+1);
				strcpy(output_method1_file,optarg);
				break;
			case 'g':
				gflag = 1;
				output_method2_file = malloc(strlen(optarg)+1);
				strcpy(output_method2_file,optarg);
				break;
			case 'n':	
				nflag = 1;
				sscanf(optarg, "%d", &iterations);
				break;
			case 'm':
				mflag = 1;
				sscanf(optarg, "%d", &pixels_to_average);
				break;
			case 'o':	
				oflag = 1;
				sscanf(optarg, "%d", &methods_to_execute);
				break;
			case 'd':
				dflag = 1;
				break;
			case '?':
				if(optopt == 'i'){
					fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
				}else if(optopt == 's'){
					fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
				}else if(optopt == 'g'){
					fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
				}else if(optopt == 'n'){
					fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
				}else if(optopt == 'm'){
					fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
				}else if(optopt == 'o'){
					fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
				}else if(isprint(optopt)){
					fprintf(stderr, "Opcion desconocida '-%c'.\n", optopt);
				}else{
					fprintf(stderr, "Opcion con caracter desconocido '\\x%x'.\n", optopt);
				}
				return 1;
			default:
				abort();
		}
	}
	
	/*
		Procesamiento
	*/

	// Revisar que se puedan crear/abrir los archivos.
	FILE* file_in = fopen(input_file, "r");
	if(file_in == NULL) {
		printf("El archivo %s no existe, ejecute el programa con un archivo existente.\n", input_file);
		return 1;
	}
	if(methods_to_execute == 1 || methods_to_execute == 3) {
		FILE* file_out_1 = fopen(output_method1_file, "w");
		if(file_out_1 == NULL) {
			printf("No se puede crear el archivo %s, revise que tenga los privilegios necesaros.\n", output_method1_file);
			return 1;
		}
		fclose(file_out_1);
	}
	if(methods_to_execute == 2 || methods_to_execute == 3) {
		FILE* file_out_2 = fopen(output_method2_file, "w");
		if(file_out_2 == NULL && (methods_to_execute == 2 || methods_to_execute == 3)) {
			printf("No se puede crear el archivo %s, revise que tenga los privilegios necesaros.\n", output_method2_file);
			return 1;
		}
		fclose(file_out_2);
	}
	fclose(file_in);

	// Crear la variable de la imagen, se inicializa cada ciclo
	Image image;
	//image_read_initialize(&image, input_file, pixels_to_average);

	// Variables para la medicion de tiempo, no se toma en cuenta
	// el tiempo que toma abrir y cerrar los archivos.
	clock_t start, start_iter, end;
	double duration, totalDuration;

	switch(methods_to_execute){
		case 1:
			totalDuration = 0;
			// Solo Metodo 1
			for (i = 0; i < iterations; ++i) {
				if(i == 0){
					image_read_initialize(&image, input_file, pixels_to_average);
				} else {
					image_read_initialize(&image, output_method1_file, pixels_to_average);
				}

				if(dflag) {
					start_iter = clock();
				}
				image_reduction_method1(&image);
				if(dflag) {
					end = clock();
					duration = ((double)(end - start_iter)) / CLOCKS_PER_SEC;
					totalDuration += duration;
					printf("La duracion de ejecutar el metodo 1 en la iteracion %d, fue de %f segundos.\n", i+1, duration);
				}

				image_write_reduction(&image, output_method1_file);
				image_free(&image);
			}

			if(dflag) {
				printf("La duracion de ejecutar el metodo 1 %d veces fue de %f segundos.\n", iterations, totalDuration);
				printf("Con un tiempo promedio de ejecucion de %f segundos.\n", totalDuration / (double)iterations);
			}
			break;
		case 2:
			totalDuration = 0;
			//Solo Metodo 2
			for (i = 0; i < iterations; ++i) {
				if(i == 0){
					image_read_initialize(&image, input_file, pixels_to_average);
				} else {
					image_read_initialize(&image, output_method2_file, pixels_to_average);
				}

				if(dflag) {
					start_iter = clock();
				}
				image_reduction_method2(&image);
				if(dflag) {
					end = clock();
					duration = ((double)(end - start_iter)) / CLOCKS_PER_SEC;
					totalDuration += duration;
					printf("La duracion de ejecutar el metodo 2 en la iteracion %d, fue de %f segundos.\n", i+1, duration);
				}
				image_write_reduction(&image, output_method2_file);
				image_free(&image);
			}

			if(dflag) {
				end = clock();
				duration = ((double)(end - start)) / CLOCKS_PER_SEC;
				printf("La duracion de ejecutar el metodo 2 %d veces fue de %f segundos.\n",iterations, totalDuration);
				printf("Con un tiempo promedio de ejecucion de %f segundos.\n", totalDuration / (double)iterations);
			}
			break;
		case 3:
			totalDuration = 0;
			// Metodo 1
			for (i = 0; i < iterations; ++i) {
				if(i == 0){
					image_read_initialize(&image, input_file, pixels_to_average);
				} else {
					image_read_initialize(&image, output_method1_file, pixels_to_average);
				}

				if(dflag) {
					start_iter = clock();
				}
				image_reduction_method1(&image);
				if(dflag) {
					end = clock();
					duration = ((double)(end - start_iter)) / CLOCKS_PER_SEC;
					totalDuration += duration;
					printf("La duracion de ejecutar el metodo 1 en la iteracion %d, fue de %f segundos.\n", i+1, duration);
				}
				image_write_reduction(&image, output_method1_file);
				image_free(&image);
			}

			if(dflag) {
				printf("La duracion de ejecutar el metodo 1 %d veces fue de %f segundos.\n", iterations, totalDuration);
				printf("Con un tiempo promedio de ejecucion de %f segundos.\n\n", totalDuration / (double)iterations);
			}

			totalDuration = 0;
			//Metodo 2
			for (i = 0; i < iterations; ++i) {
				if(i == 0){
					image_read_initialize(&image, input_file, pixels_to_average);
				} else {
					image_read_initialize(&image, output_method2_file, pixels_to_average);
				}

				if(dflag) {
					start_iter = clock();
				}
				image_reduction_method2(&image);
				if(dflag) {
					end = clock();
					duration = ((double)(end - start_iter)) / CLOCKS_PER_SEC;
					totalDuration += duration;
					printf("La duracion de ejecutar el metodo 2 en la iteracion %d, fue de %f segundos.\n", i+1, duration);
				}
				image_write_reduction(&image, output_method2_file);
				image_free(&image);
			}

			if(dflag) {
				end = clock();
				duration = ((double)(end - start)) / CLOCKS_PER_SEC;
				printf("La duracion de ejecutar el metodo 2 %d veces fue de %f segundos.\n",iterations, totalDuration);
				printf("Con un tiempo promedio de ejecucion de %f segundos.\n", totalDuration / (double)iterations);
			}
			break;
		default:
			printf("Debe seleccionar 3 opciones:\n\t1) Ejecutar solo método 1\n\t2) Ejecutar solo método 2\n\t3) Ejecutar ambos métodos\n");
			return 1;
	}

	free(input_file);
	free(output_method1_file);
	free(output_method2_file);

	return 0;
}

