#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// в 2 мерноом int массиве удалить строки если ср < ср массива и есть число кратно 3

// (int) z преобразовать в int

#define l 20

void rnd (int mas[], int len);
void prt (int mas[], int len);
void scn (int mas[], int len);
float sr (int mas[], int len);
int remm (int mas[], int len, float sr);


int main () {
    int a[l];

    rnd(a, l);
    prt(a, l);

    float s = sr(a, l);

    printf("%f\n\n", s);


    prt(a, remm(a, l, s));

}



void rnd (int mas[], int len) {
    for (int i=0; i<len; i++) {
        mas[i] = (rand()%100)-50;
    }
}

void prt (int mas[], int len) {
    printf("\n");
    for (int i=0; i<len; i++) {
        printf("%i  ", mas[i]);
    }
    printf("\n\n");
}

void scn (int mas[], int len) {
    printf("\n");
    for (int i=0; i<len; i++) {
        scanf("%i", &mas[i]);
    }
    printf("\n\n");
}

float sr (int mas[], int len) {
    int summ = 0;
    for (int i=0; i<len; i++) {
        summ += mas[i];
    }
    return summ / (float) len;
}

int remm (int mas[], int len, float maxx) {
    int i_2 = 0;
    for (int i=0; i<len; i++) {
        if (!(mas[i] % 3 == 0 && mas[i] < maxx)) {
            mas[i_2] = mas[i];
            i_2++;
        }
    }
    return i_2;
}