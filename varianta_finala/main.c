//Boraciu Ionut-Sorin
//GRUPA: 315CA
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct image {
	char magicknumber[3];
	int height, width;
	int max_value;
	int **mat_int;
	unsigned char **mat_binary;
	int x1, x2, y1, y2;
	int old_x1, old_x2, old_y1, old_y2;
};

void free_matrix_int(int ***mat, int height)
{
	//eliberez o matrice de tip int
	for (int i = 0; i < height; i++)
		free((*mat)[i]);
	free((*mat));
}

void free_matrix_binary(unsigned char ***mat, int height)
{
	//eliberez o matrice de tip unsigned char
	for (int i = 0; i < height; i++)
		free((*mat)[i]);
	free((*mat));
}

void malloc_matrix_int(int ***mat, int height, int width)
{
	//aloc dinamic o matrice de tip int
	//si verific daca a fost alocata cu succes
	*mat = malloc(height * sizeof(int *));
	if ((*mat) == NULL) {
		printf("Malloc failed\n");
		exit(1);
	}
	for (int i = 0; i < height; i++) {
		(*mat)[i] = malloc(width * sizeof(int));
		if ((*mat)[i] == NULL) {
			printf("Malloc failled\n");
			exit(1);
		}
	}
}

void malloc_matrix_binary(unsigned char ***mat, int height, int width)
{
	//aloc dinamic o matrice de tip unsigned char
	//si verific daca a fost alocata cu succes
	*mat = malloc(height * sizeof(unsigned char *));
	if ((*mat) == NULL) {
		printf("Malloc failled\n");
		exit(1);
	}
	for (int i = 0; i < height; i++) {
		(*mat)[i] = malloc(width * sizeof(unsigned char));
		if ((*mat)[i] == NULL) {
			printf("Malloc failed\n");
			exit(1);
		}
	}
}

void free_unkown_matrix(struct image *file)
{
	//eliberez o matrice al carei tip nu il cunosc la apelarea functiei
	if (file->magicknumber[1] == '2' || file->magicknumber[1] == '3')
		free_matrix_int(&file->mat_int, file->height);
	if (file->magicknumber[1] == '5' || file->magicknumber[1] == '6')
		free_matrix_binary(&file->mat_binary, file->height);
}

void readppm_p3(struct image *file, FILE *f)
{
	//stochez matricea de pixele dintr-un fisier PPM cu magic number-ul 3
	malloc_matrix_int(&file->mat_int, file->height, file->width * 3);
	for (int i = 0; i < file->height; i++)
		for (int j = 0; j < file->width * 3; j++)
			fscanf(f, "%d", &file->mat_int[i][j]);
}

void readppm_p6(struct image *file, FILE *f)
{
	//stochez matricea de pixele dintr-un fisier PPM cu magic number-ul 6
	malloc_matrix_binary(&file->mat_binary, file->height, file->width * 3);
	for (int i = 0; i < file->height; i++)
		fread(file->mat_binary[i], 3, file->width, f);
}

void readpgm_p2(struct image *file, FILE *f)
{
	//stochez matricea de pixele dintr-un fisier PGM cu magic number-ul 2
	malloc_matrix_int(&file->mat_int, file->height, file->width);
	for (int i = 0; i < file->height; i++)
		for (int j = 0; j < file->width; j++)
			fscanf(f, "%d", &file->mat_int[i][j]);
}

void readpgm_p5(struct image *file, FILE *f)
{
	//stochez matricea de pixele dintr-un fisier PGM cu magic number-ul 5
	malloc_matrix_binary(&file->mat_binary, file->height, file->width);
	for (int i = 0; i < file->height; i++)
		fread(file->mat_binary[i], sizeof(unsigned char), file->width, f);
}

void load(struct image *file, FILE *f)
{
	char garbage[256];
	int number = 0;
	int ok = 1;
	//citesc randul pana gasesc o linie care nu e comentata
	while (fgets(garbage, 256, f) && ok == 1) {
		if (garbage[0] != '#' && garbage[0] != '\n') {
			fseek(f, ftell(f) - strlen(garbage), SEEK_SET);
			fscanf(f, "%s", file->magicknumber);
			ok = 0;
		}
	}

	ok = 1;
	//citesc randul pana gasesc o linie care nu e comentata
	while (fgets(garbage, 256, f) && ok == 1) {
		if (garbage[0] != '#' && garbage[0] != '\n') {
			fseek(f, ftell(f) - strlen(garbage), SEEK_SET);
			fscanf(f, "%d%d", &file->width, &file->height);
			ok = 0;
		}
	}

	ok = 1;
	//citesc randul pana gasesc o linie care nu e comentata
	while (fgets(garbage, 256, f) && ok == 1) {
		if (garbage[0] != '#' && garbage[0] != '\n') {
			fseek(f, ftell(f) - strlen(garbage), SEEK_SET);
			fscanf(f, "%d", &file->max_value);
			ok = 0;
		}
	}

	file->x1 = 0;
	file->x2 = file->width;
	file->y1 = 0;
	file->y2 = file->height;

	//citesc matricea pixelilor in functie de magic number
	if (file->magicknumber[0] == 'P' && file->magicknumber[1] == '3')
		readppm_p3(file, f);
	if (file->magicknumber[0] == 'P' && file->magicknumber[1] == '6')
		readppm_p6(file, f);
	if (file->magicknumber[0] == 'P' && file->magicknumber[1] == '2')
		readpgm_p2(file, f);
	if (file->magicknumber[0] == 'P' && file->magicknumber[1] == '5')
		readpgm_p5(file, f);
}

