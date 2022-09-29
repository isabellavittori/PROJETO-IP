#include "character.h"
#include "animation.h"
#include "mapa.h"
#include "raylib.h"



void carregarItensMapa(Mapa *myMapa) {
    myMapa->background = LoadTexture("/assets/background.png"); // final
    myMapa->chao = LoadTexture("/assets/background_chao.png"); // final
    //myMapa->life = LoadTexture("");
    //myMapa->asset1.textura = LoadTexture("");
    // myMapa->asset1.num_frames = 6;
    // myMapa->asset1.actual_frame = 0;
    //myMapa->asset2 = LoadTexture("");
    //myMapa->asset3 = LoadTexture("");

}



void descarregarItensMapa(Mapa *myMapa) {
    UnloadTexture(myMapa->background);
    UnloadTexture(myMapa->chao);
    //UnloadTexture(myMapa->life);
    //UnloadTexture(myMapa->asset1.textura);
    // UnloadTexture(myMapa->asset2);
    // UnloadTexture(myMapa->asset3);
}


