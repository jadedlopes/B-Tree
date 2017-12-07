#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

typedef struct arvore arvore_t;

typedef struct node node_t;

arvore_t * tree_creation();

void insert_tree(void * dado, arvore_t *arvore); // Balanceamento feito dentro da inserção

void * search_tree(void * dado, arvore_t *arvore);

void free_tree(arvore_t *arvore);


#endif // BTREE_H_INCLUDED