void select_image(struct image *file, int check_file, int *check_if_select)
{
	if (check_file) {
		char c_param[256];
		fgets(c_param, 256, stdin);
		if (c_param[0] == ' ')
			for (int i = 0; i < strlen(c_param); i++)
				c_param[i] = c_param[i + 1];
		int number_of_spaces = 0;
		for (int i = 0; i < strlen(c_param); i++)
			if (c_param[i] == ' ')
				number_of_spaces = number_of_spaces + 1;
	int check_if_number = 1;
	for (int i = 0; i < strlen(c_param); i++)
		if ((c_param[i] < 48 || c_param[i] > 57) &&
			c_param[i] != ' ' && c_param[i] != '\n' &&
			c_param[i] != '-')
			check_if_number = 0;
	//daca am gasit minim 3 spatii si numai cifre atunci atribuii variabilele

	if (check_if_number && number_of_spaces == 3) {
		char *p = strtok(c_param, " ");
		file->x1 = atoi(p), p = strtok(NULL, " ");
		file->y1 = atoi(p), p = strtok(NULL, " ");
		file->x2 = atoi(p), p = strtok(NULL, "\n");
		file->y2 = atoi(p);
	}

	//verific sa fie in ordinea corecta (x1<x2,y1<y2)
	if (number_of_spaces == 3 && check_if_number) {
		if (file->x1 > file->x2) {
			int aux = file->x1;
			file->x1 = file->x2, file->x2 = aux;
		}
	if (file->y1 > file->y2) {
		int aux = file->y1;
		file->y1 = file->y2, file->y2 = aux;
	}
	if (file->x1 < 0 || file->x2 > file->width || file->y1 < 0 ||
		file->y2 > file->height || (file->x2 - file->x1 == 0) ||
		(file->y2 - file->y1 == 0)) {
		printf("Invalid set of coordinates\n");

		if (*check_if_select == 1) {
			//daca atribuirea curenta este invalida dar cea precedenta
			//este valida pastrez valorile de la cea valida
			file->x1 = file->old_x1, file->x2 = file->old_x2;
			file->y1 = file->old_y1, file->y2 = file->old_y2;
		} else if (*check_if_select == 0) {
			file->x1 = 0, file->x2 = file->width;
			file->y1 = 0, file->y2 = file->height;
		}

	} else {
		*check_if_select = 1;
		int x1 = file->x1;
		int y1 = file->y1;
		int x2 = file->x2;
		int y2 = file->y2;
		printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
		if (file->x1 == 0 && file->y1 == 0 && file->x2 == file->width &&
			file->y2 == file->height)
			*check_if_select = 0;
			file->old_x1 = file->x1, file->old_y1 = file->y1;
			file->old_x2 = file->x2, file->old_y2 = file->y2;
		}

	} else if (c_param[0] == 'A' && c_param[1] == 'L' && c_param[2] == 'L') {
		*check_if_select = 0;
		file->x1 = 0, file->x2 = file->width;
		file->y1 = 0, file->y2 = file->height;
		printf("Selected ALL\n");
	} else {
		printf("Invalid command\n");
	}

	} else {
		char garbage[256];
		fgets(garbage, 256, stdin);
		printf("No image loaded\n");
	}
}

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

void crop_p2(struct image *file)
{
	int **mat_copy;
	malloc_matrix_int(&mat_copy, file->y2 - file->y1, file->x2 - file->x1);
	int i2 = 0, j2 = 0;
	int nr = 0;
	//creez o matricea copie in care sa stochez partea selectata din matrice
	for (int i = file->y1; i < file->y2; i++) {
		j2 = 0;
		for (int j = file->x1; j < file->x2; j++) {
			mat_copy[i2][j2] = file->mat_int[i][j];
			j2 = j2 + 1;
		}
		i2 = i2 + 1;
	}

	//eliberez matricea initiala
	free_matrix_int(&file->mat_int, file->height);
	//realloc matricea cu numarul de linii si de coloane ale zonei selectate
	file->height = file->y2 - file->y1;
	file->width = file->x2 - file->x1;
	malloc_matrix_int(&file->mat_int, file->height, file->width);

	//atribuii valorile din matricea copie in matricea initiala
	for (int i = 0; i < file->height; i++)
		for (int j = 0; j < file->width; j++)
			file->mat_int[i][j] = mat_copy[i][j];

	//eliberez matricea copie
	free_matrix_int(&mat_copy, file->height);
		printf("Image cropped\n");
}

