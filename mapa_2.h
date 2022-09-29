#ifndef mapa
#define mapa
#include "animation.h"
#include "raylib.h"
#include "character.h"

typedef struct{
    Texture2D background;
    Texture2D chao;
    //Texture2D life;
    
    //sprite asset1;
    //Texture2D asset2;
    //Texture2D asset3;
    
}Mapa;

void carregarItensMapa(Mapa *myMapa);

void descarregarItensMapa(Mapa *myMapa);

#endif
