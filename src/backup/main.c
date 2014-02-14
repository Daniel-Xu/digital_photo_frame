#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

#include "types.h"
#include "fb.h"
#include "do.h"
#include "err.h"

pid_t *pid = NULL;

void *smalloc(size_t size)
{
	char *p;

	p = (char *)mmap(NULL, size, PROT_READ | PROT_WRITE, 
		MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(p == MAP_FAILED)
		return NULL;
	return p;
}

void sfree(void *ptr, size_t size)
{
	munmap(ptr, size);
}

int main(void)
{
	fb_info_t fb; int i;
	pid_t tpid;

	if(fb_init(NULL, &fb) == NULL)
		err_sys("fail to init");
	pid = (pid_t *)smalloc(sizeof(pid_t) * PROC_NUM);
	if(pid == NULL)
		err_sys("fail to smalloc");	

	for(i = 0; i < PROC_NUM; i++){
		tpid = fork();
		if(tpid == 0)
			break;
		pid[i] = tpid;
	}
	if(i < PROC_NUM){
		int res;
		
		res = handler[i](fb);
		if(res == -1)
			err_sys("fail to handle");
	}

	for(i = 0; i < PROC_NUM; i++)
		wait(NULL);

	sfree(pid, sizeof(pid_t) * PROC_NUM);
	fb_destroy(&fb);	

	return 0;
}
