#ifndef character
#define character
#include "raylib.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define ALTURA_CHAO 100
#define G 1800 // acredito que seja gravidade
#define VELOCIDADE_PULO 900.0f
#define ALTURA_PERSONAGEM 250
#define LARGURA_PERSONAGEM 105
#define ALCANCE_ATAQUE 220// esses valores devem ser testados


typedef struct{
    int cima;
    int esquerda;
    int direita;
    int ataque;
}Controle;

typedef struct{
    int num_frames;
    int actual_frame;
    Texture2D textura;
}sprite;

typedef struct{
    int index;
    int pulando;
    Vector2 posicao;
    float velocidade, dano, vida;
    Rectangle corpo;
    Rectangle ataque;
    int atk;
    Controle controle;
    sprite parado;
    sprite andar;
    sprite pular;
    sprite cair;
    sprite atacar;
    sprite morrer;
}objPersonagem;






#include "animation.h"

void iniciarPersonagem(objPersonagem *player, int choice, float posicao);

void iniciarInimigo();

void atualizarPersongem(objPersonagem *player, Rectangle chao, float delta);
void checarParede(objPersonagem *player);
void ataque(objPersonagem *player, objPersonagem *player_2);




#endif
