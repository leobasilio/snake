#include "render.h"

static SDL_Renderer* _renderer;
static SDL_Texture* _fundo;

void sn_render_init(SDL_Renderer* renderer){

    SDL_Rect rect = {0, 0, SN_JANELA_WIDTH, SN_JANELA_HEIGHT};
    int x, y;

    _renderer = renderer;

    _fundo = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SN_JANELA_WIDTH, SN_JANELA_HEIGHT);

    SDL_SetRenderTarget(_renderer, _fundo);

    SDL_SetRenderDrawColor(_renderer, 0xAE, 0xCE, 0x8B, 0xFF);
    SDL_RenderFillRect(_renderer, &rect);

    SDL_SetRenderDrawColor(_renderer, 0x8E, 0xB3, 0x67, 0xFF);

    rect.h = rect.w = SN_BLOCO_SIZE - 2*SN_BLOCO_PADDING;

    for(y = 0 ; y < SN_BLOCOS_H ; y++){

        rect.y = y*SN_BLOCO_SIZE + SN_BLOCO_PADDING;

        for(x = 0 ; x < SN_BLOCOS_W ; x++){

            rect.x = x*SN_BLOCO_SIZE + SN_BLOCO_PADDING;

            SDL_RenderFillRect(_renderer, &rect);

        }

    }

    SDL_SetRenderTarget(_renderer, NULL);

    SDL_SetRenderDrawColor(_renderer, 0x36, 0x38, 0x1B, 0xFF);

}

void sn_render_clear(){
    SDL_DestroyTexture(_fundo);
}

void sn_render_background(){

    SDL_Rect rect = {0, 0, SN_JANELA_WIDTH, SN_JANELA_HEIGHT};

    SDL_RenderCopy(_renderer, _fundo, &rect, &rect);

}

void sn_render_block(int x, int y){

    SDL_Rect rect = {x*SN_BLOCO_SIZE + SN_BLOCO_PADDING,
                     y*SN_BLOCO_SIZE + SN_BLOCO_PADDING,
                     SN_BLOCO_SIZE - 2*SN_BLOCO_PADDING,
                     SN_BLOCO_SIZE - 2*SN_BLOCO_PADDING};

    SDL_RenderFillRect(_renderer, &rect);

}

void sn_render_flush(){
    SDL_RenderPresent(_renderer);
}
