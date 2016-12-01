#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "global.h"

typedef struct {
    char nome[20];
    void (*on_enter)();
    void (*on_arrows)(SDL_Keycode key);
} SnMenuOpcao;

void sn_menu_run();
void sn_menu_custom(SnMenuOpcao* lista, int qtd);

#endif // MENU_H_INCLUDED
