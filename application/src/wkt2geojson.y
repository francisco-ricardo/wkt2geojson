/**
 * Features Parser
 *
 * The parser is a component of a transpiler program that reads a 
 * `FEATURES` file and translates it into a `GeoJSON` file.
 *
 * The `FEATURES` is a file that is part of the ODB++ standard.
 * The file consists of the geometry data of the ODB++ layers.
 * The data can be used to analysis or dfm actions on Genesis software.
 * 
 * The parser defines a BNF grammar and the production rules to
 * generate an LR algorithm parser in C language 
 * (`features.tab.h` and `features.tab.c`) from the `bison` tool.
 * The algorithm can recognize the `FEATURES` records based 
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

%code top {

  #include <stdio.h>
  #include <stdlib.h>
  #include <ctype.h>
  #include <string.h>
  #include <stddef.h>

  #include "gjs.h"

  int yylex (void);
  void yyerror(const char *s);

}

%union {
  char *str;  
};


%code provides {

  int feat_transpile(FILE *in_file, FILE *log_file, FILE *out_file);

}

%code {

  extern FILE *yyin;
  FILE *y_log_file;
  FILE *y_out_file;
  static gjs_feat_list_t *y_feat_list = NULL;

  static char *clear_token(char *token);

}


%token <str> LINE
%token <str> PAD
%token <str> INT 
%token <str> FLOAT
%token <str> TEXT
%token <str> POL
%token <str> ATTR
%token <str> SEP
%token <str> EOL

%type <str> layer
%type <str> record

%start layer


%%

layer : error {
        fprintf(y_log_file, "NOT PARSED: %s\n", $$);
        yyclearin;
      }
      |
      layer record {
      }
      ;


record : LINE SEP FLOAT SEP FLOAT SEP FLOAT SEP FLOAT SEP TEXT SEP POL SEP INT SEP EOL {

        /** Grab the tokens values */
        char *eptr;
        const double x1 = strtod(clear_token($3), &eptr);
        const double y1 = strtod(clear_token($5), &eptr);
        const double x2 = strtod(clear_token($7), &eptr);
        const double y2 = strtod(clear_token($9), &eptr);

        const char *symbol = clear_token($11);
        const char *polarity = clear_token($13);

        /** Deals with GeoJSON object */
        gjs_geom_t *geom = gjs_geom_create();
        geom->geom_type = LineString;        
        gjs_coord_list_t *coord_list = gjs_coord_list_create();
        geom->coord_list = coord_list;
        gjs_coord_list_push(coord_list, gjs_coord_node_create(x1, y1));
        gjs_coord_list_push(coord_list, gjs_coord_node_create(x2, y2));

        gjs_prop_list_t *prop_list = gjs_prop_list_create();
        
        gjs_prop_node_t *prop_symbol_node = gjs_prop_node_create("symbol", symbol);
        gjs_prop_list_push(prop_list, prop_symbol_node);
        
        gjs_prop_node_t *prop_pol_node = gjs_prop_node_create("polarity", polarity);
        gjs_prop_list_push(prop_list, prop_pol_node);       

        gjs_feat_node_t *feat_node = gjs_feat_node_create(geom, prop_list);
        gjs_feat_list_push(y_feat_list, feat_node);
      }
      |
      PAD SEP FLOAT SEP FLOAT SEP TEXT SEP POL SEP INT SEP INT SEP POL EOL {

        /** Grab the tokens values */
        char *eptr;
        const double x1 = strtod(clear_token($3), &eptr);
        const double y1 = strtod(clear_token($5), &eptr);

        const char *symbol = clear_token($7);
        const char *polarity = clear_token($9);

        /** Deals with GeoJSON object */
        gjs_geom_t *geom = gjs_geom_create();
        geom->geom_type = Point;        
        gjs_coord_list_t *coord_list = gjs_coord_list_create();
        geom->coord_list = coord_list;
        gjs_coord_list_push(coord_list, gjs_coord_node_create(x1, y1));

        gjs_prop_list_t *prop_list = gjs_prop_list_create();
        
        gjs_prop_node_t *prop_symbol_node = gjs_prop_node_create("symbol", symbol);
        gjs_prop_list_push(prop_list, prop_symbol_node);
        
        gjs_prop_node_t *prop_pol_node = gjs_prop_node_create("polarity", polarity);
        gjs_prop_list_push(prop_list, prop_pol_node);       

        gjs_feat_node_t *feat_node = gjs_feat_node_create(geom, prop_list);
        gjs_feat_list_push(y_feat_list, feat_node);
      }
      |
      PAD SEP FLOAT SEP FLOAT SEP TEXT SEP POL SEP INT SEP INT SEP POL ATTR EOL {

        /** Grab the tokens values */
        char *eptr;
        const double x1 = strtod(clear_token($3), &eptr);
        const double y1 = strtod(clear_token($5), &eptr);

        const char *symbol = clear_token($7);
        const char *polarity = clear_token($9);
        const char *attr = clear_token($16);

        /** Deals with GeoJSON object */
        gjs_geom_t *geom = gjs_geom_create();
        geom->geom_type = Point;        
        gjs_coord_list_t *coord_list = gjs_coord_list_create();
        geom->coord_list = coord_list;
        gjs_coord_list_push(coord_list, gjs_coord_node_create(x1, y1));

        gjs_prop_list_t *prop_list = gjs_prop_list_create();
        
        gjs_prop_node_t *prop_symbol_node = gjs_prop_node_create("symbol", symbol);
        gjs_prop_list_push(prop_list, prop_symbol_node);
        
        gjs_prop_node_t *prop_pol_node = gjs_prop_node_create("polarity", polarity);
        gjs_prop_list_push(prop_list, prop_pol_node);

        gjs_prop_node_t *prop_attr_node = gjs_prop_node_create("attribute", attr);
        gjs_prop_list_push(prop_list, prop_attr_node);        

        gjs_feat_node_t *feat_node = gjs_feat_node_create(geom, prop_list);
        gjs_feat_list_push(y_feat_list, feat_node);
      }      
      ;


%%


int transpile(FILE *in_file, FILE *log_file, FILE *out_file) {

  int status = 1;

  /** Uncomment the line below to enable the debugging */
  //yydebug = 1;

  yyin = in_file;
  y_log_file = log_file;
  y_out_file = out_file;

  y_feat_list = gjs_feat_list_create();  

  /** Parsing >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
  if (!yyparse()) {    
    gjs_feat_list_print(y_feat_list, out_file);
    status = 0;
    fprintf(y_log_file, "\nINFO|Transpilation completed");    
  } 
  else {
    fprintf(y_log_file, "\nERROR|Transpilation failed");
    status = 1;
  }  
  /** <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */


  /** Cleanup */
  gjs_feat_list_destroy(y_feat_list);
      
  return status;
}


void yyerror(const char *s) {
  fprintf(y_log_file, "\nERROR|%s: ", s);
}

static char *clear_token(char *token) {
  token[strcspn(token, "\t\n\v\f\r ")] = 0;
  return token;
}

// EOF
