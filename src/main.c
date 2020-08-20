#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <cairo/cairo-pdf.h>

#include "layout.h"
#include "util.h"
#include "opts.h"

int main() {
    struct opts opts = parse_opts("Dyvofile");

    cairo_surface_t *surface = cairo_pdf_surface_create(opts.output,
                               PAGE_WIDTH, PAGE_HEIGHT);
    cairo_t *cr = cairo_create(surface);

    struct dirent **files;
    const size_t filec = scandir(".", &files, not_hidden_or_dyvofile, alphasort);
    for (size_t i = 0; i < filec; ++i) {
        if (!strcmp(files[i]->d_name, opts.output)) {
            free(files[i]);
            continue;
        }
        printf("Processing %s\n", files[i]->d_name);
        layout(cr, files[i]->d_name);
        cairo_show_page(cr);

        free(files[i]);
    }

    free(files);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
