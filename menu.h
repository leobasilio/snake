#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "global.h"

typedef struct {
    char nome[20]; /* Nome base do arquivo bitmap */
    void (*on_enter)(); /* Callback para o enter, NULL para encerrar tela */
    void (*on_arrows)(SDL_Keycode key); /* Callback para setas esquerda e direita */
} SnMenuOpcao;

void sn_menu_run();
void sn_menu_custom(SnMenuOpcao* lista, int qtd);

#endif // MENU_H_INCLUDED
