#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "global.h"

typedef struct {
    SDL_Texture* texture;
    SDL_Rect rect;
} SN_BITMAP;

void sn_render_init(SDL_Renderer* renderer);
void sn_render_clear();

void sn_render_background();
void sn_render_block(int x, int y);
void sn_render_file(const char* nome, int x, int y);
void sn_render_bitmap(SN_BITMAP bitmap, int x, int y);
void sn_render_flush();

SN_BITMAP sn_load_bitmap(const char* nome);
void sn_free_bitmap(SN_BITMAP bitmap);

void sn_render_string(char* s, int x, int y);

#endif // RENDER_H_INCLUDED
