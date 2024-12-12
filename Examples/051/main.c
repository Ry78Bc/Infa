#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef
struct{
    char Name[25];
    char SecName[30];
    char Group[10];
    unsigned char Mark[4];
    char Zach[6];
} student_t;

void FillStud( student_t *st ){
    char tmp[20];
    printf( "Familia :" );
    scanf( "%s", st->SecName );   // (*st).SecName
    printf( "Imia    :" );
    scanf( "%s", st->Name );
    printf( "Gruppa  :" );
    scanf( "%s", st->Group );

    for( int i=0; i<4; i++ ){
        printf( "Ozenki %d :",i+1 );
        scanf( "%d", &(st->Mark[i]) );
        if( st->Mark[i] > 5 )
            st->Mark[i] = 5;
    }
    for( int i=0; i<6; i++ ){
        printf( "Zachet %d :",i+1 );
        scanf( "%s", tmp );

        if( tmp[0] != '+' )
            st->Zach[i] = '-';
        else
            st->Zach[i] = '+';
     }
}

void PrntStud( student_t *st ){
    printf( "%15s %15s %12s", st->SecName, st->Name, st->Group );
    for( int i=0; i<4; i++ )
        printf( " %d", st->Mark[i] );
    for( int i=0; i<6; i++ )
        printf( " %c", st->Zach[i] );
    printf( "\n" );
}

int main()
{
    char com[10];
    // system( "chcp 1251" );
    //setlocale( LC_ALL, "Russian" );
    student_t s[100];
    int ks = 0;

    while( strcmp(com, "end") != 0 ){
        printf( "com=" );
        scanf( "%s", com );

        if( strcmp( com, "add" ) == 0 ){
            FillStud( s+ks );
            ks++;
        }
        else
        if( strcmp( com, "write" ) == 0 ){
            FILE * f = fopen( "stud.dat", "wb" );
            fwrite( s, sizeof(student_t), ks, f );
            fclose( f );
        }
        else
        if( strcmp( com, "read" ) == 0 ){
            FILE * f = fopen( "stud.dat", "rb" );
            ks = fread( s, sizeof(student_t), 100, f );
            fclose( f );
        }
        else
        if( strcmp( com, "print" ) == 0 ){
            for( int i=0; i<ks; i++)
                PrntStud( s+i );
        }
        else
        if( strcmp( com, "del" ) == 0 ){
            for( int i=0; i<ks; i++){
                printf( "%3d ", i+1 );
                PrntStud( s+i );
            }
            int n;
            printf( "Delete N=" );
            scanf( "%d", &n );
            if( n<1 || n> ks ){
                printf( "Wrong number!!\n" );
                continue;
            }
            for( int i=n; i<ks; i++ )
                s[i-1] =  s[i];
            ks--;
        }



    }
    /***
    FillStud( &s );
    PrntStud( &s );
    FILE *f;
    f = fopen( "stud.dat", "wb" );
    if( fwrite( &s, sizeof(student_t), 1, f )==1 )
        printf( "Success\n" );
    fclose(f);
**/

    return 0;
}
