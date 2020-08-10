#include <dirent.h>
#include <stdlib.h>
#include <cairo/cairo.h>

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

void layout(cairo_t *cr, const char *filename) {
    char *data = fread_till_end(filename);
    display_pango_markup(cr, data, def1.x1, def1.y1, def1.x2, def1.y2);
    free(data);
}
