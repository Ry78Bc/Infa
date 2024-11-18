#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// найти предложение с max количеством слов

int main() {

    printf("\n");

    FILE *f = fopen("text.txt", "r");
    if (f == NULL) {
        printf(" No file\n");
        return 0;
    }

    char s[100];

    int l = 1, l_max = 0;
    long int w, w_max;
    bool end = 0;
    while (!feof(f)) {
        
        fscanf(f, "%s", s);
        // fgets(s, 100, f);

        if (end) {w = ftell(f);}

        end = strchr(".!?",*(strchr(s,0)-1));
        if (end && l_max < l) {
            l_max = l;
            l = 1;
            w_max = w;
        }
        
        printf(" %10s  %c  %c  %2i  %i\n", s, *(strchr(s,0)-1), 78+(end*11), l, l_max);
        // *(&s+strlen(s))
        l++;

    }

    fseek(f, 0, w_max);
    fscanf(f, "%s", s);

    printf("\n max: %s %i\n", s, l_max);

    fclose(f);

    return 0;
}