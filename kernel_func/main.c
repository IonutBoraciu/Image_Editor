#include <stdio.h>
#include <stdlib.h>
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
int main()
{
    printf("Hello world!\n");
    return 0;
}
