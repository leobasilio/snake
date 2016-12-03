#include "opcoes.h"
#include "menu.h"

#include <string.h>

static void sn_opcoes_dummy_on_enter(){} /* Callback vazio para evitar que "enter" encerre a tela */
static void sn_opcoes_nivel_toggle(SDL_Keycode key);
static void sn_opcoes_som_toggle(SDL_Keycode key);

//=================

static SnOpcaoNivel op_nivel = SN_OPCAO_NIVEL_FACIL;
static bool op_som = true;

static SnMenuOpcao lista[3] = {{"opcoes_nf", sn_opcoes_dummy_on_enter, sn_opcoes_nivel_toggle},
                               {"opcoes_sl", sn_opcoes_dummy_on_enter, sn_opcoes_som_toggle},
                               {"opcoes_voltar", NULL, NULL}};

//=================
//=================

SnOpcaoNivel sn_opcoes_nivel_get(){
    return op_nivel;
}

static void sn_opcoes_nivel_toggle(SDL_Keycode key){

    switch(op_nivel){
        case SN_OPCAO_NIVEL_FACIL:
            if(key == SDLK_RIGHT)
                op_nivel = SN_OPCAO_NIVEL_MEDIO;
            break;
        case SN_OPCAO_NIVEL_MEDIO:
            if(key == SDLK_RIGHT)
                op_nivel = SN_OPCAO_NIVEL_DIFICIL;
            else if(key == SDLK_LEFT)
                op_nivel = SN_OPCAO_NIVEL_FACIL;
            break;
        case SN_OPCAO_NIVEL_DIFICIL:
            if(key == SDLK_LEFT)
                op_nivel = SN_OPCAO_NIVEL_MEDIO;
            break;
    }

    switch(op_nivel){
        case SN_OPCAO_NIVEL_FACIL:
            strcpy(lista[0].nome, "opcoes_nf");
            break;
        case SN_OPCAO_NIVEL_MEDIO:
            strcpy(lista[0].nome, "opcoes_nm");
            break;
        case SN_OPCAO_NIVEL_DIFICIL:
            strcpy(lista[0].nome, "opcoes_nd");
            break;
    }

}

//=================
//=================

bool sn_opcoes_som_get(){
    return op_som;
}

static void sn_opcoes_som_toggle(SDL_Keycode key){

    if(key == SDLK_RIGHT){

        op_som = false;

        strcpy(lista[1].nome, "opcoes_sd");

    }else if(key == SDLK_LEFT){

        op_som = false;

        strcpy(lista[1].nome, "opcoes_sl");

    }

}

//=================
//=================

void sn_opcoes_run(){

    sn_menu_custom(lista, 3);

}
