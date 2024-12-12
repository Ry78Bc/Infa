#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

/*******************

strstr( "eerewqrqwer wqrwerwe wew", "wer" );

***********************/
int main() {

    for(int c=128; c<256; c++ ){
        printf( "%c[%3d]   ", c, c);
        if( c % 8 == 7 )
            printf( "\n" );
    }
    printf( "Привет!!\n" );

    char s[] = "Привет!!\n";
    int n = sizeof( s );
    printf( "n=%d\n", n );
    for( int i=0; i<n; i++ )
        printf( "%c[%3d]   ", s[i], s[i]+ 256 );
    printf( "\n" );
    setlocale( LC_ALL, "Russian" );

    for( int i=0; i<n; i++ )
        printf( "%c[%3d]   ", s[i], (s[i]+ 256)%256 );
    printf( "\n" );
    printf( "Привет!!\n" );

    for(int c=128; c<256; c++ ){
        printf( "%c[%3d]   ", c, c);
        if( c % 8 == 7 )
            printf( "\n" );
    }

    char s1[300], s2[300], s3[300], s4[300];
    char pr = ' ', la = 'a', star = '*';

    char *nx = strstr( "eerewqrqwer wqrwerwe wew", "wer" );

    printf( "n=%c  %s\n", *nx, nx );
    /******************
    printf( "s1=");
    scanf( "%s %s %s %s", s1, s2, s3, s4 );

    printf( "s1=%s\n", s1 );
    printf( "s2=%s\n", s2 );
    printf( "s3=%s\n", s3 );
    printf( "s4=%s\n", s4 );

    gets( s1 );
    printf( "s1=");
    gets( s1 );
    for( i=0; s1[i]!=0; i++)
        if( s1[i]=la )
            s1[i] = star;

    printf( "s1=%s\n", s1 );
    ****************************/

    printf( "s1=");
    gets( s1 );
    for(int i=0; s1[i]!=0; i++)
        if( s1[i]==la )
            s1[i] = star;

    printf( "s1=%s\n", s1 );

    return 0;
}
