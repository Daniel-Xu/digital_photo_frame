#ifndef FB_H_
#define FB_H_

#include "types.h"

extern fb_info_t *fb_init(const char *dev_name, fb_info_t *fb);
extern int fb_destroy(fb_info_t *fb);
extern int fb_pixel(const fb_info_t *fb, int x, int y, u32_t color);

#endif
