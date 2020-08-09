#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <cairo/cairo-pdf.h>

#include "main.h"
#include "util.h"
#include "display.h"

int main() {
    cairo_surface_t *surface = cairo_pdf_surface_create(OUTPUT, PAGE_WIDTH, PAGE_HEIGHT);
    cairo_t *cr = cairo_create(surface);

    struct dirent **files;
    const size_t filec = scandir(".", &files, NULL, alphasort);
    for (size_t i = 0; i < filec; ++i) {
        if (files[i]->d_name[0] == '.' || (!strcmp(files[i]->d_name, OUTPUT))) {
            continue;
        }
        printf("Processing %s\n", files[i]->d_name);

        char *data = fread_till_end(files[i]->d_name);
        display_pango_markup(cr, data,
                             PAGE_HMARGIN, PAGE_VMARGIN,
                             PAGE_WIDTH - PAGE_HMARGIN, PAGE_HEIGHT - PAGE_VMARGIN);
        free(data);

        cairo_show_page(cr);
    }

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
