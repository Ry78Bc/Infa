#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define line 5
#define column 10
#define len line*column

// gcc laba.c -o laba.exe

void rnd (int mas[], int lenn);
void prt (int* mas_line, int lines, int columns);
float sr (int mas[], int lenn);
int remm (int mas[], int lines, int columns, float minn);

int main () {
    int a[line][column];

    // srand(time(NULL));

    rnd((int *) a, len);
    prt((int *) a, line, column);

    a[2][3] = 0;

    prt((int *) a, line, column-3);

    int new_columns = remm((int *) a, line, column, sr((int *) a, len));
    
    prt((int *) a, line, new_columns);

    return 0;
}

int remm (int mas[], int lines, int columns, float minn) {
    printf("\n");
    int i_new = 0;
    for (int i = 0; i < columns; i++) {
        int summ = 0;
        bool k = false;
        for (int j = 0; j < lines; j++) {
            summ += mas[j * columns + i];
            if (!k && mas[j * columns + i] % 3 == 0) {
                k = true;
            }
        }
        float srr = (float) summ / lines;
        printf("%6g", srr);

        if (!(k && srr < minn)) {
            for (int j = 0; j < lines; j++) {
                mas[j * columns + i_new] = mas[j * columns + i];
            }
            i_new++;
        }
    }
    printf("\n\n%6g\n", minn);
    return i_new;
}

void prt (int* mas_line, int lines, int columns) {
    printf("\n");
    for(int i = 0; i < lines; i++, mas_line++){
        for(int j = 0; j < columns; j++){
            printf("%6d", mas_line[j]);
        }
        printf("\n");
    }
}

float sr (int mas[], int lenn) {
    float summ = 0;
    for (int i = 0; i < lenn; i++) {
        summ += mas[i];
    }
    return summ / lenn;
}

void rnd (int mas[], int lenn) {
    for (int i = 0; i < lenn; i++) {
        mas[i] = (rand() % 100) - 50;
    }
}
