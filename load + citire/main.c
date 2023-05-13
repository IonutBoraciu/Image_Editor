#include <stdio.h>
#include <stdlib.h>
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
int main()
{
    printf("Hello world!\n");
    return 0;
}
