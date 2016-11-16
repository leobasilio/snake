#include "render.h"

#define COR_FUNDO1 0xAECE8B
#define COR_FUNDO2 0x8EB367
#define COR_BLOCO  0x36381B

static SDL_Renderer* _renderer;
static SDL_Texture* _fundo;

void sn_render_init(SDL_Renderer* renderer){

    SDL_Rect rect = {0, 0, SN_JANELA_WIDTH, SN_JANELA_HEIGHT};
    int blocos_x = SN_JANELA_WIDTH/SN_BLOCO_SIZE;
    int blocos_y = SN_JANELA_HEIGHT/SN_BLOCO_SIZE;
    int x, y;

    _renderer = renderer;

    _fundo = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SN_JANELA_WIDTH, SN_JANELA_HEIGHT);

    SDL_SetRenderTarget(_renderer, _fundo);

    SDL_SetRenderDrawColor(_renderer, 0xAE, 0xCE, 0x8B, 0xFF);
    SDL_RenderFillRect(_renderer, &rect);

    SDL_SetRenderDrawColor(_renderer, 0x8E, 0xB3, 0x67, 0xFF);

    rect.h = rect.w = SN_BLOCO_SIZE - 2*SN_BLOCO_PADDING;

    for(y = 0 ; y < blocos_y ; y++){

        rect.y = y*SN_BLOCO_SIZE + SN_BLOCO_PADDING;

        for(x = 0 ; x < blocos_x ; x++){

            rect.x = x*SN_BLOCO_SIZE + SN_BLOCO_PADDING;

            SDL_RenderFillRect(_renderer, &rect);
;
        }

    }

    SDL_SetRenderTarget(_renderer, NULL);

}

void sn_render_clear(){
    SDL_DestroyTexture(_fundo);
}

void sn_render_background(){

    SDL_Rect rect = {0, 0, SN_JANELA_WIDTH, SN_JANELA_HEIGHT};

    SDL_RenderCopy(_renderer, _fundo, &rect, &rect);

}

void sn_render_flush(){
    SDL_RenderPresent(_renderer);
}
