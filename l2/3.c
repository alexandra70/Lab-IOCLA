

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define CONST_R 0.30
#define CONST_G 0.59
#define CONST_B 0.11

#define GET_PIXEL(a, i, j) (*(*(a + i) + j))



typedef struct Pixel {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} Pixel;

typedef struct Picture {
	int height;    
	int width;        
	Pixel **pix_array; 
} Picture;

Picture* generatePicture(int height, int width, Pixel **pix_array) {
	Picture *pic = malloc(sizeof(*pic));
	pic->height = height;
	pic->width = width;

	pic->pix_array = malloc(pic->height * sizeof(*(pic->pix_array)));

	for (int i = 0; i < pic->height; ++i)
		pic->pix_array[i] = malloc(pic->width * sizeof(*(*(pic->pix_array))));

	for (int i = 0; i < pic->height; ++i) {
		for(int j = 0; j < pic->width; ++j) {
			pic->pix_array[i][j] = pix_array[i][j];
		}
	}
    
	return pic;
}

Pixel generatePixel (const unsigned char R,
					const unsigned char G, const unsigned char B) {
	Pixel pixel;
	pixel.R = R;
	pixel.G = G;
	pixel.B = B;

	return pixel;
 }

void printPicture(Picture *pic) {
 	for (int i = 0; i < pic->height; ++i) {
		for (int j = 0; j < pic->width; ++j) {
			printf("%u %u %u ", pic->pix_array[i][j].R,
						pic->pix_array[i][j].G, pic->pix_array[i][j].B);
			if (j != pic->width - 1) {
				printf(" | ");
		    }
		}
		printf("\n");
	}
}

Pixel** generatePixelArray(int height, int width) {
	Pixel **pix_array = malloc(height * sizeof(*pix_array));
	for (int i = 0; i < height; ++i)
		pix_array[i] = malloc(width * sizeof(*(*pix_array)));

	time_t t;
	srand((unsigned) time(&t));

	for (int i = 0; i < height; ++i) {
		for(int j = 0; j < width; ++j) {
			pix_array[i][j] = generatePixel(rand() % 256,
				rand() % 256, rand() % 256);
			}
		}

	return pix_array;
}

void freePixelArray(Pixel ***pix_array, int height, int width) {
	for (int i = 0 ; i < height ; ++i) 
		free((*pix_array)[i]);

	free(*pix_array);
}

void freePicture(Picture **pic) {
	freePixelArray(&(*pic)->pix_array, (*pic)->height, (*pic)->width);
	free(*pic);
}



/*
	TODO a
	Functia primeste ca parametru o imagine si intoarce imaginea rasturnata.
	Prin imagine rasturnata se intelege inversarea liniilor matricei pix_array
	din structura lui Picture, astfel: Linia 1 devine linia n, linia 2 devine
	linia n - 1, etc.
*/

void reversePic(Picture *pic) {
	
    Pixel* tmp;
    for(int i = 0; i < pic->height / 2; i ++) {
        tmp = pic->pix_array[i];
        pic->pix_array[i] = pic->pix_array[pic->height - i - 1];
        pic->pix_array[pic->height - i - 1] = tmp;
    }
    return;
}

/*
	TODO b
	Functia primeste ca parametru o imagine si intoarce noua imagine obtinuta
	prin convertirea fiecarui pixel la valoarea sa grayscale.
	Valoarea grayscale a unui pixel sa calculeaza dupa urmatoarea formula:
	p.r = 0.3 * p.r;
	p.g = 0.59 * p.g;
	p.b = 0.11 * p.b;
*/

void colorToGray(Picture *pic) {
	for(int i = 0; i < pic->height; i ++) {
        for(int j = 0 ; j < pic->width; j ++) {
            pic->pix_array[i][j].R = GET_PIXEL(pic->pix_array, i, j).R * 0.3;
            pic->pix_array[i][j].G = GET_PIXEL(pic->pix_array, i, j).G * 0.59;
            pic->pix_array[i][j].B = GET_PIXEL(pic->pix_array, i, j).B * 0.11;
        }
    }
}

/*
	Structura unui pixel, cea a unei imagini, precum si generarea acestora
	sunt definite in pixel.h. Programul primeste de la tastatura inaltimea
	si latimea imaginii. De preferat, introduceti valori mici pentru
	a fi usor de verificat ulterior.
	Folositi functia printPicture pentru a printa componentele imaginii.
	Dupa ce ati realizat un TODO, apelati functia corespunzatoare in main
	urmata de printPicture pentru a vedea daca se obtine rezultatul dorit.
*/

int main() {
	int height, width;
	scanf("%d%d", &height, &width);
	Pixel **pix_array = generatePixelArray(height, width);
	Picture *pic = generatePicture(height, width, pix_array);

	printPicture(pic);
	printf("acum colorata\n");

	reversePic(pic);
	colorToGray(pic);
	printPicture(pic);

	freePicture(&pic);
	freePixelArray(&pix_array, height, width);

	return 0;
}