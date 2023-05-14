#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct image {
	char magicknumber[3];
	int height, width;
	int max_value;
	int **mat_int;
	unsigned char **mat_binary;
};

void readPPM_P3(struct image *file, FILE *f) {
	file->mat_int = (int **)malloc(file->height * sizeof(int *));
	if (!file->mat_int) {
		printf("The memory couldn't be allocated\n");
		exit(1);
	}
	for (int i = 0; i < file->height; i++) {
		file->mat_int[i] = (int *)malloc(file->width * 3 * sizeof(int));
		if (!file->mat_int[i]) {
			printf("The memory couldn't be allocated\n");
			exit(1);
		}
	}
	for (int i = 0; i < file->height; i++)
		for (int j = 0; j < file->width * 3; j++)
			fscanf(f, "%d", &file->mat_int[i][j]);
}
void readPPM_P6(struct image *file, FILE *f) {
	file->mat_binary =
			(unsigned char **)malloc(file->height * sizeof(unsigned char *));
	if (!file->mat_binary) {
		printf("The memory couldn't be allocated\n");
		exit(1);
	}
	for (int i = 0; i < file->height; i++) {
		file->mat_binary[i] =
				(unsigned char *)malloc(file->width * 3 * sizeof(unsigned char));
		if (!file->mat_binary[i]) {
			printf("The memory couldn't be allocated\n");
			exit(1);
		}
	}
	for (int i = 0; i < file->height; i++)
		fread(file->mat_binary[i], 3,file->width, f);
}

void readPGM_P2(struct image *file, FILE *f) {
	file->mat_int = (int **)malloc(file->height * sizeof(int *));
	if (!file->mat_int) {
		printf("The memory couldn't be allocated\n");
		exit(1);
	}
	for (int i = 0; i < file->height; i++) {
		file->mat_int[i] = (int *)malloc(file->width * sizeof(int));
		if (!file->mat_int[i]) {
			printf("The memory couldn't be allocated\n");
			exit(1);
		}
	}
	for (int i = 0; i < file->height; i++)
		for (int j = 0; j < file->width; j++) fscanf(f, "%d", &file->mat_int[i][j]);
}

void readPGM_P5(struct image *file, FILE *f) {
	file->mat_binary =
			(unsigned char **)malloc(file->height * sizeof(unsigned char *));
	if (!file->mat_binary) {
		printf("The memory couldn't be allocated\n");
		exit(1);
	}
	for (int i = 0; i < file->height; i++) {
		file->mat_binary[i] =
				(unsigned char *)malloc(file->width * sizeof(unsigned char));
		if (!file->mat_binary[i]) {
			printf("The memory couldn't be allocated\n");
			exit(1);
		}
	}
	for (int i = 0; i < file->height; i++) {
		fread(file->mat_binary[i], sizeof(unsigned char), file->width, f);
	}
}

void ignoreComments(FILE *f) {
	char garbage[256];
	do {
		fgets(garbage, 256, f);
	} while (garbage[0] == '#' || garbage[0] == '\n');
	fseek(f, ftell(f) - strlen(garbage), SEEK_SET);
}

/*void kernel_funct_P3(struct image *file, int x1, int x2, int y1, int y2,
										 int check_if_select, int kernel[3][3],char command[256]) {
if(check_if_select==0)
{
	x1=1;
	x2=file->width-1;
	y1=1;
	y2=file->height-1;
}
if(check_if_select==1)
{
	if(y1!=0)
		y1=y1-1;
	if(y2+1<file->height)
		y2=y2+1;
	if(x2+1<file->width)
		x2=x2+1;
	if(x2!=0)
		x2=x2-1;
}

for (int c = 0; c < 3; c++) {
  for (int i = y1; i < y2; i++) {
    for (int j = x1; j < x2; j++) {
      double sum_elem = 0;
      /*for (int k = -1; k < 2; k++) {
        for (int l = -1; l < 2; l++) {
          int line = i + k;
          int col = j + l;
          if (line < 0) line = 0;
          if (col < 0) col = 0;
          if (line >= file->height) line = file->height-1;
          if (col >= file->width) col = file->width-1;
          sum_elem += file->mat_int[line][col*3 + c] * kernel[k+1][l+1];
        }
      }

	 sum_elem=sum_elem+file->mat_int[i-1][(j)*3+c]*kernel[0][0]+file->mat_int[i-1][(j+1)*3+c]*kernel[0][1]+file->mat_int[i-1][(j+2)*3+c]*kernel[0][2]
	 +file->mat_int[i][(j)*3+c]*kernel[1][0]+file->mat_int[i][(j+1)*3+c]*kernel[1][1]+file->mat_int[i][(j+2)*3+c]*kernel[1][2]+
	 file->mat_int[i+1][(j)*3+c]*kernel[2][0]+file->mat_int[i+1][(j+1)*3+c]*kernel[2][1]+file->mat_int[i+1][(j+2)*3+c]*kernel[2][2];
	  if(sum_elem<0)
	  	sum_elem=0;

	if(strcmp(command,"BLUR\n")==0) {
	  		sum_elem=sum_elem/9;
	  }
	if(strcmp(command,"GAUSSIAN_BLUR\n")==0){
		  sum_elem=sum_elem/16;
		}
	//if(sum_elem>255)
	  //	sum_elem=255;
      file->mat_int[i][j*3 + c] = sum_elem;
    }
  }
}
}

*/
/*void kernel_funct_P3(struct image *file, int x1, int x2, int y1, int y2,
										 int check_if_select, int kernel[3][3],char command[256]) {
if(check_if_select==0)
{
	 x1=1;
	 x2=file->width-1;
	 y1=1;
	 y2=file->height-1;
}

  for (int i = y1; i < y2; i++) {
    for (int j = x1; j < x2; j++) {
		for (int c = 0; c < 3; c++) {
      int sum_elem = 0;
      for (int k = -1; k < 2; k++) {
        for (int l = -1; l < 2; l++) {
          int line = i + k;
          int col = j + l;

          if (line < 0) line = 0;
          if (col < 0) col = 0;
          if (line >= file->height) line = file->height-1;
          if (col >= file->width) col =  file->width-1;;

          sum_elem += (int)file->mat_int[line][col*3 + c] * kernel[k+1][l+1];
        }
      }
	  if(sum_elem<0)
	  	sum_elem=0;
	if(strcmp(command,"SHARPEN\n")==0 || strcmp(command,"EDGE\n")==0)
	  if(sum_elem>255)
	  	sum_elem=255;
	  if(strcmp(command,"BLUR\n")==0) {
	  		sum_elem=sum_elem/9;
	  }
	  if(strcmp(command,"GAUSSIAN_BLUR\n")==0){
		  sum_elem=sum_elem/16;
		}

      file->mat_int[i][j*3 + c] = sum_elem;

    }
  }
	}


}
*/

