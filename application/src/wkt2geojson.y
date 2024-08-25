%{
#include <stdio.h>
#include <string.h>

#include "writer.h"


void yyerror(const char *s);
int yylex(void);

%}

%union {
    double dval;
    char* sval;
}


%code provides {
  int transpile(FILE *in_file, FILE *out_file);
}

%code {
    extern FILE *yyin;
    static int count = 0;
    static FILE *y_output_file = NULL;
}

%token <dval> NUMBER
%token POINT LINESTRING POLYGON

%type <sval> coordinate coordinate_list coordinate_list_list point linestring polygon geometry_list

%%

geometry:
    geometry_list
    ;

geometry_list:
    point
  | linestring
  | polygon
  | geometry_list point
  | geometry_list linestring
  | geometry_list polygon
  ;

point:
    POINT '(' coordinate ')'  
    {
        $$ = to_geojson_point($3);
        count++;
        if (count > 1) {
            fprintf(y_output_file, ",%s\n", $$);    
        } else {
            fprintf(y_output_file, "%s\n", $$);
        }
        free($3);
        free($$);
    }
  ;

linestring:
    LINESTRING '(' coordinate_list ')'  
    {
        $$ = to_geojson_linestring($3);        
        count++;
        if (count > 1) {
            fprintf(y_output_file, ",%s\n", $$);    
        } else {
            fprintf(y_output_file, "%s\n", $$);
        }

        free($3);
        free($$);
    }
  ;

polygon:
    POLYGON '(' '(' coordinate_list_list ')' ')'
    {
        $$ = to_geojson_polygon($4);
        count++;
        if (count > 1) {
            fprintf(y_output_file, ",%s\n", $$);    
        } else {
            fprintf(y_output_file, "%s\n", $$);
        }

        free($4);
        free($$);
    }
  ;

coordinate:
    NUMBER NUMBER  
    {
        write_string(&$$, "[%f, %f]", $1, $2);
    }
  ;

coordinate_list:
    coordinate  
    {
        $$ = strdup($1);
        free($1);
    }
  | coordinate_list ',' coordinate  
    {
        write_string(&$$, "%s, %s", $1, $3);
        free($1);
        free($3);
    }
  ;

coordinate_list_list:
    coordinate_list  
    {
        $$ = strdup($1);
        free($1);
    }
  | coordinate_list_list ',' coordinate_list  
    {
        write_string(&$$, "%s, %s", $1, $3);
        free($1);
        free($3);
    }
  ;

%%


void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}


int transpile(FILE *in_file, FILE *out_file) {

    /** Uncomment the line below to enable the debugging */
    //yydebug = 1;

    int status = 1;
    yyin = in_file;
    y_output_file = out_file;

    fprintf(y_output_file, "%s", header());

    if (!yyparse()) {
        status = 0;
    }

    fprintf(y_output_file, "%s", footer());

    return status;

}


