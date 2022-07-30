#ifndef __NODEH__
#define __NODEH__

typedef struct node_d {
	void* ptr;
	struct node_d* prev;
	struct node_d* next;
} node_t;

//void*
//node_get_ptr(node_t* node);

#endif /* __NODEH__ */
