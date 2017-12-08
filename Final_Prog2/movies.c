#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_enc.h"
#include "no.h"
#include "movies.h"

struct movies {
    char title[80];
    lista_enc_t * genres;
    int year;
    long int id;
};

lista_enc_t * ler_arquivo(char *arquivo) {

    int i;
    int j;
    char buffer[150];
    char genrebuffer[80];
    movie_t *dados;
    lista_enc_t *lista;
    char * genre;
    lista = cria_lista_enc();

    FILE *fp = fopen(arquivo, "r");

    if (fp == NULL) {
        perror("Erro em ler_arquivo: fopen");
        exit(EXIT_FAILURE);
    }

    fgets(buffer, 150, fp);

    while(fgets(buffer, 150, fp) != NULL) {
        i = 0;
        j = 0;
        dados = malloc(sizeof(struct movies));
        sscanf(buffer, "%ld, %50[^(](%d),%[^\n]", &dados->id, dados->title, &dados->year, genrebuffer);
        dados->genres = cria_lista_enc();   // Criando uma lista para os gêneros de cada filme
        while(genrebuffer[i] != '\0') { // Lógica para pegar cada gênero do filme da lista, que estão dividos pelo carácter '|'
            if(genrebuffer[i] == '|') {
                genrebuffer[i] = '\0';
                genre = malloc(strlen((genrebuffer + j) + 1));     // + 1 para caber o '\0'
                strcpy(genre, genrebuffer + j);
                j = i+1;
                add_cauda(dados->genres, genre);
            }
            i++;
        }
        genre = malloc(strlen((genrebuffer + j) + 1));
        strcpy(genre, genrebuffer + j);
        add_cauda(lista, dados);
    }
    fclose(fp);
    return lista;
}

void libera_movies(lista_enc_t * lista) {

    movie_t *dados;
    char * g;
    no_t *no;

    no = obtem_cabeca(lista);
    no_t * no_prox, *no_genre, *no_genre_prox;

    while (no) {
        dados = obtem_dado(no);
        no_genre = obtem_cabeca(dados->genres);
        while (no_genre) {
            g = obtem_dado(no_genre);
            no_genre_prox = obtem_proximo(no_genre);
            free(g);
            free(no_genre);
            no_genre = no_genre_prox;
        }
        free(dados);
        no_prox = obtem_proximo(no);
        free(no);
        no = no_prox;
    }
    free(lista);
}
