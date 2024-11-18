#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define lin 5
#define col lin
#define len lin*col

void rnd(int mas[], int lenn);
void num(int mas[], int lenn);
void fill(int mas[], int lenn, int f);

bool swap_m(int lines, int mas[][lines]);

void prt(int lines, int columns, int mas[][columns]);

int main() {
    int a[lin][col] = {0};

    srand(time(NULL));
    rnd((int *)a, len);
    // num((int *)a, len);
    // fill((int *)a, len, 5);

    prt(lin, col, a);

    if (!swap_m(lin, a)) {printf("  No k3\n"); return 0;}

    prt(lin, col, a);

    return 0;
}

bool swap_m(int lines, int mas[][lines]) {
    int* max_lines = NULL;
    for (int i=1; i<lines; i++) {
        for (int j=0; j<i; j++) {
            if (mas[i][j] % 3 == 0 && (max_lines == NULL || mas[i][j] > *max_lines)) {
                max_lines = &mas[i][j];
            }
        }
    }
    if (max_lines == NULL) return 0;

    int* max_columns = NULL;
    for (int j=1; j<lines; j++) {
        for (int i=0; i<j; i++) {
            if (mas[i][j] % 3 == 0 && (max_columns == NULL || mas[i][j] > *max_columns)) {
                max_columns = &mas[i][j];
            }
        }
    }
    if (max_columns == NULL) return 0;

    printf("%6d %6d\n", *max_lines, *max_columns);

    int buf = *max_lines;
    *max_lines = *max_columns;
    *max_columns = buf;

    return 1;
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

void fill(int mas[], int lenn, int f) {
    for (int i = 0; i < lenn; i++) {
        mas[i] = f;
    }
}