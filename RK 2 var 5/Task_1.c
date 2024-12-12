#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// С помощью Текстового редактора создать текстовый файл, 
// каждая строка котрого состоит из слов,
// разделенных пробелами.
// Написать программу, которая определяет и выводит 
// на экран строку, в которой есть слово содержашее 
// самое наименынее количество гласных букв.

bool point(char p[]) {
    return 
    (p[1] == '.' || p[1] == '!' || p[1] == '?') &&
    (p[0] == ' ' || p[0] == '\n');
}

bool word(char p[]) {
    return 
    (65 <= p[1] && p[1] <= 122) && 
    (p[0] == ' ' || p[0] == '\n' || p[0] == '.' || p[0] == '!' || p[0] == '?');
}

int main() {

    FILE *f = fopen("Environment.txt", "r");
    if (f == NULL) {printf("\n No file\n"); return 1;}

    char buf[2] = {0};

    long int s_min, s = ftell(f);
    int w = 0, w_min_pred = 10000, w_min = 10000;

    printf("\n");

    while (!feof(f)) {
        buf[1] = buf[0];
        buf[0] = getc(f);
        printf("%c", buf[0]);

        if (strchr("euioaEUIOA", buf[0])) {
            w++;
        }
        if (point(buf) || feof(f)) {

            if (w_min_pred < w_min) {
                w_min = w_min_pred;
                s_min = s;
            }
            w_min_pred = 10000;
            s = ftell(f);
        }
        else if (word(buf)) {
            
            if (w < w_min_pred) {
                w_min_pred = w;
            }
            w = 0;
        }
    }

    printf("\n\n###### min: %i ######\n\n", w_min);

    fseek(f, s_min, SEEK_SET);

    do {
        buf[1] = buf[0];
        buf[0] = getc(f);
        printf("%c", buf[0]);

    } while (!point(buf) && !feof(f));
    printf("\n");

    fclose(f);
    return 0;
}