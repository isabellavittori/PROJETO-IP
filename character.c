#include "character.h"
#include "raylib.h"
#include "animation.h"

void iniciarPersonagem(objPersonagem *player, int choice, float posicao){
    player->pulando = 1;
    player->vida = 100.0f;
    player->dano = 0.1f;
    player->posicao.x = posicao;
    player->posicao.y = GetScreenHeight() - ALTURA_CHAO - ALTURA_PERSONAGEM;
    player->corpo = (Rectangle) { player->posicao.x , player->posicao.y, LARGURA_PERSONAGEM, ALTURA_PERSONAGEM };
    player->velocidade = 0.0;
    player->atk = 0;

    if(choice == 1) {
        player->index = 1;
        
        player->controle.cima = KEY_W;
        player->controle.direita = KEY_D;
        player->controle.esquerda = KEY_A;
        player->controle.ataque = KEY_F;
        player->parado.textura = LoadTexture("/assets/Idle.png");//textura do personagem 0
        player->andar.textura = LoadTexture("/assets/Run.png");
        player->pular.textura = LoadTexture("/assets/JumpAndFall.png");
        player->atacar.textura = LoadTexture("/assets/attack.png");
        player->cair.textura = LoadTexture("/assets/JumpAndFall2.png");
        player->morrer.textura = LoadTexture("/assets/Morrer.png");
    }

    if(choice == 2) {
        player->index = 2;

        player->controle.cima = KEY_UP;
        player->controle.direita = KEY_RIGHT;
        player->controle.esquerda = KEY_LEFT;
        player->controle.ataque = KEY_L;
        player->parado.textura = LoadTexture("/assets/Idle.png");
        player->andar.textura = LoadTexture("/assets/Run.png");
        player->pular.textura = LoadTexture("/assets/JumpAndFall.png");
        player->atacar.textura = LoadTexture("/assets/attack.png");
        player->cair.textura = LoadTexture("/assets/JumpAndFall2.png");
        player->morrer.textura = LoadTexture("/assets/Morrer.png");
    }



    player->parado.num_frames = 1;
    player->andar.num_frames = 8;
    player->atacar.num_frames = 10;
    player->pular.num_frames = 1;
    player->cair.num_frames = 1;
    player->morrer.num_frames = 4;

    player->parado.actual_frame = 0;
    player->andar.actual_frame = 0;
    player->pular.actual_frame = 0;
    player->atacar.actual_frame = 0;
    player->cair.actual_frame = 0;
    player->morrer.actual_frame = 0;

}

void atualizarPersonagem(objPersonagem *player, Rectangle chao, float delta) {
    if(IsKeyDown(player->controle.direita)) {
        player->posicao.x += 8.0f;
    }
    else if (IsKeyDown(player->controle.esquerda)) {
        player->posicao.x -= 8.0f;
    }

    if (IsKeyDown(player->controle.cima) && player->pulando == 0){
        player->velocidade = -VELOCIDADE_PULO;
        player->posicao.y -= 5.0f;
        player->pulando = 1;
    }

     if(IsKeyPressed(player->controle.ataque)){
        player->atk = 1;
    }

    if(CheckCollisionRecs(player->corpo, chao)) {
        player->pulando = 0;
    }
    else{
        player->posicao.y += player->velocidade * delta;//nao entendi, o y nao deveria diminuir?, nao o player ta caindo aqui, o y aumenta mesmo
        player->velocidade += G*delta;
    }

    if(player->index == 1) {
            player->ataque = (Rectangle) {player->posicao.x + LARGURA_PERSONAGEM-17, player->posicao.y + (ALTURA_PERSONAGEM/4), ALCANCE_ATAQUE, 20};
        }
        else if(player->index == 2) {
            player->ataque = (Rectangle) {player->posicao.x - ALCANCE_ATAQUE + 75, player->posicao.y + (ALTURA_PERSONAGEM/4), ALCANCE_ATAQUE, 20};
        }

        player->corpo = (Rectangle) { player->posicao.x - 20, player->posicao.y - 40, LARGURA_PERSONAGEM, ALTURA_PERSONAGEM };
}

void checarParede(objPersonagem *player) {
    if(player->posicao.x <= 0){
        player->posicao.x = 0;
    }
    else if(player-> posicao.x >= GetScreenWidth() - LARGURA_PERSONAGEM +16){//acho que esse +16 é desnecessario
        player->posicao.x = GetScreenWidth() - LARGURA_PERSONAGEM +16;
    }
}

void ataque(objPersonagem *player, objPersonagem *player_2) {
    if(CheckCollisionRecs(player->ataque, player_2->corpo)) {
        player_2->vida -= player->dano;
        //  if(GetSoundsPlaying() < 2) {
        //      PlaySoundMulti(player_2->somReceberDano);    
        // }
}
