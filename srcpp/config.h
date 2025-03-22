// hello
#pragma once

// config-ed
#define SCALE 32
#define XRES 32
#define YRES 32

// dynamic
#define BORDER 1
#define XPADDING 10
#define YPADDING 5
#define PALETTE 16

#define PALWIDTH (LEFTBAR-(XPADDING*2))
#define PALHEIGHT (SCALE)

#define LEFTBAR (100)
#define TOPBAR (25)
#define PICSTARTX (LEFTBAR)
#define PICSTARTY (TOPBAR)
#define PICWIDTH (SCALE*XRES)
#define PICHEIGHT (SCALE*YRES)
#define XCOORD(x) (PICSTARTX+(x*SCALE))
#define YCOORD(y) (PICSTARTY+(y*SCALE))

#define WIDTH (PICWIDTH + LEFTBAR)
#define HEIGHT (PICHEIGHT)

typedef struct {
    // general size, pixels per 'pixel' drawn
    int scale;
    // dims, i.e. 32x32
    int xres;
    int yres;
} config_t;

config_t *load(int argc, char **argv, const char *file);
