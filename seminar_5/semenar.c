#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define lin 5
#define col 10
#define len lin*col

void rnd(int mas[], int lenn);
float sr(int mas[], int lenn);

void prt(int mas[][col], int lines, int columns);

int rem(int mas[][col], int lines, int columns, float min);

int main() {
    int a[lin][col];

    // srand(time(NULL));
    rnd((int *)a, len);

    prt(a, lin, col);



    return 0;
}

int rem(int mas[][col], int lines, int columns, float min) {

}

void prt(int mas[][col], int lines, int columns) {
    printf("\n");
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%6d", mas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

float sr(int mas[], int lenn) {
    float summ = 0;
    for (int i = 0; i < lenn; i++) {
        summ += mas[i];
    }
    return summ / lenn;
}

void rnd(int mas[], int lenn) {
    for (int i = 0; i < lenn; i++) {
        mas[i] = (rand() % 100) - 50;
    }
}
