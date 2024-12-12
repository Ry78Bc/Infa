#define SVG_open(...) var_SVG_open((SVG_open_args){__VA_ARGS__})
#define SVG_polyline( p, k, ... ) \
    var_SVG_polyline( p, k, (col_wd_args){__VA_ARGS__} )
#define SVG_polygon( p, k, ... ) \
    var_SVG_polygon( p, k, (col_wd_args){__VA_ARGS__} )
#define SVG_line( x1, y1, x2, y2, ... ) \
    var_SVG_line( x1, y1, x2, y2, (col_wd_args){__VA_ARGS__} )
#define SVG_circle( x1, y1, r1, ... ) \
    var_SVG_circle( x1, y1, r1, (col_wd_args){__VA_ARGS__} )


typedef struct {
    char *fn;
    int w;
    int h;
} SVG_open_args;

typedef enum   { Default,	Silver, 	Gray,	Black,	Red,
                 Maroon,	Yellow,	    Olive,	Lime,   Green,
                 Aqua,  	Teal,   	Blue,	Navy,	Fuchsia,
                 Purple,    White  }   SVG_Color_t;

typedef struct{
    int x,y;
} Point_t;

typedef struct {
    SVG_Color_t col;
    int linewidth;
} col_wd_args;

int var_SVG_open(SVG_open_args in);

int var_SVG_polyline( Point_t *p, int k_in, col_wd_args in );
int var_SVG_polygon( Point_t *p, int k_in, col_wd_args in );
int var_SVG_line( int x1, int y1, int x2, int y2,
                  col_wd_args in );
int var_SVG_circle( int x1, int y1, int r1,
                  col_wd_args in );

void SVG_close();




