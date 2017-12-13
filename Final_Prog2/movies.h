#ifndef MOVIES_H_INCLUDED
#define MOVIES_H_INCLUDED

typedef struct movies movie_t;

lista_enc_t * ler_arquivo(char *arquivo);

void libera_movies(lista_enc_t * lista);

int compara_title(movie_t* m1, movie_t* m2);

int compara_year(movie_t* m1, movie_t* m2);

int compara_id(movie_t* m1, movie_t* m2);


#endif // MOVIES_H_INCLUDED
