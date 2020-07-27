#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "handlers.h"

cairo_surface_t *surface;
cairo_t *cr;
char buffer[1000];
size_t readc;

int main() {
    MD_PARSER parser = {
        0,
        MD_DIALECT_COMMONMARK,
        enter_block,
        leave_block,
        enter_span,
        leave_span,
        text,
        NULL,
        NULL
    };

    surface = cairo_pdf_surface_create("cairo.pdf", 500, 500);
    cr = cairo_create(surface);

    cairo_select_font_face(cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 32.0);
    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);

    while ((readc = fread(buffer, 1, 1000, stdin))) {
        md_parse(buffer, readc, &parser, cr);
    }

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
