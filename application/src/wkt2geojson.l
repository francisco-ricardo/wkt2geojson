%{
#include "wkt2geojson.tab.h"
%}

%option noinput nounput

%%
"POINT"        { return POINT; }
"LINESTRING"   { return LINESTRING; }
"POLYGON"      { return POLYGON; }
[0-9]+(\.[0-9]+)?    { yylval.dval = atof(yytext); return NUMBER; }
[ \t\n\r]+     { /* ignore whitespaces and linebreaks */ }
","            { return ','; }
"("            { return '('; }
")"            { return ')'; }
.              { return yytext[0]; }
%%

int yywrap(void) {
    return 1;
}
