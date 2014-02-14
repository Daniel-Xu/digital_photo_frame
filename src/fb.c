#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

#include "types.h"

#define FB_DEV "/dev/fb0"

fb_info_t *fb_init(const char *dev_name, fb_info_t *fb)
{
	int fd, res; u8_t *p;
	static fb_info_t fb_var;
	struct fb_var_screeninfo screen_info;	

	if(dev_name == NULL)
		dev_name = FB_DEV;
	if(fb == NULL)
		fb = &fb_var;

	fd = open(dev_name, O_RDWR);
	if(fd == -1)
		return NULL;
	res = ioctl(fd, FBIOGET_VSCREENINFO, &screen_info);
	if(res == -1)
		return NULL;
	printf("x : %d, y : %d, bpp : %d\n", screen_info.xres, screen_info.yres, screen_info.bits_per_pixel);
	
	fb->x_res = screen_info.xres;
	fb->y_res = screen_info.yres;
	fb->bpp = screen_info.bits_per_pixel;
	fb->fb_buf = (char *)mmap(NULL, fb->x_res * fb->y_res * fb->bpp / 8, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(fb->fb_buf == MAP_FAILED)
		return NULL;
	close(fd);	

	return fb;
}

int fb_destroy(fb_info_t *fb)
{
	munmap(fb->fb_buf, 
		fb->x_res * fb->y_res * fb->bpp / 8);
	fb->x_res = fb->y_res = fb->bpp = 0;
	fb->fb_buf = NULL;

	return 0;
}

int fb_pixel(const fb_info_t *fb, int x, int y, u32_t color)
{
	u32_t *p;

	p = (u32_t *)(fb->fb_buf + (y * fb->x_res + x) * fb->bpp / 8); 
	*p = color;
	
	return 0;
}

#if 0
int main(void)
{
	fb_info_t fb_info; fb_info_t *res;
	int i;

	res = fb_init(NULL, &fb_info);
	if(res == NULL)
		err_sys("fail to fb_init");
	
	for(i = 0; i < 10; i++){
		fb_pixel(&fb_info, 512 + i, 384, 0xffffff00);
		fb_pixel(&fb_info, 512 + i, 385, 0xffffff00);
		fb_pixel(&fb_info, 512 + i, 386, 0xffffff00);
	}

	fb_destroy(&fb_info);

	return 0;
}
#endif
