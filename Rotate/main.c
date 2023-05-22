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
int main()
{
    printf("Hello world!\n");
    return 0;
}
