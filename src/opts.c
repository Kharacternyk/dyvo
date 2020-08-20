#include "opts.h"
#include "util.h"

void parse_opts(config_t *cfg, struct opts *opts) {
    FILE *specfile = fopen("Dyvofile", "r");
    if (specfile == NULL) {
        return;
    }

    if (!config_read(cfg, specfile)) {
        panic("Malformed dyvofile (line %d): %s\n",
              config_error_line(cfg),
              config_error_text(cfg));
    }
    fclose(specfile);

    config_lookup_string(cfg, "output", &opts->output);
    config_lookup_float(cfg, "page.width", &opts->page_width);
    config_lookup_float(cfg, "page.height", &opts->page_height);

    config_lookup_string(cfg, "font", &opts->font);
    config_lookup_float(cfg, "fg.r", &opts->fg_r);
    config_lookup_float(cfg, "fg.g", &opts->fg_g);
    config_lookup_float(cfg, "fg.b", &opts->fg_b);
}
