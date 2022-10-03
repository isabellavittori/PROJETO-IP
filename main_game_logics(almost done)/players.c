#include "raylib.h"
#include "libs/raymath.h"
#include <math.h>


/*Essa função do personagem vai ter que receber o retangulo do chao e o vector2 do chao tbm
Rectangle chao = {0.0f, 0.0f, GetScreenWidth(), chao_text.height};
Vector2 chao_pos = {0, GetScreenHeight() - 115};
Vai ter que passar tbm o contador de frames
*/

typedef struct{
    int life;
    int dano;
    Texture2D Death;
    Texture2D Run;
    Texture2D Idle;
    Texture2D Attack;
    Texture2D Jump;
    Rectangle frameDeath;
    Rectangle frameRun;
    Rectangle frameIdle;
    Rectangle frameAttack;
    Rectangle frameJump;
    Vector2 posicao;
    Vector2 velocidade;
}Player;

bool isPlayerOnGround(Texture2D *Run, Vector2 *posicao, Vector2 *chao_pos){
    if(posicao->y + Run->height >= chao_pos->y) {
        return true;
    }
    else {
        return false;
    }
}

int main(void){

    //const int screenWidth = GetScreenWidth();
    //const int screenHeight = GetScreenHeight();
    const int personagemSpeed = 5;
    const int gravity = 1;

    unsigned frameIndex = 0;
    unsigned frameIndex_2 = 0;
    unsigned frameDelay = 5;
    unsigned frameCounter = 0;

    float distance_1 = 0;
    float distance_2 = 0;

    float x1 = 150;
    float y1 = 100;

    bool flag_attack_1 = false;
    bool flag_idle_1 = false;
    bool flag_attack_2 = false;
    bool flag_idle_2 = false;
    bool flag_attack_occur_1 = false;
    bool flag_attack_occur_2 = false;

    InitWindow(GetScreenWidth(), GetScreenHeight(), "raylib [core] example - basic window");

    Vector2 ball = {(float)x1, (float)y1};
    
    Texture2D chao_texture = LoadTexture("/assets/background_chao.png");
    Rectangle chao_rec = {0.0f, 0.0f, GetScreenWidth(), chao_texture.height};
    Vector2 chao_pos = {0, GetScreenHeight() - 115};

    Player player[2];

    player[0].Death = LoadTexture("/assets/Morrer.png");
    player[0].Run = LoadTexture("/assets/Run.png");
    player[0].Idle = LoadTexture("/assets/Idle.png");
    player[0].Attack = LoadTexture("/assets/attack.png");
    player[0].Jump = LoadTexture("/assets/jump_and_fall.png");

    player[1].Death = LoadTexture("/assets/Morrer_2.png");
    player[1].Run = LoadTexture("/assets/Run_2.png");
    player[1].Idle = LoadTexture("/assets/Idle_2.png");
    player[1].Attack = LoadTexture("/assets/attack_2.png");
    player[1].Jump = LoadTexture("/assets/jump_and_fall.png");


    player[0].frameDeath = (Rectangle){0.0f, 0.0f, (float)player[0].Death.width/4, (float)player[0].Death.height};
    player[0].frameRun = (Rectangle){0.0f, 0.0f, (float)player[0].Run.width/8, (float)player[0].Run.height};
    player[0].frameIdle = (Rectangle){0.0f, 0.0f, (float)player[0].Idle.width, (float)player[0].Idle.height};
    player[0].frameAttack = (Rectangle){0.0f, 0.0f, (float)player[0].Attack.width/10, (float)player[0].Attack.height};
    player[0].frameJump = (Rectangle){0.0f, 0.0f, (float)player[0].Jump.width/2, (float)player[0].Jump.height};

    player[0].posicao = (Vector2){0, chao_pos.y - player[0].Run.height};
    player[0].velocidade = (Vector2){0.0f, 0.0f};


    player[1].frameDeath = (Rectangle){0.0f, 0.0f, (float)player[1].Death.width/4, (float)player[1].Death.height};
    player[1].frameRun = (Rectangle){0.0f, 0.0f, (float)player[1].Run.width/8, (float)player[1].Run.height};
    player[1].frameIdle = (Rectangle){0.0f, 0.0f, (float)player[1].Idle.width, (float)player[1].Idle.height};
    player[1].frameAttack = (Rectangle){0.0f, 0.0f, (float)player[1].Attack.width/10, (float)player[1].Attack.height};
    player[1].frameJump = (Rectangle){0.0f, 0.0f, (float)player[1].Jump.width/2, (float)player[1].Jump.height};

    player[1].posicao = (Vector2){1200, chao_pos.y - player[1].Run.height};
    player[1].velocidade = (Vector2){0.0f, 0.0f};

    player[0].life = 200;
    player[1].life = 200;

    player[0].dano = 10;
    player[1].dano = 10;

    SetTargetFPS(60);

    //----------------------------------------------- 
    //Main Game Loop

    while(!WindowShouldClose()){
        if(isPlayerOnGround(&player[0].Run, &player[0].posicao, &chao_pos)){
            if(IsKeyDown(KEY_D)){
                player[0].velocidade.x = personagemSpeed;
                if(player[0].frameRun.width < 0){
                    player[0].frameRun.width = -player[0].frameRun.width;
                }
            }
            else if(IsKeyDown(KEY_A)){
                player[0].velocidade.x = -personagemSpeed;
                if(player[0].frameRun.width > 0){
                    player[0].frameRun.width = -player[0].frameRun.width;
                }
            }
            else if(IsKeyDown(KEY_F)){
                flag_attack_1 = true;
                player[0].velocidade.x = 0.0f;
            }
            else if(IsKeyDown(KEY_W)){
                player[0].velocidade.y = -2 * (personagemSpeed + 3);
            }
            else{
                flag_idle_1 = true;
                player[0].velocidade.x = 0.0f;
            }
        }

         if(isPlayerOnGround(&player[1].Run, &player[1].posicao, &chao_pos)){
            if(IsKeyDown(KEY_RIGHT)){
                player[1].velocidade.x = personagemSpeed;
                if(player[1].frameRun.width < 0){
                    player[1].frameRun.width = -player[1].frameRun.width;
                }
            }
            else if(IsKeyDown(KEY_LEFT)){
                player[1].velocidade.x = -personagemSpeed;
                if(player[1].frameRun.width > 0){
                    player[1].frameRun.width = -player[1].frameRun.width;
                }
            }
            else if(IsKeyDown(KEY_L)){
                flag_attack_2 = true;
                player[1].velocidade.x = 0.0f;
            }
            else if(IsKeyDown(KEY_UP)){
                player[1].velocidade.y = -2 * (personagemSpeed + 3);
            }
            else{
                flag_idle_2 = true;
                player[1].velocidade.x = 0.0f;
            }
        }


        bool movimentacaoPlayer_1 = player[0].velocidade.x != 0.0f || player[0].velocidade.y != 0.0f;
        player[0].posicao = Vector2Add(player[0].posicao, player[0].velocidade);
        bool PlayerIsOnGround_1 = isPlayerOnGround(&player[0].Run, &player[0].posicao, &chao_pos);

        bool movimentacaoPlayer_2 = player[1].velocidade.x != 0.0f || player[1].velocidade.y != 0.0f;
        player[1].posicao = Vector2Add(player[1].posicao, player[1].velocidade);
        bool PlayerIsOnGround_2 = isPlayerOnGround(&player[1].Run, &player[1].posicao, &chao_pos);


        if(PlayerIsOnGround_1) {
            player[0].velocidade.y = 0;
            player[0].posicao.y = chao_pos.y - player[0].Run.height;
        }
        else {
            player[0].velocidade.y += gravity;
        }

        if(player[0].posicao.x <= 0) {
            player[0].posicao.x = 0;
        }

        if(player[0].posicao.x >= GetScreenWidth() + 1200) {
            player[0].posicao.x = GetScreenWidth() + 1200;
        }





        if(PlayerIsOnGround_2) {
            player[1].velocidade.y = 0;
            player[1].posicao.y = chao_pos.y - player[1].Run.height;
        }
        else {
            player[1].velocidade.y += gravity;
        }

        if(player[1].posicao.x <= 0) {
            player[1].posicao.x = 0;
        }

        if(player[1].posicao.x >= GetScreenWidth() + 1200) { //acho que vai ter que mudar
            player[1].posicao.x = GetScreenWidth() + 1200;
        }


        distance_1 = sqrt((player[0].posicao.x - player[1].posicao.x) * (player[0].posicao.x - player[1].posicao.x) + (player[0].posicao.y - player[1].posicao.y) * (player[0].posicao.y - player[1].posicao.y));
        distance_2 = sqrt((player[1].posicao.x - player[0].posicao.x) * (player[1].posicao.x - player[0].posicao.x) + (player[1].posicao.y - player[0].posicao.y) * (player[1].posicao.y - player[0].posicao.y));

        ++frameCounter;
        if(frameCounter > frameDelay) {
            frameCounter = 0;

            if(movimentacaoPlayer_1){
                if(PlayerIsOnGround_1){
                    ++frameIndex;
                    frameIndex %= 8;
                    player[0].frameRun.x = (float)player[0].Run.width/8 * frameIndex;
                }
                else if(PlayerIsOnGround_1 && flag_idle_1 == true){
                    ++frameIndex;
                    frameIndex %= 1;
                    player[0].frameIdle.x = (float)player[0].Idle.width * frameIndex;
                }
                else{
                    if(player[0].velocidade.y < 0){
                        frameIndex = 0;
                    }
                    else{
                        frameIndex = 1;
                    }
                    player[0].frameJump.x = (float)player[0].Jump.width/2 * frameIndex;
                }
            }

            else if(PlayerIsOnGround_1 && flag_attack_1 == true && distance_1 <= 250){
                flag_attack_occur_1 = true;
            }

            if(PlayerIsOnGround_1 && flag_attack_1 == true){
                ++frameIndex;
                frameIndex %= 10;
                player[0].frameAttack.x = (float)player[0].Attack.width/10 * frameIndex;
                if(player[0].frameAttack.x == 315){
                    flag_attack_1 = false;
                }
            }

            if(PlayerIsOnGround_1 && player[0].life <= 0){//acho que aqui é else if
                ++frameIndex;
                frameIndex %= 4;
                player[0].frameDeath.x = (float)player[0].Death.width/4 * frameIndex;
            }





            if(movimentacaoPlayer_2){
                if(PlayerIsOnGround_2){
                    ++frameIndex_2;
                    frameIndex_2 %= 8;
                    player[1].frameRun.x = (float)player[1].Run.width/8 * frameIndex_2;
                }
                else if(PlayerIsOnGround_2 && flag_idle_2 == true){
                    ++frameIndex_2;
                    frameIndex_2 %= 1;
                    player[1].frameIdle.x = (float)player[1].Idle.width * frameIndex_2;
                }
                else{
                    if(player[1].velocidade.y < 0){
                        frameIndex_2 = 0;
                    }
                    else{
                        frameIndex_2 = 1;
                    }
                    player[1].frameJump.x = (float)player[1].Jump.width/2 * frameIndex_2;
                }
            }
            else if(PlayerIsOnGround_2 && flag_attack_2 == true && distance_2 <= 250){
                flag_attack_occur_2 = true;
            }

            if(PlayerIsOnGround_2 && flag_attack_2 == true){
                ++frameIndex_2;
                frameIndex_2 %= 10;
                player[1].frameAttack.x = (float)player[1].Attack.width/10 * frameIndex_2;
                if(player[1].frameAttack.x == 315){
                    flag_attack_2 = false;
                }
            }

        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTextureRec(chao_texture, chao_rec, chao_pos, WHITE);

        if(movimentacaoPlayer_1 && PlayerIsOnGround_1){
            DrawTextureRec(player[0].Run, player[0].frameRun, player[0].posicao, WHITE);
        }
        else if(PlayerIsOnGround_1 && flag_attack_1 == true){
            DrawTextureRec(player[0].Attack, player[0].frameAttack, player[0].posicao, WHITE);
            if(flag_attack_occur_1 == true){
                DrawCircleV(ball, 50, GOLD);
                flag_attack_occur_1 = false;
                player[1].life -= player[0].dano;
            }
        }
        else if(PlayerIsOnGround_1 && flag_idle_1 == true){
            DrawTextureRec(player[0].Idle, player[0].frameIdle, player[0].posicao, WHITE);
        }
        else if(PlayerIsOnGround_1 && player[0].life <= 0){
            DrawTextureRec(player[0].Death, player[0].frameDeath, player[0].posicao, WHITE);
            //flag end of round
            //go to next round
        }
        else{
            DrawTextureRec(player[0].Jump, player[0].frameJump, player[0].posicao, WHITE);
        }

        

        if(movimentacaoPlayer_2 && PlayerIsOnGround_2){
            DrawTextureRec(player[1].Run, player[1].frameRun, player[1].posicao, WHITE);
        }
        else if(PlayerIsOnGround_2 && flag_attack_2 == true){
            DrawTextureRec(player[1].Attack, player[1].frameAttack, player[1].posicao, WHITE);
            if(flag_attack_occur_2 == true){
                DrawCircleV(ball, 50, MAROON);
                flag_attack_occur_2 = false;
                player[0].life -= player[1].dano;
            }
        }
        else if(PlayerIsOnGround_2 && flag_idle_2 == true){
            DrawTextureRec(player[1].Idle, player[1].frameIdle, player[1].posicao, WHITE);
        }
        else{
            DrawTextureRec(player[1].Jump, player[1].frameJump, player[1].posicao, WHITE);
        }



        EndDrawing();

    }

    for(int i = 0; i < 2; ++i){
        UnloadTexture(player[i].Run);
        UnloadTexture(player[i].Idle);
        UnloadTexture(player[i].Attack);
        UnloadTexture(player[i].Jump);
    }

    UnloadTexture(chao_texture);

    CloseWindow();

    return 0;
}
