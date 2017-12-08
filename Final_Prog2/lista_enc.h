#ifndef LISTA_ENC_H_INCLUDED
#define LISTA_ENC_H_INCLUDED

#include "no.h"

typedef struct lista_enc lista_enc_t;

lista_enc_t* cria_lista_enc (void);

void add_cauda(lista_enc_t *lista, void* elemento);

void add_cabeca(lista_enc_t *lista, void* elemento);

no_t* obtem_cabeca(lista_enc_t* lista);

no_t* obtem_cauda(lista_enc_t* lista);

void* remove_cabeca(lista_enc_t *lista);

void* remove_cauda(lista_enc_t *lista);

void* remove_elem(lista_enc_t* lista, int index);

int tamanho (lista_enc_t *lista);

int vazio(lista_enc_t* lista);

#endif // LISTA_ENC_H_INCLUDED
