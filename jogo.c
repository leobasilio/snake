#include "jogo.h"
#include "render.h"
#include "audio.h"
#include "ranking.h"
#include "opcoes.h"

#define MARGIN 2 /* Margem da área interna, em blocos, sem contar a borda */

#define TAM_INICIAL 4 /* Tamanho inicial da cobra */

typedef struct {
    int x;
    int y;
} Bloco; /* Posições em relação ao topo esquerdo da mesa */

static Bloco *cobra;
static int cobra_tam;
static char cobra_direcao; /* Cima, Baixo, Esquerda, Direita*/
static int cobra_ponta; /* Cabeça da cobra */
static int cobra_vel; /* Velocidade da cobra */
static float fator_vel; /* Fator de mudança da velocidade */

static Bloco comida;
static int pontuacao;

static int mesa_w, mesa_h; /* Dimensões da área interna do jogo */

static SN_BITMAP sprites[11];

static void sn_jogo_render(){

    int i, j;

    sn_render_background();

    /* Linhas horizontais da borda */
    for(i = 0 ; i < mesa_w+2 ; i++){
        sn_render_block(i + MARGIN, MARGIN);
        sn_render_block(i + MARGIN, MARGIN + mesa_h + 1);
    }

    /* Linhas verticais da borda */
    for(i = 1 ; i < mesa_h+2 ; i++){
        sn_render_block(MARGIN, i + MARGIN);
        sn_render_block(MARGIN + mesa_w + 1 , i + MARGIN);
    }

    /* Cobra */
    for(i = 0 ; i < cobra_tam ; i++){
        sn_render_block(MARGIN + (cobra+i)->x + 1, MARGIN + (cobra+i)->y + 1);
    }

    sn_render_block(MARGIN + comida.x + 1, MARGIN + comida.y + 1);

    /* Pontuação */
    for(i = 0, j = 10 ; i < 3 ; i++, j *= 10){
        sn_render_bitmap(sprites[10 * (pontuacao % j) / j], MARGIN + mesa_w - 2*i, MARGIN + mesa_h + 3);
    }

    sn_render_bitmap(sprites[10], MARGIN + mesa_w - 12, MARGIN + mesa_h + 3);

    sn_render_flush();

}

static void sn_jogo_posicionar_comida(){

    int i;

    do{

        comida.x = rand() % mesa_w;
        comida.y = rand() % mesa_h;

        for(i = 0 ; i < cobra_tam ; i++){
            if(cobra[i].x == comida.x && cobra[i].y == comida.y){
                break;
            }
        }

    }while(i != cobra_tam);

}

static void sn_jogo_comer_comida(){

    int i;

    cobra = realloc(cobra, ++cobra_tam * sizeof(Bloco));

    for(i = cobra_tam-1 ; i > cobra_ponta ; i--){
        *(cobra+i) = *(cobra+i-1);
    }

    cobra_vel *= fator_vel;

    pontuacao++;

}

/* Retorna true caso o movimento seja
   bem-sucedido ou false em caso de
   fim de jogo */
static bool sn_jogo_mover_cobra(){

    Bloco* atual = cobra+cobra_ponta;
    Bloco proximo;
    int i;

    switch(cobra_direcao){
        case 'D':
            if(atual->x+1 < mesa_w){
                proximo.x = atual->x+1;
                proximo.y = atual->y;
            }else{
                return false;
            }
            break;
        case 'E':
            if(atual->x-1 >= 0){
                proximo.x = atual->x-1;
                proximo.y = atual->y;
            }else{
                return false;
            }
            break;
        case 'C':
            if(atual->y-1 >= 0){
                proximo.x = atual->x;
                proximo.y = atual->y-1;
            }else{
                return false;
            }
            break;
        default:
            if(atual->y+1 < mesa_h){
                proximo.x = atual->x;
                proximo.y = atual->y+1;
            }else{
                return false;
            }
            break;
    }

    cobra_ponta++;

    if(cobra_ponta >= cobra_tam) cobra_ponta = 0;

    if(proximo.x == comida.x && proximo.y == comida.y){

        sn_jogo_comer_comida();

        cobra[cobra_ponta] = proximo;

        sn_jogo_posicionar_comida();

    }else{

        /* Verifica se a cobra não colidiu consigo */
        for(i = 0 ; i < cobra_tam ; i++){
            if(cobra[i].x == proximo.x && cobra[i].y == proximo.y && i != cobra_ponta){
                return false;
            }
        }

        cobra[cobra_ponta] = proximo;

    }

    return true;

}

