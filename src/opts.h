#ifndef OPTS_H
#define OPTS_H

struct opts {
    const char *output;
    double page_width;
    double page_height;
};

struct opts parse_opts(const struct opts *defaults);

#endif
