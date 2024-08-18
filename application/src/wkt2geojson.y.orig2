%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void yyerror(const char *s);
int yylex(void);

int safe_asprintf(char **strp, const char *fmt, ...);
char* to_geojson_point(const char* coordinates);
char* to_geojson_linestring(const char* coordinates);
char* to_geojson_polygon(const char* coordinates_list);

%}

%union {
    double dval;
    char* sval;
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
        printf("%s\n", $$);
        free($3);
        free($$);
    }
  ;

linestring:
    LINESTRING '(' coordinate_list ')'  
    {
        $$ = to_geojson_linestring($3);
        printf("%s\n", $$);
        free($3);
        free($$);
    }
  ;

polygon:
    POLYGON '(' '(' coordinate_list_list ')' ')'
    {
        $$ = to_geojson_polygon($4);
        printf("%s\n", $$);
        free($4);
        free($$);
    }
  ;

coordinate:
    NUMBER NUMBER  
    {
        safe_asprintf(&$$, "[%f, %f]", $1, $2);
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
        safe_asprintf(&$$, "%s, %s", $1, $3);
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
        safe_asprintf(&$$, "%s, %s", $1, $3);
        free($1);
        free($3);
    }
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    return yyparse();
}

int safe_asprintf(char **strp, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    int len = vsnprintf(NULL, 0, fmt, ap);
    if (len < 0) {
        va_end(ap);
        return -1;
    }

    *strp = malloc(len + 1);
    if (!*strp) {
        va_end(ap);
        return -1;
    }

    va_end(ap);
    va_start(ap, fmt);
    vsnprintf(*strp, len + 1, fmt, ap);
    va_end(ap);

    return len;
}

char* to_geojson_point(const char* coordinates) {
    char* result;
    safe_asprintf(&result, "{\"type\": \"Point\", \"coordinates\": %s}", coordinates);
    return result;
}

char* to_geojson_linestring(const char* coordinates) {
    char* result;
    safe_asprintf(&result, "{\"type\": \"LineString\", \"coordinates\": [%s]}", coordinates);
    return result;
}

char* to_geojson_polygon(const char* coordinates_list) {
    char* result;
    safe_asprintf(&result, "{\"type\": \"Polygon\", \"coordinates\": [[%s]]}", coordinates_list);
    return result;
}
