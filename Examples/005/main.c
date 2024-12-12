#include <stdio.h>
#include <stdlib.h>

void fill( int * a, int n ){
    for( int i=0; i<n; i++ )
        a[i] = rand() %140 -30;
}

float srArr( int *a, int n ){
    int sum = 0;
    for( int i=0; i<n; i++ )
        sum += a[i];
    return (float) sum / n;
}

int k3( int *a, int n ){
    int k=0;
    for( int i=0; i<n; i++ )
        if( a[i] %3 == 0 )
            k++;
    return k;
}

void prnt( int n, int m, int a[n][m] ){
    for( int i=0; i<n; i++ ){
        for( int j=0; j<m; j++ )
            printf( "%6d", a[i][j] );
        printf( "    %9.4f   %d\n", srArr( a[i], m ), k3( a[i], m ));
    }
    printf( "\n\n" );
}

int Del(  int n, int m, int a[n][m], float p ){
    int nnew = 0;
    for( int i=0; i<n; i++ ){
        if(srArr( a[i], m )>=p || k3( a[i], m) == 0){

            for( int j=0; j<m; j++ )
                a[nnew][j] = a[i][j];

            nnew++;
        }
    }
    return nnew;
}

int main()
{
    int z[7][9];

    fill( (int *) z, 7*9 );
    z[2][2] = 22;
    z[2][6] = 22;
    prnt( 7, 9, z );
    float srar = srArr( (int *) z, 7*9 );
    printf( "srArr = %9.4f\n", srar );

    int n = Del( 7, 9, z, srar );

    prnt( n, 9, z );

    return 0;
}
