#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

/*
    Fala configurar com o resto do projeto: Incompleto
*/

/* Copia um texto com limite de tamanho */
static void copiar_texto(char *destino, const char *origem, int tamanho) {
    if (origem == NULL) {
        destino[0] = '\0';
        return;
    }

    strncpy(destino, origem, tamanho - 1);
    destino[tamanho - 1] = '\0';
}

/* Inicializa o historico */
void log_inicializar(LogBatalha *log) {
    if (log == NULL) return;

    log->inicio = NULL;
    log->fim = NULL;
    log->quantidade = 0;
    log->proxima_sequencia = 1;
}

/* Registra um acontecimento no historico */
int log_registrar(
    LogBatalha *log,
    int rodada,
    int tipo,
    const char *ator,
    const char *alvo,
    const char *descricao,
    int valor,
    int referencia
) {
    if (log == NULL || descricao == NULL)
        return 0;

    if (tipo < LOG_INICIO_BATALHA || tipo > LOG_OUTRO)
        return 0;

    if (rodada < 0)
        return 0;

    NoLog *novo = malloc(sizeof(NoLog));

    if (novo == NULL)
        return 0;

    novo->sequencia = log->proxima_sequencia;
    novo->rodada = rodada;
    novo->tipo = tipo;
    novo->valor = valor;
    novo->referencia = referencia;

    copiar_texto(novo->ator, ator, sizeof(novo->ator));
    copiar_texto(novo->alvo, alvo, sizeof(novo->alvo));
    copiar_texto(novo->descricao, descricao, sizeof(novo->descricao));

    novo->prox = NULL;

    /* Insere no final para preservar a ordem dos acontecimentos */
    if (log->inicio == NULL) {
        log->inicio = novo;
        log->fim = novo;
    } else {
        log->fim->prox = novo;
        log->fim = novo;
    }

    log->quantidade++;
    log->proxima_sequencia++;

    return 1;
}

/* Registra quando o jogador utiliza o desfazer */
int log_registrar_desfazer(
    LogBatalha *log,
    int rodada,
    const char *jogador,
    int referencia
) {
    return log_registrar(
        log,
        rodada,
        LOG_DESFAZER,
        jogador,
        NULL,
        "Jogador restaurou um estado anterior da batalha",
        0,
        referencia
    );
}

/* Retorna o primeiro registro */
NoLog *log_primeiro(LogBatalha *log) {
    if (log == NULL)
        return NULL;

    return log->inicio;
}

/* Retorna o proximo registro */
NoLog *log_proximo(NoLog *registro) {
    if (registro == NULL)
        return NULL;

    return registro->prox;
}

/* Busca um registro pela sequencia */
NoLog *log_buscar(LogBatalha *log, int sequencia) {
    if (log == NULL || sequencia <= 0)
        return NULL;

    NoLog *atual = log->inicio;

    while (atual != NULL) {
        if (atual->sequencia == sequencia)
            return atual;

        atual = atual->prox;
    }

    return NULL;
}

/* Exibe todos os acontecimentos registrados */
void log_exibir(LogBatalha *log) {
    if (log == NULL || log->inicio == NULL) {
        printf("Historico vazio.\n");
        return;
    }

    NoLog *atual = log->inicio;

    printf("\n========== HISTORICO DA BATALHA ==========\n");

    while (atual != NULL) {
        printf("\nRegistro: %d", atual->sequencia);
        printf("\nRodada: %d", atual->rodada);
        printf("\nTipo: %d", atual->tipo);

        if (atual->ator[0] != '\0')
            printf("\nAtor: %s", atual->ator);

        if (atual->alvo[0] != '\0')
            printf("\nAlvo: %s", atual->alvo);

        printf("\nDescricao: %s", atual->descricao);
        printf("\nValor: %d", atual->valor);

        if (atual->referencia > 0)
            printf("\nReferencia: %d", atual->referencia);

        printf("\n------------------------------------------\n");

        atual = atual->prox;
    }
}

/* Verifica se o historico esta vazio */
int log_vazio(LogBatalha *log) {
    if (log == NULL || log->inicio == NULL)
        return 1;

    return 0;
}

/* Libera todos os registros */
void log_liberar(LogBatalha *log) {
    if (log == NULL) return;

    NoLog *atual = log->inicio;

    while (atual != NULL) {
        NoLog *proximo = atual->prox;

        free(atual);

        atual = proximo;
    }

    log->inicio = NULL;
    log->fim = NULL;
    log->quantidade = 0;
    log->proxima_sequencia = 1;
}