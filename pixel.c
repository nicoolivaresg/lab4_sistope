#include "pixel.h"

void pixel_init(Pixel* pixel, unsigned char Red, unsigned char Green, unsigned char Blue) {
	pixel->R = Red;
	pixel->G = Green;
	pixel->B = Blue;
}