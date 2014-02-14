#ifndef DO_H_
#define DO_H_

#define PROC_NUM 2

extern handler_t handler[]; 
extern sem_t sem;

extern void *do_disp(void *arg);
extern void *do_mouse(void *arg);

#endif
