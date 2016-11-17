#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SN_JANELA_WIDTH      640
#define SN_JANELA_HEIGHT     480
#define SN_BLOCO_SIZE         20
#define SN_BLOCO_PADDING       1

#define SN_BLOCOS_W         (SN_JANELA_WIDTH/SN_BLOCO_SIZE)
#define SN_BLOCOS_H         (SN_JANELA_HEIGHT/SN_BLOCO_SIZE)

#endif // GLOBAL_H_INCLUDED
