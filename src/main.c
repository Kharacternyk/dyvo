#include <md4c.h>
#include <stdio.h>

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
}
