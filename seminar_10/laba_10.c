#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

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
#define max_mark 10

typedef struct {
    char f_name[32];
    char l_name[32];
    char group[32];
    uint8_t Mark[marks];
} stud;

void FillStud(stud *student) {
    printf("\nФамилия: " );
    scanf( "%15s", student->l_name);
    printf("Имя: ");
    scanf("%15s", student->f_name);
    printf("Группа: ");
    scanf("%15s", student->group);

    for (int8_t i=0; i < marks; i++) {
        printf("Оценка %d : ",i+1);
        while (!(scanf("%d", &(student->Mark[i])) && student->Mark[i] >= 0  && student->Mark[i] <= max_mark))
            while (getchar() != 10);
    }
    printf("\n");
}

const char f_Names[][32] = {
    "Артем",
    "Виктория",
    "Илья",
    "Марина",
    "Дмитрий",
    "София",
    "Павел",
    "Анна",
    "Максим",
    "Ольга"
};
const char l_Names[][32] = {
    "Иванов",
    "Смирнова",
    "Петров",
    "Кузнецова",
    "Сидоров",
    "Лебедева",
    "Попов",
    "Волкова",
    "Михайлов",
    "Федорова"
};
const char Grups[][32] = {
    "ВТ6-15А",
    "ИТ4-09Б",
    "МК8-22Г",
    "ПГ3-11В",
    "АЛ5-16А",
    "ОР9-14Г",
    "РК2-10Д",
    "ЛМ7-18Б",
    "ТН6-13А",
    "СТ4-08В"
};

void FillRand(stud *student) {
    strcpy(student->l_name, l_Names[rand() % 10]);
    strcpy(student->f_name, f_Names[rand() % 10]);
    strcpy(student->group, Grups[rand() % 10]);

    for (int8_t i=0; i < marks; i++) {
        student->Mark[i] = rand() % (max_mark+1);
    }
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
    // system("chcp 65001"); // utf-8

    FILE *f = fopen("Base.dat", "rb+");
    if (f == NULL) {printf("\n No file\n"); return 1;}

    printf("\n read write del top gen exit\n\n");

    srand(time(NULL));

    char com[16];
    stud student;
    size_t i;
    size_t num_students;
    stud* students;

    while (1) {
        scanf("%15s", com);

        switch (adler32(com, strlen(com))) {        
            case 69271965 :    // Read
                fseek(f, 0, SEEK_SET);
                
                for (i=0; fread(&student, sizeof(stud), 1, f); i++) {
                    printf("\n %d", i);
                    PrntStud(&student);
                }
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
                num_students = ftell(f) / sizeof(stud);
                if (num_students < 2) {printf("\n No students\n\n"); break;}

                students = malloc(num_students * sizeof(stud));
                if (students == NULL) {printf("\n Overflowed\n\n"); break;}

                fseek(f, 0, SEEK_SET);
                fread(students, sizeof(stud), num_students, f);

                SortStud(students, num_students);

                fseek(f, 0, SEEK_SET);
                fwrite(students, sizeof(stud), num_students, f);

                for (i=0; i < 10 && i < num_students; i++) {
                    printf("\n %d", i);
                    PrntStud(&students[i]);
                }
                printf("\n");

                free(students);
            break;
            case 40173878 :    // Delete
                fseek(f, 0, SEEK_END);
                num_students = ftell(f) / sizeof(stud);
                if (num_students == 0) {printf("\n No students\n\n"); break;}

                printf("\n Enter the number: ");
                scanf("%zu", &i);
                if (i >= num_students) {printf("\n Student not found\n\n"); break;}
                fseek(f, i * sizeof(stud), SEEK_SET);
                fread(&student, sizeof(stud), 1, f);
                PrntStud(&student);

                printf("\n Delete a student? ");
                scanf("%15s", com);
                if (adler32(com, strlen(com)) != 44761426) {printf("\n Exit...\n\n"); break;}

                students = malloc(num_students * sizeof(stud));
                if (students == NULL) {printf("\n Overflowed\n\n"); break;}
                fseek(f, 0, SEEK_SET);
                fread(students, sizeof(stud), num_students, f);
                for (; i < num_students - 1; i++) {
                   students[i] = students[i+1];
                }
                f = freopen("Base.dat", "wb", f);
                if (f == NULL) {printf("\n Failed write\n"); free(students); return 1;}
                fwrite(students, sizeof(stud), num_students-1, f);
                free(students);

                f = freopen("Base.dat", "rb+", f);
                if (f == NULL) {printf("\n Failed write\n"); free(students); return 1;}
                printf("\n Deleted\n\n");
            break;
            case 40894779 :    // Generate
                printf("\n Enter the count: ");
                scanf("%zu", &num_students);
                students = malloc(num_students * sizeof(stud));
                if (students == NULL) {printf("\n Overflowed\n\n"); break;}

                for (i=0; i < num_students; i++) {
                    FillRand(&students[i]);
                }
                fseek(f, 0, SEEK_END);
                fwrite(students, sizeof(stud), num_students, f);

                free(students);
                printf("\n Generated\n\n");
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