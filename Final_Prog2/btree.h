#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED
#include "fila.h"

typedef struct arvore arvore_t;

typedef struct btNode btNode_t;

arvore_t * tree_create(int(*c)(void *, void *), int (*c_s)(void *, void *));

btNode_t* tree_node_create();

/*------- Get tree status ----------*/
int get_treeNode_size (btNode_t* node);

void* get_treeNode_key (btNode_t* node, int pos);

btNode_t* get_treeNode_child (btNode_t* node, int pos);

btNode_t* get_treeNode_father (btNode_t* node);

int get_treeNode_leaf (btNode_t* node);

btNode_t* get_tree_root (arvore_t* tree);

/*----------------------------------*/

void insert_tree (void* data, arvore_t* tree); // Balanceamento feito dentro da inserção

fila_t* search_tree(void * data, arvore_t *arvore);

void free_tree(arvore_t *arvore);

#endif // BTREE_H_INCLUDED
