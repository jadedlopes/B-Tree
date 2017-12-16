#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include "fila.h"
#include "lista_enc.h"
#include "no.h"
#define ORDER 3         // Definimos que a ordem da árvore é 3

/*------------ Private function declaration ------------------- */
static int searchKey (btNode_t* btn, void* data, arvore_t* tree);
static void insert_node (void* data, btNode_t* right, btNode_t*  btn, int pos);
static btNode_t* split_node(btNode_t* btn, void* data, arvore_t* tree);
static int median (btNode_t* btn, void* data, arvore_t* tree);
static btNode_t* go_to_leaf(btNode_t* node, void* data, arvore_t* tree);
static btNode_t * nodePrev(btNode_t * btn, int * k);
/*------------------------------------------------------------- */


struct arvore {
    btNode_t * raiz;
    int (*comp)(void *, void *);    // Ponteiro para a função de comparação (recebe como argumento um void*, pois não sabemos o que ela vai receber)
    int (*comp_search) (void *, void *); // Ponteiro para função de comparação para pesquisa na arvore
};

struct btNode {
    int n;               // n é a quantidade de chaves que o nó possui
    void * key[ORDER - 1];
    btNode_t * p[ORDER];  // p[ORDER] são as ligações dos filhos
    btNode_t * pai;
    int leaf;         //0 = false / 1 = true
};

arvore_t * tree_create(int(*c)(void *, void *), int (*c_s)(void *, void *)) {

    arvore_t * arvore;

    arvore = malloc(sizeof(arvore_t));

    arvore->raiz = NULL;    // Não há nenhum dado ainda na raiz

    arvore->comp = c;

    arvore->comp_search = c_s;

    return arvore;
}

btNode_t* tree_node_create() {
    btNode_t* tNode = (btNode_t*)malloc(sizeof(btNode_t));

    if (tNode == NULL) {
        perror("btree -> tree_node_create: ");
        exit(EXIT_FAILURE);
    }

    int i;

    tNode->n = 0;
    tNode->pai = NULL;
    for (i = 0; i<ORDER; i++) {
        tNode->p[i] = NULL;
    }

    tNode->leaf = 0;

    return tNode;
}

// devolve a posição a ser inserido o dado ou para qual filho ir
static int searchKey (btNode_t* btn, void* data, arvore_t* tree) {
    int i;

    for (i = 0; i < btn->n; i++) {
        if (tree->comp(data, btn->key[i]) < 0) {
            break;
        }
    }
    return i;
}

// retorna filho da direita se split se não retorna null
void insert_tree (void* data, arvore_t* tree) {
    btNode_t *btn;
    btNode_t *right = NULL;
    btNode_t *p;
    int pos, finished;

    if(tree->raiz) {
        btn = go_to_leaf(tree->raiz, data, tree);

        if(btn->n < ORDER-1 ) {
            pos = searchKey(btn, data, tree);
            insert_node(data, NULL, btn, pos);
            finished = 1;
        } else {
            while(1) {      // Se não tiver espaço
                right = split_node(btn, data, tree);

                if (btn->pai == NULL) {     // Se não tiver pai é porque é a raiz; logo, sai do while(1)
                    break;
                } else {
                    btn = btn->pai;
                }

                if(btn->n < ORDER-1) {      // Checar se o pai tem espaço
                    pos = searchKey(btn, data, tree);
                    insert_node(data, right, btn, pos);
                    finished = 1;
                    break;
                }
            }

            if(!finished) {
                if(btn != tree->raiz) {
                    perror("Error: btree->insert_tree_int: ");
                    exit(EXIT_FAILURE);
                }

                p = tree_node_create();
                p->n++;
                p->key[0] = data;
                p->p[0] = btn;
                btn->pai = p;
                p->p[1] = right;
                right->pai = p;
                tree->raiz = p;
            }
        }
        return;
    }

    btn = tree_node_create();
    btn->key[0] = data;
    btn->n = 1;
    btn->leaf = 1;
    tree->raiz = btn;

    return;
}

static void insert_node (void* data, btNode_t* right, btNode_t*  btn, int pos) {
    int i;

    if(pos == 0) {
        btn->key[1] = btn->key[0];
        btn->key[0] = data;
    } else {
        btn->key[1] = data;
    }

    if (!btn->leaf) {
        pos++;
        for(i = btn->n+1; i-- > pos;) {
            btn->p[i+1] = btn->p[i];
        }

        btn->p[pos] = right;
        right->pai = btn;
    }

    btn->n++;
}