void crop_p5(struct image *file)
{
	unsigned char **mat_copy;
	int number_lines = file->y2 - file->y1;
	int number_cols = file->x2 - file->x1;
	malloc_matrix_binary(&mat_copy, number_lines, number_cols);

	int i2 = 0, j2 = 0;
	for (int i = file->y1; i < file->y2; i++) {
		j2 = 0;
		for (int j = file->x1; j < file->x2; j++) {
			mat_copy[i2][j2] = file->mat_binary[i][j];
		j2 = j2 + 1;
		}
		i2 = i2 + 1;
	}

	free_matrix_binary(&file->mat_binary, file->height);
	file->height = file->y2 - file->y1;
	file->width = file->x2 - file->x1;
	malloc_matrix_binary(&file->mat_binary, file->height, file->width);

	for (int i = 0; i < file->height; i++)
		for (int j = 0; j < file->width; j++)
			file->mat_binary[i][j] = mat_copy[i][j];

	free_matrix_binary(&mat_copy, file->height);
	printf("Image cropped\n");
}

void crop(struct image *file, int *check_if_select)
{
	if (file->magicknumber[1] == '2') {
		crop_p2(file);

	} else if (file->magicknumber[1] == '5') {
		crop_p5(file);

	} else if (file->magicknumber[1] == '3') {
		int **mat_copy;
		int number_lines = file->y2 - file->y1;
		int number_cols = file->x2 - file->x1;
		malloc_matrix_int(&mat_copy, number_lines, number_cols * 3);

		int i2 = 0, j2 = 0;
		for (int i = file->y1; i < file->y2; i++) {
			j2 = 0;
			for (int j = file->x1 * 3; j < file->x2 * 3; j = j + 3) {
				mat_copy[i2][j2] = file->mat_int[i][j];
				mat_copy[i2][j2 + 1] = file->mat_int[i][j + 1];
				mat_copy[i2][j2 + 2] = file->mat_int[i][j + 2];
				j2 = j2 + 3;
			}
			i2 = i2 + 1;
		}

		free_matrix_int(&file->mat_int, file->height);
		file->height = file->y2 - file->y1;
		file->width = file->x2 - file->x1;
		malloc_matrix_int(&file->mat_int, file->height, file->width * 3);

		for (int i = 0; i < file->height; i++)
			for (int j = 0; j < file->width * 3; j++)
				file->mat_int[i][j] = mat_copy[i][j];
		free_matrix_int(&mat_copy, file->height);
		printf("Image cropped\n");

	} else if (file->magicknumber[1] == '6') {
		unsigned char **mat_copy;
		int number_lines = file->y2 - file->y1;
		int number_cols = file->x2 - file->x1;
		malloc_matrix_binary(&mat_copy, number_lines, number_cols * 3);

		int i2 = 0, j2 = 0;
		for (int i = file->y1; i < file->y2; i++) {
			j2 = 0;
			for (int j = file->x1 * 3; j < file->x2 * 3; j = j + 3) {
				mat_copy[i2][j2] = file->mat_binary[i][j];
				mat_copy[i2][j2 + 1] = file->mat_binary[i][j + 1];
				mat_copy[i2][j2 + 2] = file->mat_binary[i][j + 2];
				j2 = j2 + 3;
			}
			i2 = i2 + 1;
		}

		free_matrix_binary(&file->mat_binary, file->height);
		file->height = file->y2 - file->y1;
		file->width = file->x2 - file->x1;

		malloc_matrix_binary(&file->mat_binary, file->height, file->width * 3);
		for (int i = 0; i < file->height; i++)
			for (int j = 0; j < file->width * 3; j++)
				file->mat_binary[i][j] = mat_copy[i][j];

		free_matrix_binary(&mat_copy, file->height);
		printf("Image cropped\n");
	}
	file->x1 = 0;
	file->y1 = 0;
	file->x2 = file->width;
	file->y2 = file->height;
	*check_if_select = 0;
}

