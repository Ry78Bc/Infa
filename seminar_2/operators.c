  // sizeof()
  // & адрес
  // * обращение по адресу 

  // j = i++; // j = i     i++
  // j = ++i; // j = i+1   i++
  // i += 4;
  // j = i++, k++; // j = k  j++  k++
  // int a[100]; // статический массив
  // rand();
  // c(int) преобразовать с в int

/*
найти:
сумму
произведение
сумму кратных 7
макс
макс кратных 7
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

# define n 15

int main() {

  int a[n];
  for (int i = 0; i < n; i++) {
    a[i] = (rand()%100)*2-11;
    printf("   %i", a[i]);

  }

  long sum = 0, pro = 1, max = a[0], sumk = 0, maxk = 0;

  int maxkin;

  bool f = 0;

  for (int i = 0; i < n; i++) {
    sum += a[i];
    pro *= a[i];

    if (a[i] > max)
      max = a[i];

    if (a[i] % 2 == 0) {
      f++;
      sumk += a[i];

      if (a[i] > maxk || maxk == 0) {
        maxk = a[i];
        maxkin = i;
      }
      
    }
  }
  
  printf("\n\nsum = %li\n", sum);
  printf("proizv = %li\n", pro);
  printf("max = %li\n", max);
  if (f) {
    printf("sum krat = %li\n", sumk);
    printf("max krat = %li\n", maxk);
    printf("max krat index = %li\n", maxkin);
  }
  else {
    printf("No even values\n");
  }
  scanf("");

  return 0;
}
