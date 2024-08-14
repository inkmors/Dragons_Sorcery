#ifndef DECK_H
#define DECK_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "JOGADOR.h"

#define NUM_CARTAS_CAVA 12
#define TAM_MAO 5
#define MANA_INICIAL 10
#define MAX_CARTAS_USADAS 20

typedef enum {
    ATAQUE,
    DEFESA,
    ULTIMATE,
    CURA
} TipoCarta;

typedef struct {
    char nome[50];
    TipoCarta tipo;
    int valor;
    int custo;
    int danoAtaque;
    int danoDefesa;
    int danoUltimate;
    int id;
} Carta;

typedef struct {
    Carta *cartas;
    int topo; 
    int tamanho; 
} PilhaCartas;

void inicializa_Pilha(PilhaCartas *pilha, int tamanho) {
    pilha->cartas = (Carta *)malloc(tamanho * sizeof(Carta));
    pilha->topo = -1;
    pilha->tamanho = tamanho;
}

void push(PilhaCartas *pilha, Carta carta) {
    if (pilha->topo == pilha->tamanho - 1) {
        printf("[ ERRO ]:Pilha cheia. Impossível empilhar.\n");
        return;
    }

    pilha->topo++;
    pilha->cartas[pilha->topo] = carta;
}

Carta pop(PilhaCartas *pilha) {
    if (pilha->topo == -1) {
        printf("[ ERRO ]: Pilha vazia. Impossível desempilhar.\n");
        Carta cartaVazia = {"", ATAQUE, 0, 0, 0, 0, 0}; 
        return cartaVazia;
    }

    Carta cartaDesempilhada = pilha->cartas[pilha->topo];
    pilha->topo--;

    return cartaDesempilhada;
}

int cartasUsadas[MAX_CARTAS_USADAS] = {0};

void gravarCartaEscolhida(Carta carta) {
    FILE *arquivo;
    arquivo = fopen("cartas.txt", "a");

    if (arquivo == NULL) {
        printf("[ SISTEMA ]: Erro.\n");
        return;
    }

    fprintf(arquivo, "%s %d %d %d %d %d %d %d\n",
            carta.nome, carta.tipo, carta.valor,
            carta.custo, carta.danoAtaque, carta.danoDefesa, carta.danoUltimate,
            carta.id);

    fclose(arquivo);
}

void exibirCartasUsadas() {
    FILE *arquivo;
    arquivo = fopen("cartas.txt", "r");

    if (arquivo == NULL) {
        textcolor(4);
        printf("[ SISTEMA ]: Nenhuma carta usada ate o momento.\n");
        textcolor(15);
        return;
    }
    textcolor(10);
    printf("[ SISTEMA ]: Cartas usadas ate o momento:\n");
    textcolor(15);
    Carta cartaLida;
    while (fscanf(arquivo, "%s %d %d %d %d %d %d %d\n",
                  cartaLida.nome, &cartaLida.tipo, &cartaLida.valor,
                  &cartaLida.custo, &cartaLida.danoAtaque, &cartaLida.danoDefesa, &cartaLida.danoUltimate,
                  &cartaLida.id) != EOF) {
        printf(" %s \n", cartaLida.nome);
    }

    fclose(arquivo);
}

void apagarCartasArquivo() {
    FILE *arquivo;
    arquivo = fopen("cartas.txt", "w");

    if (arquivo == NULL) {
        textcolor(4);
        printf("[ SISTEMA ]: Erro.\n");
        return;
    }

    fclose(arquivo);
}

int cartaFoiUsada(int idCarta) {
    for (int i = 0; i < MAX_CARTAS_USADAS; i++) {
        if (cartasUsadas[i] == idCarta) {
            return 1; 
        }
    }
    return 0;
}

void marcarCartaComoUsada(int idCarta) {
    for (int i = 0; i < MAX_CARTAS_USADAS; i++) {
        if (cartasUsadas[i] == 0) {
            cartasUsadas[i] = idCarta;
            break;
        }
    }
}

void embaralharCartas(Carta *cartas, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int j = i + rand() % (tamanho - i);
        Carta temp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = temp;
    }
}

void imprime_mao(Carta *mao, int tamanho, int mana_r) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d. Nome: %s, Tipo: ", i + 1, mao[i].nome);
        switch (mao[i].tipo) {
            case ATAQUE:
                textcolor(4);
                printf("[ CARTA ]: (ATAQUE) | ( Custo ): %d | ( Dano ): %d | ( ID ): %d\n", mao[i].custo, mao[i].danoAtaque, mao[i].id);
                textcolor(15);
                break;
            case DEFESA:
                textcolor(14);
                printf("[ CARTA ]: (DEFESA) | ( Custo ): %d | ( Defesa ): %d | ( ID ): %d\n", mao[i].custo, mao[i].danoDefesa, mao[i].id);
                textcolor(15);
                break;
            case ULTIMATE:
                textcolor(9);
                printf("[ CARTA ]: (ULTIMATE) | ( Custo ): %d | ( Dano ): %d | ( ID ): %d\n", mao[i].custo, mao[i].danoUltimate, mao[i].id);
                textcolor(15);
                break;
            case CURA:
                textcolor(10);
                printf("[ CARTA ]: (CURA) | ( Custo ): %d | ( Valor ): %d | ( ID ): %d\n", mao[i].custo, mao[i].valor, mao[i].id);
                textcolor(15);
                break;
        }
    }
    printf("\n");
}


#endif