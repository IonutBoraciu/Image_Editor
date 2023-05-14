#include <stdio.h>
#include <stdlib.h>
void equalize(struct image *file)
{
	if (file->magicknumber[1] == '3' || file->magicknumber[1] == '6')
		printf("Black and white image needed\n");
	if (file->magicknumber[1] == '2') {
		int histogram[256] = {0};
		//calculez vectorul de frecventa din matricea pixelilor
		for (int i = 0; i < file->height; i++)
			for (int j = 0; j < file->width; j++) {
				int value = file->mat_int[i][j];
				histogram[value] = histogram[value] + 1;
			}

		//aplic egalizarea conform formulei primite
		int area = file->height * file->width;
		int s = 0, vec_aux[256];
		for (int a = 0; a <= 255; a++) {
			s += histogram[a];
			vec_aux[a] = (int)(255 * s / area);
		}

		for (int i = 0; i < file->height; i++)
			for (int j = 0; j < file->width; j++) {
				int value = file->mat_int[i][j];
				file->mat_int[i][j] = vec_aux[value];
			}
		printf("Equalize done\n");

	} else if (file->magicknumber[1] == '5') {
		int histogram[256] = {0};
		for (int i = 0; i < file->height; i++)
			for (int j = 0; j < file->width; j++) {
				int value = (int)file->mat_binary[i][j];
			histogram[value] = histogram[value] + 1;
			}

		int area = file->height * file->width;
		int s = 0, vec_aux[256];
		for (int a = 0; a <= 255; a++) {
			s += histogram[a];
			vec_aux[a] = (int)(255 * ((float)s / area));
		}

		for (int i = 0; i < file->height; i++)
			for (int j = 0; j < file->width; j++) {
				int value = (int)file->mat_binary[i][j];
				file->mat_binary[i][j] = vec_aux[value];
			}
		printf("Equalize done\n");
	}
}
