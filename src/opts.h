#ifndef OPTS_H
#define OPTS_H

struct opts {
    const char *output;
};

struct opts parse_opts(const struct opts *defaults);

#endif
