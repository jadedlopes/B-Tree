#include <stdio.h>
#include <stdlib.h>
#include "lista_enc.h"
#include "no.h"
#include "movies.h"
#include "btree.h"

int main()
{
    no_t* no;
    lista_enc_t *lista;
    arvore_t* tree_title = tree_create(title_comp, title_search_comp);

    lista = ler_arquivo("movies.csv");

    no = obtem_cabeca(lista);
    while(no){
        insert_tree(obtem_dado(no), tree_title);

        no = obtem_proximo(no);
    }

    //print_list_movies(lista, 10);


    return 0;
}
