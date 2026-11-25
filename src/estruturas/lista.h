
#ifndef LISTA_H
#define LISTA_H

/*
    Para Implementar o inventário, incluindo inserção ordenada, busca, remoção e consumo de itens.
*/

// Tipos de itens do inventário
#define POCAO 1
#define ARMA 2
#define ARMADURA 3
#define EQUIPAMENTO 4

// Estrutura que representa um item
typedef struct {
    int id;
    char nome[50];
    int quantidade;
    int tipo;

    // Recuperação de recursos
    int recupera_hp;
    int recupera_mana;

    // Bônus nos atributos do personagem
    int bonus_vida;
    int bonus_mana;
    int bonus_velocidade;
    int bonus_inteligencia;
    int bonus_sorte;

} Item;

// Nó da lista encadeada
typedef struct NoItem {
    Item item;
    struct NoItem *prox;
} NoItem;

// Estrutura principal do inventário
typedef struct {
    NoItem *inicio;
    int tamanho;
} ListaInventario;

// Funções da lista
void lista_inicializar(ListaInventario *lista);
int lista_inserir(ListaInventario *lista, const Item *item);
Item *lista_buscar(ListaInventario *lista, const char *nome);
int lista_remover(ListaInventario *lista, const char *nome);
int lista_atualizar_quantidade(ListaInventario *lista, const char *nome, int quantidade);
int lista_consumir(ListaInventario *lista, const char *nome);
void lista_exibir(ListaInventario *lista);
void lista_liberar(ListaInventario *lista);

#endif
