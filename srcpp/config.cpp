// hello
#include "config.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>

config_t *parse_args(int argc, char **argv);
void usage(char *cmd);

config_t *load(int argc, char **argv, const char *file) {
    (void) file; // nothing yet
    config_t *ret = parse_args(argc, argv);
    return ret;
}

config_t *parse_args(int argc, char **argv) {
    config_t *args = (config_t *) malloc(sizeof(config_t));
    args->xres = YRES;
    args->xres = XRES;
    args->scale = SCALE;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            usage(argv[0]);
            exit(1);
        }

        // else if (!strcmp(argv[i][0], "-") && !strcmp(argv[i][1], "X")) {
        //     args->xres = atoi(argv[i][2]);
        // }
        //
        // else if (!strcmp(argv[i][0], "-") && !strcmp(argv[i][1], "Y")) {
        //     args->yres = atoi(argv[i][2]);
        // }
        //
        // else if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--scale")) {
        //     if ((i+1) > argc) {
        //         fprintf(stderr, "Command line error: missing scale\n");
        //         exit(1);
        //     }
        //     args->scale = atoi(argv[i+1]);
        // }

        else {
            fprintf(stderr, "Command line error: unknown argument `%s`\n", argv[i]);
        }
    }

    return args;
}

void usage(char *cmd) {
    fprintf(stderr,
"Usage:\n$ %s [options]\n\
options:\n\
\t-X<num>\ti.e. -X32 sets the X resolution of the image\n\
\t-Y<num>\tsame as above, but for Y res\n\
\t-s|--scale <num>\t determines scale per image pixel\n\
\t-h|--help\tdisplays this message\n", cmd);
}
