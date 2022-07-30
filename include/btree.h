#ifndef __BTRREH__
#define __BTRREH__

#include "str.h"

typedef struct bnode_d {
	struct bnode_d* left;
	struct bnode_d* right;
	str_t key;
	void* ptr;
} bnode_t;

typedef struct {
	bnode_t* root;
} btree_t;

int btree_has(btree_t* tree, str_t key);

void* btree_get(btree_t* tree, str_t key);

void btree_insert(btree_t* tree, str_t key, void* ptr);

#endif /* __BTRREH__ */
