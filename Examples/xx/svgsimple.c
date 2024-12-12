#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svgsimple.h"

char *hd;
char *tl;
char *tab1;

char *SVG_Color_names [ White+1 ] =  {//SVC_Color  (int) Purple
        "Default",	"Silver", 	"Gray",	    "Black",	"Red",
        "Maroon",	"Yellow",	"Olive",	"Lime",     "Green",
        "Aqua",  	"Teal",   	"Blue",	    "Navy",	    "Fuchsia",
        "Purple",   "White"  };


int load_str( char fn[], char **str ){
    FILE *f = fopen( fn, "r" );
    if( NULL==f ){
        printf( "Not found <%s> !!", fn );
        return 10;
    }
    printf( "load 10\n" );

    fseek( f, 0, SEEK_END );
    long k = ftell(f);
    fseek( f, 0, SEEK_SET );
    char *str1 = (char*) malloc( k+1 );
    int i = fread( str1, 1, k, f );
    fclose(f);

    str1[i] = 0;
    printf( "load\n" );
    *str = str1;
    return 0;
}

int init(){

    if( load_str( "SVG/h.txt", &hd ) )
        return 10;
    if( load_str( "SVG/t1.txt", &tab1 ) )
        return 11;


    for( SVG_Color_t cl=Default; cl<=White; cl++ ){
        printf( "%12s[%2d]        ", SVG_Color_names[cl], cl );
    }
    printf("\n");
    return 0;
}

char work[100] = "";
int SVGwidth  = 0;
int SVGheight = 0;

typedef enum{
    Fig_Polyline,
    Fig_Polygon,
    Fig_Line,
    Fig_Circle
} SVG_Figure;

typedef struct SVG_rec{
    SVG_Figure fig;
    char *pos;
    float linewidth;
    SVG_Color_t col;
    struct SVG_rec *next;
} SVG_rec;

SVG_rec *SVG_Head = NULL;
SVG_rec *SVG_Tail = NULL;

Point_t Recalc_Point( Point_t *p ){
    Point_t tmp;
    tmp.x =  p->x + SVGwidth/2;
    tmp.y = -p->y + SVGheight/2;

    return tmp;
}

int AddTail( SVG_Figure fg, char *pos, int lw, SVG_Color_t cl  ){
    SVG_rec *tmp = (SVG_rec*) malloc( sizeof(SVG_rec) );
    tmp->fig = fg;
    tmp->col = cl;
    tmp->linewidth = lw;
    tmp->pos = (char*) malloc( strlen(pos)+2);
    strcpy( tmp->pos, pos );
    tmp->next = NULL;

    printf( "%s Color[%d] width=%4.2f ff=%d\n", tmp->pos,
                                             tmp->col,
                                             tmp->linewidth,
                                             tmp->fig );

    if( ! SVG_Head ){
        SVG_Head = tmp;
        SVG_Tail = tmp;
    }
    else{
        SVG_Tail->next = tmp;
        SVG_Tail = tmp;
    }
    return 0;
}

int SVG_open_base( char *fn_out, int width_out, int height_out );

char xyline[] = "<line x1=\"%d\" y1=\"%d\" \
x2=\"%d\" y2=\"%d\" stroke-width=\"%4.2f\" />\n";


char xytext[] = "<text \n\
    x='%d' \n\
    y='%d' \n\
    style=\"font-family: 'Super Sans', Helvetica, sans-serif; \n\
        font-weight: italic; font-style: normal; orientation='%c'\">\n\
    %s \n\
  </text>\n" ;
/****************
"<text x=\"%dpx\" y=\"%dpx\" \
font-weight: italic; font-style: normal; \
text-anchor=\"start\"> %s </text>" ;
*****************/
char xypolyline[] = "<polyline fill='none' stroke='%s' \
stroke-width='%4.2f' %s />\n";
char xypolygon[] = "<polygon fill='none' stroke='%s' \
stroke-width='%4.2f' %s />\n";

char xyzline[] = "<line %s stroke-width='%4.2f' stroke='%s' />\n";
char xyzcircle[] = "<circle %s fill='none' stroke-width='%4.2f' stroke='%s' />\n";
//


