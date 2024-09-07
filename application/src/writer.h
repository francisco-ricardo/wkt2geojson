/*
 * writer.h
 *
 * Interface for the writer module, used to generate GeoJSON strings
 * from parsed WKT data.
 */
#include <stdio.h>

#ifndef INCLUDED_WRITER_H
#define INCLUDED_WRITER_H

/*
 * Formats and allocates a string dynamically.
 * Returns the length of the formatted string or -1 in case of error.
 */
int write_string(char **strp, const char *fmt, ...);


/*
 * Generates the header for a GeoJSON FeatureCollection.
 * Returns a dynamically allocated string.
 */
char* header(void);


/*
 * Generates the footer for a GeoJSON FeatureCollection.
 * Returns a dynamically allocated string.
 */
char* footer(void);


/*
 * Creates a GeoJSON Point feature from the given coordinates.
 * Returns a dynamically allocated string.
 */
char* to_geojson_point(const char* coordinates);


/*
 * Creates a GeoJSON LineString feature from the given coordinates.
 * Returns a dynamically allocated string.
 */
char* to_geojson_linestring(const char* coordinates);


/*
 * Creates a GeoJSON Polygon feature from the given coordinates list.
 * Returns a dynamically allocated string.
 */
char* to_geojson_polygon(const char* coordinates_list);

#endif  /* INCLUDED_WRITER_H */

// EOF
