#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

// Составить подпрограмму, определяющую записи:
// фамилия “ Иванов“, 
// адрес не содержит название города Тверь, 
// год рождения не позже 1970.

typedef struct {
    char fam[20];
    char adr[50];
    uint16_t year;

} human;

const char fams[][30] = {
    "Иванов",
    "Смирнова",
    "Петров",
    "Кузнецова",
    "Сидоров",
};
const char addresses[][50] = {
    "Тверь, ул. Тверская, 5",
    "Москва, ул. Ленина, 12",
    "Санкт-Петербург, пр. Мира, 34",
    "Новосибирск, пер. Чехова, 7",
    "Екатеринбург, пл. Победы, 3"
};

void FillRand(human *men) {
    strcpy(men->fam, fams[rand() % 5]);
    strcpy(men->adr, addresses[rand() % 5]);

    men->year = 1900 + (rand() % 120);
}

const char path[] = "people.dat";

uint16_t num_humans = 10;
human* humans;

void PrntMen(human men) {
    printf("\nФамилия: %s\n", men.fam);
    printf("Год: %i\n", men.year);
    printf("Адрес: %s\n", men.adr);
}

int main() {

    system("chcp 65001"); // utf-8

    FILE *f = fopen(path, "rb+");
    if (f != NULL) {

        fseek(f, 0, SEEK_END);
        num_humans = ftell(f) / sizeof(human);
        if (num_humans < 2) {printf("\n No humans\n\n"); return 1;}

        humans = malloc(num_humans * sizeof(human));
        if (humans == NULL) {printf("\n Overflowed\n\n"); return 2;}

        fseek(f, 0, SEEK_SET);
        fread(humans, sizeof(human), num_humans, f);
    } 
    else {
        f = fopen(path, "wb+");

        humans = malloc(num_humans * sizeof(human));

        srand(time(NULL));

        for (uint16_t i=0; i < num_humans; i++) {
            FillRand(&humans[i]);
        }
        strcpy(humans[3].fam,fams[0]);
        strcpy(humans[3].adr,addresses[0]);
        humans[3].year = 1800;
        // humans[3] = {fams[0], addresses[0], 1800};

        fwrite(humans, sizeof(human), num_humans, f);
    }
    fclose(f);
    
    for (uint16_t i=0; i < num_humans; i++) {
        PrntMen(humans[i]);
    }

    for (uint16_t i=0; i < num_humans; i++) {
        if (
            strstr(humans[i].fam,fams[0]) &&
            strstr(humans[3].adr,addresses[0]) &&
            humans[i].year < 1970
        ) {
            printf("\n######## %i ########\n", i);
            PrntMen(humans[i]);
        }
    }

    free(humans);
    return 0;
}