#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>
#include <md4c.h>

int enter_block(MD_BLOCKTYPE bt, void *d, void *cr);
int leave_block(MD_BLOCKTYPE bt, void *d, void *cr);
int enter_span(MD_SPANTYPE st, void *d, void *cr);
int leave_span(MD_SPANTYPE st, void *d, void *cr);
int text(MD_TEXTTYPE tt, const MD_CHAR *t, MD_SIZE s, void *cr);
