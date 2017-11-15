#include "image_reduction.h"

void image_read_initialize(Image* image, char* filename, int m) {
	FILE* input = fopen(filename, "r");

	image->mPixels = m;

	// Somehow read image and allocate memory for matrix, reduction and N, M


	fclose(input);
}


void image_reduction_method1(Image* image) {
	
}

void image_reduction_method2(Image* image) {
	
}


void image_write(Image * image, char* filename) {
	FILE* output = fopen(filename, "w");

	// Somehow write image to file using fwrite

	fclose(output);
}