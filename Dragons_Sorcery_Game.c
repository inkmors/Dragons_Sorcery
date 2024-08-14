
#include <string.h>
#include <math.h>
#include <conio.c>
#include <locale.h>
#include <time.h>
#include "COMBATE.h"

int mapa_principal(){
    struct tp_no* comeco = novo_no("Floresta Esmeralda");
    comeco->prox = novo_no("Aldeia da Liberdade");
    comeco->prox->prox = novo_no("Deserto Ardente");
    comeco->prox->prox->prox = novo_no("Pico do Dragao");
    comeco->prox->prox->prox->prox = novo_no("Paraiso das Brisas");
    comeco->prox->prox->prox->prox->prox = novo_no("Pantano da Desolacao");
    comeco->prox->prox->prox->prox->prox->prox = novo_no("Castelo dos Dados Sombrios");

  
    struct tp_no* posAtual = comeco;

    while (posAtual != NULL) {

        if (strstr(posAtual->caminho, "Aldeia da Liberdade") != NULL){
           
            if (escolha_desvio() == 2) {
                desvios_ponto(&posAtual);
                inimigoAtual = 2;
            } else {
                posAtual = posAtual->prox;
            }
        } else if(strstr(posAtual->caminho, "Paraiso das Brisas") != NULL) {
             if (escolha_desvio() == 2) {
                desvios_ponto(&posAtual);
                inimigoAtual = 4;
            } else {
                posAtual = posAtual->prox;
            }
        } else {
            system("cls");
            textcolor(10);
            printf("[ %s ]\n", posAtual->caminho);
            textcolor(15);
            combate();

            if(inimigoAtual < NUM_INIMIGOS) {
                posAtual = avancar_prox(posAtual);
                inimigoAtual++;
            } else {
                textcolor(10);
                printf("[ SISTEMA ]: Parabens! Voce derrotou todos os inimigos. Voce venceu o jogo!\n");
                textcolor(15);
            break;
            }
        }
    }

    return 0;
}


void jogar()
{
    inicializa_jogador();  

    imprime_mapa();

    mapa_principal();     
}

void regras()
{
    textcolor(4);
    printf("================== | REGRAS | ==================\n");
    textcolor(11);
    printf("[ OBJETIVO ]:\n");
    printf("> Avancar no mapa para derrotar o chefe no final.\n");
    printf("> Como jogar:\n");
    printf("> O jogo e de um jogador contra o computador.\n");
    printf("> O jogador inicia o jogo com um deck de 10 cartas, posicionado no inicio do mapa.\n\n\n");
    textcolor(15);
    
    system("pause");
}

void creditos()
{
    textcolor(4);
    printf("================== | CREDITOS | ==================\n\n");
    textcolor(11);
    printf("[ Jogo esta sendo desenvolvido por aluno de Engenharia da Computacao do Senai CIMATEC ]:\n");
    printf("> Vinicius Lima\n");
    printf("> Professor: Marcio Soussa\n\n");
    textcolor(15);
    system("pause");
}

void sair()
{
    textcolor(4);
    printf("[ SISTEMA ]\n");
    printf("> Tem certeza que deseja, sair do game? aaa....aa...a.\n\n");
    getchar();
}

int main(void)
{
	setlocale(LC_ALL, "Portuguese");
    int continuar=1;

    do
    {
        system("cls");
        textcolor(4);
        printf("           [ Dragons & Sorcery ]\n");
        textcolor(10);
        printf("_______ > O Jogo das Cartas Epicas <_______\n\n");
        textcolor(4);
        printf("========== [MENU PRINCIPAL] =========\n\n");
        textcolor(11);
        printf("          > 1. Novo Jogo\n");
        printf("          > 2. Regras   \n");
        printf("          > 3. Creditos \n");
        printf("          > 0. Sair     \n");
        textcolor(15);

        scanf("%d", &continuar);
        system("cls");

        switch(continuar)
        {
            case 1:
                jogar();
                break;

            case 2:
                regras();
                break;
                
            case 3:
                creditos();
                break;    

            case 0:
                sair();
                break;

            default:
            	
                printf("Por Favor digite apenas 1,2,3 ou 0\n");
        }
    } while(continuar);
    
}
