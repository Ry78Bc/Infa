#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// найти предложение с самым большим количеством слов

#define len 1000

// ' ' - символ 33 (пробел)
// "asd" - строка 'a' 's' 'd' 0 (символы и символ конца строки)

int main() {

    char s[len];

    // ../ - папка назад

    FILE *f = fopen("../White Fung/1.txt", "r");
    if (f == NULL) {
        print("no file\n");
    }

    int i;
    while (!feof(f)) {
        // fscanf(f, "%s", s);
        fgets(s, 50, f);
        printf("%d : %s\n", i, s);
        i++;

    }

    fclose(f);

    printf("\n%s\n", s);

    return 0;
}

