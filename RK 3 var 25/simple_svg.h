#ifndef SIMPLE_SVG_H
#define SIMPLE_SVG_H

#include <stdint.h>
#include <stdio.h>

// template <typename Type>
// typedef struct {
//     size_t size;
//     size_t capacity;
//     Type *mas;
// } vec<Type>;

typedef struct {
    uint16_t x,y;
} point;

typedef struct {
    point p[3];
} tre;

typedef struct {
    point p[2];
} seg;

typedef struct {
    size_t size;
    size_t capacity;
    tre *mas;
} tre_s;

typedef struct {
    size_t size;
    size_t capacity;
    seg *mas;
} seg_s;

template <typename mas_Type, typename Type>
mas_Type init();

template <typename mas_Type, typename Type>
int extend(mas_Type *vector, Type shape);

template <typename mas_Type>
void vector_free(mas_Type *vector);

FILE* open_gen_svg(const char *path, uint16_t *wh, uint8_t t, uint8_t g, const char* colour);

void gen_tre(FILE *f, uint8_t t, uint16_t wh, const char* colour);
void gen_seg(FILE *f, uint8_t g, uint16_t wh, const char* colour);

void read_svg(FILE *f, tre_s *triangles, seg_s *segments);

void Print_Tre(tre triangl);
void Print_Seg(seg segment);

void Print_Tre_s(tre_s *triangles);
void Print_Seg_s(seg_s *triangles);

void Get_P(point *p);
void Prunt_P(point p);
void write_p(FILE *f, point p, const char* colour);

#include "simple_svg.cpp" // gcc ?

#endif