#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "simple_svg.h"

float S_Tre(tre triangle) {
    float x1 = triangle.p[0].x, y1 = triangle.p[0].y;
    float x2 = triangle.p[1].x, y2 = triangle.p[1].y;
    float x3 = triangle.p[2].x, y3 = triangle.p[2].y;

    return fabs(0.5 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));
}

bool P_in_Tre(tre triangle, point p) {
    float total_area = S_Tre(triangle);

    float area1 = S_Tre({triangle.p[0], triangle.p[1], p});
    float area2 = S_Tre({triangle.p[1], triangle.p[2], p});
    float area3 = S_Tre({triangle.p[2], triangle.p[0], p});

    return (area1 + area2 + area3) <= total_area;
}

float Len_Seg(seg segment) {
    uint16_t x1 = segment.p[0].x;
    uint16_t y1 = segment.p[0].y;
    uint16_t x2 = segment.p[1].x;
    uint16_t y2 = segment.p[1].y;

    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

bool Seg_in_Tre(seg segment, tre triangle) {

    uint16_t num_points = (Len_Seg(segment) / 10) + 2;

    for (uint16_t i = 0; i <= num_points; i++) {

        float t = (float)i / num_points;
        point p_on_seg = {
            (uint16_t)(segment.p[0].x + t * (segment.p[1].x - segment.p[0].x)),
            (uint16_t)(segment.p[0].y + t * (segment.p[1].y - segment.p[0].y))
        };

        if (P_in_Tre(triangle, p_on_seg)) {
            return true;
        }
    }

    return false;
}

// Входные данные:
//     • задана точка координаты вводятся с клавиатуры;
//     • segments.txt — текстовый файл с координатами концов отрезков на плоскости.
//     • treangles.txt — текстовый файл с координатами вершин треугольниковна плоскости.

// Задание:
// найти треугольник максимальной площали, содержалиий точку и хотя бы один отрезок.

tre_s triangles = init<tre_s, tre>();
seg_s segments = init<seg_s, seg>();

uint16_t wh = 700;

int main() {
    system("chcp 65001"); // utf-8

    FILE *f = open_gen_svg("./visual.svg", &wh, 0, 0, "white");

    read_svg(f, &triangles, &segments);

    Print_Tre_s(&triangles);
    Print_Seg_s(&segments);

    point p1;
    // Get_P(&p1);
    // Prunt_P(p1);
    // write_p(f, p1, "white");

    #define abrakadabra
    write_seg(f, seg {50,50,500,500}, "white");
    write_tre(f, tre {100,200,400,200,100,500}, "white");
    write_circ(f, circ {300,300,100}, "white");


    float S_max = 0;
    tre *t1;
    for (uint8_t i=0; i < triangles.size; i++) {
        if (P_in_Tre(triangles.mas[i], p1)) {

            for (uint8_t j=0; j < triangles.size; j++) {
                if (Seg_in_Tre(segments.mas[j], triangles.mas[j])) {

                    float S = S_Tre(triangles.mas[i]);
                    if (S > S_max) {
                        S_max = S;
                        t1 = &triangles.mas[i];
                    }
                }
            }
        }
    }

    if (S_max != 0) {
        printf("\n######## S_max: %.0f ########\n", S_max);
        Print_Tre(*t1);
    }
    else {
        printf("\n Triangle was not found\n");
    }
    vector_free(&segments);
    vector_free(&triangles);

    fclose(f);
    // system("viewer.html");
    return 0;
}