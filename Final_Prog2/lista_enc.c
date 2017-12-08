#include <stdio.h>
#include <stdlib.h>

#include "lista_enc.h"
#include "no.h"

#define DEBUG

struct lista_enc {
    no_t *cabeca;
    no_t *cauda;
    int tamanho;
};

//cria uma lista vazia
lista_enc_t *cria_lista_enc (void) {
    lista_enc_t *p = malloc(sizeof(lista_enc_t));

    if (p == NULL){
        perror("cria_lista_enc:");
        exit(EXIT_FAILURE);
    }

    p->cabeca = NULL;
    p->cauda = NULL;
    p->tamanho = 0;

    return p;
}

void add_cauda(lista_enc_t *lista, void* elemento){
    if (lista == NULL || elemento == NULL){
        fprintf(stderr,"add_cauda: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

   #ifdef DEBUG
   printf("Adicionando %p --- tamanho: %d\n", elemento, lista->tamanho);
   #endif // DEBUG

   no_t* no = cria_no(elemento);

   //lista vazia
   if (lista->tamanho == 0)
   {
        #ifdef DEBUG
        printf("add_cauda: add primeiro elemento: %p\n", no);
        #endif // DEBUG

        lista->cauda = no;
        lista->cabeca = no;
        lista->tamanho++;

        desliga_no(no);
   }
   else {
        // Remove qualquer ligacao antiga
        desliga_no(no);
        // Liga cauda da lista com novo elemento
        liga_nos(lista->cauda, no);

        lista->cauda = no;
        lista->tamanho++;
   }
}

void add_cabeca(lista_enc_t *lista, void* elemento){
    if (lista == NULL || elemento == NULL){
        fprintf(stderr,"add_cabeca: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

   #ifdef DEBUG
   printf("Adicionando %p --- tamanho: %d\n", elemento, lista->tamanho);
   #endif // DEBUG

   no_t* no = cria_no(elemento);

   //lista vazia
   if (lista->tamanho == 0)
   {
        #ifdef DEBUG
        printf("add_cabeca: add primeiro elemento: %p\n", no);
        #endif // DEBUG

        lista->cauda = no;
        lista->cabeca = no;
        lista->tamanho++;

        desliga_no(no);
   }
   else {
        liga_nos(no, lista->cabeca);

        lista->cabeca = no;
        lista->tamanho++;
   }
}

void* obtem_cabeca(lista_enc_t* lista){
    if (lista == NULL){
        fprintf(stderr,"add_cabeca: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    return obtem_dado(lista->cabeca);
}

void* obtem_cauda(lista_enc_t* lista){
    if (lista == NULL){
        fprintf(stderr,"add_cabeca: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    return obtem_dado(lista->cauda);
}

void* remove_cabeca(lista_enc_t *lista){
    if (lista == NULL){
        fprintf(stderr, "remove_cabeca: ponteiro invalido");
        exit(EXIT_FAILURE);
    }

    no_t* no = lista->cabeca;
    lista->cabeca = obtem_proximo(no);

    if(no == NULL){
        lista->cauda = NULL;
    }

    lista->tamanho--;
    void* dado = obtem_dado(no);

    free(no);

    return dado;
}

void* remove_cauda(lista_enc_t *lista){
    if (lista == NULL){
        fprintf(stderr, "remove_cauda: ponteiro invalido");
        exit(EXIT_FAILURE);
    }

    no_t* no = lista->cauda;
    no_t* no_test = lista->cabeca;

    while(obtem_proximo(no_test) != no){
        no_test = obtem_proximo(no_test);
    }

    lista->cauda = no_test;
    desliga_no(no_test);
    void* dado = obtem_dado(no);
    lista->tamanho--;

    free(no);

    return dado;
}

void* remove_elem(lista_enc_t* lista, int index){
    if (lista == NULL){
        fprintf(stderr, "remove_elem: ponteiro invalido");
        exit(EXIT_FAILURE);
    }

    if (index >= lista->tamanho || index < 0){
        fprintf(stderr, "remove_elem: index invalido");
        exit(EXIT_FAILURE);
    }

    if (index == 0){
        return remove_cabeca(lista);
    }

    if (index == (lista->tamanho)-1){
        return remove_cauda(lista);
    }

    int i = 1;
    no_t* no_ant = lista->cabeca;
    no_t* no     = obtem_proximo(no_ant);
    while ( i < index){
        no_ant = no;
        no     = obtem_proximo(no_ant);

        i++;
    }

    no_t* no_prox = obtem_proximo(no);

    liga_nos(no_ant, no_prox);
    lista->tamanho--;

    void* dado = obtem_dado(no);
    free(no);

    return dado;
}

int tamanho (lista_enc_t *lista){
    if (lista == NULL){
        fprintf(stderr, "tamanho: ponteiro invalido");
        exit(EXIT_FAILURE);
    }

    return lista->tamanho;
}

int vazio(lista_enc_t* lista){
    if (lista == NULL){
        fprintf(stderr, "vazio: ponteiro invalido");
        exit(EXIT_FAILURE);
    }

    if (lista->tamanho == 0){
        return 1;
    }else{
        return 0;
    }
}
