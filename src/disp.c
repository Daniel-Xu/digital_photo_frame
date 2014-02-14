#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "fb.h"
#include "types.h"
#include "disp.h"

u8_t *decode_jpeg (const char *filename, fb_info_t *jpeg_inf);
u32_t *rgb24to32(u8_t *buf24, fb_info_t jpeg_inf);
u8_t * scale24(u8_t *buf24, fb_info_t new_inf, fb_info_t jpeg_inf);

disp_t effect[DISP_NUM] = {disp_t2b, disp_b2t, disp_l2r, disp_r2l};

int disp_t2b(const char *filename, fb_info_t *fb)
{
	u8_t *decode_buf, *scale_buf;
	u32_t *rgb_buf;
	fb_info_t jpeg_info;
	int i, j; u32_t color;
 
	decode_buf = decode_jpeg(filename, &jpeg_info);
	if(decode_buf == NULL)
		return -1;
	scale_buf = scale24(decode_buf, *fb, jpeg_info);
	if(scale_buf == NULL)
		return -1;
	rgb_buf = rgb24to32(scale_buf, *fb);
	if(rgb_buf == NULL)
		return -1;

	for(i = 0; i < fb->y_res; i++){
		for(j = 0; j < fb->x_res; j++){
			color = *(rgb_buf + i * fb->x_res + j);
			fb_pixel(fb, j, i, color);
		}
		usleep(1000);
	}

	free(decode_buf);
	free(scale_buf);
	free(rgb_buf);

	return 0;
}

int disp_b2t(const char *filename, fb_info_t *fb)
{
	u8_t *decode_buf, *scale_buf;
	u32_t *rgb_buf;
	fb_info_t jpeg_info;
	int i, j; u32_t color;
 
	decode_buf = decode_jpeg(filename, &jpeg_info);
	if(decode_buf == NULL)
		return -1;
	scale_buf = scale24(decode_buf, *fb, jpeg_info);
	if(scale_buf == NULL)
		return -1;
	rgb_buf = rgb24to32(scale_buf, *fb);
	if(rgb_buf == NULL)
		return -1;

	for(i = fb->y_res - 1; i >= 0; i--){
		for(j = 0; j < fb->x_res; j++){
			color = *(rgb_buf + i * fb->x_res + j);
			fb_pixel(fb, j, i, color);
		}
		usleep(1000);
	}

	free(decode_buf);
	free(scale_buf);
	free(rgb_buf);

	return 0;
}

int disp_l2r(const char *filename, fb_info_t *fb)
{
	u8_t *decode_buf, *scale_buf;
	u32_t *rgb_buf;
	fb_info_t jpeg_info;
	int i, j; u32_t color;
 
	decode_buf = decode_jpeg(filename, &jpeg_info);
	if(decode_buf == NULL)
		return -1;
	scale_buf = scale24(decode_buf, *fb, jpeg_info);
	if(scale_buf == NULL)
		return -1;
	rgb_buf = rgb24to32(scale_buf, *fb);
	if(rgb_buf == NULL)
		return -1;

	for(j = 0; j < fb->x_res; j++){
		for(i = 0; i < fb->y_res; i++){
			color = *(rgb_buf + i * fb->x_res + j);
			fb_pixel(fb, j, i, color);
		}
		usleep(1000);
	}

	free(decode_buf);
	free(scale_buf);
	free(rgb_buf);

	return 0;
}

int disp_r2l(const char *filename, fb_info_t *fb)
{
	u8_t *decode_buf, *scale_buf;
	u32_t *rgb_buf;
	fb_info_t jpeg_info;
	int i, j; u32_t color;
 
	decode_buf = decode_jpeg(filename, &jpeg_info);
	if(decode_buf == NULL)
		return -1;
	scale_buf = scale24(decode_buf, *fb, jpeg_info);
	if(scale_buf == NULL)
		return -1;
	rgb_buf = rgb24to32(scale_buf, *fb);
	if(rgb_buf == NULL)
		return -1;

	for(j = fb->x_res - 1; j >= 0; j--){
		for(i = 0; i < fb->y_res; i++){
			color = *(rgb_buf + i * fb->x_res + j);
			fb_pixel(fb, j, i, color);
		}
		usleep(1000);
	}

	free(decode_buf);
	free(scale_buf);
	free(rgb_buf);

	return 0;
}
