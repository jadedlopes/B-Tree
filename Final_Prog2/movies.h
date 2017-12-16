#ifndef MOVIES_H_INCLUDED
#define MOVIES_H_INCLUDED

typedef struct movies movie_t;

lista_enc_t * ler_arquivo(char *arquivo);

void libera_movies(lista_enc_t * lista);

int title_comp(movie_t* m1, movie_t* m2);

int title_search_comp(char* str, movie_t* m);

int year_comp(movie_t* m1, movie_t* m2);

int year_search_comp(int year, movie_t* m);

int id_comp(movie_t* m1, movie_t* m2);

void print_list_movies(lista_enc_t* lista, int size);

void print_movie(movie_t* m);

char* get_title(movie_t* m);

#endif // MOVIES_H_INCLUDED