void rotate_int_to_right(struct image *file, int check_if_select)
{
	int **rotate;
	int n = file->y2 - file->y1;
	int m = file->x2 - file->x1;
	//aloc o matrice copie cu coloanele si liniile inversate
	malloc_matrix_int(&rotate, file->width, file->height);

	//calculez matricea rotita cu 90 de grade la dreapte in rotate
	for (int i = file->y1; i < file->y2; i++)
		for (int j = file->x1; j < file->x2; j++)
			rotate[j][file->y2 - (i - file->y1) - 1] = file->mat_int[i][j];

	if (check_if_select == 0) {
		//reatribuii matricea daca e selectata toata imaginea pentru
		//a inversa liniile si coloanele
		free_matrix_int(&file->mat_int, file->height);
		file->height = m;
		file->width = n;
		malloc_matrix_int(&file->mat_int, file->height, file->width);
	}
	if (check_if_select == 0) {
		for (int i = file->x1; i < file->x2; i++)
			for (int j = file->y1; j < file->y2; j++)
				file->mat_int[i][j] = rotate[i][j];
	}
	if (check_if_select == 1) {
		//copiez valoriile din rotate in matricea initiala
		int j2 = file->y1, i2 = file->x1;
		for (int i = file->y1; i < file->y2; i++) {
			j2 = file->y1;
			for (int j = file->x1; j < file->x2; j++) {
				file->mat_int[i][j] = rotate[i2][j2];
				j2 = j2 + 1;
			}
			i2 = i2 + 1;
		}
	}
	if (check_if_select == 0)
		free_matrix_int(&rotate, file->height);
	else
		free_matrix_int(&rotate, file->width);
}

void rotate_binary_to_right(struct image *file, int check_if_select)
{
	unsigned char **rotate;
	int n = file->y2 - file->y1;
	int m = file->x2 - file->x1;

	malloc_matrix_binary(&rotate, file->width, file->height);
	for (int i = file->y1; i < file->y2; i++)
		for (int j = file->x1; j < file->x2; j++)
			rotate[j][file->y2 - (i - file->y1) - 1] = file->mat_binary[i][j];
	if (check_if_select == 0) {
		free_matrix_binary(&file->mat_binary, file->height);
		file->height = m;
		file->width = n;
		malloc_matrix_binary(&file->mat_binary, file->height, file->width);
	}
	if (check_if_select == 0) {
		for (int i = file->x1; i < file->x2; i++)
			for (int j = file->y1; j < file->y2; j++)
				file->mat_binary[i][j] = rotate[i][j];

	} else {
		int j2 = file->y1, i2 = file->x1;
		for (int i = file->y1; i < file->y2; i++) {
			j2 = file->y1;
			for (int j = file->x1; j < file->x2; j++) {
				file->mat_binary[i][j] = rotate[i2][j2];
				j2 = j2 + 1;
			}
			i2 = i2 + 1;
		}
	}
	if (check_if_select == 0)
		free_matrix_binary(&rotate, file->height);
	else
		free_matrix_binary(&rotate, file->width);
}

void rotate_binary_right2(struct image *file, int check_if_select)
{
	unsigned char **rotate;
	int n = file->y2 - file->y1;
	int m = file->x2 - file->x1;
	malloc_matrix_binary(&rotate, file->width, file->height * 3);
	for (int i = file->y1; i < file->y2; i++) {
		for (int j = file->x1; j < file->x2; j++) {
			for (int k = 0; k < 3; k++) {
				rotate[j][(file->y2 - (i - file->y1) - 1) * 3 + k] =
				file->mat_binary[i][j * 3 + k];
			}
		}
	}

	if (check_if_select == 0) {
		free_matrix_binary(&file->mat_binary, file->height);
		file->height = m;
		file->width = n;
		malloc_matrix_binary(&file->mat_binary, file->height, file->width * 3);
	}
	if (check_if_select == 0) {
		for (int i = file->x1; i < file->x2; i++) {
			for (int j = file->y1; j < file->y2; j++) {
				for (int k = 0; k < 3; k++)
					file->mat_binary[i][j * 3 + k] = rotate[i][j * 3 + k];
			}
		}
	} else {
		int i2 = file->x1;
		int j2 = file->y1;
		for (int i = file->y1; i < file->y2; i++) {
			j2 = file->y1;
			for (int j = file->x1; j < file->x2; j++) {
				for (int k = 0; k < 3; k++)
					file->mat_binary[i][j * 3 + k] = rotate[i2][j2 * 3 + k];
				j2 = j2 + 1;
			}
			i2 = i2 + 1;
		}
	}
	if (check_if_select == 0)
		free_matrix_binary(&rotate, file->height);
	else
		free_matrix_binary(&rotate, file->width);
}

