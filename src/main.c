#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <pango/pangocairo.h>

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

    PangoLayout *layout;

    cairo_surface_t *surface = cairo_pdf_surface_create(OUTPUT, PAGE_WIDTH, PAGE_HEIGHT);
    cairo_t *cr = cairo_create(surface);

    cairo_select_font_face(cr, TYPEFACE, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, FONT_SIZE);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);

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
            md_parse(buffer, readc, &parser, cr);
        }
        fclose(file);

        cairo_show_page(cr);
    }

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
