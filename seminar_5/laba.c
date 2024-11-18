#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int lin =  5;
int col =  10;

void rnd(int mas[], int lenn);
void num(int mas[], int lenn);

void prt(int lines, int columns, int mas[][columns]);

void rem(int mas[], int lines, int *columns, int del_col);

int main() {
    int a[lin][col];

    // srand(time(NULL));
    // rnd((int *)a, len);
    num((int *)a, lin*col);

    prt(lin, col, a);

    rem((int *)a, lin, &col, 6);

    // prt(lin, col-1, a);

    // rem((int *)a, lin, col-1, 5);

    // prt(lin, col-2, a);

    // rem((int *)a, lin, col-2, 2);

    prt(lin, col, a);

    return 0;
}

void rem(int mas[], int lines, int* columns, int del_col) {
    const int lenn = lines* (*columns);
    for (int i = lenn - (*columns) + del_col; i >= 0; i-=(*columns)) {
            for (int j = i; j < lenn-1; j++) {
                mas[j] = mas[j+1];
            }
    }
    *columns = *columns-1;
}

void prt(int lines, int columns, int mas[][columns]) {
    printf("\n");
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%6d", mas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void rnd(int mas[], int lenn) {
    for (int i = 0; i < lenn; i++) {
        mas[i] = (rand() % 100) - 50;
    }
}

void num(int mas[], int lenn) {
    for (int i = 0; i < lenn; i++) {
        mas[i] = i;
    }
}