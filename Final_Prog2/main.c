/******************************************************
 * Instituto Federal de Santa Catarina
 * Curso:       Engenharia Eletr�nica
 * Disciplina:  Programa��o de Computadores II
 * Professor:   Renan Augusto Starke
 * Aluna:       Jade Dutra Lopes e Raquel Dutra Kotzias
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "lista_enc.h"
#include "no.h"
#include "movies.h"
#include "btree.h"

int main()
{
    char nome[80];
    int ano;
    int input;
    no_t * no;
    lista_enc_t * lista;
    fila_t * fila;
    arvore_t * tree_title = tree_create(title_comp, title_search_comp);

    lista = ler_arquivo("movies.csv");

   /* no = obtem_cabeca(lista);
    while(no){
        insert_tree(obtem_dado(no), tree_title);

        no = obtem_proximo(no);
    }
*/
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
            printf("Digite as primeiras palavras do t�tulo do filme desejado: ");
            scanf("%s", nome);

            fila = search_tree(nome, tree_title);

            while(!fila_vazia(fila))
            {
                dequeue(fila);
            }
            libera_fila(fila);

            break;

        case 2:
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            printf("Digite o ano do filme desejado: ");
            scanf("%d", &ano);

            fila = search_tree((void*)ano, tree_title);

            while(!fila_vazia(fila))
            {
                dequeue(fila);
            }
            libera_fila(fila);

            break;
        }

        libera_movies(lista);
        free(tree_title);

    return 0;
    }
}
