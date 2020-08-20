#include <libconfig.h>

#include "opts.h"
#include "util.h"

struct opts parse_opts(const struct opts *defaults) {
    struct opts opts = *defaults;

    FILE *specfile = fopen("Dyvofile", "r");
    if (specfile == NULL) {
        return opts;
    }

    config_t cfg;
    config_init(&cfg);
    if (!config_read(&cfg, specfile)) {
        panic("Malformed dyfofile (%s:%d): %s\n",
              config_error_file(&cfg),
              config_error_line(&cfg),
              config_error_text(&cfg));
    }
    fclose(specfile);

    config_lookup_string(&cfg, "output", &opts.output);

    return opts;
}
