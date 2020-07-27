#include <stdio.h>

#include "handlers.h"
#include "config.h"

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

    cairo_surface_t *surface = cairo_pdf_surface_create(OUTPUT, PAGE_WIDTH, PAGE_HEIGHT);
    cairo_t *cr = cairo_create(surface);

    cairo_set_font_size(cr, FONT_SIZE);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);

    char buffer[BUFFER_SIZE];
    size_t readc;
    while ((readc = fread(buffer, sizeof(char), BUFFER_SIZE, stdin))) {
        md_parse(buffer, readc, &parser, cr);
    }

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
