#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_enc.h"
#include "no.h"
#include "movies.h"

#define DEBUG

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
    char* genre;
    lista = cria_lista_enc();

    FILE *fp = fopen(arquivo, "r");

    if (fp == NULL) {
        perror("Erro em ler_arquivo: fopen");
        exit(EXIT_FAILURE);
    }

    while(fgets(buffer, 150, fp) != NULL) {
        i = 0;
        j = 0;
        dados = (movie_t*)malloc(sizeof(struct movies));
        if (!dados){
            perror("movies.c: ler_arquivo -> malloc ");
            exit(EXIT_FAILURE);
        }
        sscanf(buffer, "%ld, %50[^(](%d),%[^\n]", &dados->id, dados->title, &dados->year, genrebuffer);
        dados->genres = cria_lista_enc();   // Criando uma lista para os gêneros de cada filme

        while(genrebuffer[i] != '\0') { // Lógica para pegar cada gênero do filme da lista, que estão dividos pelo carácter '|'
            if(genrebuffer[i] == '|') {
                genrebuffer[i] = '\0';
                genre = malloc(strlen((genrebuffer + j) + 1));     // + 1 para caber o '\0'
                if (!genre){
                    perror("movies.c: ler_arquivo -> malloc ");
                    exit(EXIT_FAILURE);
                }
                strcpy(genre, genrebuffer + j);
                j = i+1;
                printf("ahhhhhh: %s\n", genre);
                add_cauda(dados->genres, genre);
            }
            i++;
        }
        genre = malloc(strlen((genrebuffer + j) + 1));
        if (!genre){
            perror("movies.c: ler_arquivo -> malloc ");
            exit(EXIT_FAILURE);
        }
        strcpy(genre, genrebuffer + j);
        add_cauda(dados->genres, genre);

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

int title_comp(movie_t* m1, movie_t* m2){
    int res;
    res = strcmp(m1->title, m2->title);

    return res;
}

int title_search_comp(char* str, movie_t* m){
    char* aux;
    int ret;

    aux = malloc(strlen(str) + 1);
    strcpy(aux, m->title);
    aux[strlen(str)+1] = '\0';
    ret = strcmp(str, aux);
    free(aux);

    return ret;

}

int year_comp(movie_t* m1, movie_t* m2){
    int res;

    if (m1->year > m2->year){
        res = 1;
    }else if (m1->year < m2->year){
        res = -1;
    }else{
        res = 0;
    }

    return res;
}

int year_search_comp(int year, movie_t* m){
    if (year < 100){
        if (year > 17){
            year = year + 1900;
        }else{
            year = year + 2000;
        }
    }

    if (year > m->year){
        return 1;
    }else if (year < m->year){
        return -1;
    }else{
        return 0;
    }
}

int id_comp(movie_t* m1, movie_t* m2){
    int res;

    if (m1->id > m2->id){
        res = 1;
    }else if(m1->id < m2->id){
        res = -1;
    }else{
        res = 0;
    }

    return res;
}

void print_list_movies(lista_enc_t* lista, int size){
    movie_t* m;
    no_t* no;
    int i = 0;

    if (size> tamanho(lista) || size <= 0){
        size = tamanho(lista);
    }

    no = obtem_cabeca(lista);
    for(i = 0; i < size; i++){
        m = obtem_dado(no);
        print_movie(m);

        no = obtem_proximo(no);
    }

}

void print_movie(movie_t* m){
    no_t* no;
    char* aux;

    printf("Id: %ld |Title: %s |Year: %d |Genres: ", m->id, m->title, m->year);

    no = obtem_cabeca(m->genres);
    while(no){
        aux = obtem_dado(no);
        printf("%s ", aux);

        no = obtem_proximo(no);
    }
    printf("\n");
}
