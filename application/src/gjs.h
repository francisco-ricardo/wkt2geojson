/**
 * GJS - GeoJSON Package
 * 
 * GeoJSON is a geospatial data interchange format based on JavaScript 
 * Object Notation (JSON).
 * 
 * The purpose of the package is to provide the data structure and  
 * the functions for generating and handling data in GeoJSON format.
 * 
 * The data structure chosen was Singly Linked List.
 * 
 * The struct and the function names start with a `gjs` prefix.
 * 
 * The standard functions are defined like below:
 *   - `gjs_*_create`: alloc the memory resources for the data structure.
 *   - `gjs_*_is_empty: predicate function to check if the list is empty.
 *   - `gjs_*_push: add a node to the list.
 *   - `gjs_*_print: print the data in GeoJSON format into the file specified.
 *   - `gjs_*_destroy`: free the memory resources allocated by create function.
 * 
 * The objects allocated with the create functions must be freed 
 * using the appropriate destroy functions.
 * 
 * The relationship of objects forms a chained structure as illustrated below.
 * 
 *                                   --> gjs_geom_t --> gjs_coord_list_t --> gjs_coord_node_t
 * gjs_feat_list_t --> gjs_feat_node  
 *                                   --> gjs_prop_list_t --> gjs_prop_node_t
 * 
 * Some functions (e.g. gjs_*_print and gjs_*_destroy) will traverse all data structures 
 * to the right of the calling object.
 * 
 * The `docs/gjs.drawio` diagram shows more information about the relationship
 * of the objects.
 *  
*/


#include <stdio.h>


#ifndef INCLUDED_GJS_H
#define INCLUDED_GJS_H


/** `gjs_coord_node_t`:
 *  It is the node of the `gjs_coord_list_t` linked list.
*/
struct gjs_coord_node_t {
    double x;
    double y;
    struct gjs_coord_node_t *next;
};
typedef struct gjs_coord_node_t gjs_coord_node_t;

gjs_coord_node_t *gjs_coord_node_create(double x, double y);
void gjs_coord_node_destroy(gjs_coord_node_t *coord_node);


/** `gjs_coord_list_t`: 
 *  It is the linked list for the `coordinates` GeoJSON member.
 */
struct gjs_coord_list_t {
    gjs_coord_node_t *head;
    gjs_coord_node_t *tail;
    size_t count;
};
typedef struct gjs_coord_list_t gjs_coord_list_t;

gjs_coord_list_t *gjs_coord_list_create(void);
int gjs_coord_list_is_empty(gjs_coord_list_t *coord_list);
void gjs_coord_list_push(gjs_coord_list_t *coord_list, gjs_coord_node_t *coord_node);
void gjs_coord_list_print(gjs_coord_list_t *coord_list, FILE *out_file);
void gjs_coord_list_destroy(gjs_coord_list_t *coord_list);


/**
 * `gjs_geom_t`:
 * It is the data structure for `geometry` GeoJSON member.
*/

/** Defines the possible types for geometries. */
typedef enum {
  Point,
  LineString,
  Polygon
} gjs_geom_type_t; 

struct gjs_geom_t {
    gjs_geom_type_t geom_type;
    gjs_coord_list_t *coord_list;
};
typedef struct gjs_geom_t gjs_geom_t;

gjs_geom_t *gjs_geom_create(void);
const char *gjs_geom_type_get(gjs_geom_type_t geom_type);
void gjs_geom_print(gjs_geom_t *geom, FILE *out_file);
void gjs_geom_destroy(gjs_geom_t *geom);


/**
 * `gjs_prop_node_t`:
 * It is the node of the `gjs_prop_list_t` linked list.
*/
struct gjs_prop_node_t {
    const char *name;
    const char *value;
    struct gjs_prop_node_t *next;
};
typedef struct gjs_prop_node_t gjs_prop_node_t;

gjs_prop_node_t *gjs_prop_node_create(const char *name, const char *value);
void gjs_prop_node_destroy(gjs_prop_node_t *prop_node);


/**
 * `gjs_prop_list_t`:
 * It is the linked list for the `properties` GeoJSON member.
*/
struct gjs_prop_list_t {
    gjs_prop_node_t *head;
    gjs_prop_node_t *tail;
    size_t count;
};
typedef struct gjs_prop_list_t gjs_prop_list_t;

gjs_prop_list_t *gjs_prop_list_create(void);
int gjs_prop_list_is_empty(gjs_prop_list_t *prop_list);
void gjs_prop_list_push(gjs_prop_list_t *prop_list, gjs_prop_node_t *prop_node);
void gjs_prop_list_print(gjs_prop_list_t *prop_list, FILE *out_file);
void gjs_prop_list_destroy(gjs_prop_list_t *prop_list);


/** 
 * `gjs_feat_node_t`:
 * It is the node of the `gjs_feat_list_t` linked list. 
*/
struct gjs_feat_node_t {
    gjs_geom_t *geom;
    gjs_prop_list_t *prop_list;
    struct gjs_feat_node_t *next;
};
typedef struct gjs_feat_node_t gjs_feat_node_t;

gjs_feat_node_t *gjs_feat_node_create(gjs_geom_t *geom, gjs_prop_list_t *prop_list);
void gjs_feat_node_destroy(gjs_feat_node_t *feat_node);
void gjs_feat_node_print(gjs_feat_node_t *feat_node, FILE *out_file);


/** 
 * `gjs_feat_list_t`:
 * It is the linked list for the `features` GeoJSON member.
*/
struct gjs_feat_list_t {
    gjs_feat_node_t *head;
    gjs_feat_node_t *tail;
    size_t count;
};
typedef struct gjs_feat_list_t gjs_feat_list_t;

gjs_feat_list_t *gjs_feat_list_create(void);
int gjs_feat_list_is_empty(gjs_feat_list_t *feat_list);
void gjs_feat_list_push(gjs_feat_list_t *feat_list, gjs_feat_node_t *feat_node);
void gjs_feat_list_print(gjs_feat_list_t *feat_list, FILE *out_file);
void gjs_feat_list_destroy(gjs_feat_list_t *feat_list);


#endif // ifndef INCLUDED_GJS_H

// EOF
