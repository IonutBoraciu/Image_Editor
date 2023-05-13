#include <stdio.h>
#include <stdlib.h>
void select_part_image (struct image *pic, int *x1, int *y1, int *x2, int *y2) {

   int help;
   if (*x1 < *x2 && *y1 < *y2) {
      if (*x1 < 0 || *x1 > pic -> width || *y1 < 0 || *y1 > pic -> height) {
         printf ("Invalid set of coordinates\n");
      }
      else if (*x2 < 0 || *x2 > pic -> width || *y2 < 0 || *y2 > pic ->height) {
         printf ("Invalid set of coordinates\n");
      }
      else  {
         printf ("Selected %d %d %d %d\n", *x1, *y1, *x2, *y2);
         pic -> x1 = *x1;
         pic -> y1 = *y1;
         pic -> x2 = *x2;
         pic -> y2 = *y2;
      }
   }
   else if (*x1 > *x2 && *y1 > *y2) {
      if (*x2 < 0 || *x2 > pic -> width || *y2 < 0 || *y2 > pic -> height) {
         printf ("Invalid set of coordinates\n");
      }
      else if (*x1 < 0 || *x1 > pic -> width || *y1 < 0 || *y1 > pic ->height) {
         printf ("Invalid set of coordinates\n");
      }
      else {
         help = *x1;
         *x1 = *x2;
         *x2 = help;
         help = *y1;
         *y1 = *y2;
         *y2 = help;
         printf ("Selected %d %d %d %d\n", *x1, *y1, *x2, *y2);
         pic -> x1 = *x1;
         pic -> y1 = *y1;
         pic -> x2 = *x2;
         pic -> y2 = *y2;
      }
   }
   else if (*x1 < *x2 || *y1 > *y2) {
      if (*x1 < 0 || *x1 > pic -> width || *y2 < 0 || *y2 > pic -> height) {
         printf ("Invalid set of coordinates\n");
      }
      else if (*x2 < 0 || *x2 > pic -> width || *y1 < 0 || *y1 > pic -> height) {
         printf ("Invalid set of coordinates\n");
      }
      else if((*y1-*y2)!=0 &&(*x1-*x2)!=0) {
         help = *y1;
         *y1 = *y2;
         *y2 = help;
         printf ("Selected %d %d %d %d\n", *x1, *y1, *x2, *y2);
         pic -> x1 = *x1;
         pic -> y1 = *y1;
         pic -> x2 = *x2;
         pic -> y2 = *y2;
      }
       else
      {
         printf("Invalid set of coordinates\n");
      }
   }
   else if (*x1 > *x2 || *y1 < *y2) {
      if (*x2 < 0 || *x2 > pic -> width || *y1 < 0 || *y1 > pic -> height) {
         printf ("Invalid set of coordinates\n");
      }
      else if (*x1 < 0 || *x1 > pic -> width || *y2 < 0 || *y2 > pic -> height) {
         printf ("Invalid set of coordinates\n");
      }
      else if((*y1-*y2)!=0 &&(*x1-*x2)!=0){
         help = *x1;
         *x1 = *x2;
         *x2 = help;
         printf ("Selected %d %d %d %d\n", *x1, *y1, *x2, *y2);
         pic -> x1 = *x1;
         pic -> y1 = *y1;
         pic -> x2 = *x2;
         pic -> y2 = *y2;
      }
      else
      {
         printf("Invalid set of coordinates\n");
      }

   }
   else
   {
      printf ("Invalid set of coordinates\n");
   }
}

/* functie care selecteaza intreaga suprafata a unei imagini */
void select_all_image (struct image *pic) {

   int x_i = 0;
   int x_f = pic -> width;
   int y_i = 0;
   int y_f = pic -> height;
   printf("Selected ALL\n");
}
int main()
{
    printf("Hello world!\n");
    return 0;
}
