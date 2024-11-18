#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define lin 10
#define col 3
#define len lin*col

void rnd(int mas[], int lenn);
void num(int mas[], int lenn);

void num_snake(int lines, int columns, int mas[][columns]);

void num_speral(int lines, int columns, int mas[][columns]);

void prt(int lines, int columns, int mas[][columns]);

int main() {
    int a[lin][col] = {0};

    // srand(time(NULL));
    // rnd((int *)a, len);
    // num((int *)a, len);

    num_speral(lin, col, a);

    prt(lin, col, a);

    return 0;
}

void num_speral(int lines, int columns, int mas[][columns]) {
    int i = 0, j = 0, n = 0, m, b = 0;
    if (lines < columns) {m = lines;} else {m = columns;}
    for (int l = 0; l < m; l++) {
        if (l % 2 == 0) {
            for (; j < (columns-b); j++) {
                mas[i][j] = ++n;
            }
            j--;
            printf("> %4d  %4d\n",i,j);

            for (i++; i < (lines-b); i++) {
                mas[i][j] = ++n;
            }
            i--;
            printf("v %4d  %4d\n",i,j);
        }
        else {
            for (j--; j >= b; j--) {
                mas[i][j] = ++n;
            }
            j++;
            printf("< %4d  %4d\n",i,j);
            b++;

            for (i--; i >= b; i--) {
                mas[i][j] = ++n;
            }
            i++;
            printf("^ %4d  %4d\n\n",i,j);
            j++;
        }
    }
}

void num_snake(int lines, int columns, int mas[][columns]) {
    int i = 0, n = 0;
    for (int j = 0; j < columns; j++) {
        if (j % 2 == 0) {
            printf("%6d\n",i);
            for (; i < lines; i++) {
                mas[i][j] = ++n;
            }
        }
        else {
            printf("%6d\n",i);
            for (i--; i >= 0; i--) {
                mas[i][j] = ++n;
            }
            i++;
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