#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "global.h"

void sn_render_init(SDL_Renderer* renderer);
void sn_render_clear();

void sn_render_background();
void sn_render_block(int x, int y);
void sn_render_bitmap(char* nome, int x, int y);
void sn_render_flush();

#endif // RENDER_H_INCLUDED
