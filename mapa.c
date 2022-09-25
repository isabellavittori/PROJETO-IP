#include "character.h"
#include "animation.h"
#include "mapa.h"
#include "include/raylib.h"



void carregarItensMapa(Mapa *myMapa, int index) {
    if(index == 0) {
        myMapa[index].background = LoadTexture(""); //fundo 0
        myMapa[index].chao = LoadTexture("");// chao 0
        myMapa[index].asset1.textura = LoadTexture("");
        myMapa[index].asset1.num_frames = 6;
        myMapa[index].asset1.actual_frame = 0;
        myMapa[index].asset2 = LoadTexture("");
        myMapa[index].asset3 = LoadTexture(""); 
    }

    if(index == 1) {
        myMapa[index].background = LoadTexture(""); // fundo 1
        myMapa[index].chao = LoadTexture(""); // chao 1
        myMapa[index].asset1.textura = LoadTexture("");
        myMapa[index].asset1.num_frames = 6;
        myMapa[index].asset1.actual_frame = 0;
        myMapa[index].asset2 = LoadTexture("");
        myMapa[index].asset3 = LoadTexture("");
    }

    if(index == 2) {
        myMapa[index].background = LoadTexture(""); // fundo 2
        myMapa[index].chao = LoadTexture(""); // chao 2
        myMapa[index].asset1.textura = LoadTexture("");
        myMapa[index].asset1.num_frames = 6;
        myMapa[index].asset1.actual_frame = 0;
        myMapa[index].asset2 = LoadTexture("");
        myMapa[index].asset3 = LoadTexture("");
    }

    if(index == 3) {
        myMapa[index].background = LoadTexture(""); // final
        myMapa[index].chao = LoadTexture(""); // final
        myMapa[index].asset1.textura = LoadTexture("");
        myMapa[index].asset1.num_frames = 6;
        myMapa[index].asset1.actual_frame = 0;
        myMapa[index].asset2 = LoadTexture("");
        myMapa[index].asset3 = LoadTexture("");
    }

}



void descarregarItensMapa(Mapa *myMapa, int index) {
     if(index == 0) {
        UnloadTexture(myMapa[index].background);
        UnloadTexture(myMapa[index].chao);
        UnloadTexture(myMapa[index].asset1.textura);
        UnloadTexture(myMapa[index].asset2);
        UnloadTexture(myMapa[index].asset3); 
    }

    if(index == 1) {
        UnloadTexture(myMapa[index].background);
        UnloadTexture(myMapa[index].chao);
        UnloadTexture(myMapa[index].asset1.textura);
        UnloadTexture(myMapa[index].asset2);
        UnloadTexture(myMapa[index].asset3); 
    }

    if(index == 2) {
        UnloadTexture(myMapa[index].background);
        UnloadTexture(myMapa[index].chao);
        UnloadTexture(myMapa[index].asset1.textura);
        UnloadTexture(myMapa[index].asset2);
        UnloadTexture(myMapa[index].asset3); 
    }

    if(index == 3) {
        UnloadTexture(myMapa[index].background);
        UnloadTexture(myMapa[index].chao);
        UnloadTexture(myMapa[index].asset1.textura);
        UnloadTexture(myMapa[index].asset2);
        UnloadTexture(myMapa[index].asset3); 
    }
}



