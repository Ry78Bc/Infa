#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define lin 5
#define col 10
#define len lin*col

void rnd(int mas[], int lenn);
void num(int mas[], int lenn);
float sr(int mas[], int lenn);

void prt(int lines, int columns, int mas[][columns]);

void rem(int mas[], int lines, int columns, int del_col);

int main() {
    int a[lin][col];

    // srand(time(NULL));
    rnd((int *)a, len);
    // num((int *)a, len);

    prt(lin, col, a);

    float srr = sr((int *)a, len);

    bool d[col] = {0};

    for (int j = 0; j < col; j++) {
        float sum = 0;
        bool k3 = false;

        for (int i = 0; i < lin; i++) {
            sum += a[i][j];
            if (!k3 && a[i][j] % 3 == 0) {
                k3 = true;
            }
        }
        float avg = sum / lin;
        printf("%6g", avg);

        if (k3 && (avg < srr)) {
            d[j] = true;
        }
    }
    printf("\n\n%6g\n", srr);

    int dc = 0;
    for (int i = col-1; i >= 0; i--) {
        if (d[i]) {
            rem((int *)a, lin, col-dc, i);
            dc++;
        }
    }

    prt(lin, col-dc, a);

    return 0;
}

void rem(int mas[], int lines, int columns, int del_col) {
    const int lenn = lines*columns;
    for (int i = lenn - columns + del_col; i >= 0; i-=columns) {
            for (int j = i; j < lenn-1; j++) {
                mas[j] = mas[j+1];
            }
    }
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

void num(int mas[], int lenn) {
    for (int i = 0; i < lenn; i++) {
        mas[i] = i;
    }
}