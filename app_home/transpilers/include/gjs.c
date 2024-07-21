/** 
 * GJS - GeoJSON Package
 * 
 * Implementation of the functions declared in the header file (`gjs.h` file).
 * 
 * More information can be found in the header file.
 * 
*/


#include <string.h>
#include <stdlib.h>

#include "gjs.h"


/**
 * Functions definitions for the `gjs_coord_node_t`.
*/

gjs_coord_node_t *gjs_coord_node_create(double x, double y) {
    gjs_coord_node_t *p = (gjs_coord_node_t *) malloc(sizeof(gjs_coord_node_t));
    p->next = NULL;
    p->x = x;
    p->y = y;
    return p;
}


void gjs_coord_node_destroy(gjs_coord_node_t *coord_node) {
    gjs_coord_node_t *node = coord_node;
    gjs_coord_node_t *node_tmp;

    while (node != NULL) {
        node_tmp = node;
        node = node->next;
        free(node_tmp);
        node_tmp = NULL;
    }
}


/**
 * Functions definitions for the `gjs_coord_list_t`.
*/

gjs_coord_list_t *gjs_coord_list_create(void) {
    gjs_coord_list_t *l = (gjs_coord_list_t *) malloc(sizeof(gjs_coord_list_t));
    l->count = 0;
    l->head = NULL;
    l->tail = NULL;
    return l;
}


int gjs_coord_list_is_empty(gjs_coord_list_t *coord_list) {
    return (coord_list->head == NULL);
}


void gjs_coord_list_push(gjs_coord_list_t *coord_list, gjs_coord_node_t *coord_node) {
    if(gjs_coord_list_is_empty(coord_list)) {
        coord_list->head = coord_list->tail = coord_node;
    }
    else {
        coord_list->tail->next = coord_node;
        coord_list->tail = coord_node;
    }
    coord_list->count++;
}


void gjs_coord_list_print(gjs_coord_list_t *coord_list, FILE *out_file) {
        fprintf(out_file, "\n\"coordinates\": [");
        size_t count = 1;
        gjs_coord_node_t *coord_node = coord_list->head;
        while (coord_node != NULL) {
            if (count == 1) {
                fprintf(out_file, "\n[%f, %f]", coord_node->x, coord_node->y);
            }
            else {
                fprintf(out_file, ",\n[%f, %f]", coord_node->x, coord_node->y);
            }
            coord_node = coord_node->next;
            ++count;
        }
        fprintf(out_file, "\n]");
}


void gjs_coord_list_destroy(gjs_coord_list_t *coord_list) {
    gjs_coord_node_t *head = coord_list->head;
    gjs_coord_node_destroy(head);  // Destroy the nodes
    free(coord_list);              // Destroy the list
    coord_list = NULL;
}


/**
 * Functions definitions for the `gjs_geom_t`.
*/

gjs_geom_t *gjs_geom_create(void) {
    gjs_geom_t *g = (gjs_geom_t *) malloc(sizeof(gjs_geom_t));
    g->coord_list = NULL;
    return g;    
}


const char *gjs_geom_type_get(gjs_geom_type_t geom_type) {
    if (geom_type == Point) {
        return "Point";
    }
    else if (geom_type == LineString) {
        return "LineString";
    }
    else if (geom_type == Polygon) {
        return "Polygon";
    }
    return "Unknown";
}


void gjs_geom_print(gjs_geom_t *geom, FILE *out_file) {
    fprintf(out_file, "\n\"geometry\": {");
    fprintf(out_file, "\n\"type\": \"%s\",", gjs_geom_type_get(geom->geom_type));
    gjs_coord_list_print(geom->coord_list, out_file);
    fprintf(out_file, "\n}");
}


void gjs_geom_destroy(gjs_geom_t *geom) {
    gjs_coord_list_destroy(geom->coord_list);   // Destroy the list
    free(geom);                                 // Destroy geom
    geom = NULL;
}


/**
 * Functions definitions for `gjs_prop_node_t`.
 * 
*/

gjs_prop_node_t *gjs_prop_node_create(const char *name, const char *value) {
    gjs_prop_node_t *node = (gjs_prop_node_t *) malloc(sizeof(gjs_prop_node_t));
    node->name = name;
    node->value = value;
    node->next = NULL;
    return node;
}


void gjs_prop_node_destroy(gjs_prop_node_t *prop_node) {
    gjs_prop_node_t *node = prop_node;
    gjs_prop_node_t *node_tmp;

    while (node != NULL) {
        node_tmp = node;
        node = node->next;
        free(node_tmp);
        node_tmp = NULL;
    }
}


/**
 * Functions definitions for `gjs_prop_list_t`.
*/

gjs_prop_list_t *gjs_prop_list_create(void) {
    gjs_prop_list_t *prop_list = (gjs_prop_list_t *) malloc(sizeof(gjs_prop_list_t));
    prop_list->count = 0;
    prop_list->head = NULL;
    prop_list->tail = NULL;
    return prop_list;
}


int gjs_prop_list_is_empty(gjs_prop_list_t *prop_list) {
    return (prop_list->head == NULL);
}


void gjs_prop_list_push(gjs_prop_list_t *prop_list, gjs_prop_node_t *prop_node) {
    if(gjs_prop_list_is_empty(prop_list)) {
        prop_list->head = prop_list->tail = prop_node;
    }
    else {
        prop_list->tail->next = prop_node;
        prop_list->tail = prop_node;
    }
    prop_list->count++;
}