void rotate_int_right2(struct image *file, int check_if_select)
{
	int **rotate;
	int n = file->y2 - file->y1;
	int m = file->x2 - file->x1;
	malloc_matrix_int(&rotate, file->width, file->height * 3);
	for (int i = file->y1; i < file->y2; i++) {
		for (int j = file->x1; j < file->x2; j++) {
			for (int k = 0; k < 3; k++)
				rotate[j][(file->y2 - (i - file->y1) - 1) * 3 + k] =
				file->mat_int[i][j * 3 + k];
		}
	}

	if (check_if_select == 0) {
		free_matrix_int(&file->mat_int, file->height);
		file->height = m;
		file->width = n;
		malloc_matrix_int(&file->mat_int, file->height, file->width * 3);
	}

	if (check_if_select == 0) {
		for (int i = file->x1; i < file->x2; i++) {
			for (int j = file->y1; j < file->y2; j++) {
				for (int k = 0; k < 3; k++)
					file->mat_int[i][j * 3 + k] = rotate[i][j * 3 + k];
			}
		}
	} else {
		int i2 = file->x1;
		int j2 = file->y1;
		for (int i = file->y1; i < file->y2; i++) {
			j2 = file->y1;
			for (int j = file->x1; j < file->x2; j++) {
				for (int k = 0; k < 3; k++)
					file->mat_int[i][j * 3 + k] = rotate[i2][j2 * 3 + k];
				j2 = j2 + 1;
			}
			i2 = i2 + 1;
		}
	}
	if (check_if_select == 0)
		free_matrix_int(&rotate, file->height);
	else
		free_matrix_int(&rotate, file->width);
}

void rotate(struct image *file, int check_if_select)
{
	int angle;
	scanf("%d", &angle);
	int already_print = 0;
	if (angle == 0)
		printf("Rotated 0\n"), already_print = 1;
	if (angle % 90 == 0 && angle != 0) {
		int ok = 0, old_angle;
		old_angle = angle;
		if (angle < 0)
			ok = 1;

		while (angle < 0)
			angle = angle + 360;
		if (old_angle == -360) {
			printf("Rotated -360\n");
			already_print = 1;
		}

		if ((((file->y2 - file->y1) == (file->x2 - file->x1) &&
			  check_if_select == 1) ||
			check_if_select == 0) &&
		   already_print == 0) {
			if (file->magicknumber[1] == '2') {
				//pentru a rotii o zona selectata sau toata imaginea
				//cu mai mult de 90 de grade, apelez functia rotate
				//de mai multe ori
				while (angle != 0 && angle > 0) {
					rotate_int_to_right(file, check_if_select);
					if (check_if_select == 0) {
						file->x2 = file->width;
						file->y2 = file->height;
					}
					angle = angle - 90;
				}
			}

		if (file->magicknumber[1] == '5')
			while (angle != 0 && angle > 0) {
				rotate_binary_to_right(file, check_if_select);
				if (check_if_select == 0) {
					file->x2 = file->width;
					file->y2 = file->height;
				}

				angle = angle - 90;
			}

		if (file->magicknumber[1] == '6')
			while (angle != 0 && angle > 0) {
				rotate_binary_right2(file, check_if_select);
				if (check_if_select == 0) {
					file->x2 = file->width;
					file->y2 = file->height;
				}
				angle = angle - 90;
			}

		if (file->magicknumber[1] == '3')
			while (angle != 0) {
				rotate_int_right2(file, check_if_select);
				if (check_if_select == 0) {
					file->x2 = file->width;
					file->y2 = file->height;
				}
				angle = angle - 90;
			}
		if (ok && old_angle != -360)
			printf("Rotated %d\n", old_angle);
		else
			printf("Rotated %d\n", old_angle);

		} else if (angle != 0) {
			printf("The selection must be square\n");
		}
	} else if (angle != 0) {
		printf("Unsupported rotation angle\n");
	}
}

void kernel_funct_p3(struct image *file, int x1, int x2, int y1, int y2,
					 int check_if_select, int kernel[3][3], char command[256])
{
	//verific daca am selectat toata imaginea, pentru a nu lua marginiile
	if (check_if_select == 0) {
		x1 = 1;
		x2 = file->width - 1;
		y1 = 1;
		y2 = file->height - 1;
	}
	if (check_if_select == 1) {
		//verific ca daca am selectat doar o zona
		//nu iau marginile intregii imaginii
		if (x1 == 0)
			x1 = 1;
		if (y1 == 0)
			y1 = 1;
		if (x2 == file->width)
			x2 = x2 - 1;
		if (y2 == file->height)
			y2 = y2 - 1;
	}

	//aloc o matrice in care sa salvez raspunsul
	int **result;
	malloc_matrix_int(&result, file->height, file->width * 3);

	for (int c = 0; c < 3; c++) {
		for (int i = y1; i < y2; i++) {
			for (int j = x1; j < x2; j++) {
				float sum_elem = 0;
				//aplic kernel-ul primit, si il salvez in matricea result
					sum_elem = sum_elem +
					file->mat_int[i - 1][(j - 1) * 3 + c] * kernel[0][0] +
					file->mat_int[i - 1][j * 3 + c] * kernel[0][1] +
					file->mat_int[i - 1][(j + 1) * 3 + c] * kernel[0][2] +
					file->mat_int[i][(j - 1) * 3 + c] * kernel[1][0] +
					file->mat_int[i][(j) * 3 + c] * kernel[1][1] +
					file->mat_int[i][(j + 1) * 3 + c] * kernel[1][2] +
					file->mat_int[i + 1][(j - 1) * 3 + c] * kernel[2][0] +
					file->mat_int[i + 1][(j) * 3 + c] * kernel[2][1] +
					file->mat_int[i + 1][(j + 1) * 3 + c] * kernel[2][2];

		if (sum_elem < 0)
			sum_elem = 0;

		if (strcmp(command, "BLUR\n") == 0)
			sum_elem = sum_elem / 9;
		if (strcmp(command, "GAUSSIAN_BLUR\n") == 0)
			sum_elem = sum_elem / 16;
		if (sum_elem > 255)
			sum_elem = 255;
		result[i][j * 3 + c] = round(sum_elem);
			}
		}
	}
	//copiez rezultatele din result in matricea initiala
	for (int c = 0; c < 3; c++)
		for (int i = y1; i < y2; i++)
			for (int j = x1; j < x2; j++)
				file->mat_int[i][j * 3 + c] = result[i][j * 3 + c];
	free_matrix_int(&result, file->height);
}

