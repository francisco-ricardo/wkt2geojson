/**
 * WKT Parser
 *
 * The parser is a component of the transpiler that reads a 
 * `WKT` file and translates it into a `GeoJSON` file.
 *
 * Well-known text (WKT) is a text markup language for representing 
 * vector geometry objects (Wikipedia, 2024). 
 * 
 * GeoJSON is a standard format, based on the JSON format, designed 
 * for representing simple geographical features, along with their 
 * non-spatial attributes (Wikipedia, 2024).  
 *
 * The parser defines a BNF grammar and the production rules to
 * generate an LR algorithm parser in C language 
 * (`parser.tab.h` and `parser.tab.c`) from the `bison` tool.
 * The algorithm can recognize the `WKT` records based 
 * on the tokens generated from the scanner.
 *
 * The parser also defines the production rules set.
 * The production rules extract data according to the records structure 
 * and populate the `GeoJSON` object.
 * After processing all the tokens generated from the scanner
 * the parser will save the `GeoJSON` object into the output file.
 *
 * The parser exports the `feat_transpile` function.
 * The caller has to specify 3 arguments: input file, log file, and
 * output file.
 * The bison debug mode can be activated by defining the variable 
 * yydebug to 1 on feat_transpile function.
 *
 * The global static pointer named `y_feat_list` is a `gjs_feat_list_t`
 * pointer. It will hold the `GeoJSON` data extracted from the input.
 *
 * The static function named `clear_token` cleans the token, 
 * by removing white spaces and newlines characters. 
 * The scanner implemented by the `flex` tool is greedy and 
 * the tokens may be dirty.
*/


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

%left ','

%token <dval> NUMBER
%token POINT LINESTRING POLYGON

%type <sval> coordinate coordinate_list point linestring polygon geometry_list polygon_coordinates

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
    POLYGON '(' polygon_coordinates ')'  
    {
        $$ = to_geojson_polygon($3);
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

polygon_coordinates:
    '(' coordinate_list ')'  
    {
        $$ = strdup($2);
        free($2);
    }
  | polygon_coordinates ',' '(' coordinate_list ')'  
    {
        write_string(&$$, "%s, %s", $1, $4);
        free($1);
        free($4);
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

    char* header_str = header();
    fprintf(y_output_file, "%s", header_str);
    free(header_str);

    if (!yyparse()) {
        status = 0;
    }

    char* footer_str = footer();
    fprintf(y_output_file, "%s", footer_str);
    free(footer_str);

    return status;
}
