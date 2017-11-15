#include "bitmap_manager.h"

Pixel** load_bitmap_file(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	int row, col, pixelsRead;
    FILE *filePtr; // Puntero al archivo.
    BITMAPFILEHEADER bitmapFileHeader; // Cabecera del archivo bitmap.
    unsigned char *bitmapImage;  // Informacion inicial de la imagen.
    Pixel** bitmapPixels; // Guardar los pixeles que se retornan.
    int imageIdx=0;  // Indice de la imagen.
    unsigned char tempRGB;  // Variable para hacer un swap.

    // Se usa el modo binario para lectura y escritura de archivos.
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return NULL;

    // Leer la cabecera del archivo bitmap.
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);
    
    // Verificar que es un archivo bitmap viendo su tipo.
    if (bitmapFileHeader.bfType !=0x4D42)
    {
        fclose(filePtr);
        return NULL;
    }

    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr);

    // Mover el puntero del archivo al principio de los datos de los pixeles.
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

    //printf("sizeof WORD %d\n sizeof DWORD %d\n sizeof LONG %d\n", sizeof(WORD), sizeof(DWORD), sizeof(LONG));
    //printf("sizeof file header%d\n sizeof info header %d\n", sizeof(BITMAPFILEHEADER), sizeof(BITMAPINFOHEADER));

    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

    if (bitmapImage == NULL)
    {
    	printf("Could not assign bitmap image data memory.\n");
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    // Leer los datos de la imagen bmp.
    fread(bitmapImage,bitmapInfoHeader->biSizeImage, 1, filePtr);

    if (bitmapImage == NULL)
    {
    	printf("Could not read bitmap image data.\n");
        fclose(filePtr);
        return NULL;
    }

    // Como se usan 24 bits, se debe rellenar hasta que la cantidad de bytes por fila sean multiplos de 4.
    int widthPadded = (bitmapInfoHeader->biWidth * 3 + 3) & (~3);
    // Swappear los valores de R y B para obtener RGB (el bitmap usa BGR).
    for (pixelsRead = 0, imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage;imageIdx+=3)
    {
    	if(pixelsRead >= bitmapInfoHeader->biWidth) {
    		pixelsRead = 0;
    		imageIdx += widthPadded - bitmapInfoHeader->biWidth;
    	}
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    // Alocar memoria para almecenar los pixeles en una matriz.
    bitmapPixels = malloc(bitmapInfoHeader->biHeight * sizeof(*bitmapPixels));
    for(row = 0, imageIdx = 0; row < bitmapInfoHeader->biHeight; row++) {
    	bitmapPixels[row] = malloc(bitmapInfoHeader->biWidth * sizeof(*(bitmapPixels[row])));
    	for(col = 0; col < bitmapInfoHeader->biWidth; col++, imageIdx += 3) {
    		pixel_init(&(bitmapPixels[row][col]), bitmapImage[imageIdx], bitmapImage[imageIdx + 1], bitmapImage[imageIdx + 2]);
    	}
    	imageIdx += widthPadded - bitmapInfoHeader->biWidth * 3;

    }

    /*for(row = 0; row < bitmapInfoHeader->biHeight; row++) {
    	
    	for(col = 0; col < bitmapInfoHeader->biWidth; col++) {
    		printf("(%d %d %d), ", bitmapPixels[row][col].R, bitmapPixels[row][col].G, bitmapPixels[row][col].B);
    	}
    	printf("\n");
    }*/

    // Cerrar el archivo y retornar los valores de los pixeles .
    fclose(filePtr);
    return bitmapPixels;
}

void save_bitmap_file(char* filename, BITMAPINFOHEADER *bitmapInfoHeader, Pixel** bitmapPixels, int height, int width) {
	int row, col;
	FILE* filePtr;
	int widthPadded = (width * 3 + 3) & (~3);
	unsigned char* bitmapImage = unload_pixels(bitmapPixels, width, height);
	int bitmapBytes = widthPadded * height;

	// Abrir archivo y escribir en modo binario, se supone que ya se reviso que se puede abrir.
    filePtr = fopen(filename,"wb");
    if (filePtr == NULL)
        return;

	// Crear headers
	BITMAPFILEHEADER bitmapFileHeader;
	bitmapFileHeader.bfType = 0x4D42;
	bitmapFileHeader.bfSize = 54 + bitmapBytes;
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	bitmapFileHeader.bfOffBits = 54;


	// Cambiar valores en la cabecera del bitmap
	bitmapInfoHeader->biWidth = width;
	bitmapInfoHeader->biHeight = height;
	bitmapInfoHeader->biSizeImage = bitmapBytes;

    fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr);

    fwrite(bitmapImage, 1, bitmapBytes, filePtr);

    fclose(filePtr);
}

unsigned char* unload_pixels(Pixel** bitmapPixels, int width, int height) {
	int row, col, imageIdx;
	int widthPadded = (width * 3 + 3) & (~3);
	unsigned char* bitmapImage = malloc(sizeof(*bitmapImage) * (widthPadded * height));

    for(row = 0, imageIdx = 0; row < height; row++) {
    	
    	for(col = 0; col < width; col++, imageIdx += 3) {
    		bitmapImage[imageIdx] = bitmapPixels[row][col].B;
    		bitmapImage[imageIdx+1] = bitmapPixels[row][col].G;
    		bitmapImage[imageIdx+2] = bitmapPixels[row][col].R;
    	}
    	while(imageIdx % 4 != 0) {
    		bitmapImage[imageIdx++] = 0x00;
    	}
    }

    return bitmapImage;
}