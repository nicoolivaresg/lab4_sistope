#include "bitmap_manager.h"

Pixel** load_bitmap_file(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	int row, col;
    FILE *filePtr; //our file pointer
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
    unsigned char *bitmapImage;  //store image data
    Pixel** bitmapPixels; // Guardar los pixeles que se retornan
    int imageIdx=0;  //image index counter
    unsigned char tempRGB;  //our swap variable

    //open filename in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return NULL;

    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);

    //verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.bfType !=0x4D42)
    {
        fclose(filePtr);
        return NULL;
    }

    //read the bitmap info header
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr); // small edit. forgot to add the closing bracket at sizeof

    //move file point to the begging of bitmap data
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

    //verify memory allocation
    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    //read in the bitmap image data
    fread(bitmapImage,bitmapInfoHeader->biSizeImage,filePtr);

    //make sure bitmap image data was read
    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }

    //swap the r and b values to get RGB (bitmap is BGR)
    for (imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage;imageIdx+=3) // fixed semicolon
    {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }


    bitmapPixels = malloc(bitmapInfoHeader->biHeight * sizeof(*bitmapPixels));
    for(row = 0, imageIdx = 0; row < bitmapInfoHeader->biHeight; row++) {
    	bitmapPixels[row] = malloc(bitmapInfoHeader->biWidth * sizeof(*(bitmapPixels[row])));
    	for(col = 0; col < bitmapInfoHeader->biWidth; col++, imageIdx += 3) {
    		pixel_init(&(bitmapPixels[row][col]), bitmapImage[imageIdx], bitmapImage[imageIdx + 1], bitmapImage[imageIdx + 2]);
    	}
    }

    //close file and return bitmap image data
    fclose(filePtr);
    return bitmapPixels;
}

void save_bitmap_file(char* filename, BITMAPINFOHEADER *bitmapInfoHeader, Pixel** bitmapPixels, int height, int width) {
	int row, col;
	FILE* filePtr;

	// Crear headers


	// Cambiar valores en la cabecera del bitmap
	bitmapInfoHeader->biWidth = width;
	bitmapInfoHeader->biHeight = height;

	// Abrir archivo y escribir en modo binario
    filePtr = fopen(filename,"wb");
    if (filePtr == NULL)
        return NULL;

    fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr);

    for(row = 0; row < height; row++) {
    	fwrite(bitmapPixels[row], sizeof(bitmapPixels[row][0]), width, filePtr);
    }

    fclose(filePtr);
}