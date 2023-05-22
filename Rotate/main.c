#include <stdio.h>
#include <stdlib.h>
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
int main()
{
    printf("Hello world!\n");
    return 0;
}
