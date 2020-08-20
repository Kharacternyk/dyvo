#ifndef OPTS_H
#define OPTS_H

#include <libconfig.h>

struct opts {
    const char *output;
    double page_width;
    double page_height;
};

void parse_opts(config_t *cfg, struct opts *opts);

#endif
