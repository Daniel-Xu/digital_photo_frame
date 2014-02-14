#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <semaphore.h>

#include "types.h"
#include "mouse.h"
#include "pic_link.h"
#include "do.h"
#include "disp.h"

#define PIC_ROOT "./jpg"

handler_t handler[PROC_NUM] = {do_disp, do_mouse};
sem_t sem;

void *do_disp(void *arg)
{
	DIR *dp; fb_info_t *fb;
	struct dirent *item;
	char path[1024]; node_t *p;
	int which; 

	fb = (fb_info_t *)arg;

	dp = opendir(PIC_ROOT);
	if(dp == NULL)
		return (void *)-1;
	while(item = readdir(dp)){
		if(item->d_name[0] == '.')
			continue;
		pic_insert(item->d_name);
	}
	
	p = pic_head;
	while(1){
		time_t t; struct timespec timeout;

		sprintf(path, "%s/%s", PIC_ROOT, p->filename);
		which = rand() % DISP_NUM;
		effect[which](path, fb);
		
		t = time(NULL);
		t += 5;
		timeout.tv_sec = t; timeout.tv_nsec = 0;
		sem_timedwait(&sem, &timeout);			
		p = p->next;
		if(p == NULL)
			p = pic_head;
	}

	return NULL;
}

void *do_mouse(void *arg)
{
	int fd; int x, y, n;
	char buf[8]; mouse_event_t me;
	fb_info_t *fb;

	fb = (fb_info_t *)arg;

	fd = mouse_open(NULL);
	if(fd == -1)
		return (void *)-1;
	
	x = fb->x_res / 2, y = fb->y_res / 2;
	cursor_draw(fb, x, y);

	while(1){
		n = read(fd, buf, 8);
		mouse_parse(buf, &me);

        cursor_restore(fb, x, y);
        x += me.x;
        y += me.y;
        cursor_save(fb, x, y);
        cursor_draw(fb, x, y);

		if(me.button == 1){
			sem_post(&sem);
        }
	}
		
	return NULL;
}
