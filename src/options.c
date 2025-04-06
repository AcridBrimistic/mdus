#include "mdus.h"

static struct config_opts {
    const char *config_path;
} cfg_opts = {
    DEFAULT_CONFIG_PATH,
};

struct server_opts opts = {
    DEFAULT_PORT,
    DEFAULT_HBTIME,
    DEFAULT_WORKING_DIRECTORY,
    DEFAULT_WORKING_DIRECTORY_LEN,
    {"https://uncivserver.xyz", NULL, NULL, NULL},
    {false, NULL, NULL, NULL},
};

static void handle_opt_port(struct server_opts *s_opts, void *v);
static void handle_opt_backup_server(struct server_opts *s_opts, void *v);

static const struct option {
    const char * const name;
    void (*optfn)(struct server_opts *, void *);
} optlist[] = {
    { "port", handle_opt_port },
    { "backup_server", handle_opt_backup_server },
    { NULL, NULL },
};

static void handle_opt_backup_server(struct server_opts *s_opts, void *v) {
    char *server = (char *) v; 
    for (int i = 0; i < 4; ++i) {
        if (s_opts->is_dynamic_server[i]) continue;
        s_opts->backup_servers[i] = strdup(server);
        s_opts->is_dynamic_server[i] = true;
        return;
    }
    MDUS_WARN("too many backup servers?  (reached end of opt handler)\n");
}

static void handle_opt_port(struct server_opts *s_opts, void *v) {
    errno = 0;
    int p = (int) strtol((char *) v, NULL, 0);

    if (errno != 0 || p > 65535 || p < 1 ) {
        MDUS_WARN("port is invalid, using 80 instead\n");
        p = 80;
    }

    if (p < 1024 && geteuid())
        MDUS_WARN("using port number below 1024 as non-superuser\n");

    s_opts->port = p;
}

int parse_config() {

    FILE *cfgfp = fopen(cfg_opts.config_path, "r");
    if (!cfgfp) {
        MDUS_WARN("failed to process config file\n");
        return -1;
    }

    char *opt_buffer = nullptr;
    char *opt_buffer_current = nullptr;
    size_t size = 0;
    int r = 0;
    while ((r = getline(&opt_buffer, &size, cfgfp)) != -1) {
        opt_buffer_current = strtok(opt_buffer, " ");
        MDUS_DEBUG("parsing option %s\n", opt_buffer_current);
        int c = 0;
        for (;;) {
            if (optlist[c].name == NULL) break;

            if (!strcmp(optlist[c].name, opt_buffer_current)) {
                opt_buffer_current = strtok(NULL, " ");
                MDUS_DEBUG("has value %s\n", opt_buffer_current);
                optlist[c].optfn(&opts, opt_buffer_current);
                break;
            }
            ++c;
        }
    }

    free(opt_buffer);
    fclose(cfgfp);

    return 0;
}
