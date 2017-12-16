#include <stdio.h>
#include <stdlib.h>
#include "lista_enc.h"
#include "no.h"
#include "movies.h"
#include "btree.h"

/*------------ Function declaration ------------------- */
void print_dot (btNode_t* node, FILE* arquivo);
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

    print_dot(get_tree_root(tree_title), fp);

    //print_list_movies(lista, 10);


    return 0;
}

void print_dot (btNode_t* node, FILE* arquivo) {
    if (node) {
        if (!get_treeNode_father(node)) {
            fputs("graph{", arquivo);
        }

        fprintf(arquivo, "n%p [label=%s", node, get_title(get_treeNode_key(node, 0)));
        if (get_treeNode_size(node) > 1) {
            fprintf(arquivo, " %s];\n", get_title(get_treeNode_key(node, 1)));
        } else {
            fputs("];", arquivo);
        }

        if(get_treeNode_father(node)) {
            fprintf(arquivo,"%p -- %p;\n", node, get_treeNode_father(node));
        }

        print_dot(get_treeNode_child(node, 0), arquivo);
        print_dot(get_treeNode_child(node, 1), arquivo);
        print_dot(get_treeNode_child(node, 2), arquivo);

        if (!get_treeNode_father(node)) {
            fputs("}", arquivo);
        }

    }
}

