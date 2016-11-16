#include "menu.h"
#include "jogo.h"

void sn_menu_run(){

    SDL_Event evento;

    while(1){

        while(SDL_PollEvent(&evento)){
            if(evento.type == SDL_QUIT){
                return;
            }
        }

        sn_jogo_run();

        break;

    }

}

static void sn_menu_render(){
}
