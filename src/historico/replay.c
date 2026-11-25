#include <stdio.h>
#include "replay.h"

/*
    Fala configurar com o resto do projeto: Incompleto
*/

/* Inicializa o replay */
void replay_inicializar(Replay *replay) {
    if (replay == NULL) return;

    replay->historico = NULL;
    replay->atual = NULL;
    replay->posicao = 0;
    replay->reproduzindo = 0;
}

/* Prepara o replay para uma batalha */
int replay_iniciar(Replay *replay, const LogBatalha *historico) {
    if (replay == NULL || historico == NULL)
        return 0;

    if (historico->inicio == NULL)
        return 0;

    replay->historico = historico;
    replay->atual = historico->inicio;
    replay->posicao = 0;
    replay->reproduzindo = 1;

    return 1;
}

/* Reinicia a reproducao desde o primeiro acontecimento */
void replay_reiniciar(Replay *replay) {
    if (replay == NULL || replay->historico == NULL)
        return;

    replay->atual = replay->historico->inicio;
    replay->posicao = 0;
    replay->reproduzindo = 1;
}

/* Retorna o proximo acontecimento */
const NoLog *replay_proximo(Replay *replay) {
    if (replay == NULL || !replay->reproduzindo)
        return NULL;

    if (replay->atual == NULL) {
        replay->reproduzindo = 0;
        return NULL;
    }

    const NoLog *registro = replay->atual;

    replay->atual = replay->atual->prox;
    replay->posicao++;

    if (replay->atual == NULL)
        replay->reproduzindo = 0;

    return registro;
}

/* Exibe o proximo acontecimento */
void replay_exibir_proximo(Replay *replay) {
    const NoLog *registro = replay_proximo(replay);

    if (registro == NULL) {
        printf("\nFim do replay.\n");
        return;
    }

    printf("\n========== REPLAY DA BATALHA ==========\n");

    printf("Registro: %d\n", registro->sequencia);
    printf("Rodada: %d\n", registro->rodada);

    switch (registro->tipo) {

        case LOG_INICIO_BATALHA:
            printf("[INICIO DA BATALHA]\n");
            break;

        case LOG_ATAQUE:
            printf("[ATAQUE]\n");
            break;

        case LOG_DANO:
            printf("[DANO]\n");
            break;

        case LOG_CURA:
            printf("[CURA]\n");
            break;

        case LOG_USO_ITEM:
            printf("[USO DE ITEM]\n");
            break;

        case LOG_EFEITO_APLICADO:
            printf("[EFEITO APLICADO]\n");
            break;

        case LOG_EFEITO_REMOVIDO:
            printf("[EFEITO REMOVIDO]\n");
            break;

        case LOG_PASSAGEM_RODADA:
            printf("[PASSAGEM DE RODADA]\n");
            break;

        case LOG_DESFAZER:
            printf("[DESFAZER - ESTADO RESTAURADO]\n");
            break;

        case LOG_FIM_BATALHA:
            printf("[FIM DA BATALHA]\n");
            break;

        default:
            printf("[OUTRO ACONTECIMENTO]\n");
            break;
    }

    if (registro->ator[0] != '\0')
        printf("Ator: %s\n", registro->ator);

    if (registro->alvo[0] != '\0')
        printf("Alvo: %s\n", registro->alvo);

    printf("Descricao: %s\n", registro->descricao);

    if (registro->valor != 0)
        printf("Valor: %d\n", registro->valor);

    if (registro->referencia > 0)
        printf("Registro relacionado: %d\n", registro->referencia);

    printf("=======================================\n");
}

/* Verifica se a reproducao terminou */
int replay_finalizado(Replay *replay) {
    if (replay == NULL)
        return 1;

    return !replay->reproduzindo;
}

/* Verifica se o historico esta vazio */
int replay_vazio(Replay *replay) {
    if (replay == NULL || replay->historico == NULL)
        return 1;

    return replay->historico->inicio == NULL;
}

/* Encerra o replay */
void replay_finalizar(Replay *replay) {
    if (replay == NULL) return;

    replay->historico = NULL;
    replay->atual = NULL;
    replay->posicao = 0;
    replay->reproduzindo = 0;
}