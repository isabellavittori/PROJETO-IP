#ifndef mapa
#define mapa
#include "animation.h"
#include "include/raylib.h"
#include "character.h"

typedef struct{
    int index;
    Texture2D background;
    Texture2D chao;
    
    sprite asset1;
    Texture2D asset2;
    Texture2D asset3;
    
}Mapa;

void carregarItensMapa(Mapa *myMapa, int index);

void descarregarItensMapa(Mapa *myMapa, int index);

#endif
