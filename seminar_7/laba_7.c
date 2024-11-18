#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

//в строке найти самое длинное слово с буквой A и замен на ***

#define len 50  

void censor(char* str);

int main() {
    setlocale(LC_ALL, "Rus");

    char s[len];
    printf("\n");
    if(!gets_s(s, len)) {printf("\nToo match"); return 0;}
    if(!strchr(s,'a')) {printf("\nNo a"); return 0;}

    censor(&s[0]);

    printf("\n%s\n", s);

    return 0;
}

void censor(char* str) {
    char* w = str;
    char* w_max;
    int len_max = 0;
    bool a = 0;

    for(char* i=str; i <= strchr(str,0); i++) {
        if(*i == 'a') a++;

        if(*i == ' ' || *i == 0) {
            if(a && len_max < i - w) {
                len_max = i - w;
                w_max = w;
            }
            a--;
            w = i+1;
        }
    }

    for(char* j=w_max; j < w_max+len_max; j++) {
        *j = '*';
    }
}