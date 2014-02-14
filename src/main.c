#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>

#include "types.h"
#include "fb.h"
#include "do.h"
#include "err.h"

int main(void)
{
	fb_info_t fb; int i;
	pthread_t tid[PROC_NUM];

	if(fb_init(NULL, &fb) == NULL)
		err_sys("fail to init");
	sem_init(&sem, 0, 0);

	for(i = 0; i < PROC_NUM; i++)
		pthread_create(&tid[i], NULL, handler[i], &fb);
	for(i = 0; i < PROC_NUM; i++)
		pthread_join(tid[i], NULL);

	sem_destroy(&sem);
	fb_destroy(&fb);	

	return 0;
}
