#include "image_reduction.h"

void image_read_initialize(Image* image, char* filename, int m) {
	BITMAPINFOHEADER bitmapInfoHeader;
	image->bitmapPixels = load_bitmap_file(filename, &bitmapInfoHeader);
	image->bitmapInfoHeader = bitmapInfoHeader;
	image->rows = bitmapInfoHeader.biHeight;
	image->cols = bitmapInfoHeader.biWidth;

	image->mPixels = m;
}


void image_reduction_method1(Image* image) {
	
}

void image_reduction_method2(Image* image) {
	
}


void image_write(Image * image, char* filename) {
	save_bitmap_file(filename, image->bitmapInfoHeader, image->bitmapReduction, image->reductionHeight, image->reductionWidth);
}