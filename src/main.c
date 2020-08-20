#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <cairo/cairo-pdf.h>

#include "layout.h"
#include "util.h"
#include "opts.h"

int main() {
    struct opts opts = {
        .output = "dyvo.pdf",
        .page_width = 72 * 13.33,
        .page_height = 72 * 7.5,
        .font = "Serif 24",
        .fg_r = 0,
        .fg_g = 0,
        .fg_b = 0
    };

    config_t cfg;
    config_init(&cfg);
    config_set_option(&cfg, CONFIG_OPTION_AUTOCONVERT, CONFIG_TRUE);

    parse_opts(&cfg, &opts);

    cairo_surface_t *surface = cairo_pdf_surface_create(opts.output,
                               opts.page_width, opts.page_height);
    cairo_t *cr = cairo_create(surface);

    struct dirent **files;
    const size_t filec = scandir(".", &files, not_hidden_or_dyvofile, alphasort);
    for (size_t i = 0; i < filec; ++i) {
        if (!strcmp(files[i]->d_name, opts.output)) {
            free(files[i]);
            continue;
        }
        printf("Processing %s\n", files[i]->d_name);
        layout(cr, files[i]->d_name, &opts);
        cairo_show_page(cr);

        free(files[i]);
    }

    config_destroy(&cfg);
    free(files);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
