#include "menu.h"
#include "jogo.h"
#include "render.h"

#define MENU_Y 8
#define MENU_X 8
#define QTD_OPCOES 4

typedef struct {
    char nome[20];
    void (*funcao)();
} Opcao;

static int selecao = 0;
static Opcao lista[QTD_OPCOES] = {{"iniciar", sn_jogo_run},
                                  {"opcoes", NULL},
                                  {"ranking", NULL},
                                  {"sair", NULL}};

static void sn_menu_render(){

    int i;
    char nome[30];

    sn_render_background();

    for(i = 0 ; i < QTD_OPCOES ; i++){

        sprintf(nome, "menu_%s_%s", lista[i].nome, (selecao == i) ? "on" : "off");

        sn_render_file(nome, MENU_X, MENU_Y + 2*i);

    }

    sn_render_flush();

}

void sn_menu_run(){

    SDL_Event evento;
    bool refresh = true;

    while(1){

        while(SDL_PollEvent(&evento)){

            switch(evento.type){

                case SDL_QUIT:

                    return;

                case SDL_KEYDOWN:

                    switch(evento.key.keysym.sym){

                        case SDLK_DOWN:

                            if(selecao < QTD_OPCOES-1){
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

                        case SDLK_RETURN:

                            if(lista[selecao].funcao){

                                lista[selecao].funcao();

                                refresh = true;

                            }else{

                                return;

                            }

                            break;

                    }

                    break;

            }

        }

        if(refresh){

            sn_menu_render();

            refresh = false;

        }

    }

}
