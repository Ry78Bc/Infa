#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

uint32_t adler32(const void *buf, size_t buflength) {
    const uint8_t *buffer = (const uint8_t*)buf;

    uint32_t s1 = 1;
    uint32_t s2 = 0;

    for (size_t n = 0; n < buflength; n++) {
        s1 = (s1 + buffer[n]) % 65521;
        s2 = (s2 + s1) % 65521;
    }     
    return (s2 << 16) | s1;
}

#define marks 3

typedef struct {
    char f_name[16];
    char l_name[16];
    char group[16];
    uint8_t Mark[marks];
} stud;

void FillStud(stud *student) {
    printf("\nФамилия: " );
    scanf( "%s", student->l_name);
    printf("Имя: ");
    scanf("%s", student->f_name);
    printf("Группа: ");
    scanf("%s", student->group);

    for (int8_t i=0; i<marks; i++) {
        printf("Оценка %d : ",i+1);
        while (!(scanf("%d", &(student->Mark[i])) && student->Mark[i] >= 0  && student->Mark[i] <= 10))
            while (getchar() != 10);
    }
    printf("\n");
}

void PrntStud(stud *student) {
    printf("\nФамилия: %s\n", student->l_name);
    printf("Имя: %s\n", student->f_name);
    printf("Группа: %s\n", student->group);
    
    for (int8_t i=0; i<marks; i++)
        printf("  %d", student->Mark[i]);
    printf("\n");
}

uint8_t SumStud(stud *student) {
    uint8_t sum = 0;
    for (int8_t i=0; i < marks; i++)
        sum += student->Mark[i];
    return sum;
}

void SortStud(stud *students, size_t num_students) {
    for (size_t i=0; i < num_students-1; i++) {
        for (size_t j=0; j < num_students - i-1; j++) {
            if (SumStud(&students[j]) < SumStud(&students[j+1])) {
                stud temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }
}

int main() {
    system("chcp 65001"); // utf-8

    FILE *f = fopen("Base.dat", "rb+");
    if (f == NULL) {printf("\n No file\n"); return 1;}

    printf("\n read write find del top exit\n\n");

    char com[16];
    stud student;

    while (1) {
        scanf("%s", com);

        switch (adler32(com, strlen(com))) {        
            case 69271965 :    // Read
                fseek(f, 0, SEEK_SET);

                while (fread(&student, sizeof(stud), 1, f))
                    PrntStud(&student);
                printf("\n");
            break;
            case 111673900 :    // Write
                fseek(f, 0, SEEK_END);
                do {
                    FillStud(&student);
                    fwrite(&student, sizeof(stud), 1, f);
                    printf(" Enter for resume: ");
                    while (getchar() != 10);

                } while (getchar() == 10);

                while (getchar() != 10);

                printf("\n Exit...\n\n");
            break;
            case 44892500 :    // Top
                fseek(f, 0, SEEK_END);
                size_t num_students = ftell(f) / sizeof(stud);
                if (num_students < 2) {printf("\n No students\n\n"); break;}

                stud *students = malloc(num_students * sizeof(stud));
                if (students == NULL) {printf("\n Overflowed\n\n"); break;}

                fseek(f, 0, SEEK_SET);
                fread(students, sizeof(stud), num_students, f);

                SortStud(students, num_students);

                fseek(f, 0, SEEK_SET);
                fwrite(students, sizeof(stud), num_students, f);

                for (int8_t i=0; i < 10 && i < num_students; i++)
                    PrntStud(&students[i]);
                printf("\n");

                free(students);
            break;
            case 68616610 :    // Find

            break;
            case 40173878 :    // Delite

            break;
            case 71696827 :    // Exit
                fclose(f);
                return 0;
            break;
            default:
                // printf("\n Unknown command\n\n");
                printf("\n %i\n\n", adler32(com, strlen(com)));
            break;
        
        }
    }
}