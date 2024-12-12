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

typedef struct {
    size_t size;
    size_t capacity;
    Treangle* treangles;
} Mesh;

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

    const char *st = 
    "\n    <polygon\n\
        points=\"%i,%i %i,%i %i,%i\"\n\
        fill=\"none\"\n\
        stroke=\"white\"\n\
        stroke-width=\"3\"\n\
    />\n\n\
</svg>";

    fprintf(f, st,
        trr.A.x, trr.A.y,
        trr.B.x, trr.B.y,
        trr.C.x, trr.C.y
    );
}

int mesh_expand(Mesh* mesh, Treangle treangle);

void ReadTre(Mesh *mesh, FILE *f) {

    fseek(f, 0, SEEK_SET);

    char s[50];
    while (fgets(s, sizeof(s), f)) {

        if (strstr(s, "points")) {
            
            Treangle trr;
            sscanf(s, " points=\"%i,%i %i,%i %i,%i\"\n",
                &trr.A.x, &trr.A.y,
                &trr.B.x, &trr.B.y,
                &trr.C.x, &trr.C.y
            );
            mesh_expand(mesh, trr);
        }
    }
}

void PrintTre(Treangle trr) {

    const char *stt = 
"\n A: %i %i\n\
 B: %i %i\n\
 C: %i %i\n";

    printf(stt,
        trr.A.x, trr.A.y,
        trr.B.x, trr.B.y,
        trr.C.x, trr.C.y
    );
}

Mesh mesh_init() {
    Mesh mesh;
    mesh.size = 0;
    mesh.capacity = 8;

    mesh.treangles = malloc(sizeof(*mesh.treangles) * mesh.capacity);
    if (mesh.treangles == NULL) {
        mesh.capacity = 0;
    }
    
    return mesh;
}

void mesh_free(Mesh *mesh) {
    if (mesh == NULL) {
        return;
    }
    mesh->size = 0;
    mesh->capacity = 0;

    free(mesh->treangles);
}

int mesh_expand(Mesh* mesh, Treangle treangle) {
    if (mesh == NULL && mesh->capacity > 0) {
        return -1;
    }

    if (mesh->size >= mesh->capacity) {
        Treangle *buf = realloc(mesh->treangles, mesh->capacity * 2 * sizeof(Treangle));

        if (buf == NULL) {
            return -1;
        }
        
        mesh->capacity *= 2;
        mesh->treangles = buf;
    }

    mesh->treangles[mesh->size] = treangle;
    mesh->size++;
    
    return 0;
}

const char* path = "Treangles.svg";

uint16_t wh = 200;

int main() {

    FILE *f = fopen(path, "r+");
    if (f != NULL) {

        fscanf(f, "<svg width=\"%i\"", &wh);
    } 
    else {
        f = fopen(path, "w+");

        fprintf(f,"<svg width=\"%i\" height=\"%i\"\
 xmlns=\"http://www.w3.org/2000/svg\">\n\n</svg>", wh, wh);
    }

    srand(time(NULL));  

    Mesh mesh = mesh_init();

    for (uint8_t i=0; i < 10; i++) {
        Treangle tr;
        AddRand(&tr, wh);
        WriteTre(tr, f);
    }

    ReadTre(&mesh, f);

    for (uint8_t  i=0; i < mesh.size; i++) {

        PrintTre(mesh.treangles[i]);
    }

    mesh_free(&mesh);
    fclose(f);
    return 0;
}
