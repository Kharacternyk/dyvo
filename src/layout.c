#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <cairo/cairo.h>
#include <sys/stat.h>

#include "layout.h"
#include "display.h"
#include "util.h"

#define PAGE_MARGIN 10

typedef struct layout_t {
    double x1, y1, x2, y2;
    struct layout_t *next;
} layout_t;

static layout_t def1 = {
    PAGE_MARGIN, PAGE_MARGIN,
    PAGE_WIDTH - PAGE_MARGIN, PAGE_HEIGHT - PAGE_MARGIN,
    NULL
};

static void layout_file(cairo_t *cr, const char *filename) {
    char *data = fread_till_end(filename);
    display_pango_markup(cr, data, def1.x1, def1.y1, def1.x2, def1.y2);
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
