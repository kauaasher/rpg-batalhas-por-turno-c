#ifndef DESFAZER_H
#define DESFAZER_H

/*
    Para guardar estados anteriores da batalha e permitir restaurá-los.
*/

/*
    Fala configurar com o resto do projeto: Incompleto
*/

/* Estado completo de uma batalha.
   Sua estrutura sera definida durante a integracao. */
typedef struct EstadoBatalha EstadoBatalha;

/* No da pilha de estados anteriores */
typedef struct NoDesfazer {
    EstadoBatalha *estado;
    struct NoDesfazer *prox;
} NoDesfazer;

/* Funcoes que serao fornecidas durante a integracao */
typedef EstadoBatalha *(*DesfazerCopiarEstado)(
    const EstadoBatalha *estado
);

typedef int (*DesfazerRestaurarEstado)(
    EstadoBatalha *destino,
    const EstadoBatalha *origem
);

typedef void (*DesfazerLiberarEstado)(
    EstadoBatalha *estado
);

/* Estrutura principal da pilha */
typedef struct {
    NoDesfazer *topo;
    int quantidade;
    int usos;

    DesfazerCopiarEstado copiar;
    DesfazerRestaurarEstado restaurar;
    DesfazerLiberarEstado liberar;
} PilhaDesfazer;

/* Inicializacao e configuracao */
void desfazer_inicializar(PilhaDesfazer *pilha);

void desfazer_configurar(
    PilhaDesfazer *pilha,
    DesfazerCopiarEstado copiar,
    DesfazerRestaurarEstado restaurar,
    DesfazerLiberarEstado liberar
);

/* Registro e restauracao */
int desfazer_registrar(
    PilhaDesfazer *pilha,
    const EstadoBatalha *estado
);

int desfazer_aplicar(
    PilhaDesfazer *pilha,
    EstadoBatalha *estado
);

/* Verificacoes */
int desfazer_pode_usar(PilhaDesfazer *pilha);
int desfazer_vazio(PilhaDesfazer *pilha);

/* Liberacao de memoria */
void desfazer_liberar(PilhaDesfazer *pilha);

#endif