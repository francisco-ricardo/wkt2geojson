/** 
 * Features Scanner
 *
 * The scanner is a component of a transpiler program that reads a `FEATURES` file 
 * and translates it into a `GeoJSON` file.
 *
 * The `FEATURES` is a file that is part of the ODB++ standard.
 * The file consists of the geometry data of the ODB++ layers.
 * The data can be used to analysis or dfm actions on Genesis software.
 *
 * The scanner defines a set of regular expressions to generate a 
 * Finite State Automaton (FSA) in C language (`lex.yy.c`) from the `flex` tool.
 * The FSA can read the input text and split it into the tokens defined by the 
 * regular expressions.
 * The tokens are injected into the parser that is responsible for the grammar parsing.
 *
 * The LR parser header (`features.tab.h`) is a dependency for the scanner.
 * The token names must be defined on the parser.
 *
*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wkt_parser.tab.h"   // Tokens definitions from Bison
%}

/** %option noinput nounput */
%option noinput nounput noyywrap

%%

"POINT"            { return POINT; }
"LINESTRING"       { return LINESTRING; }
"POLYGON"          { return POLYGON; }
"("                { return OPEN_PARENTHESIS; }
")"                { return CLOSE_PARENTHESIS; }
","                { return COMMA; }
[0-9]+             { yylval.ival = atoi(yytext); return INTEGER; }
[0-9]+"."[0-9]+    { yylval.fval = atof(yytext); return FLOAT; }
[ \t\n\r]+         ;  // Ignore whitespaces and line breaks
.                  { return UNKNOWN; }

%%


int yywrap(void) {
    return 1;
}


// EOF


// %option noinput nounput nodefault