int Axess( FILE *f ){
    int x0 = SVGwidth / 2;
    int y0 = SVGheight / 2;
    fprintf( f, "<g stroke='black' \
fill='black' font-size='8' writing-mode='tb-rl' \
transform='translate(3,3)' >\n" );

    fprintf( f, xyline, x0, 0, x0, SVGheight, 1.5 );
    fprintf( f, xyline, 0, y0, SVGwidth, y0, 1.5 );

    for( int xx=50; xx<x0; xx+=50 ){
        char mark[40];

        int yy0 = y0-5;
        int yy1 = y0+5;

        sprintf( mark, "%d", xx );
        int xx1 = xx+x0;
        fprintf( f, xyline, xx1, yy0, xx1, yy1, 0.7 );
        fprintf( f, xytext, xx1+5, yy1+5, 'v', mark );

        sprintf( mark, "%d", -xx );
        xx1 = -xx+x0;
        fprintf( f, xyline, xx1, yy0, xx1, yy1, 0.7 );
        fprintf( f, xytext, xx1+5, yy1+5, 'v', mark );
    }
    fprintf( f, "</g>\n\
<g stroke='black' \
fill='black' font-size='8' writing-mode='rl-tb' \
transform='translate(3,3)' >\n" );

    for( int yy=50; yy<y0; yy+=50 ){
        char mark[40];

        int xx0 = x0-5;
        int xx1 = x0+5;

        sprintf( mark, "%d", -yy );
        int yy1 = yy+y0;
        fprintf( f, xyline, xx1, yy1, xx0, yy1, 0.7 );
        fprintf( f, xytext, xx1+5, yy1+5, 'h', mark );

        sprintf( mark, "%d", yy );
        yy1 = -yy+y0;
        fprintf( f, xyline, xx1, yy1, xx0, yy1, 0.7 );
        fprintf( f, xytext, xx1+5, yy1+5, 'h', mark );
    }
    SVG_rec *tmp_rec = SVG_Head;
    while( tmp_rec ){
        switch( tmp_rec->fig ){
            case Fig_Polygon:
                fprintf( f, xypolygon,
                         SVG_Color_names[tmp_rec->col],
                         tmp_rec->linewidth,
                         tmp_rec->pos );
                break;
            case Fig_Polyline:
                fprintf( f, xypolyline,
                         SVG_Color_names[tmp_rec->col],
                         tmp_rec->linewidth,
                         tmp_rec->pos );
                break;
            case Fig_Line:
                fprintf( f, xyzline,
                         tmp_rec->pos,
                         tmp_rec->linewidth,
                         SVG_Color_names[tmp_rec->col] );
                break;
//    char xyzline[] = "<line %s stroke-width='%4.2f' stroke='%s' />\n";
            case Fig_Circle:
                fprintf( f, xyzcircle,
                         tmp_rec->pos,
                         tmp_rec->linewidth,
                         SVG_Color_names[tmp_rec->col] );
                break;
// char xyzcircle[] = "<circle %s fill='none' stroke-width="%4.2f" stroke='%s' />\n";
        }
        tmp_rec = tmp_rec->next;
    }
    fprintf( f, "</g>\n" );
    fprintf( f,
"<g writing-mode='tb-rl' fill='red' font-size='10'>\n\
    <text x='%dpx' y='10px' text-anchor='start'>Пример   \"SVGsimle.h\"</text>\n\
    <text x='%dpx' y='%dpx' text-anchor='start'>Ver 0.1</text>\n\
    <text x='%dpx' y='%dpx' text-anchor='end'>sasha@bmstu.ru</text>\n\
</g>\n",
    SVGwidth-10, SVGwidth-10, y0+10,  SVGwidth-10,  SVGheight-10 );
    return 0;
}

extern int SVG_open1( char filename[], int width, int height ){
    if( strlen(work)!=0 ){
        printf( "Close SVG!!\n" );
        return 100;
    }
    strcpy( work, filename );

    int rez = 0;
    if( ( rez = init() )  ){
        printf( "FAIL %d !\n", rez );
        return 10;
    }
    SVGwidth  = width;
    SVGheight = height;
    return 0;
}


extern int var_SVG_open(SVG_open_args in){
    char *fn_out   = in.fn ? in.fn : "default";
    int width_out  = in.w ? in.w : 800;
    int height_out = in.h ? in.h : 600;
    return SVG_open1( fn_out, width_out, height_out );
}

/*************************
int SVG_open_base( char *fn_out, int width_out, int height_out ){
    printf( "s=%16s   w=%3d  h=%3d\n", fn_out, width_out, height_out );
    return width_out*1000+height_out;
}
*************************/

extern void SVG_close(){

    char tmp_filename[100];
    strcpy( tmp_filename, work );
    int i1 = strlen(tmp_filename);
    if( strcmp( tmp_filename+i1-4, ".svg" ) ){
        strcat( tmp_filename, ".svg" );
    }
    FILE *f = fopen( tmp_filename, "w" );
    fprintf( f, hd, SVGwidth+5, SVGheight+5 );
    fprintf( f, tab1, SVGwidth, SVGheight );
    Axess( f );

    fprintf( f, "</svg>\n" );
    fclose( f );

    system( tmp_filename );

}

