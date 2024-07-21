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

#include "features.tab.h"
%}

%option noinput nounput

LINE     "#L"
PAD      "#P"
DIGIT    [0-9]
TEXT     [a-z]+[a-z0-9._]*
NEG      "N"
POS      "P"
ATTR     [;][.]?[a-z0-9,=_.]+
SEP      [ \t]+
EOL      [\n\r\f]
COMMENT  ^"###"[\t ]+[a-zA-Z0-9._\-\t ]+[\t ]+"###"

%%

{LINE} {
     yylval.str = yytext;
     return LINE;
}

{PAD} {
     yylval.str = yytext;
     return PAD;
}

{DIGIT}+"."{DIGIT}* {
     yylval.str = yytext;
     return FLOAT;
}

{TEXT} {
     yylval.str = yytext;
     return TEXT;     
}

{NEG}|{POS} {
     yylval.str = yytext;
     return POL;
}

{ATTR} {
     yylval.str = yytext;
     return ATTR;
}

{DIGIT}+ {
     yylval.str = yytext;
     return INT;
}

{EOL} {
     yylval.str = yytext;
     return EOL;
}

{SEP} {
     yylval.str = yytext;
     return SEP;
}

{COMMENT} {
     /** Ignore comments */
}

%%


int yywrap(void) {
    return 1;
}


// EOF


// %option noinput nounput nodefault