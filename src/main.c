#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <pango/pangocairo.h>
#include <cairo/cairo-pdf.h>

#include "config.h"

int main() {
    cairo_surface_t *surface = cairo_pdf_surface_create(OUTPUT, PAGE_WIDTH, PAGE_HEIGHT);
    cairo_t *cr = cairo_create(surface);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_move_to(cr, PAGE_HMARGIN, PAGE_VMARGIN);

    PangoLayout *layout = pango_cairo_create_layout(cr);
    PangoFontDescription *desc = pango_font_description_from_string(TYPEFACE);
    pango_font_description_free(desc);
    pango_layout_set_font_description(layout, desc);
    pango_layout_set_justify(layout, 1);
    pango_layout_set_width(layout, PANGO_SCALE * (PAGE_WIDTH - 2 * PAGE_HMARGIN));
    pango_layout_set_height(layout, PANGO_SCALE * (PAGE_HEIGHT - 2 * PAGE_VMARGIN));

    struct dirent **files;
    size_t filec = scandir(".", &files, NULL, alphasort);
    for (size_t i = 0; i < filec; ++i) {
        if (files[i]->d_name[0] == '.' || (!strcmp(files[i]->d_name, OUTPUT))) {
            continue;
        }
        printf("Processing %s\n", files[i]->d_name);

        char buffer[BUFFER_SIZE];
        FILE *file = fopen(files[i]->d_name, "r");
        size_t readc = fread(buffer, sizeof(char), BUFFER_SIZE, file);
        fclose(file);

        pango_layout_set_markup(layout, buffer, readc);
        pango_cairo_show_layout(cr, layout);
        cairo_show_page(cr);
    }

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
