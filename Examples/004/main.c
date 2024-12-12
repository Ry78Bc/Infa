#include <stdio.h>
#include <stdlib.h>

void fill( int a[], int n ){
    int i;
    for( i=0; i<n; i++)
        a[i] = rand()%141 - 59;
}

void prnt( int a[], int n ){
    int i;
    for( i=0; i<n; i++)
        printf( "%8d", a[i] );
    printf("\n\n");
}


int arr_f1( int n, int *a ){
    int sum = 0;

    for( int i=0; i<n; i++, a++ )
        sum += *a;
    a -= n;

    float arif = (float) sum/n;

    printf( "arif = %10.4f\n", arif );

    int *anew = a;
    for( int i=0; i<n; i++, a++ )
        if( *a %3 != 0 ||  arif <= *a ){

            *(anew++) = *a;
        }
        else
            printf( "%8d", *a );
    printf( "\n!!tmp\n");
    a -= n;
    return anew - a;
}


int main()
{
    int z[100], n=100;
    fill( z, n );
    prnt( z, n );

    n = arr_f1( n, z );

    prnt( z, n );
    return 0;
}
