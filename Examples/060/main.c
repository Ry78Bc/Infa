#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    int x,y;
} Point_t;

typedef struct{
    Point_t A,B,C;
} Treangle_t;

typedef struct{
    int R;
    Point_t O;
} Circle_t;

typedef struct{
    Point_t P1,P2;
} Segment_t;

int ReadTreangle( char *fn, Treangle_t *a ){
    FILE *F;
    F = fopen( fn, "r" );
    if( F==NULL ){
        printf( "File %s not found\n", fn );
        return 0;
    }

    int k=0;
    while( !feof(F) ){
        int p = fscanf( F, "%d %d %d %d %d %d",
                           &(a->A.x), &(a->A.y),
                           &(a->B.x), &(a->B.y),
                           &(a->C.x), &(a->C.y)
                           );
        if( p==6 ){
            k++;
            a++;
        }
        else
          break;
    }

    fclose(F);
    return k;
}

int ReadPoints( char *fn, Point_t *a ){
    FILE *F;
    F = fopen( fn, "r" );
    if( F==NULL ){
        printf( "File %s not found\n", fn );
        return 0;
    }

    int k=0;
    while( !feof(F) ){
        int p = fscanf( F, "%d %d",
                           &(a->x), &(a->y) );
        if( p==2 ){
            k++;
            a++;
        }
        else
          break;
    }

    fclose(F);
    return k;
}

void PrintTreangls( Treangle_t *a, int ak ){
    for( int i=0; i<ak; i++){
        printf( "%2d  A(%4d%4d) B(%4d%4d) C(%4d%4d)\n", i,
                           a->A.x, a->A.y,
                           a->B.x, a->B.y,
                           a->C.x, a->C.y
                        );
        a++;
    }
}

void PrintPoints( Point_t *a, int ak ){
    for( int i=0; i<ak; i++){
        printf( "%2d Point(%4d%4d)  ", i,
                           a->x, a->y
                        );
        a++;
    }
    printf( "\n" );
}

float dist( Point_t p1, Point_t p2 ){
    return sqrt( (p1.x-p2.x)*(p1.x-p2.x) +
                 (p1.y-p2.y)*(p1.y-p2.y) );
}

float Heron( Treangle_t t ){
    float ab, bc, ac, pp;
    ab = dist( t.A, t.B );
    bc = dist( t.B, t.C );
    ac = dist( t.A, t.C );
    pp = ( ab + bc + ac )/2;

    return sqrt( pp * (pp-ab) * (pp-bc) * (pp-ac) );
}

//  vect k    x0* y1 - x1 * y0

int VectMult( Point_t v00, Point_t v01,
              Point_t v10, Point_t v11 ){
    int  v0x, v0y, v1x, v1y;

    v0x = v01.x - v00.x;
    v1x = v11.x - v10.x;
    v0y = v01.y - v00.y;
    v1y = v11.y - v10.y;

    return v0x * v1y - v0y * v1x;
}

int PointInCircle( Point_t p, Circle_t C ){
    float d = dist( p, C.O );
    if( d < C.R ){
        return 1;
    }
    else
    if( d==0 ){
        return 0;
    }
    else{
        return -1;
    }
}

int TreangleInCircle( Treangle_t t, Circle_t C ){
   int t1 = PointInCircle( t.A, C );
   int t2 = PointInCircle( t.B, C );
   int t3 = PointInCircle( t.C, C );
   if( t1<0 || t2<0 || t3<0 ){
       return -1;
   }
   if( t1==0 || t2==0 || t3==0 ){
       return 0;
   }
   return 1;
}

int PointInTreangle( Point_t p, Treangle_t t ){
  int v_ab, v_bc, v_ca;

  v_ab = VectMult( t.A, t.B, t.A, p );
  v_bc = VectMult( t.B, t.C, t.B, p );
  v_ca = VectMult( t.C, t.A, t.C, p );

  if( v_ab>0 && v_bc>0 && v_ca>0 ||
      v_ab<0 && v_bc<0 && v_ca<0 ){
     return 1;
  }
  if( v_ab>=0 && v_bc>=0 && v_ca>=0 ||
      v_ab<=0 && v_bc<=0 && v_ca<=0 ){
     return 0;
  }
  return -1;
}

int CircleInTreangle( Circle_t C, Treangle_t t ){
    int f = PointInTreangle( C.O, t );
    if( f == -1 ){
        return -1;
    }
    if( f == 0 && C.R == 0 ){
        return 0;
    }
    if( f == 0 ){
        return -1;
    }

    int Vab = VectMult( t.A, t.B, t.A, C.O );
    int Vbc = VectMult( t.B, t.C, t.B, C.O );
    int Vca = VectMult( t.C, t.A, t.C, C.O );
    float Pab = fabs(Vab)/dist( t.A, t.B);
    float Pbc = fabs(Vbc)/dist( t.B, t.C);
    float Pca = fabs(Vca)/dist( t.C, t.A);
    if( Pab<C.R || Pbc<C.R || Pca<C.R ){
        return -1;
    }
    if( Pab==C.R || Pbc==C.R || Pca==C.R ){
        return 0;
    }
    return 1;
}

int TreangleInTreangle( Treangle_t tin, Treangle_t tout ){
    int ta = PointInTreangle( tin.A, tout );
    int tb = PointInTreangle( tin.B, tout );
    int tc = PointInTreangle( tin.C, tout );

    if( ta<0 || tb<0 || tc<0 ){
        return -1;
    }
    if( ta==0 || tb==0 || tc==0 ){
        return 0;
    }
    return 1;
}

int main()
{
    Treangle_t t[100];
    int kt=0, kp=0;
    kt = ReadTreangle( "treangles.txt", t );
    PrintTreangls( t, kt );
    Point_t p[100];
    kp = ReadPoints( "points.txt", p );
    PrintPoints( p, kp );
/*
    for( int i=0; i<kt; i++ )
        printf( "%2d  Square=%12.6f\n", i, Heron( t[i] ) );

    Point_t p1 = { x:110, y:110 };
    for( int i=0; i<kt; i++ )
        printf( "p(%4d %4d) in %d %2d\n", p1.x, p1.y, i, PointInTreangle( p1, t[i] ) );

    Point_t p2 = { x:150, y:150 };
    for( int i=0; i<kt; i++ )
        printf( "p(%4d %4d) in %d %2d\n", p2.x, p2.y, i, PointInTreangle( p2, t[i] ) );
*/
    Treangle_t tmax;
    float Smax = -1.0;

    for( int i=0; i<kt; i++){

        int flag = 1;
        for( int j=0; j<kp; j++){
           if( PointInTreangle( p[j], t[i] ) >0 ){
              flag = 0;
              break;
           }
        }

        if( flag ){
            if( Smax < Heron( t[i] ) ){
                Smax = Heron( t[i] );
                tmax = t[i];
            }
        }
    }
    if( Smax == -1.0 ){
        printf( "not found\n" );
    }
    else{
        printf( "Smax = %12.8f\n", Smax );
        PrintTreangls( &tmax, 1 );
    }



    return 0;
}