static void sn_jogo_init(){

    int i;

    mesa_w = SN_BLOCOS_W - 2*MARGIN - 2;
    mesa_h = SN_BLOCOS_H - 3*MARGIN - 2;

    //==========================

    switch(sn_opcoes_nivel_get()){

        case SN_OPCAO_NIVEL_MEDIO:

            cobra_vel = 120;
            fator_vel = 0.98;

            break;

        case SN_OPCAO_NIVEL_DIFICIL:

            cobra_vel = 100;
            fator_vel = 0.97;

            break;

        default:

            cobra_vel = 150;
            fator_vel = 0.99;

            break;

    }

    //==========================

    pontuacao = 0;

    cobra_tam = TAM_INICIAL;
    cobra_ponta = 0;
    cobra_direcao = 'D';

    cobra = malloc(cobra_tam*sizeof(Bloco));

    cobra[0].x = mesa_w/2;
    cobra[0].y = mesa_h/2;

    for(i = 1 ; i < TAM_INICIAL ; i++){
        cobra[i].x = cobra[0].x + i - TAM_INICIAL;
        cobra[i].y = cobra[0].y;
    }

    //==========================

    char arq[] = "n0";

    for(i = 0 ; i < 10 ; i++){
        arq[1] = '0'+i;
        sprites[i] = sn_load_bitmap(arq);
    }

    sprites[10] = sn_load_bitmap("pontos");

    //==========================

    sn_jogo_posicionar_comida();

    //==========================

    sn_audio_start("jogo");

}

static void sn_jogo_clear(){

    int i;

    for(i = 0 ; i < 11 ; i++){
        sn_free_bitmap(sprites[i]);
    }

    free(cobra);

    sn_audio_stop();

}

static void sn_jogo_fim(){

    sn_jogo_clear();

    sn_render_file("fim", MARGIN + mesa_w/2 - 9, MARGIN + mesa_h/2 - 1);

    sn_render_flush();

    sn_audio_play("fim");

    sn_ranking_novo(pontuacao);

    sn_ranking_run();

}

void sn_jogo_run(){

    SDL_Event evento;
    bool morreu = false;
    char nova_direcao;

    //==========================

    sn_jogo_init();

    nova_direcao = cobra_direcao;

    //==========================

    Uint32 tick_inicial = SDL_GetTicks();

    while(!morreu){

        while(SDL_PollEvent(&evento)){

            switch(evento.type){

                case SDL_QUIT:

                    sn_jogo_clear();

                    exit(0);

                    return;

                case SDL_KEYDOWN:

                    switch(evento.key.keysym.sym){
                        case SDLK_DOWN:
                        case SDLK_s:
                            if(cobra_direcao != 'C')
                                nova_direcao = 'B';
                            break;
                        case SDLK_UP:
                        case SDLK_w:
                            if(cobra_direcao != 'B')
                                nova_direcao = 'C';
                            break;
                        case SDLK_RIGHT:
                        case SDLK_d:
                            if(cobra_direcao != 'E')
                                nova_direcao = 'D';
                            break;
                        case SDLK_LEFT:
                        case SDLK_a:
                            if(cobra_direcao != 'D')
                                nova_direcao = 'E';
                            break;
                        case SDLK_ESCAPE:
                            sn_jogo_clear();
                            return;
                    }

                    break;

            }
        }

        if(SDL_TICKS_PASSED(SDL_GetTicks(), tick_inicial+cobra_vel) || nova_direcao != cobra_direcao){

            cobra_direcao = nova_direcao;

            morreu = !sn_jogo_mover_cobra();

            sn_jogo_render();

            tick_inicial = SDL_GetTicks();

        }

    }

    sn_jogo_fim();

}
