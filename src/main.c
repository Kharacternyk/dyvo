#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <pango/pangocairo.h>
#include <cairo/cairo-pdf.h>

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
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);

    PangoLayout *layout = pango_cairo_create_layout(cr);
    PangoFontDescription *desc = pango_font_description_from_string("Monospace 27");
    pango_layout_set_font_description(layout, desc);
    pango_layout_set_width(layout, 20);
    pango_layout_set_markup(layout, "<b> bold </b> <u> is </u> <i> nice </i>", -1);
    cairo_show_page(cr);
    pango_font_description_free(desc);

    struct dirent **files;
    size_t filec = scandir(".", &files, NULL, alphasort);
    for (size_t i = 0; i < filec; ++i) {
        if (files[i]->d_name[0] == '.' || (!strcmp(files[i]->d_name, OUTPUT))) {
            continue;
        }
        printf("Processing %s\n", files[i]->d_name);

        char buffer[BUFFER_SIZE];
        size_t readc;
        FILE *file = fopen(files[i]->d_name, "r");
        while ((readc = fread(buffer, sizeof(char), BUFFER_SIZE, file))) {
            md_parse(buffer, readc, &parser, layout);
        }
        fclose(file);

        pango_cairo_show_layout(cr, layout);
        cairo_show_page(cr);
    }

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