static btNode_t * keyPrev(btNode_t * btn, int * k)
{
	int i;
	btNode_t * pai;

	if(btn->p[*k]) {
		btn = btn->p[*k];
		while(btn->p[btn->n]) {
			btn = btn->p[btn->n];
		}
		*k = btn->n-1;
		return btn;
	}

	if(*k > 0) {
		*k--;
		return btn;
	}

	while(*k == 0) {

		if(btn->pai == NULL) {
			return NULL;
		}
		if(btn == btn->pai->p[0]) {
			btn = btn->pai;
		}
		else {
			pai = btn->pai;
			for(i = 1; btn != pai->p[i]; i++);
			btn = pai;
			*k = i - 1;
			break;
		}
	}

	return btn;
}

static btNode_t * keyNext(btNode_t * btn, int * k)
{
	int i;
	btNode_t * pai;

	if(btn->p[*k+1]) {
		btn = btn->p[*k+1];
		while(btn->p[0]) {
			btn = btn->p[0];
		}
		*k = 0;
		return btn;
	}

	if(*k < btn->n - 1) {
		*k++;
		return btn;
	}

	while(*k == btn->n - 1) {

		if(btn->pai == NULL) {
			return NULL;
		}
		if(btn == btn->pai->p[btn->n]) {
			btn = btn->pai;
		}
		else {
			pai = btn->pai;
			for(i = btn->n; btn != pai->p[i]; i--);
			btn = pai;
			*k = i;
			break;
		}
	}

	return btn;
}

fila_t * search_tree(void * data, arvore_t * tree) {

    btNode_t * btn;
    fila_t * fila;
    fila = cria_fila();
    int i;
    int found = 0;

    if(tree->raiz == NULL) {
        return NULL;
    }

    btNode_t * bnt = tree->raiz;

    while(!found){
            if (btn == NULL){
                return NULL;
            }
        for(i = 0; i < btn->n; i++) {
            if(tree->comp(data, btn->key[i]) == 0) {
                found = 1;
                break;
            }

        else if(tree->comp(data, btn->key[i]) < 0) {
            i = searchKey(btn, data, tree);
            btn = btn->p[i];
            break;
            }
        }
    }

    while(tree->comp(data, btn->key[i]) == 0){
        btn = keyPrev(btn, &i);
    }

    btn = keyNext(btn, &i);

    while(tree->comp(data, btn->key[i]) == 0){
        enqueue(btn->key[i], fila);
        keyNext(btn, &i);
    }

    return fila;
}

static btNode_t* go_to_leaf(btNode_t* node, void* data, arvore_t* tree) {
    int pos;

    while(!node->leaf) {
        pos = searchKey(node, data, tree);
        node = node->p[pos];
    }

    return node;
}

//só funciona p/ ordem 3
static btNode_t* split_node(btNode_t* btn, void* data, arvore_t* tree) {
    btNode_t* btn2;
    btNode_t* aux;
    int mid = median(btn, data, tree);
    int i;

    if (mid != -1) {
        aux = data;
        data = btn->key[mid];
        btn->key[mid] = aux;
    }

    btn2 = tree_node_create();

    btn2->n = btn->n -1;
    btn2->leaf = btn->leaf;
    btn2->pai = btn->pai;

    btn2->key[0] = btn->key[1];
    if (!btn->leaf) {
        for (i = 0; i < btn2->n; i++) {
            btn2->p[i] = btn->p[i+1];
        }
    }

    btn->n = btn->n -1;

    return btn2;
}

// retorna posição do dado medio, se o medio for o dado a ser inserido retorna -1
static int median (btNode_t* btn, void* data, arvore_t* tree) {

    if (tree->comp(data, btn->key[0]) >= 0 && tree->comp(data, btn->key[1]) == -1) {
        return -1;
    }

    if (tree->comp(data, btn->key[0]) == -1) {
        return 0;
    } else {
        return 1;
    }
}

void print_dot (btNode_t* node, FILE* arquivo, char*(*title_func)(void*)) {
    if (node) {
        if (!node->pai) {
            fputs("graph{", arquivo);
        }

        fprintf(arquivo, "n%p [label=%s", node, title_func(node->key[0]));
        if (node->n > 1) {
            fprintf(arquivo, " %s];\n", title_func(node->key[1]));
        } else {
            fputs("];", arquivo);
        }

        if(node->pai) {
            fprintf(arquivo,"%p -- %p;\n", node, node->pai);
        }

        print_dot(node->p[0], arquivo, title_func);
        print_dot(node->p[1], arquivo, title_func);
        print_dot(node->p[3], arquivo, title_func);

        if (!node->pai) {
            fputs("}", arquivo);
        }

    }
}
