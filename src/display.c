#include <pango/pangocairo.h>
#include <cairo/cairo.h>

#include "display.h"
#include "util.h"

void display_pango_markup(cairo_t *cr, const char *filename,
                          double x1, double y1, double x2, double y2) {
    char *data = fread_till_end(filename);

    cairo_set_source_rgb(cr, FONT_COLOR_R, FONT_COLOR_G, FONT_COLOR_B);
    cairo_move_to(cr, x1, y1);

    PangoLayout *layout = pango_cairo_create_layout(cr);
    PangoFontDescription *desc = pango_font_description_from_string(FONT_DESC);
    pango_layout_set_font_description(layout, desc);
    pango_layout_set_justify(layout, 1);
    pango_layout_set_width(layout, PANGO_SCALE * (x2 - x1));
    pango_layout_set_height(layout, PANGO_SCALE * (y2 - y1));
    pango_layout_set_markup(layout, data, -1);
    pango_cairo_show_layout(cr, layout);

    pango_font_description_free(desc);
    g_object_unref(layout);
    free(data);
}
