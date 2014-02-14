#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

#include "types.h"
#include "mouse.h"
#include "pic_link.h"
#include "do.h"
#include "disp.h"

#define PIC_ROOT "./jpg"

extern pid_t *pid;

void sig_usr1(int signo)
{
	/* do nothing... */
}

int do_disp(fb_info_t fb)
{
	DIR *dp; struct dirent *item;
	char path[1024]; node_t *p;
	int which;

	signal(SIGUSR1, sig_usr1);

	dp = opendir(PIC_ROOT);
	if(dp == NULL)
		return -1;
	while(item = readdir(dp)){
		if(item->d_name[0] == '.')
			continue;
		pic_insert(item->d_name);
	}
#if 0
	pic_print();
#endif
	p = pic_head;
	while(1){
		sprintf(path, "%s/%s", PIC_ROOT, p->filename);
		which = rand() % DISP_NUM;
		effect[which](path, &fb);
		sleep(5);
		p = p->next;
		if(p == NULL)
			p = pic_head;
	}

	return 0;
}

int do_mouse(fb_info_t fb)
{
	int fd; int x, y, n;
	char buf[8]; mouse_event_t me;

	fd = mouse_open(NULL);
	if(fd == -1)
		return -1;
	
	x = fb.x_res / 2, y = fb.y_res / 2;
	cursor_draw(&fb, x, y);
	while(1){
		n = read(fd, buf, 8);
		mouse_parse(buf, &me);
		
		cursor_restore(&fb, x, y);
		x += me.x;
		y += me.y;
		cursor_save(&fb, x, y);
		cursor_draw(&fb, x, y);

		if(me.button == 1)
			kill(pid[0], SIGUSR1);
	}
		
	return 0;
}

handler_t handler[PROC_NUM] = {do_disp, do_mouse};
