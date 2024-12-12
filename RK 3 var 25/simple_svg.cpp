#include "simple_svg.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

FILE* open_gen_svg(const char* path, uint16_t *wh, uint8_t t, uint8_t g, const char* colour) {

    FILE *f = fopen(path, "r+");
    if (f != NULL) {
        fscanf(f, "<svg width=\"%i\"", wh);
    }
    else {
        f = fopen(path, "w+");

        fprintf(f, "<svg width=\"%i\" height=\"%i\"\
 xmlns=\"http://www.w3.org/2000/svg\">\n", *wh, *wh);

        srand(time(NULL));

        gen_tre(f, t, *wh, colour);
        gen_seg(f, g, *wh, colour);

        fprintf(f, "\n</svg>");
    }
    return f;
}

uint16_t gen(uint8_t *last, uint16_t wh, uint16_t *y) {

    uint8_t quarter;
    do {
        quarter = rand() % 4;
    } while (quarter == *last);

    *last = quarter;
    uint16_t wh_q = (wh / 2);

    switch (quarter) {
        case 0:
            *y = rand() % wh_q;
            return rand() % wh_q;
        break;
        case 1:
            *y = wh_q + rand() % wh_q;
            return rand() % wh_q;
        break;
        case 2:
            *y = rand() % wh_q;
            return wh_q + rand() % wh_q;
        break;
        case 3:
            *y = wh_q + rand() % wh_q;
            return wh_q + rand() % wh_q;
        break;
        default:
            *y = 0;
            return 0;
        break;
    }
}

void gen_tre(FILE *f, uint8_t t, uint16_t wh, const char* colour) {

    const char* pol = 
    "\n    <polygon\n\
        points=\"%i,%i %i,%i %i,%i\"\n\
        fill=\"none\"\n\
        stroke=\"%s\"\n\
        stroke-width=\"3\"\n\
    />\n";

    uint8_t last = 5;
    uint16_t y = 0;

    for (uint8_t i=0; i < t; i++) {
        fprintf(f, pol,
            gen(&last, wh, &y), y,
            gen(&last, wh, &y), y,
            gen(&last, wh, &y), y,
            colour
        );
    }
}

void gen_seg(FILE *f, uint8_t g, uint16_t wh, const char* colour) {
    
    const char* pol = 
    "\n    <polygon\n\
        points=\"%i,%i %i,%i\"\n\
        stroke=\"%s\"\n\
        stroke-width=\"3\"\n\
    />\n";

    uint8_t last = 5;
    uint16_t y = 0;

    for (uint8_t i=0; i < g; i++) {
        fprintf(f, pol,
            gen(&last, wh, &y), y,
            gen(&last, wh, &y), y,
            colour
        );
    }
}

void read_svg(FILE *f, tre_s *triangles, seg_s *segments) {
    
    fseek(f, 0, SEEK_SET);

    char s[50];
    while (fgets(s, sizeof(s), f)) {

        if (strstr(s, "points")) {
            
            uint16_t buf[6];
            if (6 == sscanf(s, " points=\"%i,%i %i,%i %i,%i\"\n",
                &buf[0], &buf[1],
                &buf[2], &buf[3],
                &buf[4], &buf[5]
            )) {
                extend(triangles, tre {buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]});
            }
            else {
                extend(segments, seg {buf[0], buf[1], buf[2], buf[3]});
            }
        }
    }
}

void Print_Tre(tre triangl) {

    const char *pol = 
"\n A: %3i %3i\n\
 B: %3i %3i\n\
 C: %3i %3i\n";

    printf(pol,
        triangl.p[0].x, triangl.p[0].y,
        triangl.p[1].x, triangl.p[1].y,
        triangl.p[2].x, triangl.p[2].y
    );
}

void Print_Tre_s(tre_s *triangles) {

    for (uint8_t i=0; i < triangles->size; i++) {
        Print_Tre(triangles->mas[i]);
    }
}

void Print_Seg(seg segment) {

    const char *pol = 
"\n A: %3i %3i\n\
 B: %3i %3i\n";

    printf(pol,
        segment.p[0].x, segment.p[0].y,
        segment.p[1].x, segment.p[1].y
    );
}

void Print_Seg_s(seg_s *segments) {

    for (uint8_t i=0; i < segments->size; i++) {
        Print_Seg(segments->mas[i]);
    }
}

void Get_P(point *p) {

    printf("\n Point: ");
    scanf("%i %i", &(p->x), &(p->y));

    // uint16_t buf[2];
    // scanf("%i %i", &buf[0], &buf[1]);
    // p->x = buf[0];
    // p->y = buf[1];

}

void Prunt_P(point p) {

    printf("\n %i %i\n", p.x, p.y);
}

void write_p(FILE *f, point p, const char* colour) { // не пишет ):

    const char* circ = 
 "\n    <circle cx=\"%i\" cy=\"%i\" r=\"3\" fill=\"%s\" />\n\n\
    </svg>";

    fseek(f, -8, SEEK_END);

    fprintf(f, circ, p.x, p.y, colour);
}