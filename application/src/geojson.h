
#include <stdio.h>

#ifndef INCLUDED_GEOJSON_H
#define INCLUDED_GEOJSON_H

char* to_geojson_point(const char* coordinates);

char* to_geojson_linestring(const char* coordinates);

char* to_geojson_polygon(const char* coordinates_list);

#endif // ifndef INCLUDED_GEOJSON_H

// EOF
