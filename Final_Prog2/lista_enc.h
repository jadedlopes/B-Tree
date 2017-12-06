#ifndef LISTA_ENC_H_INCLUDED
#define LISTA_ENC_H_INCLUDED

#include "no.h"

typedef struct listas_enc lista_enc_t;

lista_enc_t *cria_lista_enc(void);
void add_cauda(lista_enc_t *lista, no_t* elemento);

no_t * cabeca_lista(lista_enc_t *lista);
no_t * remove_elem(lista_enc_t *lista, int index);

#endif // LISTA_ENC_H_INCLUDED
