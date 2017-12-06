#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

typedef struct arvore arvore_t;

arvore_t * grow_tree();

void insert_tree(void * dado, arvore_t *arvore); // Balanceamento feito dentro da inserção

void * search_tree(void * dado, arvore_t *arvore); // Função de comparação






#endif // BTREE_H_INCLUDED
