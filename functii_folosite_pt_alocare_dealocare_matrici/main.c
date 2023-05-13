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
int main()
{
    printf("Hello world!\n");
    return 0;
}
