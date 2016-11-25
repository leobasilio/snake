#include "ranking.h"
#include "render.h"
#include <string.h>

#define QTD_LIMITE 10
#define TAM_NOME 15
#define NOME_ARQUIVO "ranking.bin"

#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef struct {
    char nome[TAM_NOME+1];
    int pontuacao;
} Registro;

void sn_ranking_render_ler(char* nome){

    int i, len = strlen(nome);
    char letra[20];

    sn_render_file("ranking_nome", 4, 5);

    for(i = 0 ; i < len ; i++){

        if(nome[i] != ' '){

            sprintf(letra, "letra_%c", nome[i]);

            sn_render_file(letra, i + (SN_BLOCOS_W - len)/2, 12);

        }

    }

    sn_render_flush();

}

void sn_ranking_ler_nome(char* nome){

    SDL_Event evento;
    bool refresh = true;
    int len = strlen(nome);

    while(1){

        while(SDL_PollEvent(&evento)){

            switch(evento.type){

                case SDL_QUIT:

                    return;

                case SDL_KEYDOWN:

                    if((evento.key.keysym.sym >= SDLK_a && evento.key.keysym.sym <= SDLK_z) ||
                       evento.key.keysym.sym == ' '){

                        if(len < TAM_NOME){

                            char c = evento.key.keysym.sym;

                            strncat(nome, &c, 1);

                            len++;

                            refresh = true;

                        }

                    }else if(evento.key.keysym.sym == SDLK_BACKSPACE){

                        if(len > 0){

                            nome[len - 1] = '\0';

                            len--;

                            refresh = true;

                        }

                    }else if(evento.key.keysym.sym == SDLK_RETURN || evento.key.keysym.sym == SDLK_RETURN2){

                        return;

                    }

                    break;

            }

        }

        if(refresh){

            sn_ranking_render_ler(nome);

            refresh = false;

        }

    }

}

/* Recebe um ponteiro para arquivo já
posicionado no local de inserção */
void sn_ranking_inserir(FILE* arq, int pontuacao){

    Registro novo = {"", pontuacao}, seguintes[QTD_LIMITE];
    int posicao, qtd_anteriores, qtd_seguintes;

    sn_ranking_ler_nome(novo.nome);

    if(*novo.nome){

        posicao = ftell(arq); /* posição de inserção*/

        qtd_anteriores = posicao / sizeof(Registro);

        qtd_seguintes = fread(&seguintes, sizeof(Registro), QTD_LIMITE, arq); /* lê registros seguintes */

        fseek(arq, posicao, SEEK_SET); /* retorna pra posição de inserção */

        fwrite(&novo, sizeof(Registro), 1, arq); /* escreve o novo */

        fwrite(seguintes, sizeof(Registro), MIN(qtd_seguintes, QTD_LIMITE - qtd_anteriores - 1), arq); /* escreve quantos faltam para QTD_LIMITE*/

    }

}

/* Avalia a necessidade e processa a
inclusão do jogador no ranking */
void sn_ranking_novo(int pontuacao){

    FILE* arq;
    Registro reg;
    int qtd = 0;

    if(pontuacao > 0){

        arq = fopen(NOME_ARQUIVO, "r+");

        if(!arq){
            arq = fopen(NOME_ARQUIVO, "w+");
        }

        if(arq){

            while(fread(&reg, sizeof(Registro), 1, arq)){

                qtd++;

                if(reg.pontuacao <= pontuacao){

                    fseek(arq, -sizeof(Registro), SEEK_CUR); // volta 1 registro para inserir acima deste

                    sn_ranking_inserir(arq, pontuacao);

                    fclose(arq);

                    return;

                }

            }

            if(qtd < QTD_LIMITE){
                sn_ranking_inserir(arq, pontuacao);
            }

            fclose(arq);

        }

    }

}

void sn_ranking_run(){


}
