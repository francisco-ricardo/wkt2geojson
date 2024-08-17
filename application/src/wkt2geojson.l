%{
#include "wkt2geojson.tab.h"
%}

%%

"POINT"       { return POINT; }
"LINESTRING"  { return LINESTRING; }
"POLYGON"     { return POLYGON; }
[0-9]+(\.[0-9]+)?  { yylval.dval = atof(yytext); return NUMBER; }
","           { return ','; }
"("           { return '('; }
")"           { return ')'; }
[ \t\n\r]+    { /* Ignore whitespaces */ }
.             { /* Ignore everything else */ }

%%

int yywrap() {
    return 1;
}
