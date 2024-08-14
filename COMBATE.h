#ifndef COMBATE_H
#define COMBATE_H
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "JOGADOR.h"
#include "MAPA.h"
#include "FILA_MONSTRO.h"
#include "DECK.h"

int CartaAtaque(Carta ataque, Inimigo *inimigo) {
    printf("[ SISTEMA ]: Jogador ataca com %s!\n", ataque.nome);

    inimigo->vida -= ataque.danoAtaque;

    if(inimigo->vida >= 0){
        printf("[ SISTEMA ]: Inimigo agora tem %d de vida.\n", inimigo->vida);
    }return 0;
}

void CartaDefesa(Carta defesa, Inimigo *inimigo) {
    printf("Jogador usa %s para se defender.\n", defesa.nome);
    int danoReduzido = inimigo->ataque - defesa.danoDefesa;
    if (danoReduzido > 0) {
        printf("[ SISTEMA ]: Defesa! O jogador sofre %d de dano.\n", danoReduzido);
    } else {
        printf("[ SISTEMA ]: Defesa! O jogador nao sofre dano.\n");
    }
}

void realizarUltimate(Carta ultimate, Inimigo *inimigo) {
    printf("[ SISTEMA ]: Jogador usa %s como ataque ultimate!\n", ultimate.nome);
    inimigo->vida -= ultimate.danoUltimate;
    printf("[ SISTEMA ]: Inimigo agora tem %d de vida.\n", inimigo->vida);
}

void CartaCura(Carta cura, int *vida_r) {
    printf("[ SISTEMA ]: Jogador usa %s para se curar.\n", cura.nome);
    *vida_r += cura.valor;
    printf("[ SISTEMA ]: Jogador agora tem %d de vida.\n", *vida_r);
}

void DefesaInimigo(Carta ataque, Inimigo *inimigo) {
    printf("[ SISTEMA ]: Inimigo se defende!\n");

    int danoReduzido = ataque.danoAtaque - inimigo[inimigoAtual].defesa;

    if (danoReduzido > 0) {
        printf("[ SISTEMA ]: Defesa! O inimigo sofre %d de dano.\n", danoReduzido);
        inimigo->vida -= danoReduzido;
    } else {
        printf("[ SISTEMA ]: Defesa! O inimigo nao sofre dano.\n");
    }
}

void realizarAcoesDoInimigo(Inimigo *inimigo, Carta *mao, int *vida_r) {

    Acao acaoRealizada = remover_fila(inimigo);

    if (acaoRealizada.tipo != -1) {
        int escolhaAcao = rand() % 3; 
        switch (escolhaAcao) {
            case 0:
                printf("Inimigo ataca!\n");
                *vida_r -= inimigo->ataque;
                printf("[ SISTEMA ]: Jogador agora tem %d de vida.\n", *vida_r);
                break;
            case 1:
                //aqui era para ser o defesa do inimigo, porém não consegui resolver e achar uma forma que resolva que o jogador não mate o inimigo antes dele poder se defender
                DefesaInimigo(mao[rand() % TAM_MAO], inimigo);
                break;
            case 2:
                printf("[ SISTEMA ]: Inimigo usa ataque ultimate!\n");
                *vida_r -= inimigo->ultimate;
                printf("[ SISTEMA ]: Jogador agora tem %d de vida.\n", *vida_r);
                break;
        }
    }    
}

Jogador J;