void kernel_funct_p6(struct image *file, int x1, int x2, int y1, int y2,
					 int check_if_select, int kernel[3][3], char command[256])
{
	if (check_if_select == 0) {
		x1 = 1;
		x2 = file->width - 1;
		y1 = 1;
		y2 = file->height - 1;
	}

	if (check_if_select == 1) {
		if (x1 == 0)
			x1 = 1;
		if (y1 == 0)
			y1 = 1;
		if (x2 == file->width)
			x2 = x2 - 1;
		if (y2 == file->height)
			y2 = y2 - 1;
	}

	unsigned char **result;
	malloc_matrix_binary(&result, file->height, file->width * 3);

	for (int c = 0; c < 3; c++) {
		for (int i = y1; i < y2; i++) {
			for (int j = x1; j < x2; j++) {
				float sum_elem = 0;
				sum_elem = sum_elem +
				file->mat_binary[i - 1][(j - 1) * 3 + c] * kernel[0][0] +
				file->mat_binary[i - 1][j * 3 + c] * kernel[0][1] +
				file->mat_binary[i - 1][(j + 1) * 3 + c] * kernel[0][2] +
				file->mat_binary[i][(j - 1) * 3 + c] * kernel[1][0] +
				file->mat_binary[i][(j) * 3 + c] * kernel[1][1] +
				file->mat_binary[i][(j + 1) * 3 + c] * kernel[1][2] +
				file->mat_binary[i + 1][(j - 1) * 3 + c] * kernel[2][0] +
				file->mat_binary[i + 1][(j) * 3 + c] * kernel[2][1] +
				file->mat_binary[i + 1][(j + 1) * 3 + c] * kernel[2][2];

		if (sum_elem < 0)
			sum_elem = 0;

		if (strcmp(command, "BLUR\n") == 0)
			sum_elem = sum_elem / 9;
		if (strcmp(command, "GAUSSIAN_BLUR\n") == 0)
			sum_elem = sum_elem / 16;
		if (sum_elem > 255)
			sum_elem = 255;
		result[i][j * 3 + c] = round(sum_elem);
		}
		}
	}
	for (int c = 0; c < 3; c++)
		for (int i = y1; i < y2; i++)
			for (int j = x1; j < x2; j++)
				file->mat_binary[i][j * 3 + c] = result[i][j * 3 + c];
	free_matrix_binary(&result, file->height);
}

