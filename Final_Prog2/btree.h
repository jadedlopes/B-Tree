#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED
#include "fila.h"

typedef struct arvore arvore_t;

typedef struct btNode btNode_t;

arvore_t * tree_create(int(*c)(void *, void *), int (*c_s)(void *, void *));

btNode_t* tree_node_create();

void insert_tree (void* data, arvore_t* tree); // Balanceamento feito dentro da inserção

fila_t* search_tree(void * data, arvore_t *arvore);

void free_tree(arvore_t *arvore);

void print_dot (btNode_t* node, FILE* arquivo, char*(*title_func)(void*));

#endif // BTREE_H_INCLUDED
