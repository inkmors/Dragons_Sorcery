#ifndef FILAM_H
#define FILAM_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_INIMIGOS 5

typedef struct {
    int tipo;
} Acao;

typedef struct {
    char nome[20];
    int vida;
    int ataque;
    int defesa;
    int ultimate;
    Acao acoes[50];
    int frente;       
    int tras;
} Inimigo;


void inicializarInimigo(Inimigo* inimigo, char nome[]) {
    snprintf(inimigo->nome, sizeof(inimigo->nome), "%s", nome);
    inimigo->frente = -1;
    inimigo->tras = -1;
}

void inserir_fila(Inimigo* inimigo, Acao acao) {
    if ((inimigo->frente == 0 && inimigo->tras == sizeof(inimigo->acoes) - 1) || (inimigo->tras == (inimigo->frente - 1) % (sizeof(inimigo->acoes) - 1))) {
        textcolor(4);
        printf("[ ERRO ]:Fila cheia. Acao nao enfileirada.\n");
        textcolor(15);
        return;
    }

    if (inimigo->frente == -1) {
        inimigo->frente = inimigo->tras = 0;
        inimigo->acoes[inimigo->tras] = acao;
    } else {
        inimigo->tras = (inimigo->tras + 1) % sizeof(inimigo->acoes);
        inimigo->acoes[inimigo->tras] = acao;
    }
} 

Acao remover_fila(Inimigo* inimigo) {
    Acao acaoVazia = {-1}; 

    if (inimigo->frente == -1) {
        textcolor(4);
        printf("[ ERRO ]: Fila vazia. Nenhuma acao desenfileirada.\n");
        textcolor(15);
        return acaoVazia;
    }

    Acao acao = inimigo->acoes[inimigo->frente];
    if (inimigo->frente == inimigo->tras) {
        inimigo->frente = inimigo->tras = -1;
    } else {
        inimigo->frente = (inimigo->frente + 1) % sizeof(inimigo->acoes);
    }

    inserir_fila(inimigo, acao);

    return acao;
}

void imprime_fila(Inimigo* inimigo) {
    if (inimigo->frente == -1) {
        textcolor(4);
        printf("[ ERRO ]: Fila vazia.\n");
        textcolor(15);
        return;
    }

    int i = inimigo->frente;
    printf("Inimigo %s : Acoes na fila:\n", inimigo->nome);
    do {
        printf("Acao %d\n", inimigo->acoes[i].tipo);
        i = (i + 1) % sizeof(inimigo->acoes);
    } while (i != (inimigo->tras + 1) % sizeof(inimigo->acoes));
}

extern Inimigo inimigos[5];

Inimigo criarInimigo(const char *nome, int vida, int ataque, int defesa, int ultimate) {
    Inimigo inimigo;
    sprintf(inimigo.nome, "%s", nome);
    inimigo.vida = vida;
    inimigo.ataque = ataque;
    inimigo.defesa = defesa;
    inimigo.ultimate = ultimate;
    return inimigo;
}

int inimigoAtual = 0;

int inicializarInimigos(Inimigo *inimigos) {
    inimigos[0] = criarInimigo("Slovk", 10, 2, 1, 5);
    inimigos[1] = criarInimigo("Dungenar", 10, 4, 2, 3);
    inimigos[2] = criarInimigo("Bong Bong", 15, 4, 3, 4);
    inimigos[3] = criarInimigo("Mors Semi Boss", 15, 5, 5, 7);
    inimigos[4] = criarInimigo("Soussa Final Boss", 20, 7, 8, 10);

    if(inimigoAtual == 0){

        textcolor(4);
        printf("========== | INFORMACOES DO PRIMEIRO MONSTRO | ==========\n\n");
        textcolor(15);
        printf("      [ NOME ]: %s\n", inimigos[0].nome);
        printf("      [ VIDA ]: %d\n", inimigos[0].vida);
        printf("      [ ATAQUE ]: %d\n", inimigos[0].ataque);
        printf("      [ DEFESA ]: %d\n", inimigos[0].defesa);
        printf("      [ ULTIMATE ]: %d\n", inimigos[0].ultimate);
        printf("====================================================\n\n\n");
        system("pause");
        system("cls");
    } else if(inimigoAtual == 1){

        textcolor(4);
        printf("========== | INFORMACOES DO SEGUNDO MONSTRO | ==========\n\n");
        textcolor(15);
        printf("      [ NOME ]: %s\n", inimigos[1].nome);
        printf("      [ VIDA ]: %d\n", inimigos[1].vida);
        printf("      [ ATAQUE ]: %d\n", inimigos[1].ataque);
        printf("      [ DEFESA ]: %d\n", inimigos[1].defesa);
        printf("      [ ULTIMATE ]: %d\n", inimigos[1].ultimate);
        printf("====================================================\n\n\n");
        system("pause");
        system("cls");
    } else if(inimigoAtual == 2){

        textcolor(4);
        printf("========== | INFORMACOES DO TERCEIRO MONSTRO | ==========\n\n");
        textcolor(15);
        printf("      [ NOME ]: %s\n", inimigos[2].nome);
        printf("      [ VIDA ]: %d\n", inimigos[2].vida);
        printf("      [ ATAQUE ]: %d\n", inimigos[2].ataque);
        printf("      [ DEFESA ]: %d\n", inimigos[2].defesa);
        printf("      [ ULTIMATE ]: %d\n", inimigos[2].ultimate);
        printf("====================================================\n\n\n");
        system("pause");
        system("cls");
    } else if(inimigoAtual == 3){

        textcolor(4);
        printf("========== | INFORMACOES DO QUARTO MONSTRO | ==========\n\n");
        textcolor(15);
        printf("      [ NOME ]: %s\n", inimigos[3].nome);
        printf("      [ VIDA ]: %d\n", inimigos[3].vida);
        printf("      [ ATAQUE ]: %d\n", inimigos[3].ataque);
        printf("      [ DEFESA ]: %d\n", inimigos[3].defesa);
        printf("      [ ULTIMATE ]: %d\n", inimigos[3].ultimate);
        printf("====================================================\n\n\n");
        system("pause");
        system("cls");
    } else if(inimigoAtual == 4){

        textcolor(4);
        printf("========== | INFORMACOES DO BOSS FINAL | ==========\n\n");
        textcolor(15);
        printf("      [ NOME ]: %s\n", inimigos[4].nome);
        printf("      [ VIDA ]: %d\n", inimigos[4].vida);
        printf("      [ ATAQUE ]: %d\n", inimigos[4].ataque);
        printf("      [ DEFESA ]: %d\n", inimigos[4].defesa);
        printf("      [ ULTIMATE ]: %d\n", inimigos[4].ultimate);
        printf("====================================================\n\n\n");
        system("pause");
        system("cls");
    } else 

    return 0;  
}

void imprime_inimigo(Inimigo *inimigo) {
    textcolor(4);
    printf("[ INIMIGO ]:\n");
    textcolor(15);
    printf("[ NOME ]: %s | [ VIDA ]: %d | [ ATAQUE ]: %d | [ DEFESA ]: %d | [ ULTIMATE ]: %d\n\n", inimigo->nome, inimigo->vida, inimigo->ataque, inimigo->defesa, inimigo->ultimate);
}

#endif

