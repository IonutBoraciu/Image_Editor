#include <stdio.h>
#include <stdlib.h>
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

int main()
{
    printf("Hello world!\n");
    return 0;
}
