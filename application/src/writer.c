/*
 * writer.c
 *
 * This module provides functions to generate GeoJSON strings
 * based on the parsed WKT data. The `writer` is used by the parser
 * to create the final GeoJSON output.
 */

#include "writer.h"

#include <stdarg.h>
#include <stdlib.h>


/*
 * Creates and returns the header for the GeoJSON file.
 * This function returns a string containing the start of a GeoJSON
 * FeatureCollection, which includes the opening of the features
 * array.
 *
 * Returns:
 *   A dynamically allocated string containing the GeoJSON header.
 */
char* header(void) {
    char* result;
    write_string(&result, "%s",
        "{\n\"type\": \"FeatureCollection\",\n\"features\": [");
    return result;
}


/*
 * Creates and returns the footer for the GeoJSON file.
 * This function returns a string containing the closing braces of the
 * features array and the entire FeatureCollection object.
 *
 * Returns:
 *   A dynamically allocated string containing the GeoJSON footer.
 */
char* footer(void) {
    char* result;
    write_string(&result, "%s", "\n]\n}\n");
    return result;
}


/*
 * Formats and allocates a string dynamically using a variable number
 * of arguments.
 * This function uses `vsnprintf` to format the string according to the
 * provided format and arguments, and allocates enough memory to store
 * the result.
 *
 * Parameters:
 *   strp - Pointer to a char* where the resulting string will be stored.
 *   fmt  - Format string similar to printf.
 *   ...  - Additional arguments that correspond to the format specifiers.
 *
 * Returns:
 *   The length of the formatted string (excluding the null terminator),
 *   or -1 if an error occurs.
 */
int write_string(char **strp, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    int len = vsnprintf(NULL, 0, fmt, ap);
    if (len < 0) {
        va_end(ap);
        return -1;
    }

    *strp = malloc((size_t)len + 1);
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


/*
 * Creates and returns a GeoJSON Feature with Point geometry.
 * The coordinates are inserted into the appropriate place in the
 * GeoJSON structure for a Point.
 *
 * Parameters:
 *   coordinates - A string representing the coordinates of the point.
 *
 * Returns:
 *   A dynamically allocated string containing the GeoJSON representation
 *   of a Point feature.
 */
char* to_geojson_point(const char* coordinates) {
    char* result;
    write_string(&result,
        "{\"type\": \"Feature\", \"geometry\": {\"type\": \"Point\", \"coordinates\": %s}}",
        coordinates);
    return result;
}


/*
 * Creates and returns a GeoJSON Feature with LineString geometry.
 * The coordinates are inserted into the appropriate place in the
 * GeoJSON structure for a LineString.
 *
 * Parameters:
 *   coordinates - A string representing the coordinates of the LineString.
 *
 * Returns:
 *   A dynamically allocated string containing the GeoJSON representation
 *   of a LineString feature.
 */
char* to_geojson_linestring(const char* coordinates) {
    char* result;
    write_string(&result,
        "{\"type\": \"Feature\", \"geometry\": {\"type\": \"LineString\", \"coordinates\": [%s]}}",
        coordinates);
    return result;
}


/*
 * Creates and returns a GeoJSON Feature with Polygon geometry.
 * The coordinates list is inserted into the appropriate place in the
 * GeoJSON structure for a Polygon.
 *
 * Parameters:
 *   coordinates_list - A string representing the list of coordinates
 *                      that define the Polygon.
 *
 * Returns:
 *   A dynamically allocated string containing the GeoJSON representation
 *   of a Polygon feature.
 */
char* to_geojson_polygon(const char* coordinates_list) {
    char* result;
    write_string(&result,
        "{\"type\": \"Feature\", \"geometry\": {\"type\": \"Polygon\", \"coordinates\": [[%s]]}}",
        coordinates_list);
    return result;
}
