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
        panic("Malformed dyvofile (line %d): %s\n",
              config_error_line(&cfg),
              config_error_text(&cfg));
    }
    fclose(specfile);

    config_set_option(&cfg, CONFIG_OPTION_AUTOCONVERT, CONFIG_TRUE);

    config_lookup_string(&cfg, "output", &opts.output);
    config_lookup_float(&cfg, "page.width", &opts.page_width);
    config_lookup_float(&cfg, "page.height", &opts.page_height);

    return opts;
}
