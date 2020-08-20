#ifndef DISPLAY_H
#define DISPLAY_H

#include <cairo/cairo.h>

#include "opts.h"

void display_pango_markup(cairo_t *cr, const char *filename,
                          double x1, double y1, double x2, double y2,
                          const struct opts *opts);

int display_source_code(cairo_t *cr, const char *filename,
                        double x1, double y1, double x2, double y2,
                        const struct opts *opts);

void display_png(cairo_t *cr, const char *filename,
                 double x1, double y1, double x2, double y2,
                 const struct opts *opts);

void display_svg(cairo_t *cr, const char *filename,
                 double x1, double y1, double x2, double y2,
                 const struct opts *opts);

#endif
