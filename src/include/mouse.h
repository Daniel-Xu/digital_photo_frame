#ifndef MOUSE_H_
#define MOUSE_H_

#include "types.h"

extern int mouse_open(const char *dev_name);
extern mouse_event_t *mouse_parse(char buf[8], mouse_event_t *mevent);
extern void cursor_save(const fb_info_t *fb, int x, int y);
extern void cursor_restore(const fb_info_t *fb, int x, int y);
extern void cursor_draw(const fb_info_t *fb, int x, int y);

#endif