void gjs_prop_list_print(gjs_prop_list_t *prop_list, FILE *out_file) {
        fprintf(out_file, "\n\"properties\": {");
        size_t count = 1;
        gjs_prop_node_t *prop_node = prop_list->head;
        while (prop_node != NULL) {
            if (count == 1) {
                fprintf(out_file, "\n\"%s\": \"%s\"", prop_node->name, prop_node->value);
            }
            else {
                fprintf(out_file, ",\n\"%s\": \"%s\"", prop_node->name, prop_node->value);
            }
            prop_node = prop_node->next;
            ++count;
        }
        fprintf(out_file, "\n}");
}


void gjs_prop_list_destroy(gjs_prop_list_t *prop_list) {
    gjs_prop_node_t *head = prop_list->head;
    gjs_prop_node_destroy(head);          // Destroy the nodes
    free(prop_list);                      // Destroy the list
    prop_list = NULL;
}


/** 
 * Functions definitions for `gjs_feat_node_t`.
*/

gjs_feat_node_t *gjs_feat_node_create(gjs_geom_t *geom, gjs_prop_list_t *prop_list) {
    gjs_feat_node_t *feat_node = (gjs_feat_node_t *) malloc(sizeof(gjs_feat_node_t));
    feat_node->next = NULL;
    feat_node->geom = geom;
    feat_node->prop_list = prop_list;
    return feat_node;
}


void gjs_feat_node_destroy(gjs_feat_node_t *feat_node) {
    gjs_feat_node_t *node = feat_node;
    gjs_feat_node_t *node_tmp;

    while (node != NULL) {
        node_tmp = node;
        node = node->next;
        gjs_geom_destroy(node_tmp->geom);
        gjs_prop_list_destroy(node_tmp->prop_list);
        free(node_tmp);
        node_tmp = NULL;
    }
}


void gjs_feat_node_print(gjs_feat_node_t *feat_node, FILE *out_file) {
    fprintf(out_file, "\n\"type\": \"Feature\",");
    gjs_geom_print(feat_node->geom, out_file);
    fprintf(out_file, ",");
    gjs_prop_list_print(feat_node->prop_list, out_file);
    fprintf(out_file, "}");
}


/** 
 * Functions definitions for `gjs_feat_list_t`.
*/

gjs_feat_list_t *gjs_feat_list_create(void) {
    gjs_feat_list_t *f = (gjs_feat_list_t *) malloc(sizeof(gjs_feat_list_t));
    f->count = 0;
    f->head = NULL;
    f->tail = NULL;
    return f;
}


int gjs_feat_list_is_empty(gjs_feat_list_t *feat_list) {
    return (feat_list->head == NULL);
}


void gjs_feat_list_push(gjs_feat_list_t *feat_list, gjs_feat_node_t *feat_node) {
    if (gjs_feat_list_is_empty(feat_list)) {
        feat_list->head = feat_list->tail = feat_node;
    }
    else {
        feat_list->tail->next = feat_node;
        feat_list->tail = feat_node;
    }
    feat_list->count++;
}


void gjs_feat_list_print(gjs_feat_list_t *feat_list, FILE *out_file) {
    fprintf(out_file, "{\n");
    fprintf(out_file, "\"type\": \"FeatureCollection\",");
    fprintf(out_file, "\n\"features\": [");

    size_t count = 1;
    gjs_feat_node_t *feat_node = feat_list->head;    
    while (feat_node != NULL) {
        if (count == 1) {
            fprintf(out_file, "{");
        }
        else {
            fprintf(out_file, ",\n{");
        }
        //fprintf(out_file, "\n\"type\": \"Feature\",");
        //gjs_geom_print(feat_node->geom, out_file);
        //fprintf(out_file, ",");
        //gjs_prop_list_print(feat_node->prop_list, out_file);
        //fprintf(out_file, "}");

        gjs_feat_node_print(feat_node, out_file);


        feat_node = feat_node->next;
        ++count;
    }
    fprintf(out_file, "\n]");
    fprintf(out_file, "\n}\n");
}


void gjs_feat_list_destroy(gjs_feat_list_t *feat_list) {
    gjs_feat_node_destroy(feat_list->head);  // Destroy the nodes
    free(feat_list);                         // Destroy the list
    feat_list = NULL;
}


// void gjs_feat_list_print2(gjs_feat_list_t *feat_list, FILE *out_file) {

//     cJSON *geom_type = NULL;
//     geom_type = cJSON_CreateString("Point");

//     cJSON *json = cJSON_CreateObject();
//     cJSON_AddItemToObject(json, "type", geom_type);

//     cJSON *coordinates = cJSON_CreateArray();
//     gjs_coord_node_t *coord_node = feat_list->head->geom->coordinates->head;

//     while (coord_node != NULL) {

//         cJSON *row = cJSON_CreateArray();    
//         cJSON *x = cJSON_CreateNumber(coord_node->x);
//         cJSON *y = cJSON_CreateNumber(coord_node->y);
//         cJSON_AddItemToArray(row, x);
//         cJSON_AddItemToArray(row, y);

        
//         cJSON_AddItemToArray(coordinates, row);

//         fprintf(out_file, "\nX: %f Y: %f", coord_node->x, coord_node->y);

//         coord_node = coord_node->next;       

//     }

//     cJSON_AddItemToObject(json, "coordinates", coordinates);

//     char *string = cJSON_Print(json);
//     fprintf(out_file, "\n%s", string);

//     /** Cleanup */
//     cJSON_Delete(json);
//     //cJSON_Delete(coordinates);
//     free(string);
// }


/* EOF */
