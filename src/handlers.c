#include <string.h>
#include <stdlib.h>

#include "handlers.h"

int enter_block(MD_BLOCKTYPE bt, void *d, void *cr) {
    cairo_move_to(cr, 10.0, 50.0);
    return 0;
}

int leave_block(MD_BLOCKTYPE bt, void *d, void *cr) {
    cairo_show_page(cr);
    return 0;
}

int enter_span(MD_SPANTYPE st, void *d, void *cr) {
    switch (st) {
    case MD_SPAN_EM:
        cairo_select_font_face(cr, "serif",
                               CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_NORMAL);
        break;
    case MD_SPAN_STRONG:
        cairo_select_font_face(cr, "serif",
                               CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        break;
    default:
        break;
    }
    return 0;
}

int leave_span(MD_SPANTYPE st, void *d, void *cr) {
    cairo_select_font_face(cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    return 0;
}

int text(MD_TEXTTYPE tt, const MD_CHAR *t, MD_SIZE s, void *cr) {
    char *buf = malloc(s + 1);
    switch (tt) {
    case MD_TEXT_NORMAL:
        strncpy(buf, t, s);
        buf[s] = '\0';
        cairo_show_text(cr, buf);
        free(buf);
        break;
    case MD_TEXT_SOFTBR:
        cairo_show_text(cr, " ");
        break;
    default:
        break;
    }
    return 0;
}
