#include "ranking.h"
#include "render.h"
#include <string.h>

#define QTD_LIMITE 10
#define TAM_NOME 15
#define NOME_ARQUIVO "ranking.bin"
#define ALTURA (SN_BLOCOS_H-4) /* Altura da tela */

#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef struct {
    char nome[TAM_NOME+1];
    int pontuacao;
} Registro;

static int animacao = 0; // estágio da animação da borda

static SN_BITMAP bmp_titulo;
static Registro lista[QTD_LIMITE]; /* lista do ranking */
static int qtd_lista = 0;

void sn_ranking_render(Registro entradas[], int tam){

    int i, y_base = (SN_BLOCOS_H - ALTURA)/2;
    char linha[26];

    sn_render_background();

    sn_render_bitmap(bmp_titulo, SN_BLOCOS_W/2-6, y_base+2);

    /* Animação horizontal */
    for(i = 1 ; i < SN_BLOCOS_W-1 ; i++){
        if(i % 2 == animacao){
            sn_render_block(i, y_base);
        }else{
            sn_render_block(i, y_base + ALTURA - 1);
        }
    }

    /* Animação vertical */
    for(i = y_base+1 ; i < SN_BLOCOS_H-y_base ; i++){
        if(i % 2 == animacao){
            sn_render_block(SN_BLOCOS_W-2, i);
        }else{
            sn_render_block(1, i);
        }
    }

    /* Lista do ranking */

    for(i = 0 ; i < QTD_LIMITE ; i++){

        if(i < qtd_lista){
            sprintf(linha, "%2i %-17s %03i", i+1, lista[i].nome, lista[i].pontuacao);
        }else{
            sprintf(linha, "%2i %-17s %s", i+1, "----------", "---");
        }

        sn_render_string(linha, 4, y_base+6+i);
    }

    sn_render_flush();

    animacao = (animacao == 0 ? 1 : 0);

}

void sn_ranking_render_ler(char* nome){

    int len = strlen(nome);

    sn_render_file("ranking_nome", 4, 5);

    sn_render_string(nome, (SN_BLOCOS_W - len)/2, 12);

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

void sn_ranking_init(){

    bmp_titulo = sn_load_bitmap("ranking_titulo");

    //===========================

    FILE* arq = fopen(NOME_ARQUIVO, "r");

    if(arq){

        qtd_lista = fread(lista, sizeof(Registro), QTD_LIMITE, arq);

        fclose(arq);

    }else{

        qtd_lista = 0;

    }

}

void sn_ranking_clear(){

    sn_free_bitmap(bmp_titulo);

}

void sn_ranking_run(){

    SDL_Event evento;
    Uint32 tick = SDL_GetTicks();

    sn_ranking_init();

    while(1){

        while(SDL_PollEvent(&evento)){

            switch(evento.type){

                case SDL_QUIT:

                    sn_ranking_clear();

                    return;

                case SDL_KEYDOWN:

                    switch(evento.key.keysym.sym){

                        case SDLK_RETURN:
                        case SDLK_RETURN2:
                        case SDLK_ESCAPE:

                            sn_ranking_clear();

                            return;

                    }

                    break;

            }

        }

        if(SDL_TICKS_PASSED(SDL_GetTicks(), tick)){

            sn_ranking_render(0, 0);

            tick = SDL_GetTicks()+200;

        }

    }

}
