#include <stdio.h>
#include <stdlib.h>


void DelCol( int n, int m, int a[][m], int k ){

    int *ip = a[0];
    for( int i=0; i<n; i++ )
        for( int j=0; j<m; j++ )
            if( j != k ){
                *ip = a[i][j];
                ip++;
            }
}


int DelCol5( int n, int m, int a[][m] ){

    int k5[m], nn;
    for( int j=0; j<m; j++ ){
        k5[j] = 0;
        for( int i=0; i<n; i++ )
            if( a[i][j] % 5 ==0 )
                k5[j]++;
    }

    nn = 0;
    for( int j=0; j<m; j++ ){
        printf( "%5d", k5[j] );
        if( k5[j] >0 )
            nn++;
    }
    printf( "\n\n\n" );

    int *ip = a[0];
    for( int i=0; i<n; i++ )
        for( int j=0; j<m; j++ )
            if( k5[j] > 0 ){
                *ip = a[i][j];
                ip++;
            }
    return nn;
}

void fill( int a[], int n ){
    for( int i=0; i<n; i++ )
        a[i] = rand() %121 - 40;
}

void prnt( int n, int m, int b[][m] ){
    for( int i=0; i<n; i++ ){
        for( int j=0; j<m; j++ )
            printf( "%5d", b[i][j] );
        printf( "\n" );
    }
    printf( "\n\n" );
}

int main()
{
    int d[5][6], dm, d1[7][12];

    fill( d[0], 5*6 );
    d[4][0] = 11;
    d[0][5] = 11;
    prnt( 5, 6, d );

//    DelCol( 5,6,d, 3 );
    dm = DelCol5( 5, 6, d );

    prnt( 5, dm, d );

    fill( d1[0], 7*12 );
    prnt( 7, 12, d1 );

    dm = DelCol5( 7, 12, d1 );

    prnt( 7, dm, d1 );

    return 0;
}