/*void kernel_funct_P3(struct image *file, int x1, int x2, int y1, int y2,
										 int check_if_select, int kernel[3][3],char command[256]) {
if(check_if_select==0)
{
	 x1=1;
	 x2=file->width-1;
	 y1=1;
	 y2=file->height-1;
}
 for (int c = 0; c < 3; c++) {
  for (int i = y1; i < y2; i++) {
    for (int j = x1; j < x2; j++) {

     int sum_elem = 0;
     /* for (int k = -1; k < 2; k++) {
        for (int l = -1; l < 2; l++) {
          int line = i + k;
          int col = j + l;

          if (line < 0) line = 0;
          if (col < 0) col = 0;
          if (line >= file->height) line = file->height-1;
          if (col >= file->width) col =  file->width-1;;

          sum_elem += (int)file->mat_int[line][col*3 + c] * kernel[k+1][l+1];
        }
      }

	 sum_elem=sum_elem+file->mat_int[i-1][(j-1)*3+c]*kernel[0][0]+file->mat_int[i-1][j*3+c]*kernel[0][1]+file->mat_int[i-1][(j+1)*3+c]*kernel[0][2]+
	 file->mat_int[i][(j-1)*3+c]*kernel[1][0]+file->mat_int[i][(j)*3+c]*kernel[1][1]+file->mat_int[i][(j+1)*3+c]*kernel[1][2]+
	 file->mat_int[i+1][(j-1)*3+c]*kernel[2][0]+file->mat_int[i+1][(j)*3+c]*kernel[2][1]+file->mat_int[i+1][(j+1)*3+c]*kernel[2][2];

	  if(sum_elem<0)
	  	sum_elem=0;
	if(strcmp(command,"SHARPEN\n")==0 || strcmp(command,"EDGE\n")==0)
	  if(sum_elem>255)
	  	sum_elem=255;
	  if(strcmp(command,"BLUR\n")==0) {
	  		sum_elem=sum_elem/9;
	  }
	  if(strcmp(command,"GAUSSIAN_BLUR\n")==0){
		  sum_elem=sum_elem/16;
		}

      file->mat_int[i][j*3 + c] = sum_elem;


  }
	}
 }
}
*/
void kernel_funct_P3(struct image *file, int x1, int x2, int y1, int y2,
										 int check_if_select, int kernel[3][3],char command[256]) {
if(check_if_select==0)
{
	 x1=1;
	 x2=file->width-1;
	 y1=1;
	 y2=file->height-1;
}
if(check_if_select==1)
{
	if(x1==0)
		x1=1;
	if(y1==0)
		y1=1;
	if(x2==file->width)
		x2=x2-1;
	if(y2==file->height)
	y2=y2-1;

}
int **result;
result=malloc(file->height*sizeof(int*));
for(int i=0;i<file->height;i++)
	result[i]=malloc(file->width*3*sizeof(int));
 for (int c = 0; c < 3; c++) {
  for (int i = y1; i < y2; i++) {
    for (int j = x1; j < x2; j++) {

     float sum_elem = 0;
     /* for (int k = -1; k < 2; k++) {
        for (int l = -1; l < 2; l++) {
          int line = i + k;
          int col = j + l;

          if (line < 0) line = 0;
          if (col < 0) col = 0;
          if (line >= file->height) line = file->height-1;
          if (col >= file->width) col =  file->width-1;;

          sum_elem += (int)file->mat_int[line][col*3 + c] * kernel[k+1][l+1];
        }
      }
	  */
	 sum_elem=sum_elem+file->mat_int[i-1][(j-1)*3+c]*kernel[0][0]+file->mat_int[i-1][j*3+c]*kernel[0][1]+file->mat_int[i-1][(j+1)*3+c]*kernel[0][2]+
	 file->mat_int[i][(j-1)*3+c]*kernel[1][0]+file->mat_int[i][(j)*3+c]*kernel[1][1]+file->mat_int[i][(j+1)*3+c]*kernel[1][2]+
	 file->mat_int[i+1][(j-1)*3+c]*kernel[2][0]+file->mat_int[i+1][(j)*3+c]*kernel[2][1]+file->mat_int[i+1][(j+1)*3+c]*kernel[2][2];

	  if(sum_elem<0)
	  	sum_elem=0;
	//if(strcmp(command,"SHARPEN\n")==0 || strcmp(command,"EDGE\n")==0)

	  if(strcmp(command,"BLUR\n")==0) {
	  		sum_elem=sum_elem/9;
	  }
	  if(strcmp(command,"GAUSSIAN_BLUR\n")==0){
		  sum_elem=sum_elem/16;
		}
	  if(sum_elem>255)
	  	sum_elem=255;
      result[i][j*3 + c] = round(sum_elem);


  }

	}
 }
 for (int c = 0; c < 3; c++)
	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			file->mat_int[i][j*3+c]=result[i][j*3+c];
	for(int i=0;i<file->height;i++)
		free(result[i]);
		free(result);
}