int ff_lne( char s[], int color, int width, int ff ){

    return 0;
}

int ff_base( Point_t *p, int k, int color, int width, int ff ){
    char tmp[2000],*ptr;
    strcpy( tmp, "points=\"" );
    ptr = tmp + strlen(tmp);

    for( int i=0; i<k; i++ ){
        // printf( "( %3d %3d)\n", p->x, p->y );
        Point_t r = Recalc_Point( p );
        sprintf( ptr, "%d,%d", r.x, r.y );
        // printf( "1 +len = %d\n", strlen(ptr) );
        ptr += strlen(ptr);

        // printf( "1<%s>\n", tmp );

        if( i<k-1 ){
            if( i%5 )
               *(ptr++) = ' ';
            else
               *(ptr++) = '\n';
            *ptr = '\0';
        }

        //printf( "2<%s>\n", tmp );
        p++;
    }
    *(ptr++) = '"';
    *ptr = '\0';
    printf( "%s Color[%d] width=%d ff=%d\n", tmp, color, width, ff );
    AddTail( ff, tmp, width, color );

    return 0;
}

int var_SVG_polyline( Point_t *p, int k_in, col_wd_args in ){

    int col_out = ( in.col>0 && in.col<=White ) ? in.col : Green;
    int k_out = ( k_in>0 ) ? k_in : 1;
    int lw_out = ( in.linewidth>0 && in.linewidth<16 ) ? in.linewidth : 3;

    return ff_base( p, k_out, col_out, lw_out, Fig_Polyline );
}

int var_SVG_polygon( Point_t *p, int k_in, col_wd_args in ){

    int col_out = ( in.col>0 && in.col<=White ) ? in.col : Blue;
    int k_out = ( k_in>0 ) ? k_in : 1;
    int lw_out = ( in.linewidth>0 && in.linewidth<16 ) ? in.linewidth : 3;

    return ff_base( p, k_out, col_out, lw_out, Fig_Polygon );
}

Point_t Point( int x1, int y1 ){
    Point_t tmp = { x:x1, y:y1 };
    return tmp;
}

char xyline_par[] = "x1='%d' y1='%d' x2='%d' y2='%d'";

int var_SVG_line( int x1, int y1, int x2, int y2,
                  col_wd_args in ){
    Point_t temp[2] = { Point( x1, y1 ),
                        Point( x2, y2 ) };
    temp[0] = Recalc_Point( temp );
    temp[1] = Recalc_Point( temp+1 );

    char par[300];
    sprintf( par, xyline_par, temp[0].x,
                              temp[0].y,
                              temp[1].x,
                              temp[1].y );
    int col_out = ( in.col>0 && in.col<=White ) ? in.col : Olive;
    int lw_out = ( in.linewidth>0 && in.linewidth<16 ) ? in.linewidth : 2;

    return AddTail( Fig_Line, par, lw_out, col_out );
}

char xycircle_par[] = "cx='%dpx' cy='%dpx' r='%dpx'";

int var_SVG_circle( int x1, int y1, int r1,
                  col_wd_args in ){

//    Point_t xy = Recalc_Point( );
    Point_t temp = Point( x1, y1 );
    Point_t xy = Recalc_Point( &temp );
    r1 = (r1<3)?3:r1;
    char par[300];
    sprintf( par, xycircle_par, xy.x, xy.y, r1 );
    int col_out = ( in.col>0 && in.col<=White ) ? in.col : Purple;
    int lw_out = ( in.linewidth>0 && in.linewidth<16 ) ? in.linewidth : 2;

    return AddTail( Fig_Circle, par, lw_out, col_out );
}


/********************
typedef struct SVG_rec{
    SVG_Figure fig;
    char *pos;
    float linewidth;
    SVG_Color_t col;
    struct SVG_rec *next;
} SVG_rec;

SVG_rec *SVG_Head = NULL;
SVG_rec *SVG_Tail = NULL;

Point_t Recalc_Point( Point_t *p ){
    Point_t tmp;
    tmp.x =  p->x + SVGwidth/2;
    tmp.y = -p->y + SVGheight/2;

    return tmp;
}

void AddTail( SVG_Figure fg, char *pos, int lw, SVG_Color_t cl  ){
    SVG_rec *tmp = (SVG_rec*) malloc( sizeof(SVG_rec) );

********************/
