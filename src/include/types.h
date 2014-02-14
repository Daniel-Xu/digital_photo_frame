#ifndef TYPES_H_
#define TYPES_H_

typedef unsigned char u8_t;
typedef unsigned int u32_t;
typedef unsigned short u16_t;

typedef struct
{
	int x_res, y_res;
	int bpp; /* bits per pixel */
	u8_t *fb_buf;
}fb_info_t;

typedef struct node node_t;
struct node
{
	char *filename;
	struct node *next;
};

typedef struct
{
	int x, y;	
	int button;
}mouse_event_t;

//typedef int (*handler_t)(fb_info_t);
typedef void *(*handler_t)(void *);
typedef int (*disp_t)(const char *filename, fb_info_t *fb);

#endif