void apply(struct image *file, int check_if_select)
{
		char parameter[256];
		fgets(parameter, 256, stdin);
		if (parameter[0] == ' ') {
			for (int i = 0; i < strlen(parameter); i++)
				parameter[i] = parameter[i + 1];
		}

		//verific daca parametrul primit este valid
		if (strlen(parameter) < 4 && strcmp(parameter, "\n") != 0) {
			printf("APPLY parameter invalid\n");
		} else {
			if (strcmp(parameter, "SHARPEN\n") == 0) {
				int kernel[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
				if (file->magicknumber[1] == '3') {
					kernel_funct_p3(file, file->x1, file->x2, file->y1,
									file->y2, check_if_select, kernel,
									parameter);
				printf("APPLY SHARPEN done\n");
				} else if (file->magicknumber[1] == '6') {
					kernel_funct_p6(file, file->x1, file->x2, file->y1,
									file->y2, check_if_select, kernel,
									parameter);
				printf("APPLY SHARPEN done\n");
				} else {
					printf("Easy, Charlie Chaplin\n");
				}

			} else if (strcmp(parameter, "EDGE\n") == 0) {
				int kernel[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
				if (file->magicknumber[1] == '3') {
					kernel_funct_p3(file, file->x1, file->x2, file->y1,
									file->y2, check_if_select, kernel,
									parameter);
					printf("APPLY EDGE done\n");
				} else if (file->magicknumber[1] == '6') {
					kernel_funct_p6(file, file->x1, file->x2, file->y1,
									file->y2, check_if_select, kernel,
									parameter);
					printf("APPLY EDGE done\n");
				} else {
					printf("Easy, Charlie Chaplin\n");
				}

			} else if (strcmp(parameter, "BLUR\n") == 0) {
				int kernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
				if (file->magicknumber[1] == '3') {
					kernel_funct_p3(file, file->x1, file->x2, file->y1,
									file->y2, check_if_select, kernel,
									parameter);
					printf("APPLY BLUR done\n");
				} else if (file->magicknumber[1] == '6') {
					kernel_funct_p6(file, file->x1, file->x2, file->y1,
									file->y2, check_if_select, kernel,
									parameter);
					printf("APPLY BLUR done\n");
				}

		if (file->magicknumber[1] == '2' || file->magicknumber[1] == '5')
			printf("Easy, Charlie Chaplin\n");
		} else if (strcmp(parameter, "GAUSSIAN_BLUR\n") == 0) {
			int kernel[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
			if (file->magicknumber[1] == '3') {
				kernel_funct_p3(file, file->x1, file->x2, file->y1, file->y2,
								check_if_select, kernel, parameter);
				printf("APPLY GAUSSIAN_BLUR done\n");
			} else if (file->magicknumber[1] == '6') {
				kernel_funct_p6(file, file->x1, file->x2, file->y1, file->y2,
								check_if_select, kernel, parameter);
				printf("APPLY GAUSSIAN_BLUR done\n");
			}

		if (file->magicknumber[1] == '2' || file->magicknumber[1] == '5')
			printf("Easy, Charlie Chaplin\n");
		} else if (strcmp(parameter, "\n") != 0) {
			printf("APPLY parameter invalid\n");
		} else {
			printf("Invalid command\n");
		}
	}
}

void invalid_command(char command[256])
{
	//verific daca comanda primita este una valida sau nu
	char garbage[256];
	fgets(garbage, 256, stdin);
	int test_if_print = 0;

	if (strcmp(garbage, "\n") != 0 && strcmp(garbage, " ascii\n") != 0 &&
		strcmp(garbage, " ALL\n") != 0) {
		printf("Invalid command\n");
		test_if_print = 1;
	}

	int test_if_case = 0;
	for (int i = 0; i < strlen(command); i++)
		if (command[i] < 'A' || command[i] > 'Z')
			test_if_case = 1;

	if (test_if_case == 0 && strlen(command) != 0 && test_if_print == 0)
		printf("Invalid command\n");
}

void print_image_in_file_int(struct image *file, FILE *f3)
{
	//afisez matricea in fisierul primit in funcite de
	//magic number-ul matricei stocate

	if (file->magicknumber[1] == '2') {
		fprintf(f3, "%s\n%d %d\n%d\n", file->magicknumber, file->width,
				file->height, file->max_value);
	for (int i = 0; i < file->height; i++) {
		for (int j = 0; j < file->width; j++)
			fprintf(f3, "%d ", file->mat_int[i][j]);
		fprintf(f3, "\n");
	}

	} else if (file->magicknumber[1] == '3') {
		fprintf(f3, "%s\n%d %d\n%d\n", file->magicknumber, file->width,
				file->height, file->max_value);
	for (int i = 0; i < file->height; i++) {
		for (int j = 0; j < file->width * 3; j++)
			fprintf(f3, "%d ", file->mat_int[i][j]);
		fprintf(f3, "\n");
	}

	} else if (file->magicknumber[1] == '5') {
		fprintf(f3, "%s\n%d %d\n%d\n", "P2", file->width, file->height,
				file->max_value);
		for (int i = 0; i < file->height; i++) {
			for (int j = 0; j < file->width; j++)
				fprintf(f3, "%d ", (int)file->mat_binary[i][j]);
		fprintf(f3, "\n");
		}

	} else if (file->magicknumber[1] == '6') {
		fprintf(f3, "%s\n%d %d\n%d\n", "P3", file->width, file->height,
				file->max_value);
		for (int i = 0; i < file->height; i++) {
			for (int j = 0; j < file->width * 3; j++)
				fprintf(f3, "%d ", (int)file->mat_binary[i][j]);
		fprintf(f3, "\n");
		}
	}
}

void print_image_in_file_binary(struct image *file, FILE *f3)
{
	if (file->magicknumber[1] == '5') {
		fprintf(f3, "%s\n%d %d\n%d\n", file->magicknumber, file->width,
				file->height, file->max_value);
	for (int i = 0; i < file->height; i++)
		fwrite(file->mat_binary[i], 1, file->width, f3);

	} else if (file->magicknumber[1] == '6') {
		fprintf(f3, "%s\n%d %d\n%d\n", file->magicknumber, file->width,
				file->height, file->max_value);
	for (int i = 0; i < file->height; i++)
		fwrite(file->mat_binary[i], 3, file->width, f3);

	} else if (file->magicknumber[1] == '2') {
		fprintf(f3, "%s\n%d %d\n%d\n", "P5", file->width, file->height,
				file->max_value);

	unsigned char **mat_copy;
	malloc_matrix_binary(&mat_copy, file->height, file->width);
	for (int i = 0; i < file->height; i++)
		for (int j = 0; j < file->width; j++)
			mat_copy[i][j] = (unsigned char)file->mat_int[i][j];

	for (int i = 0; i < file->height; i++)
		fwrite(mat_copy[i], 1, file->width, f3);
	free_matrix_binary(&mat_copy, file->height);

	} else if (file->magicknumber[1] == '3') {
		unsigned char **mat_copy;
		malloc_matrix_binary(&mat_copy, file->height, file->width * 3);

		for (int i = 0; i < file->height; i++)
			for (int j = 0; j < file->width * 3; j++)
				mat_copy[i][j] = (unsigned char)file->mat_int[i][j];
					fprintf(f3, "%s\n%d %d\n%d\n", "P6", file->width,
							file->height, file->max_value);

		for (int i = 0; i < file->height; i++)
			fwrite(mat_copy[i], 3, file->width, f3);
		free_matrix_binary(&mat_copy, file->height);
	}
}

void save(struct image *file)
{
	char file_name_ascii[256];
	fgets(file_name_ascii, 256, stdin);
	for (int i = 0; i < strlen(file_name_ascii); i++)
		file_name_ascii[i] = file_name_ascii[i + 1];
	file_name_ascii[strlen(file_name_ascii) - 1] = '\0';
	int ok = 0;
	for (int i = 0; i < strlen(file_name_ascii); i++)
		if (file_name_ascii[i] == ' ')
			ok = 1;

	//verific daca trebuie salvata matricea pixelilor
	//in format ascii sau binar
	if (ok) {
		char *p = strtok(file_name_ascii, " ");
		char file_name[256];
		strcpy(file_name, p);
		FILE *f3;
		f3 = fopen(file_name, "w");
		print_image_in_file_int(file, f3);
		printf("Saved %s\n", file_name);
		fclose(f3);

	} else {
		FILE *f3;
		f3 = fopen(file_name_ascii, "w");
		print_image_in_file_binary(file, f3);
		printf("Saved %s\n", file_name_ascii);
		fclose(f3);
	}
}

int main(void)
{
	char command[50];
	scanf("%s", command);
	struct image file;
	int check_if_select = 0, check_file = 0;
	FILE *f;
	while (strcmp(command, "EXIT") != 0) {
		if (strcmp(command, "LOAD") == 0) {
			//verific daca am deja un fisier incarcat
			if (check_file == 1)
				fclose(f);
			char file_name[256];
			scanf("%s", file_name);
			f = fopen(file_name, "r");
			if (!f) {
				printf("Failed to load %s\n", file_name);
				free_unkown_matrix(&file);
				check_file = 0;

			} else {
				if (check_file == 1)
					free_unkown_matrix(&file);
				load(&file, f);
				check_file = 1;
				printf("Loaded %s\n", file_name);
			}
		} else if (strcmp(command, "SELECT") == 0) {
			select_image(&file, check_file, &check_if_select);
		} else if (strcmp(command, "HISTOGRAM") == 0) {
			if (check_file) {
				histogram(&file);
			} else {
				char garbage[256];
				fgets(garbage, 256, stdin);
				printf("No image loaded\n");
			}
		} else if (strcmp(command, "EQUALIZE") == 0) {
			if (check_file)
				equalize(&file);
			else
				printf("No image loaded\n");
		} else if (strcmp(command, "CROP") == 0) {
			if (check_file)
				crop(&file, &check_if_select);
			else
				printf("No image loaded\n");
		} else if (strcmp(command, "SAVE") == 0) {
			if (check_file)
				save(&file);
			else
				printf("No image loaded\n");
		} else if (strcmp(command, "ROTATE") == 0) {
			if (check_file != 0)
				rotate(&file, check_if_select);
			else
				printf("No image loaded\n");

		} else if (strcmp(command, "APPLY") == 0) {
			if (check_file != 0) {
				apply(&file, check_if_select);
			} else {
				char garbage[256];
				fgets(garbage, 256, stdin);
				printf("No image loaded\n");
			}

		} else {
			invalid_command(command);
		}

	scanf("%s", command);
	}
	if (check_file)
		free_unkown_matrix(&file);
	else
		printf("No image loaded\n");

	if (check_file)
		fclose(f);
	return 0;
}
