#include <md4c.h>

int enter_block(MD_BLOCKTYPE bt, void *d, void *layout);
int leave_block(MD_BLOCKTYPE bt, void *d, void *layout);
int enter_span(MD_SPANTYPE st, void *d, void *layout);
int leave_span(MD_SPANTYPE st, void *d, void *layout);
int text(MD_TEXTTYPE tt, const MD_CHAR *t, MD_SIZE s, void *layout);
