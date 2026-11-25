#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

/*
    Para Implementar o efeitos temporários dos personagens e inimigos.
*/


// Inicializa a pilha 
void pilha_inicializar(PilhaEfeitos *pilha) {
    if (pilha == NULL) return;

    pilha->topo = NULL;
}

// Insere um novo efeito na pilha 
int pilha_push(PilhaEfeitos *pilha, const Efeito *efeito) {
    if (pilha == NULL || efeito == NULL) return 0;
    if (efeito->duracao <= 0) return 0;

    if (efeito->tipo < VENENO || efeito->tipo > ATORDOAMENTO)
        return 0;

    Efeito *novo = malloc(sizeof(Efeito));

    if (novo == NULL) return 0;

    *novo = *efeito;

    novo->prox = pilha->topo;
    pilha->topo = novo;

    return 1;
}

// Remove o efeito que esta no topo 
int pilha_pop(PilhaEfeitos *pilha, Efeito *efeito) {
    if (pilha == NULL || pilha->topo == NULL)
        return 0;

    Efeito *removido = pilha->topo;

    if (efeito != NULL) {
        *efeito = *removido;
        efeito->prox = NULL;
    }

    pilha->topo = removido->prox;

    free(removido);

    return 1;
}

// Retorna o efeito que esta no topo 
Efeito *pilha_topo(PilhaEfeitos *pilha) {
    if (pilha == NULL)
        return NULL;

    return pilha->topo;
}

// Retorna o efeito de maior valor de determinado tipo 
Efeito *pilha_efeito_mais_forte(PilhaEfeitos *pilha, int tipo) {
    if (pilha == NULL)
        return NULL;

    Efeito *atual = pilha->topo;
    Efeito *mais_forte = NULL;

    while (atual != NULL) {
        if (atual->tipo == tipo) {
            if (mais_forte == NULL ||
                atual->valor > mais_forte->valor) {

                mais_forte = atual;
            }
        }

        atual = atual->prox;
    }

    return mais_forte;
}

// Diminui a duracao de TODOS os efeitos em uma rodada 
void pilha_atualizar(PilhaEfeitos *pilha) {
    if (pilha == NULL) return;

    Efeito *atual = pilha->topo;
    Efeito *anterior = NULL;

    while (atual != NULL) {
        atual->duracao--;

        if (atual->duracao <= 0) {
            Efeito *removido = atual;

            if (anterior == NULL)
                pilha->topo = atual->prox;
            else
                anterior->prox = atual->prox;

            atual = atual->prox;

            free(removido);
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }
}

// Remove TODOS os efeitos de determinado tipo 
int pilha_remover_tipo(PilhaEfeitos *pilha, int tipo) {
    if (pilha == NULL) return 0;

    Efeito *atual = pilha->topo;
    Efeito *anterior = NULL;
    int removidos = 0;

    while (atual != NULL) {
        if (atual->tipo == tipo) {
            Efeito *removido = atual;

            if (anterior == NULL)
                pilha->topo = atual->prox;
            else
                anterior->prox = atual->prox;

            atual = atual->prox;

            free(removido);
            removidos++;
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }

    return removidos;
}

// Reduz a duracao de todos os efeitos de determinado tipo 
int pilha_reduzir_duracao(PilhaEfeitos *pilha, int tipo, int quantidade) {
    if (pilha == NULL || quantidade <= 0)
        return 0;

    Efeito *atual = pilha->topo;
    Efeito *anterior = NULL;
    int alterados = 0;

    while (atual != NULL) {
        if (atual->tipo == tipo) {
            atual->duracao -= quantidade;
            alterados++;

            if (atual->duracao <= 0) {
                Efeito *removido = atual;

                if (anterior == NULL)
                    pilha->topo = atual->prox;
                else
                    anterior->prox = atual->prox;

                atual = atual->prox;

                free(removido);
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }

    return alterados;
}

// Verifica se a pilha esta vazia 
int pilha_vazia(PilhaEfeitos *pilha) {
    if (pilha == NULL || pilha->topo == NULL)
        return 1;

    return 0;
}

// Libera toda a memoria utilizada pela pilha
void pilha_liberar(PilhaEfeitos *pilha) {
    if (pilha == NULL) return;

    Efeito *atual = pilha->topo;

    while (atual != NULL) {
        Efeito *proximo = atual->prox;

        free(atual);

        atual = proximo;
    }

    pilha->topo = NULL;
}