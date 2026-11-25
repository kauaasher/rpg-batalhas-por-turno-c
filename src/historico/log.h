#ifndef LOG_H
#define LOG_H

/*
    Fala configurar com o resto do projeto: Incompleto
*/

/* Tipos de acontecimentos registrados no historico */
#define LOG_INICIO_BATALHA 1
#define LOG_ATAQUE 2
#define LOG_DANO 3
#define LOG_CURA 4
#define LOG_USO_ITEM 5
#define LOG_EFEITO_APLICADO 6
#define LOG_EFEITO_REMOVIDO 7
#define LOG_PASSAGEM_RODADA 8
#define LOG_DESFAZER 9
#define LOG_FIM_BATALHA 10
#define LOG_OUTRO 11

/* Estrutura de cada acontecimento */
typedef struct NoLog {
    int sequencia;
    int rodada;
    int tipo;

    char ator[50];
    char alvo[50];
    char descricao[150];

    int valor;

    /* Referencia ao registro relacionado, se houver */
    int referencia;

    struct NoLog *prox;
} NoLog;

/* Estrutura principal do historico */
typedef struct {
    NoLog *inicio;
    NoLog *fim;
    int quantidade;
    int proxima_sequencia;
} LogBatalha;

/* Inicializacao */
void log_inicializar(LogBatalha *log);

/* Registro de acontecimentos */
int log_registrar(
    LogBatalha *log,
    int rodada,
    int tipo,
    const char *ator,
    const char *alvo,
    const char *descricao,
    int valor,
    int referencia
);

/* Registro especifico de desfazer */
int log_registrar_desfazer(
    LogBatalha *log,
    int rodada,
    const char *jogador,
    int referencia
);

/* Consulta dos registros */
NoLog *log_primeiro(LogBatalha *log);
NoLog *log_proximo(NoLog *registro);
NoLog *log_buscar(LogBatalha *log, int sequencia);

/* Exibicao e verificacao */
void log_exibir(LogBatalha *log);
int log_vazio(LogBatalha *log);

/* Liberacao de memoria */
void log_liberar(LogBatalha *log);

#endif