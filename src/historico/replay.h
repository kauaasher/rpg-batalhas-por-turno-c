#ifndef REPLAY_H
#define REPLAY_H

#include "log.h"

/*
    Fala configurar com o resto do projeto: Incompleto
*/

/* Estrutura responsavel pelo replay */
typedef struct {
    const LogBatalha *historico;
    const NoLog *atual;
    int posicao;
    int reproduzindo;
} Replay;

/* Inicializacao */
void replay_inicializar(Replay *replay);

/* Preparacao e controle */
int replay_iniciar(Replay *replay, const LogBatalha *historico);
void replay_reiniciar(Replay *replay);

/* Reproducao dos acontecimentos */
const NoLog *replay_proximo(Replay *replay);
void replay_exibir_proximo(Replay *replay);

/* Verificacoes */
int replay_finalizado(Replay *replay);
int replay_vazio(Replay *replay);

/* Encerramento */
void replay_finalizar(Replay *replay);

#endif