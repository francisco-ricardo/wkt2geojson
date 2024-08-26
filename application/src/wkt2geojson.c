#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "parser.tab.h"

void print_help(const char *program_name) {
    printf("Usage: %s [options]\n", program_name);
    printf("Options:\n");
    printf("  -i <file>  Specify input file (default: stdin)\n");
    printf("  -o <file>  Specify output file (default: stdout)\n");
    printf("  -h         Display this help message\n");
}


int main(int argc, char *argv[]) {
    int opt;
    char *input_file = NULL;
    char *output_file = NULL;

    while ((opt = getopt(argc, argv, "i:o:h")) != -1) {
        switch (opt) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'h':
                print_help(argv[0]);
                return 0;
            default:
                print_help(argv[0]);
                return 1;
        }
    }

    FILE *input_fp = stdin;
    FILE *output_fp = stdout;

    if (input_file) {
        input_fp = fopen(input_file, "r");
        if (!input_fp) {
            perror("Error opening input file");
            return 1;
        }
    }

    if (output_file) {
        output_fp = fopen(output_file, "w");
        if (!output_fp) {
            perror("Error opening output file");
            fclose(input_fp);
            return 1;
        }
    }

    /** Run the parser */
    int status = 1;
    if (!transpile(input_fp, output_fp)) {
        status = 0;
    }

    // Cleanup
    if (input_fp != stdin) fclose(input_fp);
    if (output_fp != stdout) fclose(output_fp);

    return status;
}
