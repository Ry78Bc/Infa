#include <stdio.h>
#include <stdlib.h>
// #include <conio.h>
#include <math.h>

int main(int argc, char *argv[]) {
   // printf("A: %d\n",argc);
   // for (int i = 0; i < argc; i++) {
   //   printf("%s\n", argv[i]);
   // }

   float a,b,c;

   if (argc != 1) {
      a = atof(argv[1]);
      b = atof(argv[2]);
      c = atof(argv[3]);

      printf("\n");
      printf("A: %g\n",a);
      printf("B: %g\n",b);
      printf("C: %g\n",c);
      printf("\n");
   }
   else {
      printf(" Enter the arguments\n\n");

      printf("A: ");
      scanf("%f", &a);
      printf("B: ");
      scanf("%f", &b);
      printf("C: ");
      scanf("%f", &c);
      printf("\n");
   }

   char* B;
   char* C;

   if (b > 0)  B = "+";  else  B = ""; 
   if (c > 0)  C = "+";  else  C = "";

   printf("%gx^2 %s%gx %s%g = 0\n\n", a,B,b,C,c);

   float d = pow(b,2) - 4*a*c;
   // printf("D = %g\n", d);

   float x1=0, x2=0;

   if (d < 0) {
      printf("x  is not in  R\n");
   }
   else if (d == 0) {
      x1 = -0.5*b/a;
      printf("x = %g\n", x1);
   }
   else {
      x1 = (-b-sqrt(d))/(2*a);
      x2 = (-b+sqrt(d))/(2*a);
      printf("x = %g  x = %g\n", x1, x2);
   }

   printf("\n");
   
   // return x1+x2;
   return 0;

   // if ((argc != 1) || (getch() != 13)) break;
}