void kernel_funct_P6(struct image *file, int x1, int x2, int y1, int y2,
										 int check_if_select, int kernel[3][3],char command[256]) {
if(check_if_select==0)
{
	 x1=1;
	 x2=file->width-1;
	 y1=1;
	 y2=file->height-1;
}
if(check_if_select==1)
{
	if(x1==0)
		x1=1;
	if(y1==0)
		y1=1;
	if(x2==file->width)
		x2=x2-1;
	if(y2==file->height)
	y2=y2-1;

}
unsigned char **result;
result=malloc(file->height*sizeof(unsigned char*));
for(int i=0;i<file->height;i++)
	result[i]=malloc(file->width*3*sizeof(unsigned char));
 for (int c = 0; c < 3; c++) {
  for (int i = y1; i < y2; i++) {
    for (int j = x1; j < x2; j++) {

     float sum_elem = 0;
     /* for (int k = -1; k < 2; k++) {
        for (int l = -1; l < 2; l++) {
          int line = i + k;
          int col = j + l;

          if (line < 0) line = 0;
          if (col < 0) col = 0;
          if (line >= file->height) line = file->height-1;
          if (col >= file->width) col =  file->width-1;;

          sum_elem += (int)file->mat_int[line][col*3 + c] * kernel[k+1][l+1];
        }
      }
	  */
	 sum_elem=sum_elem+file->mat_binary[i-1][(j-1)*3+c]*kernel[0][0]+file->mat_binary[i-1][j*3+c]*kernel[0][1]+file->mat_binary[i-1][(j+1)*3+c]*kernel[0][2]+
	 file->mat_binary[i][(j-1)*3+c]*kernel[1][0]+file->mat_binary[i][(j)*3+c]*kernel[1][1]+file->mat_binary[i][(j+1)*3+c]*kernel[1][2]+
	 file->mat_binary[i+1][(j-1)*3+c]*kernel[2][0]+file->mat_binary[i+1][(j)*3+c]*kernel[2][1]+file->mat_binary[i+1][(j+1)*3+c]*kernel[2][2];

	  if(sum_elem<0)
	  	sum_elem=0;
	//if(strcmp(command,"SHARPEN\n")==0 || strcmp(command,"EDGE\n")==0)

	  if(strcmp(command,"BLUR\n")==0) {
	  		sum_elem=sum_elem/9;
	  }
	  if(strcmp(command,"GAUSSIAN_BLUR\n")==0){
		  sum_elem=sum_elem/16;
		}
	  if(sum_elem>255)
	  	sum_elem=255;
      result[i][j*3 + c] = round(sum_elem);


  }

	}
 }
 for (int c = 0; c < 3; c++)
	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			file->mat_binary[i][j*3+c]=result[i][j*3+c];
	for(int i=0;i<file->height;i++)
		free(result[i]);
		free(result);
}
int main() {
	char command[50];
	scanf("%s", command);
	struct image file;
	int check_if_select = 0, x1, x2, y1, y2, check_file = 0;

	FILE *f;
	while (strcmp(command, "EXIT") != 0) {
		if (strcmp(command, "LOAD") == 0) {
			if (check_file == 1) fclose(f);
			char file_name[256];
			scanf("%s", file_name);
			f = fopen(file_name, "r");
			if (!f) {
				printf("Failed to load %s\n", file_name);
				if (file.magicknumber[1] == '2' || file.magicknumber[1] == '3') {
					for (int i = 0; i < file.height; i++) free(file.mat_int[i]);
					free(file.mat_int);
				}
				if (file.magicknumber[1] == '5' || file.magicknumber[1] == '6') {
					for (int i = 0; i < file.height; i++) free(file.mat_binary[i]);
					free(file.mat_binary);
				}

				check_file = 0;

			} else {
				if (check_file == 1) {
					if (file.magicknumber[1] == '2' || file.magicknumber[1] == '3') {
						for (int i = 0; i < file.height; i++) free(file.mat_int[i]);
						free(file.mat_int);
					}
					if (file.magicknumber[1] == '5' || file.magicknumber[1] == '6') {
						for (int i = 0; i < file.height; i++) free(file.mat_binary[i]);
						free(file.mat_binary);
					}
				}
				fscanf(f, "%s", file.magicknumber);
				ignoreComments(f);
				fscanf(f, "%d%d", &file.width, &file.height);
				ignoreComments(f);
				fscanf(f, "%d", &file.max_value);
				x1 = 0;
				x2 = file.width;
				y1 = 0;
				y2 = file.height;
				ignoreComments(f);

				if (file.magicknumber[0] == 'P' && file.magicknumber[1] == '3')
					readPPM_P3(&file, f);
				if (file.magicknumber[0] == 'P' && file.magicknumber[1] == '6')
					readPPM_P6(&file, f);
				if (file.magicknumber[0] == 'P' && file.magicknumber[1] == '2')
					readPGM_P2(&file, f);
				if (file.magicknumber[0] == 'P' && file.magicknumber[1] == '5')
					readPGM_P5(&file, f);
				printf("Loaded %s\n", file_name);
				check_file = 1;
			}
		} else if (strcmp(command, "SELECT") == 0) {
			if (check_file) {
				char check_param[256];
				fgets(check_param, 256, stdin);
				if (check_param[0] == ' ')
					for (int i = 0; i < strlen(check_param); i++)
						check_param[i] = check_param[i + 1];
				int number_of_spaces = 0;
				for (int i = 0; i < strlen(check_param); i++)
					if (check_param[i] == ' ') number_of_spaces = number_of_spaces + 1;
				int check_if_number = 1;
				for (int i = 0; i < strlen(check_param); i++)
					if ((check_param[i] < 48 || check_param[i] > 57) &&
							check_param[i] != ' ' && check_param[i] != '\n' &&
							check_param[i] != '-')
						check_if_number = 0;
				if (check_if_number && number_of_spaces == 3) {
					char *p = strtok(check_param, " ");
					x1 = atoi(p);
					p = strtok(NULL, " ");
					y1 = atoi(p);
					p = strtok(NULL, " ");
					x2 = atoi(p);
					p = strtok(NULL, "\n");
					y2 = atoi(p);
				}
				if (number_of_spaces == 3 && check_if_number) {
					if (x1 > x2) {
						int aux = x1;
						x1 = x2;
						x2 = aux;
					}
					if (y1 > y2) {
						int aux = y1;
						y1 = y2;
						y2 = aux;
					}
					if (x1 < 0 || x2 > file.width || y1 < 0 || y2 > file.height  ||
							(x2 - x1 == 0) || (y2 - y1 == 0)) {
						printf("Invalid set of coordinates\n");
						x1 = 0;
						x2 = file.width;
						y1 = 0;
						y2 = file.height;
					} else {
						check_if_select = 1;
						printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
						if(x1==0 && y1==0 && x2==file.width && y2==file.height)
							check_if_select=0;
					}

				} else if (strcmp(check_param, "ALL\n") == 0 || strcmp(check_param, "ALL \n")==0) {
					check_if_select = 0;
					x1 = 0;
					x2 = file.width;
					y1 = 0;
					y2 = file.height;
					printf("Selected ALL\n");
				} else {
					printf("Invalid command\n");
				}

			} else {
				char garbage[256];
				fgets(garbage,256,stdin);
				printf("No image loaded\n");
			}
		} else if (strcmp(command, "HISTOGRAM") == 0) {
			if (check_file) {
				char check_if_param[256];
				int check = 0;
				fgets(check_if_param, 256, stdin);
				if (check_if_param[0] == ' ')
					for (int i = 0; i < strlen(check_if_param); i++)
						check_if_param[i] = check_if_param[i + 1];
				for (int i = 0; i < strlen(check_if_param); i++)
					if (check_if_param[i] == ' ') check = check + 1;
				if (!check || check != 1) {
					printf("Invalid command\n");
				} else if (check == 1) {
					if (file.magicknumber[1] == '3' || file.magicknumber[1] == '6')
						printf("Black and white image needed\n");
					else {
						int stars, bins, max = 0;
						char *p = strtok(check_if_param, " ");
						stars = atoi(p);
						p = strtok(NULL, " ");
						bins = atoi(p);
						if (file.magicknumber[1] == '2') {
							int Histogram[256] = {0};
							max = 0;
							for (int i = 0; i < file.height; i++)
								for (int j = 0; j < file.width; j++) {
									int value = file.mat_int[i][j];
									Histogram[value] = Histogram[value] + 1;
								}
							int bin[256] = {0};
							int val = 256 / bins;
							int k = 0, j = 0;
							for (int i = 0; i < bins; i = i + 1) {
								int copy = val;
								int s = 0;
								while (copy != 0) {
									s = s + Histogram[j];
									copy = copy - 1;
									j = j + 1;
								}
								bin[i] = s;
								if (bin[i] > max) max = bin[i];
							}
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
						if (file.magicknumber[1] == '5') {
							int Histogram[256] = {0};
							max = 0;
							for (int i = 0; i < file.height; i++)
								for (int j = 0; j < file.width; j++) {
									int value = (int)file.mat_binary[i][j];
									Histogram[value] = Histogram[value] + 1;
								}
							int bin[256] = {0};
							int val = 256 / bins;
							int k = 0, j = 0;
							for (int i = 0; i < bins; i = i + 1) {
								int copy = val;
								int s = 0;
								while (copy != 0) {
									s = s + Histogram[j];
									copy = copy - 1;
									j = j + 1;
								}
								bin[i] = s;
								if (bin[i] > max) max = bin[i];
							}
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
			} else {
				char garbage[256];
				fgets(garbage,256,stdin);
				printf("No image loaded\n");
			}
		} else if (strcmp(command, "EQUALIZE") == 0) {
			if (check_file) {
				if (file.magicknumber[1] == '3' || file.magicknumber[1] == '6') {
					printf("Black and white image needed\n");
				}
				if (file.magicknumber[1] == '2') {
					int Histogram[256] = {0};
					for (int i = 0; i < file.height; i++)
						for (int j = 0; j < file.width; j++) {
							int value = file.mat_int[i][j];
							Histogram[value] = Histogram[value] + 1;
						}
					int area = file.height * file.width;
					int s = 0, vec_aux[256];
					for (int a = 0; a <= 255; a++) {
						s += Histogram[a];
						vec_aux[a] = (int)(255 * s / area);
					}
					for (int i = 0; i < file.height; i++)
						for (int j = 0; j < file.width; j++) {
							int value = file.mat_int[i][j];
							file.mat_int[i][j] = vec_aux[value];
						}
					printf("Equalize done\n");

				} else if (file.magicknumber[1] == '5') {
					int Histogram[256] = {0};
					for (int i = 0; i < file.height; i++)
						for (int j = 0; j < file.width; j++) {
							int value = (int)file.mat_binary[i][j];
							Histogram[value] = Histogram[value] + 1;
						}
					int area = file.height * file.width;
					int s = 0, vec_aux[256];
					for (int a = 0; a <= 255; a++) {
						s += Histogram[a];
						vec_aux[a] = (int)(255 * ((float)s / area));
					}
					for (int i = 0; i < file.height; i++)
						for (int j = 0; j < file.width; j++) {
							int value = (int)file.mat_binary[i][j];
							file.mat_binary[i][j] = vec_aux[value];
						}
					printf("Equalize done\n");
				}

			} else {
				printf("No image loaded\n");
			}

		} else if (strcmp(command, "CROP") == 0) {
			if (check_file) {
				if (file.magicknumber[1] == '2') {
					int **mat_copy;

					mat_copy = malloc((y2 - y1) * sizeof(int *));
					for (int i = 0; i < y2 - y1; i++)
						mat_copy[i] = malloc((x2 - x1) * sizeof(int));

					int i2 = 0, j2 = 0;

					int nr = 0;
					for (int i = y1; i < y2; i++) {
						j2 = 0;
						for (int j = x1; j < x2; j++) {
							mat_copy[i2][j2] = file.mat_int[i][j];
							j2 = j2 + 1;
						}
						i2 = i2 + 1;
					}

					for (int i = 0; i < file.height; i++) free(file.mat_int[i]);
					free(file.mat_int);
					file.height = y2 - y1;
					file.width = x2 - x1;
					file.mat_int = malloc((file.height * sizeof(int *)));
					for (int i = 0; i < file.height; i++)
						file.mat_int[i] = malloc(file.width * sizeof(int));
					for (int i = 0; i < file.height; i++)
						for (int j = 0; j < file.width; j++)
							file.mat_int[i][j] = mat_copy[i][j];
					for (int i = 0; i < file.height; i++) free(mat_copy[i]);
					free(mat_copy);
					printf("Image cropped\n");

				} else if (file.magicknumber[1] == '5') {
					unsigned char **mat_copy;
					mat_copy = malloc((y2 - y1) * sizeof(unsigned char *));
					for (int i = 0; i < y2 - y1; i++)
						mat_copy[i] = malloc((x2 - x1) * sizeof(unsigned char));
					int i2 = 0, j2 = 0;
					for (int i = y1; i < y2; i++) {
						j2 = 0;
						for (int j = x1; j < x2; j++) {
							mat_copy[i2][j2] = file.mat_binary[i][j];
							j2 = j2 + 1;
						}
						i2 = i2 + 1;
					}
					for (int i = 0; i < file.height; i++) free(file.mat_binary[i]);
					free(file.mat_binary);
					file.height = y2 - y1;
					file.width = x2 - x1;
					file.mat_binary = malloc((file.height * sizeof(unsigned char *)));
					for (int i = 0; i < y2 - y1; i++)
						file.mat_binary[i] = malloc(file.width * sizeof(unsigned char));
					for (int i = 0; i < file.height; i++)
						for (int j = 0; j < file.width; j++)
							file.mat_binary[i][j] = mat_copy[i][j];
					for (int i = 0; i < file.height; i++) free(mat_copy[i]);
					free(mat_copy);
					printf("Image cropped\n");

				} else if (file.magicknumber[1] == '3') {
					int **mat_copy;
					mat_copy = malloc((y2 - y1) * sizeof(int *));
					for (int i = 0; i < y2 - y1; i++)
						mat_copy[i] = malloc((x2 - x1) * 3 * sizeof(int));
					int i2 = 0, j2 = 0;
					for (int i = y1; i < y2; i++) {
						j2 = 0;
						for (int j = x1 * 3; j < x2 * 3; j = j + 3) {
							mat_copy[i2][j2] = file.mat_int[i][j];
							mat_copy[i2][j2 + 1] = file.mat_int[i][j + 1];
							mat_copy[i2][j2 + 2] = file.mat_int[i][j + 2];
							j2 = j2 + 3;
						}
						i2 = i2 + 1;
					}

					for (int i = 0; i < file.height; i++) free(file.mat_int[i]);
					free(file.mat_int);
					file.height = y2 - y1;
					file.width = x2 - x1;
					file.mat_int = malloc((file.height * sizeof(int *)));
					for (int i = 0; i < y2 - y1; i++)
						file.mat_int[i] = malloc(file.width * 3 * sizeof(int));
					for (int i = 0; i < file.height; i++)
						for (int j = 0; j < file.width * 3; j++)
							file.mat_int[i][j] = mat_copy[i][j];
					for (int i = 0; i < file.height; i++) free(mat_copy[i]);
					free(mat_copy);
					printf("Image cropped\n");

				} else if (file.magicknumber[1] == '6') {
					unsigned char **mat_copy;
					mat_copy = malloc((y2 - y1) * sizeof(unsigned char *));
					for (int i = 0; i < y2 - y1; i++)
						mat_copy[i] = malloc((x2 - x1) * 3 * sizeof(unsigned char));
					int i2 = 0, j2 = 0;
					for (int i = y1; i < y2; i++) {
						j2 = 0;
						for (int j = x1 * 3; j < x2 * 3; j = j + 3) {
							mat_copy[i2][j2] = file.mat_binary[i][j];
							mat_copy[i2][j2 + 1] = file.mat_binary[i][j + 1];
							mat_copy[i2][j2 + 2] = file.mat_binary[i][j + 2];
							j2 = j2 + 3;
						}
						i2 = i2 + 1;
					}

					for (int i = 0; i < file.height; i++) free(file.mat_binary[i]);
					free(file.mat_binary);
					file.height = y2 - y1;
					file.width = x2 - x1;
					file.mat_binary = malloc((file.height * sizeof(unsigned char *)));
					for (int i = 0; i < file.height; i++)
						file.mat_binary[i] = malloc(file.width * 3 * sizeof(unsigned char));
					for (int i = 0; i < file.height; i++)
						for (int j = 0; j < file.width * 3; j++)
							file.mat_binary[i][j] = mat_copy[i][j];

					for (int i = 0; i < file.height; i++) free(mat_copy[i]);
					free(mat_copy);
					printf("Image cropped\n");
				}
				x1 = 0;
				y1 = 0;
				x2 = file.width;
				y2 = file.height;
				check_if_select=0;

			} else {
				printf("No image loaded\n");
			}

		} else if (strcmp(command, "SAVE") == 0) {
			if (check_file) {
				char file_name_ascii[256];
				fgets(file_name_ascii, 256, stdin);
				for (int i = 0; i < strlen(file_name_ascii); i++)
					file_name_ascii[i] = file_name_ascii[i + 1];
				file_name_ascii[strlen(file_name_ascii) - 1] = '\0';
				int ok = 0;
				for (int i = 0; i < strlen(file_name_ascii); i++)
					if (file_name_ascii[i] == ' ') ok = 1;
				if (ok) {
					char *p = strtok(file_name_ascii, " ");
					char file_name[256];
					strcpy(file_name, p);
					FILE *f3;
					f3 = fopen(file_name, "w");
					if (file.magicknumber[1] == '2') {
						fprintf(f3, "%s\n%d %d\n%d\n", file.magicknumber, file.width,
										file.height, file.max_value);
						for (int i = 0; i < file.height; i++) {
							for (int j = 0; j < file.width; j++)

								fprintf(f3, "%d ", file.mat_int[i][j]);

							fprintf(f3, "\n");
						}
					} else if (file.magicknumber[1] == '3') {
						fprintf(f3, "%s\n%d %d\n%d\n", file.magicknumber, file.width,
										file.height, file.max_value);
						for (int i = 0; i < file.height; i++) {
							for (int j = 0; j < file.width * 3; j++)
								fprintf(f3, "%d ", file.mat_int[i][j]);
							fprintf(f3, "\n");
						}
					} else if (file.magicknumber[1] == '5') {
						fprintf(f3, "%s\n%d %d\n%d\n", "P2", file.width, file.height,
										file.max_value);
						for (int i = 0; i < file.height; i++) {
							for (int j = 0; j < file.width; j++)

								fprintf(f3, "%d ", (int)file.mat_binary[i][j]);
							fprintf(f3, "\n");
						}
					} else if (file.magicknumber[1] == '6') {
						fprintf(f3, "%s\n%d %d\n%d\n", "P3", file.width, file.height,
										file.max_value);
						for (int i = 0; i < file.height; i++) {
							for (int j = 0; j < file.width * 3; j++)

								fprintf(f3, "%d ", (int)file.mat_binary[i][j]);

							fprintf(f3, "\n");
						}
					}
					printf("Saved %s\n", file_name);
					fclose(f3);

				} else {
					FILE *f3;
					f3 = fopen(file_name_ascii, "w");

					if (file.magicknumber[1] == '5') {
						fprintf(f3, "%s\n%d %d\n%d\n", file.magicknumber, file.width,
										file.height, file.max_value);
						for (int i = 0; i < file.height; i++)
							fwrite(file.mat_binary[i], 1, file.width, f3);
					} else if (file.magicknumber[1] == '6') {
						fprintf(f3, "%s\n%d %d\n%d\n", file.magicknumber, file.width,
										file.height, file.max_value);
						for (int i = 0; i < file.height; i++)
							fwrite(file.mat_binary[i], 3, file.width, f3);
					} else if (file.magicknumber[1] == '2') {
						fprintf(f3, "%s\n%d %d\n%d\n", "P5", file.width, file.height,
										file.max_value);
						unsigned char **mat_copy;
						mat_copy = malloc(file.height * sizeof(unsigned char *));
						for (int i = 0; i < file.height; i++)
							mat_copy[i] = malloc(file.width * sizeof(unsigned char));
						for (int i = 0; i < file.height; i++)
							for (int j = 0; j < file.width; j++)
								mat_copy[i][j] = (unsigned char)file.mat_int[i][j];
						for (int i = 0; i < file.height; i++)
							fwrite(mat_copy[i], 1, file.width, f3);
						for (int i = 0; i < file.height; i++) free(mat_copy[i]);
						free(mat_copy);
					} else if (file.magicknumber[1] == '3') {
						unsigned char **mat_copy;
						mat_copy = malloc(file.height * sizeof(unsigned char *));
						for (int i = 0; i < file.height; i++)
							mat_copy[i] = malloc(file.width * 3 * sizeof(unsigned char));
						for (int i = 0; i < file.height; i++)
							for (int j = 0; j < file.width * 3; j++)
								mat_copy[i][j] = (unsigned char)file.mat_int[i][j];
						fprintf(f3, "%s\n%d %d\n%d\n", "P6", file.width, file.height,
										file.max_value);
						for (int i = 0; i < file.height; i++)
							fwrite(mat_copy[i], 3, file.width, f3);
						for (int i = 0; i < file.height; i++) free(mat_copy[i]);
						free(mat_copy);
					}
					printf("Saved %s\n", file_name_ascii);
					fclose(f3);
				}

			} else {
				printf("No image loaded\n");
			}
		} else if (strcmp(command, "ROTATE") == 0) {
			if (check_file) {
				int angle;
				scanf("%d", &angle);
				int already_print = 0;
				if (angle == 0) printf("Rotated 0\n"), already_print = 1;
				;
				if (angle % 90 == 0 && angle != 0) {
					int ok = 0, old_angle;
					old_angle = angle;
					if (angle < 0) {
						ok = 1;
					}
					while (angle < 0) angle = angle + 360;
					if (old_angle == -360) {
						printf("Rotated -360\n");
						already_print = 1;
					}
					if ((((y2 - y1) == (x2 - x1) && check_if_select == 1) ||
							 check_if_select == 0) &&
							already_print == 0) {
						if (file.magicknumber[1] == '2')
							while (angle != 0 && angle > 0) {
								//TO DO
								if(check_if_select==0){

									x2=file.width;
									y2=file.height;
								}
								angle = angle - 90;
							}
						if (file.magicknumber[1] == '5')
							while (angle != 0 && angle > 0) {
								//TO DO
								if(check_if_select==0){

									x2=file.width;
									y2=file.height;
								}

								angle = angle - 90;
							}
						if (file.magicknumber[1] == '6')
							while (angle != 0 && angle > 0) {
								//TO DO
								if(check_if_select==0){

									x2=file.width;
									y2=file.height;
								}
								angle = angle - 90;
							}
						if (file.magicknumber[1] == '3')
							while (angle != 0) {
								//TO DO
								if(check_if_select==0){

									x2=file.width;
									y2=file.height;
								}
								angle = angle - 90;
							}
						if (ok && old_angle != -360)
							printf("Rotated %d\n", old_angle);
						else
							printf("Rotated %d\n", old_angle);

					} else if (angle != 0)
						printf("The selection must be square\n");
				} else if (angle != 0)
					printf("Unsupported rotation angle\n");
			} else {
				printf("No image loaded\n");
			}
		} else if (strcmp(command, "APPLY") == 0) {
			if (check_file) {
				char parameter[256];
				fgets(parameter, 256, stdin);
				if (parameter[0] == ' ') {
					for (int i = 0; i < strlen(parameter); i++)
						parameter[i] = parameter[i + 1];
				}

				if (strlen(parameter) < 4 && strcmp(parameter,"\n")!=0) {
					printf("APPLY parameter invalid\n");
				} else {
					if (strcmp(parameter, "SHARPEN\n") == 0) {
						int kernel[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
						if(file.magicknumber[1]=='3') {
							kernel_funct_P3(&file,x1,x2,y1,y2,check_if_select,kernel,parameter);
							printf("APPLY SHARPEN done\n");
						}
						if(file.magicknumber[1]=='6') {
							kernel_funct_P6(&file, x1, x2, y1, y2, check_if_select, kernel,parameter);
							printf("APPLY SHARPEN done\n");
						}

						if(file.magicknumber[1]=='2' || file.magicknumber[1]=='5')
							printf("Easy, Charlie Chaplin\n");
					}
					else if (strcmp(parameter, "EDGE\n") == 0) {
						int kernel[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
						if(file.magicknumber[1]=='3') {
							kernel_funct_P3(&file,x1,x2,y1,y2,check_if_select,kernel,parameter);
							printf("APPLY EDGE done\n");
						}
					if(file.magicknumber[1]=='6')  {
							kernel_funct_P6(&file, x1, x2, y1, y2, check_if_select, kernel,parameter);
							printf("APPLY EDGE done\n");
					}
						if(file.magicknumber[1]=='2' || file.magicknumber[1]=='5')
							printf("Easy, Charlie Chaplin\n");
					}
					else if (strcmp(parameter, "BLUR\n") == 0) {
						int kernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
						if(file.magicknumber[1]=='3') {
							kernel_funct_P3(&file, x1, x2, y1, y2, check_if_select, kernel,parameter);
							printf("APPLY BLUR done\n");
						}
						else if(file.magicknumber[1]=='6') {
							kernel_funct_P6(&file, x1, x2, y1, y2, check_if_select, kernel,parameter);
							printf("APPLY BLUR done\n");
						}

						if(file.magicknumber[1]=='2' || file.magicknumber[1]=='5')
							printf("Easy, Charlie Chaplin\n");
					}
					else if(strcmp(parameter,"GAUSSIAN_BLUR\n")==0){
						int kernel[3][3]={{1,2,1},{2,4,2},{1,2,1}};
						if(file.magicknumber[1]=='3') {
							kernel_funct_P3(&file, x1, x2, y1, y2, check_if_select, kernel,parameter);
							printf("APPLY GAUSSIAN_BLUR done\n");
						}
						else if(file.magicknumber[1]=='6'){
							kernel_funct_P6(&file, x1, x2, y1, y2, check_if_select, kernel,parameter);
							printf("APPLY GAUSSIAN_BLUR done\n");
						}

						if(file.magicknumber[1]=='2' || file.magicknumber[1]=='5')
							printf("Easy, Charlie Chaplin\n");
					}
					else if(strcmp(parameter,"\n")!=0)
					{
						printf("APPLY parameter invalid\n");
					}
					else
					{
						printf("Invalid command\n");
					}


				}

			} else {
				printf("No image loaded\n");
			}
		}
		else
		{
			char garbage[256];
			fgets(garbage,256,stdin);
			if(strcmp(garbage,"\n")!=0 && strcmp(garbage," ascii\n")!=0 && strcmp(garbage," ALL\n")!=0)
			printf("Invalid command\n");
		}


		scanf("%s", command);
	}
	if (check_file) {
		if (file.magicknumber[1] == '2' || file.magicknumber[1] == '3') {
			for (int i = 0; i < file.height; i++) free(file.mat_int[i]);
			free(file.mat_int);
		}
		if (file.magicknumber[1] == '5' || file.magicknumber[1] == '6') {
			for (int i = 0; i < file.height; i++) free(file.mat_binary[i]);
			free(file.mat_binary);
		}
	} else {
		printf("No image loaded\n");
	}

	if (check_file) fclose(f);
	return 0;
}
