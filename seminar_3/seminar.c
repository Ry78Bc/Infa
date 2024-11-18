#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// через указатель вычислить max среди кратных 5 в int массиве

#define l 10

void rnd (int mas[], int len);
void prt (int mas[], int len);
void scn (int mas[], int len);
bool maxx (int mas[], int len);

int *m;

int main() {
    int a[l];

    // scn(a, l);
    rnd(a, l);
    prt(a, l);

    if (maxx(a, l)) {
        printf("%i    %p\n\n", *m, m);
    }
    else {
        printf("No multiples of five values\n\n");
    }

    return 0;
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

bool maxx (int mas[], int len) {
    bool b = 0;
    for (int i=0; i<len; i++) {
        if (mas[i] % 5 == 0 && (!b || mas[i] > *m)) {
            b++;
            m = &mas[i];
        }
    }
    return b;
}
