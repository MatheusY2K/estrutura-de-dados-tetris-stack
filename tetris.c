#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#define TAMANHO_FILA 5 // Tamanho fixo da fila

// Estrutura de uma peça
typedef struct {
    char nome; 
    int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca pecas[TAMANHO_FILA]; 
    int inicio;
    int fim;
    int qtd;
} Fila;

// Função para iniciar fila vazia
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = -1;
    f->qtd = 0;
}

// Cria uma nova peça com o tipo aleatório 
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4]; // Escolhe tipo aleatório
    nova.id = id; //Define o id
    return nova;
}

// Insere uma nova peça no final da fila (enqueue)
void inserirPeca(Fila *f, Peca p) {
    if (f->qtd == TAMANHO_FILA){
        printf("\nFila cheia! Não é possivel adicionar mais peças.\n");
        return;
    }
    f->fim = (f->fim + 1) % TAMANHO_FILA; // Move o fim circulamente
    f->pecas[f->fim] = p;
    f->qtd++;
}

// Remove a peça da frente da fila (dequeue)
void jogarPeca(Fila *f) {
    if (f->qtd == 0) {
        printf("\nFila vazia! Sem peças para jogar.\n");
        return;
    }
    Peca p = f->pecas[f->inicio];
    printf("\nPeca jogada: [%c %d]\n", p.nome, p.id);
    f->inicio = (f->inicio + 1) % TAMANHO_FILA; // Move o inicio circulamente
    f->qtd--;
}

// Mostra a fila atual
void exibirFila(Fila f) {
    printf("\nFila de peças:\n");
    if (f.qtd == 0) {
        printf("(Vazia)\n");
        return;
    }
    int i, pos = f.inicio;
    for (i = 0; i < f.qtd; i++) {
        Peca p = f.pecas[pos];
        printf("[%c %d] ", p.nome, p.id);
        pos = (pos + 1) % TAMANHO_FILA; // Passa para o próximo circularmente
    }
    printf("\n");
}

int main() {
    srand(time(NULL)); // Garante peças aleatórias
    Fila fila;
    inicializarFila(&fila);

    int opcao, contador = 0;

    // Começa a fila com 5 peças
    for (int i = 0; i < TAMANHO_FILA; i++) {
        inserirPeca(&fila, gerarPeca(contador++));
    }

    do {
        exibirFila(fila);
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                inserirPeca(&fila, gerarPeca(contador++));
                break;
            case 0: 
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida!\n"); 
        }
    } while (opcao != 0);

    return 0;
}