#ifndef MAPA2_H
#define MAPA2_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct tp_no {
    char caminho[50]; 
    struct tp_no* prox;
};

int vida_r = 20;
int mana_r = 10;

struct tp_no* novo_no(char caminho[]) {
    struct tp_no* no = (struct tp_no*)malloc(sizeof(struct tp_no));
    if (no == NULL) {
        textcolor(4);
        printf("[ SISTEMA ]: ERRO!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(no->caminho, caminho);
    no->prox = NULL;
    return no;
}


void imprimir_locAtual(struct tp_no* localAtual) {
    printf("[ SISTEMA ]: VOCE ESTA AGORA EM: %s.\n", localAtual->caminho);
}


struct tp_no* avancar_prox(struct tp_no* localAtual) {
    printf("[ SISTEMA ]: VOCE VENCEU O INIMIGO: ! COM ISSO AVANCE PARA O PROXIMO MAPA.\n");
    
    return localAtual->prox;
}


int escolha_desvio() {
    int escolher;
    printf("====== [ PONTO DE ESCOLHA ] ======\n");
    textcolor(10);
    printf("1. Seguir em frente para o proximo inimigo.\n");
    textcolor(4);
    printf("2. Recuperar vida e mana.\n");
    textcolor(15);
    printf("Escolha: ");
    scanf("%d", &escolher);
    return escolher;
}


void desvios_ponto(struct tp_no** posAtual) {
    vida_r = 20;
    mana_r = 10;
    printf("[ SISTEMA ]: VOCE ESTA EM %s. COM ISSO SUA VIDA FOI RECUPERADA EM [ %d ] E SUA MANA EM [ %d ].\n", (*posAtual)->caminho, vida_r, mana_r);      
    system("pause");

    if(posAtual == (*posAtual)->caminho, "Aldeia da Liberdade"){
        *posAtual = (*posAtual)->prox->prox;
    } else if(posAtual == (*posAtual)->caminho, "Paraiso das Brisas"){
        *posAtual = (*posAtual)->prox;
    }
}

void imprime_mapa(void){
    //textcolor(4);
    printf("    [ MAPA ]       \n\n");
    printf("        B <-----  \n");
    printf("        ^      |  \n");
    printf("        |      |  \n");
    printf("        D      |  \n");
    printf("        ^      |  \n");
    printf("        |----> C  \n");
    printf("  ----> C         \n");
    printf("  |     ^         \n");
    printf("  |     |         \n");
    printf("  |     C         \n");
    printf("  |     ^         \n");
    printf("  D <---|         \n");
    printf("        C         \n\n");

    printf("[ LEGENDA ]:\n\n[ C ] = Area de combate\n[ D ] = Ponto de Descanso\n[ B ] = Boss Final\n");
    system("pause");
    system("cls");
}

#endif
