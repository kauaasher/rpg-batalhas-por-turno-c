#include <stdlib.h>
#include "desfazer.h"

/*
    Para guardar estados anteriores da batalha e permitir restaurá-los.
*/

/*
    Fala configurar com o resto do projeto: Incompleto
*/

/* Inicializa a pilha de desfazer */
void desfazer_inicializar(PilhaDesfazer *pilha) {
    if (pilha == NULL) return;

    pilha->topo = NULL;
    pilha->quantidade = 0;
    pilha->usos = 0;

    pilha->copiar = NULL;
    pilha->restaurar = NULL;
    pilha->liberar = NULL;
}

/* Configura as funcoes de manipulacao do estado */
void desfazer_configurar(
    PilhaDesfazer *pilha,
    DesfazerCopiarEstado copiar,
    DesfazerRestaurarEstado restaurar,
    DesfazerLiberarEstado liberar
) {
    if (pilha == NULL) return;

    pilha->copiar = copiar;
    pilha->restaurar = restaurar;
    pilha->liberar = liberar;
}

/* Registra uma copia do estado atual da batalha */
int desfazer_registrar(
    PilhaDesfazer *pilha,
    const EstadoBatalha *estado
) {
    if (pilha == NULL || estado == NULL)
        return 0;

    if (pilha->copiar == NULL || pilha->liberar == NULL)
        return 0;

    /* Cria uma copia independente do estado */
    EstadoBatalha *copia = pilha->copiar(estado);

    if (copia == NULL)
        return 0;

    /* Cria um novo no para armazenar a copia */
    NoDesfazer *novo = malloc(sizeof(NoDesfazer));

    if (novo == NULL) {
        pilha->liberar(copia);
        return 0;
    }

    novo->estado = copia;
    novo->prox = pilha->topo;

    pilha->topo = novo;
    pilha->quantidade++;

    return 1;
}

/* Restaura o estado anterior da batalha */
int desfazer_aplicar(
    PilhaDesfazer *pilha,
    EstadoBatalha *estado
) {
    if (pilha == NULL || estado == NULL)
        return 0;

    if (!desfazer_pode_usar(pilha))
        return 0;

    if (pilha->restaurar == NULL || pilha->liberar == NULL)
        return 0;

    /* Obtém o estado salvo no topo */
    NoDesfazer *removido = pilha->topo;

    /* Tenta restaurar o estado da batalha */
    if (!pilha->restaurar(estado, removido->estado))
        return 0;

    /* Remove o estado utilizado da pilha */
    pilha->topo = removido->prox;
    pilha->quantidade--;

    /* Libera a copia que foi utilizada */
    pilha->liberar(removido->estado);
    free(removido);

    /* Contabiliza a utilizacao do desfazer */
    pilha->usos++;

    return 1;
}

/* Verifica se ainda existem utilizacoes disponiveis */
int desfazer_pode_usar(PilhaDesfazer *pilha) {
    if (pilha == NULL)
        return 0;

    if (pilha->usos >= 3)
        return 0;

    if (pilha->topo == NULL)
        return 0;

    return 1;
}

/* Verifica se a pilha esta vazia */
int desfazer_vazio(PilhaDesfazer *pilha) {
    if (pilha == NULL || pilha->topo == NULL)
        return 1;

    return 0;
}

/* Libera todos os estados armazenados */
void desfazer_liberar(PilhaDesfazer *pilha) {
    if (pilha == NULL) return;

    NoDesfazer *atual = pilha->topo;

    while (atual != NULL) {
        NoDesfazer *proximo = atual->prox;

        /* Libera a copia do estado, se possivel */
        if (pilha->liberar != NULL && atual->estado != NULL)
            pilha->liberar(atual->estado);

        free(atual);

        atual = proximo;
    }

    pilha->topo = NULL;
    pilha->quantidade = 0;
    pilha->usos = 0;
}