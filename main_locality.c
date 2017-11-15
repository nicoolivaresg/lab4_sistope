#include "util.h"
#include "image_reduction.h"
#include <time.h>

int main(int  argc, char ** argv){
	int i, j;
	int iflag = 0;//Flag nombre de archivo de entrada
	int sflag = 0;//Flag nombre de archivo de salida
	int nflag = 0;//Flag cantidad de veces a implementar la reduccion
	int mflag = 0;//Flag cantidad de pixeles a promediar
	int dflag = 0;//Flag mostrar resultados por pantalla
	char * input_file = NULL;
	char * output_file = NULL;
	int iterations = 0;
	int pixels_to_average = 0;
	int c;
	opterr=0;
	while((c = getopt(argc,argv,"i:s:n:m:d")) != -1){
		switch(c){
			case 'i':
				iflag = 1;
				input_file = malloc(strlen(optarg)+1);
				strcpy(input_file,optarg);
				break;
			case 's':
				sflag = 1;
				output_file = malloc(strlen(optarg)+1);
				strcpy(output_file,optarg);
				break;
			case 'n':
				nflag = 1;
				sscanf(optarg, "%d", &iterations);
				break;
			case 'm':
				mflag = 1;
				sscanf(optarg, "%d", &pixels_to_average);
				break;
			case 'd':
				dflag = 1;
				break;
			case '?':
				if(optopt == 'i'){
					fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
				}else if(optopt == 's'){
					fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
				}else if(optopt == 'n'){
					fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
				}else if(optopt == 'm'){
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
		Prueba de paso de argumentos por línea de comandos
	*/
	/*
	*/
	/*printf("iflag = %d, sflag = %d, nflag = %d, mflag = %d, dflag = %d\n", iflag, sflag, nflag, mflag, dflag);
	printf("Archivo de entrada: %s\nArchivo de salida: %s\nIteraciones ha realizar: %d\nPixeles a promediar: %d\nImprime por pantalla?: %s\n", 
		input_file,
		output_file,
		iterations,
		pixels_to_average,
		dflag ? "Si":"No"
		);*/
	/*
		Hasta acá 
	*/
	/*
		Procesamiento
	*/

	// Revisar que se puedan crear/abrir los archivos.
	FILE* file_in = fopen(input_file, "r");
	if(file_in == NULL) {
		printf("El archivo %s no existe, ejecute el programa con un archivo existente.\n", input_file);
		return 1;
	}
	FILE* file_out = fopen(output_file, "w");
	if(file_out == NULL) {
		printf("No se puede crear el archivo %s, revise que tenga los privilegios necesaros.\n", input_file);
		return 1;
	}
	fclose(file_in);
	fclose(file_out);

	// Initialize and create image variable
	Image image;
	image_read_initialize(&image, input_file, pixels_to_average);

	// Variables para la medicion de tiempo
	clock_t start, end;
	double duration;

	// Metodo 1
	if(dflag) {
		start = clock();
	}

	for (i = 0; i < iterations; ++i) {
		//image_reduction_method1(&image);
		image_write(&image, output_file);
	}

	if(dflag) {
		end = clock();
		duration = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("La duracion de ejecutar el metodo 1 %d veces fue de %f\n", iterations, duration);
		printf("Con un tiempo promedio de ejecucion de %f\n\n", duration / (double)iterations);
	}


	// Metodo 2
	if(dflag) {
		start = clock();
	}
	for (i = 0; i < iterations; ++i) {
		//image_reduction_method2(&image);
		//image_write(&image, output_file);
	}

	if(dflag) {
		end = clock();
		duration = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("La duracion de ejecutar el metodo 2 %d veces fue de %f\n", iterations, duration);
		printf("Con un tiempo promedio de ejecucion de %f\n", duration / (double)iterations);
	}

	return 0;
}

