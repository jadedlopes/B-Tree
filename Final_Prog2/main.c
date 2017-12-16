#include <stdio.h>
#include <stdlib.h>
#include "lista_enc.h"
#include "no.h"
#include "movies.h"
#include "btree.h"

/*------------ Function declaration ------------------- */
print_dot (btNode_t* node, FILE* arquivo);
/*----------------------------------------------------- */

int main()
{
    no_t* no;
    lista_enc_t *lista;
    arvore_t* tree_title = tree_create(title_comp, title_search_comp);
    FILE* fp = fopen("tree.dot", "w");

    lista = ler_arquivo("movies.csv");

    no = obtem_cabeca(lista);
    while(no){
        insert_tree(obtem_dado(no), tree_title);

        no = obtem_proximo(no);
    }

    print_dot(tree_title->raiz, fp);

    //print_list_movies(lista, 10);


    return 0;
}

void print_dot (btNode_t* node, FILE* arquivo) {
    if (node) {
        if (!node->pai) {
            fputs("graph{", arquivo);
        }

        fprintf(arquivo, "n%p [label=%s", node, get_title(node->key[0]));
        if (node->n > 1) {
            fprintf(arquivo, " %s];\n", get_title(node->key[1]));
        } else {
            fputs("];", arquivo);
        }

        if(node->pai) {
            fprintf(arquivo,"%p -- %p;\n", node, node->pai);
        }

        print_dot(node->p[0], arquivo, title_func);
        print_dot(node->p[1], arquivo, title_func);
        print_dot(node->p[3], arquivo, title_func);

        if (!node->pai) {
            fputs("}", arquivo);
        }

    }
}

