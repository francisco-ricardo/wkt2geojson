%{
#include "wkt2geojson.tab.h"
%}

%%
"POINT"        { return POINT; }
"LINESTRING"   { return LINESTRING; }
"POLYGON"      { return POLYGON; }
[0-9]+(\.[0-9]+)?    { yylval.dval = atof(yytext); return NUMBER; }
[ \t\n\r]+     { /* ignorar espaços em branco e quebras de linha */ }
","            { return ','; }
"("            { return '('; }
")"            { return ')'; }
.              { return yytext[0]; }
%%

int yywrap() {
    return 1;
}
