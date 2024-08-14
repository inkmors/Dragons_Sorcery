#ifndef JOGADOR_H
#define JOGADOR_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include "MAPA.h"

typedef struct Jogador {
    char nome[50];
    int vida;
    int mana;
} Jogador;

Jogador criar_jogador(const char* nome, int vida, int mana) {
    Jogador lutador;
    strcpy(lutador.nome, nome);
    lutador.vida = vida;
    lutador.mana = mana;
    return lutador;
}

extern Jogador J;

void inicializa_jogador(){
    printf("[ SISTEMA ] POR FAVOR INSIRA O NOME DO SEU PERSONAGEM PARA INICIAR O GAME:\n");
    scanf("%s", J.nome);

    J.vida = 20;
    J.mana = 10;

    system("cls");
    textcolor(10);
    printf("========== | INFORMACOES DO(A) GUERREIRO(A) | ==========\n\n");
    textcolor(15);
    printf("         [ NOME ]: %s\n", J.nome);
    printf("         [ VIDA ]: %d\n", J.vida);
    printf("         [ MANA ]: %d\n\n", J.mana);
    printf("====================================================\n\n\n");
    system("pause");
    system("cls"); 

}

void imprime_jogador() {
    textcolor(10);
    printf("[ JOGADOR ]:\n");
    textcolor(15);
    printf("[ Vida ]: %d | [ Mana ]: %d\n\n", vida_r, mana_r);
}

#endif


