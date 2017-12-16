#ifndef MOVIES_H_INCLUDED
#define MOVIES_H_INCLUDED

typedef struct movies movie_t;

lista_enc_t * ler_arquivo(char *arquivo);

void libera_movies(lista_enc_t * lista);

int title_comp(void* v1, void* v2);

int title_search_comp(void* t_string, void* v);

int year_comp(void* v1, void* v2);

int year_search_comp(void* y, void* v);

int id_comp(void* v1, void* v2);

void print_list_movies(lista_enc_t* lista, int size);

void print_movie(movie_t* m);

char* get_title(movie_t* m);

#endif // MOVIES_H_INCLUDED
