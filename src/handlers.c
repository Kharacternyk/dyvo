#include <string.h>
#include <stdlib.h>
#include <pango/pangocairo.h>
#include <pango/pango.h>

#include "handlers.h"
#include "config.h"

int enter_block(MD_BLOCKTYPE bt, void *d, void *layout) {
    return 0;
}

int leave_block(MD_BLOCKTYPE bt, void *d, void *layout) {
    return 0;
}

int enter_span(MD_SPANTYPE st, void *d, void *layout) {
    return 0;
}

int leave_span(MD_SPANTYPE st, void *d, void *layout) {
    return 0;
}

int text(MD_TEXTTYPE tt, const MD_CHAR *t, MD_SIZE s, void *layout) {
    return 0;
}
