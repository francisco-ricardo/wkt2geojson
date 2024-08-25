#include "writer.h"

#include <stdarg.h>
#include <stdlib.h>

char* header(void) {
    char* result;
    write_string(&result,
         "{\n\"type\": \"FeatureCollection\",\n\"features\": [");
    return result;
}

char* footer(void) {
    char* result;
    //write_string(&result,
         //"\n]\n}\n");
    write_string(&result, "%s", "\n]\n}\n");
    return result;
}

int write_string(char **strp, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    int len = vsnprintf(NULL, 0, fmt, ap);
    if (len < 0) {
        va_end(ap);
        return -1;
    }

    *strp = malloc((size_t)len + 1);
    //*strp = malloc(len + 1);
    if (!*strp) {
        va_end(ap);
        return -1;
    }

    va_end(ap);

    va_start(ap, fmt);
    vsnprintf(*strp, (size_t)len + 1, fmt, ap);
    va_end(ap);

    return len;
}

char* to_geojson_point(const char* coordinates) {
    char* result;
    write_string(&result, 
        "{\"type\": \"Feature\", \"geometry\": {\"type\": \"Point\", \"coordinates\": %s}}", 
        coordinates);
    return result;
}

char* to_geojson_linestring(const char* coordinates) {
    char* result;
    write_string(&result, 
        "{\"type\": \"Feature\", \"geometry\": {\"type\": \"LineString\", \"coordinates\": [%s]}}", 
        coordinates);
    return result;
}

char* to_geojson_polygon(const char* coordinates_list) {
    char* result;
    write_string(&result, 
        "{\"type\": \"Feature\", \"geometry\": {\"type\": \"Polygon\", \"coordinates\": [[%s]]}}", 
        coordinates_list);
    return result;
}
