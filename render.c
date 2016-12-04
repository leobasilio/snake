#include "render.h"

static SDL_Renderer* _renderer;
static SDL_Texture* _fundo;

static SN_BITMAP alfabeto[37]; /* 0-9 números, 10-35 letras, 36 hífen */

/* Inicializa variáveis */
void sn_render_init(SDL_Renderer* renderer){

    SDL_Rect rect = {0, 0, SN_JANELA_WIDTH, SN_JANELA_HEIGHT};
    int x, y;

    _renderer = renderer;

    /* Criando textura para o fundo */

    _fundo = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SN_JANELA_WIDTH, SN_JANELA_HEIGHT);

    SDL_SetRenderTarget(_renderer, _fundo);

    /* Fundo sólido */

    SDL_SetRenderDrawColor(_renderer, 0xAE, 0xCE, 0x8B, 0xFF);
    SDL_RenderFillRect(_renderer, &rect);

    /* Blocos por cima do fundo sólido */

    SDL_SetRenderDrawColor(_renderer, 0xA4, 0xC1, 0x84, 0xFF);

    rect.h = rect.w = SN_BLOCO_SIZE - 2*SN_BLOCO_PADDING;

    for(y = 0 ; y < SN_BLOCOS_H ; y++){

        rect.y = y*SN_BLOCO_SIZE + SN_BLOCO_PADDING;

        for(x = 0 ; x < SN_BLOCOS_W ; x++){

            rect.x = x*SN_BLOCO_SIZE + SN_BLOCO_PADDING;

            SDL_RenderFillRect(_renderer, &rect);

        }

    }

    SDL_SetRenderTarget(_renderer, NULL);

    /* Cor para os blocos ativos */

    SDL_SetRenderDrawColor(_renderer, 0x36, 0x38, 0x1B, 0xFF);

    //============================

    /* Bitmaps para o alfabeto */

    char arquivo[20];
    int i;

    for(i = 0 ; i < 10 ; i++){
        sprintf(arquivo, "letra_%i", i);
        alfabeto[i] = sn_load_bitmap(arquivo);
    }

    for(i = 0 ; i < 26 ; i++){
        sprintf(arquivo, "letra_%c", 'a' + i);
        alfabeto[10+i] = sn_load_bitmap(arquivo);
    }

    alfabeto[36] = sn_load_bitmap("letra_-");

}

/* Libera recursos alocados */
void sn_render_clear(){

    int i;

    for(i = 0 ; i < 37 ; i++){
        sn_free_bitmap(alfabeto[i]);
    }

    SDL_DestroyTexture(_fundo);

}

/* Renderiza plano de fundo */
void sn_render_background(){

    SDL_Rect rect = {0, 0, SN_JANELA_WIDTH, SN_JANELA_HEIGHT};

    SDL_RenderCopy(_renderer, _fundo, &rect, &rect);

}

/* Renderiza um bloco individual com base nas
   coordenadas próprias do jogo */
void sn_render_block(int x, int y){

    SDL_Rect rect = {x*SN_BLOCO_SIZE + SN_BLOCO_PADDING,
                     y*SN_BLOCO_SIZE + SN_BLOCO_PADDING,
                     SN_BLOCO_SIZE - 2*SN_BLOCO_PADDING,
                     SN_BLOCO_SIZE - 2*SN_BLOCO_PADDING};

    SDL_RenderFillRect(_renderer, &rect);

}

/* Renderiza arquivo bitmap com base nas
   coordenadas próprias do jogo */
void sn_render_file(const char* nome, int x, int y){

    SN_BITMAP bitmap = sn_load_bitmap(nome);

    sn_render_bitmap(bitmap, x, y);

    sn_free_bitmap(bitmap);

}

/* Renderiza bitmap da memória com base nas
   coordenadas próprias do jogo */
void sn_render_bitmap(SN_BITMAP bitmap, int x, int y){

    SDL_Rect dst_rect = {x*SN_BLOCO_SIZE + SN_BLOCO_PADDING,
                         y*SN_BLOCO_SIZE + SN_BLOCO_PADDING,
                         bitmap.rect.w,
                         bitmap.rect.h};

    SDL_RenderCopy(_renderer, bitmap.texture, &bitmap.rect, &dst_rect);

}

/* Envia buffer para a tela */
void sn_render_flush(){
    SDL_RenderPresent(_renderer);
}

/* Carrega um arquivo bitmap para a memória */
SN_BITMAP sn_load_bitmap(const char* nome){

    SN_BITMAP ret;
    char arquivo[50];

    sprintf(arquivo, "sprites/%s.bmp", nome);

    SDL_Surface* bitmap = SDL_LoadBMP(arquivo);

    if(bitmap == NULL){

        printf("Erro ao carregar o arquivo \"%s\": %s\n", arquivo, SDL_GetError());

        exit(EXIT_FAILURE);

    }

    SDL_GetClipRect(bitmap, &ret.rect);

    ret.texture = SDL_CreateTextureFromSurface(_renderer, bitmap);

    SDL_FreeSurface(bitmap);

    return ret;

}

/* Libera um bitmap da memória */
void sn_free_bitmap(SN_BITMAP bitmap){
    SDL_DestroyTexture(bitmap.texture);
}

/* Renderiza uma string com base nas
   coordenadas próprias do jogo */
void sn_render_string(char* s, int x, int y){

    for( ; *s ; s++, x++){

        if(*s >= '0' && *s <= '9'){
            sn_render_bitmap(alfabeto[*s-'0'], x, y);
        }else if(*s >= 'a' && *s <= 'z'){
            sn_render_bitmap(alfabeto[*s-'a'+10], x, y);
        }else if(*s == '-'){
            sn_render_bitmap(alfabeto[36], x, y);
        }

    }

}
