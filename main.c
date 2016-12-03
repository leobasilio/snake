#include "menu.h"
#include "render.h"

#include <sys/types.h>
#include <dirent.h>

bool checkdir(char* nome){

    DIR* dir = opendir(nome);

    if(dir){
        closedir(dir);
        return true;
    }

    return false;

}

int main(int argc, char* argv[]){

    if(!checkdir("audio")){
        printf("O diretório \"audio\" não foi localizado.\n");
        return -1;
    }else if(!checkdir("sprites")){
        printf("O diretório \"sprites\" não foi localizado.\n");
        return -1;
    }

    //========================

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
        printf("Falha ao inicializar a SDL: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* janela = SDL_CreateWindow("Jogo da Cobrinha", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SN_JANELA_WIDTH, SN_JANELA_HEIGHT, 0);

    if(janela != NULL){

        SDL_Renderer* renderer = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

        if(renderer != NULL){

            sn_render_init(renderer);

            sn_menu_run();

            sn_render_clear();

            SDL_DestroyRenderer(renderer);

        }else{
            printf("Falha ao criar o renderer: %s\n", SDL_GetError());
        }

        SDL_DestroyWindow(janela);

    }else{
        printf("Falha ao criar a janela: %s\n", SDL_GetError());
    }

    SDL_Quit();

    return 0;

}
