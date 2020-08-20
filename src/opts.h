#ifndef OPTS_H
#define OPTS_H

#include <libconfig.h>

struct opts {
    const char *output;
    double page_width, page_height;

    const char *font;
    double fg_r, fg_g, fg_b;
};

void parse_opts(config_t *cfg, struct opts *opts);

#endif
