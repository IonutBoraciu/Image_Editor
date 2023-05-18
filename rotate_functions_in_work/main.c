#include <stdio.h>
#include <stdlib.h>
void rotate_int_to_right(struct image *file, int x1, int x2, int y1, int y2,int check_if_select) {
	int **rotate;
	int n=y2-y1;
	int m=x2-x1;
    rotate=malloc(file->width*sizeof(int*));
    for(int i=0;i<file->width;i++)
        rotate[i]=malloc(file->height*sizeof(int));

    for(int i=y1;i<y2;i++)
        for(int j=x1;j<x2;j++) {

            rotate[j][y2-(i-y1)-1]=file->mat_int[i][j];

		}
	if(check_if_select==0) {
    for(int i=0;i<n;i++)
        free(file->mat_int[i]);
    free(file->mat_int);

    file->mat_int=malloc(m*sizeof(int*));
    for(int i=0;i<m;i++)
        file->mat_int[i]=malloc(n*sizeof(int));
	file->height=m;
	file->width=n;
	}
	if(check_if_select==0) {
    for(int i=x1;i<x2;i++)
        for(int j=y1;j<y2;j++) {
            file->mat_int[i][j]=rotate[i][j];
		}
	}
	else
	{	int j2=y1,i2=x1;
		for(int i=y1;i<y2;i++) {
			j2=y1;
        for(int j=x1;j<x2;j++) {
            file->mat_int[i][j]=rotate[i2][j2];
			j2=j2+1;
		}
		i2=i2+1;
		}
	}
	if(check_if_select==0) {
    for(int i=0;i<file->height;i++)
        free(rotate[i]);
    free(rotate);
	}
	else
	{
		for(int i=0;i<file->width;i++)
        free(rotate[i]);
    free(rotate);
	}


}

void rotate_binary_to_right(struct image *file, int x1, int x2, int y1,int y2,int check_if_select) {
	unsigned char **rotate;
	int n=y2-y1;
	int m=x2-x1;

	rotate=malloc(file->width*sizeof(unsigned char*));
    for(int i=0;i<file->width;i++)
        rotate[i]=malloc(file->height*sizeof(unsigned char));
    for(int i=y1;i<y2;i++)
        for(int j=x1;j<x2;j++)
            rotate[j][y2-(i-y1)-1]=file->mat_binary[i][j];
	if(check_if_select==0) {
    for(int i=0;i<n;i++)
        free(file->mat_binary[i]);
    free(file->mat_binary);

    file->mat_binary=malloc(m*sizeof(unsigned char*));
    for(int i=0;i<m;i++)
        file->mat_binary[i]=malloc(n*sizeof(unsigned char));

	}
    if(check_if_select==0) {
    for(int i=x1;i<x2;i++)
        for(int j=y1;j<y2;j++) {
            file->mat_binary[i][j]=rotate[i][j];
		}
	file->height=m;
	file->width=n;
	}
	else
	{
		int j2=y1,i2=x1;
		for(int i=y1;i<y2;i++) {
			j2=y1;
        for(int j=x1;j<x2;j++) {
            file->mat_binary[i][j]=rotate[i2][j2];
			j2=j2+1;
		}
		i2=i2+1;
		}

	}
	if(check_if_select==0) {
    for(int i=0;i<file->height;i++)
        free(rotate[i]);
    free(rotate);
	}
	else
	{
		for(int i=0;i<file->width;i++)
        free(rotate[i]);
    free(rotate);
	}


}

void rotate_binary_right2(struct image *file, int x1, int x2, int y1,int y2, int check_if_select) {
    unsigned char **rotate;
    int n = y2 - y1;
    int m = x2 - x1;
    rotate = malloc(file->width * sizeof(unsigned char*));
    for (int i = 0; i < file->width; i++) {
        rotate[i] = malloc(file->height* 3 * sizeof(unsigned char));
    }
    for (int i = y1; i < y2; i++) {
        for (int j = x1; j < x2; j++) {
            for (int k = 0; k < 3; k++) {
                rotate[j][(y2 - (i-y1) - 1) * 3 + k] = file->mat_binary[i][j * 3 + k];
            }
        }
    }

    if (check_if_select == 0) {
        for (int i = 0; i < file->height; i++) {
            free(file->mat_binary[i]);
        }
        free(file->mat_binary);

        file->mat_binary = malloc(m * sizeof(unsigned char*));
        for (int i = 0; i < m; i++) {
            file->mat_binary[i] = malloc(n * 3 * sizeof(unsigned char));
        }
		int aux;
        file->height = m;
        file->width = n;


    }
	if(check_if_select==0)
	{
		for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            for (int k = 0; k < 3; k++) {
                file->mat_binary[i][j * 3 + k] = rotate[i][j  * 3 + k];
            }
        }

	}
	}
	else {
	int i2=x1;
	int j2=y1;
    for (int i = y1; i < y2; i++) {
		 j2=y1;
        for (int j = x1; j < x2; j++) {
            for (int k = 0; k < 3; k++) {
                file->mat_binary[i][j * 3 + k] = rotate[i2][j2  * 3 + k];

            }
			j2=j2+1;
        }
		i2=i2+1;

    }
}
	if(check_if_select==0) {
    for (int i = 0; i < file->height; i++) {
        free(rotate[i]);
    }
	free(rotate);
	}
	else
	{
	for (int i = 0; i < file->width; i++) {
        free(rotate[i]);
    }
	free(rotate);
	}


}
void rotate_int_right2(struct image *file, int x1, int x2, int y1,int y2, int check_if_select) {
    int **rotate;
    int n = y2 - y1;
    int m = x2 - x1;
    rotate = malloc(file->width * sizeof(int*));
    for (int i = 0; i < file->width; i++) {
        rotate[i] = malloc(file->height* 3 * sizeof(int));
    }
    for (int i = y1; i < y2; i++) {
        for (int j = x1; j < x2; j++) {
            for (int k = 0; k < 3; k++) {
                rotate[j][(y2 - (i-y1) - 1) * 3 + k] = file->mat_int[i][j * 3 + k];
            }
        }
    }

    if (check_if_select == 0) {
        for (int i = 0; i < file->height; i++) {
            free(file->mat_int[i]);
        }
        free(file->mat_int);

        file->mat_int = malloc(m * sizeof(int*));
        for (int i = 0; i < m; i++) {
            file->mat_int[i] = malloc(n * 3 * sizeof(int));
        }

        file->height = m;
        file->width = n;

    }

    if(check_if_select==0)
	{
		for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            for (int k = 0; k < 3; k++) {
                file->mat_int[i][j * 3 + k] = rotate[i][j  * 3 + k];
            }
        }

	}
	}
	else {
	int i2=x1;
	int j2=y1;
    for (int i = y1; i < y2; i++) {
		 j2=y1;
        for (int j = x1; j < x2; j++) {
            for (int k = 0; k < 3; k++) {
                file->mat_int[i][j * 3 + k] = rotate[i2][j2  * 3 + k];

            }
			j2=j2+1;
        }
		i2=i2+1;

    }
}
	if(check_if_select==0) {
    for (int i = 0; i < file->height; i++) {
        free(rotate[i]);
    }
	free(rotate);
	}
	else
	{
	for (int i = 0; i < file->width; i++) {
        free(rotate[i]);
    }
	free(rotate);
	}
}
int main()
{
    printf("Hello world!\n");
    return 0;
}
