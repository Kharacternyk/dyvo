#ifndef __display
#define __display

#include <cairo/cairo.h>

#define FONT_DESC "Serif 24"
#define FONT_COLOR_R 0
#define FONT_COLOR_G 0
#define FONT_COLOR_B 0

void display_pango_markup(cairo_t *cr, const char *data,
                          double x1, double y1, double x2, double y2);

#endif
