/**
 * WKT Scanner
 *
 * This scanner is responsible for tokenizing the input WKT file.
 * It generates a Finite State Automaton (FSA) using the `flex` tool, 
 * which produces a C-based lexical analyzer (`lex.yy.c`).
 *
 * The scanner recognizes WKT tokens and feeds them to the parser for 
 * further processing. It reads the input character by character and 
 * groups them into tokens based on predefined regular expressions.
 *
 * The key function exported by the scanner is `yylex`, which is 
 * responsible for returning the next token in the input stream. 
 * Each token is associated with a specific type, as defined in the 
 * parser's token declarations (`parser.tab.h`), and contains the 
 * corresponding lexical value.
 *
 * The scanner is designed to work in conjunction with a Bison parser, 
 * which processes the tokens according to the grammar rules defined 
 * in the parser.
 *
 * Some key features of the scanner:
 * 
 * - **Greedy token recognition**: The scanner always attempts to 
 *   match the longest possible token in the input.
 * - **Whitespace and comments**: Whitespace characters (spaces, 
 *   tabs, newlines) are ignored, and comments (in a predefined 
 *   format) are skipped entirely.
 * - **Error handling**: If an invalid token is encountered, 
 *   the scanner triggers an error, which is handled by the parser.
 *
 * The scanner also defines the function `yywrap`, which is responsible 
 * for indicating the end of the input. By default, `yywrap` returns 1 
 * when the scanner reaches the end of the input, allowing the parser 
 * to finish processing.
 *
 * Additionally, the scanner keeps track of the current line number and 
 * position in the input file, which is useful for debugging and error 
 * reporting.
 */

%{
#include "parser.tab.h"
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
