
#include <stdio.h>

#ifndef INCLUDED_WRITER_H
#define INCLUDED_WRITER_H

int safe_asprintf(char **strp, const char *fmt, ...);

char* header(void);

char* footer(void);

char* to_geojson_point(const char* coordinates);

char* to_geojson_linestring(const char* coordinates);

char* to_geojson_polygon(const char* coordinates_list);

#endif

// EOF
