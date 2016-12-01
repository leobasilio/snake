#ifndef OPCOES_H_INCLUDED
#define OPCOES_H_INCLUDED

#include "global.h"

typedef enum {
    SN_OPCAO_NIVEL_FACIL,
    SN_OPCAO_NIVEL_MEDIO,
    SN_OPCAO_NIVEL_DIFICIL
} SnOpcaoNivel;

void sn_opcoes_run();

SnOpcaoNivel sn_opcoes_nivel_get();

#endif // OPCOES_H_INCLUDED
