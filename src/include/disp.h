#ifndef DISP_H_
#define DISP_H_

#include "types.h"

#define DISP_NUM 4

extern disp_t effect[];

extern int disp_t2b(const char *filename, fb_info_t *fb);
extern int disp_b2t(const char *filename, fb_info_t *fb);
extern int disp_l2r(const char *filename, fb_info_t *fb);
extern int disp_r2l(const char *filename, fb_info_t *fb);

#endif
