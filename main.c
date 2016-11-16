#include "menu.h"
#include "render.h"

int main(int argc, char* argv[]){

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Falha ao inicializar o vídeo: %s", SDL_GetError());
        return -1;
    }

    SDL_Window* janela = SDL_CreateWindow("Jogo da Cobrinha", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SN_JANELA_WIDTH, SN_JANELA_HEIGHT, 0);

    if(janela != NULL){

        SDL_Renderer* renderer = SDL_CreateRenderer(janela, -1, 0);

        if(renderer != NULL){

            sn_render_init(renderer);

            sn_menu_run();

            sn_render_clear();

        }else{
            printf("Falha ao criar o renderer: %s", SDL_GetError());
        }

        SDL_DestroyWindow(janela);

    }else{
        printf("Falha ao criar a janela: %s", SDL_GetError());
    }

    SDL_Quit();

    return 0;

}