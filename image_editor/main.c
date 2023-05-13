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


