#include <libconfig.h>

#include "opts.h"
#include "util.h"

struct opts parse_opts(const char *filename) {
    struct opts opts = {
        .output = "dyvo.pdf"
    };
    return opts;
}
