
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lista.h"

/*
    Para Implementar o inventário, incluindo inserção ordenada, busca, remoção e consumo de itens.
*/


// Compara dois nomes sem diferenciar letras maiusculas e minusculas
static int comparar_nomes(const char *nome1, const char *nome2) {
    while (*nome1 && *nome2) {
        int letra1 = tolower((unsigned char)*nome1);
        int letra2 = tolower((unsigned char)*nome2);

        if (letra1 != letra2) {
            return letra1 - letra2;
        }

        nome1++;
        nome2++;
    }

    return tolower((unsigned char)*nome1) -
           tolower((unsigned char)*nome2);
}

// Inicializa o inventario
void lista_inicializar(ListaInventario *lista) {
    if (lista == NULL) {
        return;
    }

    lista->inicio = NULL;
    lista->tamanho = 0;
}

// Insere um item em ordem alfabetica
int lista_inserir(ListaInventario *lista, const Item *item) {
    if (lista == NULL || item == NULL ||
        item->nome[0] == '\0' || item->quantidade <= 0) {
        return 0;
    }

    // Verifica se o item ja existe
    if (lista_buscar(lista, item->nome) != NULL) {
        return 0;
    }

    // Cria um novo no
    NoItem *novo = malloc(sizeof(NoItem));

    if (novo == NULL) {
        return 0;
    }

    novo->item = *item;
    novo->prox = NULL;

    // Insere no inicio, se for o primeiro ou vier antes
    if (lista->inicio == NULL ||
        comparar_nomes(item->nome, lista->inicio->item.nome) < 0) {

        novo->prox = lista->inicio;
        lista->inicio = novo;

    } else {
        // Procura a posicao correta
        NoItem *atual = lista->inicio;

        while (atual->prox != NULL &&
               comparar_nomes(atual->prox->item.nome, item->nome) < 0) {
            atual = atual->prox;
        }

        novo->prox = atual->prox;
        atual->prox = novo;
    }

    lista->tamanho++;

    return 1;
}

// Busca um item pelo nome
Item *lista_buscar(ListaInventario *lista, const char *nome) {
    if (lista == NULL || nome == NULL) {
        return NULL;
    }

    NoItem *atual = lista->inicio;

    while (atual != NULL) {
        if (comparar_nomes(atual->item.nome, nome) == 0) {
            return &atual->item;
        }

        atual = atual->prox;
    }

    return NULL;
}

// Remove um item pelo nome
int lista_remover(ListaInventario *lista, const char *nome) {
    if (lista == NULL || nome == NULL) {
        return 0;
    }

    NoItem *atual = lista->inicio;
    NoItem *anterior = NULL;

    while (atual != NULL) {
        if (comparar_nomes(atual->item.nome, nome) == 0) {

            // Se for o primeiro no
            if (anterior == NULL) {
                lista->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            free(atual);
            lista->tamanho--;

            return 1;
        }

        anterior = atual;
        atual = atual->prox;
    }

    return 0;
}

// Atualiza a quantidade de um item
int lista_atualizar_quantidade(ListaInventario *lista,
                               const char *nome, int quantidade) {
    if (lista == NULL || nome == NULL || quantidade <= 0) {
        return 0;
    }

    Item *item = lista_buscar(lista, nome);

    if (item == NULL) {
        return 0;
    }

    item->quantidade = quantidade;

    return 1;
}

// Consome uma unidade de um item
int lista_consumir(ListaInventario *lista, const char *nome) {
    if (lista == NULL || nome == NULL) {
        return 0;
    }

    Item *item = lista_buscar(lista, nome);

    if (item == NULL) {
        return 0;
    }

    item->quantidade--;

    // Remove o item se a quantidade chegar a zero
    if (item->quantidade == 0) {
        lista_remover(lista, nome);
    }

    return 1;
}

// Exibe os itens do inventario
void lista_exibir(ListaInventario *lista) {
    if (lista == NULL) {
        return;
    }

    NoItem *atual = lista->inicio;

    printf("\n===== INVENTARIO =====\n");

    if (atual == NULL) {
        printf("O inventario esta vazio.\n");
        return;
    }

    while (atual != NULL) {
        printf("ID: %d | Nome: %s | Quantidade: %d | Tipo: %d\n",
               atual->item.id,
               atual->item.nome,
               atual->item.quantidade,
               atual->item.tipo);

        atual = atual->prox;
    }

    printf("Total de itens diferentes: %d\n", lista->tamanho);
}

// Libera toda a memoria do inventario
void lista_liberar(ListaInventario *lista) {
    if (lista == NULL) {
        return;
    }

    NoItem *atual = lista->inicio;

    while (atual != NULL) {
        NoItem *proximo = atual->prox;

        free(atual);

        atual = proximo;
    }

    lista->inicio = NULL;
    lista->tamanho = 0;
}
