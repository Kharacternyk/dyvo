#include <md4c.h>
#include <stdio.h>
#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>

int enter_block(MD_BLOCKTYPE bt, void *d, void *ud) {
    return 0;
}

int leave_block(MD_BLOCKTYPE bt, void *d, void *ud) {
    return 0;
}

int enter_span(MD_SPANTYPE st, void *d, void *ud) {
    return 0;
}

int leave_span(MD_SPANTYPE st, void *d, void *ud) {
    return 0;
}

int text(MD_TEXTTYPE tt, const MD_CHAR *t, MD_SIZE s, void *ud) {
    fwrite(t, 1, s, stdout);
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

    MD_CHAR *data = "Blah *Italics* Blah *BOLD*                ";
    md_parse(data, 30, &parser, NULL);

    cairo_surface_t *surface =
        cairo_pdf_surface_create ("cairo.pdf", 240, 80);
    cairo_t *cr =
        cairo_create (surface);

    cairo_select_font_face (cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size (cr, 32.0);
    cairo_set_source_rgb (cr, 0.0, 0.0, 1.0);
    cairo_move_to (cr, 10.0, 50.0);
    cairo_show_text (cr, "Hello, world");

    cairo_destroy (cr);
    cairo_surface_destroy (surface);
}
