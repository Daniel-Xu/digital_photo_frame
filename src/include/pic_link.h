#ifndef PIC_LINK_H_
#define PIC_LINK_H_

extern node_t *pic_insert(const char *filename);
extern void pic_destroy(void);
extern void pic_print(void);

extern node_t *pic_head;

#endif
