#ifndef PILHA_H
#define PILHA_H

/*
    Para Implementar o efeitos temporários dos personagens e inimigos.
*/


/* Tipos fixos de efeitos */
#define VENENO 1
#define QUEIMADURA 2
#define REGENERACAO 3
#define FORTALECIMENTO 4
#define ENFRAQUECIMENTO 5
#define ATORDOAMENTO 6

typedef struct Efeito {
    char nome[50];
    int duracao;
    int tipo;
    int valor;
    struct Efeito *prox;
} Efeito;

typedef struct {
    Efeito *topo;
} PilhaEfeitos;

/* Operacoes basicas da pilha */
void pilha_inicializar(PilhaEfeitos *pilha);
int pilha_push(PilhaEfeitos *pilha, const Efeito *efeito);
int pilha_pop(PilhaEfeitos *pilha, Efeito *efeito);
Efeito *pilha_topo(PilhaEfeitos *pilha);

/* Operacoes com efeitos */
Efeito *pilha_efeito_mais_forte(PilhaEfeitos *pilha, int tipo);
void pilha_atualizar(PilhaEfeitos *pilha);
int pilha_remover_tipo(PilhaEfeitos *pilha, int tipo);
int pilha_reduzir_duracao(PilhaEfeitos *pilha, int tipo, int quantidade);

/* Verificacao e liberacao */
int pilha_vazia(PilhaEfeitos *pilha);
void pilha_liberar(PilhaEfeitos *pilha);

#endif