#include <stdio.h>
#include <stdlib.h>

#include "gjs.h"



int main(int argc, char **argv) {

    FILE *out_file;
    FILE *log_file;
       
    /** Args validation */
    if (argc < 4) {
        fprintf(stderr, "Usage: testx INFILE LOGFILE OUTFILE \n");
        exit(1);
    }

    
    /** Open log file */
    log_file = fopen(argv[2], "a");
    if (log_file == NULL) {
        fprintf(stderr, "\nERROR: Cannot open log file %s\n", argv[2]);
        exit(1);
    }


    /** Open output file */
    out_file = fopen(argv[3], "w");
    if (out_file == NULL) {
        fprintf(log_file, "\nERROR: Cannot open output file %s\n", argv[3]);
        exit(1);
    }

    /** Create the Features List */
    gjs_feat_list_t *feat_list = gjs_feat_list_create(); 
    for (size_t i = 0; i < 3; i++) {
        if (i == 0) {
            gjs_geom_t *geom = gjs_geom_create();
            geom->geom_type = Polygon;
            gjs_coord_list_t *coord_list = gjs_coord_list_create();
            geom->coord_list = coord_list;            
            gjs_coord_list_push(coord_list, gjs_coord_node_create(100.0, 50.0));
            gjs_coord_list_push(coord_list, gjs_coord_node_create(101.0, 51.0));
            gjs_coord_list_push(coord_list, gjs_coord_node_create(102.0, 52.0));

            gjs_prop_list_t *prop_list = gjs_prop_list_create();
            gjs_prop_node_t *prop_node = gjs_prop_node_create(".nomenclature", "true");
            gjs_prop_list_push(prop_list, prop_node);

            gjs_feat_node_t *feat_node = gjs_feat_node_create(geom, prop_list);
            gjs_feat_list_push(feat_list, feat_node);
        }
        else if (i == 1) {
            gjs_geom_t *geom = gjs_geom_create();
            geom->geom_type = Point;
            gjs_coord_list_t *coord_list = gjs_coord_list_create();
            geom->coord_list = coord_list;
            gjs_coord_list_push(coord_list, gjs_coord_node_create(200.0, 201.0));

            gjs_prop_list_t *prop_list = gjs_prop_list_create();
            gjs_prop_node_t *prop_node1 = gjs_prop_node_create(".smd", "true");
            gjs_prop_list_push(prop_list, prop_node1);
            gjs_prop_node_t *prop_node2 = gjs_prop_node_create(".bga", "true");
            gjs_prop_list_push(prop_list, prop_node2);
            gjs_prop_node_t *prop_node3 = gjs_prop_node_create("symbol", "r100.0");
            gjs_prop_list_push(prop_list, prop_node3);
            gjs_feat_node_t *feat_node = gjs_feat_node_create(geom, prop_list);
            gjs_feat_list_push(feat_list, feat_node);          
        }
        else {
            gjs_geom_t *geom = gjs_geom_create();
            geom->geom_type = Polygon;
            gjs_coord_list_t *coord_list = gjs_coord_list_create();
            geom->coord_list = coord_list;            
            gjs_coord_list_push(coord_list, gjs_coord_node_create(300.0, 80.0));
            gjs_coord_list_push(coord_list, gjs_coord_node_create(301.0, 81.0));
            gjs_coord_list_push(coord_list, gjs_coord_node_create(302.0, 82.0));
            gjs_coord_list_push(coord_list, gjs_coord_node_create(303.0, 83.0));

            gjs_prop_list_t *prop_list = gjs_prop_list_create();
            gjs_prop_node_t *prop_node = gjs_prop_node_create(".sliver_fill", "true");
            gjs_prop_list_push(prop_list, prop_node);

            gjs_feat_node_t *feat_node = gjs_feat_node_create(geom, prop_list);
            gjs_feat_list_push(feat_list, feat_node);

        }
    }

    /** Show the results */
    gjs_feat_list_print(feat_list, stderr);

    /** Cleanup */
    fclose(log_file); 
    fclose(out_file); 
    gjs_feat_list_destroy(feat_list);

    fprintf(stderr, "\n\nThat\'s all folks\n\n");
    return 0;

}
