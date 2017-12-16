/******************************************************
 * Instituto Federal de Santa Catarina
 * Curso:       Engenharia Eletrônica
 * Disciplina:  Programação de Computadores II
 * Professor:   Renan Augusto Starke
 * Aluna:       Jade Dutra Lopes e Raquel Dutra Kotzias
 ******************************************************/

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
<<<<<<< HEAD
    char nome[80];
    int ano;
    no_t * no;
    lista_enc_t * lista;
    fila_t * fila;
    arvore_t * tree_title = tree_create(title_comp, title_search_comp);
=======
    no_t* no;
    lista_enc_t *lista;
    arvore_t* tree_title = tree_create(title_comp, title_search_comp);
    FILE* fp = fopen("tree.dot", "w");
>>>>>>> f5e192f04d11c02c2820179ca4cd0222176c296b

    lista = ler_arquivo("movies.csv");

    no = obtem_cabeca(lista);
    while(no){
        insert_tree(obtem_dado(no), tree_title);

        no = obtem_proximo(no);
    }

    print_dot(get_tree_root(tree_title), fp);

    //print_list_movies(lista, 10);


    while(1) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        printf ("\tMENU PRINCIPAL\n"
                "\n"
                "Digite:\n"
                "<1> Para realizar busca por nome do filme;\n"
                "<2> Para realizar busca pelo ano;\n"
                "<3> Para sair.\n");
        fflush(stdin);
        scanf("%d",&input);

        if(input == 3)
            break;

        switch(input) {

        case 1:
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            printf("Digite as primeiras palavras do título do filme desejado: ");
            scanf("%s", nome);

            fila = search_tree(nome, tree_title);


            break;

        case 2:
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            printf("Digite o ano do filme desejado: ");
            scanf("%d", ano);

            fila = search_tree(ano, tree_title);

            break;
        }

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

