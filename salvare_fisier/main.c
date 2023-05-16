#include <stdio.h>
#include <stdlib.h>
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
int main()
{
    printf("Hello world!\n");
    return 0;
}
