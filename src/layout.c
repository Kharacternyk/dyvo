#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <cairo/cairo.h>
#include <sys/stat.h>

#include "layout.h"
#include "display.h"
#include "util.h"

#define PAGE_DEF_MARGIN 10

static void layout_file(cairo_t *cr, const char *filename,
                        double x1, double y1, double x2, double y2,
                        const struct opts *defaults) {
    const char *ext = strstr(filename, ".");
    if (ext == NULL || !strcmp(ext, ".txt")) {
        display_pango_markup(cr, filename, x1, y1, x2, y2, defaults);
        return;
    }
    if (!strcmp(ext, ".png")) {
        display_png(cr, filename, x1, y1, x2, y2, defaults);
        return;
    }
    if (!strcmp(ext, ".svg")) {
        display_svg(cr, filename, x1, y1, x2, y2, defaults);
        return;
    }
    if (!display_source_code(cr, filename, x1, y1, x2, y2, defaults)) {
        return;
    }

    panic("Could not process file %s (unknown extension: %s).\n",
          filename, ext);
}

static void layout_dir(cairo_t *cr, const char *filename, const struct opts *defaults) {
    chdir(filename);
    FILE *spec;

    /***INDENT-OFF***/
    if (!((spec = fopen("Dyvofile", "r")) ||
          (spec = fopen("dyvofile", "r")) ||
          (spec = fopen("dyvo.yaml", "r")) ||
          (spec = fopen("Dyvo.yaml", "r")))) {
        panic("Layout file (%s/.dyvo) was not found.\n", filename);
    }
    /***INDENT-ON***/

    struct dirent **files;
    const size_t filec = scandir(".", &files, not_hidden_or_dyvofile, alphasort);

    for (size_t i = 0; i < filec; ++i) {
        double x1, y1, x2, y2;
        if (fscanf(spec, "%lf%lf%lf%lf", &x1, &y1, &x2, &y2) < 4) {
            panic("Line #%lu of %s/.dyvo is malformed.\n",
                  (unsigned long) i + 1, filename);
        }
        x1 *= defaults->page_width, x2 *= defaults->page_width;
        y1 *= defaults->page_height, y2 *= defaults->page_height;
        layout_file(cr, files[i]->d_name, x1, y1, x2, y2, defaults);

        free(files[i]);
    }

    fclose(spec);
    free(files);
    chdir("..");
}

void layout(cairo_t *cr, const char *filename, const struct opts *defaults) {
    struct stat st;
    stat(filename, &st);
    if (S_ISDIR(st.st_mode)) {
        layout_dir(cr, filename, defaults);
    } else {
        layout_file(cr, filename,
                    PAGE_DEF_MARGIN, PAGE_DEF_MARGIN,
                    defaults->page_width - PAGE_DEF_MARGIN,
                    defaults->page_height - PAGE_DEF_MARGIN, defaults);
    }
}
