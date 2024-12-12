#ifndef SIMPLE_SVG_H
#define SIMPLE_SVG_H

#include <stdint.h>
#include <stdio.h>

// template <typename Type>
// struct vec2 {
//     size_t size;
//     size_t capacity;
//     Type *mas;
// };

// template <typename Type>
// using Vec = struct vec2<Type>;


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
    point p;
    uint16_t r;
} circ;

typedef struct {
    size_t size;
    size_t capacity;
    circ *mas;
} circles;

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
mas_Type init() {
    mas_Type vector;
    vector.size = 0;
    vector.capacity = 8;

    vector.mas = (Type*) malloc(sizeof(*vector.mas) * vector.capacity);
    if (vector.mas == NULL) {
        vector.capacity = 0;
    }
    
    return vector;
}

template <typename mas_Type, typename Type>
int extend(mas_Type *vector, Type shape) {
    if (vector == NULL && vector->capacity > 0) {
        return -1;
    }

    if (vector->size >= vector->capacity) {
        Type *buf = (Type*) realloc(vector->mas, vector->capacity * 2 * sizeof(Type));

        if (buf == NULL) {
            return -2;
        }
        
        vector->capacity *= 2;
        vector->mas = buf;
    }

    vector->mas[vector->size] = shape;
    vector->size++;
    
    return 0;
}

template <typename mas_Type>
void vector_free(mas_Type *vector) {
    if (vector == NULL) {
        return;
    }
    vector->size = 0;
    vector->capacity = 0;

    free(vector->mas);
}

FILE* open_gen_svg(const char *path, uint16_t *wh, uint8_t t, uint8_t g, const char* colour);

void read_svg(FILE *f, tre_s *triangles, seg_s *segments);

void write_seg(FILE *f, seg segment, const char* colour);
void write_tre(FILE *f, tre triangle, const char* colour);
void write_circ(FILE *f, circ circle, const char* colour);

void Print_Tre(tre triangle);
void Print_Seg(seg segment);

void Print_Tre_s(tre_s *triangles);
void Print_Seg_s(seg_s *triangles);

void Get_P(point *p);
void Prunt_P(point p);
void write_p(FILE *f, point p, const char* colour);

#endif