int combate() {
    srand(time(NULL));

    PilhaCartas cava, descarte;
    inicializa_Pilha(&cava, NUM_CARTAS_CAVA);
    inicializa_Pilha(&descarte, NUM_CARTAS_CAVA);

    Carta cartas[NUM_CARTAS_CAVA] = {
        {"Lamina da Tempestade", ATAQUE, 3, 0, 3, 0, 0, 1},
        {"Escudo da Serenidade", DEFESA, 1, 0, 0, 1, 0, 2},
        {"Furia Sombria", ATAQUE, 4, 0, 4, 0, 0, 3},
        {"Barreira do Vento Forte", DEFESA, 2, 0, 0, 2, 0, 4},
        {"Estrela da Manha Ardente", ATAQUE, 2, 0, 2, 0, 0, 5},
        {"Muralha de Espelhos", DEFESA, 2, 0, 0, 2, 0, 6},
        {"Flecha da Aurora", ATAQUE, 1, 0, 1, 0, 0, 7},
        {"Armadura da Aurora", DEFESA, 2, 0, 0, 2, 0, 8},
        {"Punho da Serpente de Fogo", ATAQUE, 4, 0, 4, 0, 0, 9},
        {"Guardiao da Eternidade", DEFESA, 3, 0, 0, 3, 0, 10},
        {"Corte Dimensional Supremo", ULTIMATE, 8, 8, 10, 0, 10, 11},
        {"Pocao da Vitalidade", CURA, 7, 5, 0, 0, 0, 11},
    };

    for (int i = 0; i < NUM_CARTAS_CAVA - 1; i++) {
        int j = i + rand() % (NUM_CARTAS_CAVA - i);
        Carta temp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = temp;
    }

    for (int i = 0; i < NUM_CARTAS_CAVA; i++) {
        push(&cava, cartas[i]);
    }

    Carta *mao = (Carta *)malloc(TAM_MAO * sizeof(Carta));

    for (int i = 0; i < TAM_MAO; i++) {
        mao[i] = pop(&cava);
    }

    Inimigo inimigos[NUM_INIMIGOS];
    inicializarInimigos(inimigos);
    system("cls");

    while (inimigoAtual < NUM_INIMIGOS) {

        do {
            imprime_inimigo(&inimigos[inimigoAtual]);
            imprime_jogador(vida_r, mana_r);
            imprime_mao(mao, TAM_MAO, mana_r);

            textcolor(15);
            printf("[ SISTEMA ]: Escolha uma carta para usar (1 a 5): ");
            int escolha;
            scanf("%d", &escolha);

            if (escolha >= 1 && escolha <= TAM_MAO) {
                Carta cartaEscolhida = mao[escolha - 1];

                if (cartaEscolhida.custo <= mana_r) {
                    switch (cartaEscolhida.tipo) {
                        case ATAQUE:
                            CartaAtaque(cartaEscolhida, &inimigos[inimigoAtual]);
                            break;
                        case DEFESA:
                            CartaDefesa(cartaEscolhida, &inimigos[inimigoAtual]);
                            break;
                        case ULTIMATE:
                            realizarUltimate(cartaEscolhida, &inimigos[inimigoAtual]);
                            break;
                        case CURA:
                            CartaCura(cartaEscolhida, &vida_r);
                            break;
                    }

                    gravarCartaEscolhida(cartaEscolhida);
                    push(&descarte, cartaEscolhida);
                    printf("Carta %s descartada.\n", cartaEscolhida.nome);
                    
                    mao[escolha - 1] = pop(&cava);

                    mana_r -= cartaEscolhida.custo;

                    realizarAcoesDoInimigo(&inimigos[inimigoAtual], &mao, &vida_r);
                    system("pause");
                    system("cls");

                } else {
                    textcolor(4);
                    printf("[ SISTEMA ]: Mana insuficiente para usar esta carta.\n");
                    textcolor(15);
                }

            } else if (escolha != 0) {
                textcolor(4);
                printf("[ SISTEMA ]: Escolha de carta invalida. Tente novamente.\n");
                textcolor(15);
            }

            if (cava.topo == -1) {
                textcolor(4);
                printf("[ SISTEMA ]: Pilha de cava vazia. Embaralhando cartas da pilha de descarte e retornando para a pilha de cava.\n");
                textcolor(10);

                while (descarte.topo >= 0) {
                    push(&cava, pop(&descarte));
                }

                embaralharCartas(cava.cartas, NUM_CARTAS_CAVA);
            }

        } while (vida_r > 0 && inimigos[inimigoAtual].vida > 0);

        if (vida_r > 0) {
            textcolor(10);
            printf("[ SISTEMA ]:  %s derrotado! ###\n\n", inimigos[inimigoAtual].nome);
            textcolor(15);
            exibirCartasUsadas();
            system("pause");
            break;
        } else if(vida_r <= 0) {
            textcolor(4);
            printf("[ SISTEMA ]: NAO FOI DESSA VEZ..... POREM NÃO DESISTA!\n");
            textcolor(15);
            exibirCartasUsadas();
            system("pause");
            break;
        }
    }

    if (inimigoAtual == NUM_INIMIGOS) {
        textcolor(10);
        printf("[ SISTEMA ]: PARABENS! VOCE PROVOU SER UM(A) GUERREIRO(A) E DERROTOU TODOS OS MONSTROS, AGORA TODO PODEM DORMIR EM PAZ!\n");
        exibirCartasUsadas();
        system("pause");
        apagarCartasArquivo();
    }
    free(cava.cartas);
    free(descarte.cartas);
    free(mao);

    return 0;
}

#endif