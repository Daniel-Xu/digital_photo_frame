#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

node_t *pic_head = NULL;

static node_t *new_node(const char *filename)
{
	node_t *p;

	p = (node_t *)malloc(sizeof(node_t));
	if(p != NULL){
		p->next = NULL;
		p->filename = (char *)malloc(strlen(filename) + 1);
		if(p->filename == NULL){
			free(p);
			return NULL;
		}	
		strcpy(p->filename, filename);
	}

	return p;
}

node_t *pic_insert(const char *filename)
{
	node_t *p, *q;

	p = new_node(filename);
	if(p == NULL)
		return NULL;	
	if(pic_head == NULL){
		pic_head = p;
		return pic_head;
	}
	for(q = pic_head; q->next != NULL; q = q->next);
	q->next = p;
	
	return pic_head;
}

void pic_destroy(void)
{
	node_t *p, *q;

	for(p = pic_head; p != NULL; p = q){
		q = p->next;
		free(p->filename);
		free(p);
	}
	pic_head = NULL;
}

void pic_print(void)
{
	node_t *p;

	for(p = pic_head; p != NULL; p = p->next)
		printf("%s\n", p->filename);
}

#if 0
int main(void)
{
	pic_insert("1.jpg");
	pic_insert("2.jpg");
	pic_insert("3.jpg");
	pic_insert("4.jpg");
	
	pic_print();
	pic_destroy();
	
	return 0;
}
#endif
