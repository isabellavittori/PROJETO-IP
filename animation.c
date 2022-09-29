#include "animation.h"
#include "raylib.h"
#include "character.h"


void animacaoPersonagem(objPersonagem *player, int frameCounter){// provavelmente nao vai passar esse fim de jogo

    int multipliyer = 1;
    if(player->index == 1){
        multipliyer = 1;
    }
    else if(player->index == 2) {
        multipliyer = -1;
    }

    if(player->vida <=0){
        DrawTextureRec(player->morrer.textura, (Rectangle){player->morrer.actual_frame * player->morrer.textura.width/player->morrer.num_frames, 0, player->morrer.textura.width/player->morrer.num_frames, player->andar.textura.height}, player->posicao, RAYWHITE);
        // if(player->morrer.actual_frame == player->morrer.num_frames - 1){
        //         (*fimDeJogo) = 1;
        // }
        /*else*/ if(frameCounter <= 60/200){
            player->morrer.actual_frame = (player->morrer.actual_frame + 1) % player->morrer.num_frames;
        }

    }

    else if (IsKeyDown(player->controle.direita) && player->pulando == 0 && player->atk == 0){
        // float player_andar_direita_timer = 0.0f;
        // float player_width_andar = (float)(player->andar.textura.width/8);
        
        // int player_andar_direira_frame = 0;
        // int max_frames_andar_direita = (int)(player->andar.textura.width/(int)player_width_andar);
        
        // player_andar_direita_timer += GetFrameTime();

        // if(player_andar_direita_timer >= 0.1f) {
        //     player_andar_direita_timer = 0.0f;
        //     player_andar_direira_frame += 1;
        // }

        // player_andar_direira_frame = player_andar_direira_frame % max_frames_andar_direita;
       
        // Rectangle player_rec_andar = (Rectangle){(player_width_andar * player_andar_direira_frame), 0, player_width_andar, (float)player->andar.textura.height};
        // DrawTextureRec(player->andar.textura, player_rec_andar, player->posicao, RAYWHITE);

        DrawTextureRec(player->andar.textura, (Rectangle){player->andar.actual_frame * player->andar.textura.width/player->andar.num_frames, 0, player->andar.textura.width/player->andar.num_frames, player->andar.textura.height}, player->posicao, WHITE);

        if(frameCounter <= 60/50){//ainda nao entendi muito bem
            player->andar.actual_frame = (player->andar.actual_frame + 1) % player->andar.num_frames;
        }

    }
    else if(IsKeyDown(player->controle.esquerda)  && player->pulando == 0 && player->atk == 0) {
        DrawTextureRec(player->andar.textura, (Rectangle){player->andar.actual_frame * player->andar.textura.width/player->andar.num_frames, 0, -player->andar.textura.width/player->andar.num_frames, player->andar.textura.height}, player->posicao, WHITE);
        if(frameCounter <= 60/50){
            player->andar.actual_frame = (player->andar.actual_frame + 1) % player->andar.num_frames;
        }
    }
    else if (player->pulando == 1 && player->atk == 0){
        if(player->velocidade <0){
            DrawTextureRec(player->pular.textura, (Rectangle){0, 0,multipliyer* player->pular.textura.width, player->pular.textura.height}, player->posicao, WHITE);
        }else{
            DrawTextureRec(player->cair.textura, (Rectangle){0, 0,multipliyer* player->cair.textura.width, player->cair.textura.height}, player->posicao, WHITE);
        }
        
    }
        
    else if(player->atk == 1){
        if(player->index == 1){
            DrawTextureRec(player->atacar.textura, (Rectangle){player->atacar.actual_frame * player->atacar.textura.width/player->atacar.num_frames, 0, multipliyer*player->atacar.textura.width/player->atacar.num_frames, player->atacar.textura.height}, player->posicao, WHITE);
            
        }   
        else if(player->index == 2){
            DrawTextureRec(player->atacar.textura, (Rectangle){player->atacar.actual_frame * player->atacar.textura.width/player->atacar.num_frames, 0, multipliyer*player->atacar.textura.width/player->atacar.num_frames, player->atacar.textura.height}, (Vector2){player->posicao.x - 150, player->posicao.y}, WHITE);
           
        }
        
        if(frameCounter <= 60/50){
            player->atacar.actual_frame = (player->atacar.actual_frame + 1) % player->atacar.num_frames;
            if(player->atacar.actual_frame == player->atacar.num_frames - 1){
                player->atk = 0;
            }
        }
    }
    else{
        DrawTextureRec(player->parado.textura, (Rectangle){0,0,multipliyer* player->parado.textura.width,player->parado.textura.height}, player->posicao, WHITE);
    }
}

void terminarAnimacao(objPersonagem *player){
    UnloadTexture(player->parado.textura);
    UnloadTexture(player->atacar.textura);
    UnloadTexture(player->pular.textura);
    UnloadTexture(player->andar.textura);
    UnloadTexture(player->cair.textura);
    UnloadTexture(player->morrer.textura);
}
