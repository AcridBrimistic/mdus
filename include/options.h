/*
 * options.h
 */

#include <stddef.h>

#define DEFAULT_PORT      80
#define DEFAULT_WORKING_DIRECTORY "/srv/mdus/"
#define DEFAULT_WORKING_DIRECTORY_LEN 11
#define DEFAULT_CONFIG_PATH "/etc/mdus/mdusrc"
#define DEFAULT_HBTIME    120
#define BACKUP_SERVER_MAX 4

enum {
    MDUS_VERBOSE = 1 << 0,
    MDUS_DRY     = 1 << 1,
    MDUS_INET4   = 1 << 2,
    MDUS_QUIET   = 1 << 3,
    MDUS_NTW     = 1 << 4, /* --no-thread-warning */
};

struct server_opts {
    int port;
    int hbtime;
    char *working_directory;
    size_t working_directory_len;
    const char *backup_servers[BACKUP_SERVER_MAX];
    bool is_dynamic_server[BACKUP_SERVER_MAX];
};

int parse_config();
extern struct server_opts opts;
