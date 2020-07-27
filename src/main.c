#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <md4c.h>
#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>

cairo_surface_t *surface;
cairo_t *cr;
char buffer[1000];
size_t readc;
const char *space = " ";

int enter_block(MD_BLOCKTYPE bt, void *d, void *ud) {
    cairo_move_to(cr, 10.0, 50.0);
    return 0;
}

int leave_block(MD_BLOCKTYPE bt, void *d, void *ud) {
    cairo_show_page(cr);
    return 0;
}

int enter_span(MD_SPANTYPE st, void *d, void *ud) {
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

int leave_span(MD_SPANTYPE st, void *d, void *ud) {
    cairo_select_font_face(cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    return 0;
}

int text(MD_TEXTTYPE tt, const MD_CHAR *t, MD_SIZE s, void *ud) {
    char *buf = malloc(s + 1);
    switch (tt) {
    case MD_TEXT_NORMAL:
        strncpy(buf, t, s);
        buf[s] = '\0';
        cairo_show_text(cr, buf);
        free(buf);
        break;
    case MD_TEXT_SOFTBR:
        cairo_show_text(cr, space);
        break;
    default:
        break;
    }
    return 0;
}

int main() {
    MD_PARSER parser = {
        0,
        MD_DIALECT_COMMONMARK,
        enter_block,
        leave_block,
        enter_span,
        leave_span,
        text,
        NULL,
        NULL
    };

    surface = cairo_pdf_surface_create("cairo.pdf", 500, 500);
    cr = cairo_create(surface);

    cairo_select_font_face(cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 32.0);
    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);

    while ((readc = fread(buffer, 1, 1000, stdin))) {
        md_parse(buffer, readc, &parser, NULL);
    }

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
