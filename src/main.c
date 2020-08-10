#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <cairo/cairo-pdf.h>

#include "main.h"
#include "layout.h"

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
        layout(cr, files[i]->d_name);
        cairo_show_page(cr);
    }

    free(files);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
