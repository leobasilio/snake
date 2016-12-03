#include "menu.h"
#include "jogo.h"
#include "ranking.h"
#include "opcoes.h"
#include "render.h"

#define MENU_Y 10
#define MENU_X 8

static void sn_menu_render(SnMenuOpcao* lista, int qtd, int selecao){

    int i;
    char nome[30];

    sn_render_background();

    sn_render_file("logo", 7, 2);

    /* Opções do menu */
    for(i = 0 ; i < qtd ; i++){

        sprintf(nome, "menu_%s_%s", lista[i].nome, (selecao == i) ? "on" : "off");

        sn_render_file(nome, MENU_X, MENU_Y + 2*i);

    }

    sn_render_flush();

}

void sn_menu_run(){

    SnMenuOpcao lista[4] = {{"iniciar", sn_jogo_run, NULL},
                            {"opcoes", sn_opcoes_run, NULL},
                            {"ranking", sn_ranking_run, NULL},
                            {"sair", NULL, NULL}};

    sn_menu_custom(lista, 4);

}

/* Lógica para menu personalizado */
void sn_menu_custom(SnMenuOpcao* lista, int qtd){

    SDL_Event evento;
    bool refresh = true;
    int selecao = 0;

    while(1){

        while(SDL_PollEvent(&evento)){

            switch(evento.type){

                case SDL_QUIT:

                    exit(0);

                    return;

                case SDL_KEYDOWN:

                    switch(evento.key.keysym.sym){

                        case SDLK_DOWN:

                            if(selecao < qtd-1){
                                selecao++;
                                refresh = true;
                            }
                            break;

                        case SDLK_UP:

                            if(selecao > 0){
                                selecao--;
                                refresh = true;
                            }
                            break;

                        case SDLK_LEFT:
                        case SDLK_RIGHT:

                            if(lista[selecao].on_arrows){

                                lista[selecao].on_arrows(evento.key.keysym.sym);

                                refresh = true;

                            }

                            break;

                        case SDLK_RETURN:

                            if(lista[selecao].on_enter){

                                lista[selecao].on_enter();

                                refresh = true;

                            }else{

                                return;

                            }

                            break;

                        case SDLK_ESCAPE:

                            return;

                    }

                    break;

            }

        }

        if(refresh){

            sn_menu_render(lista, qtd, selecao);

            refresh = false;

        }

    }

}
