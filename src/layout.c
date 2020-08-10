#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <cairo/cairo.h>
#include <sys/stat.h>

#include "layout.h"
#include "display.h"
#include "util.h"

#define PAGE_DEF_MARGIN 10

static void layout_file(cairo_t *cr, const char *filename) {
    char *data = fread_till_end(filename);
    display_pango_markup(cr, data,
                         PAGE_DEF_MARGIN, PAGE_DEF_MARGIN,
                         PAGE_WIDTH - PAGE_DEF_MARGIN, PAGE_HEIGHT - PAGE_DEF_MARGIN);
    free(data);
}

static void layout_chain(cairo_t *cr, size_t filec,
                         struct dirent **files, FILE *spec) {
    for (size_t i = 0; i < filec; ++i) {
        double x1, y1, x2, y2;
        if (fscanf(spec, "%lf %lf %lf %lf", &x1, &y1, &x2, &y2) < 4) {
            return;
        }
        char *data = fread_till_end(files[i]->d_name);
        display_pango_markup(cr, data, x1, y1, x2, y2);
        free(data);
    }
}


static int nothidden(const struct dirent *file) {
    return file->d_name[0] != '.';
}

void layout(cairo_t *cr, const char *filename) {
    struct stat st;
    stat(filename, &st);
    if (S_ISDIR(st.st_mode)) {
        chdir(filename);
        FILE *spec = fopen(".dyvo", "r");
        struct dirent **files;
        const size_t filec = scandir(".", &files, nothidden, alphasort);
        layout_chain(cr, filec, files, spec);
        fclose(spec);
        free(files);
        chdir("..");
    } else {
        layout_file(cr, filename);
    }
}
