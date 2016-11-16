#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "global.h"

void sn_render_init(SDL_Renderer* renderer);
void sn_render_clear();

void sn_render_background();
void sn_render_flush();

/*void sn_render_draw_rect(SDL_Renderer* renderer, int x, int y, int w, int h, uint32_t cor);
void sn_video_fill_rect(SDL_Renderer* renderer, int x, int y, int w, int h, uint32_t cor);*/

#endif // RENDER_H_INCLUDED
