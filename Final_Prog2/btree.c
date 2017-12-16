#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#define ORDER 3         // Definimos que a ordem da árvore é 3

/*------------ Private function declaration ------------------- */
static int searchKey (btNode_t* btn, void* data, arvore_t* tree);
static void insert_node (void* data, btNode_t* right, btNode_t*  btn, int pos);
static btNode_t* split_node(btNode_t* btn, void* data, arvore_t* tree);
static int median (btNode_t* btn, void* data, arvore_t* tree);
static btNode_t* go_to_leaf(btNode_t* node, void* data, arvore_t* tree);
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

// devolve a posição a ser inserrido o dado ou para qual filho ir
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
            while(1) {
                right = split_node(btn, data, tree);

                if (btn->pai == NULL) {
                    break;
                } else {
                    btn = btn->pai;
                }

                if(btn->n < ORDER-1) {
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
