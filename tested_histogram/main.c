#include <stdio.h>
#include <stdlib.h>
void histogram_p2(struct image *file, int bins, int stars)
{
	int histogram[256] = {0};
	int max = 0;
	//calculez un vector de frecventa cu valoriile imaginii
	for (int i = 0; i < file->height; i++)
		for (int j = 0; j < file->width; j++) {
			int value = file->mat_int[i][j];
			histogram[value] = histogram[value] + 1;
			}
	int bin[256] = {0};
	int val = 256 / bins;
	int k = 0, j = 0;

	//restrictionez vectorul de frecventa histogram la numarul de bin-uri
	for (int i = 0; i < bins; i = i + 1) {
		int copy = val;
		int s = 0;
		while (copy != 0) {
			s = s + histogram[j];
			copy = copy - 1;
			j = j + 1;
		}
		bin[i] = s;
		if (bin[i] > max)
			max = bin[i];
	}

	//afisez numarul de stelute conform formulei din tema
	for (int i = 0; i < bins; i++) {
		int nr_stel = (bin[i] * stars) / max;
		printf("%d\t|\t", nr_stel);
		while (nr_stel != 0) {
			nr_stel = nr_stel - 1;
			printf("*");
		}
		printf("\n");
	}
}

void histogram(struct image *file)
{
	//incep prin a verifica daca parametrii sunt valizi
	char check_if_param[256];
	int check = 0;
	fgets(check_if_param, 256, stdin);
	if (check_if_param[0] == ' ')
		for (int i = 0; i < strlen(check_if_param); i++)
			check_if_param[i] = check_if_param[i + 1];
	for (int i = 0; i < strlen(check_if_param); i++)
		if (check_if_param[i] == ' ')
			check = check + 1;
	if (!check || check != 1) {
		printf("Invalid command\n");
	} else if (check == 1) {
		if (file->magicknumber[1] == '3' || file->magicknumber[1] == '6')
			printf("Black and white image needed\n");
		if (file->magicknumber[1] == '5'  || file->magicknumber[1] == '2') {
			int stars, bins, max = 0;
			char *p = strtok(check_if_param, " ");
			stars = atoi(p);
			p = strtok(NULL, " ");
			bins = atoi(p);
			if (file->magicknumber[1] == '2')
				histogram_p2(file, bins, stars);

			if (file->magicknumber[1] == '5') {
				int histogram[256] = {0};
				max = 0;
				//calculez vectorul de frecventa din matricea pixelilor
				for (int i = 0; i < file->height; i++)
					for (int j = 0; j < file->width; j++) {
						int value = (int)file->mat_binary[i][j];
							histogram[value] = histogram[value] + 1;
					}
				int bin[256] = {0};
				int val = 256 / bins;
				int k = 0, j = 0;
				//restrictionez vectorul de frecventa la numarul de bin-uri

				for (int i = 0; i < bins; i = i + 1) {
					int copy = val;
					int s = 0;
					while (copy != 0) {
						s = s + histogram[j];
						copy = copy - 1;
						j = j + 1;
					}
					bin[i] = s;
					if (bin[i] > max)
						max = bin[i];
				}

				//afisez stelutele conform formulei primite
				for (int i = 0; i < bins; i++) {
					int nr_stel = (bin[i] * stars) / max;
					printf("%d\t|\t", nr_stel);
					while (nr_stel != 0) {
						nr_stel = nr_stel - 1;
						printf("*");
					}
					printf("\n");
				}
			}
		}
	}
}
int main(void)
{
    return 0;
}

