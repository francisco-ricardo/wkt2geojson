/**
 * Features Transpiler
 * 
 * The transpiler reads a `FEATURES` file and translates it into a 
 * `GeoJSON` file. 
 * 
 * The `FEATURES` is a file that is part of the ODB++ standard.
 * The file consists of the geometry data of the ODB++ layers.
 * The data can be used to analysis or dfm actions on Genesis software.
 * 
 * The `features` program is the entry point for the transpilation.
 * It deals with the command line arguments (input file, log file, 
 * and output file) and calls the `feat_transpile` function defined on 
 * the Features Parser (`features.y`).
 * The LR parser header (wkt2geojson.tab.h`) is a dependency for the transpiler.
 * 
*/

#include <stdio.h>
#include <stdlib.h>

#include "wkt2geojson.tab.h"

  
int main(int argc, char **argv) {

    FILE *in_file;
    FILE *out_file;
    FILE *log_file;

    int status = 1;

    /** Args validation */
    if (argc < 4) {
        fprintf(stderr, "\nERROR|Usage: wkt2geojson INFILE LOGFILE OUTFILE\n");
        exit(1);
    }

    /** Open log file */
    log_file = fopen(argv[2], "a");
    if (log_file == NULL) {
        fprintf(stderr, "\nERROR|Cannot open log file %s\n", argv[2]);
        exit(1);
    }
    //log_file = stderr;

    /** Open input file */
    in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        fprintf(log_file, "\nERROR|Cannot open input file %s", argv[1]);
        fclose(log_file); 
        exit(1);
    }

    /** Open output file */
    out_file = fopen(argv[3], "w");
    if (out_file == NULL) {
        fprintf(log_file, "\nERROR|Cannot open output file %s", argv[3]);
        fclose(log_file);
        fclose(in_file);
        exit(1);
    }
    
   /** Run the parser */
    if (!transpile(in_file, log_file, out_file)) {
        status = 0;
        fprintf(log_file, "\nINFO|File %s transpiled to %s", argv[1], argv[3]);        
    }
    else {
        fprintf(log_file, "\nERROR|Cannot transpile file %s", argv[1]);
        status = 1;
    }

    /** Cleanup */
    fclose(log_file);
    fclose(in_file);    
    fclose(out_file);
 
    return status;
}

// EOF
