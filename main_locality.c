#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main(int  argc, char ** argv){
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
	printf("iflag = %d, sflag = %d, nflag = %d, mflag = %d, dflag = %d\n", iflag, sflag, nflag, mflag, dflag);
	printf("Archivo de entrada: %s\nArchivo de salida: %s\nIteraciones ha realizar: %d\nPixeles a promediar: %d\nImprime por pantalla?: %s\n", 
		input_file,
		output_file,
		iterations,
		pixels_to_average,
		dflag ? "Si":"No"
		);
	/*
		Hasta acá 
	*/
	/*
		Procesamiento
	*/
	FILE* file_in = fopen(input_file, "r");
	if(file_in == NULL) {
		printf("El archivo %s no existe, ejecute el programa con un archivo existente\n", input_file);
		return 1;
	}
	FILE* file_out = fopen(output_file, "w");

	fclose(file_in);
	fclose(file_out);


	return 0;
}

