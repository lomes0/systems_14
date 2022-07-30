#include <stdlib.h>

#include "btree.h"

static void*
bnode_get(bnode_t* node, str_t key)
{
	int cmp = str_cmp(node->key, key);

	if (cmp == 0) {
		return node->ptr;
	}

	if (cmp < 0 && node->left != NULL) {
		return bnode_get(node->left, key);
	}

	if (cmp > 0 && node->right != NULL) {
		return bnode_get(node->right, key);
	}

	return NULL;
}

void
bnode_insert(bnode_t* node, str_t key, void* ptr)
{
	int cmp = str_cmp(node->key, key);
	bnode_t** node_p;

	//assert(cmp != 0);

	if (node->left != NULL && cmp < 0) {
		bnode_insert(node->left, key, ptr);
		return;
	}

	if (node->right != NULL && cmp > 0) {
		bnode_insert(node->right, key, ptr);
		return;
	}

	node_p = cmp < 0 ? &(node->left) : &(node->right);

	(*node_p) = (bnode_t*) malloc(sizeof(bnode_t));
	(*node_p)->left = NULL;
	(*node_p)->right = NULL;
	(*node_p)->key = key;
	(*node_p)->ptr = ptr;
}

void*
btree_get(btree_t* tree, str_t key)
{
	if (tree->root == NULL) {
		return NULL;
	}

	return bnode_get(tree->root, key);
}

int
btree_has(btree_t* tree, str_t key)
{
	void* ptr = btree_get(tree, key);

	return ptr != NULL;
}

void
btree_insert(btree_t* tree, str_t key, void* ptr)
{
	if (tree->root == NULL) {
		tree->root = (bnode_t*) malloc(sizeof(bnode_t));
		tree->root->left = NULL;
		tree->root->right = NULL;
		tree->root->key = key;
		tree->root->ptr = ptr;
		return;
	}

	bnode_insert(tree->root, key, ptr);
}
