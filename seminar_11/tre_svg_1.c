#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

typedef struct {
    uint16_t  x,y;
} Point;

typedef struct {
    Point A,B,C;
} Treangle;

void AddRand(Treangle *trr, uint16_t wh) {

    trr->A.x = rand() % wh;
    trr->A.y = rand() % wh;
    trr->B.x = rand() % wh;
    trr->B.y = rand() % wh;
    trr->C.x = rand() % wh;
    trr->C.y = rand() % wh;
}

void WriteTre(Treangle trr, FILE *f) {

    fseek(f, -8, SEEK_END);

    const char st[] = 
    "\n    <polygon\n\
        points=\"%i,%i %i,%i %i,%i\"\n\
        fill=\"none\"\n\
        stroke=\"white\"\n\
        stroke-width=\"3\"\n\
    />\n\n\
</svg>";

    fprintf(f,st,
        trr.A.x, trr.A.y,
        trr.B.x, trr.B.y,
        trr.C.x, trr.C.y
    );
}

void ReadTre(Treangle trr[], FILE *f) {

    fseek(f, 0, SEEK_SET);

    char s[50];
    uint16_t  i = 0;
    while (fgets(s, sizeof(s), f)) {

        if (strstr(s, "points")) {
            
            sscanf(s, " points=\"%i,%i %i,%i %i,%i\"\n",
                &trr[i].A.x, &trr[i].A.y,
                &trr[i].B.x, &trr[i].B.y,
                &trr[i].C.x, &trr[i].C.y
            );
            i++;
        }

    }
}

void PrintTre(Treangle trr) {

    const char stt[] = 
"\n A: %i %i\n\
 B: %i %i\n\
 C: %i %i\n";

    printf(stt,
        trr.A.x, trr.A.y,
        trr.B.x, trr.B.y,
        trr.C.x, trr.C.y
    );
}

const char path[] = "Treangles.svg";

uint16_t wh = 200;

int main() {

    FILE *f = fopen(path, "r+");
    if (f != NULL) {
        fscanf(f, "<svg width=\"%i\"", &wh);
    } 
    else {
        f = fopen(path, "w+");

        fprintf(f,"<svg width=\"%i\" height=\"%i\" xmlns=\"http://www.w3.org/2000/svg\">\n\n</svg>", wh, wh);
    }

    srand(time(NULL));

    Treangle tr[10] = {0};

    for (uint8_t i=0; i < 5; i++) {

        AddRand(&tr[0], wh);

        WriteTre(tr[0], f);
    }

    ReadTre(tr, f);

    for (uint8_t  i=0; i < 5; i++) {

        PrintTre(tr[1]);
    }

    fclose(f);
    return 0;
}