#include "jogo.h"
#include "render.h"

static void sn_jogo_render(){

    sn_render_background();

    sn_render_flush();

}

void sn_jogo_run(){

    SDL_Event evento;


    while(1){

        while(SDL_PollEvent(&evento)){
            if(evento.type == SDL_QUIT){
                return;
            }
        }

        sn_jogo_render();

    }

}
