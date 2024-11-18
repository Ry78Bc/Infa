#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// найти предложение с max количеством слов

bool point(char p[]) {
    return 
    (p[0] == ' ' || p[0] == '\n') && 
    (p[1] == '.' || p[1] == '!' || p[1] == '?');
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

    long int s_max, s = ftell(f);
    int w = 0, w_max = 0;

    printf("\n");

    while (!feof(f)) {
        buf[1] = buf[0];
        buf[0] = getc(f);
        printf("%c", buf[0]);

        if (word(buf) || feof(f)) {
            w++;
        }
        if (point(buf) || feof(f)) {
            
            if (w > w_max) {
                w_max = w;
                s_max = s;
            }
            w = 0;
            s = ftell(f);
        }
    }
    if (!w_max) {printf(" No sentence\n"); return 2;}

    printf("\n\n###### max: %i ######\n\n", w_max);

    fseek(f, s_max, SEEK_SET);

    do {
        buf[1] = buf[0];
        buf[0] = getc(f);
        printf("%c", buf[0]);

    } while (!point(buf) && !feof(f));

    printf("\n");

    fclose(f);

    return 0;
}